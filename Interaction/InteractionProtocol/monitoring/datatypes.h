#ifndef DATATYPES_H
#define DATATYPES_H

#include <QObject>
#include <QList>
#include <QUuid>
#include <QDataStream>
#include "interactionprotocollib.h"

/// \remark ТГ-каналы

/*
        if (!query.exec("CREATE TABLE telegram_channels "
                        "( "
                        "id guid primary key, "
                        "name text, "
                        "token_bot text, "
                        "token_channel text, "
                        "server_list blob "
                        ") ")) {
            qDebug() << query.lastError().text();
        }
*/

typedef QList<QUuid> UidList;
QDataStream INTERACTION_PROTOCOL_API &operator<<(QDataStream & out, const UidList & value);
QDataStream INTERACTION_PROTOCOL_API &operator>>(QDataStream & in, UidList & value);

struct INTERACTION_PROTOCOL_API TelegramChannel {
    QString mName;
    QString mTokenBot;
    QString mTokenChannel;
    UidList mServerUids;
};
QDataStream INTERACTION_PROTOCOL_API &operator<<(QDataStream & out, const TelegramChannel & value);
QDataStream INTERACTION_PROTOCOL_API &operator>>(QDataStream & in, TelegramChannel & value);


///< Email-каналы

/*
        if (!query.exec("CREATE TABLE email_channels "
                        "( "
                        "id guid primary key, "
                        "name text, "
                        "email_server_url text, "
                        "email_server_port integer, "
                        "email_server_login text, "
                        "email_server_password text, "
                        "server_list blob, "
                        "email_list blob "
                        ") ")) {
            qDebug() << query.lastError().text();
        }
*/

typedef QList<QString> EmailList;
QDataStream INTERACTION_PROTOCOL_API &operator<<(QDataStream & out, const EmailList & value);
QDataStream INTERACTION_PROTOCOL_API &operator>>(QDataStream & in, EmailList & value);

struct INTERACTION_PROTOCOL_API EmailChannel {
    QString mName;
    QString mEmailServerUrl;
    int mEmailServerPort;
    QString mEmailServerLogin;
    QString mEmailServerPassword;
    UidList mServerUids;
    EmailList mEmailList;
};
QDataStream INTERACTION_PROTOCOL_API &operator<<(QDataStream & out, const EmailChannel & value);
QDataStream INTERACTION_PROTOCOL_API &operator>>(QDataStream & in, EmailChannel & value);


#endif // DATATYPES_H
