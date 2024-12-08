#include "interactionprotocol.h"
#include "servicemacros.h"
#include <QDataStream>
#include <QHostAddress>

#include <QBinaryJson>

// ------------------------------------------------
// ----- NetworkMessage
// ------------------------------------------------

NetworkMessage::NetworkMessage(): mType(EDataType::None)
{

}

NetworkMessage::NetworkMessage(EDataType type, const QByteArray &data) :
    mType(type)

{
    mData =  data ;
}

NetworkMessage::NetworkMessage(const NetworkMessage &obj)
{
    selfCopy(obj);
}

NetworkMessage &NetworkMessage::operator =(const NetworkMessage &obj)
{
    OPERATOR_EQUAL_BODY;
}

bool NetworkMessage::isValid() const
{
    if ((mType != EDataType::None) && (!mData.isEmpty()))
        return true;
    else
        return false;
}

void NetworkMessage::setJsonData(const QJsonObject &json)
{
    if (json.isEmpty())
        return;
    if ( !json.contains(TYPE_TAG)
         )
        return;
    mType = static_cast<EDataType>( json.value(TYPE_TAG).toString().toUInt() );
    //mData = QJsonDocument(json).toBinaryData();//.toBase64();
   //mData = QJsonDocument(json).toBase64();
    mData = QBinaryJson::toBinaryData(QJsonDocument(json));

}

QByteArray NetworkMessage::serialize()
{
    QByteArray raw;
    QDataStream stream(&raw, QIODevice::WriteOnly);
    stream << cSyncroSequence;
    stream << static_cast<quint32>(mType);
    stream << static_cast<quint32>(mData.length());
    stream.writeRawData(mData.constData(), mData.length());
    return raw;
}

EDataType NetworkMessage::type() const
{
    return mType;
}

QUuid NetworkMessage::uidRequest() const
{
    auto json = getJsonData();
    return QUuid(json.value(UID_REQUEST_TAG).toString());
}

QJsonObject NetworkMessage::getJsonData() const
{
    //auto jsonDoc = QJsonDocument::fromBinaryData( mData );
    //auto jsonDoc = QJsonDocument::fromBase64( mData );

    auto jsonDoc = QBinaryJson::fromBinaryData(mData);
    return jsonDoc.object();

}

void NetworkMessage::selfCopy(const NetworkMessage &obj)
{
    mType = obj.mType;
    mData = obj.mData;
}

// ------------------------------------------------
// ----- ResponseBadRequest
// ------------------------------------------------

ResponseBadRequest::ResponseBadRequest():IJsonable(), ICommonFields(), IResponseResultable(),
    mRequestType(EDataType::None)
{
}

ResponseBadRequest::ResponseBadRequest(EDataType requestType) : IJsonable(), ICommonFields(), IResponseResultable(),
    mRequestType(requestType)
{
}

ResponseBadRequest::ResponseBadRequest(const ResponseBadRequest &obj) : IJsonable(), ICommonFields(), IResponseResultable()
{
    selfCopy(obj);
}

ResponseBadRequest &ResponseBadRequest::operator =(const ResponseBadRequest &obj)
{
    OPERATOR_EQUAL_BODY;
}

ResponseBadRequest::ResponseBadRequest(const QJsonObject &json)
{
    if ( !IJsonable::typeFromJsonObject(json) ||
         !IResponseResultable::resultResponseFromJsonObject(json)
            )
        return;
    if ( !json.contains("mRequestType")
         )
        return;
    ICommonFields::fromJsonObject(json);
    JSON_TO_ENUM(json, EDataType, mRequestType);
}

void ResponseBadRequest::selfCopy(const ResponseBadRequest &obj)
{
    mUidRequest = obj.mUidRequest;
    mRequestType = obj.mRequestType;
    mResponseResult = obj.mResponseResult;
}

EDataType ResponseBadRequest::type() const
{
    return EDataType::ResponseBadRequest;
}

QJsonObject ResponseBadRequest::toJsonObject() const
{
    QJsonObject object;
    ICommonFields::toJsonObject(object);
    IJsonable::typeToJsonObject(object);
    IResponseResultable::resultResponseToJsonObject(object);
    ENUM_TO_JSON(mRequestType, object);
    return object;
}

bool ResponseBadRequest::isValid() const
{
    if ((mRequestType == EDataType::None) ||
            (mResponseResult == EResult::None)
            )
        return false;
    else
        return true;
}


// ------------------------------------------------
// ----- RequestAuthorization
// ------------------------------------------------

RequestAuthorization::RequestAuthorization(): IJsonable(), ICommonFields(), mLogin(""), mPassword(""), mMACAddress(""), mServerIpConnectTo()
{

}

RequestAuthorization::RequestAuthorization(const QString &login, const QString &password, const QString &MAC, const QString &serverIpConnectTo):IJsonable(), ICommonFields(),
    mLogin(login), mPassword(password), mMACAddress(MAC), mServerIpConnectTo(serverIpConnectTo)
{

}

RequestAuthorization::RequestAuthorization(const RequestAuthorization &obj):IJsonable(), ICommonFields()
{
    selfCopy(obj);
}

RequestAuthorization &RequestAuthorization::operator =(const RequestAuthorization &obj)
{
    OPERATOR_EQUAL_BODY;
}

RequestAuthorization::RequestAuthorization(const QJsonObject &json)
{
    if (!IJsonable::typeFromJsonObject(json))
        return;
    if ( !json.contains("mLogin") ||
         !json.contains("mPassword") ||
         !json.contains("mMACAddress") ||
         !json.contains("mServerIpConnectTo")||
         !json.contains("mClientType")
         )
        return;
    ICommonFields::fromJsonObject(json);
    JSON_TO_QSTRING(json, mLogin);
    JSON_TO_QSTRING(json, mPassword);
    JSON_TO_QSTRING(json, mMACAddress);
    JSON_TO_QSTRING(json, mServerIpConnectTo);
    JSON_TO_ENUM(json, EClientType, mClientType);
}

bool RequestAuthorization::isValid() const
{
    if (!mLogin.isEmpty())
        return true;
    else
        return false;
}

EDataType RequestAuthorization::type() const { return EDataType::RequestAuthorization; }

QJsonObject RequestAuthorization::toJsonObject() const
{
    QJsonObject object;
    ICommonFields::toJsonObject(object);
    IJsonable::typeToJsonObject(object);
    QSTRING_TO_JSON(mLogin, object);
    QSTRING_TO_JSON(mPassword, object);
    QSTRING_TO_JSON(mMACAddress, object);
    QSTRING_TO_JSON(mServerIpConnectTo, object);
    ENUM_TO_JSON(mClientType, object);
    return object;
}

void RequestAuthorization::selfCopy(const RequestAuthorization &obj)
{
    mUidRequest = obj.mUidRequest;
    mLogin = obj.mLogin;
    mPassword = obj.mPassword;
    mMACAddress = obj.mMACAddress;
    mServerIpConnectTo = obj.mServerIpConnectTo;
    mClientType = obj.mClientType;
}

// ------------------------------------------------
// ----- ResponseAuthorization
// ------------------------------------------------

ResponseAuthorization::ResponseAuthorization(const ResponseAuthorization &obj): IJsonable(), ICommonFields(), IResponseResultable()
{
    selfCopy(obj);
}

ResponseAuthorization &ResponseAuthorization::operator =(const ResponseAuthorization &obj)
{
    OPERATOR_EQUAL_BODY;
}

ResponseAuthorization::ResponseAuthorization(const QJsonObject &json)
{
    if ( !IJsonable::typeFromJsonObject(json) ||
         !IResponseResultable::resultResponseFromJsonObject(json)
            )
        return;
    if ( !json.contains("mUid") ||
         !json.contains("mUidUserFromDb") ||

         !json.contains("mRole") ||
         !json.contains("mConnectionName") ||
         !json.contains("mDbName") ||
         !json.contains("mHostIp") ||
         !json.contains("mHostPort") ||
         !json.contains("mUser") ||
         !json.contains("mPassword") ||
         !json.contains("mFtpLogin") ||
         !json.contains("mFtpPassword") ||
         !json.contains("mFtpPort") ||
         !json.contains("mFtpVirtualPath") ||
         !json.contains("mServerCategory") ||
//         !json.contains("mServerUuid") ||
         !json.contains("mNotificationPort") ||

         !json.contains("mCashDatabaseIp") ||
         !json.contains("mCashDatabasePort") ||
         !json.contains("mCashDatabaseName") ||
         !json.contains("mCashDatabaseLogin") ||
         !json.contains("mCashDatabasePassword") ||

         !json.contains("mCashTransactionDatabaseIp") ||
         !json.contains("mCashTransactionDatabasePort") ||
         !json.contains("mCashTransactionDatabaseName") ||
         !json.contains("mCashTransactionDatabaseLogin") ||
         !json.contains("mCashTransactionDatabasePassword") ||

         !json.contains("mCentralFacesDatabaseIp") ||
         !json.contains("mCentralFacesDatabasePort") ||
         !json.contains("mCentralFacesDatabaseName") ||
         !json.contains("mCentralFacesDatabaseLogin") ||
         !json.contains("mCentralFacesDatabasePassword") ||

         !json.contains("mFacesDatabaseIp") ||
         !json.contains("mFacesDatabasePort") ||
         !json.contains("mFacesDatabaseName") ||
         !json.contains("mFacesDatabaseLogin") ||
         !json.contains("mFacesDatabasePassword")
         )
        return;
    ICommonFields::fromJsonObject(json);
    JSON_TO_QUUID(json, mUid);
    JSON_TO_QUUID(json, mUidUserFromDb);

    JSON_TO_ENUM(json, EUserRole, mRole);
    JSON_TO_QSTRING(json, mConnectionName);
    JSON_TO_QSTRING(json, mDbName);
    JSON_TO_QSTRING(json, mHostIp);
    JSON_TO_INT(json, mHostPort);
    JSON_TO_QSTRING(json, mUser);
    JSON_TO_QSTRING(json, mPassword);
    JSON_TO_QSTRING(json, mFtpLogin);
    JSON_TO_QSTRING(json, mFtpPassword);
    JSON_TO_INT(json, mFtpPort);
    JSON_TO_QSTRING(json, mFtpVirtualPath);
    JSON_TO_ENUM(json, ServerCategory, mServerCategory);
//    JSON_TO_QUUID(json, mServerUuid);
    JSON_TO_INT(json, mNotificationPort);

    JSON_TO_QSTRING(json, mCashDatabaseIp);
    JSON_TO_INT(json, mCashDatabasePort);
    JSON_TO_QSTRING(json, mCashDatabaseName);
    JSON_TO_QSTRING(json, mCashDatabaseLogin);
    JSON_TO_QSTRING(json, mCashDatabasePassword);

    JSON_TO_QSTRING(json, mCashTransactionDatabaseIp);
    JSON_TO_INT(json, mCashTransactionDatabasePort);
    JSON_TO_QSTRING(json, mCashTransactionDatabaseName);
    JSON_TO_QSTRING(json, mCashTransactionDatabaseLogin);
    JSON_TO_QSTRING(json, mCashTransactionDatabasePassword);

    JSON_TO_QSTRING(json, mCentralFacesDatabaseIp);
    JSON_TO_INT(json,     mCentralFacesDatabasePort);
    JSON_TO_QSTRING(json, mCentralFacesDatabaseName);
    JSON_TO_QSTRING(json, mCentralFacesDatabaseLogin);
    JSON_TO_QSTRING(json, mCentralFacesDatabasePassword);

    JSON_TO_QSTRING(json, mFacesDatabaseIp);
    JSON_TO_INT(json,     mFacesDatabasePort);
    JSON_TO_QSTRING(json, mFacesDatabaseName);
    JSON_TO_QSTRING(json, mFacesDatabaseLogin);
    JSON_TO_QSTRING(json, mFacesDatabasePassword);

    JSON_TO_INT(json,     mMainDefaultPort);
    JSON_TO_QSTRING(json, mMainDefaultLogin);
    JSON_TO_QSTRING(json, mMainDefaultPassword);
    JSON_TO_INT(json,     mMainDefaultDbPort);
    JSON_TO_QSTRING(json, mMainDefaultDbName);
    JSON_TO_QSTRING(json, mMainDefaultDbUser);
    JSON_TO_QSTRING(json, mMainDefaultDbPassword);
}

bool ResponseAuthorization::isValid() const
{
    if (!mUid.isNull() && (mRole != EUserRole::None))
        return true;
    else
        return false;
}

EDataType ResponseAuthorization::type() const { return EDataType::ResponseAuthorization; }

QJsonObject ResponseAuthorization::toJsonObject() const
{
    QJsonObject object;
    ICommonFields::toJsonObject(object);
    IJsonable::typeToJsonObject(object);
    IResponseResultable::resultResponseToJsonObject(object);
    QUUID_TO_JSON(mUid, object);
    QUUID_TO_JSON(mUidUserFromDb, object);
    ENUM_TO_JSON(mRole, object);
    QSTRING_TO_JSON(mConnectionName, object);
    QSTRING_TO_JSON(mDbName, object);
    QSTRING_TO_JSON(mHostIp, object);
    INT_TO_JSON(mHostPort, object);
    QSTRING_TO_JSON(mUser, object);
    QSTRING_TO_JSON(mPassword, object);
    QSTRING_TO_JSON(mFtpLogin, object);
    QSTRING_TO_JSON(mFtpPassword, object);
    INT_TO_JSON(mFtpPort, object);
    QSTRING_TO_JSON(mFtpVirtualPath, object);
    ENUM_TO_JSON(mServerCategory, object);
//    QUUID_TO_JSON(mServerUuid, object);
    INT_TO_JSON(mNotificationPort, object);

    QSTRING_TO_JSON(mCashDatabaseIp, object);
    INT_TO_JSON(mCashDatabasePort, object);
    QSTRING_TO_JSON(mCashDatabaseName, object);
    QSTRING_TO_JSON(mCashDatabaseLogin, object);
    QSTRING_TO_JSON(mCashDatabasePassword, object);

    QSTRING_TO_JSON(mCashTransactionDatabaseIp, object);
    INT_TO_JSON(mCashTransactionDatabasePort, object);
    QSTRING_TO_JSON(mCashTransactionDatabaseName, object);
    QSTRING_TO_JSON(mCashTransactionDatabaseLogin, object);
    QSTRING_TO_JSON(mCashTransactionDatabasePassword, object);

    QSTRING_TO_JSON(mCentralFacesDatabaseIp, object);
    INT_TO_JSON(mCentralFacesDatabasePort, object);
    QSTRING_TO_JSON(mCentralFacesDatabaseName, object);
    QSTRING_TO_JSON(mCentralFacesDatabaseLogin, object);
    QSTRING_TO_JSON(mCentralFacesDatabasePassword, object);

    QSTRING_TO_JSON(mFacesDatabaseIp, object);
    INT_TO_JSON    (mFacesDatabasePort, object);
    QSTRING_TO_JSON(mFacesDatabaseName, object);
    QSTRING_TO_JSON(mFacesDatabaseLogin, object);
    QSTRING_TO_JSON(mFacesDatabasePassword, object);

    INT_TO_JSON(     mMainDefaultPort, object);
    QSTRING_TO_JSON( mMainDefaultLogin, object);
    QSTRING_TO_JSON( mMainDefaultPassword, object);
    INT_TO_JSON(     mMainDefaultDbPort, object);
    QSTRING_TO_JSON( mMainDefaultDbName, object);
    QSTRING_TO_JSON( mMainDefaultDbUser, object);
    QSTRING_TO_JSON( mMainDefaultDbPassword, object);
    return object;
}

void ResponseAuthorization::selfCopy(const ResponseAuthorization &obj)
{
    mUidRequest = obj.mUidRequest;

    mUid = obj.mUid;
    mUidUserFromDb = obj.mUidUserFromDb;

    mRole = obj.mRole;
    mConnectionName = obj.mConnectionName;
    mDbName = obj.mDbName;
    mHostIp = obj.mHostIp;
    mHostPort = obj.mHostPort;
    mUser = obj.mUser;
    mPassword = obj.mPassword;
    mResponseResult = obj.mResponseResult;
    mFtpLogin = obj.mFtpLogin;
    mFtpPassword = obj.mFtpPassword;
    mFtpPort = obj.mFtpPort;
    mFtpVirtualPath = obj.mFtpVirtualPath;
    mServerCategory = obj.mServerCategory;
//    mServerUuid = obj.mServerUuid;
    mNotificationPort = obj.mNotificationPort;

    mCashDatabaseIp = obj.mCashDatabaseIp;
    mCashDatabasePort = obj.mCashDatabasePort;
    mCashDatabaseName = obj.mCashDatabaseName;
    mCashDatabaseLogin = obj.mCashDatabaseLogin;
    mCashDatabasePassword = obj.mCashDatabasePassword;

    mCashTransactionDatabaseIp = obj.mCashTransactionDatabaseIp;
    mCashTransactionDatabasePort = obj.mCashTransactionDatabasePort;
    mCashTransactionDatabaseName = obj.mCashTransactionDatabaseName;
    mCashTransactionDatabaseLogin = obj.mCashTransactionDatabaseLogin;
    mCashTransactionDatabasePassword = obj.mCashTransactionDatabasePassword;

    mCentralFacesDatabaseIp         = obj.mCentralFacesDatabaseIp;
    mCentralFacesDatabasePort       = obj.mCentralFacesDatabasePort;
    mCentralFacesDatabaseName       = obj.mCentralFacesDatabaseName;
    mCentralFacesDatabaseLogin      = obj.mCentralFacesDatabaseLogin;
    mCentralFacesDatabasePassword   = obj.mCentralFacesDatabasePassword;

    mFacesDatabaseIp         = obj.mFacesDatabaseIp;
    mFacesDatabasePort       = obj.mFacesDatabasePort;
    mFacesDatabaseName       = obj.mFacesDatabaseName;
    mFacesDatabaseLogin      = obj.mFacesDatabaseLogin;
    mFacesDatabasePassword   = obj.mFacesDatabasePassword;

    mMainDefaultPort         = obj.mMainDefaultPort;
    mMainDefaultLogin       = obj.mMainDefaultLogin;
    mMainDefaultPassword       = obj.mMainDefaultPassword;
    mMainDefaultDbPort      = obj.mMainDefaultDbPort;
    mMainDefaultDbName   = obj.mMainDefaultDbName;
    mMainDefaultDbUser      = obj.mMainDefaultDbUser;
    mMainDefaultDbPassword   = obj.mMainDefaultDbPassword;
}

// ------------------------------------------------
// ----- RequestDirectoryContent
// ------------------------------------------------

RequestDirectoryContent::RequestDirectoryContent(): IJsonable(), ICommonFields()
{

}

RequestDirectoryContent::RequestDirectoryContent(const RequestDirectoryContent &obj):IJsonable(), ICommonFields()
{
    selfCopy(obj);
}

RequestDirectoryContent &RequestDirectoryContent::operator =(const RequestDirectoryContent &obj)
{
    OPERATOR_EQUAL_BODY;
}

RequestDirectoryContent::RequestDirectoryContent(const QJsonObject &json)
{
    if (!IJsonable::typeFromJsonObject(json))
        return;
    if ( !json.contains("mTypeDirRequest") ||
         !json.contains("mFullNameDirectory")
         )
        return;
    ICommonFields::fromJsonObject(json);
    JSON_TO_ENUM(json, ETypeDirRequest, mTypeDirRequest);
    JSON_TO_QSTRING(json, mFullNameDirectory);
}

bool RequestDirectoryContent::isValid() const
{
    return true;
}

EDataType RequestDirectoryContent::type() const { return EDataType::RequestDirectoryContent; }

QJsonObject RequestDirectoryContent::toJsonObject() const
{
    QJsonObject object;
    ICommonFields::toJsonObject(object);
    IJsonable::typeToJsonObject(object);
    ENUM_TO_JSON(mTypeDirRequest, object);
    QSTRING_TO_JSON(mFullNameDirectory, object);
    return object;
}

void RequestDirectoryContent::selfCopy(const RequestDirectoryContent &obj)
{
    mUidRequest = obj.mUidRequest;
    mTypeDirRequest = obj.mTypeDirRequest;
    mFullNameDirectory = obj.mFullNameDirectory;
}

ResponseDirectoryContent::ResponseDirectoryContent():IJsonable(), ICommonFields(), IResponseResultable()
{

}

ResponseDirectoryContent::ResponseDirectoryContent(const ResponseDirectoryContent &obj):IJsonable(), ICommonFields(), IResponseResultable()
{
    selfCopy(obj);
}

ResponseDirectoryContent &ResponseDirectoryContent::operator =(const ResponseDirectoryContent &obj)
{
    OPERATOR_EQUAL_BODY;
}

ResponseDirectoryContent::ResponseDirectoryContent(const QJsonObject &json)
{
    if ( !IJsonable::typeFromJsonObject(json) ||
         !IResponseResultable::resultResponseFromJsonObject(json)
            )
        return;
    if ( !json.contains("mFullNameDirectory")
         )
        return;
    ICommonFields::fromJsonObject(json);
    JSON_TO_QSTRING(json, mFullNameDirectory);
    if (json.contains("mDirectoryContent_0") && json.contains("mDirectoryContent_1")) {
        mDirectoryContent.clear();
        auto json_variable_0 = json.value("mDirectoryContent_0");
        auto json_variable_1 = json.value("mDirectoryContent_1");
        if (json_variable_0.isArray() && json_variable_1.isArray()) {
            auto json_array_0 = json_variable_0.toArray();
            auto json_array_1 = json_variable_1.toArray();
            if (!json_array_0.isEmpty() && !json_array_1.isEmpty()) {
                for (auto index=0; index<json_array_0.count(); index++) {
                    auto val_0 = static_cast<ETypeItem>(json_array_0[index].toInt());
                    auto val_1 = json_array_1[index].toString();
                    mDirectoryContent.append(std::make_tuple(val_0, val_1));
                }
            }
        }
    }
}

void ResponseDirectoryContent::selfCopy(const ResponseDirectoryContent &obj)
{
    mUidRequest = obj.mUidRequest;
    mResponseResult = obj.mResponseResult;
    mFullNameDirectory = obj.mFullNameDirectory;
    mDirectoryContent = obj.mDirectoryContent;
}

EDataType ResponseDirectoryContent::type() const
{
    return EDataType::ResponseDirectoryContent;
}

QJsonObject ResponseDirectoryContent::toJsonObject() const
{
    QJsonObject object;
    ICommonFields::toJsonObject(object);
    IJsonable::typeToJsonObject(object);
    IResponseResultable::resultResponseToJsonObject(object);
    QSTRING_TO_JSON(mFullNameDirectory, object);
    if (!mDirectoryContent.isEmpty()) {
        QJsonArray json_variable_0;
        QJsonArray json_variable_1;
        for(const std::tuple<ETypeItem, QString>& item : mDirectoryContent) {
            json_variable_0.append(QJsonValue(static_cast<int>(std::get<0>(item))));
            json_variable_1.append(QJsonValue(std::get<1>(item)));
        }
        object.insert("mDirectoryContent_0", json_variable_0);
        object.insert("mDirectoryContent_1", json_variable_1);
    }
    return object;
}

bool ResponseDirectoryContent::isValid() const
{
    if (mResponseResult == EResult::None)
        return false;
    else
        return true;
}

// ------------------------------------------------
// ----- RequestUpdateVirtualPath
// ------------------------------------------------

RequestUpdateVirtualPath::RequestUpdateVirtualPath(): IJsonable(), ICommonFields()
{

}

RequestUpdateVirtualPath::RequestUpdateVirtualPath(const RequestUpdateVirtualPath &obj):IJsonable(), ICommonFields()
{
    selfCopy(obj);
}

