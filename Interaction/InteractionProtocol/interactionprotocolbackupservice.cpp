#include "interactionprotocolbackupservice.h"

#define NULL_TERM_CHAR \
    (char)('\0')

// JsonStringParserMachine

QVector<QString> InteractionProtocolBackupService::JsonStringParserMachine::step(const QByteArray &data)
{
    QByteArray currentData;// текущие данные
    // учёт предыдущих данных (на предыдущем шаге)
    if (!mPrevData.isEmpty()) {
        currentData = mPrevData.append(data);
    } else {
        currentData = data;
    }
    QVector<QString> messages; // список разобранных сообщений
    // Цикл разбора сообщения
    while(currentData.length() > 0) { // пока есть что обрабатывать
        auto indexOfEnd = currentData.indexOf(NULL_TERM_CHAR, 0);
        if (indexOfEnd == -1) { // не найден конец очередного сообщения
            break;
        } else {
            QString message = QString::fromUtf8(currentData.left(indexOfEnd));
            currentData = currentData.remove(0, indexOfEnd + 1);
            messages.append(message);
        }
    }
    mPrevData = currentData;
    return messages;
}

void InteractionProtocolBackupService::JsonStringParserMachine::reset()
{
    mPrevData.clear();
}

QJsonObject InteractionProtocolBackupService::HeaderMessage::toJsonObject() const
{
    QJsonObject object;
    object.insert("Type", QJsonValue::fromVariant(static_cast<int>(mType)));
    object.insert("UidMessage", QJsonValue::fromVariant(mUidMessage.toString(QUuid::WithoutBraces)));
    //return IJsonable::fromJsonObject(object);
    return object;
}

QByteArray InteractionProtocolBackupService::HeaderMessage::fromJsonObject(const QJsonObject &object)
{
    QJsonDocument doc(object);
    auto jsonString = doc.toJson(QJsonDocument::Indented);
    jsonString.append(NULL_TERM_CHAR);
    return jsonString;
}

QJsonObject InteractionProtocolBackupService::ReadListMessage::toJsonObject() const
{
    QJsonObject object;
    ICommonFields::toJsonObject(object);
    IJsonable::typeToJsonObject(object);
    return object;
}

QByteArray InteractionProtocolBackupService::ReadListMessage::fromJsonObject(const QJsonObject &object)
{
    QJsonDocument doc(object);
    auto jsonString = doc.toJson(QJsonDocument::Indented);
    jsonString.append(NULL_TERM_CHAR);
    return jsonString;
}


bool InteractionProtocolBackupService::ReadListMessage::isValid() const
{
    //список по 1 uuid ?
    if(mUidMessage.isNull())
        return false;
    else
        return true;
}

InteractionProtocolBackupService::ReadListMessage::ReadListMessage(const QJsonObject &object)
{
    if ( !IJsonable::typeFromJsonObject(object) )
        return;
    ICommonFields::fromJsonObject(object);
}

EDataType InteractionProtocolBackupService::ReadListMessage::type() const
{
    return EDataType::ResponseBackupList;
}

QJsonObject InteractionProtocolBackupService::RequestCreateBackup::toJsonObject() const
{
    QJsonObject object;
    ICommonFields::toJsonObject(object);
    IJsonable::typeToJsonObject(object);
    QUUID_TO_JSON(mUidMessage, object);
    QSTRING_TO_JSON(mStrPath, object);
    return object;
}

bool InteractionProtocolBackupService::RequestCreateBackup::isValid() const
{
    if(mUidMessage.isNull())
        return false;
    else
        return true;
}

InteractionProtocolBackupService::RequestCreateBackup::RequestCreateBackup(const QJsonObject &object)
{
    if ( !IJsonable::typeFromJsonObject(object)
            )
        return;
    if ( !object.contains("mUidMessage") ||
         !object.contains("mStrPath")
         )
        return;
    ICommonFields::fromJsonObject(object);
    JSON_TO_QUUID(object, mUidMessage);
    JSON_TO_QSTRING(object, mStrPath);
}

EDataType InteractionProtocolBackupService::RequestCreateBackup::type() const
{
    return EDataType::RequestCreateBackup;
}

InteractionProtocolBackupService::ResponseCreateBackup::ResponseCreateBackup(const QJsonObject &json)
{
    if ( !IJsonable::typeFromJsonObject(json) ||
         !IResponseResultable::resultResponseFromJsonObject(json)
            )
        return;
    ICommonFields::fromJsonObject(json);
    JSON_TO_QUUID(json, mUidMessage);
    JSON_TO_QSTRING(json, mStrPath);
    JSON_TO_BOOL(json, mLaunchedBackup);
    JSON_TO_BOOL(json, mLaunchedRestor);
    JSON_TO_INT(json, mProgress);
}

EDataType InteractionProtocolBackupService::ResponseCreateBackup::type() const
{
    return EDataType::ResponseCreateBackup;
}

QJsonObject InteractionProtocolBackupService::ResponseCreateBackup::toJsonObject() const
{
    QJsonObject object;
    ICommonFields::toJsonObject(object);
    IJsonable::typeToJsonObject(object);
    IResponseResultable::resultResponseToJsonObject(object);
    QUUID_TO_JSON(mUidMessage, object);
    QSTRING_TO_JSON(mStrPath, object);
    BOOL_TO_JSON(mLaunchedBackup, object);
    BOOL_TO_JSON(mLaunchedRestor, object);
    INT_TO_JSON(mProgress, object);
    return object;
}

