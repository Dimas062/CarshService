#ifndef INTERACTIONCLIENT_H
#define INTERACTIONCLIENT_H

#include <QObject>
#include <QThread>
#include <QUuid>
#include <QTimer>
#include <QEventLoop>
#include <QUuid>
#include <QTime>
#include <QDateTime>
#include <QDate>
#include <QStringList>
#include <QMap>
#include <QTcpSocket>
#include <QQueue>
#include <QEventLoop>
#include "networkparsermachine.h"
#include "interactionprotocol.h"

///
/// \brief The InteractionClient class взаимодействие с СА
///
class InteractionClient : public QObject
{
    Q_OBJECT
private:
    explicit InteractionClient();
    ~InteractionClient();
    InteractionClient(InteractionClient const&) = delete;
    InteractionClient& operator= (InteractionClient const&) = delete;

    void ProcessingQueueFromSA();    ///< обработка очереди приёма от СА
    void SendMessageToSA(NetworkMessage message);  ///< отправить сообщение в СА
public:
    static InteractionClient& getInstance()
    {
        static InteractionClient s;
        return s;
    }
    Q_INVOKABLE bool start(); ///< старт модуля

    /*Онлайн видео, камера.*/
    ///
    /// \brief startVideoStream старт видеопотока камеры - неблокирующий
    /// \param cameraUid уид камеры
    /// \param videoStreamUid уид потока
    /// \return уид запроса
    ///
    Q_INVOKABLE QUuid startVideoStream(const QUuid & cameraUid, const QUuid & videoStreamUid);


    ///
    /// \brief stopVideoStream стоп видеопотока камеры - неблокирующий
    /// \param cameraUid уид камеры
    /// \param videoStreamUid уид потока
    /// \return уид запроса
    ///
    Q_INVOKABLE QUuid stopVideoStream(const QUuid &, const QUuid& videoStreamUid);


    /*Архив видео, камера создание*/
    ///
    /// \brief startArchiveVideoStream запрос архива камеры - неблокирующий
    /// \param videoUid уид видеоотрезка
    /// \param videoStreamUid УНИКАЛЬНЫЙ уид потока
    /// \param startSecond секунда с начала отрезка
    /// \param playbackSpeed скорость воспроизведения, 1 - нормальная
    /// \return уид запроса
    ///
    Q_INVOKABLE QUuid createArchiveVideoStream(const QUuid & videoUid,const  double & startSecond,const  double & playbackSpeed);


    ///
    /// \brief startArchiveVideoStream старт архива камеры - неблокирующий
    /// \param videoUid UID видеозаписи
    /// \param videoStreamUid УНИКАЛЬНЫЙ идентификатор RTSP потока
    /// \return уид запроса
    ///
    Q_INVOKABLE QUuid startArchiveVideoStream(const QUuid & videoUid);


    ///
    /// \brief stopArchiveVideoStream стоп архива камеры - неблокирующий
    /// \param videoUid UID видеозаписи
    /// \param videoStreamUid УНИКАЛЬНЫЙ идентификатор RTSP потока
    /// \return уид запроса
    ///
    Q_INVOKABLE QUuid stopArchiveVideoStream(const QUuid & videoUid);


    ///
    /// \brief getScreenShot получить скриншот с камеры - неблокирующий
    /// \param mVideoStreamUid;          ///< уид видеопотока
    /// \param Time mDateTimeSreenshot;	///< дата-время скриншота
    /// \param mTargetOutputResolution;  ///< целевое выходное разрешение скриншота
    Q_INVOKABLE QUuid getScreenShot(const QUuid & VideoStreamUid , const QDateTime & DateTimeScreenshot , const QSize & TargetOutputResolution);


    ///
    /// \brief containsResponse проверка наличия ответа от СА - неблокирующий
    /// \param uidRequest уид запроса
    /// \return признак наличия
    ///
    bool containsResponse(const QUuid& uidRequest);
    ///
    /// \brief getResponse получить ответ от СА - неблокирующий
    /// \param uidRequest уид запроса
    /// \param message ответ от СА
    /// \return признак наличия
    ///
    bool getResponse(const QUuid& uidRequest, NetworkMessage& message);
    bool hasAuthorizated();
    bool licenseValid();
    Q_INVOKABLE void disconnect();
signals:
    void notifyEvent(QUuid eventUid);
    //void listAvailableCamerasSignal(QVector<AvailableCameraProperties>);
    void videoCameraRtspStarted(QString);
    void videoCameraRtspStopped();
    void videoCameraArchiveCreated(QString);
    void videoCameraArchiveStarted();
    void videoCameraArchiveStopped();
    void serverConnectStatusChanged(QString);
    void screenShotGetet(QImage);
private slots:
    void onReceiveDataBySocket();   ///< приём данных от СА
    void onDisconnectSocket();      ///< дисконнект от СА
    void onConnectSocket();         ///< коннект к СА
    void onReconnectionTimer();     ///< переподключение к СА
    void onProcessingHeartbeatTimer();  ///< отработка таймера хардбита



    void onResponseAuthorization(const NetworkMessage& message);
    void onResponseStartPlayCamera(const NetworkMessage& message);
    void onResponseStopPlayCamera(const NetworkMessage& message);
    void onResponseStartArchiveCamera(const NetworkMessage& message);
    void onResponseStopArchiveCamera(const NetworkMessage& message);
    void onResponseCreateArchiveCamera(const NetworkMessage& message);
    void onResponseGetScreenShot(const NetworkMessage& message);
    void onResponseLicence(const NetworkMessage&message);

    //void onLicenseTimer();
    void onRequestNotifyEvent(const NetworkMessage& message);
private:
    QThread mThread;
    std::shared_ptr<QTcpSocket> mSocket;    ///< сокет для связи с СА
    bool mHasConnectedToHost = false;       ///< признак приконнекченности к СА
    bool mHasAuthorizated = false;          ///< признак авторизованности в СА

    std::shared_ptr<NetworkParserMachine> mInputParser; ///< парсер входных сообщений от СА

    QQueue<NetworkMessage> mQueueFromSA;    ///< очередь приёма от СА

    std::shared_ptr<QTimer> mReconnectionTimer; ///< таймер переподключения к СА

    /// \todo таймер периодичского запроса лицензии
    // QTimer* mLicenseTimer = nullptr;
    // const int cLicenseTimeout = 10 * 60 * 1000;

    const qint64 cReconnectionTimeout = 5000;  ///< таймаут переподключения к СА
    const quint16 cPortSA = 65000;          ///< порт для подключения к СА
    QUuid mRtspStreamUid;   ///< уид ртсп потока для РК

    std::shared_ptr<QTimer> mHeartbeatTimer; ///< таймер обработки очереди приёма от СА


    const int m_iHeartbeatTimer = 60 * 1000;
    bool mIsInAuthProcess = false;

    std::atomic_bool mLicenseValid = {true};
};

#endif // INTERACTIONCLIENT_H
