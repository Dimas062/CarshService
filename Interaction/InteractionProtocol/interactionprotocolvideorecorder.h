#ifndef INTERACTIONPROTOCOLVIDEORECORDER_H
#define INTERACTIONPROTOCOLVIDEORECORDER_H

/// \remark команды для взаимодействия с видеорегистраторами

#include "interactionprotocolstructs.h"
#include "interfaces.h"
#include <QSize>
#include <QPicture>
#include <QBuffer>
#include <QImage>

/// \remark запросы

struct INTERACTION_PROTOCOL_API RequestCreateRtspStreamVideoVR : public IJsonable, public ICommonFields, public IRequestVR {
    RequestCreateRtspStreamVideoVR();
    RequestCreateRtspStreamVideoVR(const RequestCreateRtspStreamVideoVR &obj);
    RequestCreateRtspStreamVideoVR &operator =(const RequestCreateRtspStreamVideoVR &obj);
    RequestCreateRtspStreamVideoVR(const QJsonObject &json);

    QUuid mRtspStreamUid = QUuid();           ///< УНИКАЛЬНЫЙ идентификатор RTSP потока
    QJsonObject streamId = QJsonObject();   ///< Описание потока (VRStreamId из VideoRecorderApi)
    QDateTime dt = QDateTime();
    quint8 speed = 1;
    bool needPreview = true;

protected:
    void selfCopy(const RequestCreateRtspStreamVideoVR &obj);
    // IJsonable interface
public:
    virtual EDataType type() const override;
    virtual QJsonObject toJsonObject() const override;
    virtual bool isValid() const override;
};

struct INTERACTION_PROTOCOL_API RequestStartRtspStreamVideoVR : public IJsonable, public ICommonFields, public IRequestVR {
    RequestStartRtspStreamVideoVR();
    RequestStartRtspStreamVideoVR(const RequestStartRtspStreamVideoVR &obj);
    RequestStartRtspStreamVideoVR &operator =(const RequestStartRtspStreamVideoVR &obj);
    RequestStartRtspStreamVideoVR(const QJsonObject &json);

    QUuid mRtspStreamUid = QUuid();           ///< УНИКАЛЬНЫЙ идентификатор RTSP потока
    QString transToken = "";
    QDateTime dt = QDateTime();
    quint8 speed = 1;
protected:
    void selfCopy(const RequestStartRtspStreamVideoVR &obj);
    // IJsonable interface
public:
    virtual EDataType type() const override;
    virtual QJsonObject toJsonObject() const override;
    virtual bool isValid() const override;
};

struct INTERACTION_PROTOCOL_API RequestStopRtspStreamVideoVR : public IJsonable, public ICommonFields, public IRequestVR {
    RequestStopRtspStreamVideoVR();
    RequestStopRtspStreamVideoVR(const RequestStopRtspStreamVideoVR &obj);
    RequestStopRtspStreamVideoVR &operator =(const RequestStopRtspStreamVideoVR &obj);
    RequestStopRtspStreamVideoVR(const QJsonObject &json);

    QUuid mRtspStreamUid = QUuid();           ///< УНИКАЛЬНЫЙ идентификатор RTSP потока
    QString transToken = "";
protected:
    void selfCopy(const RequestStopRtspStreamVideoVR &obj);
    // IJsonable interface
public:
    virtual EDataType type() const override;
    virtual QJsonObject toJsonObject() const override;
    virtual bool isValid() const override;
};

struct INTERACTION_PROTOCOL_API RequestStartRtspStreamCameraVR : public IJsonable, public ICommonFields, public IRequestVR {
    RequestStartRtspStreamCameraVR();
    RequestStartRtspStreamCameraVR(const RequestStartRtspStreamCameraVR &obj);
    RequestStartRtspStreamCameraVR &operator =(const RequestStartRtspStreamCameraVR &obj);
    RequestStartRtspStreamCameraVR(const QJsonObject &json);

    QUuid mStreamUid = QUuid();           ///< UID потока камеры
    QUuid mRtspStreamUid = QUuid();       ///< УНИКАЛЬНЫЙ идентификатор RTSP потока
    QUuid mCameraUid = QUuid();           ///< UID камеры
    QUuid mCassyUid = QUuid();            ///< UID кассы
protected:
    void selfCopy(const RequestStartRtspStreamCameraVR &obj);
    // IJsonable interface
public:
    virtual EDataType type() const override;
    virtual QJsonObject toJsonObject() const override;
    virtual bool isValid() const override;
};

struct INTERACTION_PROTOCOL_API RequestStopRtspStreamCameraVR : public IJsonable, public ICommonFields, public IRequestVR {
    RequestStopRtspStreamCameraVR();
    RequestStopRtspStreamCameraVR(const RequestStopRtspStreamCameraVR &obj);
    RequestStopRtspStreamCameraVR &operator =(const RequestStopRtspStreamCameraVR &obj);
    RequestStopRtspStreamCameraVR(const QJsonObject &json);

