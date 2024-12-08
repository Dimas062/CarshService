#include "interactionprotocolevents.h"
#include "servicemacros.h"
#include "QBuffer"
#include "QPicture"

// InteractionProtocolEvent

InteractionProtocolEvent::InteractionProtocolEvent() : IJsonable()
{

}

InteractionProtocolEvent::InteractionProtocolEvent(const InteractionProtocolEvent &obj)
{
    selfCopy(obj);
}

InteractionProtocolEvent &InteractionProtocolEvent::operator =(const InteractionProtocolEvent &obj)
{
    OPERATOR_EQUAL_BODY;
}

InteractionProtocolEvent::InteractionProtocolEvent(const QJsonObject &json)
{
    if (!IJsonable::typeFromJsonObject(json))
        return;
    if ( !json.contains("mCameraStreamUuid") ||
         !json.contains("mEventUuid") ||
         !json.contains("mEventTypeUuid") ||
         !json.contains("mEventText") ||
         !json.contains("mDateTime") ||
         !json.contains("mForeColor") ||
         !json.contains("mBackColor")
         )
        return;
    JSON_TO_QUUID(json, mCameraStreamUuid);
    JSON_TO_QUUID(json, mEventUuid);
    JSON_TO_QUUID(json, mEventTypeUuid);
    JSON_TO_QSTRING(json, mEventText);
    JSON_TO_LONG_LONG(json, mDateTime);
    mForeColor = QColor(json.value("mForeColor").toString());
    mBackColor = QColor(json.value("mBackColor").toString());
}

void InteractionProtocolEvent::selfCopy(const InteractionProtocolEvent &obj)
{
    mCameraStreamUuid = obj.mCameraStreamUuid;
    mEventUuid = obj.mEventUuid;
    mEventTypeUuid = obj.mEventTypeUuid;
    mEventText = obj.mEventText;
    mDateTime = obj.mDateTime;
    mForeColor = obj.mForeColor;
    mBackColor = obj.mBackColor;
}

EDataType InteractionProtocolEvent::type() const
{
    return EDataType::InteractionProtocolEvent;
}

QJsonObject InteractionProtocolEvent::toJsonObject() const
{
    QJsonObject object;
    IJsonable::typeToJsonObject(object);
    QUUID_TO_JSON(mCameraStreamUuid, object);
    QUUID_TO_JSON(mEventUuid, object);
    QUUID_TO_JSON(mEventTypeUuid, object);
    QSTRING_TO_JSON(mEventText, object);
    LONG_LONG_TO_JSON(mDateTime, object);
    object.insert("mForeColor", QJsonValue::fromVariant(mForeColor.name()));
    object.insert("mBackColor", QJsonValue::fromVariant(mBackColor.name()));
    return object;
}

bool InteractionProtocolEvent::isValid() const
{
    return !mCameraStreamUuid.isNull() && !mEventUuid.isNull();
}

// InteractionProtocolNotification

InteractionProtocolNotification::InteractionProtocolNotification() : IJsonable()
{

}

InteractionProtocolNotification::InteractionProtocolNotification(const InteractionProtocolNotification &obj)
{
    selfCopy(obj);
}

InteractionProtocolNotification &InteractionProtocolNotification::operator =(const InteractionProtocolNotification &obj)
{
    OPERATOR_EQUAL_BODY;
}

InteractionProtocolNotification::InteractionProtocolNotification(const QJsonObject &json)
{
    if (!IJsonable::typeFromJsonObject(json))
        return;
    if ( !json.contains("mCameraStreamUuid") ||
         !json.contains("mEventTypeUuid") ||
         !json.contains("mHexedPicture") ||
         !json.contains("mDateTime")
         )
        return;
    JSON_TO_QUUID(json, mCameraStreamUuid);
    JSON_TO_QUUID(json, mEventTypeUuid);
    JSON_TO_LONG_LONG(json, mDateTime);
    mHexedPicture = json.value("mHexedPicture").toVariant().toByteArray();
}

QPicture InteractionProtocolNotification::picture()
{
    QPicture picture;
    QByteArray array = QByteArray::fromHex(mHexedPicture);
    QBuffer pictureBuffer(&array);
    pictureBuffer.open(QIODevice::ReadOnly);
    picture.load(&pictureBuffer);
    return picture;
}

void InteractionProtocolNotification::setPicture(QPicture picture)
{
    mHexedPicture.clear();
    QBuffer pictureBuffer(&mHexedPicture);
    pictureBuffer.open(QIODevice::WriteOnly);
    picture.save(&pictureBuffer);
    pictureBuffer.close();
    mHexedPicture = mHexedPicture.toHex();
}

