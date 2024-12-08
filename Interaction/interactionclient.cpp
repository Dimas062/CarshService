#include "interactionclient.h"
#include <QMetaObject>
#include <QHostAddress>
#include "licence/licence.h"
#include "../common.h"
#include <QCryptographicHash>

extern VSMobileSettings settings;

InteractionClient::InteractionClient() : QObject()
{
    mThread.setObjectName("InteractionClient");
    moveToThread(&mThread);
    mThread.start();
}

bool InteractionClient::start()
{
    mRtspStreamUid = QUuid::createUuid();
    mInputParser = std::make_shared<NetworkParserMachine>();
    mSocket = std::make_shared<QTcpSocket>(this);
    connect(mSocket.get(), &QTcpSocket::readyRead, this, &InteractionClient::onReceiveDataBySocket);
    connect(mSocket.get(), &QTcpSocket::disconnected, this, &InteractionClient::onDisconnectSocket);
    connect(mSocket.get(), &QTcpSocket::connected, this, &InteractionClient::onConnectSocket);
    mReconnectionTimer = std::make_shared<QTimer>(this);
    connect(mReconnectionTimer.get(), &QTimer::timeout, this, &InteractionClient::onReconnectionTimer);
    mHeartbeatTimer = std::make_shared<QTimer>(this);
    connect(mHeartbeatTimer.get(), &QTimer::timeout, this, &InteractionClient::onProcessingHeartbeatTimer);

    mReconnectionTimer->start(1); // onReconnectionTimer();

    ProcessingQueueFromSA();

    return true;
}

bool InteractionClient::containsResponse(const QUuid &uidRequest)
{
    auto result = false;
    auto end = mQueueFromSA.cend();
    for (auto it = mQueueFromSA.cbegin(); it != end; ++it) {
        if (it->uidRequest() == uidRequest) {
            result = true;
            break;
        }
    }
    return result;
}

bool InteractionClient::getResponse(const QUuid &uidRequest, NetworkMessage &message)
{
    auto result = false;
    auto end = mQueueFromSA.cend();
    auto index = 0;
    for (auto it = mQueueFromSA.cbegin(); it != end; ++it, index++) {
        if (it->uidRequest() == uidRequest) {
            result = true;
            auto takenMessage = mQueueFromSA.takeAt(index);
            message = takenMessage;
            break;
        }
    }
    return result;
}

bool InteractionClient::hasAuthorizated()
{
    return mHasAuthorizated;
}

bool InteractionClient::licenseValid()
{
    return mLicenseValid;
}

void InteractionClient::onReceiveDataBySocket()
{
    QTcpSocket* socket = static_cast<QTcpSocket*>(sender());
    quint64 countBytes = socket->bytesAvailable();
    if (countBytes > 0) {   // если есть данные
        QByteArray frame = socket->readAll();
        auto messages = mInputParser->step(frame);
        for(const auto& message : messages) {
            mQueueFromSA.enqueue(message);
        }

        auto count = mQueueFromSA.count();

        if (count > 200) {
            mQueueFromSA.clear();
        }
    }
    ProcessingQueueFromSA();
}

void InteractionClient::onDisconnectSocket()
{
    qDebug()<<"InteractionClient::onDisconnectSocket()";
    emit serverConnectStatusChanged("Разрыв соединения");
    mHasAuthorizated = false;
    mHasConnectedToHost = false;
    QTcpSocket* socket = static_cast<QTcpSocket*>(sender());
    qDebug("%s", qUtf8Printable(QString("InteractionClient::onDisconnectSocket(): '%1', error: %2")
                                .arg(socket->objectName())
                                .arg(socket->errorString())
                                )
           );
}

void InteractionClient::disconnect()
{
    mSocket->disconnectFromHost();
}

void InteractionClient::onConnectSocket()
{
    qDebug()<<"InteractionClient::onConnectSocket()";
    emit serverConnectStatusChanged("Соединение с " + settings.strServAdress + " устанавливается...");
    mHasConnectedToHost = true;
}