bool InteractionProtocolBackupService::ResponseCreateBackup::isValid() const
{
    if(mUidMessage.isNull())
        return false;
    else
        return true;
}

InteractionProtocolBackupService::RequestApplyBackup::RequestApplyBackup(const QJsonObject &object)
{
    if ( !IJsonable::typeFromJsonObject(object)
            )
        return;
    if ( !object.contains("mUidMessage") ||
         !object.contains("mStrPath")
         )
        return;
    ICommonFields::fromJsonObject(object);
    JSON_TO_QUUID(object, mUidMessage);
    JSON_TO_QSTRING(object, mStrPath);
}

EDataType InteractionProtocolBackupService::RequestApplyBackup::type() const
{
    return EDataType::RequestApplyBackup;
}

QJsonObject InteractionProtocolBackupService::RequestApplyBackup::toJsonObject() const
{
    QJsonObject object;
    ICommonFields::toJsonObject(object);
    IJsonable::typeToJsonObject(object);
    QUUID_TO_JSON(mUidMessage, object);
    QSTRING_TO_JSON(mStrPath, object);
    return object;
}

bool InteractionProtocolBackupService::RequestApplyBackup::isValid() const
{
    if(mUidMessage.isNull())
        return false;
    else
        return true;
}

InteractionProtocolBackupService::ResponseApplyBackup::ResponseApplyBackup(const QJsonObject &json)
{
    if ( !IJsonable::typeFromJsonObject(json) ||
         !IResponseResultable::resultResponseFromJsonObject(json) )
        return;
    ICommonFields::fromJsonObject(json);
    JSON_TO_QUUID(json, mUidMessage);
    JSON_TO_QSTRING(json, mStrPath);
    JSON_TO_BOOL(json, mLaunchedBackup);
    JSON_TO_BOOL(json, mLaunchedRestor);
    JSON_TO_INT(json, mProgress);
}

EDataType InteractionProtocolBackupService::ResponseApplyBackup::type() const
{
    return EDataType::ResponseApplyBackup;
}

QJsonObject InteractionProtocolBackupService::ResponseApplyBackup::toJsonObject() const
{
    QJsonObject object;
    ICommonFields::toJsonObject(object);
    IJsonable::typeToJsonObject(object);
    IResponseResultable::resultResponseToJsonObject(object);
    QUUID_TO_JSON(mUidMessage, object);
    QSTRING_TO_JSON(mStrPath, object);
    BOOL_TO_JSON(mLaunchedBackup, object);
    BOOL_TO_JSON(mLaunchedRestor, object);
    INT_TO_JSON(mProgress, object);
    return object;
}

bool InteractionProtocolBackupService::ResponseApplyBackup::isValid() const
{
    if(mUidMessage.isNull())
        return false;
    else
        return true;
}

InteractionProtocolBackupService::RequestStateBackup::RequestStateBackup(const QJsonObject &jsObj)
{
    if ( !IJsonable::typeFromJsonObject(jsObj)
            )
        return;
    ICommonFields::fromJsonObject(jsObj);
    JSON_TO_QUUID(jsObj, mUidMessage);
    JSON_TO_BOOL(jsObj, mStatusBackup);
    JSON_TO_BOOL(jsObj, mStatusRestore);
    JSON_TO_INT(jsObj, mProgress);
}

EDataType InteractionProtocolBackupService::RequestStateBackup::type() const
{
    return EDataType::RequestStateBackup;
}

QJsonObject InteractionProtocolBackupService::RequestStateBackup::toJsonObject() const
{
    QJsonObject object;
    ICommonFields::toJsonObject(object);
    IJsonable::typeToJsonObject(object);
    QUUID_TO_JSON(mUidMessage, object);
    BOOL_TO_JSON(mStatusBackup, object);
    BOOL_TO_JSON(mStatusRestore, object);
    INT_TO_JSON(mProgress, object);
    return object;
}

bool InteractionProtocolBackupService::RequestStateBackup::isValid() const
{
    if(mUidMessage.isNull())
        return false;
    else
        return true;
}

InteractionProtocolBackupService::ResponseStateBackup::ResponseStateBackup(const QJsonObject &json)
{
    if ( !IJsonable::typeFromJsonObject(json) ||
         !IResponseResultable::resultResponseFromJsonObject(json)
            )
        return;
    ICommonFields::fromJsonObject(json);
    JSON_TO_QUUID(json, mUidMessage);
    JSON_TO_BOOL(json, mStatusBackup);
    JSON_TO_BOOL(json, mStatusRestore);
    JSON_TO_INT(json, mProgress);
}

EDataType InteractionProtocolBackupService::ResponseStateBackup::type() const
{
    return EDataType::ResponseStateBackup;
}

QJsonObject InteractionProtocolBackupService::ResponseStateBackup::toJsonObject() const
{
    QJsonObject object;
    ICommonFields::toJsonObject(object);
    IJsonable::typeToJsonObject(object);
    IResponseResultable::resultResponseToJsonObject(object);
    QUUID_TO_JSON(mUidMessage, object);
    BOOL_TO_JSON(mStatusBackup, object);
    BOOL_TO_JSON(mStatusRestore, object);
    INT_TO_JSON(mProgress, object);
    return object;
}

bool InteractionProtocolBackupService::ResponseStateBackup::isValid() const
{
    if(mUidMessage.isNull())
        return false;
    else
        return true;
}
