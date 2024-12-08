#include "interactionprotocolcashcontrolservice.h"

#define NULL_TERM_CHAR \
    (char)('\0')

// JsonStringParserMachine

QVector<QString> InteractionProtocolCashControlService::JsonStringParserMachine::step(const QByteArray &data)
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

void InteractionProtocolCashControlService::JsonStringParserMachine::reset()
{
    mPrevData.clear();
}

// IJsonStringable

QByteArray InteractionProtocolCashControlService::IJsonStringable::fromJsonObject(const QJsonObject &object) const
{
    QJsonDocument doc(object);
    auto jsonString = doc.toJson(QJsonDocument::Indented);
    jsonString.append(NULL_TERM_CHAR);
    return jsonString;
}

QJsonObject InteractionProtocolCashControlService::IJsonStringable::toJsobObject(const QString &text, const Type &type) const
{
    auto object = toJsobObject(text);
    if (
            object.contains("Type") &&
            (type == static_cast<Type>(object.value("Type").toInt()))
            ) {
        return object;
    } else {
        return QJsonObject();
    }
}

QJsonObject InteractionProtocolCashControlService::IJsonStringable::toJsobObject(const QString &text) const
{
    QJsonParseError jsonError;
    auto doc = QJsonDocument::fromJson(QByteArray(text.toUtf8().constData(), text.toUtf8().size()), &jsonError);
    if (QJsonParseError::NoError != jsonError.error) {
        qDebug("Json Parsing error: %s", jsonError.errorString().toLocal8Bit().constData());
        return QJsonObject();
    } else {
        auto object = doc.object();
        return object;
    }
}

// HeaderMessage

QByteArray InteractionProtocolCashControlService::HeaderMessage::toJsonString() const
{
    QJsonObject object;
    object.insert("Type", QJsonValue::fromVariant(static_cast<int>(mType)));
    object.insert("UidMessage", QJsonValue::fromVariant(mUidMessage.toString(QUuid::WithoutBraces)));
    return IJsonStringable::fromJsonObject(object);
}

void InteractionProtocolCashControlService::HeaderMessage::fromJsonString(const QString &text)
{
    auto object = IJsonStringable::toJsobObject(text);
    mType = static_cast<Type>(object.value("Type").toInt());
    mUidMessage = QUuid(object.value("UidMessage").toString());
}

// ReceiptMessage

QByteArray InteractionProtocolCashControlService::ReceiptMessage::toJsonString() const
{
    QJsonObject object;
    object.insert("Type", QJsonValue::fromVariant(static_cast<int>(mType)));
    object.insert("UidMessage", QJsonValue::fromVariant(mUidMessage.toString(QUuid::WithoutBraces)));
    object.insert("TypeMessage", QJsonValue::fromVariant( static_cast<int>(mTypeMessage) ));
    return IJsonStringable::fromJsonObject(object);
}

void InteractionProtocolCashControlService::ReceiptMessage::fromJsonString(const QString &text)
{
    auto object = IJsonStringable::toJsobObject(text, mType);
    mUidMessage = QUuid(object.value("UidMessage").toString());
    mTypeMessage = static_cast<Type>(object.value("TypeMessage").toInt());
}

// PingMessage

QByteArray InteractionProtocolCashControlService::PingMessage::toJsonString() const
{
    QJsonObject object;
    object.insert("Type", QJsonValue::fromVariant(static_cast<int>(mType)));
    object.insert("UidMessage", QJsonValue::fromVariant(mUidMessage.toString(QUuid::WithoutBraces)));
    return IJsonStringable::fromJsonObject(object);
}

void InteractionProtocolCashControlService::PingMessage::fromJsonString(const QString &text)
{
    auto object = IJsonStringable::toJsobObject(text, mType);
    mUidMessage = QUuid(object.value("UidMessage").toString());
}

// ConfigMessage

QByteArray InteractionProtocolCashControlService::ConfigMessage::toJsonString() const
{
    QJsonObject object;
    object.insert("Type", QJsonValue::fromVariant(static_cast<int>(mType)));
    object.insert("ConnString", QJsonValue::fromVariant(mConnString));
    object.insert("Language", QJsonValue::fromVariant(mLanguage));
    {
        auto subObject = QJsonObject();
        subObject.insert("CashCnt", QJsonValue::fromVariant(mLicense.mCashCnt));
        subObject.insert("RelayCnt", QJsonValue::fromVariant(mLicense.mRelayCnt));
        subObject.insert("CentralServer", QJsonValue::fromVariant( mLicense.mCentralServer? 1:0 ));
        subObject.insert("AccessCS", QJsonValue::fromVariant( mLicense.mAccessCS? 1:0 ));
        object.insert("License", subObject);
    }
    {
        auto subObject = QJsonObject();
        subObject.insert("ID", QJsonValue::fromVariant(mObjInfo.mID));
        subObject.insert("Name", QJsonValue::fromVariant(mObjInfo.mName));
        subObject.insert("Address", QJsonValue::fromVariant(mObjInfo.mAddress));

        /*
    "Distributor ": "Пятерочка",

    "Region ": "Московский",

    "Division ": "Северо-Запад",

    "Cluster ": "СЗО",

    "City ": "Москва"
        */

        subObject.insert("Distributor", QJsonValue::fromVariant(mObjInfo.mDistributor));
        subObject.insert("Region", QJsonValue::fromVariant(mObjInfo.mRegion));
        subObject.insert("Division", QJsonValue::fromVariant(mObjInfo.mDivision));
        subObject.insert("Cluster", QJsonValue::fromVariant(mObjInfo.mCluster));
        subObject.insert("City", QJsonValue::fromVariant(mObjInfo.mCity));
        object.insert("ObjInfo", subObject);
    }
    return IJsonStringable::fromJsonObject(object);
}

