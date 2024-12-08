#include "interactionprotocolstructs.h"
#include "servicemacros.h"

/// \remark AvailableCameraProperties

AvailableCameraProperties::AvailableCameraProperties():
        mIp(""), mUid("")
{
}

AvailableCameraProperties::AvailableCameraProperties(const QString& ip, const QString& uid):
    mIp(ip), mUid(uid)
{

}

AvailableCameraProperties::AvailableCameraProperties(const AvailableCameraProperties &obj)
{
    selfCopy(obj);
}

bool AvailableCameraProperties::isValid() const
{
    if (mIp.isEmpty() || mUid.isEmpty())
        return false;
    else
        return true;
}

EDataType AvailableCameraProperties::type() const { return EDataType::AvailableCameraProperties; }



QJsonObject AvailableCameraProperties::toJsonObject() const
{
    QJsonObject object;
    IJsonable::typeToJsonObject(object);
    QSTRING_TO_JSON(mIp, object);
    QSTRING_TO_JSON(mUid, object);
    return object;
}

void AvailableCameraProperties::selfCopy(const AvailableCameraProperties &obj)
{
    mIp = obj.mIp;
    mUid = obj.mUid;
}

AvailableCameraProperties &AvailableCameraProperties::operator =(const AvailableCameraProperties &obj)
{
    OPERATOR_EQUAL_BODY;
}

AvailableCameraProperties::AvailableCameraProperties(const QJsonObject &json)
{
    if (!IJsonable::typeFromJsonObject(json))
        return;
    if ( !json.contains("mIp") ||
         !json.contains("mUid")
         )
        return;
    JSON_TO_QSTRING(json, mIp);
    JSON_TO_QSTRING(json, mUid);
}

/// \remark ZoneProperties

ZoneProperties::ZoneProperties():
        mUid(QUuid()), mName(""), mDescription(""), mAddress(""), mCoordinates(QPointF(0., 0.))
{
}

ZoneProperties::ZoneProperties(const QUuid &uid, const QString& name, const QString &description, const QString &address, const QPointF &coordinates, const QVector<ZoneProperties> subZones):
    mUid(uid), mName(name), mDescription(description), mAddress(address), mCoordinates(coordinates)
{
    mSubZones.clear();
    mSubZones.append(subZones);
}

ZoneProperties::ZoneProperties(const ZoneProperties &obj)
{
    selfCopy(obj);
}

bool ZoneProperties::isValid() const
{
    if (mUid.isNull() || mName.isEmpty())
        return false;
    else
        return true;
}

EDataType ZoneProperties::type() const { return EDataType::ZoneProperties; }



QJsonObject ZoneProperties::toJsonObject() const
{
    QJsonObject object;
    IJsonable::typeToJsonObject(object);
    QUUID_TO_JSON(mUid, object);
    QSTRING_TO_JSON(mName, object);
    QSTRING_TO_JSON(mDescription, object);
    QSTRING_TO_JSON(mAddress, object);
    double lat = mCoordinates.x(), lng = mCoordinates.y();
    DOUBLE_TO_JSON(lat, object);
    DOUBLE_TO_JSON(lng, object);
    QVECTOR_STRUCT_TO_JSON(mSubZones, ZoneProperties, object);
    return object;
}

void ZoneProperties::selfCopy(const ZoneProperties &obj)
{
    mUid = obj.mUid;
    mName = obj.mName;
    mDescription = obj.mDescription;
    mAddress = obj.mAddress;
    mCoordinates = obj.mCoordinates;
    mSubZones.clear();
    mSubZones.append(obj.mSubZones);
}

ZoneProperties &ZoneProperties::operator =(const ZoneProperties &obj)
{
    OPERATOR_EQUAL_BODY;
}

ZoneProperties::ZoneProperties(const QJsonObject &json)
{
    if (!IJsonable::typeFromJsonObject(json))
        return;
    if ( !json.contains("mUid") ||
         !json.contains("mName") ||
         !json.contains("mDescription") ||
         !json.contains("mAddress")
         )
        return;
    JSON_TO_QUUID(json, mUid);
    JSON_TO_QSTRING(json, mName);
    JSON_TO_QSTRING(json, mDescription);
    JSON_TO_QSTRING(json, mAddress);
    double lat = 0., lng = 0.;
    JSON_TO_DOUBLE(json, lat);
    JSON_TO_DOUBLE(json, lng);
    mCoordinates = QPointF(lat, lng);
    JSON_TO_QVECTOR_STRUCT(json, ZoneProperties, mSubZones);
}

/// \remark UserProperties

UserProperties::UserProperties():
    mUid(QUuid()), mLogin(""), mRole(EUserRole::None), mIsRemoved(false)
{
}

UserProperties::UserProperties(const QUuid &uid, const QString &login, const EUserRole &role, bool isRemoved):
    mUid(uid), mLogin(login), mRole(role), mIsRemoved(isRemoved)
{
}

UserProperties::UserProperties(const UserProperties &obj)
{
    selfCopy(obj);
}

UserProperties &UserProperties::operator =(const UserProperties &obj)
{
    OPERATOR_EQUAL_BODY;
}

UserProperties::UserProperties(const QJsonObject &json)
{
    if (!IJsonable::typeFromJsonObject(json))
        return;
    if ( !json.contains("mUid") ||
         !json.contains("mLogin") ||
         !json.contains("mRole") ||
         !json.contains("mIsRemoved")
         )
        return;
    JSON_TO_QUUID(json, mUid);
    JSON_TO_QSTRING(json, mLogin);
    JSON_TO_ENUM(json, EUserRole, mRole);
    JSON_TO_BOOL(json, mIsRemoved);
}

