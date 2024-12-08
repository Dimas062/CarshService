#include "interactionprotocolvideorecorder.h"

// RequestCreateRtspStreamVideoVR
RequestCreateRtspStreamVideoVR &RequestCreateRtspStreamVideoVR::operator =(const RequestCreateRtspStreamVideoVR &obj)
{
    OPERATOR_EQUAL_BODY;
}
RequestCreateRtspStreamVideoVR::RequestCreateRtspStreamVideoVR():IJsonable(), ICommonFields(), IRequestVR()
{

}

RequestCreateRtspStreamVideoVR::RequestCreateRtspStreamVideoVR(const RequestCreateRtspStreamVideoVR &obj):IJsonable(), ICommonFields(), IRequestVR()
{
    selfCopy(obj);
}

RequestCreateRtspStreamVideoVR::RequestCreateRtspStreamVideoVR(const QJsonObject &json)
{
    if ( !IJsonable::typeFromJsonObject(json)
         )
        return;
    ICommonFields::fromJsonObject(json);
    IRequestVR::fromJsonObject(json);
    JSON_TO_QUUID(json, mRtspStreamUid);
    streamId = json.value("streamId").toObject();
    JSON_TO_QDATETIME(json, dt);
    speed = json.value("speed").toInt();
    needPreview = json.value("needPreview").toBool();
}

void RequestCreateRtspStreamVideoVR::selfCopy(const RequestCreateRtspStreamVideoVR &obj)
{
    mUidRequest = obj.mUidRequest;
    IRequestVR::selfCopyIRequestVR(obj);
    mRtspStreamUid = obj.mRtspStreamUid;
    streamId = obj.streamId;
    dt = obj.dt;
    speed = obj.speed;
    needPreview = obj.needPreview;
}

EDataType RequestCreateRtspStreamVideoVR::type() const
{
    return EDataType::RequestCreateRtspStreamVideoVR;
}

QJsonObject RequestCreateRtspStreamVideoVR::toJsonObject() const
{
    QJsonObject object;
    ICommonFields::toJsonObject(object);
    IJsonable::typeToJsonObject(object);
    IRequestVR::toJsonObject(object);
    QUUID_TO_JSON(mRtspStreamUid, object);
    object.insert("streamId", streamId);
    QDATETIME_TO_JSON(dt, object);
    object.insert("speed", QJsonValue::fromVariant(speed));
    object.insert("needPreview", QJsonValue::fromVariant(needPreview));
    return object;
}

bool RequestCreateRtspStreamVideoVR::isValid() const
{
    return true;
}

// RequestStartRtspStreamVideoVR
RequestStartRtspStreamVideoVR &RequestStartRtspStreamVideoVR::operator =(const RequestStartRtspStreamVideoVR &obj)
{
    OPERATOR_EQUAL_BODY;
}
RequestStartRtspStreamVideoVR::RequestStartRtspStreamVideoVR():IJsonable(), ICommonFields(), IRequestVR()
{

}

RequestStartRtspStreamVideoVR::RequestStartRtspStreamVideoVR(const RequestStartRtspStreamVideoVR &obj):IJsonable(), ICommonFields(), IRequestVR()
{
   selfCopy(obj);
}

RequestStartRtspStreamVideoVR::RequestStartRtspStreamVideoVR(const QJsonObject &json)
{
    if ( !IJsonable::typeFromJsonObject(json)
         )
        return;
    ICommonFields::fromJsonObject(json);
    IRequestVR::fromJsonObject(json);
    JSON_TO_QUUID(json, mRtspStreamUid);
    JSON_TO_QSTRING(json, transToken);
    JSON_TO_QDATETIME(json, dt);
    speed = json.value("speed").toInt();
}

void RequestStartRtspStreamVideoVR::selfCopy(const RequestStartRtspStreamVideoVR &obj)
{
    mUidRequest = obj.mUidRequest;
    IRequestVR::selfCopyIRequestVR(obj);
    mRtspStreamUid = obj.mRtspStreamUid;
    transToken = obj.transToken;
    dt = obj.dt;
    speed = obj.speed;
}

EDataType RequestStartRtspStreamVideoVR::type() const
{
    return EDataType::RequestStartRtspStreamVideoVR;
}

QJsonObject RequestStartRtspStreamVideoVR::toJsonObject() const
{
    QJsonObject object;
    ICommonFields::toJsonObject(object);
    IJsonable::typeToJsonObject(object);
    IRequestVR::toJsonObject(object);
    QUUID_TO_JSON(mRtspStreamUid, object);
    QSTRING_TO_JSON(transToken, object);
    QDATETIME_TO_JSON(dt, object);
    object.insert("speed", QJsonValue::fromVariant(speed));
    return object;
}

bool RequestStartRtspStreamVideoVR::isValid() const
{
    return true;
}

//RequestStopRtspStreamVideoVR
RequestStopRtspStreamVideoVR &RequestStopRtspStreamVideoVR::operator =(const RequestStopRtspStreamVideoVR &obj)
{
    OPERATOR_EQUAL_BODY;
}
RequestStopRtspStreamVideoVR::RequestStopRtspStreamVideoVR():IJsonable(), ICommonFields(), IRequestVR()
{

}

RequestStopRtspStreamVideoVR::RequestStopRtspStreamVideoVR(const RequestStopRtspStreamVideoVR &obj):IJsonable(), ICommonFields(), IRequestVR()
{
    selfCopy(obj);
}

RequestStopRtspStreamVideoVR::RequestStopRtspStreamVideoVR(const QJsonObject &json)
{
    if ( !IJsonable::typeFromJsonObject(json)
         )
        return;
    ICommonFields::fromJsonObject(json);
    IRequestVR::fromJsonObject(json);
    JSON_TO_QUUID(json, mRtspStreamUid);
    JSON_TO_QSTRING(json, transToken);
}

void RequestStopRtspStreamVideoVR::selfCopy(const RequestStopRtspStreamVideoVR &obj)
{
    mUidRequest = obj.mUidRequest;
    IRequestVR::selfCopyIRequestVR(obj);
    mRtspStreamUid = obj.mRtspStreamUid;
    transToken = obj.transToken;
}

EDataType RequestStopRtspStreamVideoVR::type() const
{
   return EDataType::RequestStopRtspStreamVideoVR;
}

QJsonObject RequestStopRtspStreamVideoVR::toJsonObject() const
{
    QJsonObject object;
    ICommonFields::toJsonObject(object);
    IJsonable::typeToJsonObject(object);
    IRequestVR::toJsonObject(object);
    QUUID_TO_JSON(mRtspStreamUid, object);
    QSTRING_TO_JSON(transToken, object);
    return object;
}

bool RequestStopRtspStreamVideoVR::isValid() const
{
    return true;
}

// RequestStartRtspStreamCameraVR
RequestStartRtspStreamCameraVR &RequestStartRtspStreamCameraVR::operator =(const RequestStartRtspStreamCameraVR &obj)
{
    OPERATOR_EQUAL_BODY;
}
RequestStartRtspStreamCameraVR::RequestStartRtspStreamCameraVR():IJsonable(), ICommonFields(), IRequestVR()
{

}

RequestStartRtspStreamCameraVR::RequestStartRtspStreamCameraVR(const RequestStartRtspStreamCameraVR &obj):IJsonable(), ICommonFields(), IRequestVR()
{
    selfCopy(obj);
}

RequestStartRtspStreamCameraVR::RequestStartRtspStreamCameraVR(const QJsonObject &json)
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
    IRequestVR::fromJsonObject(json);
    JSON_TO_QUUID(json, mStreamUid);
    JSON_TO_QUUID(json, mRtspStreamUid);
    JSON_TO_QUUID(json, mCameraUid);
    JSON_TO_QUUID(json, mCassyUid);
}

void RequestStartRtspStreamCameraVR::selfCopy(const RequestStartRtspStreamCameraVR &obj)
{
    mUidRequest = obj.mUidRequest;
    IRequestVR::selfCopyIRequestVR(obj);
    mStreamUid = obj.mStreamUid;
    mRtspStreamUid = obj.mRtspStreamUid;
    mCameraUid = obj.mCameraUid;
    mCassyUid = obj.mCassyUid;
}

EDataType RequestStartRtspStreamCameraVR::type() const
{
    return EDataType::RequestStartRtspStreamCameraVR;
}

QJsonObject RequestStartRtspStreamCameraVR::toJsonObject() const
{
    QJsonObject object;
    ICommonFields::toJsonObject(object);
    IJsonable::typeToJsonObject(object);
    IRequestVR::toJsonObject(object);
    QUUID_TO_JSON(mStreamUid, object);
    QUUID_TO_JSON(mRtspStreamUid, object);
    QUUID_TO_JSON(mCameraUid, object);
    QUUID_TO_JSON(mCassyUid, object);
    return object;
}

bool RequestStartRtspStreamCameraVR::isValid() const
{
    return true;
}

// RequestStopRtspStreamCameraVR
RequestStopRtspStreamCameraVR &RequestStopRtspStreamCameraVR::operator =(const RequestStopRtspStreamCameraVR &obj)
{
    OPERATOR_EQUAL_BODY;
}
RequestStopRtspStreamCameraVR::RequestStopRtspStreamCameraVR():IJsonable(), ICommonFields(), IRequestVR()
{

}

RequestStopRtspStreamCameraVR::RequestStopRtspStreamCameraVR(const RequestStopRtspStreamCameraVR &obj):IJsonable(), ICommonFields(), IRequestVR()
{
    selfCopy(obj);
}

RequestStopRtspStreamCameraVR::RequestStopRtspStreamCameraVR(const QJsonObject &json)
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
    IRequestVR::fromJsonObject(json);
    JSON_TO_QUUID(json, mStreamUid);
    JSON_TO_QUUID(json, mRtspStreamUid);
    JSON_TO_QUUID(json, mCameraUid);
    JSON_TO_QUUID(json, mCassyUid);
}