void InteractionProtocolCashControlService::ConfigMessage::fromJsonString(const QString &text)
{
    auto object = IJsonStringable::toJsobObject(text, mType);
    mConnString = object.value("ConnString").toString();
    mLanguage = object.value("Language").toString();
    {
        auto license = object.value("License").toObject();
        mLicense.mCashCnt = license.value("CashCnt").toInt();
        mLicense.mRelayCnt = license.value("RelayCnt").toInt();
        mLicense.mCentralServer = (license.value("CentralServer").toInt() == 0) ? false : true;
        mLicense.mAccessCS = (license.value("AccessCS").toInt() == 0) ? false : true;
    }
    {
        auto objInfo = object.value("ObjInfo").toObject();
        mObjInfo.mID = objInfo.value("ID").toString();
        mObjInfo.mName = objInfo.value("Name").toString();
        mObjInfo.mAddress = objInfo.value("Address").toString();

        mObjInfo.mDistributor = objInfo.value("Distributor").toString();
        mObjInfo.mRegion = objInfo.value("Region").toString();
        mObjInfo.mDivision = objInfo.value("Division").toString();
        mObjInfo.mCluster = objInfo.value("Cluster").toString();
        mObjInfo.mCity = objInfo.value("City").toString();
    }
}

// EventMessage

QByteArray InteractionProtocolCashControlService::EventMessage::toJsonString() const
{
    QJsonObject object;
    object.insert("Type", QJsonValue::fromVariant(static_cast<int>(mType)));
    object.insert("EventType", QJsonValue::fromVariant(static_cast<int>(mType)));
    object.insert("ID", QJsonValue::fromVariant(mID.toString(QUuid::WithoutBraces)));
    object.insert("Date", QJsonValue::fromVariant(mDate.toString(Qt::ISODate)));
    object.insert("UidCash", QJsonValue::fromVariant(mCashNo.toString(QUuid::WithoutBraces)));
    object.insert("Message", QJsonValue::fromVariant(mMessage));
    object.insert("ForeColor", QJsonValue::fromVariant(mForeColor.value()));
    object.insert("BackColor", QJsonValue::fromVariant(mBackColor.value()));
    return IJsonStringable::fromJsonObject(object);
}

void InteractionProtocolCashControlService::EventMessage::fromJsonString(const QString &text)
{
    auto object = IJsonStringable::toJsobObject(text, mType);
    mEventType = static_cast<EEventType>(object.value("EventType").toInt());
    mID = QUuid(object.value("ID").toString());
    mDate = QDateTime::fromString(object.value("Date").toString(), Qt::ISODate);
    mCashNo = QUuid(object.value("UidCash").toString());
    mMessage = object.value("Message").toString();
    mForeColor = QColor(object.value("ForeColor").toInt());
    mBackColor = QColor(object.value("BackColor").toInt());
}

// CassyFilterMessage

QByteArray InteractionProtocolCashControlService::CassyFilterMessage::toJsonString() const
{
    QJsonObject object;
    object.insert("Type", QJsonValue::fromVariant(static_cast<int>(mType)));
    object.insert("UidMessage", QJsonValue::fromVariant(mUidMessage.toString(QUuid::WithoutBraces)));
    object.insert("UidCash", QJsonValue::fromVariant(mUidCash.toString(QUuid::WithoutBraces)));
    object.insert("PermissionCashTransaction", QJsonValue::fromVariant(mPermissionCashTransaction));
    return IJsonStringable::fromJsonObject(object);
}

void InteractionProtocolCashControlService::CassyFilterMessage::fromJsonString(const QString &text)
{
    auto object = IJsonStringable::toJsobObject(text, mType);
    mUidMessage = QUuid(object.value("UidMessage").toString());
    mUidCash = QUuid(object.value("UidCash").toString());
    mPermissionCashTransaction = object.value("PermissionCashTransaction").toBool();
}

// CleanHandsEventMessage

QByteArray InteractionProtocolCashControlService::CleanHandsEventMessage::toJsonString() const
{
    QJsonObject object;
    object.insert("Type", QJsonValue::fromVariant(static_cast<int>(mType)));
    object.insert("UidMessage", QJsonValue::fromVariant(mUidMessage.toString(QUuid::WithoutBraces)));
    object.insert("Date", QJsonValue::fromVariant(mDate.toString(Qt::ISODateWithMs)));
    object.insert("CashNum", QJsonValue::fromVariant(static_cast<int>(mCashNum)));
    return IJsonStringable::fromJsonObject(object);
}

void InteractionProtocolCashControlService::CleanHandsEventMessage::fromJsonString(const QString &text)
{
    auto object = IJsonStringable::toJsobObject(text, mType);
    mUidMessage = QUuid(object.value("UidMessage").toString());
    mDate = QDateTime::fromString(object.value("Date").toString(), Qt::ISODateWithMs);
    mCashNum = object.value("CashNum").toInt();
}
