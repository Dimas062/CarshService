#include "interactionprotocolcameramanage.h"

// ------------------------------------------------
// ----- RequestGetCameraParameters
// ------------------------------------------------

RequestGetCameraParameters::RequestGetCameraParameters(): IJsonable(), ICommonFields()
{

}

RequestGetCameraParameters::RequestGetCameraParameters(const RequestGetCameraParameters &obj):IJsonable(), ICommonFields()
{
    selfCopy(obj);
}

RequestGetCameraParameters &RequestGetCameraParameters::operator =(const RequestGetCameraParameters &obj)
{
    OPERATOR_EQUAL_BODY;
}

RequestGetCameraParameters::RequestGetCameraParameters(const QJsonObject &json)
{
    if (!IJsonable::typeFromJsonObject(json))
        return;
    if ( !json.contains("mCameraUid") ||
         !json.contains("mStreamType")
         )
        return;
    ICommonFields::fromJsonObject(json);
    JSON_TO_QUUID(json, mCameraUid);
    JSON_TO_INT(json, mStreamType);
}

bool RequestGetCameraParameters::isValid() const
{
    if (!mCameraUid.isNull())
        return true;
    else
        return false;
}

EDataType RequestGetCameraParameters::type() const { return EDataType::RequestGetCameraParameters; }

QJsonObject RequestGetCameraParameters::toJsonObject() const
{
    QJsonObject object;
    ICommonFields::toJsonObject(object);
    IJsonable::typeToJsonObject(object);
    QUUID_TO_JSON(mCameraUid, object);
    INT_TO_JSON(mStreamType, object);
    return object;
}

void RequestGetCameraParameters::selfCopy(const RequestGetCameraParameters &obj)
{
    mUidRequest = obj.mUidRequest;
    mCameraUid = obj.mCameraUid;
    mStreamType = obj.mStreamType;
}

// ResponseGetCameraParameters

ResponseGetCameraParameters::ResponseGetCameraParameters():IJsonable(), ICommonFields(), IResponseResultable()
{

}

ResponseGetCameraParameters &ResponseGetCameraParameters::operator =(const ResponseGetCameraParameters &obj)
{
    OPERATOR_EQUAL_BODY;
}

ResponseGetCameraParameters::ResponseGetCameraParameters(const ResponseGetCameraParameters &obj):IJsonable(), ICommonFields(), IResponseResultable()
{
   selfCopy(obj);
}

ResponseGetCameraParameters::ResponseGetCameraParameters(const QJsonObject &json)
{
    if ( !IJsonable::typeFromJsonObject(json) ||
         !IResponseResultable::resultResponseFromJsonObject(json)  )
        return;
    if ( !json.contains("mJsonParameters") )
        return;
    ICommonFields::fromJsonObject(json);
    JSON_TO_QSTRING(json, mJsonParameters);
}

void ResponseGetCameraParameters::selfCopy(const ResponseGetCameraParameters &obj)
{
    mUidRequest = obj.mUidRequest;
    mResponseResult = obj.mResponseResult;
    mJsonParameters = obj.mJsonParameters;
}

EDataType ResponseGetCameraParameters::type() const
{
    return EDataType::ResponseGetCameraParameters;
}

QJsonObject ResponseGetCameraParameters::toJsonObject() const
{
    QJsonObject object;
    ICommonFields::toJsonObject(object);
    IJsonable::typeToJsonObject(object);
    IResponseResultable::resultResponseToJsonObject(object);
    QSTRING_TO_JSON(mJsonParameters, object);
    return object;
}

bool ResponseGetCameraParameters::isValid() const
{
    return true;
}

// ------------------------------------------------
// ----- RequestSetCameraParameters
// ------------------------------------------------

RequestSetCameraParameters::RequestSetCameraParameters(): IJsonable(), ICommonFields()
{

}

RequestSetCameraParameters::RequestSetCameraParameters(const RequestSetCameraParameters &obj):IJsonable(), ICommonFields()
{
    selfCopy(obj);
}

RequestSetCameraParameters &RequestSetCameraParameters::operator =(const RequestSetCameraParameters &obj)
{
    OPERATOR_EQUAL_BODY;
}

RequestSetCameraParameters::RequestSetCameraParameters(const QJsonObject &json)
{
    if (!IJsonable::typeFromJsonObject(json))
        return;
    if ( !json.contains("mCameraUid") ||
         !json.contains("mJsonParameters")
         )
        return;
    ICommonFields::fromJsonObject(json);
    JSON_TO_QUUID(json, mCameraUid);
    JSON_TO_QSTRING(json, mJsonParameters);
}

bool RequestSetCameraParameters::isValid() const
{
    if (!mCameraUid.isNull())
        return true;
    else
        return false;
}

EDataType RequestSetCameraParameters::type() const { return EDataType::RequestSetCameraParameters; }

