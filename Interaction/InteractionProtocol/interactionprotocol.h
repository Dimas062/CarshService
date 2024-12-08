/** @file
\copyright   (c) CodLix LLC
\authors     Колосов В.В., Слепнев А.В.
\version     1.0
Project:     VideoSystem
File:        interactionprotocol.h
* @brief     Протокол взаимодействия клиента с сервером. Описание запросов/ответов.
**/
#ifndef INTERACTIONPROTOCOL_H
#define INTERACTIONPROTOCOL_H

#include "interactionprotocolstructs.h"
#include "interfaces.h"
#include <QPicture>
#include <QBuffer>
#include <QImage>

INTERACTION_PROTOCOL_API QString userRoleName(const EUserRole &role);
///
/// \brief The NetworkMessage struct сетевой пакет для транспортировки запросов/ответов
///
struct INTERACTION_PROTOCOL_API NetworkMessage {
    NetworkMessage();
    NetworkMessage(EDataType type, const QByteArray &data);
    NetworkMessage(const NetworkMessage &obj);
    NetworkMessage &operator =(const NetworkMessage &obj);
    ///
    /// \brief isValid проверка валидности
    /// \return true - валидное
    ///
    bool isValid() const;
    ///
    /// \brief getJsonData значение поля mData в json
    /// \return json-объект
    ///
    QJsonObject getJsonData() const;
    ///
    /// \brief setJsonData заполнить поле mData из json
    /// \param json json-объект
    ///
    void setJsonData(const QJsonObject& json);
    ///
    /// \brief serialize сериализовать
    /// \return бинарный вид
    ///
    QByteArray serialize();
    ///
    /// \brief getDataType тип поля mData
    /// \return тип
    ///
    EDataType type() const;
    QUuid uidRequest() const;

    static const quint32 cSyncroSequence = 0xA5A5A5A5;

private:
    EDataType mType;    ///< тип данных в поле mData (запрос/ответ)
    QByteArray mData;   ///< данные в json
protected:
    void selfCopy(const NetworkMessage &obj);
};

/** @code

  // приём ответа
  NetworkMessage message;
  ...
  if (message.type() const == EDataType::ResponseAuthorization) {
    ResponseAuthorization request(message.getJsonData());
  }

  // отправка запроса
  NetworkMessage message;
  ResponseAuthorization request;
  ...
  message.setJsonData(request.toJsonObject() const);

  // отправка сообщения
  QTcpSocket sock;
  sock.write(message.serialize());

 **/

///
/// \brief The ResponseBadRequest struct ответ (ошибка)
///
struct INTERACTION_PROTOCOL_API ResponseBadRequest : public IJsonable, public ICommonFields, public IResponseResultable {
    ResponseBadRequest();
    ResponseBadRequest(EDataType requestType);
    ResponseBadRequest(const ResponseBadRequest &obj);
    ResponseBadRequest &operator =(const ResponseBadRequest &obj);
    ResponseBadRequest(const QJsonObject &json);

    EDataType mRequestType;     ///< тип запроса, на который ошибка
protected:
    void selfCopy(const ResponseBadRequest &obj);
    // IJsonable interface
public:
    virtual EDataType type() const override;
    virtual QJsonObject toJsonObject() const override;
    virtual bool isValid() const override;
};

///
/// \brief The RequestHeartbeat struct Heartbeat-сообщение(отправляется 1 раз в 60 секунд)
/// его должен клиент отправлять - если сервер не увидит от клиента это сообщение чрез 60 сек * 2, то клиента - отрубаем
///
struct INTERACTION_PROTOCOL_API RequestHeartbeat : public IJsonable, public ICommonFields {
    RequestHeartbeat();
    RequestHeartbeat(const RequestHeartbeat &obj);
    RequestHeartbeat &operator =(const RequestHeartbeat &obj);
    RequestHeartbeat(const QJsonObject &json);
protected:
    void selfCopy(const RequestHeartbeat &obj);
    // IJsonable interface
public:
    virtual EDataType type() const override;
    virtual QJsonObject toJsonObject() const override;
    virtual bool isValid() const override;
};

/********************************************************************************/
/// \remark запросы/ответы - действия с пользователями
/********************************************************************************/

///
/// \brief The RequestAuthorization struct запрос авторизации
///
struct INTERACTION_PROTOCOL_API RequestAuthorization : public IJsonable, public ICommonFields {
    RequestAuthorization();
    RequestAuthorization(const QString& login, const QString& password, const QString& MAC, const QString &serverIpConnectTo);
    RequestAuthorization(const RequestAuthorization &obj);
    RequestAuthorization &operator =(const RequestAuthorization &obj);
    RequestAuthorization(const QJsonObject &json);

    QString mLogin;                     ///< логин
    QString mPassword;                  ///< пароль
    QString mMACAddress = "";           ///< MAC-адрес ПК, на котором запускается клиент
    QString mServerIpConnectTo = "";
    EClientType mClientType = EClientType::ClientApp;   ///< тип клиента
protected:
    void selfCopy(const RequestAuthorization &obj);
    // IJsonable interface
public:
    virtual EDataType type() const override;
    virtual QJsonObject toJsonObject() const override;
    virtual bool isValid() const override;
};

/// \remark для каждой роли доступны свои команды:
/// наблюдение - доступны только команды, связанные с просмотром камер и зон
/// аналитика - доступны команды просмотра камер и зон, а также отчёты, статистика (события)
/// администрирование - доступны все команды

///
/// \brief The ResponseAuthorization struct результат авторизации
/// если не прошла, то роль будет None и Uid == NULL
///
struct INTERACTION_PROTOCOL_API ResponseAuthorization : public IJsonable, public ICommonFields, public IResponseResultable {
    ResponseAuthorization():IJsonable(), ICommonFields(), IResponseResultable(){}
    ResponseAuthorization(const ResponseAuthorization &obj);
    ResponseAuthorization &operator =(const ResponseAuthorization &obj);
    ResponseAuthorization(const QJsonObject &json);