RequestUpdateVirtualPath &RequestUpdateVirtualPath::operator =(const RequestUpdateVirtualPath &obj)
{
    OPERATOR_EQUAL_BODY;
}

RequestUpdateVirtualPath::RequestUpdateVirtualPath(const QJsonObject &json)
{
    if (!IJsonable::typeFromJsonObject(json))
        return;
    ICommonFields::fromJsonObject(json);
}

bool RequestUpdateVirtualPath::isValid() const
{
    return true;
}

EDataType RequestUpdateVirtualPath::type() const { return EDataType::RequestUpdateVirtualPath; }

QJsonObject RequestUpdateVirtualPath::toJsonObject() const
{
    QJsonObject object;
    ICommonFields::toJsonObject(object);
    IJsonable::typeToJsonObject(object);
    return object;
}

void RequestUpdateVirtualPath::selfCopy(const RequestUpdateVirtualPath &obj)
{
    mUidRequest = obj.mUidRequest;
}

ResponseUpdateVirtualPath::ResponseUpdateVirtualPath():IJsonable(), ICommonFields(), IResponseResultable()
{

}

ResponseUpdateVirtualPath::ResponseUpdateVirtualPath(const ResponseUpdateVirtualPath &obj):IJsonable(), ICommonFields(), IResponseResultable()
{
    selfCopy(obj);
}

ResponseUpdateVirtualPath &ResponseUpdateVirtualPath::operator =(const ResponseUpdateVirtualPath &obj)
{
    OPERATOR_EQUAL_BODY;
}

ResponseUpdateVirtualPath::ResponseUpdateVirtualPath(const QJsonObject &json)
{
    if ( !IJsonable::typeFromJsonObject(json) ||
         !IResponseResultable::resultResponseFromJsonObject(json)
            )
        return;
    ICommonFields::fromJsonObject(json);
}

void ResponseUpdateVirtualPath::selfCopy(const ResponseUpdateVirtualPath &obj)
{
    mUidRequest = obj.mUidRequest;
    mResponseResult = obj.mResponseResult;
}

EDataType ResponseUpdateVirtualPath::type() const
{
    return EDataType::ResponseUpdateVirtualPath;
}

QJsonObject ResponseUpdateVirtualPath::toJsonObject() const
{
    QJsonObject object;
    ICommonFields::toJsonObject(object);
    IJsonable::typeToJsonObject(object);
    IResponseResultable::resultResponseToJsonObject(object);
    return object;
}

bool ResponseUpdateVirtualPath::isValid() const
{
    if (mResponseResult == EResult::None)
        return false;
    else
        return true;
}

/****************************/

RequestSetStreamsUrls::RequestSetStreamsUrls(): IJsonable(), ICommonFields()
{

}

RequestSetStreamsUrls::RequestSetStreamsUrls(const RequestSetStreamsUrls &obj):IJsonable(), ICommonFields()
{
    selfCopy(obj);
}

RequestSetStreamsUrls &RequestSetStreamsUrls::operator =(const RequestSetStreamsUrls &obj)
{
    OPERATOR_EQUAL_BODY;
}

RequestSetStreamsUrls::RequestSetStreamsUrls(const QJsonObject &json)
{
    if (!IJsonable::typeFromJsonObject(json))
        return;
    ICommonFields::fromJsonObject(json);
    QJsonArray keys = json.value("mStreamUrlMap_keys").toArray();
    QJsonArray values = json.value("mStreamUrlMap_values").toArray();
    mStreamUrlMap.clear();
    for(auto i=0; i<keys.count(); i++) {
        mStreamUrlMap.insert(
                    QUuid(keys[i].toString()),
                    values[i].toString()
                    );
    }
    JSON_TO_BOOL(json, mResetStreams);
}

bool RequestSetStreamsUrls::isValid() const
{
    return true;
}

EDataType RequestSetStreamsUrls::type() const { return EDataType::RequestSetStreamsUrls; }

QJsonObject RequestSetStreamsUrls::toJsonObject() const
{
    QJsonObject object;
    ICommonFields::toJsonObject(object);
    IJsonable::typeToJsonObject(object);
    QJsonArray keys;
    QJsonArray values;
    foreach (QUuid key, mStreamUrlMap.keys()) {
        keys.append(QJsonValue(key.toString(QUuid::WithoutBraces)));
        values.append(QJsonValue(mStreamUrlMap[key]));
    }
    object.insert("mStreamUrlMap_keys", keys);
    object.insert("mStreamUrlMap_values", values);
    BOOL_TO_JSON(mResetStreams, object);
    return object;
}

void RequestSetStreamsUrls::selfCopy(const RequestSetStreamsUrls &obj)
{
    mUidRequest = obj.mUidRequest;
    mStreamUrlMap = obj.mStreamUrlMap;
    mResetStreams = obj.mResetStreams;
}

/***********************************/

ResponseSetStreamsUrls::ResponseSetStreamsUrls():IJsonable(), ICommonFields(), IResponseResultable()
{

}

ResponseSetStreamsUrls::ResponseSetStreamsUrls(const ResponseSetStreamsUrls &obj):IJsonable(), ICommonFields(), IResponseResultable()
{
    selfCopy(obj);
}

ResponseSetStreamsUrls &ResponseSetStreamsUrls::operator =(const ResponseSetStreamsUrls &obj)
{
    OPERATOR_EQUAL_BODY;
}

ResponseSetStreamsUrls::ResponseSetStreamsUrls(const QJsonObject &json)
{
    if ( !IJsonable::typeFromJsonObject(json) ||
         !IResponseResultable::resultResponseFromJsonObject(json)
            )
        return;
    ICommonFields::fromJsonObject(json);
}

void ResponseSetStreamsUrls::selfCopy(const ResponseSetStreamsUrls &obj)
{
    mUidRequest = obj.mUidRequest;
    mResponseResult = obj.mResponseResult;
}

EDataType ResponseSetStreamsUrls::type() const
{
    return EDataType::ResponseSetStreamsUrls;
}

QJsonObject ResponseSetStreamsUrls::toJsonObject() const
{
    QJsonObject object;
    ICommonFields::toJsonObject(object);
    IJsonable::typeToJsonObject(object);
    IResponseResultable::resultResponseToJsonObject(object);
    return object;
}

bool ResponseSetStreamsUrls::isValid() const
{
    if (mResponseResult == EResult::None)
        return false;
    else
        return true;
}

// ------------------------------------------------
// ----- RequestListAvailableCameras
// ------------------------------------------------

RequestListAvailableCameras::RequestListAvailableCameras():IJsonable(), ICommonFields()
{

}

RequestListAvailableCameras::RequestListAvailableCameras(const RequestListAvailableCameras &obj):IJsonable(), ICommonFields()
{
    selfCopy(obj);
}

RequestListAvailableCameras &RequestListAvailableCameras::operator =(const RequestListAvailableCameras &obj)
{
    OPERATOR_EQUAL_BODY;
}

RequestListAvailableCameras::RequestListAvailableCameras(const QJsonObject &json)
{
    if ( !IJsonable::typeFromJsonObject(json)
            )
        return;
    ICommonFields::fromJsonObject(json);
}

void RequestListAvailableCameras::selfCopy(const RequestListAvailableCameras &obj)
{
    mUidRequest = obj.mUidRequest;
}

EDataType RequestListAvailableCameras::type() const
{
  return EDataType::RequestListAvailableCameras;
}

QJsonObject RequestListAvailableCameras::toJsonObject() const
{
    QJsonObject object;
    ICommonFields::toJsonObject(object);
    IJsonable::typeToJsonObject(object);
    return object;
}

bool RequestListAvailableCameras::isValid() const
{
    return true;
}

// ------------------------------------------------
// ----- ResponseListAvailableCameras
// ------------------------------------------------

ResponseListAvailableCameras::ResponseListAvailableCameras():IJsonable(), ICommonFields(), IResponseResultable()
{

}

ResponseListAvailableCameras::ResponseListAvailableCameras(const ResponseListAvailableCameras &obj):IJsonable(), ICommonFields(), IResponseResultable()
{
    selfCopy(obj);
}

ResponseListAvailableCameras &ResponseListAvailableCameras::operator =(const ResponseListAvailableCameras &obj)
{
    OPERATOR_EQUAL_BODY;
}

ResponseListAvailableCameras::ResponseListAvailableCameras(const QJsonObject &json)
{
    if ( !IJsonable::typeFromJsonObject(json) ||
         !IResponseResultable::resultResponseFromJsonObject(json)
            )
        return;
    ICommonFields::fromJsonObject(json);
    JSON_TO_QVECTOR_STRUCT(json, AvailableCameraProperties, mCameras);
}

void ResponseListAvailableCameras::selfCopy(const ResponseListAvailableCameras &obj)
{
    mUidRequest = obj.mUidRequest;
    mResponseResult = obj.mResponseResult;
    mCameras.clear();
    mCameras = obj.mCameras;
}

EDataType ResponseListAvailableCameras::type() const
{
    return EDataType::ResponseListAvailableCameras;
}

QJsonObject ResponseListAvailableCameras::toJsonObject() const
{
    QJsonObject object;
    ICommonFields::toJsonObject(object);
    IJsonable::typeToJsonObject(object);
    IResponseResultable::resultResponseToJsonObject(object);
    QVECTOR_STRUCT_TO_JSON(mCameras, AvailableCameraProperties, object);
    return object;
}

bool ResponseListAvailableCameras::isValid() const
{
    if (mResponseResult == EResult::None)
        return false;
    else
        return true;
}

// ------------------------------------------------
// ----- RequestUpdate
// ------------------------------------------------

RequestUpdate::RequestUpdate():IJsonable(), ICommonFields()
{

}

RequestUpdate::RequestUpdate(const RequestUpdate &obj):IJsonable(), ICommonFields()
{
    selfCopy(obj);
}

RequestUpdate &RequestUpdate::operator =(const RequestUpdate &obj)
{
    OPERATOR_EQUAL_BODY;
}

RequestUpdate::RequestUpdate(const QJsonObject &json)
{
    if ( !IJsonable::typeFromJsonObject(json)
            )
        return;
    ICommonFields::fromJsonObject(json);
}

void RequestUpdate::selfCopy(const RequestUpdate &obj)
{
    mUidRequest = obj.mUidRequest;
}

EDataType RequestUpdate::type() const
{
  return EDataType::RequestUpdate;
}

QJsonObject RequestUpdate::toJsonObject() const
{
    QJsonObject object;
    ICommonFields::toJsonObject(object);
    IJsonable::typeToJsonObject(object);
    return object;
}

bool RequestUpdate::isValid() const
{
    return true;
}

// ------------------------------------------------
// ----- ResponseUpdate
// ------------------------------------------------

ResponseUpdate::ResponseUpdate():IJsonable(), ICommonFields(), IResponseResultable()
{

}

ResponseUpdate::ResponseUpdate(const ResponseUpdate &obj):IJsonable(), ICommonFields(), IResponseResultable()
{
    selfCopy(obj);
}

ResponseUpdate &ResponseUpdate::operator =(const ResponseUpdate &obj)
{
    OPERATOR_EQUAL_BODY;
}

ResponseUpdate::ResponseUpdate(const QJsonObject &json)
{
    if ( !IJsonable::typeFromJsonObject(json) ||
         !IResponseResultable::resultResponseFromJsonObject(json)
            )
        return;
    ICommonFields::fromJsonObject(json);
}

void ResponseUpdate::selfCopy(const ResponseUpdate &obj)
{
    mUidRequest = obj.mUidRequest;
    mResponseResult = obj.mResponseResult;
}

EDataType ResponseUpdate::type() const
{
    return EDataType::ResponseUpdate;
}

QJsonObject ResponseUpdate::toJsonObject() const
{
    QJsonObject object;
    ICommonFields::toJsonObject(object);
    IJsonable::typeToJsonObject(object);
    IResponseResultable::resultResponseToJsonObject(object);
    return object;
}

bool ResponseUpdate::isValid() const
{
    if (mResponseResult == EResult::None)
        return false;
    else
        return true;
}

// ------------------------------------------------
// ----- RequestFaceUpdate
// ------------------------------------------------

RequestFaceUpdate::RequestFaceUpdate():IJsonable(), ICommonFields()
{

}

RequestFaceUpdate::RequestFaceUpdate(const RequestFaceUpdate &obj):IJsonable(), ICommonFields()
{
    selfCopy(obj);
}

RequestFaceUpdate &RequestFaceUpdate::operator =(const RequestFaceUpdate &obj)
{
    OPERATOR_EQUAL_BODY;
}

RequestFaceUpdate::RequestFaceUpdate(const QJsonObject &json)
{
    if ( !IJsonable::typeFromJsonObject(json)
            )
        return;
    ICommonFields::fromJsonObject(json);
}

void RequestFaceUpdate::selfCopy(const RequestFaceUpdate &obj)
{
    mUidRequest = obj.mUidRequest;
}

EDataType RequestFaceUpdate::type() const
{
  return EDataType::RequestFaceUpdate;
}

QJsonObject RequestFaceUpdate::toJsonObject() const
{
    QJsonObject object;
    ICommonFields::toJsonObject(object);
    IJsonable::typeToJsonObject(object);
    return object;
}

bool RequestFaceUpdate::isValid() const
{
    return true;
}


// ------------------------------------------------
// ----- ResponseFaceUpdate
// ------------------------------------------------

ResponseFaceUpdate::ResponseFaceUpdate():IJsonable(), ICommonFields(), IResponseResultable()
{

}

ResponseFaceUpdate::ResponseFaceUpdate(const ResponseFaceUpdate &obj):IJsonable(), ICommonFields(), IResponseResultable()
{
    selfCopy(obj);
}

ResponseFaceUpdate &ResponseFaceUpdate::operator =(const ResponseFaceUpdate &obj)
{
    OPERATOR_EQUAL_BODY;
}

ResponseFaceUpdate::ResponseFaceUpdate(const QJsonObject &json)
{
    if ( !IJsonable::typeFromJsonObject(json) ||
         !IResponseResultable::resultResponseFromJsonObject(json)
            )
        return;
    ICommonFields::fromJsonObject(json);
}

void ResponseFaceUpdate::selfCopy(const ResponseFaceUpdate &obj)
{
    mUidRequest = obj.mUidRequest;
    mResponseResult = obj.mResponseResult;
}

EDataType ResponseFaceUpdate::type() const
{
    return EDataType::ResponseFaceUpdate;
}

QJsonObject ResponseFaceUpdate::toJsonObject() const
{
    QJsonObject object;
    ICommonFields::toJsonObject(object);
    IJsonable::typeToJsonObject(object);
    IResponseResultable::resultResponseToJsonObject(object);
    return object;
}

bool ResponseFaceUpdate::isValid() const
{
    if (mResponseResult == EResult::None)
        return false;
    else
        return true;
}


// ------------------------------------------------
// ----- RequestStartRtspStreamCamera
// ------------------------------------------------

RequestStartRtspStreamCamera::RequestStartRtspStreamCamera():IJsonable(), ICommonFields(),
    mStreamUid(QUuid()), mRtspStreamUid(QUuid()), mCameraUid(QUuid()), mCassyUid(QUuid())
{

}

RequestStartRtspStreamCamera::RequestStartRtspStreamCamera(const QUuid& streamUid, const QUuid &rtspStreamUid, const QUuid& cameraUid, const QUuid &cassyUid):IJsonable(), ICommonFields(),
    mStreamUid(streamUid), mRtspStreamUid(rtspStreamUid), mCameraUid(cameraUid), mCassyUid(cassyUid)
{

}

RequestStartRtspStreamCamera::RequestStartRtspStreamCamera(const RequestStartRtspStreamCamera &obj):IJsonable(), ICommonFields()
{
    selfCopy(obj);
}

RequestStartRtspStreamCamera &RequestStartRtspStreamCamera::operator =(const RequestStartRtspStreamCamera &obj)
{
    OPERATOR_EQUAL_BODY;
}

RequestStartRtspStreamCamera::RequestStartRtspStreamCamera(const QJsonObject &json)
{
    if ( !IJsonable::typeFromJsonObject(json)
            )
        return;
    if ( !json.contains("mStreamUid") ||
         !json.contains("mRtspStreamUid") ||
         !json.contains("mCameraUid") ||
         !json.contains("mCassyUid")
         )
        return;
    ICommonFields::fromJsonObject(json);
    JSON_TO_QUUID(json, mStreamUid);
    JSON_TO_QUUID(json, mRtspStreamUid);
    JSON_TO_QUUID(json, mCameraUid);
    JSON_TO_QUUID(json, mCassyUid);
}

void RequestStartRtspStreamCamera::selfCopy(const RequestStartRtspStreamCamera &obj)
{
    mUidRequest = obj.mUidRequest;
    mStreamUid = obj.mStreamUid;
    mRtspStreamUid = obj.mRtspStreamUid;
    mCameraUid = obj.mCameraUid;
    mCassyUid = obj.mCassyUid;
}

EDataType RequestStartRtspStreamCamera::type() const
{
    return EDataType::RequestStartRtspStreamCamera;
}

QJsonObject RequestStartRtspStreamCamera::toJsonObject() const
{
    QJsonObject object;
    ICommonFields::toJsonObject(object);
    IJsonable::typeToJsonObject(object);
    QUUID_TO_JSON(mStreamUid, object);
    QUUID_TO_JSON(mRtspStreamUid, object);
    QUUID_TO_JSON(mCameraUid, object);
    QUUID_TO_JSON(mCassyUid, object);
    return object;
}

bool RequestStartRtspStreamCamera::isValid() const
{
    if (mStreamUid.isNull() || mRtspStreamUid.isNull())
        return false;
    else
        return true;
}

// ------------------------------------------------
// ----- ResponseStartRtspStreamCamera
// ------------------------------------------------

ResponseStartRtspStreamCamera::ResponseStartRtspStreamCamera():IJsonable(), ICommonFields(), IResponseResultable(),
    mRtspUrl("")
{

}

ResponseStartRtspStreamCamera::ResponseStartRtspStreamCamera(const QString &rtspUrl):IJsonable(), ICommonFields(),IResponseResultable(),
    mRtspUrl(rtspUrl)
{

}

ResponseStartRtspStreamCamera::ResponseStartRtspStreamCamera(const ResponseStartRtspStreamCamera &obj):IJsonable(), ICommonFields(),IResponseResultable()
{
    selfCopy(obj);
}

ResponseStartRtspStreamCamera &ResponseStartRtspStreamCamera::operator =(const ResponseStartRtspStreamCamera &obj)
{
    OPERATOR_EQUAL_BODY;
}

ResponseStartRtspStreamCamera::ResponseStartRtspStreamCamera(const QJsonObject &json)
{
    if ( !IJsonable::typeFromJsonObject(json) ||
         !IResponseResultable::resultResponseFromJsonObject(json)
            )
        return;
    if ( !json.contains("mRtspUrl")
         )
        return;
    ICommonFields::fromJsonObject(json);
    JSON_TO_QSTRING(json, mRtspUrl);
}

void ResponseStartRtspStreamCamera::selfCopy(const ResponseStartRtspStreamCamera &obj)
{
    mRtspUrl = obj.mRtspUrl;
    mUidRequest = obj.mUidRequest;
    mResponseResult = obj.mResponseResult;
}

EDataType ResponseStartRtspStreamCamera::type() const
{
    return EDataType::ResponseStartRtspStreamCamera;
}

QJsonObject ResponseStartRtspStreamCamera::toJsonObject() const
{
    QJsonObject object;
    ICommonFields::toJsonObject(object);
    IJsonable::typeToJsonObject(object);
    IResponseResultable::resultResponseToJsonObject(object);
    QSTRING_TO_JSON(mRtspUrl, object);
    return object;
}

bool ResponseStartRtspStreamCamera::isValid() const
{
    if (mResponseResult == EResult::None)
        return false;
    else
        return true;
}

// ------------------------------------------------
// ----- RequestStopRtspStreamCamera
// ------------------------------------------------

RequestStopRtspStreamCamera::RequestStopRtspStreamCamera():IJsonable(), ICommonFields(),
    mStreamUid(QUuid()), mRtspStreamUid(QUuid()), mCameraUid(QUuid()), mCassyUid(QUuid())
{

}

RequestStopRtspStreamCamera::RequestStopRtspStreamCamera(const QUuid& streamUid, const QUuid& rtspStreamUid, const QUuid& cameraUid, const QUuid& cassyUid):IJsonable(), ICommonFields(),
    mStreamUid(streamUid), mRtspStreamUid(rtspStreamUid), mCameraUid(cameraUid), mCassyUid(cassyUid)
{

}

RequestStopRtspStreamCamera::RequestStopRtspStreamCamera(const RequestStopRtspStreamCamera &obj):IJsonable(), ICommonFields()
{
    selfCopy(obj);
}

RequestStopRtspStreamCamera &RequestStopRtspStreamCamera::operator =(const RequestStopRtspStreamCamera &obj)
{
    OPERATOR_EQUAL_BODY;
}

RequestStopRtspStreamCamera::RequestStopRtspStreamCamera(const QJsonObject &json)
{
    if ( !IJsonable::typeFromJsonObject(json)
            )
        return;
    if ( !json.contains("mStreamUid") ||
         !json.contains("mRtspStreamUid") ||
         !json.contains("mCameraUid") ||
         !json.contains("mCassyUid")
         )
        return;
    ICommonFields::fromJsonObject(json);
    JSON_TO_QUUID(json, mStreamUid);
    JSON_TO_QUUID(json, mRtspStreamUid);
    JSON_TO_QUUID(json, mCameraUid);
    JSON_TO_QUUID(json, mCassyUid);
}

void RequestStopRtspStreamCamera::selfCopy(const RequestStopRtspStreamCamera &obj)
{
    mUidRequest = obj.mUidRequest;
    mStreamUid = obj.mStreamUid;
    mRtspStreamUid = obj.mRtspStreamUid;
    mCameraUid = obj.mCameraUid;
    mCassyUid = obj.mCassyUid;
}

EDataType RequestStopRtspStreamCamera::type() const
{
    return EDataType::RequestStopRtspStreamCamera;
}

QJsonObject RequestStopRtspStreamCamera::toJsonObject() const
{
    QJsonObject object;
    ICommonFields::toJsonObject(object);
    IJsonable::typeToJsonObject(object);
    QUUID_TO_JSON(mStreamUid, object);
    QUUID_TO_JSON(mRtspStreamUid, object);
    QUUID_TO_JSON(mCameraUid, object);
    QUUID_TO_JSON(mCassyUid, object);
    return object;
}

bool RequestStopRtspStreamCamera::isValid() const
{
    if (mStreamUid.isNull() || mRtspStreamUid.isNull())
        return false;
    else
        return true;
}

// ------------------------------------------------
// ----- ResponseStopRtspStreamCamera
// ------------------------------------------------

ResponseStopRtspStreamCamera::ResponseStopRtspStreamCamera(): IJsonable(), ICommonFields(), IResponseResultable()
{

}

ResponseStopRtspStreamCamera::ResponseStopRtspStreamCamera(const ResponseStopRtspStreamCamera &obj): IJsonable(), ICommonFields(), IResponseResultable()
{
    selfCopy(obj);
}

ResponseStopRtspStreamCamera &ResponseStopRtspStreamCamera::operator =(const ResponseStopRtspStreamCamera &obj)
{
    OPERATOR_EQUAL_BODY;
}

ResponseStopRtspStreamCamera::ResponseStopRtspStreamCamera(const QJsonObject &json)
{
    if ( !IJsonable::typeFromJsonObject(json) ||
         !IResponseResultable::resultResponseFromJsonObject(json)
            )
        return;
    ICommonFields::fromJsonObject(json);
}

void ResponseStopRtspStreamCamera::selfCopy(const ResponseStopRtspStreamCamera &obj)
{
    mUidRequest = obj.mUidRequest;
    mResponseResult = obj.mResponseResult;
}