void InteractionClient::onReconnectionTimer()
{

    mReconnectionTimer->stop();
    if (!mHasConnectedToHost) { // если РК не приконнекчен к СА
        qDebug()<<"InteractionClient::onReconnectionTimer() - connectToHost - ip =" << settings.strServAdress <<"port = "<<cPortSA;
        emit serverConnectStatusChanged("Подключение к " + settings.strServAdress + "...");
        mSocket->connectToHost(
                    QHostAddress(settings.strServAdress),
                    cPortSA
                    );
    } else if (!mHasAuthorizated) { // если РК не авторизован в СА
            emit serverConnectStatusChanged("Авторизация на " + settings.strServAdress + "...");
            mIsInAuthProcess = true;
            auto request = std::make_shared<RequestAuthorization>();
            request->mLogin = settings.strServLogin;
            QString strPassMD5 =  QString(QCryptographicHash::hash(settings.strServPassword.toUtf8(), QCryptographicHash::Sha3_512).toHex());
            request->mPassword = strPassMD5;
            request->mClientType = EClientType::ClientApp;
            request->mServerIpConnectTo = settings.strServAdress;
            auto message = NetworkMessage();
            message.setJsonData(request->toJsonObject());

            SendMessageToSA(message);

            qDebug()<<"InteractionClient::onReconnectionTimer() - RequestAuthorization request->mLogin="<<request->mLogin<<" request->mPassword="<<request->mPassword;

    }
    mReconnectionTimer->start(cReconnectionTimeout);
}


void InteractionClient::onProcessingHeartbeatTimer()
{
    mHeartbeatTimer->stop();

    /*Отправляем сообщение хардбита*/
    auto request = std::make_shared<RequestHeartbeat>();
    auto message = NetworkMessage();
    message.setJsonData(request->toJsonObject());
    SendMessageToSA(message);

    mHeartbeatTimer->start(m_iHeartbeatTimer);
}

void InteractionClient::ProcessingQueueFromSA()
{

    while (!mQueueFromSA.isEmpty()) {

        auto message = mQueueFromSA.dequeue();

        auto typeMessage = message.type();
        switch (typeMessage) {
        case EDataType::ResponseAuthorization:
            onResponseAuthorization(message);
            break;

        case EDataType::RequestEventNotification:
            onRequestNotifyEvent(message);
            break;

        case EDataType::ResponseStartRtspStreamCamera:
            onResponseStartPlayCamera(message);
            break;

        case EDataType::ResponseStopRtspStreamCamera:
            onResponseStopPlayCamera(message);
            break;
        case EDataType::ResponseCreateRtspStreamVideo:
            onResponseCreateArchiveCamera(message);
            break;
        case EDataType::ResponseStartRtspStreamVideo:
            onResponseStartArchiveCamera(message);
            break;
        case EDataType::ResponseStopRtspStreamVideo:
            onResponseStopArchiveCamera(message);
            break;
        case EDataType::ResponseGetScreenshot:
            onResponseGetScreenShot(message);
            break;
        case EDataType::ResponseLicence:
            onResponseLicence(message);
            break;
        default:
            break;
        }
    }

}

void InteractionClient::SendMessageToSA(NetworkMessage message)
{
        if (mHasConnectedToHost) {
            mSocket->write(message.serialize());
        }
}


/*----------------Воспроизведение камеры----------------*/

QUuid InteractionClient::startVideoStream(const QUuid &cameraUid, const QUuid &videoStreamUid)
{
    QUuid uidRequest = QUuid::createUuid();
    auto request = std::make_shared<RequestStartRtspStreamCamera>();
    request->setUidRequest(uidRequest);
    request->mCameraUid = cameraUid;
    request->mStreamUid = videoStreamUid;
    request->mRtspStreamUid = mRtspStreamUid;
    auto message = NetworkMessage();
    message.setJsonData(request->toJsonObject());
    SendMessageToSA(message);
    qDebug("InteractionClient::startVideoStream uidRequest %s", qUtf8Printable(uidRequest.toString()));
    return uidRequest;
}

void InteractionClient::onResponseStartPlayCamera(const NetworkMessage &message)
{
    qDebug("InteractionClient::onResponseStartPlayCamera");
    auto response = std::make_shared<ResponseStartRtspStreamCamera>(message.getJsonData());
    emit videoCameraRtspStarted(response->mRtspUrl);
}

/*end----------------Воспроизведение камеры----------------------*/


/*----------------Стоп Воспроизведения камеры----------------*/
QUuid InteractionClient::stopVideoStream(const QUuid &cameraUid, const QUuid &videoStreamUid)
{
   // std::lock_guard<std::recursive_mutex> lock(mMutexQueueToSA);
    QUuid uidRequest = QUuid::createUuid();
    auto request = std::make_shared<RequestStopRtspStreamCamera>();
    request->setUidRequest(uidRequest);
    request->mCameraUid = cameraUid;
    request->mStreamUid = videoStreamUid;
    request->mRtspStreamUid = mRtspStreamUid;
    auto message = NetworkMessage();
    message.setJsonData(request->toJsonObject());
    SendMessageToSA(message);
    qDebug("InteractionClient::stopVideoStream uidRequest %s", qUtf8Printable(uidRequest.toString()));
    return uidRequest;
}


void InteractionClient::onResponseStopPlayCamera(const NetworkMessage& message)
{
    qDebug("InteractionClient::onResponseStopPlayCamera");
    emit videoCameraRtspStopped();
}