    EUserRole mRole = EUserRole::None;      ///< роль пользователя
    QUuid mUid = QUuid();                   ///< уникальный идентификатор пользователя (uid (токен) его выдаёт сервер при авторизации, будет нужен в InteractionProtocolIamClient)
    QUuid mUidUserFromDb = QUuid();         ///< уид юзера из БД
    QString mConnectionName = "";
    /// \remark параметры подключения к ОСНБД
    QString mDbName;                        ///< ОСНБД имя БД
    QString mHostIp;                        ///< ОСНБД IP БД
    int mHostPort;                          ///< ОСНБД порт БД
    QString mUser;                          ///< ОСНБД логин
    QString mPassword;                      ///< ОСНБД пароль
    ServerCategory mServerCategory = SC_UNKNOWN;    ///< Оосновной или центральный
//    QUuid mServerUuid = QUuid();                    ///< Uuid сервера из БД
    /// \remark параметры подключения к FTP
    QString mFtpLogin;                      ///< FTP логин
    QString mFtpPassword;                   ///< FTP пароль
    int mFtpPort;                           ///< FTP порт
    QString mFtpVirtualPath;                ///< FTP виртуальный порт
    int mNotificationPort;                  ///< Порт оповещений интеллектуальных модулей
    /// \remark параметры подключения к БД КЭШ-модуля
    QString                             mCashDatabaseIp;                    ///< IP адрес сервера БД КЭШ-модуля
    quint16                             mCashDatabasePort;                  ///< порт сервера БД КЭШ-модуля
    QString                             mCashDatabaseName;                  ///< имя БД на сервере БД КЭШ-модуля
    QString                             mCashDatabaseLogin;                 ///< логин сервера БД КЭШ-модуля
    QString                             mCashDatabasePassword;              ///< пароль сервера БД КЭШ-модуля
    /// \remark параметры подключения к БД КЭШ-транзакций
    QString                             mCashTransactionDatabaseIp;         ///< IP адрес сервера КЭШ-транзакций
    quint16                             mCashTransactionDatabasePort;       ///< порт сервера КЭШ-транзакций
    QString                             mCashTransactionDatabaseName;       ///< имя БД на сервере КЭШ-транзакций
    QString                             mCashTransactionDatabaseLogin;      ///< логин сервера КЭШ-транзакций
    QString                             mCashTransactionDatabasePassword;   ///< пароль сервера КЭШ-транзакций

    /// \remark примечание
    /// в режиме ОС:
    /// CentralFaceDatabaseIp - ЦС лиц
    /// FacesDatabaseIp - ОС лиц
    /// в режиме ЦС:
    /// CentralFaceDatabaseIp - ЦС лиц
    /// FacesDatabaseIp - не исп

    /// \remark параметры подключения к БД ЦС ЛИЦА
    QString                             mCentralFacesDatabaseIp;         ///< IP адрес сервера ЦС ЛИЦА
    quint16                             mCentralFacesDatabasePort;       ///< порт сервера ЦС ЛИЦА
    QString                             mCentralFacesDatabaseName;       ///< имя БД на сервере ЦС ЛИЦА
    QString                             mCentralFacesDatabaseLogin;      ///< логин сервера ЦС ЛИЦА
    QString                             mCentralFacesDatabasePassword;   ///< пароль сервера ЦС ЛИЦА
    /// \remark параметры подключения к БД ЦС ЛИЦА из ОС
    QString                             mFacesDatabaseIp;              ///< IP адрес БД ОС ЛИЦ
    quint16                             mFacesDatabasePort;            ///< порт БД ОС ЛИЦ
    QString                             mFacesDatabaseName;            ///< имя БД ОС ЛИЦ
    QString                             mFacesDatabaseLogin;           ///< логин БД ОС ЛИЦ
    QString                             mFacesDatabasePassword;        ///< пароль БД ОС ЛИЦ
    /// \remark дефолтные параметры для карточек объектов
    quint16                             mMainDefaultPort;                ///< порт по умолчанию
    QString                             mMainDefaultLogin;               ///< логин по умолчанию
    QString                             mMainDefaultPassword;            ///< пароль по умолчанию
    quint16                             mMainDefaultDbPort;              ///< порт БД по умолчанию
    QString                             mMainDefaultDbName;              ///< имя БД по умолчанию
    QString                             mMainDefaultDbUser;              ///< имя пользователя БД по умолчанию
    QString                             mMainDefaultDbPassword;          ///< пароль БД по умолчанию

protected:
    void selfCopy(const ResponseAuthorization &obj);
    // IJsonable interface
public:
    virtual EDataType type() const override;
    virtual QJsonObject toJsonObject() const override;
    virtual bool isValid() const override;
    virtual ~ResponseAuthorization() = default;
};

/********************************************************************************/
/// \remark запросы/ответы - управление параметрами сервера
/********************************************************************************/

struct INTERACTION_PROTOCOL_API RequestSetConfigParam : public IJsonable, public ICommonFields {
    RequestSetConfigParam();
    RequestSetConfigParam(const RequestSetConfigParam &obj);
    RequestSetConfigParam &operator =(const RequestSetConfigParam &obj);
    RequestSetConfigParam(const QJsonObject &json);

    QMap<EServerConfigParam, QString> mParameters;
protected:
    void selfCopy(const RequestSetConfigParam &obj);
    // IJsonable interface
public:
    virtual EDataType type() const override;
    virtual QJsonObject toJsonObject() const override;
    virtual bool isValid() const override;
};

struct INTERACTION_PROTOCOL_API RequestGetConfigParam : public IJsonable, public ICommonFields {
    RequestGetConfigParam();
    RequestGetConfigParam(const RequestGetConfigParam &obj);
    RequestGetConfigParam &operator =(const RequestGetConfigParam &obj);
    RequestGetConfigParam(const QJsonObject &json);

    QList<EServerConfigParam> mParameters;
protected:
    void selfCopy(const RequestGetConfigParam &obj);
    // IJsonable interface
public:
    virtual EDataType type() const override;
    virtual QJsonObject toJsonObject() const override;
    virtual bool isValid() const override;
};

struct INTERACTION_PROTOCOL_API ResponseSetConfigParam : public IJsonable, public ICommonFields, public IResponseResultable {
    ResponseSetConfigParam();
    ResponseSetConfigParam(const ResponseSetConfigParam &obj);
    ResponseSetConfigParam &operator =(const ResponseSetConfigParam &obj);
    ResponseSetConfigParam(const QJsonObject &json);

protected:
    void selfCopy(const ResponseSetConfigParam &obj);
    // IJsonable interface
public:
    virtual EDataType type() const override;
    virtual QJsonObject toJsonObject() const override;
    virtual bool isValid() const override;
};

struct INTERACTION_PROTOCOL_API ResponseGetConfigParam : public IJsonable, public ICommonFields, public IResponseResultable {
    ResponseGetConfigParam();
    ResponseGetConfigParam(const ResponseGetConfigParam &obj);
    ResponseGetConfigParam &operator =(const ResponseGetConfigParam &obj);
    ResponseGetConfigParam(const QJsonObject &json);

