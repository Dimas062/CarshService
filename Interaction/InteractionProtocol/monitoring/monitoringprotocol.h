#ifndef MONITORINGPROTOCOL_H
#define MONITORINGPROTOCOL_H

#include <QObject>
#include <QUuid>
#include <QByteArray>
#include <QDataStream>
#include <QDateTime>
#include <QMap>
#include "interactionprotocollib.h"

/// \remark 65001

namespace MonitoringProtocol {

const int Port = 65002;

///
/// \brief The EMessageType enum типы сообщений логического уровня протокола сервера мониторинга
///
enum class EMessageType {
    None = 0,
    HeartbeatServerMessage,         ///< сообщение - хартбит сообщение от ЦС-ОС сервера
    GetServerTableRequest,          ///< запрос - дай таблицу серверов (автоматически подписка на изменения таблицы серверов)
    GetServerTableRespone,          ///< ответ - дай таблицу серверов
    ChangeServerTableItemMessage,   ///< сообщение - сообщение об изменении элемента таблицы серверов
    NeedUpdateTableMessage,
    CheckClientConnectionRequest,   ///< запрос - проверка доступности сервера
    CheckClientConnectionResponse,  ///< ответ - проверка доступности сервера
    GetStringParameterRequest,      ///< запрос - получить текстовый параметр
    GetStringParameterResponse,     ///< ответ - получить текстовый параметр
    SetStringParameterRequest,      ///< запрос - установить текстовый параметр
    SetStringParameterResponse,     ///< ответ - установить текстовый параметр
    /// \remark контролируемые объекты
    AddObjectRequest,               ///< запрос - добавить объект
    AddObjectResponse,              ///< ответ - добавить объект
    RemoveObjectRequest,            ///< запрос - удалить объект
    RemoveObjectResponse,           ///< ответ - удалить объект
    EditObjectRequest,              ///< запрос - редактировать объект
    EditObjectResponse,             ///< ответ - редактировать объект
    GetObjectsRequest,              ///< запрос - получить контролируемые объекты
    GetObjectsResponse,             ///< ответ - получить контролируемые объекты
    /// \remark телеграм каналы
    AddTelegramChannelRequest,               ///< запрос - добавить телеграм канал
    AddTelegramChannelResponse,              ///< ответ - добавить телеграм канал
    RemoveTelegramChannelRequest,            ///< запрос - удалить телеграм канал
    RemoveTelegramChannelResponse,           ///< ответ - удалить телеграм канал
    EditTelegramChannelRequest,              ///< запрос - редактировать телеграм канал
    EditTelegramChannelResponse,             ///< ответ - редактировать телеграм канал
    GetTelegramChannelsRequest,              ///< запрос - получить телеграм каналы
    GetTelegramChannelsResponse,             ///< ответ - получить телеграм каналы
    /// \remark email каналы
    AddEmailChannelRequest,               ///< запрос - добавить email канал
    AddEmailChannelResponse,              ///< ответ - добавить email канал
    RemoveEmailChannelRequest,            ///< запрос - удалить email канал
    RemoveEmailChannelResponse,           ///< ответ - удалить email канал
    EditEmailChannelRequest,              ///< запрос - редактировать email канал
    EditEmailChannelResponse,             ///< ответ - редактировать email канал
    GetEmailChannelsRequest,              ///< запрос - получить email каналы
    GetEmailChannelsResponse              ///< ответ - получить email каналы
};

/// \remark ТРАНСПОРТНЫЙ УРОВЕНЬ

///
/// \brief The Message class сообщение транспортного уровня протокола сервера мониторинга
///
class INTERACTION_PROTOCOL_API Message {
public:
    Message();
    Message(const Message &obj);
    Message &operator =(const Message &obj);
    void deserialize(const QByteArray& raw);    ///< десериализация
    void serialize(QByteArray& raw) const;            ///< сериализация