/*end----------------Стоп Воспроизведения камеры----------------*/


/*----------------Создание Воспроизведения архива камеры----------------*/
QUuid InteractionClient::createArchiveVideoStream(const QUuid & videoUid ,const double & startSecond,const double & playbackSpeed)
{
    QUuid uidRequest = QUuid::createUuid();
    auto request = std::make_shared<RequestCreateRtspStreamVideo>();
    qDebug()<<"2 createArchiveVideoStream mVideoUid="<<videoUid<<" mRtspStreamUid="<<mRtspStreamUid<<" startSecond="<<startSecond<<" playbackSpeed="<<playbackSpeed;
    request->setUidRequest(uidRequest);
    request->mVideoUid = videoUid;
    request->mVideosUuids.append(videoUid);
    request->mRtspStreamUid = mRtspStreamUid;
    request->mStartSecond = startSecond;
    request->mPlaybackSpeed = playbackSpeed;
    request->mIsNeedPreviewFrame = false;
    auto message = NetworkMessage();
    message.setJsonData(request->toJsonObject());
    SendMessageToSA(message);
    qDebug("InteractionClient::createArchiveVideoStream uidRequest %s", qUtf8Printable(uidRequest.toString()));
    return uidRequest;
}

void InteractionClient::onResponseCreateArchiveCamera(const NetworkMessage& message)
{
    auto response = std::make_shared<ResponseCreateRtspStreamVideo>(message.getJsonData());
    emit videoCameraArchiveCreated(response->mRtspUrl);
}
/*end----------------Создание Воспроизведения архива камеры----------------*/

/*----------------Запуск Воспроизведения архива камеры----------------*/
QUuid InteractionClient::startArchiveVideoStream(const QUuid & videoUid )
{
    QUuid uidRequest = QUuid::createUuid();
    auto request = std::make_shared<RequestStartRtspStreamVideo>();
    request->setUidRequest(uidRequest);
    request->mVideoUid = videoUid;
    request->mVideosUuids.append(videoUid);
    request->mRtspStreamUid = mRtspStreamUid;
    auto message = NetworkMessage();
    message.setJsonData(request->toJsonObject());
    SendMessageToSA(message);
    return uidRequest;
}

void InteractionClient::onResponseStartArchiveCamera(const NetworkMessage& message)
{
    emit videoCameraArchiveStarted();
}
/*end----------------Запуск Воспроизведения архива камеры----------------*/

/*----------------Стоп Воспроизведения архива камеры----------------*/
QUuid InteractionClient::stopArchiveVideoStream(const QUuid & videoUid)
{
    QUuid uidRequest = QUuid::createUuid();
    auto request = std::make_shared<RequestStopRtspStreamVideo>();
    request->setUidRequest(uidRequest);
    request->mVideoUid = videoUid;
    request->mRtspStreamUid = mRtspStreamUid;
    auto message = NetworkMessage();
    message.setJsonData(request->toJsonObject());
    SendMessageToSA(message);
    qDebug("InteractionClient::stopArchiveVideoStream uidRequest %s", qUtf8Printable(uidRequest.toString()));
    return uidRequest;
}



void InteractionClient::onResponseStopArchiveCamera(const NetworkMessage& message)
{
    emit videoCameraArchiveStopped();
}
/*end----------------Стоп Воспроизведения архива камеры----------------*/


/*----------------Получить скриншот камеры----------------*/

QUuid InteractionClient::getScreenShot(const QUuid & VideoStreamUid , const QDateTime & DateTimeScreenshot , const QSize & TargetOutputResolution)
{
    QUuid uidRequest = QUuid::createUuid();
    auto request = std::make_shared<RequestGetScreenshot>();
    request->setUidRequest(uidRequest);
    request->mVideoStreamUid = VideoStreamUid;
    request->mDateTimeSreenshot = DateTimeScreenshot;
    request->mTargetOutputResolution = TargetOutputResolution;
    auto message = NetworkMessage();
    message.setJsonData(request->toJsonObject());
    SendMessageToSA(message);
    return uidRequest;
}


void InteractionClient::onResponseGetScreenShot(const NetworkMessage& message)
{
    auto response = std::make_shared<ResponseGetScreenshot>(message.getJsonData());
    emit screenShotGetet(response->sreenshot());
}
/*end----------------Получить скриншот камеры----------------*/

