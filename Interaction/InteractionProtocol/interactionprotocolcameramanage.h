#ifndef INTERACTIONPROTOCOLCAMERAMANAGE_H
#define INTERACTIONPROTOCOLCAMERAMANAGE_H

#include "interactionprotocol.h"

/// \remark GetCameraParameters

struct INTERACTION_PROTOCOL_API RequestGetCameraParameters : public IJsonable, public ICommonFields {
    RequestGetCameraParameters();
    RequestGetCameraParameters(const RequestGetCameraParameters &obj);
    RequestGetCameraParameters &operator =(const RequestGetCameraParameters &obj);
    RequestGetCameraParameters(const QJsonObject &json);

    QUuid mCameraUid = QUuid();
    int mStreamType = 0;    ///< 0 - основной, 1 - дополнтельный
protected:
    void selfCopy(const RequestGetCameraParameters &obj);
    // IJsonable interface
public:
    virtual EDataType type() const override;
    virtual QJsonObject toJsonObject() const override;
    virtual bool isValid() const override;
};

struct INTERACTION_PROTOCOL_API ResponseGetCameraParameters : public IJsonable, public ICommonFields, public IResponseResultable {
    ResponseGetCameraParameters();
    ResponseGetCameraParameters(const ResponseGetCameraParameters &obj);
    ResponseGetCameraParameters &operator =(const ResponseGetCameraParameters &obj);
    ResponseGetCameraParameters(const QJsonObject &json);

    QString mJsonParameters = "";
protected:
    void selfCopy(const ResponseGetCameraParameters &obj);
    // IJsonable interface
public:
    virtual EDataType type() const override;
    virtual QJsonObject toJsonObject() const override;
    virtual bool isValid() const override;
};

/// \remark SetCameraParameters

struct INTERACTION_PROTOCOL_API RequestSetCameraParameters : public IJsonable, public ICommonFields {
    RequestSetCameraParameters();
    RequestSetCameraParameters(const RequestSetCameraParameters &obj);
    RequestSetCameraParameters &operator =(const RequestSetCameraParameters &obj);
    RequestSetCameraParameters(const QJsonObject &json);

    QUuid mCameraUid = QUuid();
    QString mJsonParameters = "";
protected:
    void selfCopy(const RequestSetCameraParameters &obj);
    // IJsonable interface
public:
    virtual EDataType type() const override;
    virtual QJsonObject toJsonObject() const override;
    virtual bool isValid() const override;
};

struct INTERACTION_PROTOCOL_API ResponseSetCameraParameters : public IJsonable, public ICommonFields, public IResponseResultable {
    ResponseSetCameraParameters();
    ResponseSetCameraParameters(const ResponseSetCameraParameters &obj);
    ResponseSetCameraParameters &operator =(const ResponseSetCameraParameters &obj);
    ResponseSetCameraParameters(const QJsonObject &json);

protected:
    void selfCopy(const ResponseSetCameraParameters &obj);
    // IJsonable interface
public:
    virtual EDataType type() const override;
    virtual QJsonObject toJsonObject() const override;
    virtual bool isValid() const override;
};

/// \remark RebootCamera

struct INTERACTION_PROTOCOL_API RequestRebootCamera : public IJsonable, public ICommonFields {
    RequestRebootCamera();
    RequestRebootCamera(const RequestRebootCamera &obj);
    RequestRebootCamera &operator =(const RequestRebootCamera &obj);
    RequestRebootCamera(const QJsonObject &json);

    QUuid mCameraUid = QUuid();
protected:
    void selfCopy(const RequestRebootCamera &obj);
    // IJsonable interface
public:
    virtual EDataType type() const override;
    virtual QJsonObject toJsonObject() const override;
    virtual bool isValid() const override;
};

struct INTERACTION_PROTOCOL_API ResponseRebootCamera : public IJsonable, public ICommonFields, public IResponseResultable {
    ResponseRebootCamera();
    ResponseRebootCamera(const ResponseRebootCamera &obj);
    ResponseRebootCamera &operator =(const ResponseRebootCamera &obj);
    ResponseRebootCamera(const QJsonObject &json);

protected:
    void selfCopy(const ResponseRebootCamera &obj);
    // IJsonable interface
public:
    virtual EDataType type() const override;
    virtual QJsonObject toJsonObject() const override;
    virtual bool isValid() const override;
};

#endif // INTERACTIONPROTOCOLCAMERAMANAGE_H