void RequestStopRtspStreamCameraVR::selfCopy(const RequestStopRtspStreamCameraVR &obj)
{
    mUidRequest = obj.mUidRequest;
    IRequestVR::selfCopyIRequestVR(obj);
    mStreamUid = obj.mStreamUid;
    mRtspStreamUid = obj.mRtspStreamUid;
    mCameraUid = obj.mCameraUid;
    mCassyUid = obj.mCassyUid;
}

EDataType RequestStopRtspStreamCameraVR::type() const
{
    return EDataType::RequestStopRtspStreamCameraVR;
}

QJsonObject RequestStopRtspStreamCameraVR::toJsonObject() const
{
    QJsonObject object;
    ICommonFields::toJsonObject(object);
    IJsonable::typeToJsonObject(object);
    IRequestVR::toJsonObject(object);
    QUUID_TO_JSON(mStreamUid, object);
    QUUID_TO_JSON(mRtspStreamUid, object);
    QUUID_TO_JSON(mCameraUid, object);
    QUUID_TO_JSON(mCassyUid, object);
    return object;
}

bool RequestStopRtspStreamCameraVR::isValid() const
{
    return true;
}

// RequestGetExistingArchiveTimelineVR
RequestGetExistingArchiveTimelineVR &RequestGetExistingArchiveTimelineVR::operator =(const RequestGetExistingArchiveTimelineVR &obj)
{
    OPERATOR_EQUAL_BODY;
}
RequestGetExistingArchiveTimelineVR::RequestGetExistingArchiveTimelineVR():IJsonable(), ICommonFields(), IRequestVR()
{

}

RequestGetExistingArchiveTimelineVR::RequestGetExistingArchiveTimelineVR(const RequestGetExistingArchiveTimelineVR &obj):IJsonable(), ICommonFields(), IRequestVR()
{
    selfCopy(obj);
}

RequestGetExistingArchiveTimelineVR::RequestGetExistingArchiveTimelineVR(const QJsonObject &json)
{
    if ( !IJsonable::typeFromJsonObject(json)
         )
        return;
    ICommonFields::fromJsonObject(json);
    IRequestVR::fromJsonObject(json);
    JSON_TO_LONG_LONG(json, translationId);
    streamId = json.value("streamId").toObject();
    JSON_TO_LONG_LONG(json, start);
    JSON_TO_LONG_LONG(json, end);
}

void RequestGetExistingArchiveTimelineVR::selfCopy(const RequestGetExistingArchiveTimelineVR &obj)
{
    mUidRequest = obj.mUidRequest;
    IRequestVR::selfCopyIRequestVR(obj);
    translationId = obj.translationId;
    streamId = obj.streamId;
    start = obj.start;
    end = obj.end;
}

EDataType RequestGetExistingArchiveTimelineVR::type() const
{
    return EDataType::RequestGetExistingArchiveTimelineVR;
}

QJsonObject RequestGetExistingArchiveTimelineVR::toJsonObject() const
{
    QJsonObject object;
    ICommonFields::toJsonObject(object);
    IJsonable::typeToJsonObject(object);
    IRequestVR::toJsonObject(object);
    LONG_LONG_TO_JSON(translationId, object);
    object.insert("streamId", streamId);
    LONG_LONG_TO_JSON(start, object);
    LONG_LONG_TO_JSON(end, object);
    return object;
}

bool RequestGetExistingArchiveTimelineVR::isValid() const
{
    return true;
}

// RequestGetExistingArchiveTimelinesOfStreamsVR
RequestGetExistingArchiveTimelinesOfStreamsVR &RequestGetExistingArchiveTimelinesOfStreamsVR::operator =(const RequestGetExistingArchiveTimelinesOfStreamsVR &obj)
{
    OPERATOR_EQUAL_BODY;
}

RequestGetExistingArchiveTimelinesOfStreamsVR::RequestGetExistingArchiveTimelinesOfStreamsVR():IJsonable(), ICommonFields(), IRequestVR()
{

}

RequestGetExistingArchiveTimelinesOfStreamsVR::RequestGetExistingArchiveTimelinesOfStreamsVR(const RequestGetExistingArchiveTimelinesOfStreamsVR &obj):IJsonable(), ICommonFields(), IRequestVR()
{
    selfCopy(obj);
}

RequestGetExistingArchiveTimelinesOfStreamsVR::RequestGetExistingArchiveTimelinesOfStreamsVR(const QJsonObject &json)
{
    if ( !IJsonable::typeFromJsonObject(json)
         )
        return;
    ICommonFields::fromJsonObject(json);
    IRequestVR::fromJsonObject(json);
    mParameters = VRGetTimelineRequestParameters(json.value("mParameters").toObject());
}

void RequestGetExistingArchiveTimelinesOfStreamsVR::selfCopy(const RequestGetExistingArchiveTimelinesOfStreamsVR &obj)
{
    mUidRequest = obj.mUidRequest;
    IRequestVR::selfCopyIRequestVR(obj);
    mParameters = obj.mParameters;
}

EDataType RequestGetExistingArchiveTimelinesOfStreamsVR::type() const
{
    return EDataType::RequestGetExistingArchiveTimelinesOfStreamsVR;
}

QJsonObject RequestGetExistingArchiveTimelinesOfStreamsVR::toJsonObject() const
{
    QJsonObject object;
    ICommonFields::toJsonObject(object);
    IJsonable::typeToJsonObject(object);
    IRequestVR::toJsonObject(object);
    object.insert("mParameters", mParameters.toJsonObject());
    return object;
}

bool RequestGetExistingArchiveTimelinesOfStreamsVR::isValid() const
{
    return true;
}

// RequestGetRecordingScheduleVR
RequestGetRecordingScheduleVR &RequestGetRecordingScheduleVR::operator =(const RequestGetRecordingScheduleVR &obj)
{
    OPERATOR_EQUAL_BODY;
}
RequestGetRecordingScheduleVR::RequestGetRecordingScheduleVR():IJsonable(), ICommonFields(), IRequestVR()
{

}

RequestGetRecordingScheduleVR::RequestGetRecordingScheduleVR(const RequestGetRecordingScheduleVR &obj):IJsonable(), ICommonFields(), IRequestVR()
{
    selfCopy(obj);
}

RequestGetRecordingScheduleVR::RequestGetRecordingScheduleVR(const QJsonObject &json)
{
    if ( !IJsonable::typeFromJsonObject(json)
         )
        return;
    ICommonFields::fromJsonObject(json);
    IRequestVR::fromJsonObject(json);
    streamId = json.value("streamId").toObject();
}

void RequestGetRecordingScheduleVR::selfCopy(const RequestGetRecordingScheduleVR &obj)
{
    mUidRequest = obj.mUidRequest;
    IRequestVR::selfCopyIRequestVR(obj);
    streamId = obj.streamId;
}

EDataType RequestGetRecordingScheduleVR::type() const
{
    return EDataType::RequestGetRecordingScheduleVR;
}

QJsonObject RequestGetRecordingScheduleVR::toJsonObject() const
{
    QJsonObject object;
    ICommonFields::toJsonObject(object);
    IJsonable::typeToJsonObject(object);
    IRequestVR::toJsonObject(object);
    object.insert("streamId", streamId);
    return object;
}

bool RequestGetRecordingScheduleVR::isValid() const
{
    return true;
}

// RequestSetRecordingScheduleVR
RequestSetRecordingScheduleVR &RequestSetRecordingScheduleVR::operator =(const RequestSetRecordingScheduleVR &obj)
{
    OPERATOR_EQUAL_BODY;
}
RequestSetRecordingScheduleVR::RequestSetRecordingScheduleVR():IJsonable(), ICommonFields(), IRequestVR()
{

}

RequestSetRecordingScheduleVR::RequestSetRecordingScheduleVR(const RequestSetRecordingScheduleVR &obj):IJsonable(), ICommonFields(), IRequestVR()
{
   selfCopy(obj);
}

RequestSetRecordingScheduleVR::RequestSetRecordingScheduleVR(const QJsonObject &json)
{
    if ( !IJsonable::typeFromJsonObject(json)
         )
        return;
    ICommonFields::fromJsonObject(json);
    IRequestVR::fromJsonObject(json);
    streamId = json.value("streamId").toObject();
    if (json.contains("schedule")) {
        auto json_schedule = json.value("schedule");
        if (json_schedule.isArray()) {
            auto json_scheduleArray = json_schedule.toArray();
            if (!json_scheduleArray.isEmpty()) {
                for (QJsonValue json_schedule_value : json_scheduleArray) {
                    QVector<QDateTime> item_vec;
                    auto json_schedule_value_array = json_schedule_value.toArray();
                    for (QJsonValue date : json_schedule_value_array) {
                        item_vec.append(QDateTime::fromString(date.toString(), Qt::ISODate));
                    }
                    schedule.append(item_vec);
                }
            }
        }
    }
}

void RequestSetRecordingScheduleVR::selfCopy(const RequestSetRecordingScheduleVR &obj)
{
    mUidRequest = obj.mUidRequest;
    IRequestVR::selfCopyIRequestVR(obj);
    streamId = obj.streamId;
    schedule = obj.schedule;
}

EDataType RequestSetRecordingScheduleVR::type() const
{
   return EDataType::RequestSetRecordingScheduleVR;
}

