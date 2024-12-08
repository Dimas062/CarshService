#include "sharedmemorycameraprotocol.h"
#include <QIODevice>

CameraProtocol::Message::Message() : mLength(0)
{
}

CameraProtocol::Message::Message(const Message &obj)
{
    selfCopy(obj);
}

CameraProtocol::Message &CameraProtocol::Message::operator =(const Message &obj)
{
    if (this != &obj) {
        selfCopy(obj);
    }
    return *this;
}

void CameraProtocol::Message::deserialize(const QByteArray &raw)
{
    QDataStream rd(raw);
    rd >> mLength;
    {
        int len = 0;
        rd >> len;
        auto data = new char[len];
        rd.readRawData(data, len);
        QByteArray array = QByteArray::fromRawData(data, len);
        array.detach();
        mUid = QUuid::fromRfc4122(array);
        delete [] data;
    }
    {
        int len = 0;
        rd >> len;
        auto data = new char[len];
        rd.readRawData(data, len);
        mPayload = QByteArray::fromRawData(data, len);
        mPayload.detach();
        delete [] data;
    }
    {
        QDataStream rdPayload(mPayload);
        int type = 0;
        rdPayload >> type;
        mType = static_cast<EMessageType>( type );
    }
}

void CameraProtocol::Message::serialize(QByteArray &raw)
{
    QDataStream wr(&raw, QIODevice::WriteOnly);
    wr << mLength;
    {
        auto uid = mUid.toRfc4122();
        int len = uid.length();
        wr << len;
        wr.writeRawData(uid.data(), len);
    }
    {
        int len = mPayload.length();
        wr << len;
        wr.writeRawData(mPayload.data(), len);
    }
}

int CameraProtocol::Message::length() const
{
    return mLength;
}

const QUuid &CameraProtocol::Message::uid() const
{
    return mUid;
}

const QByteArray &CameraProtocol::Message::payload() const
{
    return mPayload;
}

const CameraProtocol::EMessageType &CameraProtocol::Message::type() const
{
    return mType;
}

void CameraProtocol::Message::registerMetatype()
{
    qRegisterMetaType<CameraProtocol::Message>("CameraProtocol::Message");
}

QUuid CameraProtocol::Message::setPayload(const QByteArray &payload)
{
    mLength = 0;
    mLength += sizeof(mLength);
    mPayload = payload;
    mUid = QUuid::createUuid();
    mLength += mUid.toRfc4122().length() + sizeof (int);
    mLength += mPayload.length() + sizeof (int);
    {
        QDataStream rdPayload(mPayload);
        int type = 0;
        rdPayload >> type;
        mType = static_cast<EMessageType>( type );
    }
    return mUid;
}

void CameraProtocol::Message::setUid(const QUuid &uid)
{
    mUid = uid;
}

void CameraProtocol::Message::selfCopy(const Message &obj)
{
    mLength = obj.mLength;
    mUid = obj.mUid;
    mPayload = obj.mPayload;
    mType = obj.mType;
}

CameraProtocol::EMessageType CameraProtocol::Message::getType(const QByteArray &payload)
{
    QDataStream rd(payload);
    int typeVal;
    rd >> typeVal;
    return static_cast<EMessageType>( typeVal );
}

const QString CameraProtocol::SharedMemoryNaming:: cLocalServerCameraManager = QString("vs.cameramanageapp.localserver");

/// \remark расширенные параметры. установить расширенные параметры камеры

void CameraProtocol::CammanSetParametersRequest::serialize(QByteArray &payload)
{
    QDataStream wr(&payload, QIODevice::WriteOnly);
    wr << static_cast<int>( type() );
    wr << mCameraUid;
    wr << mJsonCameraConnectionParameters;
    wr << mJsonCameraManageParameters;
}

void CameraProtocol::CammanSetParametersRequest::deserialize(const QByteArray &payload)
{
    QDataStream rd(payload);
    int typeVal;
    rd >> typeVal;
    if (static_cast<EMessageType>( typeVal ) == type()) {
        rd >> mCameraUid;
        rd >> mJsonCameraConnectionParameters;
        rd >> mJsonCameraManageParameters;
    } else {
        qDebug("CameraProtocol::CammanSetParametersRequest::deserialize - bad type - %d", typeVal);
    }
}

void CameraProtocol::CammanSetParametersResponse::serialize(QByteArray &payload)
{
    QDataStream wr(&payload, QIODevice::WriteOnly);
    wr << static_cast<int>( type() );
    wr << mResult;
}