bool UserProperties::isValid() const
{
    if (mUid.isNull() || mLogin.isEmpty() || (mRole == EUserRole::None))
        return false;
    else
        return true;
}

EDataType UserProperties::type() const { return EDataType::UserProperties; }

QJsonObject UserProperties::toJsonObject() const
{
    QJsonObject object;
    IJsonable::typeToJsonObject(object);
    QUUID_TO_JSON(mUid, object);
    QSTRING_TO_JSON(mLogin, object);
    ENUM_TO_JSON(mRole, object);
    BOOL_TO_JSON(mIsRemoved, object);
    return object;
}

void UserProperties::selfCopy(const UserProperties &obj)
{
    mUid = obj.mUid;
    mLogin = obj.mLogin;
    mRole = obj.mRole;
    mIsRemoved = obj.mIsRemoved;
}

/// \remark NewZone

NewZone::NewZone():
    mName(""), mDescription(""), mAddress(""), mCoordinates(QPointF(0.,0.)), mParentZoneUid(QUuid())
{

}

NewZone::NewZone(const QString &name, const QString &description, const QString &address, const QPointF &coordinates, const QUuid &parentZoneUid):
    mName(name), mDescription(description), mAddress(address), mCoordinates(coordinates), mParentZoneUid(parentZoneUid)
{

}

NewZone::NewZone(const NewZone &obj)
{
    selfCopy(obj);
}

NewZone &NewZone::operator =(const NewZone &obj)
{
    OPERATOR_EQUAL_BODY;
}

NewZone::NewZone(const QJsonObject &json)
{
    if (!IJsonable::typeFromJsonObject(json))
        return;
    if ( !json.contains("mParentZoneUid") ||
         !json.contains("mName") ||
         !json.contains("mDescription") ||
         !json.contains("mAddress")
         )
        return;
    JSON_TO_QSTRING(json, mName);
    JSON_TO_QSTRING(json, mDescription);
    JSON_TO_QSTRING(json, mAddress);
    double lat = 0., lng = 0.;
    JSON_TO_DOUBLE(json, lat);
    JSON_TO_DOUBLE(json, lng);
    mCoordinates = QPointF(lat, lng);
    JSON_TO_QUUID(json, mParentZoneUid);
}

void NewZone::selfCopy(const NewZone &obj)
{
    mName = obj.mName;
    mDescription = obj.mDescription;
    mAddress = obj.mAddress;
    mCoordinates = obj.mCoordinates;
    mParentZoneUid = obj.mParentZoneUid;
}

EDataType NewZone::type() const
{
    return EDataType::NewZone;
}

QJsonObject NewZone::toJsonObject() const
{
    QJsonObject object;
    IJsonable::typeToJsonObject(object);
    QSTRING_TO_JSON(mName, object);
    QSTRING_TO_JSON(mDescription, object);
    QSTRING_TO_JSON(mAddress, object);
    double lat = mCoordinates.x(), lng = mCoordinates.y();
    DOUBLE_TO_JSON(lat, object);
    DOUBLE_TO_JSON(lng, object);
    QUUID_TO_JSON(mParentZoneUid, object);
    return object;
}

bool NewZone::isValid() const
{
    if (mName.isEmpty() || mAddress.isEmpty())
        return false;
    else
        return true;
}

/// \remark Group

Group::Group():
    mUid(QUuid()), mName(""), mDescription("")
{

}

Group::Group(const QUuid& uid, const QString &name, const QString &description):
    mUid(uid), mName(name), mDescription(description)
{

}

Group::Group(const Group &obj)
{
    selfCopy(obj);
}

Group &Group::operator =(const Group &obj)
{
    OPERATOR_EQUAL_BODY;
}

Group::Group(const QJsonObject &json)
{
    if (!IJsonable::typeFromJsonObject(json))
        return;
    if ( !json.contains("mUid") ||
         !json.contains("mName") ||
         !json.contains("mDescription")
         )
        return;
    JSON_TO_QUUID(json, mUid);
    JSON_TO_QSTRING(json, mName);
    JSON_TO_QSTRING(json, mDescription);
}

void Group::selfCopy(const Group &obj)
{
    mName = obj.mName;
    mDescription = obj.mDescription;
    mUid = obj.mUid;
}

EDataType Group::type() const
{
    return EDataType::Group;
}

QJsonObject Group::toJsonObject() const
{
    QJsonObject object;
    IJsonable::typeToJsonObject(object);
    QUUID_TO_JSON(mUid, object);
    QSTRING_TO_JSON(mName, object);
    QSTRING_TO_JSON(mDescription, object);
    return object;
}

bool Group::isValid() const
{
    if (mUid.isNull())
        return false;
    else
        return true;
}

/// \remark AccessRightProperties

AccessRightProperties::AccessRightProperties():
    mUidUser(QUuid()), mUidGroup(QUuid()), mUidZone(QUuid()), mUidCamera(QUuid())
{

}

AccessRightProperties::AccessRightProperties(const QUuid& uidUser, const QUuid& uidGroup, const QUuid& uidZone, const QUuid& uidCamera):
    mUidUser(uidUser), mUidGroup(uidGroup), mUidZone(uidZone), mUidCamera(uidCamera)
{

}

AccessRightProperties::AccessRightProperties(const AccessRightProperties &obj)
{
    selfCopy(obj);
}