    QUuid mStreamUid = QUuid();         ///< UID потока камеры
    QUuid mRtspStreamUid = QUuid();     ///< УНИКАЛЬНЫЙ идентификатор RTSP потока
    QUuid mCameraUid = QUuid();         ///< UID камеры
    QUuid mCassyUid = QUuid();          ///< UID кассы
protected:
    void selfCopy(const RequestStopRtspStreamCameraVR &obj);
    // IJsonable interface
public:
    virtual EDataType type() const override;
    virtual QJsonObject toJsonObject() const override;
    virtual bool isValid() const override;
};

struct INTERACTION_PROTOCOL_API RequestGetExistingArchiveTimelineVR : public IJsonable, public ICommonFields, public IRequestVR {
    RequestGetExistingArchiveTimelineVR();
    RequestGetExistingArchiveTimelineVR(const RequestGetExistingArchiveTimelineVR &obj);
    RequestGetExistingArchiveTimelineVR &operator =(const RequestGetExistingArchiveTimelineVR &obj);
    RequestGetExistingArchiveTimelineVR(const QJsonObject &json);

    qint64 translationId = 0;               ///< Уникальный идентификатор трансляции, для которой запрашивается таймлайн
    QJsonObject streamId = QJsonObject();   ///< Описание потока (VRStreamId из VideoRecorderApi)
    qint64 start = -1;                      ///< msecs since epoch
    qint64 end = 1;                         ///< msecs since epoch
protected:
    void selfCopy(const RequestGetExistingArchiveTimelineVR &obj);
    // IJsonable interface
public:
    virtual EDataType type() const override;
    virtual QJsonObject toJsonObject() const override;
    virtual bool isValid() const override;
};

struct INTERACTION_PROTOCOL_API RequestGetExistingArchiveTimelinesOfStreamsVR : public IJsonable, public ICommonFields, public IRequestVR {
    RequestGetExistingArchiveTimelinesOfStreamsVR();
    RequestGetExistingArchiveTimelinesOfStreamsVR(const RequestGetExistingArchiveTimelinesOfStreamsVR &obj);
    RequestGetExistingArchiveTimelinesOfStreamsVR &operator =(const RequestGetExistingArchiveTimelinesOfStreamsVR &obj);
    RequestGetExistingArchiveTimelinesOfStreamsVR(const QJsonObject &json);

    VRGetTimelineRequestParameters mParameters = VRGetTimelineRequestParameters();

protected:
    void selfCopy(const RequestGetExistingArchiveTimelinesOfStreamsVR &obj);
    // IJsonable interface
public:
    virtual EDataType type() const override;
    virtual QJsonObject toJsonObject() const override;
    virtual bool isValid() const override;
};

struct INTERACTION_PROTOCOL_API RequestGetRecordingScheduleVR : public IJsonable, public ICommonFields, public IRequestVR {
    RequestGetRecordingScheduleVR();
    RequestGetRecordingScheduleVR(const RequestGetRecordingScheduleVR &obj);
    RequestGetRecordingScheduleVR &operator =(const RequestGetRecordingScheduleVR &obj);
    RequestGetRecordingScheduleVR(const QJsonObject &json);

    QJsonObject streamId = QJsonObject();   ///< Описание потока (VRStreamId из VideoRecorderApi)
protected:
    void selfCopy(const RequestGetRecordingScheduleVR &obj);
    // IJsonable interface
public:
    virtual EDataType type() const override;
    virtual QJsonObject toJsonObject() const override;
    virtual bool isValid() const override;
};

struct INTERACTION_PROTOCOL_API RequestSetRecordingScheduleVR : public IJsonable, public ICommonFields, public IRequestVR {
    RequestSetRecordingScheduleVR();
    RequestSetRecordingScheduleVR(const RequestSetRecordingScheduleVR &obj);
    RequestSetRecordingScheduleVR &operator =(const RequestSetRecordingScheduleVR &obj);
    RequestSetRecordingScheduleVR(const QJsonObject &json);

    QJsonObject streamId = QJsonObject();    ///< Описание потока (VRStreamId из VideoRecorderApi)
    QVector<QVector<QDateTime>> schedule = QVector<QVector<QDateTime>>();
protected:
    void selfCopy(const RequestSetRecordingScheduleVR &obj);
    // IJsonable interface
public:
    virtual EDataType type() const override;
    virtual QJsonObject toJsonObject() const override;
    virtual bool isValid() const override;
};

struct INTERACTION_PROTOCOL_API RequestStartRecordVR : public IJsonable, public ICommonFields, public IRequestVR {
    RequestStartRecordVR();
    RequestStartRecordVR(const RequestStartRecordVR &obj);
    RequestStartRecordVR &operator =(const RequestStartRecordVR &obj);
    RequestStartRecordVR(const QJsonObject &json);

