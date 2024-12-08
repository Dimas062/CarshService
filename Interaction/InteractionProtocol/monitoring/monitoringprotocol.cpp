#include "monitoringprotocol.h"
#include <QIODevice>
/// \remark ТРАНСПОРТНЫЙ УРОВЕНЬ

MonitoringProtocol::Message::Message() : mLength(0)
{
}

MonitoringProtocol::Message::Message(const Message &obj)
{
    selfCopy(obj);
}

MonitoringProtocol::Message &MonitoringProtocol::Message::operator =(const Message &obj)
{
    if (this != &obj) {
        selfCopy(obj);
    }
    return *this;
}

void MonitoringProtocol::Message::deserialize(const QByteArray &raw)
{
    QDataStream rd(raw);
    rd >> mLength;
    int version;
    rd >> version;
    if (version != cCurrentVersionProtocol) {
        mMarkBadVersionProtocol = true;
        return;
    }
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

void MonitoringProtocol::Message::serialize(QByteArray &raw) const
{
    QDataStream wr(&raw, QIODevice::WriteOnly);
    wr << mLength;
    wr << cCurrentVersionProtocol;
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

int MonitoringProtocol::Message::length() const
{
    return mLength;
}

const QUuid &MonitoringProtocol::Message::uid() const
{
    return mUid;
}

const QByteArray &MonitoringProtocol::Message::payload() const
{
    return mPayload;
}

const MonitoringProtocol::EMessageType &MonitoringProtocol::Message::type() const
{
    return mType;
}

void MonitoringProtocol::Message::registerMetatype()
{
    qRegisterMetaType<MonitoringProtocol::Message>("MonitoringProtocol::Message");
}

bool MonitoringProtocol::Message::markBadVersionProtocol() const
{
    return mMarkBadVersionProtocol;
}

QUuid MonitoringProtocol::Message::setPayload(const QByteArray &payload)
{
    mLength = 0;
    mLength += sizeof(mLength);
    mLength += sizeof(cCurrentVersionProtocol);
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

void MonitoringProtocol::Message::setUid(const QUuid &uid)
{
    mUid = uid;
}

void MonitoringProtocol::Message::selfCopy(const Message &obj)
{
    mLength = obj.mLength;
    mUid = obj.mUid;
    mPayload = obj.mPayload;
    mType = obj.mType;
}

MonitoringProtocol::EMessageType MonitoringProtocol::Message::getType(const QByteArray &payload)
{
    QDataStream rd(payload);
    int typeVal;
    rd >> typeVal;
    return static_cast<EMessageType>( typeVal );
}

/// \remark parser machine MonitoringProtocol

QVector<MonitoringProtocol::Message> MonitoringProtocol::ParserMessageMachine::step(const QByteArray &data)
{
    QByteArray currentData;// текущие данные
    // учёт предыдущих данных (на предыдущем шаге)
    if (!mPrevData.isEmpty()) {
        currentData = mPrevData.append(data);
    } else {
        currentData = data;
    }
    QVector<MonitoringProtocol::Message> messages; // список разобранных сообщений
    // Цикл разбора сообщения
    while(currentData.length() > 4) { // пока есть что обрабатывать
        int len = 0;
        {
            QDataStream rd(currentData);
            rd >> len;
        }
        auto curLenData = currentData.length();
//        qDebug("currentData.length() %d, len %d", curLenData, len);
        if (curLenData >= len) {
            MonitoringProtocol::Message message;
            auto rawMessage = currentData.left(len);
            message.deserialize(rawMessage);
            currentData = currentData.remove(0, len);
            if (!message.markBadVersionProtocol()) {
                messages.append(message);
            }
        } else {
            // ещё не накопилисиь данные
            break;
        }
    }
    mPrevData = currentData;
    return messages;
}

void MonitoringProtocol::ParserMessageMachine::reset()
{
    mPrevData.clear();
}

/// \remark ЛОГИЧЕСКИЙ УРОВЕНЬ

void MonitoringProtocol::LogicalMessage::readQUuid(QDataStream &rd, QUuid &uid)
{
    int len = 0;
    rd >> len;
    auto data = new char[len];
    rd.readRawData(data, len);
    QByteArray array = QByteArray::fromRawData(data, len);
    array.detach();
    uid = QUuid::fromRfc4122(array);
    delete [] data;
}

void MonitoringProtocol::LogicalMessage::writeQUuid(QDataStream &wr, const QUuid &uid) const
{
    auto _uid = uid.toRfc4122();
    int len = _uid.length();
    wr << len;
    wr.writeRawData(_uid.data(), len);
}

void MonitoringProtocol::HeartbeatServerMessage::serialize(QByteArray &payload) const
{
    QDataStream wr(&payload, QIODevice::WriteOnly);
    wr << static_cast<int>( type() );
    wr << mCode;
    wr << mName;
    wr << mName;
    wr << mOperationSystem;
    wr << mVersionSoftware;
    wr << mEndLicenseDt;
}

void MonitoringProtocol::HeartbeatServerMessage::deserialize(const QByteArray &payload)
{
    QDataStream rd(payload);
    int typeVal;
    rd >> typeVal;
    if (static_cast<EMessageType>( typeVal ) == type()) {
        rd >> mCode;
        rd >> mName;
        rd >> mAddress;
        rd >> mOperationSystem;
        rd >> mVersionSoftware;
        rd >> mEndLicenseDt;
    } else {
        qDebug("MonitoringProtocol::HeartbeatServerMessage::deserialize - bad type - %d", typeVal);
    }
}

void MonitoringProtocol::GetServerTableRequest::serialize(QByteArray &payload) const
{
    QDataStream wr(&payload, QIODevice::WriteOnly);
    wr << static_cast<int>( type() );
}

void MonitoringProtocol::GetServerTableRequest::deserialize(const QByteArray &payload)
{
    QDataStream rd(payload);
    int typeVal;
    rd >> typeVal;
    if (static_cast<EMessageType>( typeVal ) == type()) {
    } else {
        qDebug("MonitoringProtocol::GetServerTableRequest::deserialize - bad type - %d", typeVal);
    }
}

void MonitoringProtocol::GetServerTableRespone::serialize(QByteArray &payload) const
{
    QDataStream wr(&payload, QIODevice::WriteOnly);
    wr << static_cast<int>( type() );
    wr << mServerTable.count();
    for (auto it = mServerTable.begin(); it != mServerTable.end(); ++it) {
        writeQUuid(wr, it.key());
        wr << it.value().mCode;
        wr << it.value().mName;
        wr << it.value().mAddress;
        wr << it.value().mOnlineState;
        wr << it.value().mLastActiveDateTime;
        wr << it.value().mOperationSystem;
        wr << it.value().mVersionSoftware;
        wr << it.value().mEndLicenseDt;
    }
}

void MonitoringProtocol::GetServerTableRespone::deserialize(const QByteArray &payload)
{
    QDataStream rd(payload);
    int typeVal;
    rd >> typeVal;
    if (static_cast<EMessageType>( typeVal ) == type()) {
        mServerTable.clear();
        int count = 0;
        rd >> count;
        for (auto index=0; index<count; index++) {
            ServerTableItem item;
            QUuid uid;
            readQUuid(rd, uid);
            rd >> item.mCode;
            rd >> item.mName;
            rd >> item.mAddress;
            rd >> item.mOnlineState;
            rd >> item.mLastActiveDateTime;
            rd >> item.mOperationSystem;
            rd >> item.mVersionSoftware;
            rd >> item.mEndLicenseDt;
            mServerTable.insert(uid, item);
        }
    } else {
        qDebug("MonitoringProtocol::GetServerTableRespone::deserialize - bad type - %d", typeVal);
    }
}



void MonitoringProtocol::ChangeServerTableItemMessage::serialize(QByteArray &payload) const
{
    QDataStream wr(&payload, QIODevice::WriteOnly);
    wr << static_cast<int>( type() );
    writeQUuid(wr, mServerTableItemUid);
    wr << mCode;
    wr << mName;
    wr << mAddress;
    wr << mOnlineState;
    wr << mLastActiveDateTime;
    wr << mOperationSystem;
    wr << mVersionSoftware;
    wr << mEndLicenseDt;
}

void MonitoringProtocol::ChangeServerTableItemMessage::deserialize(const QByteArray &payload)
{
    QDataStream rd(payload);
    int typeVal;
    rd >> typeVal;
    if (static_cast<EMessageType>( typeVal ) == type()) {
        readQUuid(rd, mServerTableItemUid);
        rd >> mCode;
        rd >> mName;
        rd >> mAddress;
        rd >> mOnlineState;
        rd >> mLastActiveDateTime;
        rd >> mOperationSystem;
        rd >> mVersionSoftware;
        rd >> mEndLicenseDt;
    } else {
        qDebug("MonitoringProtocol::ChangeServerTableItemMessage::deserialize - bad type - %d", typeVal);
    }
}

void MonitoringProtocol::CheckClientConnectionRequest::serialize(QByteArray &payload) const
{
    QDataStream wr(&payload, QIODevice::WriteOnly);
    wr << static_cast<int>( type() );
}

void MonitoringProtocol::CheckClientConnectionRequest::deserialize(const QByteArray &payload)
{
    QDataStream rd(payload);
    int typeVal;
    rd >> typeVal;
    if (static_cast<EMessageType>( typeVal ) == type()) {
    } else {
        qDebug("MonitoringProtocol::CheckClientConnectionRequest::deserialize - bad type - %d", typeVal);
    }
}

void MonitoringProtocol::CheckClientConnectionResponse::serialize(QByteArray &payload) const
{
    QDataStream wr(&payload, QIODevice::WriteOnly);
    wr << static_cast<int>( type() );
}

void MonitoringProtocol::CheckClientConnectionResponse::deserialize(const QByteArray &payload)
{
    QDataStream rd(payload);
    int typeVal;
    rd >> typeVal;
    if (static_cast<EMessageType>( typeVal ) == type()) {
    } else {
        qDebug("MonitoringProtocol::CheckClientConnectionResponse::deserialize - bad type - %d", typeVal);
    }
}

/// \remark управление параметрами

/// \brief The GetStringParameterRequest struct получить параметр

void MonitoringProtocol::GetStringParameterRequest::serialize(QByteArray &payload) const
{
    QDataStream wr(&payload, QIODevice::WriteOnly);
    wr << static_cast<int>( type() );
    wr << static_cast<int>( mParameter );
}

void MonitoringProtocol::GetStringParameterRequest::deserialize(const QByteArray &payload)
{
    QDataStream rd(payload);
    int typeVal;
    rd >> typeVal;
    if (static_cast<EMessageType>( typeVal ) == type()) {
        int val;
        rd >> val;
        mParameter = static_cast<IStringParameter::EParameter>( val );
    } else {
        qDebug("MonitoringProtocol::GetStringParameterRequest::deserialize - bad type - %d", typeVal);
    }
}

/// \brief The GetStringParameterResponse struct получить параметр - ответ

void MonitoringProtocol::GetStringParameterResponse::serialize(QByteArray &payload) const
{
    QDataStream wr(&payload, QIODevice::WriteOnly);
    wr << static_cast<int>( type() );
    wr << static_cast<int>( mParameter );
    wr << mParameterValue;
}

void MonitoringProtocol::GetStringParameterResponse::deserialize(const QByteArray &payload)
{
    QDataStream rd(payload);
    int typeVal;
    rd >> typeVal;
    if (static_cast<EMessageType>( typeVal ) == type()) {
        int val;
        rd >> val;
        mParameter = static_cast<IStringParameter::EParameter>( val );
        rd >> mParameterValue;
    } else {
        qDebug("MonitoringProtocol::GetStringParameterResponse::deserialize - bad type - %d", typeVal);
    }
}

/// \brief The SetStringParameterRequest struct установить параметр - запрос

void MonitoringProtocol::SetStringParameterRequest::serialize(QByteArray &payload) const
{
    QDataStream wr(&payload, QIODevice::WriteOnly);
    wr << static_cast<int>( type() );
    wr << static_cast<int>( mParameter );
    wr << mParameterValue;
}

void MonitoringProtocol::SetStringParameterRequest::deserialize(const QByteArray &payload)
{
    QDataStream rd(payload);
    int typeVal;
    rd >> typeVal;
    if (static_cast<EMessageType>( typeVal ) == type()) {
        int val;
        rd >> val;
        mParameter = static_cast<IStringParameter::EParameter>( val );
        rd >> mParameterValue;
    } else {
        qDebug("MonitoringProtocol::SetStringParameterRequest::deserialize - bad type - %d", typeVal);
    }
}

/// \brief The SetStringParameterResponse struct установить параметр - ответ

void MonitoringProtocol::SetStringParameterResponse::serialize(QByteArray &payload) const
{
    QDataStream wr(&payload, QIODevice::WriteOnly);
    wr << static_cast<int>( type() );
    wr << static_cast<int>( mParameter );
}

void MonitoringProtocol::SetStringParameterResponse::deserialize(const QByteArray &payload)
{
    QDataStream rd(payload);
    int typeVal;
    rd >> typeVal;
    if (static_cast<EMessageType>( typeVal ) == type()) {
        int val;
        rd >> val;
        mParameter = static_cast<IStringParameter::EParameter>( val );
    } else {
        qDebug("MonitoringProtocol::SetStringParameterResponse::deserialize - bad type - %d", typeVal);
    }
}

/// \remark контролируемые объекты

void MonitoringProtocol::AddObjectRequest::serialize(QByteArray &payload) const
{
    QDataStream wr(&payload, QIODevice::WriteOnly);
    wr << static_cast<int>( type() );
    wr << mCode;
    wr << mName;
    wr << mAddress;
}

void MonitoringProtocol::AddObjectRequest::deserialize(const QByteArray &payload)
{
    QDataStream rd(payload);
    int typeVal;
    rd >> typeVal;
    if (static_cast<EMessageType>( typeVal ) == type()) {
        rd >> mCode;
        rd >> mName;
        rd >> mAddress;
    } else {
        qDebug("MonitoringProtocol::AddObjectRequest::deserialize - bad type - %d", typeVal);
    }
}

void MonitoringProtocol::AddObjectResponse::serialize(QByteArray &payload) const
{
    QDataStream wr(&payload, QIODevice::WriteOnly);
    wr << static_cast<int>( type() );
}

void MonitoringProtocol::AddObjectResponse::deserialize(const QByteArray &payload)
{
    QDataStream rd(payload);
    int typeVal;
    rd >> typeVal;
    if (static_cast<EMessageType>( typeVal ) == type()) {
    } else {
        qDebug("MonitoringProtocol::AddObjectResponse::deserialize - bad type - %d", typeVal);
    }
}

void MonitoringProtocol::RemoveObjectRequest::serialize(QByteArray &payload) const
{
    QDataStream wr(&payload, QIODevice::WriteOnly);
    wr << static_cast<int>( type() );
    wr << mId;
}

void MonitoringProtocol::RemoveObjectRequest::deserialize(const QByteArray &payload)
{
    QDataStream rd(payload);
    int typeVal;
    rd >> typeVal;
    if (static_cast<EMessageType>( typeVal ) == type()) {
        rd >> mId;
    } else {
        qDebug("MonitoringProtocol::RemoveObjectRequest::deserialize - bad type - %d", typeVal);
    }
}

void MonitoringProtocol::RemoveObjectResponse::serialize(QByteArray &payload) const
{
    QDataStream wr(&payload, QIODevice::WriteOnly);
    wr << static_cast<int>( type() );
}

void MonitoringProtocol::RemoveObjectResponse::deserialize(const QByteArray &payload)
{
    QDataStream rd(payload);
    int typeVal;
    rd >> typeVal;
    if (static_cast<EMessageType>( typeVal ) == type()) {
    } else {
        qDebug("MonitoringProtocol::RemoveObjectResponse::deserialize - bad type - %d", typeVal);
    }
}

void MonitoringProtocol::EditObjectRequest::serialize(QByteArray &payload) const
{
    QDataStream wr(&payload, QIODevice::WriteOnly);
    wr << static_cast<int>( type() );
    wr << mId;
    wr << mCode;
    wr << mName;
    wr << mAddress;
}

void MonitoringProtocol::EditObjectRequest::deserialize(const QByteArray &payload)
{
    QDataStream rd(payload);
    int typeVal;
    rd >> typeVal;
    if (static_cast<EMessageType>( typeVal ) == type()) {
        rd >> mId;
        rd >> mCode;
        rd >> mName;
        rd >> mAddress;
    } else {
        qDebug("MonitoringProtocol::EditObjectRequest::deserialize - bad type - %d", typeVal);
    }
}

void MonitoringProtocol::EditObjectResponse::serialize(QByteArray &payload) const
{
    QDataStream wr(&payload, QIODevice::WriteOnly);
    wr << static_cast<int>( type() );
}

void MonitoringProtocol::EditObjectResponse::deserialize(const QByteArray &payload)
{
    QDataStream rd(payload);
    int typeVal;
    rd >> typeVal;
    if (static_cast<EMessageType>( typeVal ) == type()) {
    } else {
        qDebug("MonitoringProtocol::EditObjectResponse::deserialize - bad type - %d", typeVal);
    }
}

void MonitoringProtocol::GetObjectsRequest::serialize(QByteArray &payload) const
{
    QDataStream wr(&payload, QIODevice::WriteOnly);
    wr << static_cast<int>( type() );
}

void MonitoringProtocol::GetObjectsRequest::deserialize(const QByteArray &payload)
{
    QDataStream rd(payload);
    int typeVal;
    rd >> typeVal;
    if (static_cast<EMessageType>( typeVal ) == type()) {
    } else {
        qDebug("MonitoringProtocol::GetObjectsRequest::deserialize - bad type - %d", typeVal);
    }
}

void MonitoringProtocol::GetObjectsResponse::serialize(QByteArray &payload) const
{
    QDataStream wr(&payload, QIODevice::WriteOnly);
    wr << static_cast<int>( type() );
    wr << mObjects.count();
    for (auto it = mObjects.begin(); it != mObjects.end(); ++it) {
        writeQUuid(wr, it.key());
        wr << it.value().mCode;
        wr << it.value().mName;
        wr << it.value().mAddress;
    }
}

void MonitoringProtocol::GetObjectsResponse::deserialize(const QByteArray &payload)
{
    QDataStream rd(payload);
    int typeVal;
    rd >> typeVal;
    if (static_cast<EMessageType>( typeVal ) == type()) {
        mObjects.clear();
        int count = 0;
        rd >> count;
        for (auto index=0; index<count; index++) {
            ObjectItem item;
            QUuid uid;
            readQUuid(rd, uid);
            rd >> item.mCode;
            rd >> item.mName;
            rd >> item.mAddress;
            mObjects.insert(uid, item);
        }
    } else {
        qDebug("MonitoringProtocol::GetObjectsResponse::deserialize - bad type - %d", typeVal);
    }
}

void MonitoringProtocol::NeedUpdateTableMessage::serialize(QByteArray &payload) const
{
    QDataStream wr(&payload, QIODevice::WriteOnly);
    wr << static_cast<int>( type() );
}

void MonitoringProtocol::NeedUpdateTableMessage::deserialize(const QByteArray &payload)
{
    QDataStream rd(payload);
    int typeVal;
    rd >> typeVal;
    if (static_cast<EMessageType>( typeVal ) == type()) {
    } else {
        qDebug("MonitoringProtocol::NeedUpdateTableMessage::deserialize - bad type - %d", typeVal);
    }
}