QJsonObject RequestSetRecordingScheduleVR::toJsonObject() const
{
    QJsonObject object;
    ICommonFields::toJsonObject(object);
    IJsonable::typeToJsonObject(object);
    IRequestVR::toJsonObject(object);
    object.insert("streamId", streamId);
    if (!schedule.isEmpty()) {
        QJsonArray json_schedule;
        for (auto& item_vec : schedule) {
            QJsonArray json_item_vec;
            for (auto& date : item_vec) {
                json_item_vec.append(QJsonValue::fromVariant(date.toString(Qt::ISODate)));
            }
            json_schedule.append( json_item_vec );
        }
        object.insert("schedule", json_schedule);
    }
    return object;
}

bool RequestSetRecordingScheduleVR::isValid() const
{
    return true;
}

// RequestStartRecordVR
RequestStartRecordVR &RequestStartRecordVR::operator =(const RequestStartRecordVR &obj)
{
    OPERATOR_EQUAL_BODY;
}
RequestStartRecordVR::RequestStartRecordVR():IJsonable(), ICommonFields(), IRequestVR()
{

}

RequestStartRecordVR::RequestStartRecordVR(const RequestStartRecordVR &obj):IJsonable(), ICommonFields(), IRequestVR()
{
    selfCopy(obj);
}

RequestStartRecordVR::RequestStartRecordVR(const QJsonObject &json)
{
    if ( !IJsonable::typeFromJsonObject(json)
         )
        return;
    ICommonFields::fromJsonObject(json);
    IRequestVR::fromJsonObject(json);
    streamId = json.value("streamId").toObject();
}

void RequestStartRecordVR::selfCopy(const RequestStartRecordVR &obj)
{
    mUidRequest = obj.mUidRequest;
    IRequestVR::selfCopyIRequestVR(obj);
    streamId = obj.streamId;
}

EDataType RequestStartRecordVR::type() const
{
    return EDataType::RequestStartRecordVR;
}

QJsonObject RequestStartRecordVR::toJsonObject() const
{
    QJsonObject object;
    ICommonFields::toJsonObject(object);
    IJsonable::typeToJsonObject(object);
    IRequestVR::toJsonObject(object);
    object.insert("streamId", streamId);
    return object;
}

bool RequestStartRecordVR::isValid() const
{
    return true;
}

// RequestStopRecordVR
RequestStopRecordVR &RequestStopRecordVR::operator =(const RequestStopRecordVR &obj)
{
    OPERATOR_EQUAL_BODY;
}
RequestStopRecordVR::RequestStopRecordVR():IJsonable(), ICommonFields(), IRequestVR()
{

}

RequestStopRecordVR::RequestStopRecordVR(const RequestStopRecordVR &obj):IJsonable(), ICommonFields(), IRequestVR()
{
   selfCopy(obj);
}

RequestStopRecordVR::RequestStopRecordVR(const QJsonObject &json)
{
    if ( !IJsonable::typeFromJsonObject(json)
         )
        return;
    ICommonFields::fromJsonObject(json);
    IRequestVR::fromJsonObject(json);
    streamId = json.value("streamId").toObject();
}

void RequestStopRecordVR::selfCopy(const RequestStopRecordVR &obj)
{
    mUidRequest = obj.mUidRequest;
    IRequestVR::selfCopyIRequestVR(obj);
    streamId = obj.streamId;
}

EDataType RequestStopRecordVR::type() const
{
    return EDataType::RequestStopRecordVR;
}

QJsonObject RequestStopRecordVR::toJsonObject() const
{
    QJsonObject object;
    ICommonFields::toJsonObject(object);
    IJsonable::typeToJsonObject(object);
    IRequestVR::toJsonObject(object);
    object.insert("streamId", streamId);
    return object;
}

bool RequestStopRecordVR::isValid() const
{
    return true;
}

// RequestExportArchiveVR
RequestExportArchiveVR &RequestExportArchiveVR::operator =(const RequestExportArchiveVR &obj)
{
    OPERATOR_EQUAL_BODY;
}
RequestExportArchiveVR::RequestExportArchiveVR():IJsonable(), ICommonFields(), IRequestVR()
{

}

RequestExportArchiveVR::RequestExportArchiveVR(const RequestExportArchiveVR &obj):IJsonable(), ICommonFields(), IRequestVR()
{
    selfCopy(obj);
}

RequestExportArchiveVR::RequestExportArchiveVR(const QJsonObject &json)
{
    if ( !IJsonable::typeFromJsonObject(json)
         )
        return;
    ICommonFields::fromJsonObject(json);
    IRequestVR::fromJsonObject(json);
    streamId = json.value("streamId").toObject();
    JSON_TO_QDATETIME(json, start);
    JSON_TO_QDATETIME(json, end);
}

void RequestExportArchiveVR::selfCopy(const RequestExportArchiveVR &obj)
{
   mUidRequest = obj.mUidRequest;
   IRequestVR::selfCopyIRequestVR(obj);
   streamId = obj.streamId;
   start = obj.start;
   end = obj.end;
}

EDataType RequestExportArchiveVR::type() const
{
    return EDataType::RequestExportArchiveVR;
}

QJsonObject RequestExportArchiveVR::toJsonObject() const
{
    QJsonObject object;
    ICommonFields::toJsonObject(object);
    IJsonable::typeToJsonObject(object);
    IRequestVR::toJsonObject(object);
    object.insert("streamId", streamId);
    QDATETIME_TO_JSON(start, object);
    QDATETIME_TO_JSON(end, object);
    return object;
}

bool RequestExportArchiveVR::isValid() const
{
    return true;
}


// RequestGetChannelsVR
RequestGetChannelsVR &RequestGetChannelsVR::operator =(const RequestGetChannelsVR &obj)
{
    OPERATOR_EQUAL_BODY;
}
RequestGetChannelsVR::RequestGetChannelsVR():IJsonable(), ICommonFields(), IRequestVR()
{

}

RequestGetChannelsVR::RequestGetChannelsVR(const RequestGetChannelsVR &obj):IJsonable(), ICommonFields(), IRequestVR()
{
    selfCopy(obj);
}

RequestGetChannelsVR::RequestGetChannelsVR(const QJsonObject &json)
{
    if ( !IJsonable::typeFromJsonObject(json)
         )
        return;
    ICommonFields::fromJsonObject(json);
    IRequestVR::fromJsonObject(json);
}

void RequestGetChannelsVR::selfCopy(const RequestGetChannelsVR &obj)
{
   mUidRequest = obj.mUidRequest;
   IRequestVR::selfCopyIRequestVR(obj);
}

EDataType RequestGetChannelsVR::type() const
{
    return EDataType::RequestGetChannelsVR;
}

QJsonObject RequestGetChannelsVR::toJsonObject() const
{
    QJsonObject object;
    ICommonFields::toJsonObject(object);
    IJsonable::typeToJsonObject(object);
    IRequestVR::toJsonObject(object);
    return object;
}

bool RequestGetChannelsVR::isValid() const
{
    return true;
}



// RequestDownloadFragmentVR
RequestDownloadFragmentVR &RequestDownloadFragmentVR::operator =(const RequestDownloadFragmentVR &obj)
{
    OPERATOR_EQUAL_BODY;
}
RequestDownloadFragmentVR::RequestDownloadFragmentVR():IJsonable(), ICommonFields(), IRequestVR(),
    streamId(),
    start(-1),
    end(-1)
{

}

RequestDownloadFragmentVR::RequestDownloadFragmentVR(const RequestDownloadFragmentVR &obj):IJsonable(), ICommonFields(), IRequestVR()
{
    selfCopy(obj);
}

RequestDownloadFragmentVR::RequestDownloadFragmentVR(const QJsonObject &json) :
    streamId(),
    start(-1),
    end(-1)
{
    if ( !IJsonable::typeFromJsonObject(json)
         )
        return;
    ICommonFields::fromJsonObject(json);
    IRequestVR::fromJsonObject(json);
    streamId = json.value("streamId").toObject();
    JSON_TO_LONG_LONG(json, start);
    JSON_TO_LONG_LONG(json, end);
}

void RequestDownloadFragmentVR::selfCopy(const RequestDownloadFragmentVR &obj)
{
    mUidRequest = obj.mUidRequest;
    IRequestVR::selfCopyIRequestVR(obj);
    streamId = obj.streamId;
    start = obj.start;
    end = obj.end;
}

EDataType RequestDownloadFragmentVR::type() const
{
    return EDataType::RequestDownloadFragmentVR;
}

QJsonObject RequestDownloadFragmentVR::toJsonObject() const
{
    QJsonObject object;
    ICommonFields::toJsonObject(object);
    IJsonable::typeToJsonObject(object);
    IRequestVR::toJsonObject(object);
    object.insert("streamId", streamId);
    LONG_LONG_TO_JSON(start, object);
    LONG_LONG_TO_JSON(end, object);
    return object;
}

bool RequestDownloadFragmentVR::isValid() const
{
    return true;
}


// ------------------------------------------------
// ----- RequestDeleteTmpVideoFilesVR
// ------------------------------------------------

RequestDeleteTmpVideoFilesVR::RequestDeleteTmpVideoFilesVR():IJsonable(), ICommonFields()
{

}

RequestDeleteTmpVideoFilesVR::RequestDeleteTmpVideoFilesVR(const RequestDeleteTmpVideoFilesVR &obj):IJsonable(), ICommonFields()
{
    selfCopy(obj);
}

RequestDeleteTmpVideoFilesVR &RequestDeleteTmpVideoFilesVR::operator =(const RequestDeleteTmpVideoFilesVR &obj)
{
    OPERATOR_EQUAL_BODY;
}

RequestDeleteTmpVideoFilesVR::RequestDeleteTmpVideoFilesVR(const QJsonObject &json)
{
    if ( !IJsonable::typeFromJsonObject(json) )
        return;
    ICommonFields::fromJsonObject(json);
}

void RequestDeleteTmpVideoFilesVR::selfCopy(const RequestDeleteTmpVideoFilesVR &obj)
{
    mUidRequest = obj.mUidRequest;
}

