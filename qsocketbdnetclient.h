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


signals:
    void dataReceived();

    // void connected();
    // void disconnected();
    // void errorOccurred(const QString& error);

private slots:
    void readyRead();
    void OnProcessingHeartbeatTimer();

private:
    QTcpSocket *socket;
    QByteArray *m_buffer; //We need a buffer to store data until block has completely received
    qint32 *m_size;
    QThread m_thread;
    //std::shared_ptr<QTimer> mHeartbeatTimer;
    QTimer * mHeartbeatTimer;
    const int m_iHeartbeatTime = 25000;//msecs

    void cleanup();
};

#endif // QSOCKETBDNETCLIENT_H
