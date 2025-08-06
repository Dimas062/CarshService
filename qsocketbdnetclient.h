#ifndef QSOCKETBDNETCLIENT_H
#define QSOCKETBDNETCLIENT_H

#include <QtCore>
#include <QtNetwork>
#include <QObject>
#include <QMetaObject>

class QSocketBDNetClient : public QObject
{
    Q_OBJECT
public:
    explicit QSocketBDNetClient(QObject *parent = 0);
    ~QSocketBDNetClient();
    QByteArray m_LastData;
    Q_INVOKABLE bool writeData(QByteArray data);
    Q_INVOKABLE bool connectToHost();

    static QSocketBDNetClient & getInstance()
    {
        static QSocketBDNetClient instance;
        return instance;
    }

    QMutex m_dataMutex;
signals:
    void dataReceived();

    void connected();
    void disconnected();
    void errorOccurred(const QString& error);

private slots:
    void readyRead();
    void OnProcessingHeartbeatTimer();

private:
    QTimer* mReconnectTimer;
    const int mReconnectInterval = 5000; // 5 секунд между попытками
    bool mIsReconnecting = false;

    QList<QByteArray> m_pendingData; //Данные, которые копятся в случае потери связи, которые нужно будет отправить при восстановлении связи
    QMutex m_bufferMutex;

    QTcpSocket *socket;
    QByteArray *m_buffer; //We need a buffer to store data until block has completely received
    qint32 *m_size;
    QThread m_thread;
    QTimer * mHeartbeatTimer;
    const int m_iHeartbeatTime = 25000;//msecs

    void cleanup();

};

#endif // QSOCKETBDNETCLIENT_H