EDataType RequestDeleteTmpVideoFilesVR::type() const
{
    return EDataType::RequestDeleteTmpVideoFilesVR;
}

QJsonObject RequestDeleteTmpVideoFilesVR::toJsonObject() const
{
    QJsonObject object;
    ICommonFields::toJsonObject(object);
    IJsonable::typeToJsonObject(object);
    return object;
}

bool RequestDeleteTmpVideoFilesVR::isValid() const
{
    return true;
}


// RequestStopDownloadFragmentVR
RequestStopDownloadFragmentVR &RequestStopDownloadFragmentVR::operator =(const RequestStopDownloadFragmentVR &obj)
{
    OPERATOR_EQUAL_BODY;
}
RequestStopDownloadFragmentVR::RequestStopDownloadFragmentVR():IJsonable(), ICommonFields(), IRequestVR(),
    streamId()
{

}

RequestStopDownloadFragmentVR::RequestStopDownloadFragmentVR(const RequestStopDownloadFragmentVR &obj):IJsonable(), ICommonFields(), IRequestVR()
{
    selfCopy(obj);
}

RequestStopDownloadFragmentVR::RequestStopDownloadFragmentVR(const QJsonObject &json) :
    streamId()
{
    if ( !IJsonable::typeFromJsonObject(json)
         )
        return;
    ICommonFields::fromJsonObject(json);
    IRequestVR::fromJsonObject(json);
    streamId = json.value("streamId").toObject();
}

void RequestStopDownloadFragmentVR::selfCopy(const RequestStopDownloadFragmentVR &obj)
{
    mUidRequest = obj.mUidRequest;
    IRequestVR::selfCopyIRequestVR(obj);
    streamId = obj.streamId;
}

EDataType RequestStopDownloadFragmentVR::type() const
{
    return EDataType::RequestStopDownloadFragmentVR;
}

QJsonObject RequestStopDownloadFragmentVR::toJsonObject() const
{
    QJsonObject object;
    ICommonFields::toJsonObject(object);
    IJsonable::typeToJsonObject(object);
    IRequestVR::toJsonObject(object);
    object.insert("streamId", streamId);
    return object;
}

bool RequestStopDownloadFragmentVR::isValid() const
{
    return true;
}


/// \remark ответы

// ResponseCreateRtspStreamVideoVR
ResponseCreateRtspStreamVideoVR &ResponseCreateRtspStreamVideoVR::operator =(const ResponseCreateRtspStreamVideoVR &obj)
{
    OPERATOR_EQUAL_BODY;
}
ResponseCreateRtspStreamVideoVR::ResponseCreateRtspStreamVideoVR():IJsonable(), ICommonFields(), IResponseResultable()
{
    
}

ResponseCreateRtspStreamVideoVR::ResponseCreateRtspStreamVideoVR(const ResponseCreateRtspStreamVideoVR &obj):IJsonable(), ICommonFields(), IResponseResultable()
{
    selfCopy(obj);
}

ResponseCreateRtspStreamVideoVR::ResponseCreateRtspStreamVideoVR(const QJsonObject &json)
{
    if ( !IJsonable::typeFromJsonObject(json) ||
         !IResponseResultable::resultResponseFromJsonObject(json)
            )
        return;
    ICommonFields::fromJsonObject(json);
    streamId = json.value("streamId").toObject();
    JSON_TO_QSTRING(json, transToken);
    JSON_TO_QSTRING(json, url);

    auto hexed = json.value("mPreviewFrame").toVariant().toByteArray();
    mPreviewFrame = QByteArray::fromHex(hexed);
}

void ResponseCreateRtspStreamVideoVR::selfCopy(const ResponseCreateRtspStreamVideoVR &obj)
{
    mUidRequest = obj.mUidRequest;
    mResponseResult = obj.mResponseResult;
    streamId = obj.streamId;
    transToken = obj.transToken;
    url = obj.url;
    mPreviewFrame = obj.mPreviewFrame;
}

EDataType ResponseCreateRtspStreamVideoVR::type() const
{
    return EDataType::ResponseCreateRtspStreamVideoVR;
}

QJsonObject ResponseCreateRtspStreamVideoVR::toJsonObject() const
{
    QJsonObject object;
    ICommonFields::toJsonObject(object);
    IJsonable::typeToJsonObject(object);
    IResponseResultable::resultResponseToJsonObject(object);
    object.insert("streamId", streamId);
    QSTRING_TO_JSON(transToken, object);
    QSTRING_TO_JSON(url, object);
    auto hexed = mPreviewFrame.toHex();
    object.insert("mPreviewFrame", QJsonValue::fromVariant(hexed));
    return object;
}

bool ResponseCreateRtspStreamVideoVR::isValid() const
{
    return true;
}

// ResponseStartRtspStreamVideoVR
ResponseStartRtspStreamVideoVR &ResponseStartRtspStreamVideoVR::operator =(const ResponseStartRtspStreamVideoVR &obj)
{
    OPERATOR_EQUAL_BODY;
}
ResponseStartRtspStreamVideoVR::ResponseStartRtspStreamVideoVR():IJsonable(), ICommonFields(), IResponseResultable()
{

}

ResponseStartRtspStreamVideoVR::ResponseStartRtspStreamVideoVR(const ResponseStartRtspStreamVideoVR &obj):IJsonable(), ICommonFields(), IResponseResultable()
{
    selfCopy(obj);
}

ResponseStartRtspStreamVideoVR::ResponseStartRtspStreamVideoVR(const QJsonObject &json)
{
    if ( !IJsonable::typeFromJsonObject(json) ||
         !IResponseResultable::resultResponseFromJsonObject(json)
            )
        return;
    ICommonFields::fromJsonObject(json);
    JSON_TO_QSTRING(json, transToken);
    JSON_TO_QSTRING(json, url);
}

void ResponseStartRtspStreamVideoVR::selfCopy(const ResponseStartRtspStreamVideoVR &obj)
{
    mUidRequest = obj.mUidRequest;
    mResponseResult = obj.mResponseResult;
    transToken = obj.transToken;
    url = obj.url;
}

EDataType ResponseStartRtspStreamVideoVR::type() const
{
    return EDataType::ResponseStartRtspStreamVideoVR;
}

QJsonObject ResponseStartRtspStreamVideoVR::toJsonObject() const
{
    QJsonObject object;
    ICommonFields::toJsonObject(object);
    IJsonable::typeToJsonObject(object);
    IResponseResultable::resultResponseToJsonObject(object);
    QSTRING_TO_JSON(transToken, object);
    QSTRING_TO_JSON(url, object);
    return object;
}

bool ResponseStartRtspStreamVideoVR::isValid() const
{
    return true;
}

// ResponseStopRtspStreamVideoVR
ResponseStopRtspStreamVideoVR &ResponseStopRtspStreamVideoVR::operator =(const ResponseStopRtspStreamVideoVR &obj)
{
    OPERATOR_EQUAL_BODY;
}
ResponseStopRtspStreamVideoVR::ResponseStopRtspStreamVideoVR():IJsonable(), ICommonFields(), IResponseResultable()
{

}

ResponseStopRtspStreamVideoVR::ResponseStopRtspStreamVideoVR(const ResponseStopRtspStreamVideoVR &obj):IJsonable(), ICommonFields(), IResponseResultable()
{
    selfCopy(obj);
}

ResponseStopRtspStreamVideoVR::ResponseStopRtspStreamVideoVR(const QJsonObject &json)
{
    if ( !IJsonable::typeFromJsonObject(json) ||
         !IResponseResultable::resultResponseFromJsonObject(json)
            )
        return;
    ICommonFields::fromJsonObject(json);
    JSON_TO_QSTRING(json, transToken);
    JSON_TO_BOOL(json, result);
}

void ResponseStopRtspStreamVideoVR::selfCopy(const ResponseStopRtspStreamVideoVR &obj)
{
    mUidRequest = obj.mUidRequest;
    mResponseResult = obj.mResponseResult;
    transToken = obj.transToken;
    result = obj.result;
}

EDataType ResponseStopRtspStreamVideoVR::type() const
{
    return EDataType::ResponseStopRtspStreamVideoVR;
}

QJsonObject ResponseStopRtspStreamVideoVR::toJsonObject() const
{
    QJsonObject object;
    ICommonFields::toJsonObject(object);
    IJsonable::typeToJsonObject(object);
    IResponseResultable::resultResponseToJsonObject(object);
    QSTRING_TO_JSON(transToken, object);
    BOOL_TO_JSON(result, object);
    return object;
}

bool ResponseStopRtspStreamVideoVR::isValid() const
{
    return true;
}

// ResponseStartRtspStreamCameraVR
ResponseStartRtspStreamCameraVR &ResponseStartRtspStreamCameraVR::operator =(const ResponseStartRtspStreamCameraVR &obj)
{
    OPERATOR_EQUAL_BODY;
}
ResponseStartRtspStreamCameraVR::ResponseStartRtspStreamCameraVR():IJsonable(), ICommonFields(), IResponseResultable()
{

}

ResponseStartRtspStreamCameraVR::ResponseStartRtspStreamCameraVR(const ResponseStartRtspStreamCameraVR &obj):IJsonable(), ICommonFields(), IResponseResultable()
{
    selfCopy(obj);
}

ResponseStartRtspStreamCameraVR::ResponseStartRtspStreamCameraVR(const QJsonObject &json)
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

void ResponseStartRtspStreamCameraVR::selfCopy(const ResponseStartRtspStreamCameraVR &obj)
{
    mUidRequest = obj.mUidRequest;
    mResponseResult = obj.mResponseResult;
    mUidRequest = obj.mUidRequest;
    mRtspUrl = obj.mRtspUrl;
}

