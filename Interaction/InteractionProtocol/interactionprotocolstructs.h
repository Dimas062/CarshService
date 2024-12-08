/** @file
\copyright   (c) CodLix LLC
\authors     Колосов В.В.
\version     1.0
Project:     VideoSystem
File:        interactionprotocolstructs.h
* @brief     Протокол взаимодействия клиента с сервером. Описание вспомогательных типов.
**/
#ifndef INTERACTIONPROTOCOLSTRUCTS_H
#define INTERACTIONPROTOCOLSTRUCTS_H

#include "interactionprotocollib.h"
#include "interfaces.h"
#include "interactionprotocoltypes.h"

#include <QObject>
#include <QByteArray>
#include <QUuid>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonDocument>
#include <QVariant>
#include <QVector>
#include <QPointF>
#include <QMap>
#include <QDateTime>

///
/// \brief The AvailableCameraProperties struct свойства обнаруженной камеры
/// (подключенной к серверу по локальной сети)
///
struct INTERACTION_PROTOCOL_API AvailableCameraProperties : public IJsonable {
    AvailableCameraProperties();
    AvailableCameraProperties(const QString& ip, const QString& uid);
    AvailableCameraProperties(const AvailableCameraProperties &obj);
    AvailableCameraProperties &operator =(const AvailableCameraProperties &obj);
    AvailableCameraProperties(const QJsonObject &json);

    QString mIp;  ///< IP-адрес
    QString mUid;   ///< уникальный иденификатор (производитель + модель + серийный номер)
protected:
    void selfCopy(const AvailableCameraProperties &obj);
    // IJsonable interface
public:
    virtual EDataType type() const override;
    virtual QJsonObject toJsonObject() const override;
    virtual bool isValid() const override;
};

///
/// \brief The ZoneProperties struct свойства зоны
///
struct INTERACTION_PROTOCOL_API ZoneProperties : public IJsonable {
    ZoneProperties();
    ZoneProperties(const QUuid& uid, const QString &name, const QString &description, const QString &address, const QPointF& coordinates, const QVector<ZoneProperties> subZones);
    ZoneProperties(const ZoneProperties &obj);
    ZoneProperties &operator =(const ZoneProperties &obj);
    ZoneProperties(const QJsonObject &json);

    QUuid mUid; ///< уникальный идентификатор зоны
    QString mName;  ///< имя
    QString mDescription;   ///< описание
    QString mAddress;   ///< адрес
    QPointF mCoordinates;   ///< координаты
    QVector<ZoneProperties> mSubZones;  ///< дочерние зоны
protected:
    void selfCopy(const ZoneProperties &obj);
    // IJsonable interface
public:
    virtual EDataType type() const override;
    virtual QJsonObject toJsonObject() const override;
    virtual bool isValid() const override;
};

///
/// \brief The UserProperties struct свойства пользователя
///
struct INTERACTION_PROTOCOL_API UserProperties : public IJsonable {
    UserProperties();
    UserProperties(const QUuid& uid, const QString &login, const EUserRole &role, bool isRemoved);
    UserProperties(const UserProperties &obj);
    UserProperties &operator =(const UserProperties &obj);
    UserProperties(const QJsonObject &json);

    QUuid mUid;         ///< уникальный идентификатор пользователя
    QString mLogin;     ///< логин
    EUserRole mRole;    ///< роль
    bool mIsRemoved;    ///< признак удаленного пользователя
protected:
    void selfCopy(const UserProperties &obj);
    // IJsonable interface
public:
    virtual EDataType type() const override;
    virtual QJsonObject toJsonObject() const override;
    virtual bool isValid() const override;
};

///
/// \brief The NewZone struct новая зона
///
struct INTERACTION_PROTOCOL_API NewZone : public IJsonable {
    NewZone();
    NewZone(const QString &name, const QString &description, const QString &address, const QPointF& coordinates, const QUuid& parentZoneUid);
    NewZone(const NewZone &obj);
    NewZone &operator =(const NewZone &obj);
    NewZone(const QJsonObject &json);