EDataType ResponseStopRtspStreamCamera::type() const
{
    return EDataType::ResponseStopRtspStreamCamera;
}

QJsonObject ResponseStopRtspStreamCamera::toJsonObject() const
{
    QJsonObject object;
    ICommonFields::toJsonObject(object);
    IJsonable::typeToJsonObject(object);
    IResponseResultable::resultResponseToJsonObject(object);
    return object;
}

bool ResponseStopRtspStreamCamera::isValid() const
{
    if (mResponseResult == EResult::None)
        return false;
    else
        return true;
}

// ------------------------------------------------
// ----- RequestServerList
// ------------------------------------------------

RequestServerList::RequestServerList():IJsonable(), ICommonFields()
{

}

RequestServerList::RequestServerList(const RequestServerList &obj):IJsonable(), ICommonFields()
{
    selfCopy(obj);
}

RequestServerList &RequestServerList::operator =(const RequestServerList &obj)
{
    OPERATOR_EQUAL_BODY;
}

RequestServerList::RequestServerList(const QJsonObject &json)
{
    if ( !IJsonable::typeFromJsonObject(json)
            )
        return;
    ICommonFields::fromJsonObject(json);
}

void RequestServerList::selfCopy(const RequestServerList &obj)
{
    mUidRequest = obj.mUidRequest;
}

EDataType RequestServerList::type() const
{
  return EDataType::RequestServerList;
}

QJsonObject RequestServerList::toJsonObject() const
{
    QJsonObject object;
    ICommonFields::toJsonObject(object);
    IJsonable::typeToJsonObject(object);
    return object;
}

bool RequestServerList::isValid() const
{
    return true;
}

// ------------------------------------------------
// ----- ResponseServerList
// ------------------------------------------------

ResponseServerList::ResponseServerList(): IJsonable(), ICommonFields(), IResponseResultable()
{

}

ResponseServerList::ResponseServerList(const ResponseServerList &obj): IJsonable(), ICommonFields(), IResponseResultable()
{
    selfCopy(obj);
}

ResponseServerList &ResponseServerList::operator =(const ResponseServerList &obj)
{
    OPERATOR_EQUAL_BODY;
}

ResponseServerList::ResponseServerList(const QJsonObject &json)
{
    if ( !IJsonable::typeFromJsonObject(json) ||
         !IResponseResultable::resultResponseFromJsonObject(json)
            )
        return;
    ICommonFields::fromJsonObject(json);
    JSON_TO_QMAP_QUUID_STRUCT(json, ServerProperties, mServers);
}

void ResponseServerList::selfCopy(const ResponseServerList &obj)
{
    mUidRequest = obj.mUidRequest;
    mResponseResult = obj.mResponseResult;
    mServers.clear();
    mServers = obj.mServers;
}

EDataType ResponseServerList::type() const
{
    return EDataType::ResponseServerList;
}

QJsonObject ResponseServerList::toJsonObject() const
{
    QJsonObject object;
    ICommonFields::toJsonObject(object);
    IJsonable::typeToJsonObject(object);
    IResponseResultable::resultResponseToJsonObject(object);
    QMAP_QUUID_STRUCT_TO_JSON(mServers, ServerProperties, object);
    return object;
}

bool ResponseServerList::isValid() const
{
    if (mResponseResult == EResult::None)
        return false;
    else
        return true;
}
/*
// ------------------------------------------------
// ----- RequestListArhiveVideoByStreamCamera
// ------------------------------------------------

RequestListArhiveVideoByStreamCamera::RequestListArhiveVideoByStreamCamera():
    mStreamCameraUid(QUuid()), mStartFilter(QDateTime()), mFinishFilter(QDateTime())
{

}

RequestListArhiveVideoByStreamCamera::RequestListArhiveVideoByStreamCamera(const QUuid& streamCameraUid, const QDateTime &startFilter, const QDateTime &finishFilter):
    mStreamCameraUid(streamCameraUid), mStartFilter(startFilter), mFinishFilter(finishFilter)
{

}

RequestListArhiveVideoByStreamCamera::RequestListArhiveVideoByStreamCamera(const RequestListArhiveVideoByStreamCamera &obj)
{
    selfCopy(obj);
}

RequestListArhiveVideoByStreamCamera &RequestListArhiveVideoByStreamCamera::operator =(const RequestListArhiveVideoByStreamCamera &obj)
{
    OPERATOR_EQUAL_BODY;
}

RequestListArhiveVideoByStreamCamera::RequestListArhiveVideoByStreamCamera(const QJsonObject &json)
{
    if ( !IJsonable::typeFromJsonObject(json)
            )
        return;
    if ( !json.contains("mStreamCameraUid") ||
         !json.contains("mStartFilter") ||
         !json.contains("mFinishFilter")
         )
        return;
    JSON_TO_QUUID(json, mStreamCameraUid);
    JSON_TO_QDATETIME(json, mStartFilter);
    JSON_TO_QDATETIME(json, mFinishFilter);
}

void RequestListArhiveVideoByStreamCamera::selfCopy(const RequestListArhiveVideoByStreamCamera &obj)
{
    mUidRequest = obj.mUidRequest;
    mStreamCameraUid = obj.mStreamCameraUid;
    mStartFilter = obj.mStartFilter;
    mFinishFilter = obj.mFinishFilter;
}

EDataType RequestListArhiveVideoByStreamCamera::type() const
{
    return EDataType::RequestListArhiveVideoByStreamCamera;
}

QJsonObject RequestListArhiveVideoByStreamCamera::toJsonObject() const
{
    QJsonObject object;
    IJsonable::typeToJsonObject(object);
    QUUID_TO_JSON(mStreamCameraUid, object);
    QDATETIME_TO_JSON(mStartFilter, object);
    QDATETIME_TO_JSON(mFinishFilter, object);
    return object;
}

bool RequestListArhiveVideoByStreamCamera::isValid() const
{
    return true;
}

// ------------------------------------------------
// ----- ResponseListArhiveVideoByStreamCamera
// ------------------------------------------------

ResponseListArhiveVideoByStreamCamera::ResponseListArhiveVideoByStreamCamera()
{

}

ResponseListArhiveVideoByStreamCamera::ResponseListArhiveVideoByStreamCamera(const ResponseListArhiveVideoByStreamCamera &obj)
{
    selfCopy(obj);
}

ResponseListArhiveVideoByStreamCamera &ResponseListArhiveVideoByStreamCamera::operator =(const ResponseListArhiveVideoByStreamCamera &obj)
{
    OPERATOR_EQUAL_BODY;
}

ResponseListArhiveVideoByStreamCamera::ResponseListArhiveVideoByStreamCamera(const QJsonObject &json)
{
    if ( !IJsonable::typeFromJsonObject(json) ||
         !IResponseResultable::resultResponseFromJsonObject(json)
            )
        return;
    JSON_TO_QMAP_QUUID_STRUCT(json, VideoProperties, mVideos);
}

void ResponseListArhiveVideoByStreamCamera::selfCopy(const ResponseListArhiveVideoByStreamCamera &obj)
{
    mUidRequest = obj.mUidRequest;
    mResponseResult = obj.mResponseResult;
    mVideos.clear();
    mVideos = obj.mVideos;
}

EDataType ResponseListArhiveVideoByStreamCamera::type() const
{
    return EDataType::ResponseListArhiveVideoByStreamCamera;
}

QJsonObject ResponseListArhiveVideoByStreamCamera::toJsonObject() const
{
    QJsonObject object;
    IJsonable::typeToJsonObject(object);
    IResponseResultable::resultResponseToJsonObject(object);
    QMAP_QUUID_STRUCT_TO_JSON(mVideos, VideoProperties, object);
    return object;
}

bool ResponseListArhiveVideoByStreamCamera::isValid() const
{
    if (mResponseResult == EResult::None)
        return false;
    else
        return true;
}
*/
// ------------------------------------------------
// ----- RequestCreateRtspStreamVideo
// ------------------------------------------------

RequestCreateRtspStreamVideo::RequestCreateRtspStreamVideo():IJsonable(), ICommonFields(),
    mVideoUid(QUuid()), mVideosUuids(), mRtspStreamUid(QUuid()), mStartSecond(0.), mPlaybackSpeed(1.)
{

}

RequestCreateRtspStreamVideo::RequestCreateRtspStreamVideo(const QUuid& videoUid, const QVector<QUuid> &videosUuids, const QUuid& rtspStreamUid, double startSecond, double playbackSpeed):IJsonable(), ICommonFields(),
    mVideoUid(videoUid), mVideosUuids(videosUuids), mRtspStreamUid(rtspStreamUid), mStartSecond(startSecond), mPlaybackSpeed(playbackSpeed)
{

}

RequestCreateRtspStreamVideo::RequestCreateRtspStreamVideo(const RequestCreateRtspStreamVideo &obj):IJsonable(), ICommonFields()
{
    selfCopy(obj);
}

RequestCreateRtspStreamVideo &RequestCreateRtspStreamVideo::operator =(const RequestCreateRtspStreamVideo &obj)
{
    OPERATOR_EQUAL_BODY;
}

RequestCreateRtspStreamVideo::RequestCreateRtspStreamVideo(const QJsonObject &json)
{
    if ( !IJsonable::typeFromJsonObject(json)
            )
        return;
    if ( !json.contains("mVideoUid") ||
         !json.contains("uidsVecString") ||
         !json.contains("mRtspStreamUid") ||
         !json.contains("mStartSecond") ||
         !json.contains("mPlaybackSpeed") ||
         !json.contains("mIsNeedPreviewFrame")
         )
        return;
    ICommonFields::fromJsonObject(json);
    JSON_TO_QUUID(json, mVideoUid);

    mVideosUuids.clear();
    QString uidsVecString = "";
    JSON_TO_QSTRING_NO_TRIM(json, uidsVecString);
    QStringList uidsStringList = uidsVecString.split("#");
    for (auto i = 0; i < uidsStringList.count(); ++i)
    {
        auto uid = QUuid(uidsStringList[i]);
        if (!uid.isNull())
            mVideosUuids.append(uid);
    }

    JSON_TO_QUUID(json, mRtspStreamUid);
    JSON_TO_DOUBLE(json, mStartSecond);
    JSON_TO_DOUBLE(json, mPlaybackSpeed);
    JSON_TO_BOOL(json, mIsNeedPreviewFrame);
}

void RequestCreateRtspStreamVideo::selfCopy(const RequestCreateRtspStreamVideo &obj)
{
    mUidRequest = obj.mUidRequest;
    mVideoUid = obj.mVideoUid;
    mVideosUuids = obj.mVideosUuids;
    mRtspStreamUid = obj.mRtspStreamUid;
    mStartSecond = obj.mStartSecond;
    mPlaybackSpeed = obj.mPlaybackSpeed;
    mIsNeedPreviewFrame = obj.mIsNeedPreviewFrame;
}

EDataType RequestCreateRtspStreamVideo::type() const
{
    return EDataType::RequestCreateRtspStreamVideo;
}

QJsonObject RequestCreateRtspStreamVideo::toJsonObject() const
{
    QJsonObject object;
    ICommonFields::toJsonObject(object);
    IJsonable::typeToJsonObject(object);
    QUUID_TO_JSON(mVideoUid, object);

    QString uidsVecString = "";
    for (auto i = 0; i < mVideosUuids.count(); ++i)
    {
        uidsVecString += mVideosUuids[i].toString(QUuid::WithoutBraces);
        if (i < mVideosUuids.count() - 1)
            uidsVecString += "#";
    }
    QSTRING_TO_JSON(uidsVecString, object);

    QUUID_TO_JSON(mRtspStreamUid, object);
    DOUBLE_TO_JSON(mStartSecond, object);
    DOUBLE_TO_JSON(mPlaybackSpeed, object);
    BOOL_TO_JSON(mIsNeedPreviewFrame, object);
    return object;
}

bool RequestCreateRtspStreamVideo::isValid() const
{
    if (mVideoUid.isNull() || mVideosUuids.isEmpty() || mRtspStreamUid.isNull())
        return false;
    else
        return true;
}

// ------------------------------------------------
// ----- ResponseCreateRtspStreamVideo
// ------------------------------------------------

ResponseCreateRtspStreamVideo::ResponseCreateRtspStreamVideo(): IJsonable(), ICommonFields(), IResponseResultable(),
    mRtspUrl("")
{

}

ResponseCreateRtspStreamVideo::ResponseCreateRtspStreamVideo(const QString &rtspUrl): IJsonable(), ICommonFields(), IResponseResultable(),
    mRtspUrl(rtspUrl)
{

}

ResponseCreateRtspStreamVideo::ResponseCreateRtspStreamVideo(const ResponseCreateRtspStreamVideo &obj): IJsonable(), ICommonFields(), IResponseResultable()
{
    selfCopy(obj);
}

ResponseCreateRtspStreamVideo &ResponseCreateRtspStreamVideo::operator =(const ResponseCreateRtspStreamVideo &obj)
{
    OPERATOR_EQUAL_BODY;
}

ResponseCreateRtspStreamVideo::ResponseCreateRtspStreamVideo(const QJsonObject &json)
{
    if ( !IJsonable::typeFromJsonObject(json) ||
         !IResponseResultable::resultResponseFromJsonObject(json)
            )
        return;
    if ( !json.contains("mRtspUrl") ||
         !json.contains("mPreviewFrame")
         )
        return;
    ICommonFields::fromJsonObject(json);
    JSON_TO_QSTRING(json, mRtspUrl);
    auto hexed = json.value("mPreviewFrame").toVariant().toByteArray();
    mPreviewFrame = QByteArray::fromHex(hexed);
}

void ResponseCreateRtspStreamVideo::selfCopy(const ResponseCreateRtspStreamVideo &obj)
{
    mUidRequest = obj.mUidRequest;
    mResponseResult = obj.mResponseResult;
    mPreviewFrame = obj.mPreviewFrame;
    mRtspUrl = obj.mRtspUrl;
}

EDataType ResponseCreateRtspStreamVideo::type() const
{
    return EDataType::ResponseCreateRtspStreamVideo;
}

QJsonObject ResponseCreateRtspStreamVideo::toJsonObject() const
{
    QJsonObject object;
    ICommonFields::toJsonObject(object);
    IJsonable::typeToJsonObject(object);
    IResponseResultable::resultResponseToJsonObject(object);
    QSTRING_TO_JSON(mRtspUrl, object);
    auto hexed = mPreviewFrame.toHex();
    object.insert("mPreviewFrame", QJsonValue::fromVariant(hexed));
    return object;
}

bool ResponseCreateRtspStreamVideo::isValid() const
{
    if (mResponseResult == EResult::None)
        return false;
    else
        return true;
}

// ------------------------------------------------
// ----- RequestStartRtspStreamVideo
// ------------------------------------------------

RequestStartRtspStreamVideo::RequestStartRtspStreamVideo():IJsonable(), ICommonFields(),
    mVideoUid(QUuid()), mVideosUuids(), mRtspStreamUid(QUuid())
{

}

RequestStartRtspStreamVideo::RequestStartRtspStreamVideo(const QUuid& videoUid, const QVector<QUuid> &videosUuids, const QUuid& rtspStreamUid):IJsonable(), ICommonFields(),
    mVideoUid(videoUid), mVideosUuids(videosUuids), mRtspStreamUid(rtspStreamUid)
{

}

RequestStartRtspStreamVideo::RequestStartRtspStreamVideo(const RequestStartRtspStreamVideo &obj):IJsonable(), ICommonFields()
{
    selfCopy(obj);
}

RequestStartRtspStreamVideo &RequestStartRtspStreamVideo::operator =(const RequestStartRtspStreamVideo &obj)
{
    OPERATOR_EQUAL_BODY;
}

RequestStartRtspStreamVideo::RequestStartRtspStreamVideo(const QJsonObject &json)
{
    if ( !IJsonable::typeFromJsonObject(json)
            )
        return;
    if ( !json.contains("mVideoUid") ||
         !json.contains("uidsVecString") ||
         !json.contains("mRtspStreamUid")
         )
        return;
    ICommonFields::fromJsonObject(json);
    JSON_TO_QUUID(json, mVideoUid);

    mVideosUuids.clear();
    QString uidsVecString = "";
    JSON_TO_QSTRING_NO_TRIM(json, uidsVecString);
    QStringList uidsStringList = uidsVecString.split("#");
    for (auto i = 0; i < uidsStringList.count(); ++i)
    {
        auto uid = QUuid(uidsStringList[i]);
        if (!uid.isNull())
            mVideosUuids.append(uid);
    }

    JSON_TO_QUUID(json, mRtspStreamUid);
}

void RequestStartRtspStreamVideo::selfCopy(const RequestStartRtspStreamVideo &obj)
{
    mUidRequest = obj.mUidRequest;
    mVideoUid = obj.mVideoUid;
    mVideosUuids = obj.mVideosUuids;
    mRtspStreamUid = obj.mRtspStreamUid;
}

EDataType RequestStartRtspStreamVideo::type() const
{
    return EDataType::RequestStartRtspStreamVideo;
}

QJsonObject RequestStartRtspStreamVideo::toJsonObject() const
{
    QJsonObject object;
    ICommonFields::toJsonObject(object);
    IJsonable::typeToJsonObject(object);
    QUUID_TO_JSON(mVideoUid, object);

    QString uidsVecString = "";
    for (auto i = 0; i < mVideosUuids.count(); ++i)
    {
        uidsVecString += mVideosUuids[i].toString(QUuid::WithoutBraces);
        if (i < mVideosUuids.count() - 1)
            uidsVecString += "#";
    }
    QSTRING_TO_JSON(uidsVecString, object);

    QUUID_TO_JSON(mRtspStreamUid, object);
    return object;
}

bool RequestStartRtspStreamVideo::isValid() const
{
    if (mVideoUid.isNull() || mVideosUuids.isEmpty() || mRtspStreamUid.isNull())
        return false;
    else
        return true;
}

// ------------------------------------------------
// ----- ResponseStartRtspStreamVideo
// ------------------------------------------------

ResponseStartRtspStreamVideo::ResponseStartRtspStreamVideo(): IJsonable(), ICommonFields(), IResponseResultable()
{

}

ResponseStartRtspStreamVideo::ResponseStartRtspStreamVideo(const ResponseStartRtspStreamVideo &obj): IJsonable(), ICommonFields(), IResponseResultable()
{
    selfCopy(obj);
}

ResponseStartRtspStreamVideo &ResponseStartRtspStreamVideo::operator =(const ResponseStartRtspStreamVideo &obj)
{
    OPERATOR_EQUAL_BODY;
}

ResponseStartRtspStreamVideo::ResponseStartRtspStreamVideo(const QJsonObject &json)
{
    if ( !IJsonable::typeFromJsonObject(json) ||
         !IResponseResultable::resultResponseFromJsonObject(json)
            )
        return;
    ICommonFields::fromJsonObject(json);
}

void ResponseStartRtspStreamVideo::selfCopy(const ResponseStartRtspStreamVideo &obj)
{
    mUidRequest = obj.mUidRequest;
    mResponseResult = obj.mResponseResult;
}

EDataType ResponseStartRtspStreamVideo::type() const
{
    return EDataType::ResponseStartRtspStreamVideo;
}

QJsonObject ResponseStartRtspStreamVideo::toJsonObject() const
{
    QJsonObject object;
    ICommonFields::toJsonObject(object);
    IJsonable::typeToJsonObject(object);
    IResponseResultable::resultResponseToJsonObject(object);
    return object;
}

bool ResponseStartRtspStreamVideo::isValid() const
{
    if (mResponseResult == EResult::None)
        return false;
    else
        return true;
}

// ------------------------------------------------
// ----- RequestStopRtspStreamVideo
// ------------------------------------------------

RequestStopRtspStreamVideo::RequestStopRtspStreamVideo():IJsonable(), ICommonFields(),
    mVideoUid(QUuid()), mRtspStreamUid(QUuid())
{

}

RequestStopRtspStreamVideo::RequestStopRtspStreamVideo(const QUuid& videoUid, const QUuid& rtspStreamUid):IJsonable(), ICommonFields(),
    mVideoUid(videoUid), mRtspStreamUid(rtspStreamUid)
{

}

RequestStopRtspStreamVideo::RequestStopRtspStreamVideo(const RequestStopRtspStreamVideo &obj):IJsonable(), ICommonFields()
{
    selfCopy(obj);
}

RequestStopRtspStreamVideo &RequestStopRtspStreamVideo::operator =(const RequestStopRtspStreamVideo &obj)
{
    OPERATOR_EQUAL_BODY;
}

RequestStopRtspStreamVideo::RequestStopRtspStreamVideo(const QJsonObject &json)
{
    if ( !IJsonable::typeFromJsonObject(json)
            )
        return;
    if ( !json.contains("mVideoUid") ||
         !json.contains("mRtspStreamUid")
         )
        return;
    ICommonFields::fromJsonObject(json);
    JSON_TO_QUUID(json, mVideoUid);
    JSON_TO_QUUID(json, mRtspStreamUid);
}

void RequestStopRtspStreamVideo::selfCopy(const RequestStopRtspStreamVideo &obj)
{
    mUidRequest = obj.mUidRequest;
    mVideoUid = obj.mVideoUid;
    mRtspStreamUid = obj.mRtspStreamUid;
}

EDataType RequestStopRtspStreamVideo::type() const
{
    return EDataType::RequestStopRtspStreamVideo;
}

QJsonObject RequestStopRtspStreamVideo::toJsonObject() const
{
    QJsonObject object;
    ICommonFields::toJsonObject(object);
    IJsonable::typeToJsonObject(object);
    QUUID_TO_JSON(mVideoUid, object);
    QUUID_TO_JSON(mRtspStreamUid, object);
    return object;
}

bool RequestStopRtspStreamVideo::isValid() const
{
    if (mVideoUid.isNull() || mRtspStreamUid.isNull())
        return false;
    else
        return true;
}

// ------------------------------------------------
// ----- ResponseStopRtspStreamVideo
// ------------------------------------------------

ResponseStopRtspStreamVideo::ResponseStopRtspStreamVideo(): IJsonable(), ICommonFields(), IResponseResultable()
{

}

ResponseStopRtspStreamVideo::ResponseStopRtspStreamVideo(const ResponseStopRtspStreamVideo &obj): IJsonable(), ICommonFields(), IResponseResultable()
{
    selfCopy(obj);
}

ResponseStopRtspStreamVideo &ResponseStopRtspStreamVideo::operator =(const ResponseStopRtspStreamVideo &obj)
{
    OPERATOR_EQUAL_BODY;
}

ResponseStopRtspStreamVideo::ResponseStopRtspStreamVideo(const QJsonObject &json)
{
    if ( !IJsonable::typeFromJsonObject(json) ||
         !IResponseResultable::resultResponseFromJsonObject(json)
            )
        return;
    ICommonFields::fromJsonObject(json);
}

void ResponseStopRtspStreamVideo::selfCopy(const ResponseStopRtspStreamVideo &obj)
{
    mUidRequest = obj.mUidRequest;
    mResponseResult = obj.mResponseResult;
}

EDataType ResponseStopRtspStreamVideo::type() const
{
    return EDataType::ResponseStopRtspStreamVideo;
}

QJsonObject ResponseStopRtspStreamVideo::toJsonObject() const
{
    QJsonObject object;
    ICommonFields::toJsonObject(object);
    IJsonable::typeToJsonObject(object);
    IResponseResultable::resultResponseToJsonObject(object);
    return object;
}

