#include "qsocketbdnetclient.h"

static inline QByteArray IntToArray(qint32 source);
static inline qint32 ArrayToInt(QByteArray source);


QSocketBDNetClient::QSocketBDNetClient(QObject *parent) : QObject(parent)
{
    mHeartbeatTimer = new QTimer(); // Вместо shared_ptr
    mHeartbeatTimer->setSingleShot(false);
    mHeartbeatTimer->moveToThread(&m_thread);

    m_thread.setObjectName("CarshServiceNetClient");
    moveToThread(&m_thread);

    connect(&m_thread, &QThread::finished,
            this, &QSocketBDNetClient::cleanup);

    m_thread.start();
}

QSocketBDNetClient::~QSocketBDNetClient()
{
    QMetaObject::invokeMethod(this, &QSocketBDNetClient::cleanup,
                              Qt::BlockingQueuedConnection);

    m_thread.quit();
    m_thread.wait(1000);
}

void QSocketBDNetClient::cleanup()
{
    QMutexLocker locker(&m_bufferMutex);
    m_pendingData.clear();

    if (mReconnectTimer && mReconnectTimer->isActive()) {
        mReconnectTimer->stop();
    }

    if(mHeartbeatTimer && mHeartbeatTimer->isActive()) {
        mHeartbeatTimer->stop();
    }

    if(socket) {
        socket->disconnectFromHost();
        if(socket->state() == QAbstractSocket::ConnectedState) {
            socket->waitForDisconnected(1000);
        }
        socket->deleteLater();
        socket = nullptr;
    }

    delete m_buffer;
    m_buffer = nullptr;

    delete m_size;
    m_size = nullptr;
}

bool QSocketBDNetClient::connectToHost()
{

    // Перенести создание объектов в поток
    QMetaObject::invokeMethod(this, [this]() {

        if (socket) {
                socket->deleteLater();
                socket = nullptr;
            }


        // Создаем объекты внутри потока
        socket = new QTcpSocket();
        m_buffer = new QByteArray();
        m_size = new qint32(0);


        // Подключаем обработчики событий сокета
        connect(socket, &QTcpSocket::readyRead, this, &QSocketBDNetClient::readyRead);
        connect(socket, &QTcpSocket::disconnected, this, [this]() {
            qDebug() << "Disconnected, attempting to reconnect...";
            emit disconnected();
            if (mReconnectTimer) {
                QMetaObject::invokeMethod(mReconnectTimer, "start", Qt::QueuedConnection);
            }
        });

        connect(socket, QOverload<QAbstractSocket::SocketError>::of(&QAbstractSocket::errorOccurred),
                [this](QAbstractSocket::SocketError error) {
                    qDebug() << "Socket error:" << socket->errorString();
                    emit errorOccurred(socket->errorString());
                    // Сброс флага переподключения при ошибке
                    mIsReconnecting = false; // Сброс флага при ошибке
                    if (mReconnectTimer && !mReconnectTimer->isActive()) {
                        mReconnectTimer->start(); // Перезапуск таймера
                    }
                });

        if (!mReconnectTimer) {
            mReconnectTimer = new QTimer();
            mReconnectTimer->setInterval(mReconnectInterval);
            mReconnectTimer->setSingleShot(true); // Однократный запуск
            mReconnectTimer->moveToThread(&m_thread);

            connect(mReconnectTimer, &QTimer::timeout, this, [this]() {
                if (!mIsReconnecting && socket && socket->state() == QAbstractSocket::UnconnectedState) {
                    qDebug() << "Reconnecting via timer...";
                    mIsReconnecting = true;
                    socket->connectToHost("188.243.205.147", 3333);
                }
            });
        }

        mHeartbeatTimer = new QTimer(this);
        connect(mHeartbeatTimer, &QTimer::timeout,
                this, &QSocketBDNetClient::OnProcessingHeartbeatTimer);

        socket->connectToHost("188.243.205.147", 3333);

        // Асинхронное ожидание подключения
        connect(socket, &QTcpSocket::connected, [this]() {
            mIsReconnecting = false;
            mHeartbeatTimer->start(m_iHeartbeatTime);
            mReconnectTimer->stop();
            emit connected();

            // Отправка данных из буфера
            QMutexLocker locker(&m_bufferMutex);
            while (!m_pendingData.isEmpty()) {
                QByteArray data = m_pendingData.takeFirst();
                socket->write(IntToArray(data.size()));
                socket->write(data);
                qDebug() << "Buffered data sent successfully";
            }
        });
    }, Qt::QueuedConnection);

    return true;
}
void QSocketBDNetClient::OnProcessingHeartbeatTimer()
{
    mHeartbeatTimer->stop();

    if(socket->state() == QAbstractSocket::ConnectedState)
    {
        QByteArray data;
        data.append('h');
        data.append('b');
        data.append('d');
        data.append('t');

        writeData(data); //write the data itself
    }

    mHeartbeatTimer->start(m_iHeartbeatTime);
}

bool QSocketBDNetClient::writeData(QByteArray data)
{

    QMetaObject::invokeMethod(this, [this, data]() {
        QMutexLocker lock(&m_bufferMutex);

        if (socket && socket->state() == QAbstractSocket::ConnectedState) {
            // Отправка данных, если соединение активно
            socket->write(IntToArray(data.size()));
            socket->write(data);
        } else {
            // Буферизация данных
            m_pendingData.append(data);
            qDebug() << "Data buffered. Buffer size:" << m_pendingData.size();

            // Немедленная попытка переподключения, если оно еще не начато
            if (!mIsReconnecting){// && mReconnectTimer && !mReconnectTimer->isActive()) {
                qDebug() << "Immediate reconnect attempt";
                mIsReconnecting = true;
                socket->connectToHost("188.243.205.147", 3333);
            }
            // Запуск таймера для последующих попыток
            if (mReconnectTimer) {
                mReconnectTimer->start();
            }
        }
    }, Qt::QueuedConnection);

    return true;

}



void QSocketBDNetClient::readyRead()
{
    QByteArray *buffer = m_buffer;
    qint32 *s = m_size;
    qint32 size = *s;
    while (socket->bytesAvailable() > 0)
    {
        buffer->append(socket->readAll());
        while ((size == 0 && buffer->size() >= 4) || (size > 0 && buffer->size() >= size)) //While can process data, process it
        {
            if (size == 0 && buffer->size() >= 4) //if size of data has received completely, then store it on our global variable
            {
                size = ArrayToInt(buffer->mid(0, 4));
                *s = size;
                buffer->remove(0, 4);
            }
            if (size > 0 && buffer->size() >= size) // If data has received completely, then emit our SIGNAL with the data
            {
                m_LastData = buffer->mid(0, size);
                buffer->remove(0, size);
                size = 0;
                *s = size;
                emit dataReceived();
            }
        }
    }
}


qint32 ArrayToInt(QByteArray source)
{
    qint32 temp;
    QDataStream data(&source, QIODevice::ReadWrite);
    data >> temp;
    return temp;
}

QByteArray IntToArray(qint32 source) //Use qint32 to ensure that the number have 4 bytes
{
    //Avoid use of cast, this is the Qt way to serialize objects
    QByteArray temp;
    QDataStream data(&temp, QIODevice::ReadWrite);
    data << source;
    return temp;
}