QJsonObject RequestSetCameraParameters::toJsonObject() const
{
    QJsonObject object;
    ICommonFields::toJsonObject(object);
    IJsonable::typeToJsonObject(object);
    QUUID_TO_JSON(mCameraUid, object);
    QSTRING_TO_JSON(mJsonParameters, object);
    return object;
}

void RequestSetCameraParameters::selfCopy(const RequestSetCameraParameters &obj)
{
    mUidRequest = obj.mUidRequest;
    mCameraUid = obj.mCameraUid;
    mJsonParameters = obj.mJsonParameters;
}

// ResponseSetCameraParameters

ResponseSetCameraParameters::ResponseSetCameraParameters():IJsonable(), ICommonFields(), IResponseResultable()
{

}

ResponseSetCameraParameters &ResponseSetCameraParameters::operator =(const ResponseSetCameraParameters &obj)
{
    OPERATOR_EQUAL_BODY;
}

ResponseSetCameraParameters::ResponseSetCameraParameters(const ResponseSetCameraParameters &obj):IJsonable(), ICommonFields(), IResponseResultable()
{
   selfCopy(obj);
}

ResponseSetCameraParameters::ResponseSetCameraParameters(const QJsonObject &json)
{
    if ( !IJsonable::typeFromJsonObject(json) ||
         !IResponseResultable::resultResponseFromJsonObject(json)  )
        return;
    ICommonFields::fromJsonObject(json);
}

void ResponseSetCameraParameters::selfCopy(const ResponseSetCameraParameters &obj)
{
    mUidRequest = obj.mUidRequest;
    mResponseResult = obj.mResponseResult;
}

EDataType ResponseSetCameraParameters::type() const
{
    return EDataType::ResponseSetCameraParameters;
}

QJsonObject ResponseSetCameraParameters::toJsonObject() const
{
    QJsonObject object;
    ICommonFields::toJsonObject(object);
    IJsonable::typeToJsonObject(object);
    IResponseResultable::resultResponseToJsonObject(object);
    return object;
}

bool ResponseSetCameraParameters::isValid() const
{
    return true;
}

// ------------------------------------------------
// ----- RequestRebootCamera
// ------------------------------------------------

RequestRebootCamera::RequestRebootCamera(): IJsonable(), ICommonFields()
{

}

RequestRebootCamera::RequestRebootCamera(const RequestRebootCamera &obj):IJsonable(), ICommonFields()
{
    selfCopy(obj);
}

RequestRebootCamera &RequestRebootCamera::operator =(const RequestRebootCamera &obj)
{
    OPERATOR_EQUAL_BODY;
}

RequestRebootCamera::RequestRebootCamera(const QJsonObject &json)
{
    if (!IJsonable::typeFromJsonObject(json))
        return;
    if ( !json.contains("mCameraUid")
         )
        return;
    ICommonFields::fromJsonObject(json);
    JSON_TO_QUUID(json, mCameraUid);
}

bool RequestRebootCamera::isValid() const
{
    if (!mCameraUid.isNull())
        return true;
    else
        return false;
}

EDataType RequestRebootCamera::type() const { return EDataType::RequestRebootCamera; }

QJsonObject RequestRebootCamera::toJsonObject() const
{
    QJsonObject object;
    ICommonFields::toJsonObject(object);
    IJsonable::typeToJsonObject(object);
    QUUID_TO_JSON(mCameraUid, object);
    return object;
}

void RequestRebootCamera::selfCopy(const RequestRebootCamera &obj)
{
    mUidRequest = obj.mUidRequest;
    mCameraUid = obj.mCameraUid;
}

// ResponseRebootCamera

ResponseRebootCamera::ResponseRebootCamera():IJsonable(), ICommonFields(), IResponseResultable()
{

}

ResponseRebootCamera &ResponseRebootCamera::operator =(const ResponseRebootCamera &obj)
{
    OPERATOR_EQUAL_BODY;
}

ResponseRebootCamera::ResponseRebootCamera(const ResponseRebootCamera &obj):IJsonable(), ICommonFields(), IResponseResultable()
{
   selfCopy(obj);
}

ResponseRebootCamera::ResponseRebootCamera(const QJsonObject &json)
{
    if ( !IJsonable::typeFromJsonObject(json) ||
         !IResponseResultable::resultResponseFromJsonObject(json)  )
        return;
    ICommonFields::fromJsonObject(json);
}

void ResponseRebootCamera::selfCopy(const ResponseRebootCamera &obj)
{
    mUidRequest = obj.mUidRequest;
    mResponseResult = obj.mResponseResult;
}

EDataType ResponseRebootCamera::type() const
{
    return EDataType::ResponseRebootCamera;
}

QJsonObject ResponseRebootCamera::toJsonObject() const
{
    QJsonObject object;
    ICommonFields::toJsonObject(object);
    IJsonable::typeToJsonObject(object);
    IResponseResultable::resultResponseToJsonObject(object);
    return object;
}

bool ResponseRebootCamera::isValid() const
{
    return true;
}
