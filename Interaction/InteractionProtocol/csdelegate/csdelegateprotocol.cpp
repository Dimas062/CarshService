#include "csdelegateprotocol.h"
#include <QIODevice>

/// \remark ТРАНСПОРТНЫЙ УРОВЕНЬ

CsDelegateProtocol::Message::Message() : mLength(0)
{
}

CsDelegateProtocol::Message::Message(const Message &obj)
{
    selfCopy(obj);
}

CsDelegateProtocol::Message &CsDelegateProtocol::Message::operator =(const Message &obj)
{
    if (this != &obj) {
        selfCopy(obj);
    }
    return *this;
}

void CsDelegateProtocol::Message::deserialize(const QByteArray &raw)
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

void CsDelegateProtocol::Message::serialize(QByteArray &raw)
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

int CsDelegateProtocol::Message::length() const
{
    return mLength;
}

const QUuid &CsDelegateProtocol::Message::uid() const
{
    return mUid;
}

const QByteArray &CsDelegateProtocol::Message::payload() const
{
    return mPayload;
}

const CsDelegateProtocol::EMessageType &CsDelegateProtocol::Message::type() const
{
    return mType;
}

void CsDelegateProtocol::Message::registerMetatype()
{
    qRegisterMetaType<CsDelegateProtocol::Message>("CsDelegateProtocol::Message");
}

bool CsDelegateProtocol::Message::markBadVersionProtocol() const
{
    return mMarkBadVersionProtocol;
}

QUuid CsDelegateProtocol::Message::setPayload(const QByteArray &payload)
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

void CsDelegateProtocol::Message::setUid(const QUuid &uid)
{
    mUid = uid;
}

void CsDelegateProtocol::Message::selfCopy(const Message &obj)
{
    mLength = obj.mLength;
    mUid = obj.mUid;
    mPayload = obj.mPayload;
    mType = obj.mType;
}

CsDelegateProtocol::EMessageType CsDelegateProtocol::Message::getType(const QByteArray &payload)
{
    QDataStream rd(payload);
    int typeVal;
    rd >> typeVal;
    return static_cast<EMessageType>( typeVal );
}

/// \remark parser machine CsDelegateProtocol

QVector<CsDelegateProtocol::Message> CsDelegateProtocol::ParserMessageMachine::step(const QByteArray &data)
{
    QByteArray currentData;// текущие данные
    // учёт предыдущих данных (на предыдущем шаге)
    if (!mPrevData.isEmpty()) {
        currentData = mPrevData.append(data);
    } else {
        currentData = data;
    }
    QVector<CsDelegateProtocol::Message> messages; // список разобранных сообщений
    // Цикл разбора сообщения
    while(currentData.length() > 4) { // пока есть что обрабатывать
        int len = 0;
        {
            QDataStream rd(currentData);
            rd >> len;
        }
        auto curLenData = currentData.length();
        if (curLenData >= len) {
            CsDelegateProtocol::Message message;
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

void CsDelegateProtocol::ParserMessageMachine::reset()
{
    mPrevData.clear();
}

/// \remark ЛОГИЧЕСКИЙ УРОВЕНЬ

void CsDelegateProtocol::LogicalMessage::readQUuid(QDataStream &rd, QUuid &uid)
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

void CsDelegateProtocol::LogicalMessage::writeQUuid(QDataStream &wr, const QUuid &uid)
{
    auto _uid = uid.toRfc4122();
    int len = _uid.length();
    wr << len;
    wr.writeRawData(_uid.data(), len);
}

void CsDelegateProtocol::SendTelegramPhotoWithTextMessage::serialize(QByteArray &payload)
{
    QDataStream wr(&payload, QIODevice::WriteOnly);
    wr << static_cast<int>( type() );
    wr << mTokenBot;
    wr << mTokenChannel;
    wr << mImage;
    wr << mText;
}

void CsDelegateProtocol::SendTelegramPhotoWithTextMessage::deserialize(const QByteArray &payload)
{
    QDataStream rd(payload);
    int typeVal;
    rd >> typeVal;
    if (static_cast<EMessageType>( typeVal ) == type()) {
        rd >> mTokenBot;
        rd >> mTokenChannel;
        rd >> mImage;
        rd >> mText;
    } else {
        qDebug("CsDelegateProtocol::SendTelegramPhotoWithTextMessage::deserialize - bad type - %d", typeVal);
    }
}