    QJsonObject streamId = QJsonObject();    ///< Описание потока (VRStreamId из VideoRecorderApi)
protected:
    void selfCopy(const RequestStartRecordVR &obj);
    // IJsonable interface
public:
    virtual EDataType type() const override;
    virtual QJsonObject toJsonObject() const override;
    virtual bool isValid() const override;
};

struct INTERACTION_PROTOCOL_API RequestStopRecordVR : public IJsonable, public ICommonFields, public IRequestVR {
    RequestStopRecordVR();
    RequestStopRecordVR(const RequestStopRecordVR &obj);
    RequestStopRecordVR &operator =(const RequestStopRecordVR &obj);
    RequestStopRecordVR(const QJsonObject &json);

    QJsonObject streamId = QJsonObject();   ///< Описание потока (VRStreamId из VideoRecorderApi)
protected:
    void selfCopy(const RequestStopRecordVR &obj);
    // IJsonable interface
public:
    virtual EDataType type() const override;
    virtual QJsonObject toJsonObject() const override;
    virtual bool isValid() const override;
};

struct INTERACTION_PROTOCOL_API RequestExportArchiveVR : public IJsonable, public ICommonFields, public IRequestVR {
    RequestExportArchiveVR();
    RequestExportArchiveVR(const RequestExportArchiveVR &obj);
    RequestExportArchiveVR &operator =(const RequestExportArchiveVR &obj);
    RequestExportArchiveVR(const QJsonObject &json);

    QJsonObject streamId = QJsonObject();   ///< Описание потока (VRStreamId из VideoRecorderApi)
    QDateTime start = QDateTime();
    QDateTime end = QDateTime();
protected:
    void selfCopy(const RequestExportArchiveVR &obj);
    // IJsonable interface
public:
    virtual EDataType type() const override;
    virtual QJsonObject toJsonObject() const override;
    virtual bool isValid() const override;
};


struct INTERACTION_PROTOCOL_API RequestGetChannelsVR : public IJsonable, public ICommonFields, public IRequestVR {
    RequestGetChannelsVR();
    RequestGetChannelsVR(const RequestGetChannelsVR &obj);
    RequestGetChannelsVR &operator =(const RequestGetChannelsVR &obj);
    RequestGetChannelsVR(const QJsonObject &json);

protected:
    void selfCopy(const RequestGetChannelsVR &obj);
    // IJsonable interface
public:
    virtual EDataType type() const override;
    virtual QJsonObject toJsonObject() const override;
    virtual bool isValid() const override;
};



///
/// \brief The RequestDownloadFragmentVR struct экспорт файла с регистратора во временный (для экспорта пишущегося) - команда серверу - запрос
///
struct INTERACTION_PROTOCOL_API RequestDownloadFragmentVR : public IJsonable, public ICommonFields, public IRequestVR {
    RequestDownloadFragmentVR();
    RequestDownloadFragmentVR(const RequestDownloadFragmentVR &obj);
    RequestDownloadFragmentVR &operator =(const RequestDownloadFragmentVR &obj);
    RequestDownloadFragmentVR(const QJsonObject &json);

    QJsonObject streamId = QJsonObject();   ///< Описание потока (VRStreamId из VideoRecorderApi)
    qint64 start = -1;                      ///< msecs since epoch
    qint64 end = -1;                         ///< msecs since epoch

protected:
    void selfCopy(const RequestDownloadFragmentVR &obj);
    // IJsonable interface
public:
    virtual EDataType type() const override;
    virtual QJsonObject toJsonObject() const override;
    virtual bool isValid() const override;
};



///
/// \brief The RequestDeleteTmpVideoFiles struct удали временные файлы, использованные для экспорта  - команда серверу - запрос
///
struct INTERACTION_PROTOCOL_API RequestDeleteTmpVideoFilesVR : public IJsonable, public ICommonFields {
    RequestDeleteTmpVideoFilesVR();
    RequestDeleteTmpVideoFilesVR(const RequestDeleteTmpVideoFilesVR &obj);
    RequestDeleteTmpVideoFilesVR &operator =(const RequestDeleteTmpVideoFilesVR &obj);
    RequestDeleteTmpVideoFilesVR(const QJsonObject &json);

protected:
    void selfCopy(const RequestDeleteTmpVideoFilesVR &obj);
    // IJsonable interface
public:
    virtual EDataType type() const override;
    virtual QJsonObject toJsonObject() const override;
    virtual bool isValid() const override;
};


///
/// \brief The RequestStopDownloadFragmentVR struct стоп экспорта файла с регистратора во временный (для экспорта пишущегося) - команда серверу - запрос
///
struct INTERACTION_PROTOCOL_API RequestStopDownloadFragmentVR : public IJsonable, public ICommonFields, public IRequestVR {
    RequestStopDownloadFragmentVR();
    RequestStopDownloadFragmentVR(const RequestStopDownloadFragmentVR &obj);
    RequestStopDownloadFragmentVR &operator =(const RequestStopDownloadFragmentVR &obj);
    RequestStopDownloadFragmentVR(const QJsonObject &json);

