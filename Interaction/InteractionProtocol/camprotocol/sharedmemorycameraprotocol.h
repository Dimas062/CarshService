#ifndef SHAREDMEMORYCAMERAPROTOCOL_H
#define SHAREDMEMORYCAMERAPROTOCOL_H

#include <QObject>
#include <QUuid>
#include <QByteArray>
#include <QDataStream>
#include <QSharedMemory>
#include <QDateTime>

#include "interactionprotocollib.h"

namespace CameraProtocol {

///
/// \brief The EMessageType enum типы сообщений логического протокола прокси сервера камер
///
enum class EMessageType {
    None = 0,
    CammanSetParametersRequest,         ///< запрос - расширенные параметры. установить расширенные параметры камеры
    CammanSetParametersResponse,        ///< ответ - расширенные параметры. установить расширенные параметры камеры
    CammanGetParametersRequest,         ///< запрос - расширенные параметры. получить расширенные параметры камеры
    CammanGetParametersResponse,        ///< ответ - расширенные параметры. получить расширенные параметры камеры
    CameventOnEventsRequest,            ///< запрос - события. включить события
    CameventOnEventResponse,            ///< ответ - события. включить события
    CameventOffEventRequest,            ///< запрос - события. выключить события
    CameventOffEventResponse,           ///< ответ - события. выключить события
    CameventGetMoveEventRequest,        ///< запрос - события. очередное событие движения с кадром
    CameventGetMoveEventResponse,       ///< ответ - события. очередное событие движения с кадром
    CammanRebootRequest,                ///< запрос - расширенные параметры. перезагрузка камеры
    CammanRebootResponse                ///< ответ - расширенные параметры. перезагрузка камеры
};

/// \remark ТРАНСПОРТНЫЙ УРОВЕНЬ

///
/// \brief The Message class сообщение, которе будет лежать в shared memory
///
class INTERACTION_PROTOCOL_API Message {
public:
    Message();
    Message(const Message &obj);
    Message &operator =(const Message &obj);
    void deserialize(const QByteArray& raw);    ///< десериализация
    void serialize(QByteArray& raw);            ///< сериализация

    int length() const;                 ///< получить размер сообщения
    const QUuid& uid() const;           ///< получить уид сообщения
    const QByteArray& payload() const;  ///< получить полезную нагрузка

    const EMessageType& type() const;   ///< получить тип сообщения

    static void registerMetatype();     ///< регистрация типов

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
    int mLength = 0;        ///< размер сообщения
    QUuid mUid;             ///< уид сообщения
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
    QVector<CameraProtocol::Message> step(const QByteArray& data);
    void reset();
private:
    QByteArray mPrevData;   ///< накопленные данные
};
///
/// \brief The SharedMemoryNaming class имена
///
class INTERACTION_PROTOCOL_API SharedMemoryNaming {
public:
    const static QString cLocalServerCameraManager;
};

/// \remark ЛОГИЧЕСКИЙ УРОВЕНЬ

///
/// \brief The LogicalMessage struct базовое сообщение логического протокола
///
struct INTERACTION_PROTOCOL_API LogicalMessage {
    virtual EMessageType type() = 0;
    virtual void serialize(QByteArray& payload) = 0;
    virtual void deserialize(const QByteArray& payload) = 0;
};

/// \remark расширенные параметры. установить расширенные параметры камеры

struct INTERACTION_PROTOCOL_API CammanSetParametersRequest : public LogicalMessage {
    CammanSetParametersRequest(){}
    CammanSetParametersRequest(const CammanSetParametersRequest &obj) { selfCopy(obj); }
    CammanSetParametersRequest &operator =(const CammanSetParametersRequest &obj) { if (this != &obj) { selfCopy(obj); } return *this; }
    virtual EMessageType type() { return EMessageType::CammanSetParametersRequest; }
    virtual void serialize(QByteArray& payload);
    virtual void deserialize(const QByteArray& payload);

    QUuid mCameraUid;                           ///< уид камеры
    QString mJsonCameraConnectionParameters;    ///< json параметры камеры (АПИ)
    QString mJsonCameraManageParameters;        ///< расширенные парамептры камеры

private:
    inline void selfCopy(const CammanSetParametersRequest &obj) {
        mCameraUid = obj.mCameraUid;
        mJsonCameraConnectionParameters = obj.mJsonCameraConnectionParameters;
        mJsonCameraManageParameters = obj.mJsonCameraManageParameters;
    }
};

struct INTERACTION_PROTOCOL_API CammanSetParametersResponse : public LogicalMessage {
    CammanSetParametersResponse(){}
    CammanSetParametersResponse(const CammanSetParametersResponse &obj) { selfCopy(obj); }
    CammanSetParametersResponse &operator =(const CammanSetParametersResponse &obj) { if (this != &obj) { selfCopy(obj); } return *this; }
    virtual EMessageType type() { return EMessageType::CammanSetParametersResponse; }
    virtual void serialize(QByteArray& payload);
    virtual void deserialize(const QByteArray& payload);