    int length() const;                 ///< получить размер сообщения
    const QUuid& uid() const;           ///< получить уид сообщения
    const QByteArray& payload() const;  ///< получить полезную нагрузка

    const EMessageType& type() const;   ///< получить тип сообщения

    static void registerMetatype();     ///< регистрация типов
    bool markBadVersionProtocol() const;
    ///
    /// \brief setPayload установить полезную нагрузку
    /// \param payload полезная нагрузка
    /// \return уникальный идентификатор запроса
    ///
    QUuid setPayload(const QByteArray& payload);
    ///
    /// \brief setUid установить уид сообщения
    /// \param uid уид сообщения
    ///
    void setUid(const QUuid& uid);
protected:
    void selfCopy(const Message &obj);
    EMessageType getType(const QByteArray& payload);
private:
    /// \remark ЗАГОЛОВОК
    int mLength = 0;        ///< размер сообщения
    QUuid mUid;             ///< уид сообщения
    const int cCurrentVersionProtocol = 0x02072024;
    bool mMarkBadVersionProtocol = false;
    /// \remark ПОЛЕЗНАЯ НАГРУЗКА
    QByteArray mPayload;    ///< полезная нагрузка
    EMessageType mType = EMessageType::None;    ///< тип сообщения
};

///
/// \brief The ParserMessageMachine class парсер сообщений
///
class INTERACTION_PROTOCOL_API ParserMessageMachine
{
public:
    ParserMessageMachine() {}
    QVector<MonitoringProtocol::Message> step(const QByteArray& data);
    void reset();
private:
    QByteArray mPrevData;   ///< накопленные данные
};

/// \remark ЛОГИЧЕСКИЙ УРОВЕНЬ

///
/// \brief The LogicalMessage struct базовое сообщение логического уровня протокола сервера мониторинга
///
struct INTERACTION_PROTOCOL_API LogicalMessage {
    virtual EMessageType type() const = 0;
    virtual void serialize(QByteArray& payload) const = 0;
    virtual void deserialize(const QByteArray& payload) = 0;
protected:
    void readQUuid(QDataStream& rd, QUuid& uid);
    void writeQUuid(QDataStream& wr, const QUuid& uid) const;
};

///
/// \brief The HeartbeatServerMessage struct хартбит сообщение от ЦС-ОС сервера
///
struct INTERACTION_PROTOCOL_API HeartbeatServerMessage : public LogicalMessage {
    HeartbeatServerMessage():LogicalMessage(){}
    HeartbeatServerMessage(const HeartbeatServerMessage &obj):LogicalMessage() { selfCopy(obj); }
    HeartbeatServerMessage &operator =(const HeartbeatServerMessage &obj) { if (this != &obj) { selfCopy(obj); } return *this; }
    virtual EMessageType type() const { return EMessageType::HeartbeatServerMessage; }
    virtual void serialize(QByteArray& payload) const;
    virtual void deserialize(const QByteArray& payload);

    QString mCode;
    QString mName;
    QString mAddress;