EDataType ResponseStartRtspStreamCameraVR::type() const
{
    return EDataType::ResponseStartRtspStreamCameraVR;
}

QJsonObject ResponseStartRtspStreamCameraVR::toJsonObject() const
{
    QJsonObject object;
    ICommonFields::toJsonObject(object);
    IJsonable::typeToJsonObject(object);
    IResponseResultable::resultResponseToJsonObject(object);
    QSTRING_TO_JSON(mRtspUrl, object);
    return object;
}

bool ResponseStartRtspStreamCameraVR::isValid() const
{
    return true;
}

// ResponseStopRtspStreamCameraVR
ResponseStopRtspStreamCameraVR &ResponseStopRtspStreamCameraVR::operator =(const ResponseStopRtspStreamCameraVR &obj)
{
    OPERATOR_EQUAL_BODY;
}
ResponseStopRtspStreamCameraVR::ResponseStopRtspStreamCameraVR():IJsonable(), ICommonFields(), IResponseResultable()
{

}

ResponseStopRtspStreamCameraVR::ResponseStopRtspStreamCameraVR(const ResponseStopRtspStreamCameraVR &obj):IJsonable(), ICommonFields(), IResponseResultable()
{
    selfCopy(obj);
}

ResponseStopRtspStreamCameraVR::ResponseStopRtspStreamCameraVR(const QJsonObject &json)
{
    if ( !IJsonable::typeFromJsonObject(json) ||
         !IResponseResultable::resultResponseFromJsonObject(json)
            )
        return;
    ICommonFields::fromJsonObject(json);
}

void ResponseStopRtspStreamCameraVR::selfCopy(const ResponseStopRtspStreamCameraVR &obj)
{
    mUidRequest = obj.mUidRequest;
    mResponseResult = obj.mResponseResult;
}

EDataType ResponseStopRtspStreamCameraVR::type() const
{
    return EDataType::ResponseStopRtspStreamCameraVR;
}

QJsonObject ResponseStopRtspStreamCameraVR::toJsonObject() const
{
    QJsonObject object;
    ICommonFields::toJsonObject(object);
    IJsonable::typeToJsonObject(object);
    IResponseResultable::resultResponseToJsonObject(object);
    return object;
}

bool ResponseStopRtspStreamCameraVR::isValid() const
{
    return true;
}

// ResponseGetExistingArchiveTimelineVR
ResponseGetExistingArchiveTimelineVR &ResponseGetExistingArchiveTimelineVR::operator =(const ResponseGetExistingArchiveTimelineVR &obj)
{
    OPERATOR_EQUAL_BODY;
}
ResponseGetExistingArchiveTimelineVR::ResponseGetExistingArchiveTimelineVR():IJsonable(), ICommonFields(), IResponseResultable()
{

}

ResponseGetExistingArchiveTimelineVR::ResponseGetExistingArchiveTimelineVR(const ResponseGetExistingArchiveTimelineVR &obj):IJsonable(), ICommonFields(), IResponseResultable()
{
    selfCopy(obj);
}

ResponseGetExistingArchiveTimelineVR::ResponseGetExistingArchiveTimelineVR(const QJsonObject &json)
{
    if ( !IJsonable::typeFromJsonObject(json) ||
         !IResponseResultable::resultResponseFromJsonObject(json)
            )
        return;
    ICommonFields::fromJsonObject(json);
    translationId = json.value("translationId").toVariant().toLongLong();
    streamId = json.value("streamId").toObject();
    if (json.contains("timeline")) {
        auto json_timeline = json.value("timeline");
        if (json_timeline.isArray()) {
            auto json_timelineArray = json_timeline.toArray();
            if (!json_timelineArray.isEmpty()) {
                for (QJsonValue json_timeline_value : json_timelineArray) {
                    QPair<qint64, qint64> item_pair;
                    auto obj_pair = json_timeline_value.toObject();
                    item_pair.first = obj_pair.value("first").toVariant().toLongLong();
                    item_pair.second = obj_pair.value("second").toVariant().toLongLong();
                    timeline.append(item_pair);
                }
            }
        }
    }
}

void ResponseGetExistingArchiveTimelineVR::selfCopy(const ResponseGetExistingArchiveTimelineVR &obj)
{
    mUidRequest = obj.mUidRequest;
    mResponseResult = obj.mResponseResult;
    translationId = obj.translationId;
    streamId = obj.streamId;
    timeline = obj.timeline;
}

EDataType ResponseGetExistingArchiveTimelineVR::type() const
{
    return EDataType::ResponseGetExistingArchiveTimelineVR;
}

QJsonObject ResponseGetExistingArchiveTimelineVR::toJsonObject() const
{
    QJsonObject object;
    ICommonFields::toJsonObject(object);
    IJsonable::typeToJsonObject(object);
    IResponseResultable::resultResponseToJsonObject(object);
    object.insert("translationId", QJsonValue::fromVariant(translationId));
    object.insert("streamId", streamId);
    if (!timeline.isEmpty()) {
        QJsonArray json_schedule;
        for (const QPair<qint64, qint64> &item_pair : timeline) {
            QJsonObject item_pair_json;
            item_pair_json.insert("first", QJsonValue::fromVariant(item_pair.first));
            item_pair_json.insert("second", QJsonValue::fromVariant(item_pair.second));
            json_schedule.append( item_pair_json );
        }
        object.insert("timeline", json_schedule);
    }
    return object;
}

bool ResponseGetExistingArchiveTimelineVR::isValid() const
{
    return true;
}


// ResponseGetExistingArchiveTimelinesOfStreamsVR
ResponseGetExistingArchiveTimelinesOfStreamsVR &ResponseGetExistingArchiveTimelinesOfStreamsVR::operator =(const ResponseGetExistingArchiveTimelinesOfStreamsVR &obj)
{
    OPERATOR_EQUAL_BODY;
}
ResponseGetExistingArchiveTimelinesOfStreamsVR::ResponseGetExistingArchiveTimelinesOfStreamsVR():IJsonable(), ICommonFields(), IResponseResultable()
{

}

ResponseGetExistingArchiveTimelinesOfStreamsVR::ResponseGetExistingArchiveTimelinesOfStreamsVR(const ResponseGetExistingArchiveTimelinesOfStreamsVR &obj):IJsonable(), ICommonFields(), IResponseResultable()
{
    selfCopy(obj);
}

ResponseGetExistingArchiveTimelinesOfStreamsVR::ResponseGetExistingArchiveTimelinesOfStreamsVR(const QJsonObject &json)
{
    if ( !IJsonable::typeFromJsonObject(json) ||
         !IResponseResultable::resultResponseFromJsonObject(json)
            )
        return;
    ICommonFields::fromJsonObject(json);
    mParameters = VRGetTimelineRequestParameters(json.value("mParameters").toObject());

    QJsonArray timelinesArray = json.value("timelines").toArray();
    for (auto i = 0; i < timelinesArray.count(); ++i)
    {
        auto timelineObj = timelinesArray[i].toObject();
        QUuid streamUuid = QUuid(timelineObj.value("streamUuid").toString());
        if (streamUuid.isNull())
            continue;

        QVector<QPair<qint64, qint64>> timeline;
        if (timelineObj.contains("timeline")) {
            auto json_timeline = timelineObj.value("timeline");
            if (json_timeline.isArray()) {
                auto json_timelineArray = json_timeline.toArray();
                if (!json_timelineArray.isEmpty()) {
                    for (QJsonValue json_timeline_value : json_timelineArray) {
                        QPair<qint64, qint64> item_pair;
                        auto obj_pair = json_timeline_value.toObject();
                        item_pair.first = obj_pair.value("first").toVariant().toLongLong();
                        item_pair.second = obj_pair.value("second").toVariant().toLongLong();
                        timeline.append(item_pair);
                    }
                }
            }
        }
        if (timeline.isEmpty())
            continue;
        mTimelineByStreamsMap.insert(streamUuid, timeline);
    }
}

void ResponseGetExistingArchiveTimelinesOfStreamsVR::selfCopy(const ResponseGetExistingArchiveTimelinesOfStreamsVR &obj)
{
    mUidRequest = obj.mUidRequest;
    mResponseResult = obj.mResponseResult;
    mParameters = obj.mParameters;
    mTimelineByStreamsMap = obj.mTimelineByStreamsMap;
}

EDataType ResponseGetExistingArchiveTimelinesOfStreamsVR::type() const
{
    return EDataType::ResponseGetExistingArchiveTimelinesOfStreamsVR;
}

QJsonObject ResponseGetExistingArchiveTimelinesOfStreamsVR::toJsonObject() const
{
    QJsonObject object;
    ICommonFields::toJsonObject(object);
    IJsonable::typeToJsonObject(object);
    IResponseResultable::resultResponseToJsonObject(object);
    object.insert("mParameters", mParameters.toJsonObject());
    QJsonArray timelinesArray;
    auto mapIt = mTimelineByStreamsMap.constBegin();
    for (; mapIt != mTimelineByStreamsMap.constEnd(); ++mapIt)
    {
        QJsonObject timelineObj;
        timelineObj.insert("streamUuid", QJsonValue::fromVariant(mapIt.key()));
        QVector<QPair<qint64, qint64>> timeline = mapIt.value();
        if (!timeline.isEmpty()) {
            QJsonArray json_schedule;
            for (const QPair<qint64, qint64> &item_pair : timeline) {
                QJsonObject item_pair_json;
                item_pair_json.insert("first", QJsonValue::fromVariant(item_pair.first));
                item_pair_json.insert("second", QJsonValue::fromVariant(item_pair.second));
                json_schedule.append( item_pair_json );
            }
            timelineObj.insert("timeline", json_schedule);
        }
        timelinesArray.append(timelineObj);
    }
    object.insert("timelines", timelinesArray);
    return object;
}