AccessRightProperties &AccessRightProperties::operator =(const AccessRightProperties &obj)
{
    OPERATOR_EQUAL_BODY;
}

AccessRightProperties::AccessRightProperties(const QJsonObject &json)
{
    if (!IJsonable::typeFromJsonObject(json))
        return;
    if ( !json.contains("mUidUser") ||
         !json.contains("mUidGroup") ||
         !json.contains("mUidZone") ||
         !json.contains("mUidCamera")
         )
        return;
    JSON_TO_QUUID(json, mUidUser);
    JSON_TO_QUUID(json, mUidGroup);
    JSON_TO_QUUID(json, mUidZone);
    JSON_TO_QUUID(json, mUidCamera);
}

void AccessRightProperties::selfCopy(const AccessRightProperties &obj)
{
    mUidUser = obj.mUidUser;
    mUidGroup = obj.mUidGroup;
    mUidZone = obj.mUidZone;
    mUidCamera = obj.mUidCamera;
}

EDataType AccessRightProperties::type() const
{
    return EDataType::AccessRightProperties;
}

QJsonObject AccessRightProperties::toJsonObject() const
{
    QJsonObject object;
    IJsonable::typeToJsonObject(object);
    QUUID_TO_JSON(mUidUser, object);
    QUUID_TO_JSON(mUidGroup, object);
    QUUID_TO_JSON(mUidZone, object);
    QUUID_TO_JSON(mUidCamera, object);
    return object;
}

bool AccessRightProperties::isValid() const
{
    return true;
}

/// \remark VideoProperties

VideoProperties::VideoProperties():
    mFileName(""), mCameraStreamUid(QUuid()), mStartDate(QDateTime()), mFinishDate(QDateTime()), mAddedDate(QDateTime()), mServer(QUuid())
{

}

VideoProperties::VideoProperties(const QString& fileName, const QUuid& cameraStreamUid, const QDateTime& startDate, const QDateTime& finishDate, const QDateTime& addedDate, const QUuid& server):
    mFileName(fileName), mCameraStreamUid(cameraStreamUid), mStartDate(startDate), mFinishDate(finishDate), mAddedDate(addedDate), mServer(server)
{

}

VideoProperties::VideoProperties(const VideoProperties &obj)
{
    selfCopy(obj);
}

VideoProperties &VideoProperties::operator =(const VideoProperties &obj)
{
    OPERATOR_EQUAL_BODY;
}

VideoProperties::VideoProperties(const QJsonObject &json)
{
    if (!IJsonable::typeFromJsonObject(json))
        return;
    if ( !json.contains("mFileName") ||
         !json.contains("mCameraStreamUid") ||
         !json.contains("mStartDate") ||
         !json.contains("mFinishDate") ||
         !json.contains("mAddedDate") ||
         !json.contains("mServer")
         )
        return;
    JSON_TO_QSTRING(json, mFileName);
    JSON_TO_QUUID(json, mCameraStreamUid);
    JSON_TO_QDATETIME(json, mStartDate);
    JSON_TO_QDATETIME(json, mFinishDate);
    JSON_TO_QDATETIME(json, mAddedDate);
    JSON_TO_QUUID(json, mServer);
}

void VideoProperties::selfCopy(const VideoProperties &obj)
{
    mFileName = obj.mFileName;
    mCameraStreamUid = obj.mCameraStreamUid;
    mStartDate = obj.mStartDate;
    mFinishDate = obj.mFinishDate;
    mAddedDate = obj.mAddedDate;
    mServer = obj.mServer;
}

EDataType VideoProperties::type() const
{
    return EDataType::VideoProperties;
}

QJsonObject VideoProperties::toJsonObject() const
{
    QJsonObject object;
    IJsonable::typeToJsonObject(object);
    QSTRING_TO_JSON(mFileName, object);
    QUUID_TO_JSON(mCameraStreamUid, object);
    QDATETIME_TO_JSON(mStartDate, object);
    QDATETIME_TO_JSON(mFinishDate, object);
    QDATETIME_TO_JSON(mAddedDate, object);
    QUUID_TO_JSON(mServer, object);
    return object;
}

bool VideoProperties::isValid() const
{
    return !mFileName.isEmpty();
}

/// \remark CameraProperties

CameraProperties::CameraProperties():
    mName(""), mType(QUuid()), mUrl(""), mDescription(""), mLat(0.), mLng(0.), mZone(QUuid()), mIsRemoved(false), mServer(QUuid())
{

}

CameraProperties::CameraProperties(const QString& name, const QUuid& type, const QString& url, const QString& description, const double& lat, const double& lng, const QUuid& zone, const bool& isRemoved, const QUuid &server):
     mName(name), mType(type), mUrl(url), mDescription(description), mLat(lat), mLng(lng), mZone(zone), mIsRemoved(isRemoved), mServer(server)
{

}

CameraProperties::CameraProperties(const CameraProperties &obj)
{
    selfCopy(obj);
}

CameraProperties &CameraProperties::operator =(const CameraProperties &obj)
{
    OPERATOR_EQUAL_BODY;
}