    QString mOperationSystem;   ///< операционная система
    QString mVersionSoftware;   ///< версия ПО
    QDateTime mEndLicenseDt;    ///< дата конца лицензии

private:
    inline void selfCopy(const HeartbeatServerMessage &obj) {
        mCode = obj.mCode;
        mName = obj.mName;
        mAddress = obj.mAddress;
        mOperationSystem = obj.mOperationSystem;
        mVersionSoftware = obj.mVersionSoftware;
        mEndLicenseDt = obj.mEndLicenseDt;
    }
};

///
/// \brief The GetServerTableRequest struct запрос - дай таблицу серверов (автоматически подписка на изменения таблицы серверов)
///
struct INTERACTION_PROTOCOL_API GetServerTableRequest : public LogicalMessage {
    GetServerTableRequest():LogicalMessage(){}
    GetServerTableRequest(const GetServerTableRequest &obj):LogicalMessage() { selfCopy(obj); }
    GetServerTableRequest &operator =(const GetServerTableRequest &obj) { if (this != &obj) { selfCopy(obj); } return *this; }
    virtual EMessageType type() const { return EMessageType::GetServerTableRequest; }
    virtual void serialize(QByteArray& payload) const;
    virtual void deserialize(const QByteArray& payload);

private:
    inline void selfCopy(const GetServerTableRequest &obj) {
    }
};

///
/// \brief The GetServerTableRespone struct ответ - дай таблицу серверов
///
struct INTERACTION_PROTOCOL_API GetServerTableRespone : public LogicalMessage {
    GetServerTableRespone():LogicalMessage(){}
    GetServerTableRespone(const GetServerTableRespone &obj):LogicalMessage() { selfCopy(obj); }
    GetServerTableRespone &operator =(const GetServerTableRespone &obj) { if (this != &obj) { selfCopy(obj); } return *this; }
    virtual EMessageType type() const { return EMessageType::GetServerTableRespone; }
    virtual void serialize(QByteArray& payload) const;
    virtual void deserialize(const QByteArray& payload);

    struct ServerTableItem {
        QString mCode;
        QString mName;
        QString mAddress;

        bool mOnlineState;
        QDateTime mLastActiveDateTime;
        QString mOperationSystem;   ///< операционная система
        QString mVersionSoftware;   ///< версия ПО
        QDateTime mEndLicenseDt;    ///< дата конца лицензии
    };
    QMap<QUuid, ServerTableItem> mServerTable;

private:
    inline void selfCopy(const GetServerTableRespone &obj) {
        mServerTable = obj.mServerTable;
    }
};

///
/// \brief The ChangeServerTableItemMessage struct сообщение об изменении элемента таблицы серверов
///
struct INTERACTION_PROTOCOL_API ChangeServerTableItemMessage : public LogicalMessage {
    ChangeServerTableItemMessage():LogicalMessage(){}
    ChangeServerTableItemMessage(const ChangeServerTableItemMessage &obj):LogicalMessage() { selfCopy(obj); }
    ChangeServerTableItemMessage &operator =(const ChangeServerTableItemMessage &obj) { if (this != &obj) { selfCopy(obj); } return *this; }
    virtual EMessageType type() const { return EMessageType::ChangeServerTableItemMessage; }
    virtual void serialize(QByteArray& payload) const;
    virtual void deserialize(const QByteArray& payload);

    QUuid mServerTableItemUid;

    QString mCode;
    QString mName;
    QString mAddress;