bool ResponseGetExistingArchiveTimelinesOfStreamsVR::isValid() const
{
    return true;
}

// ResponsetGetRecordingScheduleVR
ResponseGetRecordingScheduleVR &ResponseGetRecordingScheduleVR::operator =(const ResponseGetRecordingScheduleVR &obj)
{
    OPERATOR_EQUAL_BODY;
}
ResponseGetRecordingScheduleVR::ResponseGetRecordingScheduleVR():IJsonable(), ICommonFields(), IResponseResultable()
{

}

ResponseGetRecordingScheduleVR::ResponseGetRecordingScheduleVR(const ResponseGetRecordingScheduleVR &obj):IJsonable(), ICommonFields(), IResponseResultable()
{
    selfCopy(obj);
}

ResponseGetRecordingScheduleVR::ResponseGetRecordingScheduleVR(const QJsonObject &json)
{
    if ( !IJsonable::typeFromJsonObject(json) ||
         !IResponseResultable::resultResponseFromJsonObject(json)
            )
        return;
    ICommonFields::fromJsonObject(json);
    streamId = json.value("streamId").toObject();
    if (json.contains("schedule")) {
        auto json_schedule = json.value("schedule");
        if (json_schedule.isArray()) {
            auto json_scheduleArray = json_schedule.toArray();
            if (!json_scheduleArray.isEmpty()) {
                for (QJsonValue json_schedule_value : json_scheduleArray) {
                    QVector<QDateTime> item_vec;
                    auto json_schedule_value_array = json_schedule_value.toArray();
                    for (QJsonValue date : json_schedule_value_array) {
                        item_vec.append(QDateTime::fromString(date.toString(), Qt::ISODate));
                    }
                    schedule.append(item_vec);
                }
            }
        }
    }
}

void ResponseGetRecordingScheduleVR::selfCopy(const ResponseGetRecordingScheduleVR &obj)
{
    mUidRequest = obj.mUidRequest;
    mResponseResult = obj.mResponseResult;
    streamId = obj.streamId;
    schedule = obj.schedule;
}

EDataType ResponseGetRecordingScheduleVR::type() const
{
    return EDataType::ResponseGetRecordingScheduleVR;
}

QJsonObject ResponseGetRecordingScheduleVR::toJsonObject() const
{
    QJsonObject object;
    ICommonFields::toJsonObject(object);
    IJsonable::typeToJsonObject(object);
    IResponseResultable::resultResponseToJsonObject(object);
    object.insert("streamId", streamId);
    if (!schedule.isEmpty()) {
        QJsonArray json_schedule;
        for (auto& item_vec : schedule) {
            QJsonArray json_item_vec;
            for (auto& date : item_vec) {
                json_item_vec.append(QJsonValue::fromVariant(date.toString(Qt::ISODate)));
            }
            json_schedule.append( json_item_vec );
        }
        object.insert("schedule", json_schedule);
    }
    return object;
}

bool ResponseGetRecordingScheduleVR::isValid() const
{
    return true;
}

// ResponseSetRecordingScheduleVR
ResponseSetRecordingScheduleVR &ResponseSetRecordingScheduleVR::operator =(const ResponseSetRecordingScheduleVR &obj)
{
    OPERATOR_EQUAL_BODY;
}
ResponseSetRecordingScheduleVR::ResponseSetRecordingScheduleVR():IJsonable(), ICommonFields(), IResponseResultable()
{

}

ResponseSetRecordingScheduleVR::ResponseSetRecordingScheduleVR(const ResponseSetRecordingScheduleVR &obj):IJsonable(), ICommonFields(), IResponseResultable()
{
    selfCopy(obj);
}

ResponseSetRecordingScheduleVR::ResponseSetRecordingScheduleVR(const QJsonObject &json)
{
    if ( !IJsonable::typeFromJsonObject(json) ||
         !IResponseResultable::resultResponseFromJsonObject(json)
            )
        return;
    ICommonFields::fromJsonObject(json);
    streamId = json.value("streamId").toObject();
}

void ResponseSetRecordingScheduleVR::selfCopy(const ResponseSetRecordingScheduleVR &obj)
{
    mUidRequest = obj.mUidRequest;
    mResponseResult = obj.mResponseResult;
    streamId = obj.streamId;
}

EDataType ResponseSetRecordingScheduleVR::type() const
{
    return EDataType::ResponseSetRecordingScheduleVR;
}

QJsonObject ResponseSetRecordingScheduleVR::toJsonObject() const
{
    QJsonObject object;
    ICommonFields::toJsonObject(object);
    IJsonable::typeToJsonObject(object);
    IResponseResultable::resultResponseToJsonObject(object);
    object.insert("streamId", streamId);
    return object;
}

bool ResponseSetRecordingScheduleVR::isValid() const
{
    return true;
}

// ResponseStartRecordVR
ResponseStartRecordVR &ResponseStartRecordVR::operator =(const ResponseStartRecordVR &obj)
{
    OPERATOR_EQUAL_BODY;
}
ResponseStartRecordVR::ResponseStartRecordVR():IJsonable(), ICommonFields(), IResponseResultable()
{

}

ResponseStartRecordVR::ResponseStartRecordVR(const ResponseStartRecordVR &obj):IJsonable(), ICommonFields(), IResponseResultable()
{
    selfCopy(obj);
}

ResponseStartRecordVR::ResponseStartRecordVR(const QJsonObject &json)
{
    if ( !IJsonable::typeFromJsonObject(json) ||
         !IResponseResultable::resultResponseFromJsonObject(json)
            )
        return;
    ICommonFields::fromJsonObject(json);
    streamId = json.value("streamId").toObject();
    JSON_TO_BOOL(json, result);
}

void ResponseStartRecordVR::selfCopy(const ResponseStartRecordVR &obj)
{
    mUidRequest = obj.mUidRequest;
    mResponseResult = obj.mResponseResult;
    streamId = obj.streamId;
    result = obj.result;
}

EDataType ResponseStartRecordVR::type() const
{
    return EDataType::ResponseStartRecordVR;
}

QJsonObject ResponseStartRecordVR::toJsonObject() const
{
    QJsonObject object;
    ICommonFields::toJsonObject(object);
    IJsonable::typeToJsonObject(object);
    IResponseResultable::resultResponseToJsonObject(object);
    object.insert("streamId", streamId);
    BOOL_TO_JSON(result, object);
    return object;
}

bool ResponseStartRecordVR::isValid() const
{
    return true;
}

// ResponseStopRecordVR
ResponseStopRecordVR &ResponseStopRecordVR::operator =(const ResponseStopRecordVR &obj)
{
    OPERATOR_EQUAL_BODY;
}
ResponseStopRecordVR::ResponseStopRecordVR():IJsonable(), ICommonFields(), IResponseResultable()
{

}

ResponseStopRecordVR::ResponseStopRecordVR(const ResponseStopRecordVR &obj):IJsonable(), ICommonFields(), IResponseResultable()
{
    selfCopy(obj);
}

ResponseStopRecordVR::ResponseStopRecordVR(const QJsonObject &json)
{
    if ( !IJsonable::typeFromJsonObject(json) ||
         !IResponseResultable::resultResponseFromJsonObject(json)
            )
        return;
    ICommonFields::fromJsonObject(json);
    streamId = json.value("streamId").toObject();
    JSON_TO_BOOL(json, result);
}

void ResponseStopRecordVR::selfCopy(const ResponseStopRecordVR &obj)
{
    mUidRequest = obj.mUidRequest;
    mResponseResult = obj.mResponseResult;
    streamId = obj.streamId;
    result = obj.result;
}

EDataType ResponseStopRecordVR::type() const
{
    return EDataType::ResponseStopRecordVR;
}

QJsonObject ResponseStopRecordVR::toJsonObject() const
{
    QJsonObject object;
    ICommonFields::toJsonObject(object);
    IJsonable::typeToJsonObject(object);
    IResponseResultable::resultResponseToJsonObject(object);
    object.insert("streamId", streamId);
    BOOL_TO_JSON(result, object);
    return object;
}

bool ResponseStopRecordVR::isValid() const
{
    return true;
}

// ResponseExportArchiveVR
ResponseExportArchiveVR &ResponseExportArchiveVR::operator =(const ResponseExportArchiveVR &obj)
{
    OPERATOR_EQUAL_BODY;
}
ResponseExportArchiveVR::ResponseExportArchiveVR():IJsonable(), ICommonFields(), IResponseResultable()
{

}

ResponseExportArchiveVR::ResponseExportArchiveVR(const ResponseExportArchiveVR &obj):IJsonable(), ICommonFields(), IResponseResultable()
{
    selfCopy(obj);
}

ResponseExportArchiveVR::ResponseExportArchiveVR(const QJsonObject &json)
{
    if ( !IJsonable::typeFromJsonObject(json) ||
         !IResponseResultable::resultResponseFromJsonObject(json)
            )
        return;
    ICommonFields::fromJsonObject(json);
    streamId = json.value("streamId").toObject();
    JSON_TO_QSTRING(json, url);
}

void ResponseExportArchiveVR::selfCopy(const ResponseExportArchiveVR &obj)
{
    mUidRequest = obj.mUidRequest;
    mResponseResult = obj.mResponseResult;
    streamId = obj.streamId;
    url = obj.url;
}

EDataType ResponseExportArchiveVR::type() const
{
   return EDataType::ResponseExportArchiveVR;
}

QJsonObject ResponseExportArchiveVR::toJsonObject() const
{
    QJsonObject object;
    ICommonFields::toJsonObject(object);
    IJsonable::typeToJsonObject(object);
    IResponseResultable::resultResponseToJsonObject(object);
    object.insert("streamId", streamId);
    QSTRING_TO_JSON(url, object);
    return object;
}

