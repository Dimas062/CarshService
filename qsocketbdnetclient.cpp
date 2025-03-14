#include "qsocketbdnetclient.h"

static inline QByteArray IntToArray(qint32 source);
static inline qint32 ArrayToInt(QByteArray source);


QSocketBDNetClient::QSocketBDNetClient(QObject *parent) : QObject(parent)
{
    // m_thread.setObjectName("CarshServiceNetClient");
    // moveToThread(&m_thread);
    // m_thread.start();

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
    // socket = new QTcpSocket(this);
    // connect(socket, SIGNAL(readyRead()), SLOT(readyRead()));
    // m_buffer = new QByteArray();
    // m_size= new qint32(0);
    // mHeartbeatTimer = std::make_shared<QTimer>(this);
    // connect(mHeartbeatTimer.get() , &QTimer::timeout , this , &QSocketBDNetClient::OnProcessingHeartbeatTimer);
    // socket->connectToHost("188.243.205.147", 3333);
    // if(socket->waitForConnected())
    // {
    //     mHeartbeatTimer->start(m_iHeartbeatTime);
    //     return true;
    // }

    // return false;
    // Перенести создание объектов в поток
    QMetaObject::invokeMethod(this, [this]() {
        // Создаем объекты внутри потока
        socket = new QTcpSocket();
        m_buffer = new QByteArray();
        m_size = new qint32(0);

        connect(socket, &QTcpSocket::readyRead,
                this, &QSocketBDNetClient::readyRead);

        mHeartbeatTimer = new QTimer(this);
        connect(mHeartbeatTimer, &QTimer::timeout,
                this, &QSocketBDNetClient::OnProcessingHeartbeatTimer);

        socket->connectToHost("188.243.205.147", 3333);

        // Асинхронное ожидание подключения
        connect(socket, &QTcpSocket::connected, [this]() {
            mHeartbeatTimer->start(m_iHeartbeatTime);
            //emit connected();
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
    // if(socket->state() != QAbstractSocket::ConnectedState)//Попытка переподключиться
    // {
    //     socket->connectToHost("188.243.205.147", 3333);

    //     socket->waitForConnected();
    // }

    // qDebug()<<"QSocketBDNetClient::writeData 2";

    // if(socket->state() == QAbstractSocket::ConnectedState)
    // {

    //     socket->write(IntToArray(data.size())); //write size of data

    //     socket->write(data); //write the data itself

    //     return socket->waitForBytesWritten();

    // }
    // else
    //     return false;

    // Асинхронный вызов без блокировки
    QMetaObject::invokeMethod(this, [this, data]() {
        if(!socket || socket->state() != QAbstractSocket::ConnectedState) {
            qDebug() << "Socket not connected";
            return;
        }

        socket->write(IntToArray(data.size()));
        socket->write(data);
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