CameraProperties::CameraProperties(const QJsonObject &json)
{
    if (!IJsonable::typeFromJsonObject(json))
        return;
    if ( !json.contains("mName") ||
         !json.contains("mType") ||
         !json.contains("mUrl") ||
         !json.contains("mDescription") ||
         !json.contains("mLat") ||
         !json.contains("mLng") ||
         !json.contains("mZone") ||
         !json.contains("mIsRemoved") ||
         !json.contains("mServer")
         )
        return;
    JSON_TO_QSTRING(json, mName);
    JSON_TO_QUUID(json, mType);
    JSON_TO_QSTRING(json, mUrl);
    JSON_TO_QSTRING(json, mDescription);
    JSON_TO_DOUBLE(json, mLat);
    JSON_TO_DOUBLE(json, mLng);
    JSON_TO_QUUID(json, mZone);
    JSON_TO_BOOL(json, mIsRemoved);
    JSON_TO_QMAP_QUUID_STRUCT(json, StreamCameraProperties, mCameraStreams);
    JSON_TO_QUUID(json, mServer);
}

void CameraProperties::selfCopy(const CameraProperties &obj)
{
    mName = obj.mName;
    mType = obj.mType;
    mUrl = obj.mUrl;
    mDescription = obj.mDescription;
    mLat = obj.mLat;
    mLng = obj.mLng;
    mZone = obj.mZone;
    mIsRemoved = obj.mIsRemoved;
    mCameraStreams.clear();
    mCameraStreams = obj.mCameraStreams;
    mServer = obj.mServer;
}

EDataType CameraProperties::type() const
{
    return EDataType::CameraProperties;
}

QJsonObject CameraProperties::toJsonObject() const
{
    QJsonObject object;
    IJsonable::typeToJsonObject(object);
    QSTRING_TO_JSON(mName, object);
    QUUID_TO_JSON(mType, object);
    QSTRING_TO_JSON(mUrl, object);
    QSTRING_TO_JSON(mDescription, object);
    DOUBLE_TO_JSON(mLat, object);
    DOUBLE_TO_JSON(mLng, object);
    QUUID_TO_JSON(mZone, object);
    BOOL_TO_JSON(mIsRemoved, object);
    QMAP_QUUID_STRUCT_TO_JSON(mCameraStreams, StreamCameraProperties, object);
    QUUID_TO_JSON(mServer, object);
    return object;
}

bool CameraProperties::isValid() const
{
    return !mType.isNull();
}

/// \remark StreamCameraProperties

StreamCameraProperties::StreamCameraProperties():
    mCameraUid(QUuid()), mStreamCameraTypeUid(QUuid()), mUrl(""), mDescription(""), mIsRecording(false), mStreamCameraStatusUid(QUuid())
{

}

StreamCameraProperties::StreamCameraProperties(const QUuid& camera, const QUuid& streamType, const QString& url, const QString& description, const bool& isRecording, const QUuid &status):
     mCameraUid(camera), mStreamCameraTypeUid(streamType), mUrl(url), mDescription(description), mIsRecording(isRecording), mStreamCameraStatusUid(status)
{

}

StreamCameraProperties::StreamCameraProperties(const StreamCameraProperties &obj)
{
    selfCopy(obj);
}

StreamCameraProperties &StreamCameraProperties::operator =(const StreamCameraProperties &obj)
{
    OPERATOR_EQUAL_BODY;
}

StreamCameraProperties::StreamCameraProperties(const QJsonObject &json)
{
    if (!IJsonable::typeFromJsonObject(json))
        return;
    if ( !json.contains("mCameraUid") ||
         !json.contains("mStreamCameraTypeUid") ||
         !json.contains("mUrl") ||
         !json.contains("mDescription") ||
         !json.contains("mIsRecording") ||
         !json.contains("mStreamCameraStatusUid")
         )
        return;
    JSON_TO_QUUID(json, mCameraUid);
    JSON_TO_QUUID(json, mStreamCameraTypeUid);
    JSON_TO_QSTRING(json, mUrl);
    JSON_TO_QSTRING(json, mDescription);
    JSON_TO_BOOL(json, mIsRecording);
    JSON_TO_QUUID(json, mStreamCameraStatusUid);
}

void StreamCameraProperties::selfCopy(const StreamCameraProperties &obj)
{
    mCameraUid = obj.mCameraUid;
    mStreamCameraTypeUid = obj.mStreamCameraTypeUid;
    mUrl = obj.mUrl;
    mDescription = obj.mDescription;
    mIsRecording = obj.mIsRecording;
    mStreamCameraStatusUid = obj.mStreamCameraStatusUid;
}

EDataType StreamCameraProperties::type() const
{
    return EDataType::StreamCameraProperties;
}

QJsonObject StreamCameraProperties::toJsonObject() const
{
    QJsonObject object;
    IJsonable::typeToJsonObject(object);
    QUUID_TO_JSON(mCameraUid, object);
    QUUID_TO_JSON(mStreamCameraTypeUid, object);
    QSTRING_TO_JSON(mUrl, object);
    QSTRING_TO_JSON(mDescription, object);
    BOOL_TO_JSON(mIsRecording, object);
    QUUID_TO_JSON(mStreamCameraStatusUid, object);
    return object;
}

bool StreamCameraProperties::isValid() const
{
    return !mCameraUid.isNull();
}

/// \remark GroupProperties

GroupProperties::GroupProperties():
    mName(""), mDescription("")
{

}

GroupProperties::GroupProperties(const QString& name, const QString& description):
     mName(name), mDescription(description)
{

}

GroupProperties::GroupProperties(const GroupProperties &obj)
{
    selfCopy(obj);
}

GroupProperties &GroupProperties::operator =(const GroupProperties &obj)
{
    OPERATOR_EQUAL_BODY;
}