    bool mOnlineState;
    QDateTime mLastActiveDateTime;
    QString mOperationSystem;   ///< операционная система
    QString mVersionSoftware;   ///< версия ПО
    QDateTime mEndLicenseDt;    ///< дата конца лицензии

private:
    inline void selfCopy(const ChangeServerTableItemMessage &obj) {
        mServerTableItemUid = obj.mServerTableItemUid;
        mCode = obj.mCode;
        mName = obj.mName;
        mAddress = obj.mAddress;
        mOnlineState = obj.mOnlineState;
        mLastActiveDateTime = obj.mLastActiveDateTime;
        mOperationSystem = obj.mOperationSystem;
        mVersionSoftware = obj.mVersionSoftware;
        mEndLicenseDt = obj.mEndLicenseDt;
    }
};

struct INTERACTION_PROTOCOL_API NeedUpdateTableMessage : public LogicalMessage {
    NeedUpdateTableMessage():LogicalMessage(){}
    NeedUpdateTableMessage(const NeedUpdateTableMessage &obj):LogicalMessage() { selfCopy(obj); }
    NeedUpdateTableMessage &operator =(const NeedUpdateTableMessage &obj) { if (this != &obj) { selfCopy(obj); } return *this; }
    virtual EMessageType type() const { return EMessageType::NeedUpdateTableMessage; }
    virtual void serialize(QByteArray& payload) const;
    virtual void deserialize(const QByteArray& payload);

private:
    inline void selfCopy(const NeedUpdateTableMessage &obj) {
    }
};

struct INTERACTION_PROTOCOL_API CheckClientConnectionRequest : public LogicalMessage {
    CheckClientConnectionRequest():LogicalMessage(){}
    CheckClientConnectionRequest(const CheckClientConnectionRequest &obj):LogicalMessage() { selfCopy(obj); }
    CheckClientConnectionRequest &operator =(const CheckClientConnectionRequest &obj) { if (this != &obj) { selfCopy(obj); } return *this; }
    virtual EMessageType type() const { return EMessageType::CheckClientConnectionRequest; }
    virtual void serialize(QByteArray& payload) const;
    virtual void deserialize(const QByteArray& payload);

private:
    inline void selfCopy(const CheckClientConnectionRequest &obj) {
    }
};

struct INTERACTION_PROTOCOL_API CheckClientConnectionResponse : public LogicalMessage {
    CheckClientConnectionResponse():LogicalMessage(){}
    CheckClientConnectionResponse(const CheckClientConnectionResponse &obj):LogicalMessage() { selfCopy(obj); }
    CheckClientConnectionResponse &operator =(const CheckClientConnectionResponse &obj) { if (this != &obj) { selfCopy(obj); } return *this; }
    virtual EMessageType type() const { return EMessageType::CheckClientConnectionResponse; }
    virtual void serialize(QByteArray& payload) const;
    virtual void deserialize(const QByteArray& payload);

private:
    inline void selfCopy(const CheckClientConnectionResponse &obj) {
    }
};

/// \remark управление параметрами

class INTERACTION_PROTOCOL_API IStringParameter {
public:
    enum class EParameter {
        None = 0,
        TelegramChannelName,
        TelegramTokenBot
    };
};

///
/// \brief The GetStringParameterRequest struct получить параметр - запрос
///
struct INTERACTION_PROTOCOL_API GetStringParameterRequest : public LogicalMessage, public IStringParameter {
    GetStringParameterRequest():LogicalMessage(), IStringParameter(){}
    GetStringParameterRequest(const GetStringParameterRequest &obj):LogicalMessage(), IStringParameter() { selfCopy(obj); }
    GetStringParameterRequest &operator =(const GetStringParameterRequest &obj) { if (this != &obj) { selfCopy(obj); } return *this; }
    virtual EMessageType type() const { return EMessageType::GetStringParameterRequest; }
    virtual void serialize(QByteArray& payload) const;
    virtual void deserialize(const QByteArray& payload);

    IStringParameter::EParameter mParameter;

private:
    inline void selfCopy(const GetStringParameterRequest &obj) {
        mParameter = obj.mParameter;
    }
};

///
/// \brief The GetStringParameterResponse struct получить параметр - ответ
///
struct INTERACTION_PROTOCOL_API GetStringParameterResponse : public LogicalMessage {
    GetStringParameterResponse():LogicalMessage(){}
    GetStringParameterResponse(const GetStringParameterResponse &obj):LogicalMessage() { selfCopy(obj); }
    GetStringParameterResponse &operator =(const GetStringParameterResponse &obj) { if (this != &obj) { selfCopy(obj); } return *this; }
    virtual EMessageType type() const { return EMessageType::GetStringParameterResponse; }
    virtual void serialize(QByteArray& payload) const;
    virtual void deserialize(const QByteArray& payload);