    QString mName;  ///< имя
    QString mDescription;   ///< описание
    QString mAddress;   ///< адрес
    QPointF mCoordinates;   ///< координаты
    QUuid mParentZoneUid;  ///< UID родительской зоны (если корневая зона, то NULL)
protected:
    void selfCopy(const NewZone &obj);
    // IJsonable interface
public:
    virtual EDataType type() const override;
    virtual QJsonObject toJsonObject() const override;
    virtual bool isValid() const override;
};

///
/// \brief The Group struct группа
///
struct INTERACTION_PROTOCOL_API Group : public IJsonable {
    Group();
    Group(const QUuid& uid, const QString &name, const QString &description);
    Group(const Group &obj);
    Group &operator =(const Group &obj);
    Group(const QJsonObject &json);

    QUuid mUid;
    QString mName;
    QString mDescription;
protected:
    void selfCopy(const Group &obj);
    // IJsonable interface
public:
    virtual EDataType type() const override;
    virtual QJsonObject toJsonObject() const override;
    virtual bool isValid() const override;
};

///
/// \brief The AccessRightProperties struct свойства право доступа
///
struct INTERACTION_PROTOCOL_API AccessRightProperties : public IJsonable {
    AccessRightProperties();
    AccessRightProperties(const QUuid& uidUser, const QUuid& uidGroup, const QUuid& uidZone, const QUuid& uidCamera);
    AccessRightProperties(const AccessRightProperties &obj);
    AccessRightProperties &operator =(const AccessRightProperties &obj);
    AccessRightProperties(const QJsonObject &json);

    QUuid mUidUser;
    QUuid mUidGroup;
    QUuid mUidZone;
    QUuid mUidCamera;
protected:
    void selfCopy(const AccessRightProperties &obj);
    // IJsonable interface
public:
    virtual EDataType type() const override;
    virtual QJsonObject toJsonObject() const override;
    virtual bool isValid() const override;
};

///
/// \brief The VideoProperties struct свойства видеозаписи
///
struct INTERACTION_PROTOCOL_API VideoProperties : public IJsonable {
    VideoProperties();
    VideoProperties(const QString& fileName, const QUuid& cameraStreamUid, const QDateTime& startDate, const QDateTime& finishDate, const QDateTime& addedDate, const QUuid& server);
    VideoProperties(const VideoProperties &obj);
    VideoProperties &operator =(const VideoProperties &obj);
    VideoProperties(const QJsonObject &json);

    QString mFileName;          ///< полное имя файла видеозаписи
    QUuid mCameraStreamUid;     ///< UID потока камеры, которому принадлежит видеозапись
    QDateTime mStartDate;       ///< дата начала
    QDateTime mFinishDate;      ///< дата окончания
    QDateTime mAddedDate;       ///< дата добавления
    QUuid mServer;              ///< сервер
protected:
    void selfCopy(const VideoProperties &obj);
    // IJsonable interface
public:
    virtual EDataType type() const override;
    virtual QJsonObject toJsonObject() const override;
    virtual bool isValid() const override;
};

///
/// \brief The StreamCameraProperties struct видеопоток камеры
///
struct INTERACTION_PROTOCOL_API StreamCameraProperties : public IJsonable {
    StreamCameraProperties();
    StreamCameraProperties(const QUuid& camera, const QUuid& streamType, const QString& url, const QString& description, const bool& isRecording, const QUuid& status);
    StreamCameraProperties(const StreamCameraProperties &obj);
    StreamCameraProperties &operator =(const StreamCameraProperties &obj);
    StreamCameraProperties(const QJsonObject &json);

    QUuid mCameraUid;               ///< камера, к которой принадлежит поток
    QUuid mStreamCameraTypeUid;     ///< тип потока
    QString mUrl;                   ///< URL управления
    QString mDescription;           ///< описание
    bool mIsRecording;              ///< идёт запись?
    QUuid mStreamCameraStatusUid;   ///< статус потока
protected:
    void selfCopy(const StreamCameraProperties &obj);
    // IJsonable interface
public:
    virtual EDataType type() const override;
    virtual QJsonObject toJsonObject() const override;
    virtual bool isValid() const override;
};