bool ResponseStopRtspStreamVideo::isValid() const
{
    if (mResponseResult == EResult::None)
        return false;
    else
        return true;
}
/*
// ------------------------------------------------
// ----- RequestAddAccessRight
// ------------------------------------------------

RequestAddAccessRight::RequestAddAccessRight():mProperties(AccessRightProperties())
{

}

RequestAddAccessRight::RequestAddAccessRight(const AccessRightProperties &properties):mProperties(properties)
{

}

RequestAddAccessRight::RequestAddAccessRight(const RequestAddAccessRight &obj)
{
    selfCopy(obj);
}

RequestAddAccessRight &RequestAddAccessRight::operator =(const RequestAddAccessRight &obj)
{
    OPERATOR_EQUAL_BODY;
}

RequestAddAccessRight::RequestAddAccessRight(const QJsonObject &json)
{
    if ( !IJsonable::typeFromJsonObject(json)
            )
        return;
    if ( !json.contains("mProperties")
         )
        return;
    JSON_TO_STRUCT(json, AccessRightProperties, mProperties);
}

void RequestAddAccessRight::selfCopy(const RequestAddAccessRight &obj)
{
    mUidRequest = obj.mUidRequest;
    mProperties = obj.mProperties;
}

EDataType RequestAddAccessRight::type() const
{
  return EDataType::RequestAddAccessRight;
}

QJsonObject RequestAddAccessRight::toJsonObject() const
{
    QJsonObject object;
    IJsonable::typeToJsonObject(object);
    STRUCT_TO_JSON(mProperties, AccessRightProperties, object);
    return object;
}

bool RequestAddAccessRight::isValid() const
{
    return mProperties.isValid();
}

// ------------------------------------------------
// ----- ResponseAddAccessRight
// ------------------------------------------------

ResponseAddAccessRight::ResponseAddAccessRight():mAccessRightUid(QUuid())
{

}

ResponseAddAccessRight::ResponseAddAccessRight(const QUuid &accessRightUid):mAccessRightUid(accessRightUid)
{

}

ResponseAddAccessRight::ResponseAddAccessRight(const ResponseAddAccessRight &obj)
{
    selfCopy(obj);
}

ResponseAddAccessRight &ResponseAddAccessRight::operator =(const ResponseAddAccessRight &obj)
{
    OPERATOR_EQUAL_BODY;
}

ResponseAddAccessRight::ResponseAddAccessRight(const QJsonObject &json)
{
    if ( !IJsonable::typeFromJsonObject(json) ||
         !IResponseResultable::resultResponseFromJsonObject(json)
            )
        return;
    if ( !json.contains("mAccessRightUid")
         )
        return;
    JSON_TO_QUUID(json, mAccessRightUid);
}

void ResponseAddAccessRight::selfCopy(const ResponseAddAccessRight &obj)
{
    mUidRequest = obj.mUidRequest;
    mAccessRightUid = obj.mAccessRightUid;
    mResponseResult = obj.mResponseResult;
}

EDataType ResponseAddAccessRight::type() const
{
    return EDataType::ResponseAddAccessRight;
}

QJsonObject ResponseAddAccessRight::toJsonObject() const
{
    QJsonObject object;
    IJsonable::typeToJsonObject(object);
    IResponseResultable::resultResponseToJsonObject(object);
    QUUID_TO_JSON(mAccessRightUid, object);
    return object;
}

bool ResponseAddAccessRight::isValid() const
{
    if (mResponseResult == EResult::None)
        return false;
    else
        return true;
}

// ------------------------------------------------
// ----- RequestRemoveAccessRight
// ------------------------------------------------

RequestRemoveAccessRight::RequestRemoveAccessRight():mAccessRightUid(QUuid())
{

}

RequestRemoveAccessRight::RequestRemoveAccessRight(const QUuid& accessRightUid):mAccessRightUid(accessRightUid)
{

}

RequestRemoveAccessRight::RequestRemoveAccessRight(const RequestRemoveAccessRight &obj)
{
    selfCopy(obj);
}

RequestRemoveAccessRight &RequestRemoveAccessRight::operator =(const RequestRemoveAccessRight &obj)
{
    OPERATOR_EQUAL_BODY;
}

RequestRemoveAccessRight::RequestRemoveAccessRight(const QJsonObject &json)
{
    if ( !IJsonable::typeFromJsonObject(json)
            )
        return;
    if ( !json.contains("mAccessRightUid")
         )
        return;
    JSON_TO_QUUID(json, mAccessRightUid);
}

void RequestRemoveAccessRight::selfCopy(const RequestRemoveAccessRight &obj)
{
    mUidRequest = obj.mUidRequest;
    mAccessRightUid = obj.mAccessRightUid;
}

EDataType RequestRemoveAccessRight::type() const
{
  return EDataType::RequestRemoveAccessRight;
}

QJsonObject RequestRemoveAccessRight::toJsonObject() const
{
    QJsonObject object;
    IJsonable::typeToJsonObject(object);
    QUUID_TO_JSON(mAccessRightUid, object);
    return object;
}

bool RequestRemoveAccessRight::isValid() const
{
    return !mAccessRightUid.isNull();
}

// ------------------------------------------------
// ----- ResponseRemoveAccessRight
// ------------------------------------------------

ResponseRemoveAccessRight::ResponseRemoveAccessRight()
{

}

ResponseRemoveAccessRight::ResponseRemoveAccessRight(const ResponseRemoveAccessRight &obj)
{
    selfCopy(obj);
}

ResponseRemoveAccessRight &ResponseRemoveAccessRight::operator =(const ResponseRemoveAccessRight &obj)
{
    OPERATOR_EQUAL_BODY;
}

ResponseRemoveAccessRight::ResponseRemoveAccessRight(const QJsonObject &json)
{
    if ( !IJsonable::typeFromJsonObject(json) ||
         !IResponseResultable::resultResponseFromJsonObject(json)
            )
        return;
}

void ResponseRemoveAccessRight::selfCopy(const ResponseRemoveAccessRight &obj)
{
    mUidRequest = obj.mUidRequest;
    mResponseResult = obj.mResponseResult;
}

EDataType ResponseRemoveAccessRight::type() const
{
    return EDataType::ResponseRemoveAccessRight;
}

QJsonObject ResponseRemoveAccessRight::toJsonObject() const
{
    QJsonObject object;
    IJsonable::typeToJsonObject(object);
    IResponseResultable::resultResponseToJsonObject(object);
    return object;
}

bool ResponseRemoveAccessRight::isValid() const
{
    if (mResponseResult == EResult::None)
        return false;
    else
        return true;
}

// ------------------------------------------------
// ----- RequestListAccessRights
// ------------------------------------------------

RequestListAccessRights::RequestListAccessRights():
    mUserUidFilter(QUuid()), mGroupUidFilter(QUuid()), mZoneUidFilter(QUuid()), mCameraUidFilter(QUuid())
{

}

RequestListAccessRights::RequestListAccessRights(const QUuid& userUidFilter, const QUuid& groupUidFilter, const QUuid& zoneUidFilter, const QUuid& cameraUidFilter):
    mUserUidFilter(userUidFilter), mGroupUidFilter(groupUidFilter), mZoneUidFilter(zoneUidFilter), mCameraUidFilter(cameraUidFilter)
{

}

RequestListAccessRights::RequestListAccessRights(const RequestListAccessRights &obj)
{
    selfCopy(obj);
}

RequestListAccessRights &RequestListAccessRights::operator =(const RequestListAccessRights &obj)
{
    OPERATOR_EQUAL_BODY;
}

RequestListAccessRights::RequestListAccessRights(const QJsonObject &json)
{
    if ( !IJsonable::typeFromJsonObject(json)
            )
        return;
    if ( !json.contains("mUserUidFilter") ||
         !json.contains("mGroupUidFilter") ||
         !json.contains("mZoneUidFilter") ||
         !json.contains("mCameraUidFilter")
         )
        return;
    JSON_TO_QUUID(json, mUserUidFilter);
    JSON_TO_QUUID(json, mGroupUidFilter);
    JSON_TO_QUUID(json, mZoneUidFilter);
    JSON_TO_QUUID(json, mCameraUidFilter);
}

void RequestListAccessRights::selfCopy(const RequestListAccessRights &obj)
{
    mUidRequest = obj.mUidRequest;
    mUserUidFilter = obj.mUserUidFilter;
    mGroupUidFilter = obj.mGroupUidFilter;
    mZoneUidFilter = obj.mZoneUidFilter;
    mCameraUidFilter = obj.mCameraUidFilter;
}

EDataType RequestListAccessRights::type() const
{
  return EDataType::RequestListAccessRights;
}

QJsonObject RequestListAccessRights::toJsonObject() const
{
    QJsonObject object;
    IJsonable::typeToJsonObject(object);
    QUUID_TO_JSON(mUserUidFilter, object);
    QUUID_TO_JSON(mGroupUidFilter, object);
    QUUID_TO_JSON(mZoneUidFilter, object);
    QUUID_TO_JSON(mCameraUidFilter, object);
    return object;
}

bool RequestListAccessRights::isValid() const
{
    return true;
}

// ------------------------------------------------
// ----- ResponseListAccessRights
// ------------------------------------------------

ResponseListAccessRights::ResponseListAccessRights()
{

}

ResponseListAccessRights::ResponseListAccessRights(const ResponseListAccessRights &obj)
{
    selfCopy(obj);
}

ResponseListAccessRights &ResponseListAccessRights::operator =(const ResponseListAccessRights &obj)
{
    OPERATOR_EQUAL_BODY;
}

ResponseListAccessRights::ResponseListAccessRights(const QJsonObject &json)
{
    if ( !IJsonable::typeFromJsonObject(json) ||
         !IResponseResultable::resultResponseFromJsonObject(json)
            )
        return;
    JSON_TO_QMAP_QUUID_STRUCT(json, AccessRightProperties, mAccessRights);
}

void ResponseListAccessRights::selfCopy(const ResponseListAccessRights &obj)
{
    mUidRequest = obj.mUidRequest;
    mResponseResult = obj.mResponseResult;
    mAccessRights.clear();
    mAccessRights = obj.mAccessRights;
}

EDataType ResponseListAccessRights::type() const
{
    return EDataType::ResponseListAccessRights;
}

QJsonObject ResponseListAccessRights::toJsonObject() const
{
    QJsonObject object;
    IJsonable::typeToJsonObject(object);
    IResponseResultable::resultResponseToJsonObject(object);
    QMAP_QUUID_STRUCT_TO_JSON(mAccessRights, AccessRightProperties, object);
    return object;
}

bool ResponseListAccessRights::isValid() const
{
    if (mResponseResult == EResult::None)
        return false;
    else
        return true;
}

// ------------------------------------------------
// ----- RequestCreateGroup
// ------------------------------------------------

RequestCreateGroup::RequestCreateGroup():
    mName(""), mDescription("")
{

}

RequestCreateGroup::RequestCreateGroup(const QString &name, const QString &description):
    mName(name), mDescription(description)
{

}

RequestCreateGroup::RequestCreateGroup(const RequestCreateGroup &obj)
{
    selfCopy(obj);
}

RequestCreateGroup &RequestCreateGroup::operator =(const RequestCreateGroup &obj)
{
    OPERATOR_EQUAL_BODY;
}

RequestCreateGroup::RequestCreateGroup(const QJsonObject &json)
{
    if ( !IJsonable::typeFromJsonObject(json)
            )
        return;
    if ( !json.contains("mName") ||
         !json.contains("mDescription")
         )
        return;
    JSON_TO_QSTRING(json, mName);
    JSON_TO_QSTRING(json, mDescription);
}

void RequestCreateGroup::selfCopy(const RequestCreateGroup &obj)
{
    mUidRequest = obj.mUidRequest;
    mName = obj.mName;
    mDescription = obj.mDescription;
}

EDataType RequestCreateGroup::type() const
{
  return EDataType::RequestCreateGroup;
}

QJsonObject RequestCreateGroup::toJsonObject() const
{
    QJsonObject object;
    IJsonable::typeToJsonObject(object);
    QSTRING_TO_JSON(mName, object);
    QSTRING_TO_JSON(mDescription, object);
    return object;
}

bool RequestCreateGroup::isValid() const
{
    return !mName.isEmpty();
}

// ------------------------------------------------
// ----- ResponseCreateGroup
// ------------------------------------------------

ResponseCreateGroup::ResponseCreateGroup():
    mGroupUid(QUuid())
{

}

ResponseCreateGroup::ResponseCreateGroup(const QUuid &groupUid):
    mGroupUid(groupUid)
{

}

ResponseCreateGroup::ResponseCreateGroup(const ResponseCreateGroup &obj)
{
    selfCopy(obj);
}

ResponseCreateGroup &ResponseCreateGroup::operator =(const ResponseCreateGroup &obj)
{
    OPERATOR_EQUAL_BODY;
}

ResponseCreateGroup::ResponseCreateGroup(const QJsonObject &json)
{
    if ( !IJsonable::typeFromJsonObject(json) ||
         !IResponseResultable::resultResponseFromJsonObject(json)
            )
        return;
    if ( !json.contains("mGroupUid")
         )
        return;
    JSON_TO_QUUID(json, mGroupUid);
}

void ResponseCreateGroup::selfCopy(const ResponseCreateGroup &obj)
{
    mUidRequest = obj.mUidRequest;
    mGroupUid = obj.mGroupUid;
    mResponseResult = obj.mResponseResult;
}

EDataType ResponseCreateGroup::type() const
{
    return EDataType::ResponseCreateGroup;
}

QJsonObject ResponseCreateGroup::toJsonObject() const
{
    QJsonObject object;
    IJsonable::typeToJsonObject(object);
    IResponseResultable::resultResponseToJsonObject(object);
    QUUID_TO_JSON(mGroupUid, object);
    return object;
}

bool ResponseCreateGroup::isValid() const
{
    if (mResponseResult == EResult::None)
        return false;
    else
        return true;
}

// ------------------------------------------------
// ----- RequestRemoveGroup
// ------------------------------------------------

RequestRemoveGroup::RequestRemoveGroup():
    mGroupUid(QUuid())
{

}

RequestRemoveGroup::RequestRemoveGroup(const QUuid& groupUid):
    mGroupUid(groupUid)
{

}

RequestRemoveGroup::RequestRemoveGroup(const RequestRemoveGroup &obj)
{
    selfCopy(obj);
}

RequestRemoveGroup &RequestRemoveGroup::operator =(const RequestRemoveGroup &obj)
{
    OPERATOR_EQUAL_BODY;
}

RequestRemoveGroup::RequestRemoveGroup(const QJsonObject &json)
{
    if ( !IJsonable::typeFromJsonObject(json)
            )
        return;
    if ( !json.contains("mGroupUid")
         )
        return;
    JSON_TO_QUUID(json, mGroupUid);
}

void RequestRemoveGroup::selfCopy(const RequestRemoveGroup &obj)
{
    mUidRequest = obj.mUidRequest;
    mGroupUid = obj.mGroupUid;
}

EDataType RequestRemoveGroup::type() const
{
  return EDataType::RequestRemoveGroup;
}

QJsonObject RequestRemoveGroup::toJsonObject() const
{
    QJsonObject object;
    IJsonable::typeToJsonObject(object);
    QUUID_TO_JSON(mGroupUid, object);
    return object;
}

bool RequestRemoveGroup::isValid() const
{
    return !mGroupUid.isNull();
}

// ------------------------------------------------
// ----- ResponseRemoveGroup
// ------------------------------------------------

ResponseRemoveGroup::ResponseRemoveGroup()
{

}

ResponseRemoveGroup::ResponseRemoveGroup(const ResponseRemoveGroup &obj)
{
    selfCopy(obj);
}

ResponseRemoveGroup &ResponseRemoveGroup::operator =(const ResponseRemoveGroup &obj)
{
    OPERATOR_EQUAL_BODY;
}

ResponseRemoveGroup::ResponseRemoveGroup(const QJsonObject &json)
{
    if ( !IJsonable::typeFromJsonObject(json) ||
         !IResponseResultable::resultResponseFromJsonObject(json)
            )
        return;
}

void ResponseRemoveGroup::selfCopy(const ResponseRemoveGroup &obj)
{
    mUidRequest = obj.mUidRequest;
    mResponseResult = obj.mResponseResult;
}

EDataType ResponseRemoveGroup::type() const
{
    return EDataType::ResponseRemoveGroup;
}

QJsonObject ResponseRemoveGroup::toJsonObject() const
{
    QJsonObject object;
    IJsonable::typeToJsonObject(object);
    IResponseResultable::resultResponseToJsonObject(object);
    return object;
}

bool ResponseRemoveGroup::isValid() const
{
    if (mResponseResult == EResult::None)
        return false;
    else
        return true;
}

// ------------------------------------------------
// ----- RequestModifyGroup
// ------------------------------------------------

RequestModifyGroup::RequestModifyGroup():
    mGroupUid(QUuid()), mProperties(GroupProperties())
{

}

RequestModifyGroup::RequestModifyGroup(const QUuid& groupUid, const GroupProperties& properties):
    mGroupUid(groupUid), mProperties(properties)
{

}

RequestModifyGroup::RequestModifyGroup(const RequestModifyGroup &obj)
{
    selfCopy(obj);
}

RequestModifyGroup &RequestModifyGroup::operator =(const RequestModifyGroup &obj)
{
    OPERATOR_EQUAL_BODY;
}

RequestModifyGroup::RequestModifyGroup(const QJsonObject &json)
{
    if ( !IJsonable::typeFromJsonObject(json)
            )
        return;
    if ( !json.contains("mGroupUid") ||
         !json.contains("mProperties")
         )
        return;
    JSON_TO_QUUID(json, mGroupUid);
    JSON_TO_STRUCT(json, GroupProperties, mProperties);
}

void RequestModifyGroup::selfCopy(const RequestModifyGroup &obj)
{
    mUidRequest = obj.mUidRequest;
    mGroupUid = obj.mGroupUid;
    mProperties = obj.mProperties;
}

EDataType RequestModifyGroup::type() const
{
  return EDataType::RequestModifyGroup;
}

QJsonObject RequestModifyGroup::toJsonObject() const
{
    QJsonObject object;
    IJsonable::typeToJsonObject(object);
    QUUID_TO_JSON(mGroupUid, object);
    STRUCT_TO_JSON(mProperties, GroupProperties, object);
    return object;
}

bool RequestModifyGroup::isValid() const
{
    return !mGroupUid.isNull();
}

// ------------------------------------------------
// ----- ResponseModifyGroup
// ------------------------------------------------

ResponseModifyGroup::ResponseModifyGroup()
{

}

ResponseModifyGroup::ResponseModifyGroup(const ResponseModifyGroup &obj)
{
    selfCopy(obj);
}

ResponseModifyGroup &ResponseModifyGroup::operator =(const ResponseModifyGroup &obj)
{
    OPERATOR_EQUAL_BODY;
}

ResponseModifyGroup::ResponseModifyGroup(const QJsonObject &json)
{
    if ( !IJsonable::typeFromJsonObject(json) ||
         !IResponseResultable::resultResponseFromJsonObject(json)
            )
        return;
}

void ResponseModifyGroup::selfCopy(const ResponseModifyGroup &obj)
{
    mUidRequest = obj.mUidRequest;
    mResponseResult = obj.mResponseResult;
}

EDataType ResponseModifyGroup::type() const
{
    return EDataType::ResponseModifyGroup;
}

QJsonObject ResponseModifyGroup::toJsonObject() const
{
    QJsonObject object;
    IJsonable::typeToJsonObject(object);
    IResponseResultable::resultResponseToJsonObject(object);
    return object;
}

bool ResponseModifyGroup::isValid() const
{
    if (mResponseResult == EResult::None)
        return false;
    else
        return true;
}

// ------------------------------------------------
// ----- RequestListGroups
// ------------------------------------------------

RequestListGroups::RequestListGroups()
{

}

RequestListGroups::RequestListGroups(const RequestListGroups &obj)
{
    selfCopy(obj);
}

RequestListGroups &RequestListGroups::operator =(const RequestListGroups &obj)
{
    OPERATOR_EQUAL_BODY;
}

RequestListGroups::RequestListGroups(const QJsonObject &json)
{
    if ( !IJsonable::typeFromJsonObject(json)
            )
        return;
}

void RequestListGroups::selfCopy(const RequestListGroups &obj)
{
    mUidRequest = obj.mUidRequest;
}

EDataType RequestListGroups::type() const
{
  return EDataType::RequestListGroups;
}

QJsonObject RequestListGroups::toJsonObject() const
{
    QJsonObject object;
    IJsonable::typeToJsonObject(object);

    return object;
}

bool RequestListGroups::isValid() const
{
    return true;
}

// ------------------------------------------------
// ----- ResponseListGroups
// ------------------------------------------------

ResponseListGroups::ResponseListGroups()
{

}

ResponseListGroups::ResponseListGroups(const ResponseListGroups &obj)
{
    selfCopy(obj);
}

ResponseListGroups &ResponseListGroups::operator =(const ResponseListGroups &obj)
{
    OPERATOR_EQUAL_BODY;
}

ResponseListGroups::ResponseListGroups(const QJsonObject &json)
{
    if ( !IJsonable::typeFromJsonObject(json) ||
         !IResponseResultable::resultResponseFromJsonObject(json)
            )
        return;
    JSON_TO_QMAP_QUUID_STRUCT(json, GroupProperties, mGroups);
}

void ResponseListGroups::selfCopy(const ResponseListGroups &obj)
{
    mUidRequest = obj.mUidRequest;
    mResponseResult = obj.mResponseResult;
    mGroups.clear();
    mGroups = obj.mGroups;
}

EDataType ResponseListGroups::type() const
{
    return EDataType::ResponseListGroups;
}

QJsonObject ResponseListGroups::toJsonObject() const
{
    QJsonObject object;
    IJsonable::typeToJsonObject(object);
    IResponseResultable::resultResponseToJsonObject(object);
    QMAP_QUUID_STRUCT_TO_JSON(mGroups, GroupProperties, object);
    return object;
}

bool ResponseListGroups::isValid() const
{
    if (mResponseResult == EResult::None)
        return false;
    else
        return true;
}

// ------------------------------------------------
// ----- RequestAddUserToGroup
// ------------------------------------------------

RequestAddUserToGroup::RequestAddUserToGroup():
    mGroupUid(QUuid()), mUserUid(QUuid())
{

}

RequestAddUserToGroup::RequestAddUserToGroup(const QUuid& groupUid, const QUuid& userUid):
    mGroupUid(groupUid), mUserUid(userUid)
{

}

RequestAddUserToGroup::RequestAddUserToGroup(const RequestAddUserToGroup &obj)
{
    selfCopy(obj);
}

RequestAddUserToGroup &RequestAddUserToGroup::operator =(const RequestAddUserToGroup &obj)
{
    OPERATOR_EQUAL_BODY;
}

RequestAddUserToGroup::RequestAddUserToGroup(const QJsonObject &json)
{
    if ( !IJsonable::typeFromJsonObject(json)
            )
        return;
    if ( !json.contains("mGroupUid") ||
         !json.contains("mUserUid")
         )
        return;
    JSON_TO_QUUID(json, mGroupUid);
    JSON_TO_QUUID(json, mUserUid);
}

void RequestAddUserToGroup::selfCopy(const RequestAddUserToGroup &obj)
{
    mUidRequest = obj.mUidRequest;
    mGroupUid = obj.mGroupUid;
    mUserUid = obj.mUserUid;
}

EDataType RequestAddUserToGroup::type() const
{
  return EDataType::RequestAddUserToGroup;
}

QJsonObject RequestAddUserToGroup::toJsonObject() const
{
    QJsonObject object;
    IJsonable::typeToJsonObject(object);
    QUUID_TO_JSON(mGroupUid, object);
    QUUID_TO_JSON(mUserUid, object);
    return object;
}

bool RequestAddUserToGroup::isValid() const
{
    return !mGroupUid.isNull();
}

// ------------------------------------------------
// ----- ResponseAddUserToGroup
// ------------------------------------------------

ResponseAddUserToGroup::ResponseAddUserToGroup()
{

}

ResponseAddUserToGroup::ResponseAddUserToGroup(const ResponseAddUserToGroup &obj)
{
    selfCopy(obj);
}

ResponseAddUserToGroup &ResponseAddUserToGroup::operator =(const ResponseAddUserToGroup &obj)
{
    OPERATOR_EQUAL_BODY;
}

ResponseAddUserToGroup::ResponseAddUserToGroup(const QJsonObject &json)
{
    if ( !IJsonable::typeFromJsonObject(json) ||
         !IResponseResultable::resultResponseFromJsonObject(json)
            )
        return;
}

void ResponseAddUserToGroup::selfCopy(const ResponseAddUserToGroup &obj)
{
    mUidRequest = obj.mUidRequest;
    mResponseResult = obj.mResponseResult;
}

EDataType ResponseAddUserToGroup::type() const
{
    return EDataType::ResponseAddUserToGroup;
}

QJsonObject ResponseAddUserToGroup::toJsonObject() const
{
    QJsonObject object;
    IJsonable::typeToJsonObject(object);
    IResponseResultable::resultResponseToJsonObject(object);
    return object;
}

bool ResponseAddUserToGroup::isValid() const
{
    if (mResponseResult == EResult::None)
        return false;
    else
        return true;
}

// ------------------------------------------------
// ----- RequestRemoveUserToGroup
// ------------------------------------------------

RequestRemoveUserToGroup::RequestRemoveUserToGroup():
    mGroupUid(QUuid()), mUserUid(QUuid())
{

}

RequestRemoveUserToGroup::RequestRemoveUserToGroup(const QUuid& groupUid, const QUuid& userUid):
    mGroupUid(groupUid), mUserUid(userUid)
{

}

RequestRemoveUserToGroup::RequestRemoveUserToGroup(const RequestRemoveUserToGroup &obj)
{
    selfCopy(obj);
}

RequestRemoveUserToGroup &RequestRemoveUserToGroup::operator =(const RequestRemoveUserToGroup &obj)
{
    OPERATOR_EQUAL_BODY;
}

RequestRemoveUserToGroup::RequestRemoveUserToGroup(const QJsonObject &json)
{
    if ( !IJsonable::typeFromJsonObject(json)
            )
        return;
    if ( !json.contains("mGroupUid") ||
         !json.contains("mUserUid")
         )
        return;
    JSON_TO_QUUID(json, mGroupUid);
    JSON_TO_QUUID(json, mUserUid);
}

void RequestRemoveUserToGroup::selfCopy(const RequestRemoveUserToGroup &obj)
{
    mUidRequest = obj.mUidRequest;
    mGroupUid = obj.mGroupUid;
    mUserUid = obj.mUserUid;
}

EDataType RequestRemoveUserToGroup::type() const
{
  return EDataType::RequestRemoveUserToGroup;
}

QJsonObject RequestRemoveUserToGroup::toJsonObject() const
{
    QJsonObject object;
    IJsonable::typeToJsonObject(object);
    QUUID_TO_JSON(mGroupUid, object);
    QUUID_TO_JSON(mUserUid, object);
    return object;
}

bool RequestRemoveUserToGroup::isValid() const
{
    return !mGroupUid.isNull();
}

// ------------------------------------------------
// ----- ResponseRemoveUserToGroup
// ------------------------------------------------

ResponseRemoveUserToGroup::ResponseRemoveUserToGroup()
{

}

ResponseRemoveUserToGroup::ResponseRemoveUserToGroup(const ResponseRemoveUserToGroup &obj)
{
    selfCopy(obj);
}

ResponseRemoveUserToGroup &ResponseRemoveUserToGroup::operator =(const ResponseRemoveUserToGroup &obj)
{
    OPERATOR_EQUAL_BODY;
}

ResponseRemoveUserToGroup::ResponseRemoveUserToGroup(const QJsonObject &json)
{
    if ( !IJsonable::typeFromJsonObject(json) ||
         !IResponseResultable::resultResponseFromJsonObject(json)
            )
        return;
}

void ResponseRemoveUserToGroup::selfCopy(const ResponseRemoveUserToGroup &obj)
{
    mUidRequest = obj.mUidRequest;
    mResponseResult = obj.mResponseResult;
}

EDataType ResponseRemoveUserToGroup::type() const
{
    return EDataType::ResponseRemoveUserToGroup;
}

QJsonObject ResponseRemoveUserToGroup::toJsonObject() const
{
    QJsonObject object;
    IJsonable::typeToJsonObject(object);
    IResponseResultable::resultResponseToJsonObject(object);
    return object;
}

bool ResponseRemoveUserToGroup::isValid() const
{
    if (mResponseResult == EResult::None)
        return false;
    else
        return true;
}

// ------------------------------------------------
// ----- RequestAddLayout
// ------------------------------------------------

RequestAddLayout::RequestAddLayout():
    mProperties(LayoutProperties())
{

}

RequestAddLayout::RequestAddLayout(const LayoutProperties& properties):
    mProperties(properties)
{

}

RequestAddLayout::RequestAddLayout(const RequestAddLayout &obj)
{
    selfCopy(obj);
}

RequestAddLayout &RequestAddLayout::operator =(const RequestAddLayout &obj)
{
    OPERATOR_EQUAL_BODY;
}

RequestAddLayout::RequestAddLayout(const QJsonObject &json)
{
    if ( !IJsonable::typeFromJsonObject(json)
            )
        return;
    if ( !json.contains("mProperties")
         )
        return;
    JSON_TO_STRUCT(json, LayoutProperties, mProperties);
}

void RequestAddLayout::selfCopy(const RequestAddLayout &obj)
{
    mUidRequest = obj.mUidRequest;
    mProperties = obj.mProperties;
}

EDataType RequestAddLayout::type() const
{
  return EDataType::RequestAddLayout;
}

QJsonObject RequestAddLayout::toJsonObject() const
{
    QJsonObject object;
    IJsonable::typeToJsonObject(object);
    STRUCT_TO_JSON(mProperties, LayoutProperties, object);
    return object;
}

bool RequestAddLayout::isValid() const
{
    return mProperties.isValid();
}

// ------------------------------------------------
// ----- ResponseAddLayout
// ------------------------------------------------

ResponseAddLayout::ResponseAddLayout():
    mLayoutUid(QUuid())
{

}

ResponseAddLayout::ResponseAddLayout(const QUuid& layoutUid):
    mLayoutUid(layoutUid)
{

}

ResponseAddLayout::ResponseAddLayout(const ResponseAddLayout &obj)
{
    selfCopy(obj);
}

ResponseAddLayout &ResponseAddLayout::operator =(const ResponseAddLayout &obj)
{
    OPERATOR_EQUAL_BODY;
}

ResponseAddLayout::ResponseAddLayout(const QJsonObject &json)
{
    if ( !IJsonable::typeFromJsonObject(json) ||
         !IResponseResultable::resultResponseFromJsonObject(json)
            )
        return;
    if ( !json.contains("mLayoutUid")
         )
        return;
    JSON_TO_QUUID(json, mLayoutUid);
}

void ResponseAddLayout::selfCopy(const ResponseAddLayout &obj)
{
    mUidRequest = obj.mUidRequest;
    mResponseResult = obj.mResponseResult;
    mLayoutUid = obj.mLayoutUid;
}

EDataType ResponseAddLayout::type() const
{
    return EDataType::ResponseAddLayout;
}

QJsonObject ResponseAddLayout::toJsonObject() const
{
    QJsonObject object;
    IJsonable::typeToJsonObject(object);
    IResponseResultable::resultResponseToJsonObject(object);
    QUUID_TO_JSON(mLayoutUid, object);
    return object;
}

bool ResponseAddLayout::isValid() const
{
    if (mResponseResult == EResult::None)
        return false;
    else
        return true;
}

// ------------------------------------------------
// ----- RequestRemoveLayout
// ------------------------------------------------

RequestRemoveLayout::RequestRemoveLayout():
    mLayoutUid(QUuid())
{

}

RequestRemoveLayout::RequestRemoveLayout(const QUuid& layoutUid):
    mLayoutUid(layoutUid)
{

}

RequestRemoveLayout::RequestRemoveLayout(const RequestRemoveLayout &obj)
{
    selfCopy(obj);
}

RequestRemoveLayout &RequestRemoveLayout::operator =(const RequestRemoveLayout &obj)
{
    OPERATOR_EQUAL_BODY;
}

RequestRemoveLayout::RequestRemoveLayout(const QJsonObject &json)
{
    if ( !IJsonable::typeFromJsonObject(json)
            )
        return;
    if ( !json.contains("mLayoutUid")
         )
        return;
    JSON_TO_QUUID(json, mLayoutUid);
}

void RequestRemoveLayout::selfCopy(const RequestRemoveLayout &obj)
{
    mUidRequest = obj.mUidRequest;
    mLayoutUid = obj.mLayoutUid;;
}

EDataType RequestRemoveLayout::type() const
{
  return EDataType::RequestRemoveLayout;
}

QJsonObject RequestRemoveLayout::toJsonObject() const
{
    QJsonObject object;
    IJsonable::typeToJsonObject(object);
    QUUID_TO_JSON(mLayoutUid, object);
    return object;
}

bool RequestRemoveLayout::isValid() const
{
    return !mLayoutUid.isNull();
}

// ------------------------------------------------
// ----- ResponseRemoveLayout
// ------------------------------------------------

ResponseRemoveLayout::ResponseRemoveLayout()
{

}

ResponseRemoveLayout::ResponseRemoveLayout(const ResponseRemoveLayout &obj)
{
    selfCopy(obj);
}

ResponseRemoveLayout &ResponseRemoveLayout::operator =(const ResponseRemoveLayout &obj)
{
    OPERATOR_EQUAL_BODY;
}

ResponseRemoveLayout::ResponseRemoveLayout(const QJsonObject &json)
{
    if ( !IJsonable::typeFromJsonObject(json) ||
         !IResponseResultable::resultResponseFromJsonObject(json)
            )
        return;
}

void ResponseRemoveLayout::selfCopy(const ResponseRemoveLayout &obj)
{
    mUidRequest = obj.mUidRequest;
    mResponseResult = obj.mResponseResult;
}

EDataType ResponseRemoveLayout::type() const
{
    return EDataType::ResponseRemoveLayout;
}

QJsonObject ResponseRemoveLayout::toJsonObject() const
{
    QJsonObject object;
    IJsonable::typeToJsonObject(object);
    IResponseResultable::resultResponseToJsonObject(object);
    return object;
}

bool ResponseRemoveLayout::isValid() const
{
    if (mResponseResult == EResult::None)
        return false;
    else
        return true;
}

// ------------------------------------------------
// ----- RequestModifyLayout
// ------------------------------------------------

RequestModifyLayout::RequestModifyLayout():
    mLayoutUid(QUuid()), mProperties(LayoutProperties())
{

}

RequestModifyLayout::RequestModifyLayout(const QUuid& layoutUid, const LayoutProperties& properties):
    mLayoutUid(layoutUid), mProperties(properties)
{

}

RequestModifyLayout::RequestModifyLayout(const RequestModifyLayout &obj)
{
    selfCopy(obj);
}

RequestModifyLayout &RequestModifyLayout::operator =(const RequestModifyLayout &obj)
{
    OPERATOR_EQUAL_BODY;
}

RequestModifyLayout::RequestModifyLayout(const QJsonObject &json)
{
    if ( !IJsonable::typeFromJsonObject(json)
            )
        return;
    if ( !json.contains("mLayoutUid") ||
         !json.contains("mProperties")
         )
        return;
    JSON_TO_QUUID(json, mLayoutUid);
    JSON_TO_STRUCT(json, LayoutProperties, mProperties);
}

void RequestModifyLayout::selfCopy(const RequestModifyLayout &obj)
{
    mUidRequest = obj.mUidRequest;
    mLayoutUid = obj.mLayoutUid;
    mProperties = obj.mProperties;
}

EDataType RequestModifyLayout::type() const
{
  return EDataType::RequestModifyLayout;
}

QJsonObject RequestModifyLayout::toJsonObject() const
{
    QJsonObject object;
    IJsonable::typeToJsonObject(object);
    STRUCT_TO_JSON(mProperties, LayoutProperties, object);
    QUUID_TO_JSON(mLayoutUid, object);
    return object;
}

bool RequestModifyLayout::isValid() const
{
    return !mLayoutUid.isNull();
}

// ------------------------------------------------
// ----- ResponseModifyLayout
// ------------------------------------------------

ResponseModifyLayout::ResponseModifyLayout()
{

}

ResponseModifyLayout::ResponseModifyLayout(const ResponseModifyLayout &obj)
{
    selfCopy(obj);
}

ResponseModifyLayout &ResponseModifyLayout::operator =(const ResponseModifyLayout &obj)
{
    OPERATOR_EQUAL_BODY;
}

ResponseModifyLayout::ResponseModifyLayout(const QJsonObject &json)
{
    if ( !IJsonable::typeFromJsonObject(json) ||
         !IResponseResultable::resultResponseFromJsonObject(json)
            )
        return;
}

void ResponseModifyLayout::selfCopy(const ResponseModifyLayout &obj)
{
    mUidRequest = obj.mUidRequest;
    mResponseResult = obj.mResponseResult;
}

EDataType ResponseModifyLayout::type() const
{
    return EDataType::ResponseModifyLayout;
}

QJsonObject ResponseModifyLayout::toJsonObject() const
{
    QJsonObject object;
    IJsonable::typeToJsonObject(object);
    IResponseResultable::resultResponseToJsonObject(object);
    return object;
}

bool ResponseModifyLayout::isValid() const
{
    if (mResponseResult == EResult::None)
        return false;
    else
        return true;
}

// ------------------------------------------------
// ----- RequestAddProfile
// ------------------------------------------------

RequestAddProfile::RequestAddProfile():
    mProperties(UserProfileProperties())
{

}

RequestAddProfile::RequestAddProfile(const UserProfileProperties& properties):
    mProperties(properties)
{

}

RequestAddProfile::RequestAddProfile(const RequestAddProfile &obj)
{
    selfCopy(obj);
}

RequestAddProfile &RequestAddProfile::operator =(const RequestAddProfile &obj)
{
    OPERATOR_EQUAL_BODY;
}

RequestAddProfile::RequestAddProfile(const QJsonObject &json)
{
    if ( !IJsonable::typeFromJsonObject(json)
            )
        return;
    if ( !json.contains("mProperties")
         )
        return;
    JSON_TO_STRUCT(json, UserProfileProperties, mProperties);
}

void RequestAddProfile::selfCopy(const RequestAddProfile &obj)
{
    mUidRequest = obj.mUidRequest;
    mProperties = obj.mProperties;
}

EDataType RequestAddProfile::type() const
{
  return EDataType::RequestAddProfile;
}

QJsonObject RequestAddProfile::toJsonObject() const
{
    QJsonObject object;
    IJsonable::typeToJsonObject(object);
    STRUCT_TO_JSON(mProperties, UserProfileProperties, object);
    return object;
}

bool RequestAddProfile::isValid() const
{
    return mProperties.isValid();
}

// ------------------------------------------------
// ----- ResponseAddProfile
// ------------------------------------------------

ResponseAddProfile::ResponseAddProfile():
    mProfileUid(QUuid())
{

}

ResponseAddProfile::ResponseAddProfile(const QUuid& profileUid):
    mProfileUid(profileUid)
{

}

ResponseAddProfile::ResponseAddProfile(const ResponseAddProfile &obj)
{
    selfCopy(obj);
}

ResponseAddProfile &ResponseAddProfile::operator =(const ResponseAddProfile &obj)
{
    OPERATOR_EQUAL_BODY;
}

ResponseAddProfile::ResponseAddProfile(const QJsonObject &json)
{
    if ( !IJsonable::typeFromJsonObject(json) ||
         !IResponseResultable::resultResponseFromJsonObject(json)
            )
        return;
    if ( !json.contains("mProfileUid")
         )
        return;
    JSON_TO_QUUID(json, mProfileUid);
}

void ResponseAddProfile::selfCopy(const ResponseAddProfile &obj)
{
    mUidRequest = obj.mUidRequest;
    mResponseResult = obj.mResponseResult;
    mProfileUid = obj.mProfileUid;
}

EDataType ResponseAddProfile::type() const
{
    return EDataType::ResponseAddProfile;
}

QJsonObject ResponseAddProfile::toJsonObject() const
{
    QJsonObject object;
    IJsonable::typeToJsonObject(object);
    IResponseResultable::resultResponseToJsonObject(object);
    QUUID_TO_JSON(mProfileUid, object);
    return object;
}

bool ResponseAddProfile::isValid() const
{
    if (mResponseResult == EResult::None)
        return false;
    else
        return true;
}

// ------------------------------------------------
// ----- RequestRemoveProfile
// ------------------------------------------------

RequestRemoveProfile::RequestRemoveProfile():
    mProfileUid(QUuid())
{

}

RequestRemoveProfile::RequestRemoveProfile(const QUuid& profileUid):
    mProfileUid(profileUid)
{

}

RequestRemoveProfile::RequestRemoveProfile(const RequestRemoveProfile &obj)
{
    selfCopy(obj);
}

RequestRemoveProfile &RequestRemoveProfile::operator =(const RequestRemoveProfile &obj)
{
    OPERATOR_EQUAL_BODY;
}

RequestRemoveProfile::RequestRemoveProfile(const QJsonObject &json)
{
    if ( !IJsonable::typeFromJsonObject(json)
            )
        return;
    if ( !json.contains("mProfileUid")
         )
        return;
    JSON_TO_QUUID(json, mProfileUid);
}

void RequestRemoveProfile::selfCopy(const RequestRemoveProfile &obj)
{
    mUidRequest = obj.mUidRequest;
    mProfileUid = obj.mProfileUid;
}

EDataType RequestRemoveProfile::type() const
{
  return EDataType::RequestRemoveProfile;
}

QJsonObject RequestRemoveProfile::toJsonObject() const
{
    QJsonObject object;
    IJsonable::typeToJsonObject(object);
    QUUID_TO_JSON(mProfileUid, object);
    return object;
}

bool RequestRemoveProfile::isValid() const
{
    return !mProfileUid.isNull();
}

// ------------------------------------------------
// ----- ResponseRemoveProfile
// ------------------------------------------------

ResponseRemoveProfile::ResponseRemoveProfile()
{

}

ResponseRemoveProfile::ResponseRemoveProfile(const ResponseRemoveProfile &obj)
{
    selfCopy(obj);
}

ResponseRemoveProfile &ResponseRemoveProfile::operator =(const ResponseRemoveProfile &obj)
{
    OPERATOR_EQUAL_BODY;
}

ResponseRemoveProfile::ResponseRemoveProfile(const QJsonObject &json)
{
    if ( !IJsonable::typeFromJsonObject(json) ||
         !IResponseResultable::resultResponseFromJsonObject(json)
            )
        return;
}

void ResponseRemoveProfile::selfCopy(const ResponseRemoveProfile &obj)
{
    mUidRequest = obj.mUidRequest;
    mResponseResult = obj.mResponseResult;
}

EDataType ResponseRemoveProfile::type() const
{
    return EDataType::ResponseRemoveProfile;
}

QJsonObject ResponseRemoveProfile::toJsonObject() const
{
    QJsonObject object;
    IJsonable::typeToJsonObject(object);
    IResponseResultable::resultResponseToJsonObject(object);
    return object;
}

bool ResponseRemoveProfile::isValid() const
{
    if (mResponseResult == EResult::None)
        return false;
    else
        return true;
}

// ------------------------------------------------
// ----- RequestAddLayoutItem
// ------------------------------------------------

RequestAddLayoutItem::RequestAddLayoutItem():
    mProperties(LayoutItemProperties())
{

}

RequestAddLayoutItem::RequestAddLayoutItem(const LayoutItemProperties& properties):
    mProperties(properties)
{

}

RequestAddLayoutItem::RequestAddLayoutItem(const RequestAddLayoutItem &obj)
{
    selfCopy(obj);
}

RequestAddLayoutItem &RequestAddLayoutItem::operator =(const RequestAddLayoutItem &obj)
{
    OPERATOR_EQUAL_BODY;
}

RequestAddLayoutItem::RequestAddLayoutItem(const QJsonObject &json)
{
    if ( !IJsonable::typeFromJsonObject(json)
            )
        return;
    if ( !json.contains("mProperties")
         )
        return;
    JSON_TO_STRUCT(json, LayoutItemProperties, mProperties);
}

void RequestAddLayoutItem::selfCopy(const RequestAddLayoutItem &obj)
{
    mUidRequest = obj.mUidRequest;
    mProperties = obj.mProperties;;
}

EDataType RequestAddLayoutItem::type() const
{
  return EDataType::RequestAddLayoutItem;
}

QJsonObject RequestAddLayoutItem::toJsonObject() const
{
    QJsonObject object;
    IJsonable::typeToJsonObject(object);
    STRUCT_TO_JSON(mProperties, LayoutItemProperties, object);
    return object;
}

bool RequestAddLayoutItem::isValid() const
{
    return mProperties.isValid();
}

// ------------------------------------------------
// ----- ResponseAddLayoutItem
// ------------------------------------------------

ResponseAddLayoutItem::ResponseAddLayoutItem():
    mLayoutItemUid(QUuid())
{

}

ResponseAddLayoutItem::ResponseAddLayoutItem(const QUuid& layoutItemUid):
    mLayoutItemUid(layoutItemUid)
{

}

ResponseAddLayoutItem::ResponseAddLayoutItem(const ResponseAddLayoutItem &obj)
{
    selfCopy(obj);
}

ResponseAddLayoutItem &ResponseAddLayoutItem::operator =(const ResponseAddLayoutItem &obj)
{
    OPERATOR_EQUAL_BODY;
}

ResponseAddLayoutItem::ResponseAddLayoutItem(const QJsonObject &json)
{
    if ( !IJsonable::typeFromJsonObject(json) ||
         !IResponseResultable::resultResponseFromJsonObject(json)
            )
        return;
    if ( !json.contains("mLayoutItemUid")
         )
        return;
    JSON_TO_QUUID(json, mLayoutItemUid);
}

void ResponseAddLayoutItem::selfCopy(const ResponseAddLayoutItem &obj)
{
    mUidRequest = obj.mUidRequest;
    mResponseResult = obj.mResponseResult;
    mLayoutItemUid = obj.mLayoutItemUid;
}

EDataType ResponseAddLayoutItem::type() const
{
    return EDataType::ResponseAddLayoutItem;
}

QJsonObject ResponseAddLayoutItem::toJsonObject() const
{
    QJsonObject object;
    IJsonable::typeToJsonObject(object);
    IResponseResultable::resultResponseToJsonObject(object);
    QUUID_TO_JSON(mLayoutItemUid, object);
    return object;
}

bool ResponseAddLayoutItem::isValid() const
{
    if (mResponseResult == EResult::None)
        return false;
    else
        return true;
}

// ------------------------------------------------
// ----- RequestRemoveLayoutItem
// ------------------------------------------------

RequestRemoveLayoutItem::RequestRemoveLayoutItem():
    mLayoutItemUid(QUuid())
{

}

RequestRemoveLayoutItem::RequestRemoveLayoutItem(const QUuid& layoutItemUid):
    mLayoutItemUid(layoutItemUid)
{

}

RequestRemoveLayoutItem::RequestRemoveLayoutItem(const RequestRemoveLayoutItem &obj)
{
    selfCopy(obj);
}

RequestRemoveLayoutItem &RequestRemoveLayoutItem::operator =(const RequestRemoveLayoutItem &obj)
{
    OPERATOR_EQUAL_BODY;
}

RequestRemoveLayoutItem::RequestRemoveLayoutItem(const QJsonObject &json)
{
    if ( !IJsonable::typeFromJsonObject(json)
            )
        return;
    if ( !json.contains("mLayoutItemUid")
         )
        return;
    JSON_TO_QUUID(json, mLayoutItemUid);
}

void RequestRemoveLayoutItem::selfCopy(const RequestRemoveLayoutItem &obj)
{
    mUidRequest = obj.mUidRequest;
    mLayoutItemUid = obj.mLayoutItemUid;;
}

EDataType RequestRemoveLayoutItem::type() const
{
  return EDataType::RequestRemoveLayoutItem;
}

QJsonObject RequestRemoveLayoutItem::toJsonObject() const
{
    QJsonObject object;
    IJsonable::typeToJsonObject(object);
    QUUID_TO_JSON(mLayoutItemUid, object);
    return object;
}

bool RequestRemoveLayoutItem::isValid() const
{
    return !mLayoutItemUid.isNull();
}

// ------------------------------------------------
// ----- ResponseRemoveLayoutItem
// ------------------------------------------------

ResponseRemoveLayoutItem::ResponseRemoveLayoutItem()
{

}

ResponseRemoveLayoutItem::ResponseRemoveLayoutItem(const ResponseRemoveLayoutItem &obj)
{
    selfCopy(obj);
}

ResponseRemoveLayoutItem &ResponseRemoveLayoutItem::operator =(const ResponseRemoveLayoutItem &obj)
{
    OPERATOR_EQUAL_BODY;
}

ResponseRemoveLayoutItem::ResponseRemoveLayoutItem(const QJsonObject &json)
{
    if ( !IJsonable::typeFromJsonObject(json) ||
         !IResponseResultable::resultResponseFromJsonObject(json)
            )
        return;
}

void ResponseRemoveLayoutItem::selfCopy(const ResponseRemoveLayoutItem &obj)
{
    mUidRequest = obj.mUidRequest;
    mResponseResult = obj.mResponseResult;
}

EDataType ResponseRemoveLayoutItem::type() const
{
    return EDataType::ResponseRemoveLayoutItem;
}

QJsonObject ResponseRemoveLayoutItem::toJsonObject() const
{
    QJsonObject object;
    IJsonable::typeToJsonObject(object);
    IResponseResultable::resultResponseToJsonObject(object);
    return object;
}

bool ResponseRemoveLayoutItem::isValid() const
{
    if (mResponseResult == EResult::None)
        return false;
    else
        return true;
}

// ------------------------------------------------
// ----- RequestModifyLayoutItem
// ------------------------------------------------

RequestModifyLayoutItem::RequestModifyLayoutItem():
    mLayoutItemUid(QUuid()), mProperties(LayoutItemProperties())
{

}

RequestModifyLayoutItem::RequestModifyLayoutItem(const QUuid& layoutItemUid, const LayoutItemProperties& properties):
    mLayoutItemUid(layoutItemUid), mProperties(properties)
{

}

RequestModifyLayoutItem::RequestModifyLayoutItem(const RequestModifyLayoutItem &obj)
{
    selfCopy(obj);
}

RequestModifyLayoutItem &RequestModifyLayoutItem::operator =(const RequestModifyLayoutItem &obj)
{
    OPERATOR_EQUAL_BODY;
}

RequestModifyLayoutItem::RequestModifyLayoutItem(const QJsonObject &json)
{
    if ( !IJsonable::typeFromJsonObject(json)
            )
        return;
    if ( !json.contains("mLayoutItemUid") ||
         !json.contains("mProperties")
         )
        return;
    JSON_TO_QUUID(json, mLayoutItemUid);
    JSON_TO_STRUCT(json, LayoutItemProperties, mProperties);
}

void RequestModifyLayoutItem::selfCopy(const RequestModifyLayoutItem &obj)
{
    mUidRequest = obj.mUidRequest;
    mLayoutItemUid = obj.mLayoutItemUid;
    mProperties = obj.mProperties;
}

EDataType RequestModifyLayoutItem::type() const
{
  return EDataType::RequestModifyLayoutItem;
}

QJsonObject RequestModifyLayoutItem::toJsonObject() const
{
    QJsonObject object;
    IJsonable::typeToJsonObject(object);
    STRUCT_TO_JSON(mProperties, LayoutItemProperties, object);
    QUUID_TO_JSON(mLayoutItemUid, object);
    return object;
}

bool RequestModifyLayoutItem::isValid() const
{
    return !mLayoutItemUid.isNull();
}

// ------------------------------------------------
// ----- ResponseModifyLayoutItem
// ------------------------------------------------

ResponseModifyLayoutItem::ResponseModifyLayoutItem()
{

}

ResponseModifyLayoutItem::ResponseModifyLayoutItem(const ResponseModifyLayoutItem &obj)
{
    selfCopy(obj);
}

ResponseModifyLayoutItem &ResponseModifyLayoutItem::operator =(const ResponseModifyLayoutItem &obj)
{
    OPERATOR_EQUAL_BODY;
}

ResponseModifyLayoutItem::ResponseModifyLayoutItem(const QJsonObject &json)
{
    if ( !IJsonable::typeFromJsonObject(json) ||
         !IResponseResultable::resultResponseFromJsonObject(json)
            )
        return;
}

void ResponseModifyLayoutItem::selfCopy(const ResponseModifyLayoutItem &obj)
{
    mUidRequest = obj.mUidRequest;
    mResponseResult = obj.mResponseResult;
}

EDataType ResponseModifyLayoutItem::type() const
{
    return EDataType::ResponseModifyLayoutItem;
}

QJsonObject ResponseModifyLayoutItem::toJsonObject() const
{
    QJsonObject object;
    IJsonable::typeToJsonObject(object);
    IResponseResultable::resultResponseToJsonObject(object);
    return object;
}

bool ResponseModifyLayoutItem::isValid() const
{
    if (mResponseResult == EResult::None)
        return false;
    else
        return true;
}

// ------------------------------------------------
// ----- RequestAddProfileItem
// ------------------------------------------------

RequestAddProfileItem::RequestAddProfileItem():
    mProperties(ProfileItemProperties())
{

}

RequestAddProfileItem::RequestAddProfileItem(const ProfileItemProperties& properties):
    mProperties(properties)
{

}

RequestAddProfileItem::RequestAddProfileItem(const RequestAddProfileItem &obj)
{
    selfCopy(obj);
}

RequestAddProfileItem &RequestAddProfileItem::operator =(const RequestAddProfileItem &obj)
{
    OPERATOR_EQUAL_BODY;
}

RequestAddProfileItem::RequestAddProfileItem(const QJsonObject &json)
{
    if ( !IJsonable::typeFromJsonObject(json)
            )
        return;
    if ( !json.contains("mProperties")
         )
        return;
    JSON_TO_STRUCT(json, ProfileItemProperties, mProperties);
}

void RequestAddProfileItem::selfCopy(const RequestAddProfileItem &obj)
{
    mUidRequest = obj.mUidRequest;
    mProperties = obj.mProperties;
}

EDataType RequestAddProfileItem::type() const
{
  return EDataType::RequestAddProfileItem;
}

QJsonObject RequestAddProfileItem::toJsonObject() const
{
    QJsonObject object;
    IJsonable::typeToJsonObject(object);
    STRUCT_TO_JSON(mProperties, ProfileItemProperties, object);
    return object;
}

bool RequestAddProfileItem::isValid() const
{
    return mProperties.isValid();
}

// ------------------------------------------------
// ----- ResponseAddProfileItem
// ------------------------------------------------

ResponseAddProfileItem::ResponseAddProfileItem():
    mProfileItemUid(QUuid())
{

}

ResponseAddProfileItem::ResponseAddProfileItem(const QUuid& profileItemUid):
    mProfileItemUid(profileItemUid)
{

}

ResponseAddProfileItem::ResponseAddProfileItem(const ResponseAddProfileItem &obj)
{
    selfCopy(obj);
}

ResponseAddProfileItem &ResponseAddProfileItem::operator =(const ResponseAddProfileItem &obj)
{
    OPERATOR_EQUAL_BODY;
}

ResponseAddProfileItem::ResponseAddProfileItem(const QJsonObject &json)
{
    if ( !IJsonable::typeFromJsonObject(json) ||
         !IResponseResultable::resultResponseFromJsonObject(json)
            )
        return;
    if ( !json.contains("mProfileItemUid")
         )
        return;
    JSON_TO_QUUID(json, mProfileItemUid);
}

void ResponseAddProfileItem::selfCopy(const ResponseAddProfileItem &obj)
{
    mUidRequest = obj.mUidRequest;
    mResponseResult = obj.mResponseResult;
    mProfileItemUid = obj.mProfileItemUid;
}

EDataType ResponseAddProfileItem::type() const
{
    return EDataType::ResponseAddProfileItem;
}

QJsonObject ResponseAddProfileItem::toJsonObject() const
{
    QJsonObject object;
    IJsonable::typeToJsonObject(object);
    IResponseResultable::resultResponseToJsonObject(object);
    QUUID_TO_JSON(mProfileItemUid, object);
    return object;
}

bool ResponseAddProfileItem::isValid() const
{
    if (mResponseResult == EResult::None)
        return false;
    else
        return true;
}

// ------------------------------------------------
// ----- RequestRemoveProfileItem
// ------------------------------------------------

RequestRemoveProfileItem::RequestRemoveProfileItem():
    mProfileItemUid(QUuid())
{

}

RequestRemoveProfileItem::RequestRemoveProfileItem(const QUuid& profileItemUid):
    mProfileItemUid(profileItemUid)
{

}

RequestRemoveProfileItem::RequestRemoveProfileItem(const RequestRemoveProfileItem &obj)
{
    selfCopy(obj);
}

RequestRemoveProfileItem &RequestRemoveProfileItem::operator =(const RequestRemoveProfileItem &obj)
{
    OPERATOR_EQUAL_BODY;
}

RequestRemoveProfileItem::RequestRemoveProfileItem(const QJsonObject &json)
{
    if ( !IJsonable::typeFromJsonObject(json)
            )
        return;
    if ( !json.contains("mProfileItemUid")
         )
        return;
    JSON_TO_QUUID(json, mProfileItemUid);
}

void RequestRemoveProfileItem::selfCopy(const RequestRemoveProfileItem &obj)
{
    mUidRequest = obj.mUidRequest;
    mProfileItemUid = obj.mProfileItemUid;
}

EDataType RequestRemoveProfileItem::type() const
{
  return EDataType::RequestRemoveProfileItem;
}

QJsonObject RequestRemoveProfileItem::toJsonObject() const
{
    QJsonObject object;
    IJsonable::typeToJsonObject(object);
    QUUID_TO_JSON(mProfileItemUid, object);
    return object;
}

bool RequestRemoveProfileItem::isValid() const
{
    return !mProfileItemUid.isNull();
}

// ------------------------------------------------
// ----- ResponseRemoveProfileItem
// ------------------------------------------------

ResponseRemoveProfileItem::ResponseRemoveProfileItem()
{

}

ResponseRemoveProfileItem::ResponseRemoveProfileItem(const ResponseRemoveProfileItem &obj)
{
    selfCopy(obj);
}

ResponseRemoveProfileItem &ResponseRemoveProfileItem::operator =(const ResponseRemoveProfileItem &obj)
{
    OPERATOR_EQUAL_BODY;
}

ResponseRemoveProfileItem::ResponseRemoveProfileItem(const QJsonObject &json)
{
    if ( !IJsonable::typeFromJsonObject(json) ||
         !IResponseResultable::resultResponseFromJsonObject(json)
            )
        return;
}

void ResponseRemoveProfileItem::selfCopy(const ResponseRemoveProfileItem &obj)
{
    mUidRequest = obj.mUidRequest;
    mResponseResult = obj.mResponseResult;
}

EDataType ResponseRemoveProfileItem::type() const
{
    return EDataType::ResponseRemoveProfileItem;
}

QJsonObject ResponseRemoveProfileItem::toJsonObject() const
{
    QJsonObject object;
    IJsonable::typeToJsonObject(object);
    IResponseResultable::resultResponseToJsonObject(object);
    return object;
}

bool ResponseRemoveProfileItem::isValid() const
{
    if (mResponseResult == EResult::None)
        return false;
    else
        return true;
}

// ------------------------------------------------
// ----- RequestProfileItemListByProfile
// ------------------------------------------------

RequestProfileItemListByProfile::RequestProfileItemListByProfile():
    mProfileUid(QUuid())
{

}

RequestProfileItemListByProfile::RequestProfileItemListByProfile(const QUuid& profileUid):
    mProfileUid(profileUid)
{

}

RequestProfileItemListByProfile::RequestProfileItemListByProfile(const RequestProfileItemListByProfile &obj)
{
    selfCopy(obj);
}

RequestProfileItemListByProfile &RequestProfileItemListByProfile::operator =(const RequestProfileItemListByProfile &obj)
{
    OPERATOR_EQUAL_BODY;
}

RequestProfileItemListByProfile::RequestProfileItemListByProfile(const QJsonObject &json)
{
    if ( !IJsonable::typeFromJsonObject(json)
            )
        return;
    if ( !json.contains("mProfileUid")
         )
        return;
    JSON_TO_QUUID(json, mProfileUid);
}

void RequestProfileItemListByProfile::selfCopy(const RequestProfileItemListByProfile &obj)
{
    mUidRequest = obj.mUidRequest;
    mProfileUid = obj.mProfileUid;
}

EDataType RequestProfileItemListByProfile::type() const
{
  return EDataType::RequestProfileItemListByProfile;
}

QJsonObject RequestProfileItemListByProfile::toJsonObject() const
{
    QJsonObject object;
    IJsonable::typeToJsonObject(object);
    QUUID_TO_JSON(mProfileUid, object);
    return object;
}

bool RequestProfileItemListByProfile::isValid() const
{
    return true;
}

// ------------------------------------------------
// ----- ResponseProfileItemListByProfile
// ------------------------------------------------

ResponseProfileItemListByProfile::ResponseProfileItemListByProfile()
{

}

ResponseProfileItemListByProfile::ResponseProfileItemListByProfile(const ResponseProfileItemListByProfile &obj)
{
    selfCopy(obj);
}

ResponseProfileItemListByProfile &ResponseProfileItemListByProfile::operator =(const ResponseProfileItemListByProfile &obj)
{
    OPERATOR_EQUAL_BODY;
}

ResponseProfileItemListByProfile::ResponseProfileItemListByProfile(const QJsonObject &json)
{
    if ( !IJsonable::typeFromJsonObject(json) ||
         !IResponseResultable::resultResponseFromJsonObject(json)
            )
        return;
    JSON_TO_QMAP_QUUID_STRUCT(json, ProfileItemProperties, mProfileItems);
}

void ResponseProfileItemListByProfile::selfCopy(const ResponseProfileItemListByProfile &obj)
{
    mUidRequest = obj.mUidRequest;
    mResponseResult = obj.mResponseResult;
    mProfileItems.clear();
    mProfileItems = obj.mProfileItems;
}

EDataType ResponseProfileItemListByProfile::type() const
{
    return EDataType::ResponseProfileItemListByProfile;
}

QJsonObject ResponseProfileItemListByProfile::toJsonObject() const
{
    QJsonObject object;
    IJsonable::typeToJsonObject(object);
    IResponseResultable::resultResponseToJsonObject(object);
    QMAP_QUUID_STRUCT_TO_JSON(mProfileItems, ProfileItemProperties, object);
    return object;
}

bool ResponseProfileItemListByProfile::isValid() const
{
    if (mResponseResult == EResult::None)
        return false;
    else
        return true;
}

// ------------------------------------------------
// ----- RequestLayoutListByUser
// ------------------------------------------------

RequestLayoutListByUser::RequestLayoutListByUser():
    mUserUid(QUuid())
{

}

RequestLayoutListByUser::RequestLayoutListByUser(const QUuid& userUid):
    mUserUid(userUid)
{

}

RequestLayoutListByUser::RequestLayoutListByUser(const RequestLayoutListByUser &obj)
{
    selfCopy(obj);
}

RequestLayoutListByUser &RequestLayoutListByUser::operator =(const RequestLayoutListByUser &obj)
{
    OPERATOR_EQUAL_BODY;
}

RequestLayoutListByUser::RequestLayoutListByUser(const QJsonObject &json)
{
    if ( !IJsonable::typeFromJsonObject(json)
            )
        return;
    if ( !json.contains("mUserUid")
         )
        return;
    JSON_TO_QUUID(json, mUserUid);
}

void RequestLayoutListByUser::selfCopy(const RequestLayoutListByUser &obj)
{
    mUidRequest = obj.mUidRequest;
    mUserUid = obj.mUserUid;;
}

EDataType RequestLayoutListByUser::type() const
{
  return EDataType::RequestLayoutListByUser;
}

QJsonObject RequestLayoutListByUser::toJsonObject() const
{
    QJsonObject object;
    IJsonable::typeToJsonObject(object);
    QUUID_TO_JSON(mUserUid, object);
    return object;
}

bool RequestLayoutListByUser::isValid() const
{
    return !mUserUid.isNull();
}

// ------------------------------------------------
// ----- ResponseLayoutListByUser
// ------------------------------------------------

ResponseLayoutListByUser::ResponseLayoutListByUser()
{

}

ResponseLayoutListByUser::ResponseLayoutListByUser(const ResponseLayoutListByUser &obj)
{
    selfCopy(obj);
}

ResponseLayoutListByUser &ResponseLayoutListByUser::operator =(const ResponseLayoutListByUser &obj)
{
    OPERATOR_EQUAL_BODY;
}

ResponseLayoutListByUser::ResponseLayoutListByUser(const QJsonObject &json)
{
    if ( !IJsonable::typeFromJsonObject(json) ||
         !IResponseResultable::resultResponseFromJsonObject(json)
            )
        return;
    JSON_TO_QMAP_QUUID_STRUCT(json, LayoutProperties, mLayouts);
}

void ResponseLayoutListByUser::selfCopy(const ResponseLayoutListByUser &obj)
{
    mUidRequest = obj.mUidRequest;
    mResponseResult = obj.mResponseResult;
    mLayouts.clear();
    mLayouts = obj.mLayouts;
}

EDataType ResponseLayoutListByUser::type() const
{
    return EDataType::ResponseLayoutListByUser;
}

QJsonObject ResponseLayoutListByUser::toJsonObject() const
{
    QJsonObject object;
    IJsonable::typeToJsonObject(object);
    IResponseResultable::resultResponseToJsonObject(object);
    QMAP_QUUID_STRUCT_TO_JSON(mLayouts, LayoutProperties, object);
    return object;
}

bool ResponseLayoutListByUser::isValid() const
{
    if (mResponseResult == EResult::None)
        return false;
    else
        return true;
}

// ------------------------------------------------
// ----- RequestLayoutItemListByLayout
// ------------------------------------------------

RequestLayoutItemListByLayout::RequestLayoutItemListByLayout():
    mLayoutUid(QUuid())
{

}

RequestLayoutItemListByLayout::RequestLayoutItemListByLayout(const QUuid& layoutUid):
    mLayoutUid(layoutUid)
{

}

RequestLayoutItemListByLayout::RequestLayoutItemListByLayout(const RequestLayoutItemListByLayout &obj)
{
    selfCopy(obj);
}

RequestLayoutItemListByLayout &RequestLayoutItemListByLayout::operator =(const RequestLayoutItemListByLayout &obj)
{
    OPERATOR_EQUAL_BODY;
}

RequestLayoutItemListByLayout::RequestLayoutItemListByLayout(const QJsonObject &json)
{
    if ( !IJsonable::typeFromJsonObject(json)
            )
        return;
    if ( !json.contains("mLayoutUid")
         )
        return;
    JSON_TO_QUUID(json, mLayoutUid);
}

void RequestLayoutItemListByLayout::selfCopy(const RequestLayoutItemListByLayout &obj)
{
    mUidRequest = obj.mUidRequest;
    mLayoutUid = obj.mLayoutUid;
}

EDataType RequestLayoutItemListByLayout::type() const
{
  return EDataType::RequestLayoutItemListByLayout;
}

QJsonObject RequestLayoutItemListByLayout::toJsonObject() const
{
    QJsonObject object;
    IJsonable::typeToJsonObject(object);
    QUUID_TO_JSON(mLayoutUid, object);
    return object;
}

bool RequestLayoutItemListByLayout::isValid() const
{
    return !mLayoutUid.isNull();
}

// ------------------------------------------------
// ----- ResponseLayoutItemListByLayout
// ------------------------------------------------

ResponseLayoutItemListByLayout::ResponseLayoutItemListByLayout()
{

}

ResponseLayoutItemListByLayout::ResponseLayoutItemListByLayout(const ResponseLayoutItemListByLayout &obj)
{
    selfCopy(obj);
}

ResponseLayoutItemListByLayout &ResponseLayoutItemListByLayout::operator =(const ResponseLayoutItemListByLayout &obj)
{
    OPERATOR_EQUAL_BODY;
}

ResponseLayoutItemListByLayout::ResponseLayoutItemListByLayout(const QJsonObject &json)
{
    if ( !IJsonable::typeFromJsonObject(json) ||
         !IResponseResultable::resultResponseFromJsonObject(json)
            )
        return;
    JSON_TO_QMAP_QUUID_STRUCT(json, LayoutItemProperties, mLayoutItems);
}

void ResponseLayoutItemListByLayout::selfCopy(const ResponseLayoutItemListByLayout &obj)
{
    mResponseResult = obj.mResponseResult;
    mLayoutItems.clear();
    mLayoutItems = obj.mLayoutItems;
}

EDataType ResponseLayoutItemListByLayout::type() const
{
    return EDataType::ResponseLayoutItemListByLayout;
}

QJsonObject ResponseLayoutItemListByLayout::toJsonObject() const
{
    QJsonObject object;
    IJsonable::typeToJsonObject(object);
    IResponseResultable::resultResponseToJsonObject(object);
    QMAP_QUUID_STRUCT_TO_JSON(mLayoutItems, LayoutItemProperties, object);
    return object;
}

bool ResponseLayoutItemListByLayout::isValid() const
{
    if (mResponseResult == EResult::None)
        return false;
    else
        return true;
}

*/