void CameraProtocol::CammanSetParametersResponse::deserialize(const QByteArray &payload)
{
    QDataStream rd(payload);
    int typeVal;
    rd >> typeVal;
    if (static_cast<EMessageType>( typeVal ) == type()) {
        rd >> mResult;
    } else {
        qDebug("CameraProtocol::CammanSetParametersResponse::deserialize - bad type - %d", typeVal);
    }
}

/// \remark расширенные параметры. получить расширенные параметры камеры

void CameraProtocol::CammanGetParametersRequest::serialize(QByteArray &payload)
{
    QDataStream wr(&payload, QIODevice::WriteOnly);
    wr << static_cast<int>( type() );
    wr << mCameraUid;
    wr << mStreamType;
    wr << mJsonCameraConnectionParameters;
}

void CameraProtocol::CammanGetParametersRequest::deserialize(const QByteArray &payload)
{
    QDataStream rd(payload);
    int typeVal;
    rd >> typeVal;
    if (static_cast<EMessageType>( typeVal ) == type()) {
        rd >> mCameraUid;
        rd >> mStreamType;
        rd >> mJsonCameraConnectionParameters;
    } else {
        qDebug("CameraProtocol::CammanGetParametersRequest::deserialize - bad type - %d", typeVal);
    }
}

void CameraProtocol::CammanGetParametersResponse::serialize(QByteArray &payload)
{
    QDataStream wr(&payload, QIODevice::WriteOnly);
    wr << static_cast<int>( type() );
    wr << mResult;
    wr << mJsonCameraManageParameters;
}

void CameraProtocol::CammanGetParametersResponse::deserialize(const QByteArray &payload)
{
    QDataStream rd(payload);
    int typeVal;
    rd >> typeVal;
    if (static_cast<EMessageType>( typeVal ) == type()) {
        rd >> mResult;
        rd >> mJsonCameraManageParameters;
    } else {
        qDebug("CameraProtocol::CammanGetParametersResponse::deserialize - bad type - %d", typeVal);
    }
}

/// \remark события. включить события

void CameraProtocol::CameventOnEventsRequest::serialize(QByteArray &payload)
{
    QDataStream wr(&payload, QIODevice::WriteOnly);
    wr << static_cast<int>( type() );
    wr << mCameraUid;
    wr << mStreamUid;
    wr << mJsonCameraConnectionParameters;
    wr << mJsonOptions;
}

void CameraProtocol::CameventOnEventsRequest::deserialize(const QByteArray &payload)
{
    QDataStream rd(payload);
    int typeVal;
    rd >> typeVal;
    if (static_cast<EMessageType>( typeVal ) == type()) {
        rd >> mCameraUid;
        rd >> mStreamUid;
        rd >> mJsonCameraConnectionParameters;
        rd >> mJsonOptions;
    } else {
        qDebug("CameraProtocol::CameventOnEventsRequest::deserialize - bad type - %d", typeVal);
    }
}

void CameraProtocol::CameventOnEventResponse::serialize(QByteArray &payload)
{
    QDataStream wr(&payload, QIODevice::WriteOnly);
    wr << static_cast<int>( type() );
    wr << mResult;
}

void CameraProtocol::CameventOnEventResponse::deserialize(const QByteArray &payload)
{
    QDataStream rd(payload);
    int typeVal;
    rd >> typeVal;
    if (static_cast<EMessageType>( typeVal ) == type()) {
        rd >> mResult;
    } else {
        qDebug("CameraProtocol::CameventOnEventResponse::deserialize - bad type - %d", typeVal);
    }
}

/// \remark события. выключить события

void CameraProtocol::CameventOffEventRequest::serialize(QByteArray &payload)
{
    QDataStream wr(&payload, QIODevice::WriteOnly);
    wr << static_cast<int>( type() );
    wr << mCameraUid;
    wr << mStreamUid;
}

void CameraProtocol::CameventOffEventRequest::deserialize(const QByteArray &payload)
{
    QDataStream rd(payload);
    int typeVal;
    rd >> typeVal;
    if (static_cast<EMessageType>( typeVal ) == type()) {
        rd >> mCameraUid;
        rd >> mStreamUid;
    } else {
        qDebug("CameraProtocol::CameventOffEventsRequest::deserialize - bad type - %d", typeVal);
    }
}

void CameraProtocol::CameventOffEventResponse::serialize(QByteArray &payload)
{
    QDataStream wr(&payload, QIODevice::WriteOnly);
    wr << static_cast<int>( type() );
    wr << mResult;
}