    bool mResult = false;       ///< результат операции
private:
    inline void selfCopy(const CammanSetParametersResponse &obj) {
        mResult = obj.mResult;
    }
};

/// \remark расширенные параметры. получить расширенные параметры камеры

struct INTERACTION_PROTOCOL_API CammanGetParametersRequest : public LogicalMessage {
    CammanGetParametersRequest(){}
    CammanGetParametersRequest(const CammanGetParametersRequest &obj) { selfCopy(obj); }
    CammanGetParametersRequest &operator =(const CammanGetParametersRequest &obj) { if (this != &obj) { selfCopy(obj); } return *this; }
    virtual EMessageType type() { return EMessageType::CammanGetParametersRequest; }
    virtual void serialize(QByteArray& payload);
    virtual void deserialize(const QByteArray& payload);

    QUuid mCameraUid;   ///< уид камеры
    int mStreamType;    ///< тип потока
    QString mJsonCameraConnectionParameters;    ///< json параметры камеры (АПИ)
private:
    inline void selfCopy(const CammanGetParametersRequest &obj) {
        mCameraUid = obj.mCameraUid;
        mStreamType = obj.mStreamType;
        mJsonCameraConnectionParameters = obj.mJsonCameraConnectionParameters;
    }
};

struct INTERACTION_PROTOCOL_API CammanGetParametersResponse : public LogicalMessage {
    CammanGetParametersResponse(){}
    CammanGetParametersResponse(const CammanGetParametersResponse &obj) { selfCopy(obj); }
    CammanGetParametersResponse &operator =(const CammanGetParametersResponse &obj) { if (this != &obj) { selfCopy(obj); } return *this; }
    virtual EMessageType type() { return EMessageType::CammanGetParametersResponse; }
    virtual void serialize(QByteArray& payload);
    virtual void deserialize(const QByteArray& payload);

    bool mResult = false;                   ///< результат операции
    QString mJsonCameraManageParameters;    ///< расширенные параметры камеры
private:
    inline void selfCopy(const CammanGetParametersResponse &obj) {
        mResult = obj.mResult;
        mJsonCameraManageParameters = obj.mJsonCameraManageParameters;
    }
};

/// \remark события. включить события

struct INTERACTION_PROTOCOL_API CameventOnEventsRequest : public LogicalMessage {
    CameventOnEventsRequest(){}
    CameventOnEventsRequest(const CameventOnEventsRequest &obj) { selfCopy(obj); }
    CameventOnEventsRequest &operator =(const CameventOnEventsRequest &obj) { if (this != &obj) { selfCopy(obj); } return *this; }
    virtual EMessageType type() { return EMessageType::CameventOnEventsRequest; }
    virtual void serialize(QByteArray& payload);
    virtual void deserialize(const QByteArray& payload);

    QUuid mCameraUid;   ///< уид камеры
    QUuid mStreamUid;   ///< уид потока
    QString mJsonCameraConnectionParameters;    ///< json параметры камеры (АПИ)
    QString mJsonOptions;   ///< опции плагина
private:
    inline void selfCopy(const CameventOnEventsRequest &obj) {
        mCameraUid = obj.mCameraUid;
        mStreamUid = obj.mStreamUid;
        mJsonCameraConnectionParameters = obj.mJsonCameraConnectionParameters;
        mJsonOptions = obj.mJsonOptions;
    }
};

struct INTERACTION_PROTOCOL_API CameventOnEventResponse : public LogicalMessage {
    CameventOnEventResponse(){}
    CameventOnEventResponse(const CameventOnEventResponse &obj) { selfCopy(obj); }
    CameventOnEventResponse &operator =(const CameventOnEventResponse &obj) { if (this != &obj) { selfCopy(obj); } return *this; }
    virtual EMessageType type() { return EMessageType::CameventOnEventResponse; }
    virtual void serialize(QByteArray& payload);
    virtual void deserialize(const QByteArray& payload);

    bool mResult = false;   ///< результат операции
private:
    inline void selfCopy(const CameventOnEventResponse &obj) {
        mResult = obj.mResult;
    }
};

/// \remark события. выключить события

struct INTERACTION_PROTOCOL_API CameventOffEventRequest : public LogicalMessage {
    CameventOffEventRequest(){}
    CameventOffEventRequest(const CameventOffEventRequest &obj) { selfCopy(obj); }
    CameventOffEventRequest &operator =(const CameventOffEventRequest &obj) { if (this != &obj) { selfCopy(obj); } return *this; }
    virtual EMessageType type() { return EMessageType::CameventOffEventRequest; }
    virtual void serialize(QByteArray& payload);
    virtual void deserialize(const QByteArray& payload);