    IStringParameter::EParameter mParameter;
    QString mParameterValue;

private:
    inline void selfCopy(const GetStringParameterResponse &obj) {
        mParameter = obj.mParameter;
        mParameterValue = obj.mParameterValue;
    }
};

///
/// \brief The SetStringParameterRequest struct установить параметр - запрос
///
struct INTERACTION_PROTOCOL_API SetStringParameterRequest : public LogicalMessage, public IStringParameter {
    SetStringParameterRequest():LogicalMessage(), IStringParameter(){}
    SetStringParameterRequest(const SetStringParameterRequest &obj):LogicalMessage(), IStringParameter() { selfCopy(obj); }
    SetStringParameterRequest &operator =(const SetStringParameterRequest &obj) { if (this != &obj) { selfCopy(obj); } return *this; }
    virtual EMessageType type() const { return EMessageType::SetStringParameterRequest; }
    virtual void serialize(QByteArray& payload) const;
    virtual void deserialize(const QByteArray& payload);

    IStringParameter::EParameter mParameter;
    QString mParameterValue;

private:
    inline void selfCopy(const SetStringParameterRequest &obj) {
        mParameter = obj.mParameter;
        mParameterValue = obj.mParameterValue;
    }
};

///
/// \brief The SetStringParameterResponse struct установить параметр - ответ
///
struct INTERACTION_PROTOCOL_API SetStringParameterResponse : public LogicalMessage {
    SetStringParameterResponse():LogicalMessage(){}
    SetStringParameterResponse(const SetStringParameterResponse &obj):LogicalMessage() { selfCopy(obj); }
    SetStringParameterResponse &operator =(const SetStringParameterResponse &obj) { if (this != &obj) { selfCopy(obj); } return *this; }
    virtual EMessageType type() const { return EMessageType::SetStringParameterResponse; }
    virtual void serialize(QByteArray& payload) const;
    virtual void deserialize(const QByteArray& payload);

    IStringParameter::EParameter mParameter;

private:
    inline void selfCopy(const SetStringParameterResponse &obj) {
        mParameter = obj.mParameter;
    }
};

/// \remark контролируемые объекты

struct INTERACTION_PROTOCOL_API AddObjectRequest : public LogicalMessage {
    AddObjectRequest():LogicalMessage(){}
    AddObjectRequest(const AddObjectRequest &obj):LogicalMessage() { selfCopy(obj); }
    AddObjectRequest &operator =(const AddObjectRequest &obj) { if (this != &obj) { selfCopy(obj); } return *this; }
    virtual EMessageType type() const { return EMessageType::AddObjectRequest; }
    virtual void serialize(QByteArray& payload) const;
    virtual void deserialize(const QByteArray& payload);

    QString mCode;
    QString mName;
    QString mAddress;

private:
    inline void selfCopy(const AddObjectRequest &obj) {
        mCode = obj.mCode;
        mName = obj.mName;
        mAddress = obj.mAddress;
    }
};

struct INTERACTION_PROTOCOL_API AddObjectResponse : public LogicalMessage {
    AddObjectResponse():LogicalMessage(){}
    AddObjectResponse(const AddObjectResponse &obj):LogicalMessage() { selfCopy(obj); }
    AddObjectResponse &operator =(const AddObjectResponse &obj) { if (this != &obj) { selfCopy(obj); } return *this; }
    virtual EMessageType type() const { return EMessageType::AddObjectResponse; }
    virtual void serialize(QByteArray& payload) const;
    virtual void deserialize(const QByteArray& payload);

private:
    inline void selfCopy(const AddObjectResponse &obj) {
    }
};

struct INTERACTION_PROTOCOL_API RemoveObjectRequest : public LogicalMessage {
    RemoveObjectRequest():LogicalMessage(){}
    RemoveObjectRequest(const RemoveObjectRequest &obj):LogicalMessage() { selfCopy(obj); }
    RemoveObjectRequest &operator =(const RemoveObjectRequest &obj) { if (this != &obj) { selfCopy(obj); } return *this; }
    virtual EMessageType type() const { return EMessageType::RemoveObjectRequest; }
    virtual void serialize(QByteArray& payload) const;
    virtual void deserialize(const QByteArray& payload);