///
/// \brief The CameraProperties struct свойства камеры
///
struct INTERACTION_PROTOCOL_API CameraProperties : public IJsonable {
    CameraProperties();
    CameraProperties(const QString& name, const QUuid& type, const QString& url, const QString& description, const double& lat, const double& lng, const QUuid& zone, const bool& isRemoved, const QUuid& server);
    CameraProperties(const CameraProperties &obj);
    CameraProperties &operator =(const CameraProperties &obj);
    CameraProperties(const QJsonObject &json);

    QString mName;          ///< имя камеры
    QUuid mType;            ///< тип камеры
    QString mUrl;           ///< URL управления
    QString mDescription;   ///< описание
    double mLat;            ///< геолокация - широта
    double mLng;            ///< геолокация - долгота
    QUuid mZone;            ///< зона
    bool mIsRemoved;        ///< признак удалённой камеры
    QUuid mServer;          ///< сервер
    QMap<QUuid, StreamCameraProperties> mCameraStreams; ///< потоки камеры
protected:
    void selfCopy(const CameraProperties &obj);
    // IJsonable interface
public:
    virtual EDataType type() const override;
    virtual QJsonObject toJsonObject() const override;
    virtual bool isValid() const override;
};

///
/// \brief The GroupProperties struct свойства группы
///
struct INTERACTION_PROTOCOL_API GroupProperties : public IJsonable {
    GroupProperties();
    GroupProperties(const QString& name, const QString& description);
    GroupProperties(const GroupProperties &obj);
    GroupProperties &operator =(const GroupProperties &obj);
    GroupProperties(const QJsonObject &json);

    QString mName;          ///< название группы
    QString mDescription;   ///< описание группы
protected:
    void selfCopy(const GroupProperties &obj);
    // IJsonable interface
public:
    virtual EDataType type() const override;
    virtual QJsonObject toJsonObject() const override;
    virtual bool isValid() const override;
};

///
/// \brief The LayoutProperties struct свойства раскладки
///
struct INTERACTION_PROTOCOL_API LayoutProperties : public IJsonable {
    LayoutProperties();
    LayoutProperties(const QString& name, const QString& description);
    LayoutProperties(const LayoutProperties &obj);
    LayoutProperties &operator =(const LayoutProperties &obj);
    LayoutProperties(const QJsonObject &json);

    QString mName;          ///< название раскладки
    QString mDescription;   ///< описание раскладки
protected:
    void selfCopy(const LayoutProperties &obj);
    // IJsonable interface
public:
    virtual EDataType type() const override;
    virtual QJsonObject toJsonObject() const override;
    virtual bool isValid() const override;
};

///
/// \brief The UserProfileProperties struct свойства профиля пользователя
///
struct INTERACTION_PROTOCOL_API UserProfileProperties : public IJsonable {
    UserProfileProperties();
    UserProfileProperties(const QUuid& userUid, const QUuid& layoutUid);
    UserProfileProperties(const UserProfileProperties &obj);
    UserProfileProperties &operator =(const UserProfileProperties &obj);
    UserProfileProperties(const QJsonObject &json);

    QUuid mUserUid;     ///< UID пользователя
    QUuid mLayoutUid;   ///< UID раскладки
protected:
    void selfCopy(const UserProfileProperties &obj);
    // IJsonable interface
public:
    virtual EDataType type() const override;
    virtual QJsonObject toJsonObject() const override;
    virtual bool isValid() const override;
};

///
/// \brief The LayoutItemProperties struct свойства элемента раскладки
///
struct INTERACTION_PROTOCOL_API LayoutItemProperties : public IJsonable {
    LayoutItemProperties();
    LayoutItemProperties(const QUuid& layoutUid, int row, int column, int rows, int columns);
    LayoutItemProperties(const LayoutItemProperties &obj);
    LayoutItemProperties &operator =(const LayoutItemProperties &obj);
    LayoutItemProperties(const QJsonObject &json);