QString userRoleName(const EUserRole &role)
{
    QString res;
    switch(role){
    case EUserRole::Observation:res=QObject::tr("Наблюдение"); break;    ///< наблюдение
    case EUserRole::Analytics:res=QObject::tr("Аналитика");break;       ///< аналитика
    case EUserRole::Administration:res=QObject::tr("Администрирование");break;  ///< администрирование
    case EUserRole::Security:res=QObject::tr("Безопасность");break;  ///< безопасность
    default:break;
    }
    return res;
}

// ------------------------------------------------
// ----- RequestLicence
// ------------------------------------------------

RequestLicence::RequestLicence():IJsonable(), ICommonFields()
{

}

RequestLicence::RequestLicence(const RequestLicence &obj):IJsonable(), ICommonFields()
{
    selfCopy(obj);
}

RequestLicence &RequestLicence::operator =(const RequestLicence &obj)
{
    OPERATOR_EQUAL_BODY;
}

RequestLicence::RequestLicence(const QJsonObject &json)
{
    if ( !IJsonable::typeFromJsonObject(json)
            )
        return;
    ICommonFields::fromJsonObject(json);
    JSON_TO_QSTRING(json, licenceFileData);
    JSON_TO_QUUID(json, trueClientUid);
}

void RequestLicence::selfCopy(const RequestLicence &obj)
{
    mUidRequest = obj.mUidRequest;
    licenceFileData = obj.licenceFileData;
    trueClientUid = obj.trueClientUid;
}