    QJsonObject streamId = QJsonObject();   ///< Описание потока (VRStreamId из VideoRecorderApi)

protected:
    void selfCopy(const RequestStopDownloadFragmentVR &obj);
    // IJsonable interface
public:
    virtual EDataType type() const override;
    virtual QJsonObject toJsonObject() const override;
    virtual bool isValid() const override;
};











/// \remark ответы

struct INTERACTION_PROTOCOL_API ResponseCreateRtspStreamVideoVR : public IJsonable, public ICommonFields, public IResponseResultable {
    ResponseCreateRtspStreamVideoVR();
    ResponseCreateRtspStreamVideoVR(const ResponseCreateRtspStreamVideoVR &obj);
    ResponseCreateRtspStreamVideoVR &operator =(const ResponseCreateRtspStreamVideoVR &obj);
    ResponseCreateRtspStreamVideoVR(const QJsonObject &json);

    QJsonObject streamId = QJsonObject();   ///< Описание потока (VRStreamId из VideoRecorderApi)
    QString transToken = "";
    QString url = "";
    QByteArray mPreviewFrame = "";
protected:
    void selfCopy(const ResponseCreateRtspStreamVideoVR &obj);
    // IJsonable interface
public:
    virtual EDataType type() const override;
    virtual QJsonObject toJsonObject() const override;
    virtual bool isValid() const override;
};

struct INTERACTION_PROTOCOL_API ResponseStartRtspStreamVideoVR : public IJsonable, public ICommonFields, public IResponseResultable {
    ResponseStartRtspStreamVideoVR();
    ResponseStartRtspStreamVideoVR(const ResponseStartRtspStreamVideoVR &obj);
    ResponseStartRtspStreamVideoVR &operator =(const ResponseStartRtspStreamVideoVR &obj);
    ResponseStartRtspStreamVideoVR(const QJsonObject &json);

    QString transToken = "";
    QString url = "";
protected:
    void selfCopy(const ResponseStartRtspStreamVideoVR &obj);
    // IJsonable interface
public:
    virtual EDataType type() const override;
    virtual QJsonObject toJsonObject() const override;
    virtual bool isValid() const override;
};

struct INTERACTION_PROTOCOL_API ResponseStopRtspStreamVideoVR : public IJsonable, public ICommonFields, public IResponseResultable {
    ResponseStopRtspStreamVideoVR();
    ResponseStopRtspStreamVideoVR(const ResponseStopRtspStreamVideoVR &obj);
    ResponseStopRtspStreamVideoVR &operator =(const ResponseStopRtspStreamVideoVR &obj);
    ResponseStopRtspStreamVideoVR(const QJsonObject &json);

    QString transToken = "";
    bool result = false;
protected:
    void selfCopy(const ResponseStopRtspStreamVideoVR &obj);
    // IJsonable interface
public:
    virtual EDataType type() const override;
    virtual QJsonObject toJsonObject() const override;
    virtual bool isValid() const override;
};

struct INTERACTION_PROTOCOL_API ResponseStartRtspStreamCameraVR : public IJsonable, public ICommonFields, public IResponseResultable {
    ResponseStartRtspStreamCameraVR();
    ResponseStartRtspStreamCameraVR(const ResponseStartRtspStreamCameraVR &obj);
    ResponseStartRtspStreamCameraVR &operator =(const ResponseStartRtspStreamCameraVR &obj);
    ResponseStartRtspStreamCameraVR(const QJsonObject &json);

    QString mRtspUrl = "";   ///< строка доступа (url) к rtsp-потоку
protected:
    void selfCopy(const ResponseStartRtspStreamCameraVR &obj);
    // IJsonable interface
public:
    virtual EDataType type() const override;
    virtual QJsonObject toJsonObject() const override;
    virtual bool isValid() const override;
};

struct INTERACTION_PROTOCOL_API ResponseStopRtspStreamCameraVR : public IJsonable, public ICommonFields, public IResponseResultable {
    ResponseStopRtspStreamCameraVR();
    ResponseStopRtspStreamCameraVR(const ResponseStopRtspStreamCameraVR &obj);
    ResponseStopRtspStreamCameraVR &operator =(const ResponseStopRtspStreamCameraVR &obj);
    ResponseStopRtspStreamCameraVR(const QJsonObject &json);

protected:
    void selfCopy(const ResponseStopRtspStreamCameraVR &obj);
    // IJsonable interface
public:
    virtual EDataType type() const override;
    virtual QJsonObject toJsonObject() const override;
    virtual bool isValid() const override;
};