bool ResponseExportArchiveVR::isValid() const
{
    return true;
}


// ResponseGetChannelsVR
ResponseGetChannelsVR &ResponseGetChannelsVR::operator =(const ResponseGetChannelsVR &obj)
{
    OPERATOR_EQUAL_BODY;
}
ResponseGetChannelsVR::ResponseGetChannelsVR():IJsonable(), ICommonFields(), IResponseResultable()
{

}

ResponseGetChannelsVR::ResponseGetChannelsVR(const ResponseGetChannelsVR &obj):IJsonable(), ICommonFields(), IResponseResultable()
{
    selfCopy(obj);
}

ResponseGetChannelsVR::ResponseGetChannelsVR(const QJsonObject &json)
{
    if ( !IJsonable::typeFromJsonObject(json) ||
         !IResponseResultable::resultResponseFromJsonObject(json)
            )
        return;
    ICommonFields::fromJsonObject(json);
    if ( !json.contains("mChannelsJson")
         )
        return;
    JSON_TO_QSTRING(json, mChannelsJson);
}

void ResponseGetChannelsVR::selfCopy(const ResponseGetChannelsVR &obj)
{
    mUidRequest = obj.mUidRequest;
    mResponseResult = obj.mResponseResult;
    mChannelsJson = obj.mChannelsJson;
}

EDataType ResponseGetChannelsVR::type() const
{
    return EDataType::ResponseGetChannelsVR;
}

QJsonObject ResponseGetChannelsVR::toJsonObject() const
{
    QJsonObject object;
    ICommonFields::toJsonObject(object);
    IJsonable::typeToJsonObject(object);
    IResponseResultable::resultResponseToJsonObject(object);
    QSTRING_TO_JSON(mChannelsJson, object);
    return object;
}

bool ResponseGetChannelsVR::isValid() const
{
    return true;
}




// ResponseDownloadFragmentStartedVR
ResponseDownloadFragmentStartedVR::ResponseDownloadFragmentStartedVR(const QJsonObject &json)
{
    if ( !IJsonable::typeFromJsonObject(json) ||
         !IResponseResultable::resultResponseFromJsonObject(json)
            )
        return;
    ICommonFields::fromJsonObject(json);
    streamId = json.value("streamId").toObject();
    JSON_TO_QSTRING(json, mTmpVideoFilePath);
    JSON_TO_QSTRING(json, mErrorString);
}

void ResponseDownloadFragmentStartedVR::selfCopy(const ResponseDownloadFragmentStartedVR &obj)
{
    mUidRequest = obj.mUidRequest;
    mResponseResult = obj.mResponseResult;
    streamId = obj.streamId;
    mTmpVideoFilePath = obj.mTmpVideoFilePath;
    mErrorString = obj.mErrorString;
}

QJsonObject ResponseDownloadFragmentStartedVR::toJsonObject() const
{
    QJsonObject object;
    ICommonFields::toJsonObject(object);
    IJsonable::typeToJsonObject(object);
    IResponseResultable::resultResponseToJsonObject(object);
    object.insert("streamId", streamId);
    QSTRING_TO_JSON(mTmpVideoFilePath, object);
    QSTRING_TO_JSON(mErrorString, object);
    return object;
}



// ResponseDownloadFragmentProgressVR
ResponseDownloadFragmentProgressVR::ResponseDownloadFragmentProgressVR(const QJsonObject &json)
{
    if ( !IJsonable::typeFromJsonObject(json) ||
         !IResponseResultable::resultResponseFromJsonObject(json)
            )
        return;
    ICommonFields::fromJsonObject(json);
    streamId = json.value("streamId").toObject();
    JSON_TO_QSTRING(json, mTmpVideoFilePath);
    JSON_TO_QSTRING(json, mErrorString);
    mProgress = json.value("mProgress").toString().toUShort();
}

void ResponseDownloadFragmentProgressVR::selfCopy(const ResponseDownloadFragmentProgressVR &obj)
{
    mUidRequest = obj.mUidRequest;
    mResponseResult = obj.mResponseResult;
    streamId = obj.streamId;
    mTmpVideoFilePath = obj.mTmpVideoFilePath;
    mErrorString = obj.mErrorString;
    mProgress = obj.mProgress;
}

QJsonObject ResponseDownloadFragmentProgressVR::toJsonObject() const
{
    QJsonObject object;
    ICommonFields::toJsonObject(object);
    IJsonable::typeToJsonObject(object);
    IResponseResultable::resultResponseToJsonObject(object);
    object.insert("streamId", streamId);
    QSTRING_TO_JSON(mTmpVideoFilePath, object);
    QSTRING_TO_JSON(mErrorString, object);
    object.insert("mProgress", QJsonValue::fromVariant(QString::number(mProgress)));
    return object;
}

// ResponseDownloadFragmentFinishedVR
ResponseDownloadFragmentFinishedVR::ResponseDownloadFragmentFinishedVR(const QJsonObject &json)
{
    if ( !IJsonable::typeFromJsonObject(json) ||
         !IResponseResultable::resultResponseFromJsonObject(json)
            )
        return;
    ICommonFields::fromJsonObject(json);
    streamId = json.value("streamId").toObject();
    JSON_TO_QSTRING(json, mTmpVideoFilePath);
    JSON_TO_QSTRING(json, mErrorString);
}

void ResponseDownloadFragmentFinishedVR::selfCopy(const ResponseDownloadFragmentFinishedVR &obj)
{
    mUidRequest = obj.mUidRequest;
    mResponseResult = obj.mResponseResult;
    streamId = obj.streamId;
    mTmpVideoFilePath = obj.mTmpVideoFilePath;
    mErrorString = obj.mErrorString;
}

QJsonObject ResponseDownloadFragmentFinishedVR::toJsonObject() const
{
    QJsonObject object;
    ICommonFields::toJsonObject(object);
    IJsonable::typeToJsonObject(object);
    IResponseResultable::resultResponseToJsonObject(object);
    object.insert("streamId", streamId);
    QSTRING_TO_JSON(mTmpVideoFilePath, object);
    QSTRING_TO_JSON(mErrorString, object);
    return object;
}

// ResponseDownloadFragmentErrorVR
ResponseDownloadFragmentErrorVR::ResponseDownloadFragmentErrorVR(const QJsonObject &json)
{
    if ( !IJsonable::typeFromJsonObject(json) ||
         !IResponseResultable::resultResponseFromJsonObject(json)
            )
        return;
    ICommonFields::fromJsonObject(json);
    streamId = json.value("streamId").toObject();
    JSON_TO_QSTRING(json, mTmpVideoFilePath);
    JSON_TO_QSTRING(json, mErrorString);
}

void ResponseDownloadFragmentErrorVR::selfCopy(const ResponseDownloadFragmentErrorVR &obj)
{
    mUidRequest = obj.mUidRequest;
    mResponseResult = obj.mResponseResult;
    streamId = obj.streamId;
    mTmpVideoFilePath = obj.mTmpVideoFilePath;
    mErrorString = obj.mErrorString;
}

QJsonObject ResponseDownloadFragmentErrorVR::toJsonObject() const
{
    QJsonObject object;
    ICommonFields::toJsonObject(object);
    IJsonable::typeToJsonObject(object);
    IResponseResultable::resultResponseToJsonObject(object);
    object.insert("streamId", streamId);
    QSTRING_TO_JSON(mTmpVideoFilePath, object);
    QSTRING_TO_JSON(mErrorString, object);
    return object;
}




// ------------------------------------------------
// ----- ResponseDeleteTmpVideoFilesVR
// ------------------------------------------------

ResponseDeleteTmpVideoFilesVR::ResponseDeleteTmpVideoFilesVR():IJsonable(), ICommonFields(), IResponseResultable()
{

}

ResponseDeleteTmpVideoFilesVR::ResponseDeleteTmpVideoFilesVR(const ResponseDeleteTmpVideoFilesVR &obj):IJsonable(), ICommonFields(), IResponseResultable()
{
    selfCopy(obj);
}

ResponseDeleteTmpVideoFilesVR &ResponseDeleteTmpVideoFilesVR::operator =(const ResponseDeleteTmpVideoFilesVR &obj)
{
    OPERATOR_EQUAL_BODY;
}

ResponseDeleteTmpVideoFilesVR::ResponseDeleteTmpVideoFilesVR(const QJsonObject &json)
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

void ResponseDeleteTmpVideoFilesVR::selfCopy(const ResponseDeleteTmpVideoFilesVR &obj)
{
    mUidRequest = obj.mUidRequest;
    mResponseResult = obj.mResponseResult;
    mRemoved = obj.mRemoved;
    mErrorString = obj.mErrorString;
}

EDataType ResponseDeleteTmpVideoFilesVR::type() const
{
    return EDataType::ResponseDeleteTmpVideoFilesVR;
}

QJsonObject ResponseDeleteTmpVideoFilesVR::toJsonObject() const
{
    QJsonObject object;
    ICommonFields::toJsonObject(object);
    IJsonable::typeToJsonObject(object);
    IResponseResultable::resultResponseToJsonObject(object);
    BOOL_TO_JSON(mRemoved, object);
    QSTRING_TO_JSON(mErrorString, object);
    return object;
}

bool ResponseDeleteTmpVideoFilesVR::isValid() const
{
    return true;
}


// ResponseStopDownloadFragmentVR
ResponseStopDownloadFragmentVR::ResponseStopDownloadFragmentVR(const QJsonObject &json)
{
    if ( !IJsonable::typeFromJsonObject(json) ||
         !IResponseResultable::resultResponseFromJsonObject(json)
            )
        return;
    ICommonFields::fromJsonObject(json);
    streamId = json.value("streamId").toObject();
    JSON_TO_QSTRING(json, mErrorString);
}