    QMap<EServerConfigParam, QString> mParameters;
protected:
    void selfCopy(const ResponseGetConfigParam &obj);
    // IJsonable interface
public:
    virtual EDataType type() const override;
    virtual QJsonObject toJsonObject() const override;
    virtual bool isValid() const override;
};

/********************************************************************************/
/// \remark файловая система сервера
/********************************************************************************/

struct INTERACTION_PROTOCOL_API RequestDirectoryContent : public IJsonable, public ICommonFields {
    RequestDirectoryContent();
    RequestDirectoryContent(const RequestDirectoryContent &obj);
    RequestDirectoryContent &operator =(const RequestDirectoryContent &obj);
    RequestDirectoryContent(const QJsonObject &json);
    // параметры запроса
    enum class ETypeDirRequest {
        Root,
        Subdir
    };
    ETypeDirRequest mTypeDirRequest = ETypeDirRequest::Root;
    QString mFullNameDirectory = "";

protected:
    void selfCopy(const RequestDirectoryContent &obj);
    // IJsonable interface
public:
    virtual EDataType type() const override;
    virtual QJsonObject toJsonObject() const override;
    virtual bool isValid() const override;
};

struct INTERACTION_PROTOCOL_API ResponseDirectoryContent : public IJsonable, public ICommonFields, public IResponseResultable {
    ResponseDirectoryContent();
    ResponseDirectoryContent(const ResponseDirectoryContent &obj);
    ResponseDirectoryContent &operator =(const ResponseDirectoryContent &obj);
    ResponseDirectoryContent(const QJsonObject &json);
    // параметры ответа
    enum class ETypeItem {
        Directory,
        File
    };
    QString mFullNameDirectory = "";
    QList<std::tuple<ETypeItem, QString>> mDirectoryContent;

protected:
    void selfCopy(const ResponseDirectoryContent &obj);
    // IJsonable interface
public:
    virtual EDataType type() const override;
    virtual QJsonObject toJsonObject() const override;
    virtual bool isValid() const override;
};

struct INTERACTION_PROTOCOL_API RequestUpdateVirtualPath : public IJsonable, public ICommonFields {
    RequestUpdateVirtualPath();
    RequestUpdateVirtualPath(const RequestUpdateVirtualPath &obj);
    RequestUpdateVirtualPath &operator =(const RequestUpdateVirtualPath &obj);
    RequestUpdateVirtualPath(const QJsonObject &json);

protected:
    void selfCopy(const RequestUpdateVirtualPath &obj);
    // IJsonable interface
public:
    virtual EDataType type() const override;
    virtual QJsonObject toJsonObject() const override;
    virtual bool isValid() const override;
};

struct INTERACTION_PROTOCOL_API ResponseUpdateVirtualPath : public IJsonable, public ICommonFields, public IResponseResultable {
    ResponseUpdateVirtualPath();
    ResponseUpdateVirtualPath(const ResponseUpdateVirtualPath &obj);
    ResponseUpdateVirtualPath &operator =(const ResponseUpdateVirtualPath &obj);
    ResponseUpdateVirtualPath(const QJsonObject &json);

protected:
    void selfCopy(const ResponseUpdateVirtualPath &obj);
    // IJsonable interface
public:
    virtual EDataType type() const override;
    virtual QJsonObject toJsonObject() const override;
    virtual bool isValid() const override;
};

/*****************/

struct INTERACTION_PROTOCOL_API RequestSetStreamsUrls : public IJsonable, public ICommonFields {
    RequestSetStreamsUrls();
    RequestSetStreamsUrls(const RequestSetStreamsUrls &obj);
    RequestSetStreamsUrls &operator =(const RequestSetStreamsUrls &obj);
    RequestSetStreamsUrls(const QJsonObject &json);

    QMap<QUuid, QString> mStreamUrlMap;
    bool mResetStreams = false;         ///< признак сброса сатрых потоков-вещаний (указание для СА)
protected:
    void selfCopy(const RequestSetStreamsUrls &obj);
    // IJsonable interface
public:
    virtual EDataType type() const override;
    virtual QJsonObject toJsonObject() const override;
    virtual bool isValid() const override;
};

struct INTERACTION_PROTOCOL_API ResponseSetStreamsUrls : public IJsonable, public ICommonFields, public IResponseResultable {
    ResponseSetStreamsUrls();
    ResponseSetStreamsUrls(const ResponseSetStreamsUrls &obj);
    ResponseSetStreamsUrls &operator =(const ResponseSetStreamsUrls &obj);
    ResponseSetStreamsUrls(const QJsonObject &json);
protected:
    void selfCopy(const ResponseSetStreamsUrls &obj);
    // IJsonable interface
public:
    virtual EDataType type() const override;
    virtual QJsonObject toJsonObject() const override;
    virtual bool isValid() const override;
};

///
/// \brief The RequestListAvailableCameras struct запрос получения списка доступных (подключенных к серверу) камер
///
struct INTERACTION_PROTOCOL_API RequestListAvailableCameras : public IJsonable, public ICommonFields {
    RequestListAvailableCameras();
    RequestListAvailableCameras(const RequestListAvailableCameras &obj);
    RequestListAvailableCameras &operator =(const RequestListAvailableCameras &obj);
    RequestListAvailableCameras(const QJsonObject &json);

protected:
    void selfCopy(const RequestListAvailableCameras &obj);
    // IJsonable interface
public:
    virtual EDataType type() const override;
    virtual QJsonObject toJsonObject() const override;
    virtual bool isValid() const override;
};
///
/// \brief The ResponseListAvailableCameras struct ответ на запрос получения списка доступных (подключенных к серверу) камер
///
struct INTERACTION_PROTOCOL_API ResponseListAvailableCameras : public IJsonable, public ICommonFields, public IResponseResultable {
    ResponseListAvailableCameras();
    ResponseListAvailableCameras(const ResponseListAvailableCameras &obj);
    ResponseListAvailableCameras &operator =(const ResponseListAvailableCameras &obj);
    ResponseListAvailableCameras(const QJsonObject &json);

    QVector<AvailableCameraProperties> mCameras; ///< обнаруженные камеры
protected:
    void selfCopy(const ResponseListAvailableCameras &obj);
    // IJsonable interface
public:
    virtual EDataType type() const override;
    virtual QJsonObject toJsonObject() const override;
    virtual bool isValid() const override;
};