EDataType RequestLicence::type() const
{
    return EDataType::RequestLicence;
}

QJsonObject RequestLicence::toJsonObject() const
{
    QJsonObject object;
    ICommonFields::toJsonObject(object);
    IJsonable::typeToJsonObject(object);
    QSTRING_TO_JSON(licenceFileData, object);
    QUUID_TO_JSON(trueClientUid, object);
    return object;
}

bool RequestLicence::isValid() const
{
    return true;
}

// ------------------------------------------------
// ----- ResponseLicence
// ------------------------------------------------

ResponseLicence::ResponseLicence(): IJsonable(), ICommonFields(), IResponseResultable()
{

}

ResponseLicence::ResponseLicence(const ResponseLicence &obj): IJsonable(), ICommonFields(), IResponseResultable()
{
    selfCopy(obj);
}

ResponseLicence &ResponseLicence::operator =(const ResponseLicence &obj)
{
    OPERATOR_EQUAL_BODY;
}

ResponseLicence::ResponseLicence(const QJsonObject &json)
{
    if ( !IJsonable::typeFromJsonObject(json) ||
         !IResponseResultable::resultResponseFromJsonObject(json)
            )
        return;
    ICommonFields::fromJsonObject(json);
//    JSON_TO_QVECTOR_STRUCT(json, LicenceProperties, mLicence);

    if (json.contains("mLicence")) {
        auto _items = json.value("mLicence");
        if (_items.isArray()) {
            auto _itemsArray = _items.toArray();
            if (!_itemsArray.isEmpty()) {
                foreach (QJsonValue _value, _itemsArray) {
                    LicenceProperties _item(_value.toObject());
                    mLicence.append( _item );
                }
            }
        }
    }
    if (mLicence.length() > 0)
        mLicence.append(mLicence[0]);
}