    QUuid mCameraUid;   ///< уид камеры
    QUuid mStreamUid;   ///< уид потока
private:
    inline void selfCopy(const CameventOffEventRequest &obj) {
        mCameraUid = obj.mCameraUid;
        mStreamUid = obj.mStreamUid;
    }
};

struct INTERACTION_PROTOCOL_API CameventOffEventResponse : public LogicalMessage {
    CameventOffEventResponse(){}
    CameventOffEventResponse(const CameventOffEventResponse &obj) { selfCopy(obj); }
    CameventOffEventResponse &operator =(const CameventOffEventResponse &obj) { if (this != &obj) { selfCopy(obj); } return *this; }
    virtual EMessageType type() { return EMessageType::CameventOffEventResponse; }
    virtual void serialize(QByteArray& payload);
    virtual void deserialize(const QByteArray& payload);

    bool mResult = false;   ///< результат операции
private:
    inline void selfCopy(const CameventOffEventResponse &obj) {
        mResult = obj.mResult;
    }
};

/// \remark события. очередное событие движения с кадром
/// работа с буфером событий камеры

struct INTERACTION_PROTOCOL_API CameventGetMoveEventRequest : public LogicalMessage {
    CameventGetMoveEventRequest(){}
    CameventGetMoveEventRequest(const CameventGetMoveEventRequest &obj) { selfCopy(obj); }
    CameventGetMoveEventRequest &operator =(const CameventGetMoveEventRequest &obj) { if (this != &obj) { selfCopy(obj); } return *this; }
    virtual EMessageType type() { return EMessageType::CameventGetMoveEventRequest; }
    virtual void serialize(QByteArray& payload);
    virtual void deserialize(const QByteArray& payload);

    QUuid mStreamUid;   ///< уид потока
private:
    inline void selfCopy(const CameventGetMoveEventRequest &obj) {
        mStreamUid = obj.mStreamUid;
    }
};

struct INTERACTION_PROTOCOL_API CameventGetMoveEventResponse : public LogicalMessage {
    CameventGetMoveEventResponse(){}
    CameventGetMoveEventResponse(const CameventGetMoveEventResponse &obj) { selfCopy(obj); }
    CameventGetMoveEventResponse &operator =(const CameventGetMoveEventResponse &obj) { if (this != &obj) { selfCopy(obj); } return *this; }
    virtual EMessageType type() { return EMessageType::CameventGetMoveEventResponse; }
    virtual void serialize(QByteArray& payload);
    virtual void deserialize(const QByteArray& payload);

    bool mResult = false;               ///< наличие события
    bool mEventHandlerContains = true;  ///< наличе обработчика
    QDateTime mDateTimeEvent;           ///< дата-время события
    QByteArray mPicture;                ///< кадр
private:
    inline void selfCopy(const CameventGetMoveEventResponse &obj) {
        mResult = obj.mResult;
        mEventHandlerContains = obj.mEventHandlerContains;
        mDateTimeEvent = obj.mDateTimeEvent;
        mPicture = obj.mPicture;
    }
};

/// \remark расширенные параметры. перезагрузка камеры

struct INTERACTION_PROTOCOL_API CammanRebootRequest : public LogicalMessage {
    CammanRebootRequest(){}
    CammanRebootRequest(const CammanRebootRequest &obj) { selfCopy(obj); }
    CammanRebootRequest &operator =(const CammanRebootRequest &obj) { if (this != &obj) { selfCopy(obj); } return *this; }
    virtual EMessageType type() { return EMessageType::CammanRebootRequest; }
    virtual void serialize(QByteArray& payload);
    virtual void deserialize(const QByteArray& payload);

    QUuid mCameraUid;   ///< уид камеры
    QString mJsonCameraConnectionParameters;    ///< json параметры камеры (АПИ)
private:
    inline void selfCopy(const CammanRebootRequest &obj) {
        mCameraUid = obj.mCameraUid;
        mJsonCameraConnectionParameters = obj.mJsonCameraConnectionParameters;
    }
};

struct INTERACTION_PROTOCOL_API CammanRebootResponse : public LogicalMessage {
    CammanRebootResponse(){}
    CammanRebootResponse(const CammanRebootResponse &obj) { selfCopy(obj); }
    CammanRebootResponse &operator =(const CammanRebootResponse &obj) { if (this != &obj) { selfCopy(obj); } return *this; }
    virtual EMessageType type() { return EMessageType::CammanRebootResponse; }
    virtual void serialize(QByteArray& payload);
    virtual void deserialize(const QByteArray& payload);

    bool mResult = false;   ///< результат операции
private:
    inline void selfCopy(const CammanRebootResponse &obj) {
        mResult = obj.mResult;
    }
};

}

#endif // SHAREDMEMORYCAMERAPROTOCOL_H