struct INTERACTION_PROTOCOL_API RequestUpdate : public IJsonable, public ICommonFields {
    RequestUpdate();
    RequestUpdate(const RequestUpdate &obj);
    RequestUpdate &operator =(const RequestUpdate &obj);
    RequestUpdate(const QJsonObject &json);

protected:
    void selfCopy(const RequestUpdate &obj);
    // IJsonable interface
public:
    virtual EDataType type() const override;
    virtual QJsonObject toJsonObject() const override;
    virtual bool isValid() const override;
};

struct INTERACTION_PROTOCOL_API ResponseUpdate : public IJsonable, public ICommonFields, public IResponseResultable {
    ResponseUpdate();
    ResponseUpdate(const ResponseUpdate &obj);
    ResponseUpdate &operator =(const ResponseUpdate &obj);
    ResponseUpdate(const QJsonObject &json);
protected:
    void selfCopy(const ResponseUpdate &obj);
    // IJsonable interface
public:
    virtual EDataType type() const override;
    virtual QJsonObject toJsonObject() const override;
    virtual bool isValid() const override;
};

struct INTERACTION_PROTOCOL_API RequestFaceUpdate : public IJsonable, public ICommonFields {
    RequestFaceUpdate();
    RequestFaceUpdate(const RequestFaceUpdate &obj);
    RequestFaceUpdate &operator =(const RequestFaceUpdate &obj);
    RequestFaceUpdate(const QJsonObject &json);

protected:
    void selfCopy(const RequestFaceUpdate &obj);
    // IJsonable interface
public:
    virtual EDataType type() const override;
    virtual QJsonObject toJsonObject() const override;
    virtual bool isValid() const override;
};

struct INTERACTION_PROTOCOL_API ResponseFaceUpdate : public IJsonable, public ICommonFields, public IResponseResultable {
    ResponseFaceUpdate();
    ResponseFaceUpdate(const ResponseFaceUpdate &obj);
    ResponseFaceUpdate &operator =(const ResponseFaceUpdate &obj);
    ResponseFaceUpdate(const QJsonObject &json);
protected:
    void selfCopy(const ResponseFaceUpdate &obj);
    // IJsonable interface
public:
    virtual EDataType type() const override;
    virtual QJsonObject toJsonObject() const override;
    virtual bool isValid() const override;
};
// ----- //
///
/// \brief The RequestStartRtspStreamCamera struct запрос на создание и запуска вещания RTSP потока для заданного потока камеры
///
struct INTERACTION_PROTOCOL_API RequestStartRtspStreamCamera : public IJsonable, public ICommonFields {
    RequestStartRtspStreamCamera();
    RequestStartRtspStreamCamera(const QUuid& streamUid, const QUuid& rtspStreamUid, const QUuid& cameraUid, const QUuid& cassyUid);
    RequestStartRtspStreamCamera(const RequestStartRtspStreamCamera &obj);
    RequestStartRtspStreamCamera &operator =(const RequestStartRtspStreamCamera &obj);
    RequestStartRtspStreamCamera(const QJsonObject &json);

    QUuid mStreamUid;           ///< UID потока камеры
    QUuid mRtspStreamUid;       ///< УНИКАЛЬНЫЙ идентификатор RTSP потока
    QUuid mCameraUid;           ///< UID камеры
    QUuid mCassyUid;            ///< UID кассы
protected:
    void selfCopy(const RequestStartRtspStreamCamera &obj);
    // IJsonable interface
public:
    virtual EDataType type() const override;
    virtual QJsonObject toJsonObject() const override;
    virtual bool isValid() const override;
};
///
/// \brief The ResponseStartRtspStreamCamera struct ответ на запрос на создания и запускя вещания RTSP потока для заданного потока камеры
///
struct INTERACTION_PROTOCOL_API ResponseStartRtspStreamCamera : public IJsonable, public ICommonFields, public IResponseResultable {
    ResponseStartRtspStreamCamera();
    ResponseStartRtspStreamCamera(const QString &rtspUrl);
    ResponseStartRtspStreamCamera(const ResponseStartRtspStreamCamera &obj);
    ResponseStartRtspStreamCamera &operator =(const ResponseStartRtspStreamCamera &obj);
    ResponseStartRtspStreamCamera(const QJsonObject &json);

    QString mRtspUrl;   ///< строка доступа (url) к rtsp-потоку
protected:
    void selfCopy(const ResponseStartRtspStreamCamera &obj);
    // IJsonable interface
public:
    virtual EDataType type() const override;
    virtual QJsonObject toJsonObject() const override;
    virtual bool isValid() const override;
};
// ----- //
///
/// \brief The RequestStopRtspStreamCamera struct запрос на останов вещания и удаление RTSP потока для заданного потока камеры
///
struct INTERACTION_PROTOCOL_API RequestStopRtspStreamCamera : public IJsonable, public ICommonFields {
    RequestStopRtspStreamCamera();
    RequestStopRtspStreamCamera(const QUuid& streamUid, const QUuid& rtspStreamUid, const QUuid& cameraUid, const QUuid& cassyUid);
    RequestStopRtspStreamCamera(const RequestStopRtspStreamCamera &obj);
    RequestStopRtspStreamCamera &operator =(const RequestStopRtspStreamCamera &obj);
    RequestStopRtspStreamCamera(const QJsonObject &json);

    QUuid mStreamUid;         ///< UID потока камеры
    QUuid mRtspStreamUid;     ///< УНИКАЛЬНЫЙ идентификатор RTSP потока
    QUuid mCameraUid;         ///< UID камеры
    QUuid mCassyUid;          ///< UID кассы
protected:
    void selfCopy(const RequestStopRtspStreamCamera &obj);
    // IJsonable interface
public:
    virtual EDataType type() const override;
    virtual QJsonObject toJsonObject() const override;
    virtual bool isValid() const override;
};
///
/// \brief The ResponseStopRtspStreamCamera struct ответ на запрос на останов вещания и удаление RTSP потока для заданного потока камеры
///
struct INTERACTION_PROTOCOL_API ResponseStopRtspStreamCamera : public IJsonable, public ICommonFields, public IResponseResultable {
    ResponseStopRtspStreamCamera();
    ResponseStopRtspStreamCamera(const ResponseStopRtspStreamCamera &obj);
    ResponseStopRtspStreamCamera &operator =(const ResponseStopRtspStreamCamera &obj);
    ResponseStopRtspStreamCamera(const QJsonObject &json);

protected:
    void selfCopy(const ResponseStopRtspStreamCamera &obj);
    // IJsonable interface
public:
    virtual EDataType type() const override;
    virtual QJsonObject toJsonObject() const override;
    virtual bool isValid() const override;
};