struct INTERACTION_PROTOCOL_API ResponseGetExistingArchiveTimelineVR : public IJsonable, public ICommonFields, public IResponseResultable {
    ResponseGetExistingArchiveTimelineVR();
    ResponseGetExistingArchiveTimelineVR(const ResponseGetExistingArchiveTimelineVR &obj);
    ResponseGetExistingArchiveTimelineVR &operator =(const ResponseGetExistingArchiveTimelineVR &obj);
    ResponseGetExistingArchiveTimelineVR(const QJsonObject &json);

    qint64 translationId = 0;                   ///< Уникальный идентификатор трансляции, для которой запрашивается таймлайн
    QJsonObject streamId = QJsonObject();                       ///< Описание потока (VRStreamId из VideoRecorderApi)
    QVector<QPair<qint64, qint64>> timeline;    ///< msecs since epoch
protected:
    void selfCopy(const ResponseGetExistingArchiveTimelineVR &obj);
    // IJsonable interface
public:
    virtual EDataType type() const override;
    virtual QJsonObject toJsonObject() const override;
    virtual bool isValid() const override;
};


struct INTERACTION_PROTOCOL_API ResponseGetExistingArchiveTimelinesOfStreamsVR : public IJsonable, public ICommonFields, public IResponseResultable {
    ResponseGetExistingArchiveTimelinesOfStreamsVR();
    ResponseGetExistingArchiveTimelinesOfStreamsVR(const ResponseGetExistingArchiveTimelinesOfStreamsVR &obj);
    ResponseGetExistingArchiveTimelinesOfStreamsVR &operator =(const ResponseGetExistingArchiveTimelinesOfStreamsVR &obj);
    ResponseGetExistingArchiveTimelinesOfStreamsVR(const QJsonObject &json);

    VRGetTimelineRequestParameters mParameters = VRGetTimelineRequestParameters();
    QMap<QUuid, QVector<QPair<qint64, qint64>>> mTimelineByStreamsMap;    ///< msecs since epoch
protected:
    void selfCopy(const ResponseGetExistingArchiveTimelinesOfStreamsVR &obj);
    // IJsonable interface
public:
    virtual EDataType type() const override;
    virtual QJsonObject toJsonObject() const override;
    virtual bool isValid() const override;
};

struct INTERACTION_PROTOCOL_API ResponseGetRecordingScheduleVR : public IJsonable, public ICommonFields, public IResponseResultable {
    ResponseGetRecordingScheduleVR();
    ResponseGetRecordingScheduleVR(const ResponseGetRecordingScheduleVR &obj);
    ResponseGetRecordingScheduleVR &operator =(const ResponseGetRecordingScheduleVR &obj);
    ResponseGetRecordingScheduleVR(const QJsonObject &json);

    QJsonObject streamId = QJsonObject();   ///< Описание потока (VRStreamId из VideoRecorderApi)
    QVector<QVector<QDateTime>> schedule = QVector<QVector<QDateTime>>();
protected:
    void selfCopy(const ResponseGetRecordingScheduleVR &obj);
    // IJsonable interface
public:
    virtual EDataType type() const override;
    virtual QJsonObject toJsonObject() const override;
    virtual bool isValid() const override;
};

struct INTERACTION_PROTOCOL_API ResponseSetRecordingScheduleVR : public IJsonable, public ICommonFields, public IResponseResultable {
    ResponseSetRecordingScheduleVR();
    ResponseSetRecordingScheduleVR(const ResponseSetRecordingScheduleVR &obj);
    ResponseSetRecordingScheduleVR &operator =(const ResponseSetRecordingScheduleVR &obj);
    ResponseSetRecordingScheduleVR(const QJsonObject &json);

    QJsonObject streamId = QJsonObject();   ///< Описание потока (VRStreamId из VideoRecorderApi)
protected:
    void selfCopy(const ResponseSetRecordingScheduleVR &obj);
    // IJsonable interface
public:
    virtual EDataType type() const override;
    virtual QJsonObject toJsonObject() const override;
    virtual bool isValid() const override;
};

struct INTERACTION_PROTOCOL_API ResponseStartRecordVR : public IJsonable, public ICommonFields, public IResponseResultable {
    ResponseStartRecordVR();
    ResponseStartRecordVR(const ResponseStartRecordVR &obj);
    ResponseStartRecordVR &operator =(const ResponseStartRecordVR &obj);
    ResponseStartRecordVR(const QJsonObject &json);

    QJsonObject streamId = QJsonObject();   ///< Описание потока (VRStreamId из VideoRecorderApi)
    bool result = true;
protected:
    void selfCopy(const ResponseStartRecordVR &obj);
    // IJsonable interface
public:
    virtual EDataType type() const override;
    virtual QJsonObject toJsonObject() const override;
    virtual bool isValid() const override;
};

struct INTERACTION_PROTOCOL_API ResponseStopRecordVR : public IJsonable, public ICommonFields, public IResponseResultable {
    ResponseStopRecordVR();
    ResponseStopRecordVR(const ResponseStopRecordVR &obj);
    ResponseStopRecordVR &operator =(const ResponseStopRecordVR &obj);
    ResponseStopRecordVR(const QJsonObject &json);

