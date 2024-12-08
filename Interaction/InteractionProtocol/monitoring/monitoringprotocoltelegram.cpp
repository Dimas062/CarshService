#include "monitoringprotocoltelegram.h"
#include <QIODevice>

void MonitoringProtocol::AddTelegramChannelRequest::serialize(QByteArray &payload) const
{
    QDataStream wr(&payload, QIODevice::WriteOnly);
    wr << static_cast<int>( type() );
    wr << mChannel;
}

void MonitoringProtocol::AddTelegramChannelRequest::deserialize(const QByteArray &payload)
{
    QDataStream rd(payload);
    int typeVal;
    rd >> typeVal;
    if (static_cast<EMessageType>( typeVal ) == type()) {
        rd >> mChannel;
    } else {
        qDebug("MonitoringProtocol::AddTelegramChannelRequest::deserialize - bad type - %d", typeVal);
    }
}

void MonitoringProtocol::AddTelegramChannelResponse::serialize(QByteArray &payload) const
{
    QDataStream wr(&payload, QIODevice::WriteOnly);
    wr << static_cast<int>( type() );
}

void MonitoringProtocol::AddTelegramChannelResponse::deserialize(const QByteArray &payload)
{
    QDataStream rd(payload);
    int typeVal;
    rd >> typeVal;
    if (static_cast<EMessageType>( typeVal ) == type()) {
    } else {
        qDebug("MonitoringProtocol::AddTelegramChannelResponse::deserialize - bad type - %d", typeVal);
    }
}

void MonitoringProtocol::RemoveTelegramChannelRequest::serialize(QByteArray &payload) const
{
    QDataStream wr(&payload, QIODevice::WriteOnly);
    wr << static_cast<int>( type() );
    wr << mId;
}

void MonitoringProtocol::RemoveTelegramChannelRequest::deserialize(const QByteArray &payload)
{
    QDataStream rd(payload);
    int typeVal;
    rd >> typeVal;
    if (static_cast<EMessageType>( typeVal ) == type()) {
        rd >> mId;
    } else {
        qDebug("MonitoringProtocol::RemoveTelegramChannelRequest::deserialize - bad type - %d", typeVal);
    }
}

void MonitoringProtocol::RemoveTelegramChannelResponse::serialize(QByteArray &payload) const
{
    QDataStream wr(&payload, QIODevice::WriteOnly);
    wr << static_cast<int>( type() );
}

void MonitoringProtocol::RemoveTelegramChannelResponse::deserialize(const QByteArray &payload)
{
    QDataStream rd(payload);
    int typeVal;
    rd >> typeVal;
    if (static_cast<EMessageType>( typeVal ) == type()) {
    } else {
        qDebug("MonitoringProtocol::RemoveTelegramChannelResponse::deserialize - bad type - %d", typeVal);
    }
}

void MonitoringProtocol::EditTelegramChannelRequest::serialize(QByteArray &payload) const
{
    QDataStream wr(&payload, QIODevice::WriteOnly);
    wr << static_cast<int>( type() );
    wr << mId;
    wr << mChannel;
}

void MonitoringProtocol::EditTelegramChannelRequest::deserialize(const QByteArray &payload)
{
    QDataStream rd(payload);
    int typeVal;
    rd >> typeVal;
    if (static_cast<EMessageType>( typeVal ) == type()) {
        rd >> mId;
        rd >> mChannel;
    } else {
        qDebug("MonitoringProtocol::EditTelegramChannelRequest::deserialize - bad type - %d", typeVal);
    }
}

void MonitoringProtocol::EditTelegramChannelResponse::serialize(QByteArray &payload) const
{
    QDataStream wr(&payload, QIODevice::WriteOnly);
    wr << static_cast<int>( type() );
}

void MonitoringProtocol::EditTelegramChannelResponse::deserialize(const QByteArray &payload)
{
    QDataStream rd(payload);
    int typeVal;
    rd >> typeVal;
    if (static_cast<EMessageType>( typeVal ) == type()) {
    } else {
        qDebug("MonitoringProtocol::EditTelegramChannelResponse::deserialize - bad type - %d", typeVal);
    }
}

void MonitoringProtocol::GetTelegramChannelsRequest::serialize(QByteArray &payload) const
{
    QDataStream wr(&payload, QIODevice::WriteOnly);
    wr << static_cast<int>( type() );
}

void MonitoringProtocol::GetTelegramChannelsRequest::deserialize(const QByteArray &payload)
{
    QDataStream rd(payload);
    int typeVal;
    rd >> typeVal;
    if (static_cast<EMessageType>( typeVal ) == type()) {
    } else {
        qDebug("MonitoringProtocol::GetTelegramChannelsRequest::deserialize - bad type - %d", typeVal);
    }
}

void MonitoringProtocol::GetTelegramChannelsResponse::serialize(QByteArray &payload) const
{
    QDataStream wr(&payload, QIODevice::WriteOnly);
    wr << static_cast<int>( type() );
    wr << mTelegramChannels.count();
    for (auto it = mTelegramChannels.begin(); it != mTelegramChannels.end(); ++it) {
        writeQUuid(wr, it.key());
        wr << it.value();
    }
}

void MonitoringProtocol::GetTelegramChannelsResponse::deserialize(const QByteArray &payload)
{
    QDataStream rd(payload);
    int typeVal;
    rd >> typeVal;
    if (static_cast<EMessageType>( typeVal ) == type()) {
        mTelegramChannels.clear();
        int count = 0;
        rd >> count;
        for (auto index=0; index<count; index++) {
            TelegramChannel item;
            QUuid uid;
            readQUuid(rd, uid);
            rd >> item;
            mTelegramChannels.insert(uid, item);
        }
    } else {
        qDebug("MonitoringProtocol::GetTelegramChannelsResponse::deserialize - bad type - %d", typeVal);
    }
}