///
/// \brief The RequestServerList struct запрос списка серверов
///
struct INTERACTION_PROTOCOL_API RequestServerList : public IJsonable, public ICommonFields {
    RequestServerList();
    RequestServerList(const RequestServerList &obj);
    RequestServerList &operator =(const RequestServerList &obj);
    RequestServerList(const QJsonObject &json);

protected:
    void selfCopy(const RequestServerList &obj);
    // IJsonable interface
public:
    virtual EDataType type() const override;
    virtual QJsonObject toJsonObject() const override;
    virtual bool isValid() const override;
};
///
/// \brief The ResponseServerList struct ответ на запрос списка серверов
///
struct INTERACTION_PROTOCOL_API ResponseServerList : public IJsonable, public ICommonFields, public IResponseResultable {
    ResponseServerList();
    ResponseServerList(const ResponseServerList &obj);
    ResponseServerList &operator =(const ResponseServerList &obj);
    ResponseServerList(const QJsonObject &json);

    QMap<QUuid, ServerProperties> mServers; ///< коллекция серверов
protected:
    void selfCopy(const ResponseServerList &obj);
    // IJsonable interface
public:
    virtual EDataType type() const override;
    virtual QJsonObject toJsonObject() const override;
    virtual bool isValid() const override;
    virtual ~ResponseServerList() = default;
};

/********************************************************************************/
/// \remark запросы/ответы - действия с архивными видео
/********************************************************************************/
///
/// \brief The RequestCreateRtspStreamVideo struct запрос на создание RTSP потока для архивного видео
///
struct INTERACTION_PROTOCOL_API RequestCreateRtspStreamVideo : public IJsonable, public ICommonFields {
    RequestCreateRtspStreamVideo();
    RequestCreateRtspStreamVideo(const QUuid& videoUid, const QVector<QUuid> &videosUuids, const QUuid& rtspStreamUid, double startSecond, double playbackSpeed);
    RequestCreateRtspStreamVideo(const RequestCreateRtspStreamVideo &obj);
    RequestCreateRtspStreamVideo &operator =(const RequestCreateRtspStreamVideo &obj);
    RequestCreateRtspStreamVideo(const QJsonObject &json);

    QUuid mVideoUid;                ///< UID видеозаписи
    QVector<QUuid> mVideosUuids;    ///< Отсортированные по времени уиды видео для воспроизведения
    QUuid mRtspStreamUid;           ///< УНИКАЛЬНЫЙ идентификатор RTSP потока
    double mStartSecond;            ///< секунда, с которой надо начинать трансляцию в контексте всей длины всех видео
    double mPlaybackSpeed;          ///< скорость воспроизведения (1.0 - нормальная скорость)
    bool mIsNeedPreviewFrame = true;
protected:
    void selfCopy(const RequestCreateRtspStreamVideo &obj);
    // IJsonable interface
public:
    virtual EDataType type() const override;
    virtual QJsonObject toJsonObject() const override;
    virtual bool isValid() const override;
};
///
/// \brief The ResponseCreateRtspStreamVideo struct ответ на запрос создания RTSP потока для архивного видео
///
struct INTERACTION_PROTOCOL_API ResponseCreateRtspStreamVideo : public IJsonable, public ICommonFields, public IResponseResultable {
    ResponseCreateRtspStreamVideo();
    ResponseCreateRtspStreamVideo(const QString &rtspUrl);
    ResponseCreateRtspStreamVideo(const ResponseCreateRtspStreamVideo &obj);
    ResponseCreateRtspStreamVideo &operator =(const ResponseCreateRtspStreamVideo &obj);
    ResponseCreateRtspStreamVideo(const QJsonObject &json);

    QString mRtspUrl;       ///< строка доступа (url) к rtsp-потоку
    QByteArray mPreviewFrame;

protected:
    void selfCopy(const ResponseCreateRtspStreamVideo &obj);
    // IJsonable interface
public:
    virtual EDataType type() const override;
    virtual QJsonObject toJsonObject() const override;
    virtual bool isValid() const override;
};
// ----- //
///
/// \brief The RequestStartRtspStreamVideo struct запрос запуска вещания RTSP потока для архивного видео
///
struct INTERACTION_PROTOCOL_API RequestStartRtspStreamVideo : public IJsonable, public ICommonFields {
    RequestStartRtspStreamVideo();
    RequestStartRtspStreamVideo(const QUuid& videoUid, const QVector<QUuid> &videosUuids, const QUuid& rtspStreamUid);
    RequestStartRtspStreamVideo(const RequestStartRtspStreamVideo &obj);
    RequestStartRtspStreamVideo &operator =(const RequestStartRtspStreamVideo &obj);
    RequestStartRtspStreamVideo(const QJsonObject &json);

    QUuid mVideoUid;                ///< UID видеозаписи
    QVector<QUuid> mVideosUuids;    ///< Отсортированные по времени уиды видео для воспроизведения
    QUuid mRtspStreamUid;           ///< УНИКАЛЬНЫЙ идентификатор RTSP потока
protected:
    void selfCopy(const RequestStartRtspStreamVideo &obj);
    // IJsonable interface
public:
    virtual EDataType type() const override;
    virtual QJsonObject toJsonObject() const override;
    virtual bool isValid() const override;
};
///
/// \brief The ResponseStartRtspStreamVideo struct ответ на запрос запуска вещания RTSP потока для архивного видео
///
struct INTERACTION_PROTOCOL_API ResponseStartRtspStreamVideo : public IJsonable, public ICommonFields, public IResponseResultable {
    ResponseStartRtspStreamVideo();
    ResponseStartRtspStreamVideo(const ResponseStartRtspStreamVideo &obj);
    ResponseStartRtspStreamVideo &operator =(const ResponseStartRtspStreamVideo &obj);
    ResponseStartRtspStreamVideo(const QJsonObject &json);

protected:
    void selfCopy(const ResponseStartRtspStreamVideo &obj);
    // IJsonable interface
public:
    virtual EDataType type() const override;
    virtual QJsonObject toJsonObject() const override;
    virtual bool isValid() const override;
};
// ----- //
///
/// \brief The RequestStopRtspStreamVideo struct запрос останова вещания и удаления RTSP потока для архивного видео
///
struct INTERACTION_PROTOCOL_API RequestStopRtspStreamVideo : public IJsonable, public ICommonFields {
    RequestStopRtspStreamVideo();
    RequestStopRtspStreamVideo(const QUuid& videoUid, const QUuid& rtspStreamUid);
    RequestStopRtspStreamVideo(const RequestStopRtspStreamVideo &obj);
    RequestStopRtspStreamVideo &operator =(const RequestStopRtspStreamVideo &obj);
    RequestStopRtspStreamVideo(const QJsonObject &json);