GroupProperties::GroupProperties(const QJsonObject &json)
{
    if (!IJsonable::typeFromJsonObject(json))
        return;
    if ( !json.contains("mName") ||
         !json.contains("mDescription")
         )
        return;
    JSON_TO_QSTRING(json, mName);
    JSON_TO_QSTRING(json, mDescription);
}

void GroupProperties::selfCopy(const GroupProperties &obj)
{
    mName = obj.mName;
    mDescription = obj.mDescription;
}

EDataType GroupProperties::type() const
{
    return EDataType::GroupProperties;
}

QJsonObject GroupProperties::toJsonObject() const
{
    QJsonObject object;
    IJsonable::typeToJsonObject(object);
    QSTRING_TO_JSON(mName, object);
    QSTRING_TO_JSON(mDescription, object);
    return object;
}

bool GroupProperties::isValid() const
{
    return !mName.isEmpty();
}

/// \remark LayoutProperties

LayoutProperties::LayoutProperties():
    mName(""), mDescription("")
{

}

LayoutProperties::LayoutProperties(const QString& name, const QString& description):
     mName(name), mDescription(description)
{

}

LayoutProperties::LayoutProperties(const LayoutProperties &obj)
{
    selfCopy(obj);
}

LayoutProperties &LayoutProperties::operator =(const LayoutProperties &obj)
{
    OPERATOR_EQUAL_BODY;
}

LayoutProperties::LayoutProperties(const QJsonObject &json)
{
    if (!IJsonable::typeFromJsonObject(json))
        return;
    if ( !json.contains("mName") ||
         !json.contains("mDescription")
         )
        return;
    JSON_TO_QSTRING(json, mName);
    JSON_TO_QSTRING(json, mDescription);
}

void LayoutProperties::selfCopy(const LayoutProperties &obj)
{
    mName = obj.mName;
    mDescription = obj.mDescription;
}

EDataType LayoutProperties::type() const
{
    return EDataType::LayoutProperties;
}

QJsonObject LayoutProperties::toJsonObject() const
{
    QJsonObject object;
    IJsonable::typeToJsonObject(object);
    QSTRING_TO_JSON(mName, object);
    QSTRING_TO_JSON(mDescription, object);
    return object;
}

bool LayoutProperties::isValid() const
{
    return !mName.isEmpty();
}

/// \remark UserProfileProperties

UserProfileProperties::UserProfileProperties():
    mUserUid(QUuid()), mLayoutUid(QUuid())
{

}

UserProfileProperties::UserProfileProperties(const QUuid& userUid, const QUuid& layoutUid):
     mUserUid(userUid), mLayoutUid(layoutUid)
{

}

UserProfileProperties::UserProfileProperties(const UserProfileProperties &obj)
{
    selfCopy(obj);
}

UserProfileProperties &UserProfileProperties::operator =(const UserProfileProperties &obj)
{
    OPERATOR_EQUAL_BODY;
}

UserProfileProperties::UserProfileProperties(const QJsonObject &json)
{
    if (!IJsonable::typeFromJsonObject(json))
        return;
    if ( !json.contains("mUserUid") ||
         !json.contains("mLayoutUid")
         )
        return;
    JSON_TO_QUUID(json, mUserUid);
    JSON_TO_QUUID(json, mLayoutUid);
}

void UserProfileProperties::selfCopy(const UserProfileProperties &obj)
{
    mUserUid = obj.mUserUid;
    mLayoutUid = obj.mLayoutUid;
}

EDataType UserProfileProperties::type() const
{
    return EDataType::UserProfileProperties;
}

QJsonObject UserProfileProperties::toJsonObject() const
{
    QJsonObject object;
    IJsonable::typeToJsonObject(object);
    QUUID_TO_JSON(mUserUid, object);
    QUUID_TO_JSON(mLayoutUid, object);
    return object;
}

bool UserProfileProperties::isValid() const
{
    return !mUserUid.isNull() && !mLayoutUid.isNull();
}

/// \remark LayoutItemProperties

LayoutItemProperties::LayoutItemProperties():
    mLayoutUid(QUuid()), mRow(0), mColumn(0), mRows(0), mColumns(0)
{

}

LayoutItemProperties::LayoutItemProperties(const QUuid& layoutUid, int row, int column, int rows, int columns):
     mLayoutUid(layoutUid), mRow(row), mColumn(column), mRows(rows), mColumns(columns)
{

}

LayoutItemProperties::LayoutItemProperties(const LayoutItemProperties &obj)
{
    selfCopy(obj);
}

LayoutItemProperties &LayoutItemProperties::operator =(const LayoutItemProperties &obj)
{
    OPERATOR_EQUAL_BODY;
}

LayoutItemProperties::LayoutItemProperties(const QJsonObject &json)
{
    if (!IJsonable::typeFromJsonObject(json))
        return;
    if ( !json.contains("mLayoutUid") ||
         !json.contains("mRow") ||
         !json.contains("mColumn") ||
         !json.contains("mRows") ||
         !json.contains("mColumns")
         )
        return;
    JSON_TO_QUUID(json, mLayoutUid);
    JSON_TO_INT(json, mRow);
    JSON_TO_INT(json, mColumn);
    JSON_TO_INT(json, mRows);
    JSON_TO_INT(json, mColumns);
}

void LayoutItemProperties::selfCopy(const LayoutItemProperties &obj)
{
    mLayoutUid = obj.mLayoutUid;
    mRow = obj.mRow;
    mColumn = obj.mColumn;
    mRows = obj.mRows;
    mColumns = obj.mColumns;
}

