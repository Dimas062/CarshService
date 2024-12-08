#ifndef MONITORINGPROTOCOLTELEGRAM_H
#define MONITORINGPROTOCOLTELEGRAM_H

#include "monitoring/monitoringprotocol.h"
#include "monitoring/datatypes.h"

namespace MonitoringProtocol {
    /// \remark телеграм каналы

struct INTERACTION_PROTOCOL_API AddTelegramChannelRequest : public LogicalMessage {
    AddTelegramChannelRequest():LogicalMessage(){}
    AddTelegramChannelRequest(const AddTelegramChannelRequest &obj):LogicalMessage() { selfCopy(obj); }
    AddTelegramChannelRequest &operator =(const AddTelegramChannelRequest &obj) { if (this != &obj) { selfCopy(obj); } return *this; }
    virtual EMessageType type() const { return EMessageType::AddTelegramChannelRequest; }
    virtual void serialize(QByteArray& payload) const;
    virtual void deserialize(const QByteArray& payload);

    TelegramChannel mChannel;

private:
    inline void selfCopy(const AddTelegramChannelRequest &obj) {
        mChannel = obj.mChannel;
    }
};

struct INTERACTION_PROTOCOL_API AddTelegramChannelResponse : public LogicalMessage {
    AddTelegramChannelResponse():LogicalMessage(){}
    AddTelegramChannelResponse(const AddTelegramChannelResponse &obj):LogicalMessage() { selfCopy(obj); }
    AddTelegramChannelResponse &operator =(const AddTelegramChannelResponse &obj) { if (this != &obj) { selfCopy(obj); } return *this; }
    virtual EMessageType type() const { return EMessageType::AddTelegramChannelResponse; }
    virtual void serialize(QByteArray& payload) const;
    virtual void deserialize(const QByteArray& payload);

private:
    inline void selfCopy(const AddTelegramChannelResponse &obj) {
    }
};

struct INTERACTION_PROTOCOL_API RemoveTelegramChannelRequest : public LogicalMessage {
    RemoveTelegramChannelRequest():LogicalMessage(){}
    RemoveTelegramChannelRequest(const RemoveTelegramChannelRequest &obj):LogicalMessage() { selfCopy(obj); }
    RemoveTelegramChannelRequest &operator =(const RemoveTelegramChannelRequest &obj) { if (this != &obj) { selfCopy(obj); } return *this; }
    virtual EMessageType type() const { return EMessageType::RemoveTelegramChannelRequest; }
    virtual void serialize(QByteArray& payload) const;
    virtual void deserialize(const QByteArray& payload);

    QUuid mId;

private:
    inline void selfCopy(const RemoveTelegramChannelRequest &obj) {
        mId = obj.mId;
    }
};

struct INTERACTION_PROTOCOL_API RemoveTelegramChannelResponse : public LogicalMessage {
    RemoveTelegramChannelResponse():LogicalMessage(){}
    RemoveTelegramChannelResponse(const RemoveTelegramChannelResponse &obj):LogicalMessage() { selfCopy(obj); }
    RemoveTelegramChannelResponse &operator =(const RemoveTelegramChannelResponse &obj) { if (this != &obj) { selfCopy(obj); } return *this; }
    virtual EMessageType type() const { return EMessageType::RemoveTelegramChannelResponse; }
    virtual void serialize(QByteArray& payload) const;
    virtual void deserialize(const QByteArray& payload);

private:
    inline void selfCopy(const RemoveTelegramChannelResponse &obj) {
    }
};

struct INTERACTION_PROTOCOL_API EditTelegramChannelRequest : public LogicalMessage {
    EditTelegramChannelRequest():LogicalMessage(){}
    EditTelegramChannelRequest(const EditTelegramChannelRequest &obj):LogicalMessage() { selfCopy(obj); }
    EditTelegramChannelRequest &operator =(const EditTelegramChannelRequest &obj) { if (this != &obj) { selfCopy(obj); } return *this; }
    virtual EMessageType type() const { return EMessageType::EditTelegramChannelRequest; }
    virtual void serialize(QByteArray& payload) const;
    virtual void deserialize(const QByteArray& payload);

    QUuid mId;
    TelegramChannel mChannel;

private:
    inline void selfCopy(const EditTelegramChannelRequest &obj) {
        mId = obj.mId;
        mChannel = obj.mChannel;
    }
};

struct INTERACTION_PROTOCOL_API EditTelegramChannelResponse : public LogicalMessage {
    EditTelegramChannelResponse():LogicalMessage(){}
    EditTelegramChannelResponse(const EditTelegramChannelResponse &obj):LogicalMessage() { selfCopy(obj); }
    EditTelegramChannelResponse &operator =(const EditTelegramChannelResponse &obj) { if (this != &obj) { selfCopy(obj); } return *this; }
    virtual EMessageType type() const { return EMessageType::EditTelegramChannelResponse; }
    virtual void serialize(QByteArray& payload) const;
    virtual void deserialize(const QByteArray& payload);

private:
    inline void selfCopy(const EditTelegramChannelResponse &obj) {
    }
};

struct INTERACTION_PROTOCOL_API GetTelegramChannelsRequest : public LogicalMessage {
    GetTelegramChannelsRequest():LogicalMessage(){}
    GetTelegramChannelsRequest(const GetTelegramChannelsRequest &obj):LogicalMessage() { selfCopy(obj); }
    GetTelegramChannelsRequest &operator =(const GetTelegramChannelsRequest &obj) { if (this != &obj) { selfCopy(obj); } return *this; }
    virtual EMessageType type() const { return EMessageType::GetTelegramChannelsRequest; }
    virtual void serialize(QByteArray& payload) const;
    virtual void deserialize(const QByteArray& payload);

private:
    inline void selfCopy(const GetTelegramChannelsRequest &obj) {
    }
};

struct INTERACTION_PROTOCOL_API GetTelegramChannelsResponse : public LogicalMessage {
    GetTelegramChannelsResponse():LogicalMessage(){}
    GetTelegramChannelsResponse(const GetTelegramChannelsResponse &obj):LogicalMessage() { selfCopy(obj); }
    GetTelegramChannelsResponse &operator =(const GetTelegramChannelsResponse &obj) { if (this != &obj) { selfCopy(obj); } return *this; }
    virtual EMessageType type() const { return EMessageType::GetTelegramChannelsResponse; }
    virtual void serialize(QByteArray& payload) const;
    virtual void deserialize(const QByteArray& payload);

    QMap<QUuid, TelegramChannel> mTelegramChannels;

private:
    inline void selfCopy(const GetTelegramChannelsResponse &obj) {
        mTelegramChannels = obj.mTelegramChannels;
    }
};

}

#endif // MONITORINGPROTOCOLTELEGRAM_H