    QUuid mVideoUid;            ///< UID видеозаписи
    QUuid mRtspStreamUid;       ///< УНИКАЛЬНЫЙ идентификатор RTSP потока
protected:
    void selfCopy(const RequestStopRtspStreamVideo &obj);
    // IJsonable interface
public:
    virtual EDataType type() const override;
    virtual QJsonObject toJsonObject() const override;
    virtual bool isValid() const override;
};
///
/// \brief The ResponseStopRtspStreamVideo struct ответ на запрос останова вещания и удаления RTSP потока для архивного видео
///
struct INTERACTION_PROTOCOL_API ResponseStopRtspStreamVideo : public IJsonable, public ICommonFields, public IResponseResultable {
    ResponseStopRtspStreamVideo();
    ResponseStopRtspStreamVideo(const ResponseStopRtspStreamVideo &obj);
    ResponseStopRtspStreamVideo &operator =(const ResponseStopRtspStreamVideo &obj);
    ResponseStopRtspStreamVideo(const QJsonObject &json);

protected:
    void selfCopy(const ResponseStopRtspStreamVideo &obj);
    // IJsonable interface
public:
    virtual EDataType type() const override;
    virtual QJsonObject toJsonObject() const override;
    virtual bool isValid() const override;
};

///
/// \brief The RequestLicence struct запрос данных лицензии
///
struct INTERACTION_PROTOCOL_API RequestLicence : public IJsonable, public ICommonFields {
    RequestLicence();
    RequestLicence(const RequestLicence &obj);
    RequestLicence &operator =(const RequestLicence &obj);
    RequestLicence(const QJsonObject &json);

    QString licenceFileData;    ///< новый файл лицензии в виде строки
    QUuid trueClientUid;        ///< уид Клиента, который был при авторизации
protected:
    void selfCopy(const RequestLicence &obj);
    // IJsonable interface
public:
    virtual EDataType type() const override;
    virtual QJsonObject toJsonObject() const override;
    virtual bool isValid() const override;
};
///
/// \brief The ResponseLicence struct ответ на запрос данных лицензии
///
struct INTERACTION_PROTOCOL_API ResponseLicence : public IJsonable, public ICommonFields, public IResponseResultable {
    ResponseLicence();
    ResponseLicence(const ResponseLicence &obj);
    ResponseLicence &operator =(const ResponseLicence &obj);
    ResponseLicence(const QJsonObject &json);

    QVector<LicenceProperties> mLicence; ///< информация о лицензии
protected:
    void selfCopy(const ResponseLicence &obj);
    // IJsonable interface
public:
    virtual EDataType type() const override;
    virtual QJsonObject toJsonObject() const override;
    virtual bool isValid() const override;
};

///
/// \brief The RequestLicenceThroughCs struct запрос данных лицензии ОСа у ЦС
///
struct INTERACTION_PROTOCOL_API RequestLicenceThroughCs : public IJsonable, public ICommonFields {
    RequestLicenceThroughCs();
    RequestLicenceThroughCs(const RequestLicenceThroughCs &obj);
    RequestLicenceThroughCs &operator =(const RequestLicenceThroughCs &obj);
    RequestLicenceThroughCs(const QJsonObject &json);

    QString ip;     ///< айпи ОСа, у которого нужно спросить лицензию
    int port;       ///< порт ОСа, у которого нужно спросить лицензию
protected:
    void selfCopy(const RequestLicenceThroughCs &obj);
    // IJsonable interface
public:
    virtual EDataType type() const override;
    virtual QJsonObject toJsonObject() const override;
    virtual bool isValid() const override;
};
///
/// \brief The ResponseLicenceThroughCs struct ответ на запрос данных лицензии
///
struct INTERACTION_PROTOCOL_API ResponseLicenceThroughCs : public IJsonable, public ICommonFields, public IResponseResultable {
    ResponseLicenceThroughCs();
    ResponseLicenceThroughCs(const ResponseLicenceThroughCs &obj);
    ResponseLicenceThroughCs &operator =(const ResponseLicenceThroughCs &obj);
    ResponseLicenceThroughCs(const QJsonObject &json);

    LicenceProperties mLicence;         ///< информация о лицензии ОСа
protected:
    void selfCopy(const ResponseLicenceThroughCs &obj);
    // IJsonable interface
public:
    virtual EDataType type() const override;
    virtual QJsonObject toJsonObject() const override;
    virtual bool isValid() const override;
};

///
/// \brief The RequestGetClients struct список клиентов, подключенных к серверу - запрос
///
struct INTERACTION_PROTOCOL_API RequestGetClients : public IJsonable, public ICommonFields {
    RequestGetClients();
    RequestGetClients(const RequestGetClients &obj);
    RequestGetClients &operator =(const RequestGetClients &obj);
    RequestGetClients(const QJsonObject &json);

protected:
    void selfCopy(const RequestGetClients &obj);
    // IJsonable interface
public:
    virtual EDataType type() const override;
    virtual QJsonObject toJsonObject() const override;
    virtual bool isValid() const override;
};
///
/// \brief The ResponseGetClients struct список клиентов, подключенных к серверу - ответ
///
struct INTERACTION_PROTOCOL_API ResponseGetClients : public IJsonable, public ICommonFields, public IResponseResultable {
    ResponseGetClients();
    ResponseGetClients(const ResponseGetClients &obj);
    ResponseGetClients &operator =(const ResponseGetClients &obj);
    ResponseGetClients(const QJsonObject &json);

    QMap<QUuid, ClientProperties> mClients;
protected:
    void selfCopy(const ResponseGetClients &obj);
    // IJsonable interface
public:
    virtual EDataType type() const override;
    virtual QJsonObject toJsonObject() const override;
    virtual bool isValid() const override;
};

///
/// \brief The RequestKickClient struct отключить клиент - команда серверу - запрос
/// затем он отправит команду клиенту
///
struct INTERACTION_PROTOCOL_API RequestKickClient : public IJsonable, public ICommonFields {
    RequestKickClient();
    RequestKickClient(const RequestKickClient &obj);
    RequestKickClient &operator =(const RequestKickClient &obj);
    RequestKickClient(const QJsonObject &json);

    QUuid mClientUid;
protected:
    void selfCopy(const RequestKickClient &obj);
    // IJsonable interface
public:
    virtual EDataType type() const override;
    virtual QJsonObject toJsonObject() const override;
    virtual bool isValid() const override;
};