    QUuid mId;

private:
    inline void selfCopy(const RemoveObjectRequest &obj) {
        mId = obj.mId;
    }
};

struct INTERACTION_PROTOCOL_API RemoveObjectResponse : public LogicalMessage {
    RemoveObjectResponse():LogicalMessage(){}
    RemoveObjectResponse(const RemoveObjectResponse &obj):LogicalMessage() { selfCopy(obj); }
    RemoveObjectResponse &operator =(const RemoveObjectResponse &obj) { if (this != &obj) { selfCopy(obj); } return *this; }
    virtual EMessageType type() const { return EMessageType::RemoveObjectResponse; }
    virtual void serialize(QByteArray& payload) const;
    virtual void deserialize(const QByteArray& payload);

private:
    inline void selfCopy(const RemoveObjectResponse &obj) {
    }
};

struct INTERACTION_PROTOCOL_API EditObjectRequest : public LogicalMessage {
    EditObjectRequest():LogicalMessage(){}
    EditObjectRequest(const EditObjectRequest &obj):LogicalMessage() { selfCopy(obj); }
    EditObjectRequest &operator =(const EditObjectRequest &obj) { if (this != &obj) { selfCopy(obj); } return *this; }
    virtual EMessageType type() const { return EMessageType::EditObjectRequest; }
    virtual void serialize(QByteArray& payload) const;
    virtual void deserialize(const QByteArray& payload);

    QUuid mId;
    QString mCode;
    QString mName;
    QString mAddress;

private:
    inline void selfCopy(const EditObjectRequest &obj) {
        mId = obj.mId;
        mCode = obj.mCode;
        mName = obj.mName;
        mAddress = obj.mAddress;
    }
};

struct INTERACTION_PROTOCOL_API EditObjectResponse : public LogicalMessage {
    EditObjectResponse():LogicalMessage(){}
    EditObjectResponse(const EditObjectResponse &obj):LogicalMessage() { selfCopy(obj); }
    EditObjectResponse &operator =(const EditObjectResponse &obj) { if (this != &obj) { selfCopy(obj); } return *this; }
    virtual EMessageType type() const { return EMessageType::EditObjectResponse; }
    virtual void serialize(QByteArray& payload) const;
    virtual void deserialize(const QByteArray& payload);

private:
    inline void selfCopy(const EditObjectResponse &obj) {
    }
};

struct INTERACTION_PROTOCOL_API GetObjectsRequest : public LogicalMessage {
    GetObjectsRequest():LogicalMessage(){}
    GetObjectsRequest(const GetObjectsRequest &obj):LogicalMessage() { selfCopy(obj); }
    GetObjectsRequest &operator =(const GetObjectsRequest &obj) { if (this != &obj) { selfCopy(obj); } return *this; }
    virtual EMessageType type() const { return EMessageType::GetObjectsRequest; }
    virtual void serialize(QByteArray& payload) const;
    virtual void deserialize(const QByteArray& payload);

private:
    inline void selfCopy(const GetObjectsRequest &obj) {
    }
};

struct INTERACTION_PROTOCOL_API GetObjectsResponse : public LogicalMessage {
    GetObjectsResponse():LogicalMessage(){}
    GetObjectsResponse(const GetObjectsResponse &obj):LogicalMessage() { selfCopy(obj); }
    GetObjectsResponse &operator =(const GetObjectsResponse &obj) { if (this != &obj) { selfCopy(obj); } return *this; }
    virtual EMessageType type() const { return EMessageType::GetObjectsResponse; }
    virtual void serialize(QByteArray& payload) const;
    virtual void deserialize(const QByteArray& payload);

    struct ObjectItem {
        QString mCode;
        QString mName;
        QString mAddress;
    };
    QMap<QUuid, ObjectItem> mObjects;

private:
    inline void selfCopy(const GetObjectsResponse &obj) {
        mObjects = obj.mObjects;
    }
};

}

#endif // MONITORINGPROTOCOL_H