    QUuid mLayoutUid;   ///< UID раскладки
    int mRow;           ///< строка
    int mColumn;        ///< столбец
    int mRows;          ///< охват строк
    int mColumns;       ///< охват сьтолбцов
protected:
    void selfCopy(const LayoutItemProperties &obj);
    // IJsonable interface
public:
    virtual EDataType type() const override;
    virtual QJsonObject toJsonObject() const override;
    virtual bool isValid() const override;
};

///
/// \brief The ProfileProperties struct свойства пользователя
///
struct INTERACTION_PROTOCOL_API ProfileItemProperties : public IJsonable {
    ProfileItemProperties();
    ProfileItemProperties(const QUuid& profileUid, const QUuid& layoutItemUid, const QUuid& streamUid);
    ProfileItemProperties(const ProfileItemProperties &obj);
    ProfileItemProperties &operator =(const ProfileItemProperties &obj);
    ProfileItemProperties(const QJsonObject &json);

    QUuid mProfileUid;      ///< UID профиля
    QUuid mLayoutItemUid;   ///< UID элемента раскладки
    QUuid mStreamUid;       ///< UID видеопотока
protected:
    void selfCopy(const ProfileItemProperties &obj);
    // IJsonable interface
public:
    virtual EDataType type() const override;
    virtual QJsonObject toJsonObject() const override;
    virtual bool isValid() const override;
};

///
/// \brief The StreamCameraStatusProperties struct свойства статуса потока камеры
///
struct INTERACTION_PROTOCOL_API StreamCameraStatusProperties : public IJsonable {
    StreamCameraStatusProperties();
    StreamCameraStatusProperties(const QString& description, int relevance);
    StreamCameraStatusProperties(const StreamCameraStatusProperties &obj);
    StreamCameraStatusProperties &operator =(const StreamCameraStatusProperties &obj);
    StreamCameraStatusProperties(const QJsonObject &json);

    QString mDescription;       ///< описание
    int mRelevance;             ///< важность
protected:
    void selfCopy(const StreamCameraStatusProperties &obj);
    // IJsonable interface
public:
    virtual EDataType type() const override;
    virtual QJsonObject toJsonObject() const override;
    virtual bool isValid() const override;
};

///
/// \brief The StreamCameraTypeProperties struct свойства типа потока камеры
///
struct INTERACTION_PROTOCOL_API StreamCameraTypeProperties : public IJsonable {
    StreamCameraTypeProperties();
    StreamCameraTypeProperties(const QString& name, const QString& description);
    StreamCameraTypeProperties(const StreamCameraTypeProperties &obj);
    StreamCameraTypeProperties &operator =(const StreamCameraTypeProperties &obj);
    StreamCameraTypeProperties(const QJsonObject &json);

    QString mName;              ///< название
    QString mDescription;       ///< описание
protected:
    void selfCopy(const StreamCameraTypeProperties &obj);
    // IJsonable interface
public:
    virtual EDataType type() const override;
    virtual QJsonObject toJsonObject() const override;
    virtual bool isValid() const override;
};

///
/// \brief The ServerProperties struct свойства сервера
///
struct INTERACTION_PROTOCOL_API ServerProperties : public IJsonable {
    ServerProperties();
    ServerProperties(const QString& name, const QString& description, const QString& ipAddress);
    ServerProperties(const ServerProperties &obj);
    ServerProperties &operator =(const ServerProperties &obj);
    ServerProperties(const QJsonObject &json);

    QString mName;              ///< название
    QString mDescription;       ///< описание
    QString mIpAddress;         ///< IP адрес
protected:
    void selfCopy(const ServerProperties &obj);
    // IJsonable interface
public:
    virtual EDataType type() const override;
    virtual QJsonObject toJsonObject() const override;
    virtual bool isValid() const override;
};