    QJsonObject streamId = QJsonObject();   ///< Описание потока (VRStreamId из VideoRecorderApi)
    bool result = true;
protected:
    void selfCopy(const ResponseStopRecordVR &obj);
    // IJsonable interface
public:
    virtual EDataType type() const override;
    virtual QJsonObject toJsonObject() const override;
    virtual bool isValid() const override;
};

struct INTERACTION_PROTOCOL_API ResponseExportArchiveVR : public IJsonable, public ICommonFields, public IResponseResultable {
    ResponseExportArchiveVR();
    ResponseExportArchiveVR(const ResponseExportArchiveVR &obj);
    ResponseExportArchiveVR &operator =(const ResponseExportArchiveVR &obj);
    ResponseExportArchiveVR(const QJsonObject &json);

    QJsonObject streamId = QJsonObject();   ///< Описание потока (VRStreamId из VideoRecorderApi)
    QString url = "";
protected:
    void selfCopy(const ResponseExportArchiveVR &obj);
    // IJsonable interface
public:
    virtual EDataType type() const override;
    virtual QJsonObject toJsonObject() const override;
    virtual bool isValid() const override;
};

struct INTERACTION_PROTOCOL_API ResponseGetChannelsVR : public IJsonable, public ICommonFields, public IResponseResultable {
    ResponseGetChannelsVR();
    ResponseGetChannelsVR(const ResponseGetChannelsVR &obj);
    ResponseGetChannelsVR &operator =(const ResponseGetChannelsVR &obj);
    ResponseGetChannelsVR(const QJsonObject &json);

    QString mChannelsJson = "";   ///< строка с джсоном с массивом каналов видеорега
protected:
    void selfCopy(const ResponseGetChannelsVR &obj);
    // IJsonable interface
public:
    virtual EDataType type() const override;
    virtual QJsonObject toJsonObject() const override;
    virtual bool isValid() const override;
};


///
/// \brief The ResponseDownloadFragmentStartedVR struct начался экспорт файла с регистратора во временный (для экспорта пишущегося) - команда серверу - ответ
///
struct INTERACTION_PROTOCOL_API ResponseDownloadFragmentStartedVR : public IJsonable, public ICommonFields, public IResponseResultable {
    ResponseDownloadFragmentStartedVR() : IJsonable(), ICommonFields(), IResponseResultable() {}
    ResponseDownloadFragmentStartedVR(const ResponseDownloadFragmentStartedVR &obj) : IJsonable(), ICommonFields(), IResponseResultable() { selfCopy(obj); }
    ResponseDownloadFragmentStartedVR &operator =(const ResponseDownloadFragmentStartedVR &obj) { OPERATOR_EQUAL_BODY; }
    ResponseDownloadFragmentStartedVR(const QJsonObject &json);

    QJsonObject streamId = QJsonObject();   ///< Описание потока (VRStreamId из VideoRecorderApi)
    QString mTmpVideoFilePath = "";
    QString mErrorString = "";

protected:
    void selfCopy(const ResponseDownloadFragmentStartedVR &obj);
    // IJsonable interface
public:
    virtual EDataType type() const override { return EDataType::ResponseDownloadFragmentStartedVR; }
    virtual QJsonObject toJsonObject() const override;
    virtual bool isValid() const override { return true; }
};


///
/// \brief The ResponseDownloadFragmentProgressVR struct прогресс экспорт файла с регистратора во временный (для экспорта пишущегося) - команда серверу - ответ
///
struct INTERACTION_PROTOCOL_API ResponseDownloadFragmentProgressVR : public IJsonable, public ICommonFields, public IResponseResultable {
    ResponseDownloadFragmentProgressVR() : IJsonable(), ICommonFields(), IResponseResultable() {}
    ResponseDownloadFragmentProgressVR(const ResponseDownloadFragmentProgressVR &obj) : IJsonable(), ICommonFields(), IResponseResultable() { selfCopy(obj); }
    ResponseDownloadFragmentProgressVR &operator =(const ResponseDownloadFragmentProgressVR &obj) { OPERATOR_EQUAL_BODY; }
    ResponseDownloadFragmentProgressVR(const QJsonObject &json);

    QJsonObject streamId = QJsonObject();   ///< Описание потока (VRStreamId из VideoRecorderApi)
    QString mTmpVideoFilePath = "";
    QString mErrorString = "";
    quint8 mProgress = 0;

protected:
    void selfCopy(const ResponseDownloadFragmentProgressVR &obj);
    // IJsonable interface
public:
    virtual EDataType type() const override { return EDataType::ResponseDownloadFragmentProgressVR; }
    virtual QJsonObject toJsonObject() const override;
    virtual bool isValid() const override { return true; }
};