EDataType LayoutItemProperties::type() const
{
    return EDataType::LayoutItemProperties;
}

QJsonObject LayoutItemProperties::toJsonObject() const
{
    QJsonObject object;
    IJsonable::typeToJsonObject(object);
    QUUID_TO_JSON(mLayoutUid, object);
    INT_TO_JSON(mRow, object);
    INT_TO_JSON(mColumn, object);
    INT_TO_JSON(mRows, object);
    INT_TO_JSON(mColumns, object);
    return object;
}

bool LayoutItemProperties::isValid() const
{
    return !mLayoutUid.isNull();
}

/// \remark ProfileProperties

ProfileItemProperties::ProfileItemProperties():
    mProfileUid(QUuid()), mLayoutItemUid(QUuid()), mStreamUid(QUuid())
{

}

ProfileItemProperties::ProfileItemProperties(const QUuid& profileUid, const QUuid& layoutItemUid, const QUuid& streamUid):
     mProfileUid(profileUid), mLayoutItemUid(layoutItemUid), mStreamUid(streamUid)
{

}

ProfileItemProperties::ProfileItemProperties(const ProfileItemProperties &obj)
{
    selfCopy(obj);
}

ProfileItemProperties &ProfileItemProperties::operator =(const ProfileItemProperties &obj)
{
    OPERATOR_EQUAL_BODY;
}

ProfileItemProperties::ProfileItemProperties(const QJsonObject &json)
{
    if (!IJsonable::typeFromJsonObject(json))
        return;
    if ( !json.contains("mProfileUid") ||
         !json.contains("mLayoutItemUid") ||
         !json.contains("mStreamUid")
         )
        return;
    JSON_TO_QUUID(json, mProfileUid);
    JSON_TO_QUUID(json, mLayoutItemUid);
    JSON_TO_QUUID(json, mStreamUid);
}

void ProfileItemProperties::selfCopy(const ProfileItemProperties &obj)
{
    mProfileUid = obj.mProfileUid;
    mLayoutItemUid = obj.mLayoutItemUid;
    mStreamUid = obj.mStreamUid;
}

EDataType ProfileItemProperties::type() const
{
    return EDataType::ProfileItemProperties;
}

QJsonObject ProfileItemProperties::toJsonObject() const
{
    QJsonObject object;
    IJsonable::typeToJsonObject(object);
    QUUID_TO_JSON(mProfileUid, object);
    QUUID_TO_JSON(mLayoutItemUid, object);
    QUUID_TO_JSON(mStreamUid, object);
    return object;
}

bool ProfileItemProperties::isValid() const
{
    return !mProfileUid.isNull();
}

/// \remark StreamCameraStatusProperties

StreamCameraStatusProperties::StreamCameraStatusProperties():
    mDescription(""), mRelevance(0)
{

}

StreamCameraStatusProperties::StreamCameraStatusProperties(const QString& description, int relevance):
     mDescription(description), mRelevance(relevance)
{

}

StreamCameraStatusProperties::StreamCameraStatusProperties(const StreamCameraStatusProperties &obj)
{
    selfCopy(obj);
}

StreamCameraStatusProperties &StreamCameraStatusProperties::operator =(const StreamCameraStatusProperties &obj)
{
    OPERATOR_EQUAL_BODY;
}

StreamCameraStatusProperties::StreamCameraStatusProperties(const QJsonObject &json)
{
    if (!IJsonable::typeFromJsonObject(json))
        return;
    if ( !json.contains("mDescription") ||
         !json.contains("mRelevance")
         )
        return;
    JSON_TO_QSTRING(json, mDescription);
    JSON_TO_INT(json, mRelevance);
}

void StreamCameraStatusProperties::selfCopy(const StreamCameraStatusProperties &obj)
{
    mDescription = obj.mDescription;
    mRelevance = obj.mRelevance;;
}

EDataType StreamCameraStatusProperties::type() const
{
    return EDataType::StreamCameraStatusProperties;
}

QJsonObject StreamCameraStatusProperties::toJsonObject() const
{
    QJsonObject object;
    IJsonable::typeToJsonObject(object);
    QSTRING_TO_JSON(mDescription, object);
    INT_TO_JSON(mRelevance, object);
    return object;
}

bool StreamCameraStatusProperties::isValid() const
{
    return true;
}

/// \remark StreamCameraTypeProperties

StreamCameraTypeProperties::StreamCameraTypeProperties():
    mName(""), mDescription("")
{

}

StreamCameraTypeProperties::StreamCameraTypeProperties(const QString& name, const QString& description):
     mName(name), mDescription(description)
{

}

StreamCameraTypeProperties::StreamCameraTypeProperties(const StreamCameraTypeProperties &obj)
{
    selfCopy(obj);
}

StreamCameraTypeProperties &StreamCameraTypeProperties::operator =(const StreamCameraTypeProperties &obj)
{
    OPERATOR_EQUAL_BODY;
}

StreamCameraTypeProperties::StreamCameraTypeProperties(const QJsonObject &json)
{
    if (!IJsonable::typeFromJsonObject(json))
        return;
    if ( !json.contains("mName") ||
         !json.contains("mDescription")
         )
        return;
    JSON_TO_QSTRING(json, mName);
    JSON_TO_QSTRING(json, mDescription);
}

void StreamCameraTypeProperties::selfCopy(const StreamCameraTypeProperties &obj)
{
    mName = obj.mName;
    mDescription = obj.mDescription;
}