void InteractionProtocolNotification::selfCopy(const InteractionProtocolNotification &obj)
{
    mCameraStreamUuid = obj.mCameraStreamUuid;
    mEventTypeUuid = obj.mEventTypeUuid;
    mHexedPicture = obj.mHexedPicture;
    mDateTime = obj.mDateTime;
}

EDataType InteractionProtocolNotification::type() const
{
    return EDataType::InteractionProtocolNotification;
}

QJsonObject InteractionProtocolNotification::toJsonObject() const
{
    QJsonObject object;
    IJsonable::typeToJsonObject(object);
    QUUID_TO_JSON(mCameraStreamUuid, object);
    QUUID_TO_JSON(mEventTypeUuid, object);
    LONG_LONG_TO_JSON(mDateTime, object);
    object.insert("mHexedPicture", QJsonValue::fromVariant(mHexedPicture));
    return object;
}

bool InteractionProtocolNotification::isValid() const
{
    return !mCameraStreamUuid.isNull();
}

// InteractionProtocolIamPluginContainer

InteractionProtocolIamPluginContainer::InteractionProtocolIamPluginContainer() : IJsonable()
{

}

InteractionProtocolIamPluginContainer::InteractionProtocolIamPluginContainer(const InteractionProtocolIamPluginContainer &obj)
{
    selfCopy(obj);
}

InteractionProtocolIamPluginContainer &InteractionProtocolIamPluginContainer::operator =(const InteractionProtocolIamPluginContainer &obj)
{
    OPERATOR_EQUAL_BODY;
}

InteractionProtocolIamPluginContainer::InteractionProtocolIamPluginContainer(const QJsonObject &json)
{
    if (!IJsonable::typeFromJsonObject(json))
        return;
}

void InteractionProtocolIamPluginContainer::selfCopy(const InteractionProtocolIamPluginContainer &obj)
{
    Q_UNUSED(obj)
}

EDataType InteractionProtocolIamPluginContainer::type() const
{
    return EDataType::InteractionProtocolIamPluginContainer;
}

QJsonObject InteractionProtocolIamPluginContainer::toJsonObject() const
{
    QJsonObject object;
    IJsonable::typeToJsonObject(object);
    return object;
}

bool InteractionProtocolIamPluginContainer::isValid() const
{
    return true;
}

// InteractionProtocolIamClient

InteractionProtocolIamClient::InteractionProtocolIamClient() : IJsonable()
{

}

InteractionProtocolIamClient::InteractionProtocolIamClient(const InteractionProtocolIamClient &obj)
{
    selfCopy(obj);
}

InteractionProtocolIamClient &InteractionProtocolIamClient::operator =(const InteractionProtocolIamClient &obj)
{
    OPERATOR_EQUAL_BODY;
}

InteractionProtocolIamClient::InteractionProtocolIamClient(const QJsonObject &json)
{
    if (!IJsonable::typeFromJsonObject(json))
        return;
    if ( !json.contains("mClientUid")
         )
        return;
    JSON_TO_QUUID(json, mClientUid);
}

void InteractionProtocolIamClient::selfCopy(const InteractionProtocolIamClient &obj)
{
    mClientUid = obj.mClientUid;
}

EDataType InteractionProtocolIamClient::type() const
{
    return EDataType::InteractionProtocolIamClient;
}

QJsonObject InteractionProtocolIamClient::toJsonObject() const
{
    QJsonObject object;
    IJsonable::typeToJsonObject(object);
    QUUID_TO_JSON(mClientUid, object);
    return object;
}

bool InteractionProtocolIamClient::isValid() const
{
        return !mClientUid.isNull();
}

// InteractionProtocolFilter

InteractionProtocolFilter::InteractionProtocolFilter() : IJsonable()
{

}

InteractionProtocolFilter::InteractionProtocolFilter(const InteractionProtocolFilter &obj)
{
    selfCopy(obj);
}

InteractionProtocolFilter &InteractionProtocolFilter::operator =(const InteractionProtocolFilter &obj)
{
    OPERATOR_EQUAL_BODY;
}

InteractionProtocolFilter::InteractionProtocolFilter(const QJsonObject &json)
{
    if (!IJsonable::typeFromJsonObject(json))
        return;
    if ( !json.contains("mCameraUuid") ||
         !json.contains("mBroadcastResolution")
         )
        return;
    JSON_TO_QUUID(json, mCameraUuid);
    JSON_TO_BOOL(json, mBroadcastResolution);
}