void ResponseLicence::selfCopy(const ResponseLicence &obj)
{
    mUidRequest = obj.mUidRequest;
    mResponseResult = obj.mResponseResult;
//    mLicence.clear();
    mLicence = obj.mLicence;
}

EDataType ResponseLicence::type() const
{
    return EDataType::ResponseLicence;
}

QJsonObject ResponseLicence::toJsonObject() const
{
    QJsonObject object;
    ICommonFields::toJsonObject(object);
    IJsonable::typeToJsonObject(object);
    IResponseResultable::resultResponseToJsonObject(object);
    QVECTOR_STRUCT_TO_JSON(mLicence, LicenceProperties, object);
    return object;
}

bool ResponseLicence::isValid() const
{
    if (mResponseResult == EResult::None)
        return false;
    else
        return true;
}

// ------------------------------------------------
// ----- RequestLicenceThroughCs
// ------------------------------------------------

RequestLicenceThroughCs::RequestLicenceThroughCs() : IJsonable(), ICommonFields()
{

}

RequestLicenceThroughCs::RequestLicenceThroughCs(const RequestLicenceThroughCs &obj) : IJsonable(), ICommonFields()
{
    selfCopy(obj);
}

RequestLicenceThroughCs &RequestLicenceThroughCs::operator =(const RequestLicenceThroughCs &obj)
{
    OPERATOR_EQUAL_BODY;
}

RequestLicenceThroughCs::RequestLicenceThroughCs(const QJsonObject &json)
{
    if ( !IJsonable::typeFromJsonObject(json)
            )
        return;
    ICommonFields::fromJsonObject(json);
    JSON_TO_QSTRING(json, ip);
    JSON_TO_INT(json, port);
}

void RequestLicenceThroughCs::selfCopy(const RequestLicenceThroughCs &obj)
{
    mUidRequest = obj.mUidRequest;
    ip = obj.ip;
    port = obj.port;
}

EDataType RequestLicenceThroughCs::type() const
{
    return EDataType::RequestLicenceThroughCs;
}

QJsonObject RequestLicenceThroughCs::toJsonObject() const
{
    QJsonObject object;
    ICommonFields::toJsonObject(object);
    IJsonable::typeToJsonObject(object);
    QSTRING_TO_JSON(ip, object);
    INT_TO_JSON(port, object);
    return object;
}

bool RequestLicenceThroughCs::isValid() const
{
    return !QHostAddress(ip).isNull();
}

// ------------------------------------------------
// ----- ResponseLicenceThroughCs
// ------------------------------------------------

ResponseLicenceThroughCs::ResponseLicenceThroughCs() : IJsonable(), ICommonFields(), IResponseResultable()
{

}

ResponseLicenceThroughCs::ResponseLicenceThroughCs(const ResponseLicenceThroughCs &obj) : IJsonable(), ICommonFields(), IResponseResultable()
{
    selfCopy(obj);
}

ResponseLicenceThroughCs &ResponseLicenceThroughCs::operator =(const ResponseLicenceThroughCs &obj)
{
    OPERATOR_EQUAL_BODY;
}

ResponseLicenceThroughCs::ResponseLicenceThroughCs(const QJsonObject &json)
{
//    if (json.contains("mLicence")) {
//        auto _item = json.value("mLicence");
//        LicenceProperties _value(_item.toObject());
//        mLicence = _value;
//    }
    JSON_TO_STRUCT(json, LicenceProperties, mLicence);
}

void ResponseLicenceThroughCs::selfCopy(const ResponseLicenceThroughCs &obj)
{
    mUidRequest = obj.mUidRequest;
    mResponseResult = obj.mResponseResult;
    mLicence = obj.mLicence;
}

EDataType ResponseLicenceThroughCs::type() const
{
    return EDataType::ResponseLicenceThroughCs;
}

QJsonObject ResponseLicenceThroughCs::toJsonObject() const
{
    QJsonObject object;
    ICommonFields::toJsonObject(object);
    IJsonable::typeToJsonObject(object);
    IResponseResultable::resultResponseToJsonObject(object);
    STRUCT_TO_JSON(mLicence, LicenceProperties, object);
    return object;
}

bool ResponseLicenceThroughCs::isValid() const
{
    if (mResponseResult == EResult::None)
        return false;
    else
        return true;
}

// RequestHeartbeat

RequestHeartbeat::RequestHeartbeat():IJsonable(), ICommonFields()
{

}

RequestHeartbeat &RequestHeartbeat::operator =(const RequestHeartbeat &obj)
{
    OPERATOR_EQUAL_BODY;
}

RequestHeartbeat::RequestHeartbeat(const RequestHeartbeat &obj):IJsonable(), ICommonFields()
{
    selfCopy(obj);
}

RequestHeartbeat::RequestHeartbeat(const QJsonObject &json)
{
    if ( !IJsonable::typeFromJsonObject(json)
         )
        return;
    ICommonFields::fromJsonObject(json);
}

void RequestHeartbeat::selfCopy(const RequestHeartbeat &obj)
{
    mUidRequest = obj.mUidRequest;
}

EDataType RequestHeartbeat::type() const
{
    return EDataType::RequestHeartbeat;
}

QJsonObject RequestHeartbeat::toJsonObject() const
{
    QJsonObject object;
    ICommonFields::toJsonObject(object);
    IJsonable::typeToJsonObject(object);
    return object;
}

bool RequestHeartbeat::isValid() const
{
    return true;
}

// ------------------------------------------------
// ----- RequestGetClients
// ------------------------------------------------

RequestGetClients::RequestGetClients():IJsonable(), ICommonFields()
{

}

RequestGetClients::RequestGetClients(const RequestGetClients &obj):IJsonable(), ICommonFields()
{
    selfCopy(obj);
}

RequestGetClients &RequestGetClients::operator =(const RequestGetClients &obj)
{
    OPERATOR_EQUAL_BODY;
}

RequestGetClients::RequestGetClients(const QJsonObject &json)
{
    if ( !IJsonable::typeFromJsonObject(json)
            )
        return;
    ICommonFields::fromJsonObject(json);
}

void RequestGetClients::selfCopy(const RequestGetClients &obj)
{
    mUidRequest = obj.mUidRequest;
}

EDataType RequestGetClients::type() const
{
    return EDataType::RequestGetClients;
}

QJsonObject RequestGetClients::toJsonObject() const
{
    QJsonObject object;
    ICommonFields::toJsonObject(object);
    IJsonable::typeToJsonObject(object);
    return object;
}

bool RequestGetClients::isValid() const
{
    return true;
}

// ------------------------------------------------
// ----- ResponseGetClients
// ------------------------------------------------

ResponseGetClients::ResponseGetClients():IJsonable(), ICommonFields(), IResponseResultable()
{

}

ResponseGetClients::ResponseGetClients(const ResponseGetClients &obj):IJsonable(), ICommonFields(), IResponseResultable()
{
    selfCopy(obj);
}

ResponseGetClients &ResponseGetClients::operator =(const ResponseGetClients &obj)
{
    OPERATOR_EQUAL_BODY;
}

ResponseGetClients::ResponseGetClients(const QJsonObject &json)
{
    if ( !IJsonable::typeFromJsonObject(json) ||
         !IResponseResultable::resultResponseFromJsonObject(json)
            )
        return;
    if ( !json.contains("mClients")
         )
        return;
    ICommonFields::fromJsonObject(json);
    JSON_TO_QMAP_QUUID_STRUCT(json, ClientProperties, mClients);
}

void ResponseGetClients::selfCopy(const ResponseGetClients &obj)
{
    mUidRequest = obj.mUidRequest;
    mClients = obj.mClients;
    mResponseResult = obj.mResponseResult;
}

EDataType ResponseGetClients::type() const
{
    return EDataType::ResponseGetClients;
}

QJsonObject ResponseGetClients::toJsonObject() const
{
    QJsonObject object;
    ICommonFields::toJsonObject(object);
    IJsonable::typeToJsonObject(object);
    IResponseResultable::resultResponseToJsonObject(object);
    QMAP_QUUID_STRUCT_TO_JSON(mClients, ClientProperties, object);
    return object;
}

bool ResponseGetClients::isValid() const
{
    return true;
}

// ------------------------------------------------
// ----- RequestKickClient
// ------------------------------------------------

RequestKickClient::RequestKickClient():IJsonable(), ICommonFields(), mClientUid(QUuid())
{

}

RequestKickClient::RequestKickClient(const RequestKickClient &obj):IJsonable(), ICommonFields()
{
    selfCopy(obj);
}

RequestKickClient &RequestKickClient::operator =(const RequestKickClient &obj)
{
    OPERATOR_EQUAL_BODY;
}

RequestKickClient::RequestKickClient(const QJsonObject &json)
{
    if ( !IJsonable::typeFromJsonObject(json)
            )
        return;
    if ( !json.contains("mClientUid")
         )
        return;
    ICommonFields::fromJsonObject(json);
    JSON_TO_QUUID(json, mClientUid);
}

void RequestKickClient::selfCopy(const RequestKickClient &obj)
{
    mUidRequest = obj.mUidRequest;
    mClientUid = obj.mClientUid;
}

EDataType RequestKickClient::type() const
{
    return EDataType::RequestKickClient;
}

QJsonObject RequestKickClient::toJsonObject() const
{
    QJsonObject object;
    ICommonFields::toJsonObject(object);
    IJsonable::typeToJsonObject(object);
    QUUID_TO_JSON(mClientUid, object);
    return object;
}

bool RequestKickClient::isValid() const
{
    return true;
}

// ------------------------------------------------
// ----- ResponseKickClient
// ------------------------------------------------

ResponseKickClient::ResponseKickClient():IJsonable(), ICommonFields(), IResponseResultable()
{

}

ResponseKickClient::ResponseKickClient(const ResponseKickClient &obj):IJsonable(), ICommonFields(), IResponseResultable()
{
    selfCopy(obj);
}

ResponseKickClient &ResponseKickClient::operator =(const ResponseKickClient &obj)
{
    OPERATOR_EQUAL_BODY;
}

ResponseKickClient::ResponseKickClient(const QJsonObject &json)
{
    if ( !IJsonable::typeFromJsonObject(json) ||
         !IResponseResultable::resultResponseFromJsonObject(json)
            )
        return;
    ICommonFields::fromJsonObject(json);
}

void ResponseKickClient::selfCopy(const ResponseKickClient &obj)
{
    mUidRequest = obj.mUidRequest;
    mResponseResult = obj.mResponseResult;
}

EDataType ResponseKickClient::type() const
{
    return EDataType::ResponseKickClient;
}

QJsonObject ResponseKickClient::toJsonObject() const
{
    QJsonObject object;
    ICommonFields::toJsonObject(object);
    IJsonable::typeToJsonObject(object);
    IResponseResultable::resultResponseToJsonObject(object);
    return object;
}

bool ResponseKickClient::isValid() const
{
    return true;
}

// ------------------------------------------------
// ----- RequestKickselfToClient
// ------------------------------------------------

RequestKickselfToClient::RequestKickselfToClient():IJsonable(), ICommonFields()
{

}

RequestKickselfToClient::RequestKickselfToClient(const RequestKickselfToClient &obj):IJsonable(), ICommonFields()
{
    selfCopy(obj);
}

RequestKickselfToClient &RequestKickselfToClient::operator =(const RequestKickselfToClient &obj)
{
    OPERATOR_EQUAL_BODY;
}

RequestKickselfToClient::RequestKickselfToClient(const QJsonObject &json)
{
    if ( !IJsonable::typeFromJsonObject(json)
            )
        return;
    ICommonFields::fromJsonObject(json);
}

void RequestKickselfToClient::selfCopy(const RequestKickselfToClient &obj)
{
    mUidRequest = obj.mUidRequest;
}

EDataType RequestKickselfToClient::type() const
{
    return EDataType::RequestKickselfToClient;
}

QJsonObject RequestKickselfToClient::toJsonObject() const
{
    QJsonObject object;
    ICommonFields::toJsonObject(object);
    IJsonable::typeToJsonObject(object);
    return object;
}

bool RequestKickselfToClient::isValid() const
{
    return true;
}





// ------------------------------------------------
// ----- RequestCopyVideoFileToTmp
// ------------------------------------------------

RequestCopyVideoFileToTmp::RequestCopyVideoFileToTmp():IJsonable(), ICommonFields()
{

}

RequestCopyVideoFileToTmp::RequestCopyVideoFileToTmp(const RequestCopyVideoFileToTmp &obj):IJsonable(), ICommonFields()
{
    selfCopy(obj);
}

RequestCopyVideoFileToTmp &RequestCopyVideoFileToTmp::operator =(const RequestCopyVideoFileToTmp &obj)
{
    OPERATOR_EQUAL_BODY;
}

RequestCopyVideoFileToTmp::RequestCopyVideoFileToTmp(const QJsonObject &json)
{
    if ( !IJsonable::typeFromJsonObject(json) )
        return;
    if ( !json.contains("mVideoFilePath") )
        return;
    ICommonFields::fromJsonObject(json);
    JSON_TO_QSTRING(json, mVideoFilePath);
}

void RequestCopyVideoFileToTmp::selfCopy(const RequestCopyVideoFileToTmp &obj)
{
    mUidRequest = obj.mUidRequest;
    mVideoFilePath = obj.mVideoFilePath;
}

EDataType RequestCopyVideoFileToTmp::type() const
{
    return EDataType::RequestCopyVideoFileToTmp;
}

QJsonObject RequestCopyVideoFileToTmp::toJsonObject() const
{
    QJsonObject object;
    ICommonFields::toJsonObject(object);
    IJsonable::typeToJsonObject(object);
    QSTRING_TO_JSON(mVideoFilePath, object);
    return object;
}

bool RequestCopyVideoFileToTmp::isValid() const
{
    return true;
}

// ------------------------------------------------
// ----- ResponseCopyVideoFileToTmp
// ------------------------------------------------

ResponseCopyVideoFileToTmp::ResponseCopyVideoFileToTmp():IJsonable(), ICommonFields(), IResponseResultable()
{

}

ResponseCopyVideoFileToTmp::ResponseCopyVideoFileToTmp(const ResponseCopyVideoFileToTmp &obj):IJsonable(), ICommonFields(), IResponseResultable()
{
    selfCopy(obj);
}

ResponseCopyVideoFileToTmp &ResponseCopyVideoFileToTmp::operator =(const ResponseCopyVideoFileToTmp &obj)
{
    OPERATOR_EQUAL_BODY;
}

ResponseCopyVideoFileToTmp::ResponseCopyVideoFileToTmp(const QJsonObject &json)
{
    if ( !IJsonable::typeFromJsonObject(json) ||
         !IResponseResultable::resultResponseFromJsonObject(json)
            )
        return;
    ICommonFields::fromJsonObject(json);

    if ( !json.contains("mNewVideoFilePath") || !json.contains("mErrorString") )
        return;
    JSON_TO_QSTRING(json, mNewVideoFilePath);
    JSON_TO_QSTRING(json, mErrorString);
}

void ResponseCopyVideoFileToTmp::selfCopy(const ResponseCopyVideoFileToTmp &obj)
{
    mUidRequest = obj.mUidRequest;
    mResponseResult = obj.mResponseResult;
    mNewVideoFilePath = obj.mNewVideoFilePath;
    mErrorString = obj.mErrorString;
}

EDataType ResponseCopyVideoFileToTmp::type() const
{
    return EDataType::ResponseCopyVideoFileToTmp;
}

QJsonObject ResponseCopyVideoFileToTmp::toJsonObject() const
{
    QJsonObject object;
    ICommonFields::toJsonObject(object);
    IJsonable::typeToJsonObject(object);
    IResponseResultable::resultResponseToJsonObject(object);
    QSTRING_TO_JSON(mNewVideoFilePath, object);
    QSTRING_TO_JSON(mErrorString, object);
    return object;
}

bool ResponseCopyVideoFileToTmp::isValid() const
{
    return true;
}






// ------------------------------------------------
// ----- RequestDeleteTmpVideoFiles
// ------------------------------------------------

RequestDeleteTmpVideoFiles::RequestDeleteTmpVideoFiles():IJsonable(), ICommonFields()
{

}

RequestDeleteTmpVideoFiles::RequestDeleteTmpVideoFiles(const RequestDeleteTmpVideoFiles &obj):IJsonable(), ICommonFields()
{
    selfCopy(obj);
}

RequestDeleteTmpVideoFiles &RequestDeleteTmpVideoFiles::operator =(const RequestDeleteTmpVideoFiles &obj)
{
    OPERATOR_EQUAL_BODY;
}

RequestDeleteTmpVideoFiles::RequestDeleteTmpVideoFiles(const QJsonObject &json)
{
    if ( !IJsonable::typeFromJsonObject(json) )
        return;
    ICommonFields::fromJsonObject(json);
}

void RequestDeleteTmpVideoFiles::selfCopy(const RequestDeleteTmpVideoFiles &obj)
{
    mUidRequest = obj.mUidRequest;
}

EDataType RequestDeleteTmpVideoFiles::type() const
{
    return EDataType::RequestDeleteTmpVideoFiles;
}

QJsonObject RequestDeleteTmpVideoFiles::toJsonObject() const
{
    QJsonObject object;
    ICommonFields::toJsonObject(object);
    IJsonable::typeToJsonObject(object);
    return object;
}

bool RequestDeleteTmpVideoFiles::isValid() const
{
    return true;
}

// ------------------------------------------------
// ----- ResponseDeleteTmpVideoFiles
// ------------------------------------------------

ResponseDeleteTmpVideoFiles::ResponseDeleteTmpVideoFiles():IJsonable(), ICommonFields(), IResponseResultable()
{

}

ResponseDeleteTmpVideoFiles::ResponseDeleteTmpVideoFiles(const ResponseDeleteTmpVideoFiles &obj):IJsonable(), ICommonFields(), IResponseResultable()
{
    selfCopy(obj);
}

ResponseDeleteTmpVideoFiles &ResponseDeleteTmpVideoFiles::operator =(const ResponseDeleteTmpVideoFiles &obj)
{
    OPERATOR_EQUAL_BODY;
}

ResponseDeleteTmpVideoFiles::ResponseDeleteTmpVideoFiles(const QJsonObject &json)
{
    if ( !IJsonable::typeFromJsonObject(json) ||
         !IResponseResultable::resultResponseFromJsonObject(json)  )
        return;
    ICommonFields::fromJsonObject(json);

    if ( !json.contains("mRemoved") || !json.contains("mErrorString") )
        return;
    JSON_TO_BOOL(json, mRemoved);
    JSON_TO_QSTRING(json, mErrorString);
}

void ResponseDeleteTmpVideoFiles::selfCopy(const ResponseDeleteTmpVideoFiles &obj)
{
    mUidRequest = obj.mUidRequest;
    mResponseResult = obj.mResponseResult;
    mRemoved = obj.mRemoved;
    mErrorString = obj.mErrorString;
}

EDataType ResponseDeleteTmpVideoFiles::type() const
{
    return EDataType::ResponseDeleteTmpVideoFiles;
}

QJsonObject ResponseDeleteTmpVideoFiles::toJsonObject() const
{
    QJsonObject object;
    ICommonFields::toJsonObject(object);
    IJsonable::typeToJsonObject(object);
    IResponseResultable::resultResponseToJsonObject(object);
    BOOL_TO_JSON(mRemoved, object);
    QSTRING_TO_JSON(mErrorString, object);
    return object;
}

bool ResponseDeleteTmpVideoFiles::isValid() const
{
    return true;
}

/********************************************************************************/
/// \remark запросы/ответы - управление параметрами сервера
/********************************************************************************/

// RequestSetConfigParam

RequestSetConfigParam::RequestSetConfigParam():IJsonable(), ICommonFields()
{

}

RequestSetConfigParam &RequestSetConfigParam::operator =(const RequestSetConfigParam &obj)
{
    OPERATOR_EQUAL_BODY;
}

RequestSetConfigParam::RequestSetConfigParam(const RequestSetConfigParam &obj):IJsonable(), ICommonFields()
{
    selfCopy(obj);
}

RequestSetConfigParam::RequestSetConfigParam(const QJsonObject &json)
{
    if ( !IJsonable::typeFromJsonObject(json) )
        return;
    ICommonFields::fromJsonObject(json);
    if (json.contains("mParameters")) {
        auto items = json.value("mParameters");
        auto items_keys = json.value(QString("mParameters") + "_keys");
        if (items.isArray()) {
            auto itemsArray = items.toArray();
            auto itemsArray_keys = items_keys.toArray();
            for (auto index=0; index<itemsArray_keys.count(); index++) {
                mParameters.insert(
                            static_cast<EServerConfigParam>(itemsArray_keys[index].toInt()),
                            itemsArray[index].toString()
                            );
            }
        }
    }
}

void RequestSetConfigParam::selfCopy(const RequestSetConfigParam &obj)
{
    mUidRequest = obj.mUidRequest;
    mParameters = obj.mParameters;
}

EDataType RequestSetConfigParam::type() const
{
    return EDataType::RequestSetConfigParam;
}

QJsonObject RequestSetConfigParam::toJsonObject() const
{
    QJsonObject object;
    ICommonFields::toJsonObject(object);
    IJsonable::typeToJsonObject(object);
    if (!mParameters.isEmpty()) {
        QJsonArray json_variable_keys;
        QJsonArray json_variable;
        for(const auto& key : mParameters.keys()) {
            json_variable_keys.append(QJsonValue(static_cast<int>(key)));
            json_variable.append(QJsonValue(mParameters[key]));
        }
        object.insert(QString("mParameters") + "_keys", json_variable_keys);
        object.insert("mParameters", json_variable);
    }
    return object;
}

bool RequestSetConfigParam::isValid() const
{
    return true;
}

// RequestGetConfigParam

RequestGetConfigParam::RequestGetConfigParam():IJsonable(), ICommonFields()
{

}

RequestGetConfigParam &RequestGetConfigParam::operator =(const RequestGetConfigParam &obj)
{
    OPERATOR_EQUAL_BODY;
}