///
/// \brief The ResponseDownloadFragmentFinishedVR struct завершен экспорт файла с регистратора во временный (для экспорта пишущегося) - команда серверу - ответ
///
struct INTERACTION_PROTOCOL_API ResponseDownloadFragmentFinishedVR : public IJsonable, public ICommonFields, public IResponseResultable {
    ResponseDownloadFragmentFinishedVR() : IJsonable(), ICommonFields(), IResponseResultable() {}
    ResponseDownloadFragmentFinishedVR(const ResponseDownloadFragmentFinishedVR &obj) : IJsonable(), ICommonFields(), IResponseResultable() { selfCopy(obj); }
    ResponseDownloadFragmentFinishedVR &operator =(const ResponseDownloadFragmentFinishedVR &obj) { OPERATOR_EQUAL_BODY; }
    ResponseDownloadFragmentFinishedVR(const QJsonObject &json);

    QJsonObject streamId = QJsonObject();   ///< Описание потока (VRStreamId из VideoRecorderApi)
    QString mTmpVideoFilePath = "";
    QString mErrorString = "";

protected:
    void selfCopy(const ResponseDownloadFragmentFinishedVR &obj);
    // IJsonable interface
public:
    virtual EDataType type() const override { return EDataType::ResponseDownloadFragmentFinishedVR; }
    virtual QJsonObject toJsonObject() const override;
    virtual bool isValid() const override { return true; }
};


///
/// \brief The ResponseDownloadFragmentErrorVR struct ошибка экспорт файла с регистратора во временный (для экспорта пишущегося) - команда серверу - ответ
///
struct INTERACTION_PROTOCOL_API ResponseDownloadFragmentErrorVR : public IJsonable, public ICommonFields, public IResponseResultable {
    ResponseDownloadFragmentErrorVR() : IJsonable(), ICommonFields(), IResponseResultable() {}
    ResponseDownloadFragmentErrorVR(const ResponseDownloadFragmentErrorVR &obj) : IJsonable(), ICommonFields(), IResponseResultable() { selfCopy(obj); }
    ResponseDownloadFragmentErrorVR &operator =(const ResponseDownloadFragmentErrorVR &obj) { OPERATOR_EQUAL_BODY; }
    ResponseDownloadFragmentErrorVR(const QJsonObject &json);

    QJsonObject streamId = QJsonObject();   ///< Описание потока (VRStreamId из VideoRecorderApi)
    QString mTmpVideoFilePath = "";
    QString mErrorString = "";

protected:
    void selfCopy(const ResponseDownloadFragmentErrorVR &obj);
    // IJsonable interface
public:
    virtual EDataType type() const override { return EDataType::ResponseDownloadFragmentErrorVR; }
    virtual QJsonObject toJsonObject() const override;
    virtual bool isValid() const override { return true; }
};


///
/// \brief The ResponseDeleteTmpVideoFilesVR struct удали временные файлы, использованные для экспорта  - команда серверу - ответ
///
struct INTERACTION_PROTOCOL_API ResponseDeleteTmpVideoFilesVR : public IJsonable, public ICommonFields, public IResponseResultable {
    ResponseDeleteTmpVideoFilesVR();
    ResponseDeleteTmpVideoFilesVR(const ResponseDeleteTmpVideoFilesVR &obj);
    ResponseDeleteTmpVideoFilesVR &operator =(const ResponseDeleteTmpVideoFilesVR &obj);
    ResponseDeleteTmpVideoFilesVR(const QJsonObject &json);

    bool mRemoved = false;
    QString mErrorString = "";

protected:
    void selfCopy(const ResponseDeleteTmpVideoFilesVR &obj);
    // IJsonable interface
public:
    virtual EDataType type() const override;
    virtual QJsonObject toJsonObject() const override;
    virtual bool isValid() const override;
};


///
/// \brief The ResponseStopDownloadFragmentVR struct стоп экспорта файла с регистратора во временный (для экспорта пишущегося) - команда серверу - ответ
///
struct INTERACTION_PROTOCOL_API ResponseStopDownloadFragmentVR : public IJsonable, public ICommonFields, public IResponseResultable {
    ResponseStopDownloadFragmentVR() : IJsonable(), ICommonFields(), IResponseResultable() {}
    ResponseStopDownloadFragmentVR(const ResponseStopDownloadFragmentVR &obj) : IJsonable(), ICommonFields(), IResponseResultable() { selfCopy(obj); }
    ResponseStopDownloadFragmentVR &operator =(const ResponseStopDownloadFragmentVR &obj) { OPERATOR_EQUAL_BODY; }
    ResponseStopDownloadFragmentVR(const QJsonObject &json);

    QJsonObject streamId = QJsonObject();   ///< Описание потока (VRStreamId из VideoRecorderApi)
    QString mErrorString = "";

protected:
    void selfCopy(const ResponseStopDownloadFragmentVR &obj);
    // IJsonable interface
public:
    virtual EDataType type() const override { return EDataType::ResponseStopDownloadFragmentVR; }
    virtual QJsonObject toJsonObject() const override;
    virtual bool isValid() const override { return true; }
};