void CameraProtocol::CameventOffEventResponse::deserialize(const QByteArray &payload)
{
    QDataStream rd(payload);
    int typeVal;
    rd >> typeVal;
    if (static_cast<EMessageType>( typeVal ) == type()) {
        rd >> mResult;
    } else {
        qDebug("CameraProtocol::CameventOffEventResponse::deserialize - bad type - %d", typeVal);
    }
}

/// \remark события. очередное событие движения с кадром

void CameraProtocol::CameventGetMoveEventRequest::serialize(QByteArray &payload)
{
    QDataStream wr(&payload, QIODevice::WriteOnly);
    wr << static_cast<int>( type() );
    wr << mStreamUid;
}

void CameraProtocol::CameventGetMoveEventRequest::deserialize(const QByteArray &payload)
{
    QDataStream rd(payload);
    int typeVal;
    rd >> typeVal;
    if (static_cast<EMessageType>( typeVal ) == type()) {
        rd >> mStreamUid;
    } else {
        qDebug("CameraProtocol::CameventGetMoveEventRequest::deserialize - bad type - %d", typeVal);
    }
}

void CameraProtocol::CameventGetMoveEventResponse::serialize(QByteArray &payload)
{
    QDataStream wr(&payload, QIODevice::WriteOnly);
    wr << static_cast<int>( type() );
    wr << mResult;
    wr << mEventHandlerContains;
    wr << mDateTimeEvent;
    wr << mPicture;
}

void CameraProtocol::CameventGetMoveEventResponse::deserialize(const QByteArray &payload)
{
    QDataStream rd(payload);
    int typeVal;
    rd >> typeVal;
    if (static_cast<EMessageType>( typeVal ) == type()) {
        rd >> mResult;
        rd >> mEventHandlerContains;
        rd >> mDateTimeEvent;
        rd >> mPicture;
    } else {
        qDebug("CameraProtocol::CameventGetMoveEventResponse::deserialize - bad type - %d", typeVal);
    }
}

/// \remark расширенные параметры. перезагрузка камеры

void CameraProtocol::CammanRebootRequest::serialize(QByteArray &payload)
{
    QDataStream wr(&payload, QIODevice::WriteOnly);
    wr << static_cast<int>( type() );
    wr << mCameraUid;
    wr << mJsonCameraConnectionParameters;
}

void CameraProtocol::CammanRebootRequest::deserialize(const QByteArray &payload)
{
    QDataStream rd(payload);
    int typeVal;
    rd >> typeVal;
    if (static_cast<EMessageType>( typeVal ) == type()) {
        rd >> mCameraUid;
        rd >> mJsonCameraConnectionParameters;
    } else {
        qDebug("CameraProtocol::CammanRebootRequest::deserialize - bad type - %d", typeVal);
    }
}

void CameraProtocol::CammanRebootResponse::serialize(QByteArray &payload)
{
    QDataStream wr(&payload, QIODevice::WriteOnly);
    wr << static_cast<int>( type() );
    wr << mResult;
}

void CameraProtocol::CammanRebootResponse::deserialize(const QByteArray &payload)
{
    QDataStream rd(payload);
    int typeVal;
    rd >> typeVal;
    if (static_cast<EMessageType>( typeVal ) == type()) {
        rd >> mResult;
    } else {
        qDebug("CameraProtocol::CammanRebootResponse::deserialize - bad type - %d", typeVal);
    }
}

/// \remark parser machine

QVector<CameraProtocol::Message> CameraProtocol::ParserMessageMachine::step(const QByteArray &data)
{
    QByteArray currentData;// текущие данные
    // учёт предыдущих данных (на предыдущем шаге)
    if (!mPrevData.isEmpty()) {
        currentData = mPrevData.append(data);
    } else {
        currentData = data;
    }
    QVector<CameraProtocol::Message> messages; // список разобранных сообщений
    // Цикл разбора сообщения
    while(currentData.length() > 4) { // пока есть что обрабатывать
        int len = 0;
        {
            QDataStream rd(currentData);
            rd >> len;
        }
        auto curLenData = currentData.length();
        qDebug("currentData.length() %d, len %d", curLenData, len);
        if (curLenData >= len) {
            CameraProtocol::Message message;
            auto rawMessage = currentData.left(len);
            message.deserialize(rawMessage);
            currentData = currentData.remove(0, len);
            messages.append(message);
        } else {
            // ещё не накопилисиь данные
            break;
        }
    }
    mPrevData = currentData;
    return messages;
}

void CameraProtocol::ParserMessageMachine::reset()
{
    mPrevData.clear();
}