///
/// \brief The ResponseKickClient struct отключить клиент - команда серверу - ответ
///
struct INTERACTION_PROTOCOL_API ResponseKickClient : public IJsonable, public ICommonFields, public IResponseResultable {
    ResponseKickClient();
    ResponseKickClient(const ResponseKickClient &obj);
    ResponseKickClient &operator =(const ResponseKickClient &obj);
    ResponseKickClient(const QJsonObject &json);

protected:
    void selfCopy(const ResponseKickClient &obj);
    // IJsonable interface
public:
    virtual EDataType type() const override;
    virtual QJsonObject toJsonObject() const override;
    virtual bool isValid() const override;
};

///
/// \brief The RequestKickselfToClient struct отключить клиент - команда клиенту - запрос
/// не требует ответа
///
struct INTERACTION_PROTOCOL_API RequestKickselfToClient : public IJsonable, public ICommonFields {
    RequestKickselfToClient();
    RequestKickselfToClient(const RequestKickselfToClient &obj);
    RequestKickselfToClient &operator =(const RequestKickselfToClient &obj);
    RequestKickselfToClient(const QJsonObject &json);

protected:
    void selfCopy(const RequestKickselfToClient &obj);
    // IJsonable interface
public:
    virtual EDataType type() const override;
    virtual QJsonObject toJsonObject() const override;
    virtual bool isValid() const override;
};



///
/// \brief The RequestCopyVideoFileToTmp struct скопируй файл во временный (для экспорта пишущегося) - команда серверу - запрос
///
struct INTERACTION_PROTOCOL_API RequestCopyVideoFileToTmp : public IJsonable, public ICommonFields {
    RequestCopyVideoFileToTmp();
    RequestCopyVideoFileToTmp(const RequestCopyVideoFileToTmp &obj);
    RequestCopyVideoFileToTmp &operator =(const RequestCopyVideoFileToTmp &obj);
    RequestCopyVideoFileToTmp(const QJsonObject &json);

    QString mVideoFilePath = "";

protected:
    void selfCopy(const RequestCopyVideoFileToTmp &obj);
    // IJsonable interface
public:
    virtual EDataType type() const override;
    virtual QJsonObject toJsonObject() const override;
    virtual bool isValid() const override;
};

///
/// \brief The ResponseCopyVideoFileToTmp struct скопируй файл во временный (для экспорта пишущегося) - команда серверу - ответ
///
struct INTERACTION_PROTOCOL_API ResponseCopyVideoFileToTmp : public IJsonable, public ICommonFields, public IResponseResultable {
    ResponseCopyVideoFileToTmp();
    ResponseCopyVideoFileToTmp(const ResponseCopyVideoFileToTmp &obj);
    ResponseCopyVideoFileToTmp &operator =(const ResponseCopyVideoFileToTmp &obj);
    ResponseCopyVideoFileToTmp(const QJsonObject &json);

    QString mNewVideoFilePath = "";
    QString mErrorString = "";

protected:
    void selfCopy(const ResponseCopyVideoFileToTmp &obj);
    // IJsonable interface
public:
    virtual EDataType type() const override;
    virtual QJsonObject toJsonObject() const override;
    virtual bool isValid() const override;
};



///
/// \brief The RequestDeleteTmpVideoFiles struct удали временные файлы, использованные для экспорта  - команда серверу - запрос
///
struct INTERACTION_PROTOCOL_API RequestDeleteTmpVideoFiles : public IJsonable, public ICommonFields {
    RequestDeleteTmpVideoFiles();
    RequestDeleteTmpVideoFiles(const RequestDeleteTmpVideoFiles &obj);
    RequestDeleteTmpVideoFiles &operator =(const RequestDeleteTmpVideoFiles &obj);
    RequestDeleteTmpVideoFiles(const QJsonObject &json);

protected:
    void selfCopy(const RequestDeleteTmpVideoFiles &obj);
    // IJsonable interface
public:
    virtual EDataType type() const override;
    virtual QJsonObject toJsonObject() const override;
    virtual bool isValid() const override;
};

///
/// \brief The ResponseDeleteTmpVideoFiles struct удали временные файлы, использованные для экспорта  - команда серверу - ответ
///
struct INTERACTION_PROTOCOL_API ResponseDeleteTmpVideoFiles : public IJsonable, public ICommonFields, public IResponseResultable {
    ResponseDeleteTmpVideoFiles();
    ResponseDeleteTmpVideoFiles(const ResponseDeleteTmpVideoFiles &obj);
    ResponseDeleteTmpVideoFiles &operator =(const ResponseDeleteTmpVideoFiles &obj);
    ResponseDeleteTmpVideoFiles(const QJsonObject &json);

    bool mRemoved = false;
    QString mErrorString = "";

protected:
    void selfCopy(const ResponseDeleteTmpVideoFiles &obj);
    // IJsonable interface
public:
    virtual EDataType type() const override;
    virtual QJsonObject toJsonObject() const override;
    virtual bool isValid() const override;
};

/********************************************************************************/
/// \remark лента скриншотов
/********************************************************************************/

///
/// \brief The RequestGetMiniScreenshots struct Запрос "Список мини-скиншотов"
///
struct INTERACTION_PROTOCOL_API RequestGetMiniScreenshots : public IJsonable, public ICommonFields {
    RequestGetMiniScreenshots();
    RequestGetMiniScreenshots(const RequestGetMiniScreenshots &obj);
    RequestGetMiniScreenshots &operator =(const RequestGetMiniScreenshots &obj);
    RequestGetMiniScreenshots(const QJsonObject &json);

    QUuid mVideoStreamUid;                  ///< уид видеопотока
    QList<QDateTime> mDateTimeSreenshots;	///< дата-время скриншотов
    QSize mTargetOutputResolution;          ///< целевое выходное разрешение картинок
protected:
    const QString cDateTimeFormat = QString("dd.MM.yyyy hh:mm:ss.zzz");
    void selfCopy(const RequestGetMiniScreenshots &obj);
    // IJsonable interface
public:
    virtual EDataType type() const override;
    virtual QJsonObject toJsonObject() const override;
    virtual bool isValid() const override;
};

///
/// \brief The ResponseDeleteTmpVideoFiles struct Ответ "Список мини-скиншотов"
///
struct INTERACTION_PROTOCOL_API ResponseGetMiniScreenshots : public IJsonable, public ICommonFields, public IResponseResultable {
    ResponseGetMiniScreenshots();
    ResponseGetMiniScreenshots(const ResponseGetMiniScreenshots &obj);
    ResponseGetMiniScreenshots &operator =(const ResponseGetMiniScreenshots &obj);
    ResponseGetMiniScreenshots(const QJsonObject &json);