///
/// \brief The LicenceProperties struct лицензия
///
struct INTERACTION_PROTOCOL_API LicenceProperties : public IJsonable {
    LicenceProperties();
    LicenceProperties(const QDateTime& generationDateTime,
                      const QString& user,
                      const QString& key,
                      const bool& keyType,
                      const QString& customer,
                      const QString& parameters,
                      const QDateTime& endDateTime,
                      const QString& currentState,
                      const QString& cpuIdServer,
                      const QString& haspKey,
                      const int& errorCode);
    LicenceProperties(const LicenceProperties &obj);
    LicenceProperties &operator =(const LicenceProperties &obj);
    LicenceProperties(const QJsonObject &json);

    QDateTime mGenerationDateTime;              ///< Дата создания Licence
    QString mUser;                              ///< user
    QString mKey;                               ///< Ключ
    bool mKeyType;                              ///< Тип ключа (0/1 - HASP/SOFT)
    QString mCustomer;                          ///< Заказчик
    QString mParameters;                        ///< параметры
    QDateTime mEndDateTime;                     ///< Дата окончания действия лицензии
    QString cCurrentState;                      ///< Текущее состояние сервера лицензирования
    QString cCpuid;                             ///< CPUID сервера
    QString cHaspKey;                           ///< Текущий подключённый ключ
    int cErrorCode;                             ///< Ответ модуля лицензии

protected:
    void selfCopy(const LicenceProperties &obj);
    // IJsonable interface
public:
    virtual EDataType type() const override;
    virtual QJsonObject toJsonObject() const override;
    virtual bool isValid() const override;
};

///
/// \brief The ClientProperties struct свойства клиента
///
struct INTERACTION_PROTOCOL_API ClientProperties : public IJsonable {
    ClientProperties();
    ClientProperties(const ClientProperties &obj);
    ClientProperties &operator =(const ClientProperties &obj);
    ClientProperties(const QJsonObject &json);

    QString mIp;
    QString mLogin;
protected:
    void selfCopy(const ClientProperties &obj);
    // IJsonable interface
public:
    virtual EDataType type() const override;
    virtual QJsonObject toJsonObject() const override;
    virtual bool isValid() const override;
};



///
/// \brief The VRGetTimelineRequestParameters struct параметры запроса шкалы архива видеорегистратора
///
struct INTERACTION_PROTOCOL_API VRGetTimelineRequestParameters : public IJsonable {
    VRGetTimelineRequestParameters();
    VRGetTimelineRequestParameters(const VRGetTimelineRequestParameters &obj);
    VRGetTimelineRequestParameters &operator =(const VRGetTimelineRequestParameters &obj);
    VRGetTimelineRequestParameters(const QJsonObject &json);

    struct StreamParameters
    {
        QString VRParameters = "";
        QJsonObject streamId = QJsonObject();                       ///< Описание потока (VRStreamId из VideoRecorderApi)
        QUuid streamUuid = QUuid();                 ///< уникальный uuid для запроса конкретно этого потока
    };
    QVector<StreamParameters> mStreams;
    qint64 mStartMsecsSinceEpoch = 0;
    qint64 mEndMsecsSinceEpoch = 0;

protected:
    void selfCopy(const VRGetTimelineRequestParameters &obj);
    // IJsonable interface
public:
    virtual EDataType type() const override;
    virtual QJsonObject toJsonObject() const override;
    virtual bool isValid() const override;
};

Q_DECLARE_METATYPE(UserProperties)
Q_DECLARE_METATYPE(Group)
Q_DECLARE_METATYPE(GroupProperties)
Q_DECLARE_METATYPE(ZoneProperties)
Q_DECLARE_METATYPE(CameraProperties)
Q_DECLARE_METATYPE(VideoProperties)
Q_DECLARE_METATYPE(AccessRightProperties)
Q_DECLARE_METATYPE(AvailableCameraProperties)
Q_DECLARE_METATYPE(LicenceProperties)

#endif // INTERACTIONPROTOCOLSTRUCTS_H
