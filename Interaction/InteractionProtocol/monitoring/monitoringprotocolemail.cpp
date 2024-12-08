#include "monitoringprotocolemail.h"
#include <QIODevice>

void MonitoringProtocol::AddEmailChannelRequest::serialize(QByteArray &payload) const
{
    QDataStream wr(&payload, QIODevice::WriteOnly);
    wr << static_cast<int>( type() );
    wr << mChannel;
}

void MonitoringProtocol::AddEmailChannelRequest::deserialize(const QByteArray &payload)
{
    QDataStream rd(payload);
    int typeVal;
    rd >> typeVal;
    if (static_cast<EMessageType>( typeVal ) == type()) {
        rd >> mChannel;
    } else {
        qDebug("MonitoringProtocol::AddEmailChannelRequest::deserialize - bad type - %d", typeVal);
    }
}

void MonitoringProtocol::AddEmailChannelResponse::serialize(QByteArray &payload) const
{
    QDataStream wr(&payload, QIODevice::WriteOnly);
    wr << static_cast<int>( type() );
}

void MonitoringProtocol::AddEmailChannelResponse::deserialize(const QByteArray &payload)
{
    QDataStream rd(payload);
    int typeVal;
    rd >> typeVal;
    if (static_cast<EMessageType>( typeVal ) == type()) {
    } else {
        qDebug("MonitoringProtocol::AddEmailChannelResponse::deserialize - bad type - %d", typeVal);
    }
}

void MonitoringProtocol::RemoveEmailChannelRequest::serialize(QByteArray &payload) const
{
    QDataStream wr(&payload, QIODevice::WriteOnly);
    wr << static_cast<int>( type() );
    wr << mId;
}

void MonitoringProtocol::RemoveEmailChannelRequest::deserialize(const QByteArray &payload)
{
    QDataStream rd(payload);
    int typeVal;
    rd >> typeVal;
    if (static_cast<EMessageType>( typeVal ) == type()) {
        rd >> mId;
    } else {
        qDebug("MonitoringProtocol::RemoveEmailChannelRequest::deserialize - bad type - %d", typeVal);
    }
}

void MonitoringProtocol::RemoveEmailChannelResponse::serialize(QByteArray &payload) const
{
    QDataStream wr(&payload, QIODevice::WriteOnly);
    wr << static_cast<int>( type() );
}

void MonitoringProtocol::RemoveEmailChannelResponse::deserialize(const QByteArray &payload)
{
    QDataStream rd(payload);
    int typeVal;
    rd >> typeVal;
    if (static_cast<EMessageType>( typeVal ) == type()) {
    } else {
        qDebug("MonitoringProtocol::RemoveEmailChannelResponse::deserialize - bad type - %d", typeVal);
    }
}

void MonitoringProtocol::EditEmailChannelRequest::serialize(QByteArray &payload) const
{
    QDataStream wr(&payload, QIODevice::WriteOnly);
    wr << static_cast<int>( type() );
    wr << mId;
    wr << mChannel;
}

void MonitoringProtocol::EditEmailChannelRequest::deserialize(const QByteArray &payload)
{
    QDataStream rd(payload);
    int typeVal;
    rd >> typeVal;
    if (static_cast<EMessageType>( typeVal ) == type()) {
        rd >> mId;
        rd >> mChannel;
    } else {
        qDebug("MonitoringProtocol::EditEmailChannelRequest::deserialize - bad type - %d", typeVal);
    }
}

void MonitoringProtocol::EditEmailChannelResponse::serialize(QByteArray &payload) const
{
    QDataStream wr(&payload, QIODevice::WriteOnly);
    wr << static_cast<int>( type() );
}

void MonitoringProtocol::EditEmailChannelResponse::deserialize(const QByteArray &payload)
{
    QDataStream rd(payload);
    int typeVal;
    rd >> typeVal;
    if (static_cast<EMessageType>( typeVal ) == type()) {
    } else {
        qDebug("MonitoringProtocol::EditEmailChannelResponse::deserialize - bad type - %d", typeVal);
    }
}

void MonitoringProtocol::GetEmailChannelsRequest::serialize(QByteArray &payload) const
{
    QDataStream wr(&payload, QIODevice::WriteOnly);
    wr << static_cast<int>( type() );
}

void MonitoringProtocol::GetEmailChannelsRequest::deserialize(const QByteArray &payload)
{
    QDataStream rd(payload);
    int typeVal;
    rd >> typeVal;
    if (static_cast<EMessageType>( typeVal ) == type()) {
    } else {
        qDebug("MonitoringProtocol::GetEmailChannelsRequest::deserialize - bad type - %d", typeVal);
    }
}

void MonitoringProtocol::GetEmailChannelsResponse::serialize(QByteArray &payload) const
{
    QDataStream wr(&payload, QIODevice::WriteOnly);
    wr << static_cast<int>( type() );
    wr << mEmailChannels.count();
    for (auto it = mEmailChannels.begin(); it != mEmailChannels.end(); ++it) {
        writeQUuid(wr, it.key());
        wr << it.value();
    }
}

void MonitoringProtocol::GetEmailChannelsResponse::deserialize(const QByteArray &payload)
{
    QDataStream rd(payload);
    int typeVal;
    rd >> typeVal;
    if (static_cast<EMessageType>( typeVal ) == type()) {
        mEmailChannels.clear();
        int count = 0;
        rd >> count;
        for (auto index=0; index<count; index++) {
            EmailChannel item;
            QUuid uid;
            readQUuid(rd, uid);
            rd >> item;
            mEmailChannels.insert(uid, item);
        }
    } else {
        qDebug("MonitoringProtocol::GetEmailChannelsResponse::deserialize - bad type - %d", typeVal);
    }
}