    QMap<QDateTime, QImage> miniSreenshots();	// минискриншоты // image.save(qbuffer, "jpeg") запаковка и передача кадров в сыром виде вформате jpeg - для экономии места
    void setMiniScreenshots(const QMap<QDateTime, QImage>& miniScreenshots);
private:
    QMap<QDateTime, QByteArray> mHexedMiniSreenshots; ///< сырые захексованные скриншоты
protected:
    void selfCopy(const ResponseGetMiniScreenshots &obj);
    // IJsonable interface
public:
    virtual EDataType type() const override;
    virtual QJsonObject toJsonObject() const override;
    virtual bool isValid() const override;
};

///
/// \brief The RequestGetScreenshot struct Запрос "Полноразмерный скриншот"
///
struct INTERACTION_PROTOCOL_API RequestGetScreenshot : public IJsonable, public ICommonFields {
    RequestGetScreenshot();
    RequestGetScreenshot(const RequestGetScreenshot &obj);
    RequestGetScreenshot &operator =(const RequestGetScreenshot &obj);
    RequestGetScreenshot(const QJsonObject &json);

    QUuid mVideoStreamUid;          ///< уид видеопотока
    QDateTime mDateTimeSreenshot;	///< дата-время скриншота
    QSize mTargetOutputResolution;  ///< целевое выходное разрешение скриншота
protected:
    const QString cDateTimeFormat = QString("dd.MM.yyyy hh:mm:ss.zzz");
    void selfCopy(const RequestGetScreenshot &obj);
    // IJsonable interface
public:
    virtual EDataType type() const override;
    virtual QJsonObject toJsonObject() const override;
    virtual bool isValid() const override;
};

///
/// \brief The ResponseGetScreenshot struct Ответ "Полноразмерный скриншот"
///
struct INTERACTION_PROTOCOL_API ResponseGetScreenshot : public IJsonable, public ICommonFields, public IResponseResultable {
    ResponseGetScreenshot();
    ResponseGetScreenshot(const ResponseGetScreenshot &obj);
    ResponseGetScreenshot &operator =(const ResponseGetScreenshot &obj);
    ResponseGetScreenshot(const QJsonObject &json);

    QImage sreenshot();	// скриншот // image.save(qbuffer, "jpeg") запаковка и передача кадров в сыром виде вформате jpeg - для экономии места
    void setScreenshot(QImage screenshot);
private:
    QByteArray mHexedSreenshot; ///< сырой захексованный скриншот
protected:
    void selfCopy(const ResponseGetScreenshot &obj);
    // IJsonable interface
public:
    virtual EDataType type() const override;
    virtual QJsonObject toJsonObject() const override;
    virtual bool isValid() const override;
};

///
/// \brief The RequestUseVideoStream struct извещение пка об использовании видеопотока
///
struct INTERACTION_PROTOCOL_API RequestUseVideoStream : public IJsonable, public ICommonFields {
    RequestUseVideoStream();
    RequestUseVideoStream(const RequestUseVideoStream &obj);
    RequestUseVideoStream &operator =(const RequestUseVideoStream &obj);
    RequestUseVideoStream(const QJsonObject &json);

    QUuid mVideoStreamUid;                  ///< уид видеопотока
protected:
    void selfCopy(const RequestUseVideoStream &obj);
    // IJsonable interface
public:
    virtual EDataType type() const override;
    virtual QJsonObject toJsonObject() const override;
    virtual bool isValid() const override;
};

///
/// \brief The RequestResetStreams struct указание от СА в РК - перезапусти запись и перезапроси потоки
///
struct INTERACTION_PROTOCOL_API RequestResetStreams : public IJsonable, public ICommonFields {
    RequestResetStreams();
    RequestResetStreams(const RequestResetStreams &obj);
    RequestResetStreams &operator =(const RequestResetStreams &obj);
    RequestResetStreams(const QJsonObject &json);

protected:
    void selfCopy(const RequestResetStreams &obj);
    // IJsonable interface
public:
    virtual EDataType type() const override;
    virtual QJsonObject toJsonObject() const override;
    virtual bool isValid() const override;
};

///
/// \brief The RequestRestartStreamWriter struct команда рестарт писателя потока в РК
///
struct INTERACTION_PROTOCOL_API RequestRestartStreamWriter : public IJsonable, public ICommonFields {
    RequestRestartStreamWriter();
    RequestRestartStreamWriter(const RequestRestartStreamWriter &obj);
    RequestRestartStreamWriter &operator =(const RequestRestartStreamWriter &obj);
    RequestRestartStreamWriter(const QJsonObject &json);

    QUuid mVideoStreamUid;                  ///< уид видеопотока
protected:
    void selfCopy(const RequestRestartStreamWriter &obj);
    // IJsonable interface
public:
    virtual EDataType type() const override;
    virtual QJsonObject toJsonObject() const override;
    virtual bool isValid() const override;
};

///
/// \brief The RequestFreeFile struct команда от РК в СА - освободи файл
///
struct INTERACTION_PROTOCOL_API RequestFreeFile : public IJsonable, public ICommonFields {
    RequestFreeFile();
    RequestFreeFile(const RequestFreeFile &obj);
    RequestFreeFile &operator =(const RequestFreeFile &obj);
    RequestFreeFile(const QJsonObject &json);

    QUuid mVideoFileUid;                  ///< уид видеофайла
protected:
    void selfCopy(const RequestFreeFile &obj);
    // IJsonable interface
public:
    virtual EDataType type() const override;
    virtual QJsonObject toJsonObject() const override;
    virtual bool isValid() const override;
};

///
/// \brief The RequestEventNotification struct уведомление о событии
///
struct INTERACTION_PROTOCOL_API RequestEventNotification : public IJsonable, public ICommonFields {
    RequestEventNotification();
    RequestEventNotification(const RequestEventNotification &obj);
    RequestEventNotification &operator =(const RequestEventNotification &obj);
    RequestEventNotification(const QJsonObject &json);

    QUuid mEventUid;
protected:
    void selfCopy(const RequestEventNotification &obj);
    // IJsonable interface
public:
    virtual EDataType type() const override;
    virtual QJsonObject toJsonObject() const override;
    virtual bool isValid() const override;
};

#endif // INTERACTIONPROTOCOL_H