void InteractionClient::onResponseAuthorization(const NetworkMessage &message)
{
    qDebug("InteractionClient::onResponseAuthorization");
    auto response = std::make_shared<ResponseAuthorization>(message.getJsonData());
    if (response->mResponseResult == EResult::Good) {
        mHasAuthorizated = true;
        qDebug("InteractionClient::onResponseAuthorization() - mHasAuthorizated = true");

        //Проверкf лицензии
        auto request = std::make_shared<RequestLicence>();
        request->licenceFileData = QString("check").toUtf8();
        request->trueClientUid = QUuid();
        auto message = NetworkMessage();
        message.setJsonData(request->toJsonObject());
        SendMessageToSA(message);


        /*После авторизации запустим хардбит подключения*/
        //qDebug()<<"mHeartbeatTimer->start("<<m_iHeartbeatTimer<<")";
        mHeartbeatTimer->start(m_iHeartbeatTimer);
        emit serverConnectStatusChanged("Подключено к " + settings.strServAdress + ". Проверка лицензии...");

    } else {
        mHasAuthorizated = false;
        emit serverConnectStatusChanged("Авторизация не удалась");
        qDebug("InteractionClient::onResponseAuthorization() - mHasAuthorizated = false");
    }
    mIsInAuthProcess = false;
}

void InteractionClient::onResponseLicence(const NetworkMessage &message)
{
    qDebug("InteractionClient::onResponseLicence");
    auto response = std::make_shared<ResponseLicence>(message.getJsonData());
    if (response->mLicence.count()) {
        auto errCode = response->mLicence.first().cErrorCode;
        qDebug("InteractionClient::onRequestLicence cErrorCode 0x%x", errCode);

        if (errCode & Licensing::LicenceErrors::LeErrNoLicenceFileOnServer) {
            mLicenseValid = false;
            emit serverConnectStatusChanged("Подключено к " + settings.strServAdress + ". Не авторизовано - нет файла лицензии");
        } else if (errCode & Licensing::LicenceErrors::LeErrVerifySignature) {
            mLicenseValid = false;
            emit serverConnectStatusChanged("Подключено к " + settings.strServAdress + ". Не авторизовано - неверная сигнатура");
        } else if (errCode & Licensing::LicenceErrors::LeErrWrongCpuid) {
            mLicenseValid = false;
            emit serverConnectStatusChanged("Подключено к " + settings.strServAdress + ". Не авторизовано - неверный CPUid");
        } else if (errCode & Licensing::LicenceErrors::LeErrLicenceFileCorrupted) {
            mLicenseValid = false;
            emit serverConnectStatusChanged("Подключено к " + settings.strServAdress + ". Не авторизовано - файл лицензии повреждён");
        } else if (errCode & Licensing::LicenceErrors::LeWarnServerNeedRights) {
            mLicenseValid = false;
            emit serverConnectStatusChanged("Подключено к " + settings.strServAdress + ". Не авторизовано - не достаточно прав");
        } else if (errCode & Licensing::LicenceErrors::LeWarnWrongHasp) {
            mLicenseValid = false;
            emit serverConnectStatusChanged("Подключено к " + settings.strServAdress + ". Не авторизовано - не верный Hasp");
        } else if (errCode & Licensing::LicenceErrors::LeWarnNoHaspPlugged) {
            mLicenseValid = false;
            emit serverConnectStatusChanged("Подключено к " + settings.strServAdress + ". Не авторизовано - Hasp не вставлен");
        } else if (errCode & Licensing::LicenceErrors::LeWarnNoHaspDriver) {
            mLicenseValid = false;
            emit serverConnectStatusChanged("Подключено к " + settings.strServAdress + ". Не авторизовано - нет Hasp драйвера");
        } else if (errCode & Licensing::LicenceErrors::LeWarnLicenceExpired) {
            mLicenseValid = false;
            emit serverConnectStatusChanged("Подключено к " + settings.strServAdress + ". Не авторизовано - лицензия истекла.");
        }
        else {
            mLicenseValid = true;
            emit serverConnectStatusChanged("Подключено к " + settings.strServAdress);
        }
    }
}




// void InteractionClient::onLicenseTimer()
// {
//     mLicenseTimer->stop();
//     auto request = std::make_shared<RequestLicence>();
//     request->licenceFileData = QString("check").toUtf8();
//     request->trueClientUid = QUuid();
//     auto message = NetworkMessage();
//     message.setJsonData(request->toJsonObject());
//     mMutexQueueToSA.lock();
//     mQueueToSA.enqueue(message);
//     mMutexQueueToSA.unlock();
//     qDebug("InteractionClient::onLicenseTimer");
//     mLicenseTimer->start(cLicenseTimeout);
// }

void InteractionClient::onRequestNotifyEvent(const NetworkMessage &message)
{
    qDebug("InteractionClient::onRequestNotifyEvent");
    auto request = std::make_shared<RequestEventNotification>(message.getJsonData());
    emit notifyEvent(request->mEventUid);
}

InteractionClient::~InteractionClient()
{
    mThread.quit();
    mThread.wait();
}