void ResponseStopDownloadFragmentVR::selfCopy(const ResponseStopDownloadFragmentVR &obj)
{
    mUidRequest = obj.mUidRequest;
    mResponseResult = obj.mResponseResult;
    streamId = obj.streamId;
    mErrorString = obj.mErrorString;
}

QJsonObject ResponseStopDownloadFragmentVR::toJsonObject() const
{
    QJsonObject object;
    ICommonFields::toJsonObject(object);
    IJsonable::typeToJsonObject(object);
    IResponseResultable::resultResponseToJsonObject(object);
    object.insert("streamId", streamId);
    QSTRING_TO_JSON(mErrorString, object);
    return object;
}

/********************************************************************************/
/// \remark лента скриншотов (VR - VideoRecorder)
/********************************************************************************/

///
/// \brief The RequestGetMiniScreenshotsVR struct Запрос "Список мини-скиншотов"
///

RequestGetMiniScreenshotsVR::RequestGetMiniScreenshotsVR():IJsonable(), ICommonFields(),IRequestVR()
{

}

RequestGetMiniScreenshotsVR::RequestGetMiniScreenshotsVR(const RequestGetMiniScreenshotsVR &obj):IJsonable(), ICommonFields(),IRequestVR()
{
    selfCopy(obj);
}

RequestGetMiniScreenshotsVR &RequestGetMiniScreenshotsVR::operator =(const RequestGetMiniScreenshotsVR &obj)
{
    OPERATOR_EQUAL_BODY;
}

RequestGetMiniScreenshotsVR::RequestGetMiniScreenshotsVR(const QJsonObject &json)
{
    if ( !IJsonable::typeFromJsonObject(json)
         )
        return;
    ICommonFields::fromJsonObject(json);
    IRequestVR::fromJsonObject(json);
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

void RequestGetMiniScreenshotsVR::selfCopy(const RequestGetMiniScreenshotsVR &obj)
{
    mUidRequest = obj.mUidRequest;
    mVideoStreamUid = obj.mVideoStreamUid;                  // уид видеопотока
    mDateTimeSreenshots = obj.mDateTimeSreenshots;	// дата-время скриншотов
    mTargetOutputResolution = obj.mTargetOutputResolution;          // целевое выходное разрешение картинок
    IRequestVR::selfCopyIRequestVR(obj);
}

EDataType RequestGetMiniScreenshotsVR::type() const
{
    return EDataType::RequestGetMiniScreenshotsVR;
}

QJsonObject RequestGetMiniScreenshotsVR::toJsonObject() const
{
    QJsonObject object;
    ICommonFields::toJsonObject(object);
    IJsonable::typeToJsonObject(object);
    IRequestVR::toJsonObject(object);
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

bool RequestGetMiniScreenshotsVR::isValid() const
{
      return true;
}

///
/// \brief The ResponseDeleteTmpVideoFiles struct Ответ "Список мини-скиншотов"
///

ResponseGetMiniScreenshotsVR::ResponseGetMiniScreenshotsVR():IJsonable(), ICommonFields(), IResponseResultable()
{

}

ResponseGetMiniScreenshotsVR::ResponseGetMiniScreenshotsVR(const ResponseGetMiniScreenshotsVR &obj):IJsonable(), ICommonFields(), IResponseResultable()
{
    selfCopy(obj);
}

ResponseGetMiniScreenshotsVR &ResponseGetMiniScreenshotsVR::operator =(const ResponseGetMiniScreenshotsVR &obj)
{
    OPERATOR_EQUAL_BODY;
}

ResponseGetMiniScreenshotsVR::ResponseGetMiniScreenshotsVR(const QJsonObject &json)
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

QMap<QDateTime, QImage> ResponseGetMiniScreenshotsVR::miniSreenshots()
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

void ResponseGetMiniScreenshotsVR::setMiniScreenshots(const QMap<QDateTime, QImage> &miniScreenshots)
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

void ResponseGetMiniScreenshotsVR::selfCopy(const ResponseGetMiniScreenshotsVR &obj)
{
    mUidRequest = obj.mUidRequest;
    mResponseResult = obj.mResponseResult;
    mHexedMiniSreenshots = obj.mHexedMiniSreenshots;
}

EDataType ResponseGetMiniScreenshotsVR::type() const
{
    return EDataType::ResponseGetMiniScreenshotsVR;
}

QJsonObject ResponseGetMiniScreenshotsVR::toJsonObject() const
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

bool ResponseGetMiniScreenshotsVR::isValid() const
{
    return true;
}

///
/// \brief The RequestGetScreenshotVR struct Запрос "Полноразмерный скриншот"
///

RequestGetScreenshotVR::RequestGetScreenshotVR():IJsonable(), ICommonFields(),IRequestVR()
{

}

RequestGetScreenshotVR::RequestGetScreenshotVR(const RequestGetScreenshotVR &obj):IJsonable(), ICommonFields(),IRequestVR()
{
    selfCopy(obj);
}

RequestGetScreenshotVR &RequestGetScreenshotVR::operator =(const RequestGetScreenshotVR &obj)
{
    OPERATOR_EQUAL_BODY;
}

RequestGetScreenshotVR::RequestGetScreenshotVR(const QJsonObject &json)
{
    if ( !IJsonable::typeFromJsonObject(json)
         )
        return;
    ICommonFields::fromJsonObject(json);
    IRequestVR::fromJsonObject(json);
    JSON_TO_QUUID(json, mVideoStreamUid);
    mDateTimeSreenshot = QDateTime::fromString( json.value("mDateTimeSreenshot").toString(), cDateTimeFormat );
    {
        QSize temp;
        temp.setWidth(json.value("mTargetOutputResolution_width").toInt());
        temp.setHeight(json.value("mTargetOutputResolution_height").toInt());
        mTargetOutputResolution = temp;
    }
}

void RequestGetScreenshotVR::selfCopy(const RequestGetScreenshotVR &obj)
{
    mUidRequest = obj.mUidRequest;
    mVideoStreamUid = obj.mVideoStreamUid;          // уид видеопотока
    mDateTimeSreenshot = obj.mDateTimeSreenshot;	// дата-время скриншота
    IRequestVR::selfCopyIRequestVR(obj);
}

EDataType RequestGetScreenshotVR::type() const
{
    return EDataType::RequestGetScreenshotVR;
}

QJsonObject RequestGetScreenshotVR::toJsonObject() const
{
    QJsonObject object;
    ICommonFields::toJsonObject(object);
    IJsonable::typeToJsonObject(object);
    IRequestVR::toJsonObject(object);
    QUUID_TO_JSON(mVideoStreamUid, object);
    object.insert("mDateTimeSreenshot", QJsonValue(mDateTimeSreenshot.toString(cDateTimeFormat)));
    object.insert("mTargetOutputResolution_width", QJsonValue::fromVariant(mTargetOutputResolution.width()));
    object.insert("mTargetOutputResolution_height", QJsonValue::fromVariant(mTargetOutputResolution.height()));
    return object;
}

bool RequestGetScreenshotVR::isValid() const
{
    return true;
}

///
/// \brief The ResponseGetScreenshotVR struct Ответ "Полноразмерный скриншот"
///

ResponseGetScreenshotVR::ResponseGetScreenshotVR():IJsonable(), ICommonFields(), IResponseResultable()
{

}

ResponseGetScreenshotVR::ResponseGetScreenshotVR(const ResponseGetScreenshotVR &obj):IJsonable(), ICommonFields(), IResponseResultable()
{
    selfCopy(obj);
}

ResponseGetScreenshotVR &ResponseGetScreenshotVR::operator =(const ResponseGetScreenshotVR &obj)
{
    OPERATOR_EQUAL_BODY;
}

ResponseGetScreenshotVR::ResponseGetScreenshotVR(const QJsonObject &json)
{
    if ( !IJsonable::typeFromJsonObject(json) ||
         !IResponseResultable::resultResponseFromJsonObject(json)  )
        return;
    ICommonFields::fromJsonObject(json);
    mHexedSreenshot = json.value("mHexedSreenshot").toVariant().toByteArray();
}

QImage ResponseGetScreenshotVR::sreenshot()
{
    QImage image;
    QByteArray rawImg = QByteArray::fromHex(mHexedSreenshot);
    QBuffer pictureBuffer(&rawImg);
    pictureBuffer.open(QIODevice::ReadOnly);
    image.load(&pictureBuffer, "JPEG");
    return image;
}

void ResponseGetScreenshotVR::setScreenshot(const QImage &screenshot)
{
    QByteArray rawImg;
    QBuffer pictureBuffer(&rawImg);
    pictureBuffer.open(QIODevice::WriteOnly);
    screenshot.save(&pictureBuffer, "JPEG");
    pictureBuffer.close();
    mHexedSreenshot = rawImg.toHex();
}

void ResponseGetScreenshotVR::selfCopy(const ResponseGetScreenshotVR &obj)
{
    mUidRequest = obj.mUidRequest;
    mResponseResult = obj.mResponseResult;
    mHexedSreenshot = obj.mHexedSreenshot;
}

EDataType ResponseGetScreenshotVR::type() const
{
    return EDataType::ResponseGetScreenshotVR;
}

QJsonObject ResponseGetScreenshotVR::toJsonObject() const
{
    QJsonObject object;
    ICommonFields::toJsonObject(object);
    IJsonable::typeToJsonObject(object);
    IResponseResultable::resultResponseToJsonObject(object);
    object.insert("mHexedSreenshot", QJsonValue::fromVariant(mHexedSreenshot) );
    return object;
}

bool ResponseGetScreenshotVR::isValid() const
{
    return true;
}
