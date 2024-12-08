#include "interfaces.h"

/// \remark IJsonable

const QUuid &ICommonFields::uidRequest() const
{
    return mUidRequest;
}

void ICommonFields::setUidRequest(const QUuid &uid)
{
    mUidRequest = uid;
}

void ICommonFields::toJsonObject(QJsonObject &json) const
{
    json.insert(UID_REQUEST_TAG, QJsonValue::fromVariant(
                   uidRequest().toString()
                ));
}

void ICommonFields::fromJsonObject(const QJsonObject &json)
{
    setUidRequest(QUuid(json.value(UID_REQUEST_TAG).toString()));
}

void IJsonable::typeToJsonObject(QJsonObject &json) const
{
    json.insert(TYPE_TAG, QJsonValue::fromVariant(
                    QString::number(
                        static_cast<quint32>( type() )
                        )
                    )
                );
}

bool IJsonable::typeFromJsonObject(const QJsonObject &json)
{
    bool result = false;
    if ( json.isEmpty() || !json.contains(TYPE_TAG) )
        result = false;
    else
        result = true;
    if ( result ) {
        EDataType _type = EDataType::None;
        JSON_TO_ENUM(json, EDataType, _type);
        if ( type() == _type ) {
            result = true;
        } else {
            result = false;
        }

    }
    return result;
}

/// \remark IResponseResultable

void IResponseResultable::resultResponseToJsonObject(QJsonObject &json) const
{
    json.insert("mResponseResult", QJsonValue::fromVariant(
                    QString::number(
                        static_cast<quint32>( mResponseResult )
                        )
                    )
                );
}

bool IResponseResultable::resultResponseFromJsonObject(const QJsonObject &json)
{
    bool result = false;
    if ( json.isEmpty() || !json.contains("mResponseResult") )
        result = false;
    else
        result = true;
    if ( result ) {
        mResponseResult = static_cast<EResult>(
                    json.value("mResponseResult").toString().toUInt()
                    );
        result = true;
    }
    return result;
}

void IRequestVR::toJsonObject(QJsonObject &json) const
{
    json.insert("mVRJsonParameters", QJsonValue::fromVariant(mVRJsonParameters));
    json.insert("mVendor", QJsonValue::fromVariant( QVariant( static_cast<unsigned int>(mVendor) ) ));
}

void IRequestVR::fromJsonObject(const QJsonObject &json)
{
    if ( json.isEmpty() || !json.contains("mVRJsonParameters") ) {
        return;
    } else {
        mVRJsonParameters = json.value("mVRJsonParameters").toString();
        mVendor = static_cast<quint8>(json.value("mVendor").toVariant().toUInt());
    }
}