/********************************************************************************/
/// \remark лента скриншотов (VR - VideoRecorder)
/********************************************************************************/

///
/// \brief The RequestGetMiniScreenshotsVR struct Запрос "Список мини-скиншотов"
///
struct INTERACTION_PROTOCOL_API RequestGetMiniScreenshotsVR : public IJsonable, public ICommonFields, public IRequestVR  {
    RequestGetMiniScreenshotsVR();
    RequestGetMiniScreenshotsVR(const RequestGetMiniScreenshotsVR &obj);
    RequestGetMiniScreenshotsVR &operator =(const RequestGetMiniScreenshotsVR &obj);
    RequestGetMiniScreenshotsVR(const QJsonObject &json);

    QUuid mVideoStreamUid;                  ///< уид видеопотока
    QList<QDateTime> mDateTimeSreenshots;	///< дата-время скриншотов
    QSize mTargetOutputResolution;          ///< целевое выходное разрешение картинок
protected:
    const QString cDateTimeFormat = QString("dd.MM.yyyy hh:mm:ss.zzz");
    void selfCopy(const RequestGetMiniScreenshotsVR &obj);
    // IJsonable interface
public:
    virtual EDataType type() const override;
    virtual QJsonObject toJsonObject() const override;
    virtual bool isValid() const override;
};

///
/// \brief The ResponseGetMiniScreenshotsVR struct Ответ "Список мини-скиншотов"
///
struct INTERACTION_PROTOCOL_API ResponseGetMiniScreenshotsVR : public IJsonable, public ICommonFields, public IResponseResultable {
    ResponseGetMiniScreenshotsVR();
    ResponseGetMiniScreenshotsVR(const ResponseGetMiniScreenshotsVR &obj);
    ResponseGetMiniScreenshotsVR &operator =(const ResponseGetMiniScreenshotsVR &obj);
    ResponseGetMiniScreenshotsVR(const QJsonObject &json);

    QMap<QDateTime, QImage> miniSreenshots();	// минискриншоты // image.save(qbuffer, "jpeg") запаковка и передача кадров в сыром виде вформате jpeg - для экономии места
    void setMiniScreenshots(const QMap<QDateTime, QImage>& miniScreenshots);
private:
    QMap<QDateTime, QByteArray> mHexedMiniSreenshots; ///< сырые захексованные скриншоты
protected:
    void selfCopy(const ResponseGetMiniScreenshotsVR &obj);
    // IJsonable interface
public:
    virtual EDataType type() const override;
    virtual QJsonObject toJsonObject() const override;
    virtual bool isValid() const override;
};

///
/// \brief The RequestGetScreenshotVR struct Запрос "Полноразмерный скриншот"
///
struct INTERACTION_PROTOCOL_API RequestGetScreenshotVR : public IJsonable, public ICommonFields, public IRequestVR {
    RequestGetScreenshotVR();
    RequestGetScreenshotVR(const RequestGetScreenshotVR &obj);
    RequestGetScreenshotVR &operator =(const RequestGetScreenshotVR &obj);
    RequestGetScreenshotVR(const QJsonObject &json);

    QUuid mVideoStreamUid;          ///< уид видеопотока
    QDateTime mDateTimeSreenshot;	///< дата-время скриншота
    QSize mTargetOutputResolution;  ///< целевое выходное разрешение скриншота
protected:
    const QString cDateTimeFormat = QString("dd.MM.yyyy hh:mm:ss.zzz");
    void selfCopy(const RequestGetScreenshotVR &obj);
    // IJsonable interface
public:
    virtual EDataType type() const override;
    virtual QJsonObject toJsonObject() const override;
    virtual bool isValid() const override;
};

///
/// \brief The ResponseGetScreenshotVR struct Ответ "Полноразмерный скриншот"
///
struct INTERACTION_PROTOCOL_API ResponseGetScreenshotVR : public IJsonable, public ICommonFields, public IResponseResultable {
    ResponseGetScreenshotVR();
    ResponseGetScreenshotVR(const ResponseGetScreenshotVR &obj);
    ResponseGetScreenshotVR &operator =(const ResponseGetScreenshotVR &obj);
    ResponseGetScreenshotVR(const QJsonObject &json);

    QImage sreenshot();	// скриншот // image.save(qbuffer, "jpeg") запаковка и передача кадров в сыром виде вформате jpeg - для экономии места
    void setScreenshot(const QImage& screenshot);
private:
    QByteArray mHexedSreenshot; ///< сырой захексованный скриншот
protected:
    void selfCopy(const ResponseGetScreenshotVR &obj);
    // IJsonable interface
public:
    virtual EDataType type() const override;
    virtual QJsonObject toJsonObject() const override;
    virtual bool isValid() const override;
};

#endif // INTERACTIONPROTOCOLVIDEORECORDER_H