EDataType StreamCameraTypeProperties::type() const
{
    return EDataType::StreamCameraTypeProperties;
}

QJsonObject StreamCameraTypeProperties::toJsonObject() const
{
    QJsonObject object;
    IJsonable::typeToJsonObject(object);
    QSTRING_TO_JSON(mName, object);
    QSTRING_TO_JSON(mDescription, object);
    return object;
}

bool StreamCameraTypeProperties::isValid() const
{
    return true;
}

/// \remark ServerProperties

ServerProperties::ServerProperties():
    mName(""), mDescription(""), mIpAddress("")
{

}

ServerProperties::ServerProperties(const QString& name, const QString& description, const QString &ipAddress):
     mName(name), mDescription(description), mIpAddress(ipAddress)
{

}

ServerProperties::ServerProperties(const ServerProperties &obj)
{
    selfCopy(obj);
}

ServerProperties &ServerProperties::operator =(const ServerProperties &obj)
{
    OPERATOR_EQUAL_BODY;
}

ServerProperties::ServerProperties(const QJsonObject &json)
{
    if (!IJsonable::typeFromJsonObject(json))
        return;
    if ( !json.contains("mName") ||
         !json.contains("mDescription") ||
         !json.contains("mIpAddress")
         )
        return;
    JSON_TO_QSTRING(json, mName);
    JSON_TO_QSTRING(json, mDescription);
    JSON_TO_QSTRING(json, mIpAddress);
}

void ServerProperties::selfCopy(const ServerProperties &obj)
{
    mName = obj.mName;
    mDescription = obj.mDescription;
    mIpAddress = obj.mIpAddress;
}

EDataType ServerProperties::type() const
{
    return EDataType::ServerProperties;
}

QJsonObject ServerProperties::toJsonObject() const
{
    QJsonObject object;
    IJsonable::typeToJsonObject(object);
    QSTRING_TO_JSON(mName, object);
    QSTRING_TO_JSON(mDescription, object);
    QSTRING_TO_JSON(mIpAddress, object);
    return object;
}

bool ServerProperties::isValid() const
{
    return true;
}

/// \remark LicenceProperties

LicenceProperties::LicenceProperties():
    mGenerationDateTime(QDateTime()),
    mUser(QString()),
    mKey(QString()),
    mKeyType(false),
    mCustomer(QString()),
    mParameters(QString()),
    mEndDateTime(QDateTime()),
    cCurrentState(QString()),
    cCpuid(QString()),
    cHaspKey(QString()),
    cErrorCode(0)
{

}

LicenceProperties::LicenceProperties(const QDateTime& generationDateTime,
                                     const QString& user,
                                     const QString& key,
                                     const bool& keyType,
                                     const QString& customer,
                                     const QString& parameters,
                                     const QDateTime& endDateTime,
                                     const QString& currentState,
                                     const QString& cpuIdServer,
                                     const QString& haspKey,
                                     const int& message):
    mGenerationDateTime(generationDateTime),
    mUser(user),
    mKey(key),
    mKeyType(keyType),
    mCustomer(customer),
    mParameters(parameters),
    mEndDateTime(endDateTime),
    cCurrentState(currentState),
    cCpuid(cpuIdServer),
    cHaspKey(haspKey),
    cErrorCode(message)
{

}

LicenceProperties::LicenceProperties(const LicenceProperties &obj)
{
    selfCopy(obj);
}

LicenceProperties &LicenceProperties::operator =(const LicenceProperties &obj)
{
    OPERATOR_EQUAL_BODY;
}

LicenceProperties::LicenceProperties(const QJsonObject &json)
{
    if (!IJsonable::typeFromJsonObject(json))
        return;
    if ( !json.contains("mGenerationDateTime") ||
         !json.contains("mUser") ||
         !json.contains("mKey") ||
         !json.contains("mKeyType") ||
         !json.contains("mCustomer") ||
         !json.contains("mParameters") ||
         !json.contains("mEndDateTime") ||
         !json.contains("cCurrentState") ||
         !json.contains("cCpuid") ||
         !json.contains("cHaspKey") ||
         !json.contains("cErrorCode")
         )
    {
        return;
    }
    JSON_TO_QDATETIME(json, mGenerationDateTime);
    JSON_TO_QSTRING(json, mUser);
    JSON_TO_QSTRING(json, mKey);
    JSON_TO_BOOL(json, mKeyType);
    JSON_TO_QSTRING(json, mCustomer);
    JSON_TO_QSTRING(json, mParameters);
    JSON_TO_QDATETIME(json, mEndDateTime);
    JSON_TO_QSTRING(json, cCurrentState);
    JSON_TO_QSTRING(json, cCpuid);
    JSON_TO_QSTRING(json, cHaspKey);
    JSON_TO_INT(json, cErrorCode);
}

void LicenceProperties::selfCopy(const LicenceProperties &obj)
{
    mGenerationDateTime = obj.mGenerationDateTime;
    mUser = obj.mUser;
    mKey = obj.mKey;
    mKeyType = obj.mKeyType;
    mCustomer = obj.mCustomer;
    mParameters = obj.mParameters;
    mEndDateTime = obj.mEndDateTime;
    cCurrentState = obj.cCurrentState;
    cCpuid = obj.cCpuid;
    cHaspKey = obj.cHaspKey;
    cErrorCode = obj.cErrorCode;
}

EDataType LicenceProperties::type() const
{
    return EDataType::LicenceProperties;
}