RequestGetConfigParam::RequestGetConfigParam(const RequestGetConfigParam &obj):IJsonable(), ICommonFields()
{
    selfCopy(obj);
}

RequestGetConfigParam::RequestGetConfigParam(const QJsonObject &json)
{
    if ( !IJsonable::typeFromJsonObject(json) )
        return;
    ICommonFields::fromJsonObject(json);
    if (json.contains("mParameters")) {
        auto items = json.value("mParameters");
        if (items.isArray()) {
            auto itemsArray = items.toArray();
            for (auto index=0; index<itemsArray.count(); index++) {
                mParameters.append(static_cast<EServerConfigParam>(itemsArray[index].toInt()));
            }
        }
    }
}

void RequestGetConfigParam::selfCopy(const RequestGetConfigParam &obj)
{
    mUidRequest = obj.mUidRequest;
    mParameters = obj.mParameters;
}

EDataType RequestGetConfigParam::type() const
{
    return EDataType::RequestGetConfigParam;
}

QJsonObject RequestGetConfigParam::toJsonObject() const
{
    QJsonObject object;
    ICommonFields::toJsonObject(object);
    IJsonable::typeToJsonObject(object);
    if (!mParameters.isEmpty()) {
        QJsonArray json_variable;
        for(const auto& item : mParameters) {
            json_variable.append(QJsonValue(static_cast<int>(item)));
        }
        object.insert("mParameters", json_variable);
    }
    return object;
}

bool RequestGetConfigParam::isValid() const
{
    return true;
}

// ResponseSetConfigParam

ResponseSetConfigParam::ResponseSetConfigParam():IJsonable(), ICommonFields(), IResponseResultable()
{

}

ResponseSetConfigParam &ResponseSetConfigParam::operator =(const ResponseSetConfigParam &obj)
{
    OPERATOR_EQUAL_BODY;
}

ResponseSetConfigParam::ResponseSetConfigParam(const ResponseSetConfigParam &obj):IJsonable(), ICommonFields(), IResponseResultable()
{
   selfCopy(obj);
}

ResponseSetConfigParam::ResponseSetConfigParam(const QJsonObject &json)
{
    if ( !IJsonable::typeFromJsonObject(json) ||
         !IResponseResultable::resultResponseFromJsonObject(json)  )
        return;
    ICommonFields::fromJsonObject(json);
}

void ResponseSetConfigParam::selfCopy(const ResponseSetConfigParam &obj)
{
    mUidRequest = obj.mUidRequest;
    mResponseResult = obj.mResponseResult;
}

EDataType ResponseSetConfigParam::type() const
{
    return EDataType::ResponseSetConfigParam;
}

QJsonObject ResponseSetConfigParam::toJsonObject() const
{
    QJsonObject object;
    ICommonFields::toJsonObject(object);
    IJsonable::typeToJsonObject(object);
    IResponseResultable::resultResponseToJsonObject(object);
    return object;
}

bool ResponseSetConfigParam::isValid() const
{
    return true;
}

// ResponseGetConfigParam

ResponseGetConfigParam::ResponseGetConfigParam()
{

}

ResponseGetConfigParam &ResponseGetConfigParam::operator =(const ResponseGetConfigParam &obj)
{
    OPERATOR_EQUAL_BODY;
}

ResponseGetConfigParam::ResponseGetConfigParam(const ResponseGetConfigParam &obj)
{
    selfCopy(obj);
}

ResponseGetConfigParam::ResponseGetConfigParam(const QJsonObject &json)
{
    if ( !IJsonable::typeFromJsonObject(json) ||
         !IResponseResultable::resultResponseFromJsonObject(json)  )
        return;
    ICommonFields::fromJsonObject(json);
    if (json.contains("mParameters")) {
        auto items = json.value("mParameters");
        auto items_keys = json.value(QString("mParameters") + "_keys");
        if (items.isArray()) {
            auto itemsArray = items.toArray();
            auto itemsArray_keys = items_keys.toArray();
            for (auto index=0; index<itemsArray_keys.count(); index++) {
                mParameters.insert(
                            static_cast<EServerConfigParam>(itemsArray_keys[index].toInt()),
                            itemsArray[index].toString()
                            );
            }
        }
    }
}

void ResponseGetConfigParam::selfCopy(const ResponseGetConfigParam &obj)
{
    mUidRequest = obj.mUidRequest;
    mResponseResult = obj.mResponseResult;
    mParameters = obj.mParameters;
}

EDataType ResponseGetConfigParam::type() const
{
    return EDataType::ResponseGetConfigParam;
}

QJsonObject ResponseGetConfigParam::toJsonObject() const
{
    QJsonObject object;
    ICommonFields::toJsonObject(object);
    IJsonable::typeToJsonObject(object);
    IResponseResultable::resultResponseToJsonObject(object);
    if (!mParameters.isEmpty()) {
        QJsonArray json_variable_keys;
        QJsonArray json_variable;
        for(const auto& key : mParameters.keys()) {
            json_variable_keys.append(QJsonValue(static_cast<int>(key)));
            json_variable.append(QJsonValue(mParameters[key]));
        }
        object.insert(QString("mParameters") + "_keys", json_variable_keys);
        object.insert("mParameters", json_variable);
    }
    return object;
}

bool ResponseGetConfigParam::isValid() const
{
  return true;
}

///
/// \brief The RequestGetMiniScreenshots struct Запрос "Список мини-скиншотов"
///

RequestGetMiniScreenshots::RequestGetMiniScreenshots():IJsonable(), ICommonFields()
{

}

RequestGetMiniScreenshots::RequestGetMiniScreenshots(const RequestGetMiniScreenshots &obj):IJsonable(), ICommonFields()
{
    selfCopy(obj);
}

RequestGetMiniScreenshots &RequestGetMiniScreenshots::operator =(const RequestGetMiniScreenshots &obj)
{
    OPERATOR_EQUAL_BODY;
}

RequestGetMiniScreenshots::RequestGetMiniScreenshots(const QJsonObject &json)
{
    if ( !IJsonable::typeFromJsonObject(json)
         )
        return;
    ICommonFields::fromJsonObject(json);
    JSON_TO_QUUID(json, mVideoStreamUid);
    if (json.contains("mDateTimeSreenshots")) {
        mDateTimeSreenshots.clear();
        auto items = json.value("mDateTimeSreenshots");
        if (items.isArray()) {
            auto itemsArray = items.toArray();
            for (auto index=0; index<itemsArray.count(); index++) {
                mDateTimeSreenshots.append(
                            QDateTime::fromString(
                                itemsArray[index].toString(),
                                cDateTimeFormat
                                )
                            );
            }
        }
    }
    {
        QSize temp;
        temp.setWidth(json.value("mTargetOutputResolution_width").toInt());
        temp.setHeight(json.value("mTargetOutputResolution_height").toInt());
        mTargetOutputResolution = temp;
    }
}

void RequestGetMiniScreenshots::selfCopy(const RequestGetMiniScreenshots &obj)
{
    mUidRequest = obj.mUidRequest;
    mVideoStreamUid = obj.mVideoStreamUid;                  // уид видеопотока
    mDateTimeSreenshots = obj.mDateTimeSreenshots;	// дата-время скриншотов
    mTargetOutputResolution = obj.mTargetOutputResolution;          // целевое выходное разрешение картинок
}

EDataType RequestGetMiniScreenshots::type() const
{
    return EDataType::RequestGetMiniScreenshots;
}

QJsonObject RequestGetMiniScreenshots::toJsonObject() const
{
    QJsonObject object;
    ICommonFields::toJsonObject(object);
    IJsonable::typeToJsonObject(object);
    QUUID_TO_JSON(mVideoStreamUid, object);
    if (!mDateTimeSreenshots.isEmpty()) {
        QJsonArray json_variable;
        for(const auto& item : mDateTimeSreenshots) {
            json_variable.append(QJsonValue(item.toString(cDateTimeFormat)));
        }
        object.insert("mDateTimeSreenshots", json_variable);
    }
    object.insert("mTargetOutputResolution_width", QJsonValue::fromVariant(mTargetOutputResolution.width()));
    object.insert("mTargetOutputResolution_height", QJsonValue::fromVariant(mTargetOutputResolution.height()));
    return object;
}

bool RequestGetMiniScreenshots::isValid() const
{
      return true;
}

///
/// \brief The ResponseDeleteTmpVideoFiles struct Ответ "Список мини-скиншотов"
///

ResponseGetMiniScreenshots::ResponseGetMiniScreenshots():IJsonable(), ICommonFields(), IResponseResultable()
{

}

ResponseGetMiniScreenshots::ResponseGetMiniScreenshots(const ResponseGetMiniScreenshots &obj):IJsonable(), ICommonFields(), IResponseResultable()
{
    selfCopy(obj);
}

ResponseGetMiniScreenshots &ResponseGetMiniScreenshots::operator =(const ResponseGetMiniScreenshots &obj)
{
    OPERATOR_EQUAL_BODY;
}

ResponseGetMiniScreenshots::ResponseGetMiniScreenshots(const QJsonObject &json)
{
    if ( !IJsonable::typeFromJsonObject(json) ||
         !IResponseResultable::resultResponseFromJsonObject(json)  )
        return;
    ICommonFields::fromJsonObject(json);
    if (json.contains("mHexedMiniSreenshots")) {
        auto items = json.value("mHexedMiniSreenshots");
        auto items_keys = json.value(QString("mHexedMiniSreenshots") + "_keys");
        if (items.isArray()) {
            auto itemsArray = items.toArray();
            auto itemsArray_keys = items_keys.toArray();
            for (auto index=0; index<itemsArray_keys.count(); index++) {
                mHexedMiniSreenshots.insert(
                            itemsArray_keys[index].toVariant().toDateTime(),
                            itemsArray[index].toVariant().toByteArray()
                            );
            }
        }
    }
}

QMap<QDateTime, QImage> ResponseGetMiniScreenshots::miniSreenshots()
{
    QMap<QDateTime, QImage> images;
    auto keys = mHexedMiniSreenshots.keys();
    for (auto index=0; index<keys.count(); index++) {
        QImage image;
        QByteArray rawImg = QByteArray::fromHex(mHexedMiniSreenshots[keys[index]]);
        QBuffer pictureBuffer(&rawImg);
        pictureBuffer.open(QIODevice::ReadOnly);
        image.load(&pictureBuffer, "JPEG");
        images.insert(keys[index], image);
    }
    return images;
}

void ResponseGetMiniScreenshots::setMiniScreenshots(const QMap<QDateTime, QImage> &miniScreenshots)
{
    mHexedMiniSreenshots.clear();
    auto keys = miniScreenshots.keys();
    for (auto index=0; index<keys.count(); index++) {
        QByteArray rawImg;
        QBuffer pictureBuffer(&rawImg);
        pictureBuffer.open(QIODevice::WriteOnly);
        miniScreenshots[keys[index]].save(&pictureBuffer, "JPEG");
        pictureBuffer.close();
        auto hexedImg = rawImg.toHex();
        mHexedMiniSreenshots.insert(keys[index], hexedImg);
    }
}

void ResponseGetMiniScreenshots::selfCopy(const ResponseGetMiniScreenshots &obj)
{
    mUidRequest = obj.mUidRequest;
    mResponseResult = obj.mResponseResult;
    mHexedMiniSreenshots = obj.mHexedMiniSreenshots;
}

EDataType ResponseGetMiniScreenshots::type() const
{
    return EDataType::ResponseGetMiniScreenshots;
}

QJsonObject ResponseGetMiniScreenshots::toJsonObject() const
{
    QJsonObject object;
    ICommonFields::toJsonObject(object);
    IJsonable::typeToJsonObject(object);
    IResponseResultable::resultResponseToJsonObject(object);
    if (!mHexedMiniSreenshots.isEmpty()) {
            QJsonArray json_variable_keys;
            QJsonArray json_variable;
            for(const auto& key : mHexedMiniSreenshots.keys()) {
                json_variable_keys.append(QJsonValue::fromVariant(key));
                json_variable.append(QJsonValue::fromVariant(mHexedMiniSreenshots[key]));
            }
            object.insert(QString("mHexedMiniSreenshots") + "_keys", json_variable_keys);
            object.insert("mHexedMiniSreenshots", json_variable);
    }
    return object;
}

bool ResponseGetMiniScreenshots::isValid() const
{
    return true;
}

///
/// \brief The RequestGetScreenshot struct Запрос "Полноразмерный скриншот"
///

RequestGetScreenshot::RequestGetScreenshot():IJsonable(), ICommonFields()
{

}

RequestGetScreenshot::RequestGetScreenshot(const RequestGetScreenshot &obj):IJsonable(), ICommonFields()
{
    selfCopy(obj);
}

RequestGetScreenshot &RequestGetScreenshot::operator =(const RequestGetScreenshot &obj)
{
    OPERATOR_EQUAL_BODY;
}

RequestGetScreenshot::RequestGetScreenshot(const QJsonObject &json)
{
    if ( !IJsonable::typeFromJsonObject(json)
         )
        return;
    ICommonFields::fromJsonObject(json);
    JSON_TO_QUUID(json, mVideoStreamUid);
    mDateTimeSreenshot = QDateTime::fromString( json.value("mDateTimeSreenshot").toString(), cDateTimeFormat );
    {
        QSize temp;
        temp.setWidth(json.value("mTargetOutputResolution_width").toInt());
        temp.setHeight(json.value("mTargetOutputResolution_height").toInt());
        mTargetOutputResolution = temp;
    }
}

void RequestGetScreenshot::selfCopy(const RequestGetScreenshot &obj)
{
    mUidRequest = obj.mUidRequest;
    mVideoStreamUid = obj.mVideoStreamUid;          // уид видеопотока
    mDateTimeSreenshot = obj.mDateTimeSreenshot;	// дата-время скриншота
}

EDataType RequestGetScreenshot::type() const
{
    return EDataType::RequestGetScreenshot;
}

QJsonObject RequestGetScreenshot::toJsonObject() const
{
    QJsonObject object;
    ICommonFields::toJsonObject(object);
    IJsonable::typeToJsonObject(object);
    QUUID_TO_JSON(mVideoStreamUid, object);
    object.insert("mDateTimeSreenshot", QJsonValue(mDateTimeSreenshot.toString(cDateTimeFormat)));
    object.insert("mTargetOutputResolution_width", QJsonValue::fromVariant(mTargetOutputResolution.width()));
    object.insert("mTargetOutputResolution_height", QJsonValue::fromVariant(mTargetOutputResolution.height()));
    return object;
}

bool RequestGetScreenshot::isValid() const
{
    return true;
}

///
/// \brief The ResponseGetScreenshot struct Ответ "Полноразмерный скриншот"
///

ResponseGetScreenshot::ResponseGetScreenshot():IJsonable(), ICommonFields(), IResponseResultable()
{

}

ResponseGetScreenshot::ResponseGetScreenshot(const ResponseGetScreenshot &obj):IJsonable(), ICommonFields(), IResponseResultable()
{
    selfCopy(obj);
}

ResponseGetScreenshot &ResponseGetScreenshot::operator =(const ResponseGetScreenshot &obj)
{
    OPERATOR_EQUAL_BODY;
}

ResponseGetScreenshot::ResponseGetScreenshot(const QJsonObject &json)
{
    if ( !IJsonable::typeFromJsonObject(json) ||
         !IResponseResultable::resultResponseFromJsonObject(json)  )
        return;
    ICommonFields::fromJsonObject(json);
    mHexedSreenshot = json.value("mHexedSreenshot").toVariant().toByteArray();
}

QImage ResponseGetScreenshot::sreenshot()
{
    QImage image;
    QByteArray rawImg = QByteArray::fromHex(mHexedSreenshot);
    QBuffer pictureBuffer(&rawImg);
    pictureBuffer.open(QIODevice::ReadOnly);
    image.load(&pictureBuffer, "JPEG");
    return image;
}

void ResponseGetScreenshot::setScreenshot(QImage screenshot)
{
    QByteArray rawImg;
    QBuffer pictureBuffer(&rawImg);
    pictureBuffer.open(QIODevice::WriteOnly);
    screenshot.save(&pictureBuffer, "JPEG");
    pictureBuffer.close();
    mHexedSreenshot = rawImg.toHex();
}

void ResponseGetScreenshot::selfCopy(const ResponseGetScreenshot &obj)
{
    mUidRequest = obj.mUidRequest;
    mResponseResult = obj.mResponseResult;
    mHexedSreenshot = obj.mHexedSreenshot;
}

EDataType ResponseGetScreenshot::type() const
{
    return EDataType::ResponseGetScreenshot;
}

QJsonObject ResponseGetScreenshot::toJsonObject() const
{
    QJsonObject object;
    ICommonFields::toJsonObject(object);
    IJsonable::typeToJsonObject(object);
    IResponseResultable::resultResponseToJsonObject(object);
    object.insert("mHexedSreenshot", QJsonValue::fromVariant(mHexedSreenshot) );
    return object;
}

bool ResponseGetScreenshot::isValid() const
{
    return true;
}

///
/// \brief The RequestUseVideoStream struct извещение пка об использовании видеопотока
///

RequestUseVideoStream::RequestUseVideoStream():IJsonable(), ICommonFields()
{

}

RequestUseVideoStream::RequestUseVideoStream(const RequestUseVideoStream &obj):IJsonable(), ICommonFields()
{
    selfCopy(obj);
}

RequestUseVideoStream &RequestUseVideoStream::operator =(const RequestUseVideoStream &obj)
{
    OPERATOR_EQUAL_BODY;
}

RequestUseVideoStream::RequestUseVideoStream(const QJsonObject &json)
{
    if ( !IJsonable::typeFromJsonObject(json)
         )
        return;
    ICommonFields::fromJsonObject(json);
    JSON_TO_QUUID(json, mVideoStreamUid);
}

void RequestUseVideoStream::selfCopy(const RequestUseVideoStream &obj)
{
    mUidRequest = obj.mUidRequest;
    mVideoStreamUid = obj.mVideoStreamUid;                  // уид видеопотока
}

EDataType RequestUseVideoStream::type() const
{
    return EDataType::RequestUseVideoStream;
}

QJsonObject RequestUseVideoStream::toJsonObject() const
{
    QJsonObject object;
    ICommonFields::toJsonObject(object);
    IJsonable::typeToJsonObject(object);
    QUUID_TO_JSON(mVideoStreamUid, object);
    return object;
}

bool RequestUseVideoStream::isValid() const
{
      return true;
}

///
/// \brief The RequestResetStreams struct указание от СА в РК - перезапусти запись и перезапроси потоки
///

RequestResetStreams::RequestResetStreams():IJsonable(), ICommonFields()
{

}

RequestResetStreams::RequestResetStreams(const RequestResetStreams &obj):IJsonable(), ICommonFields()
{
    selfCopy(obj);
}

RequestResetStreams &RequestResetStreams::operator =(const RequestResetStreams &obj)
{
    OPERATOR_EQUAL_BODY;
}

RequestResetStreams::RequestResetStreams(const QJsonObject &json)
{
    if ( !IJsonable::typeFromJsonObject(json)
         )
        return;
    ICommonFields::fromJsonObject(json);
}

void RequestResetStreams::selfCopy(const RequestResetStreams &obj)
{
    mUidRequest = obj.mUidRequest;                 // уид видеопотока
}

EDataType RequestResetStreams::type() const
{
    return EDataType::RequestResetStreams;
}

QJsonObject RequestResetStreams::toJsonObject() const
{
    QJsonObject object;
    ICommonFields::toJsonObject(object);
    IJsonable::typeToJsonObject(object);
    return object;
}

bool RequestResetStreams::isValid() const
{
      return true;
}

///
/// \brief The RequestRestartStreamWriter struct команда рестарт писателя потока в РК
///

RequestRestartStreamWriter::RequestRestartStreamWriter():IJsonable(), ICommonFields()
{

}

RequestRestartStreamWriter::RequestRestartStreamWriter(const RequestRestartStreamWriter &obj):IJsonable(), ICommonFields()
{
    selfCopy(obj);
}

RequestRestartStreamWriter &RequestRestartStreamWriter::operator =(const RequestRestartStreamWriter &obj)
{
    OPERATOR_EQUAL_BODY;
}

RequestRestartStreamWriter::RequestRestartStreamWriter(const QJsonObject &json)
{
    if ( !IJsonable::typeFromJsonObject(json)
         )
        return;
    ICommonFields::fromJsonObject(json);
    JSON_TO_QUUID(json, mVideoStreamUid);
}

void RequestRestartStreamWriter::selfCopy(const RequestRestartStreamWriter &obj)
{
    mUidRequest = obj.mUidRequest;
    mVideoStreamUid = obj.mVideoStreamUid;                  // уид видеопотока
}

EDataType RequestRestartStreamWriter::type() const
{
    return EDataType::RequestRestartStreamWriter;
}

QJsonObject RequestRestartStreamWriter::toJsonObject() const
{
    QJsonObject object;
    ICommonFields::toJsonObject(object);
    IJsonable::typeToJsonObject(object);
    QUUID_TO_JSON(mVideoStreamUid, object);
    return object;
}

bool RequestRestartStreamWriter::isValid() const
{
      return true;
}

///
/// \brief The RequestFreeFile struct команда от РК в СА - освободи файл
///

RequestFreeFile::RequestFreeFile():IJsonable(), ICommonFields()
{

}

RequestFreeFile::RequestFreeFile(const RequestFreeFile &obj):IJsonable(), ICommonFields()
{
    selfCopy(obj);
}

RequestFreeFile &RequestFreeFile::operator =(const RequestFreeFile &obj)
{
    OPERATOR_EQUAL_BODY;
}

RequestFreeFile::RequestFreeFile(const QJsonObject &json)
{
    if ( !IJsonable::typeFromJsonObject(json)
         )
        return;
    ICommonFields::fromJsonObject(json);
    JSON_TO_QUUID(json, mVideoFileUid);
}

void RequestFreeFile::selfCopy(const RequestFreeFile &obj)
{
    mUidRequest = obj.mUidRequest;
    mVideoFileUid = obj.mVideoFileUid;                  // уид видеопотока
}

EDataType RequestFreeFile::type() const
{
    return EDataType::RequestFreeFile;
}

QJsonObject RequestFreeFile::toJsonObject() const
{
    QJsonObject object;
    ICommonFields::toJsonObject(object);
    IJsonable::typeToJsonObject(object);
    QUUID_TO_JSON(mVideoFileUid, object);
    return object;
}

bool RequestFreeFile::isValid() const
{
      return true;
}


///
/// \brief The RequestEventNotification struct уведомление о событии
///

RequestEventNotification::RequestEventNotification():IJsonable(), ICommonFields()
{

}

RequestEventNotification::RequestEventNotification(const RequestEventNotification &obj):IJsonable(), ICommonFields()
{
    selfCopy(obj);
}

RequestEventNotification &RequestEventNotification::operator =(const RequestEventNotification &obj)
{
    OPERATOR_EQUAL_BODY;
}

RequestEventNotification::RequestEventNotification(const QJsonObject &json)
{
    if ( !IJsonable::typeFromJsonObject(json)
         )
        return;
    ICommonFields::fromJsonObject(json);
    JSON_TO_QUUID(json, mEventUid);
}

void RequestEventNotification::selfCopy(const RequestEventNotification &obj)
{
    mUidRequest = obj.mUidRequest;
    mEventUid = obj.mEventUid;                  // уид видеопотока
}

EDataType RequestEventNotification::type() const
{
    return EDataType::RequestEventNotification;
}

QJsonObject RequestEventNotification::toJsonObject() const
{
    QJsonObject object;
    ICommonFields::toJsonObject(object);
    IJsonable::typeToJsonObject(object);
    QUUID_TO_JSON(mEventUid, object);
    return object;
}

bool RequestEventNotification::isValid() const
{
      return true;
}

