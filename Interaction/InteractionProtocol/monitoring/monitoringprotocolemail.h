#ifndef MONITORINGPROTOCOLEMAIL_H
#define MONITORINGPROTOCOLEMAIL_H

#include "monitoring/monitoringprotocol.h"
#include "monitoring/datatypes.h"

namespace MonitoringProtocol {
/// \remark email каналы

struct INTERACTION_PROTOCOL_API AddEmailChannelRequest : public LogicalMessage {
    AddEmailChannelRequest():LogicalMessage(){}
    AddEmailChannelRequest(const AddEmailChannelRequest &obj):LogicalMessage() { selfCopy(obj); }
    AddEmailChannelRequest &operator =(const AddEmailChannelRequest &obj) { if (this != &obj) { selfCopy(obj); } return *this; }
    virtual EMessageType type() const { return EMessageType::AddEmailChannelRequest; }
    virtual void serialize(QByteArray& payload) const;
    virtual void deserialize(const QByteArray& payload);

    EmailChannel mChannel;

private:
    inline void selfCopy(const AddEmailChannelRequest &obj) {
        mChannel = obj.mChannel;
    }
};

struct INTERACTION_PROTOCOL_API AddEmailChannelResponse : public LogicalMessage {
    AddEmailChannelResponse():LogicalMessage(){}
    AddEmailChannelResponse(const AddEmailChannelResponse &obj):LogicalMessage() { selfCopy(obj); }
    AddEmailChannelResponse &operator =(const AddEmailChannelResponse &obj) { if (this != &obj) { selfCopy(obj); } return *this; }
    virtual EMessageType type() const { return EMessageType::AddEmailChannelResponse; }
    virtual void serialize(QByteArray& payload) const;
    virtual void deserialize(const QByteArray& payload);

private:
    inline void selfCopy(const AddEmailChannelResponse &obj) {
    }
};

struct INTERACTION_PROTOCOL_API RemoveEmailChannelRequest : public LogicalMessage {
    RemoveEmailChannelRequest():LogicalMessage(){}
    RemoveEmailChannelRequest(const RemoveEmailChannelRequest &obj):LogicalMessage() { selfCopy(obj); }
    RemoveEmailChannelRequest &operator =(const RemoveEmailChannelRequest &obj) { if (this != &obj) { selfCopy(obj); } return *this; }
    virtual EMessageType type() const { return EMessageType::RemoveEmailChannelRequest; }
    virtual void serialize(QByteArray& payload) const;
    virtual void deserialize(const QByteArray& payload);

    QUuid mId;

private:
    inline void selfCopy(const RemoveEmailChannelRequest &obj) {
        mId = obj.mId;
    }
};

struct INTERACTION_PROTOCOL_API RemoveEmailChannelResponse : public LogicalMessage {
    RemoveEmailChannelResponse():LogicalMessage(){}
    RemoveEmailChannelResponse(const RemoveEmailChannelResponse &obj):LogicalMessage() { selfCopy(obj); }
    RemoveEmailChannelResponse &operator =(const RemoveEmailChannelResponse &obj) { if (this != &obj) { selfCopy(obj); } return *this; }
    virtual EMessageType type() const { return EMessageType::RemoveEmailChannelResponse; }
    virtual void serialize(QByteArray& payload) const;
    virtual void deserialize(const QByteArray& payload);

private:
    inline void selfCopy(const RemoveEmailChannelResponse &obj) {
    }
};

struct INTERACTION_PROTOCOL_API EditEmailChannelRequest : public LogicalMessage {
    EditEmailChannelRequest():LogicalMessage(){}
    EditEmailChannelRequest(const EditEmailChannelRequest &obj):LogicalMessage() { selfCopy(obj); }
    EditEmailChannelRequest &operator =(const EditEmailChannelRequest &obj) { if (this != &obj) { selfCopy(obj); } return *this; }
    virtual EMessageType type() const { return EMessageType::EditEmailChannelRequest; }
    virtual void serialize(QByteArray& payload) const;
    virtual void deserialize(const QByteArray& payload);

    QUuid mId;
    EmailChannel mChannel;

private:
    inline void selfCopy(const EditEmailChannelRequest &obj) {
        mId = obj.mId;
        mChannel = obj.mChannel;
    }
};

struct INTERACTION_PROTOCOL_API EditEmailChannelResponse : public LogicalMessage {
    EditEmailChannelResponse():LogicalMessage(){}
    EditEmailChannelResponse(const EditEmailChannelResponse &obj):LogicalMessage() { selfCopy(obj); }
    EditEmailChannelResponse &operator =(const EditEmailChannelResponse &obj) { if (this != &obj) { selfCopy(obj); } return *this; }
    virtual EMessageType type() const { return EMessageType::EditEmailChannelResponse; }
    virtual void serialize(QByteArray& payload) const;
    virtual void deserialize(const QByteArray& payload);

private:
    inline void selfCopy(const EditEmailChannelResponse &obj) {
    }
};

struct INTERACTION_PROTOCOL_API GetEmailChannelsRequest : public LogicalMessage {
    GetEmailChannelsRequest():LogicalMessage(){}
    GetEmailChannelsRequest(const GetEmailChannelsRequest &obj):LogicalMessage() { selfCopy(obj); }
    GetEmailChannelsRequest &operator =(const GetEmailChannelsRequest &obj) { if (this != &obj) { selfCopy(obj); } return *this; }
    virtual EMessageType type() const { return EMessageType::GetEmailChannelsRequest; }
    virtual void serialize(QByteArray& payload) const;
    virtual void deserialize(const QByteArray& payload);

private:
    inline void selfCopy(const GetEmailChannelsRequest &obj) {
    }
};

struct INTERACTION_PROTOCOL_API GetEmailChannelsResponse : public LogicalMessage {
    GetEmailChannelsResponse():LogicalMessage(){}
    GetEmailChannelsResponse(const GetEmailChannelsResponse &obj):LogicalMessage() { selfCopy(obj); }
    GetEmailChannelsResponse &operator =(const GetEmailChannelsResponse &obj) { if (this != &obj) { selfCopy(obj); } return *this; }
    virtual EMessageType type() const { return EMessageType::GetEmailChannelsResponse; }
    virtual void serialize(QByteArray& payload) const;
    virtual void deserialize(const QByteArray& payload);

    QMap<QUuid, EmailChannel> mEmailChannels;

private:
    inline void selfCopy(const GetEmailChannelsResponse &obj) {
        mEmailChannels = obj.mEmailChannels;
    }
};

}

#endif // MONITORINGPROTOCOLEMAIL_H