QJsonObject LicenceProperties::toJsonObject() const
{
    QJsonObject object;
    IJsonable::typeToJsonObject(object);
    QDATETIME_TO_JSON(mGenerationDateTime, object);
    QSTRING_TO_JSON(mUser, object);
    QSTRING_TO_JSON(mKey, object);
    BOOL_TO_JSON(mKeyType, object);
    QSTRING_TO_JSON(mCustomer, object);
    QSTRING_TO_JSON(mParameters, object);
    QDATETIME_TO_JSON(mEndDateTime, object);
    QSTRING_TO_JSON(cCurrentState, object);
    QSTRING_TO_JSON(cCpuid, object);
    QSTRING_TO_JSON(cHaspKey, object);
    INT_TO_JSON(cErrorCode, object);
    return object;
}

bool LicenceProperties::isValid() const
{
    bool ret_urn = true;
    if (mGenerationDateTime.isNull() ||
            mUser.isEmpty() ||
            mKey.isEmpty() ||
            mCustomer.isEmpty() ||
            mParameters.isEmpty() ||
            cCurrentState.isEmpty() ||
            cErrorCode < 0)
    {
        ret_urn = false;
    }

    return ret_urn;
}

ClientProperties::ClientProperties():
    mIp(""), mLogin("")
{

}

ClientProperties::ClientProperties(const ClientProperties &obj)
{
    selfCopy(obj);
}

ClientProperties &ClientProperties::operator =(const ClientProperties &obj)
{
    OPERATOR_EQUAL_BODY;
}

ClientProperties::ClientProperties(const QJsonObject &json)
{
    if (!IJsonable::typeFromJsonObject(json))
        return;
    if ( !json.contains("mIp") ||
         !json.contains("mLogin")
         )
        return;
    JSON_TO_QSTRING(json, mIp);
    JSON_TO_QSTRING(json, mLogin);
}

void ClientProperties::selfCopy(const ClientProperties &obj)
{
    mIp = obj.mIp;
    mLogin = obj.mLogin;
}

EDataType ClientProperties::type() const
{
    return EDataType::ClientProperties;
}

QJsonObject ClientProperties::toJsonObject() const
{
    QJsonObject object;
    IJsonable::typeToJsonObject(object);
    QSTRING_TO_JSON(mIp, object);
    QSTRING_TO_JSON(mLogin, object);
    return object;
}

bool ClientProperties::isValid() const
{
    return true;
}





VRGetTimelineRequestParameters::VRGetTimelineRequestParameters():
    mStreams(), mStartMsecsSinceEpoch(0), mEndMsecsSinceEpoch(0)
{

}

VRGetTimelineRequestParameters::VRGetTimelineRequestParameters(const VRGetTimelineRequestParameters &obj)
{
    selfCopy(obj);
}

VRGetTimelineRequestParameters &VRGetTimelineRequestParameters::operator =(const VRGetTimelineRequestParameters &obj)
{
    OPERATOR_EQUAL_BODY;
}

VRGetTimelineRequestParameters::VRGetTimelineRequestParameters(const QJsonObject &json)
{
    if (!IJsonable::typeFromJsonObject(json))
        return;
    if ( !json.contains("mStreams") ||
         !json.contains("mStartMsecsSinceEpoch") ||
         !json.contains("mEndMsecsSinceEpoch")
         )
        return;
    JSON_TO_LONG_LONG(json, mStartMsecsSinceEpoch);
    JSON_TO_LONG_LONG(json, mEndMsecsSinceEpoch);
    mStreams.clear();
    auto streamsArray = json.value("mStreams").toArray();
    for (auto strIt = 0; strIt < streamsArray.count(); ++strIt)
    {
        auto strObj = streamsArray[strIt].toObject();
        if ( !strObj.contains("streamId") ||
             !strObj.contains("streamUuid") ||
             !strObj.contains("VRParameters")
             )
            continue;
        StreamParameters stream;
        stream.streamId = strObj.value("streamId").toObject();
        stream.streamUuid = QUuid(strObj.value("streamUuid").toString());
        stream.VRParameters = strObj.value("VRParameters").toString();
        mStreams.append(stream);
    }
}

void VRGetTimelineRequestParameters::selfCopy(const VRGetTimelineRequestParameters &obj)
{
    mStreams = obj.mStreams;
    mStartMsecsSinceEpoch = obj.mStartMsecsSinceEpoch;
    mEndMsecsSinceEpoch = obj.mEndMsecsSinceEpoch;
}

EDataType VRGetTimelineRequestParameters::type() const
{
    return EDataType::VRGetTimelineRequestParameters;
}

QJsonObject VRGetTimelineRequestParameters::toJsonObject() const
{
    QJsonObject object;
    IJsonable::typeToJsonObject(object);
    LONG_LONG_TO_JSON(mStartMsecsSinceEpoch, object);
    LONG_LONG_TO_JSON(mEndMsecsSinceEpoch, object);
    QJsonArray streamsArray;
    for (auto strIt = 0; strIt < mStreams.count(); ++strIt)
    {
        QJsonObject strObj;
        auto currStream = mStreams[strIt];
        strObj.insert("streamId", currStream.streamId);
        strObj.insert("streamUuid", QJsonValue::fromVariant(currStream.streamUuid));
        strObj.insert("VRParameters", QJsonValue::fromVariant(currStream.VRParameters));
        streamsArray.append(strObj);
    }
    object.insert("mStreams", streamsArray);
    return object;
}

bool VRGetTimelineRequestParameters::isValid() const
{
    return true;
}
