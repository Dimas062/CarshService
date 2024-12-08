#include "datatypes.h"

/// \remark ТГ-каналы

QDataStream &operator<<(QDataStream & out, const UidList & value) {
    int count = value.count();
    out << count;
    for (const auto& item : value) {
        out << item;
    }
    return out;
}

QDataStream &operator>>(QDataStream & in, UidList & value) {
    value.clear();
    int count = 0;
    in >> count;
    for (auto index=0; index<count; index++) {
        QUuid item;
        in >> item;
        value.append(item);
    }
    return in;
}

QDataStream INTERACTION_PROTOCOL_API &operator<<(QDataStream & out, const TelegramChannel & value) {
    out << value.mName;
    out << value.mTokenBot;
    out << value.mTokenChannel;
    out << value.mServerUids;
    return out;
}

QDataStream INTERACTION_PROTOCOL_API &operator>>(QDataStream & in, TelegramChannel & value) {
    in >> value.mName;
    in >> value.mTokenBot;
    in >> value.mTokenChannel;
    in >> value.mServerUids;
    return in;
}

///< Email-каналы

QDataStream &operator<<(QDataStream & out, const EmailList & value) {
    int count = value.count();
    out << count;
    for (const auto& item : value) {
        out << item;
    }
    return out;
}

QDataStream &operator>>(QDataStream & in, EmailList & value) {
    value.clear();
    int count = 0;
    in >> count;
    for (auto index=0; index<count; index++) {
        QString item;
        in >> item;
        value.append(item);
    }
    return in;
}

QDataStream INTERACTION_PROTOCOL_API &operator<<(QDataStream & out, const EmailChannel & value) {
    out << value.mName;
    out << value.mEmailServerUrl;
    out << value.mEmailServerPort;
    out << value.mEmailServerLogin;
    out << value.mEmailServerPassword;
    out << value.mServerUids;
    out << value.mEmailList;
    return out;
}

QDataStream INTERACTION_PROTOCOL_API &operator>>(QDataStream & in, EmailChannel & value) {
    in >> value.mName;
    in >> value.mEmailServerUrl;
    in >> value.mEmailServerPort;
    in >> value.mEmailServerLogin;
    in >> value.mEmailServerPassword;
    in >> value.mServerUids;
    in >> value.mEmailList;
    return in;
}