void InteractionProtocolFilter::selfCopy(const InteractionProtocolFilter &obj)
{
    mCameraUuid = obj.mCameraUuid;
    mBroadcastResolution = obj.mBroadcastResolution;
}

EDataType InteractionProtocolFilter::type() const
{
    return EDataType::InteractionProtocolFilter;
}

QJsonObject InteractionProtocolFilter::toJsonObject() const
{
    QJsonObject object;
    IJsonable::typeToJsonObject(object);
    QUUID_TO_JSON(mCameraUuid, object);
    BOOL_TO_JSON(mBroadcastResolution, object);
    return object;
}

bool InteractionProtocolFilter::isValid() const
{
    return !mCameraUuid.isNull();
}

// InteractionProtocolCassyEvent

InteractionProtocolCassyEvent::InteractionProtocolCassyEvent() : IJsonable()
{
    
}

InteractionProtocolCassyEvent::InteractionProtocolCassyEvent(const InteractionProtocolCassyEvent &obj)
{
    selfCopy(obj);
}

InteractionProtocolCassyEvent &InteractionProtocolCassyEvent::operator =(const InteractionProtocolCassyEvent &obj)
{
    OPERATOR_EQUAL_BODY;
}

InteractionProtocolCassyEvent::InteractionProtocolCassyEvent(const QJsonObject &json)
{
    if (!IJsonable::typeFromJsonObject(json))
        return;
    if ( !json.contains("mCassyUuid") ||
         !json.contains("mEventType") ||
         !json.contains("mDate") ||
         !json.contains("mMessage") ||
         !json.contains("mForeColor") ||
         !json.contains("mBackColor")
         )
        return;
    JSON_TO_QUUID(json, mCassyUuid);
    JSON_TO_ENUM(json, InteractionProtocolCashControlService::EEventType, mEventType);
    JSON_TO_QDATETIME(json, mDate);
    JSON_TO_QSTRING_NO_TRIM(json, mMessage);
    mForeColor = QColor(json.value("mForeColor").toString());
    mBackColor = QColor(json.value("mBackColor").toString());
}

void InteractionProtocolCassyEvent::selfCopy(const InteractionProtocolCassyEvent &obj)
{
    mCassyUuid = obj.mCassyUuid;
    mEventType = obj.mEventType;
    mDate = obj.mDate;
    mMessage = obj.mMessage;
    mForeColor = obj.mForeColor;
    mBackColor = obj.mBackColor;
}

EDataType InteractionProtocolCassyEvent::type() const
{
    return EDataType::InteractionProtocolCassyEvent;
}

QJsonObject InteractionProtocolCassyEvent::toJsonObject() const
{
    QJsonObject object;
    IJsonable::typeToJsonObject(object);
    QUUID_TO_JSON(mCassyUuid, object);
    ENUM_TO_JSON(mEventType, object);
    QDATETIME_TO_JSON(mDate, object);
    QSTRING_TO_JSON(mMessage, object);
    object.insert("mForeColor", QJsonValue::fromVariant(mForeColor.toRgb()));
    object.insert("mBackColor", QJsonValue::fromVariant(mBackColor.toRgb()));
    return object;
}

bool InteractionProtocolCassyEvent::isValid() const
{
    return !mCassyUuid.isNull();
}

// InteractionProtocolHeartbeat

InteractionProtocolHeartbeat::InteractionProtocolHeartbeat(): IJsonable()
{
    
}

InteractionProtocolHeartbeat &InteractionProtocolHeartbeat::operator =(const InteractionProtocolHeartbeat &obj)
{
    OPERATOR_EQUAL_BODY;
}


InteractionProtocolHeartbeat::InteractionProtocolHeartbeat(const InteractionProtocolHeartbeat &obj)
{
    selfCopy(obj);
}

InteractionProtocolHeartbeat::InteractionProtocolHeartbeat(const QJsonObject &json)
{
    if (!IJsonable::typeFromJsonObject(json))
        return;
}

void InteractionProtocolHeartbeat::selfCopy(const InteractionProtocolHeartbeat &obj)
{
    Q_UNUSED(obj)
}

EDataType InteractionProtocolHeartbeat::type() const
{
    return EDataType::InteractionProtocolHeartbeat;
}

QJsonObject InteractionProtocolHeartbeat::toJsonObject() const
{
    QJsonObject object;
    IJsonable::typeToJsonObject(object);
    return object;
}

bool InteractionProtocolHeartbeat::isValid() const
{
    return true;
}
