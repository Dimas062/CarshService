#ifndef INTERFACES_H
#define INTERFACES_H

#include <QObject>
#include <QByteArray>
#include <QUuid>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonDocument>
#include <QVariant>
#include <QVector>
#include <QPointF>
#include "interactionprotocollib.h"
#include "interactionprotocoltypes.h"
#include "servicemacros.h"

///
/// \brief The IJsonable struct интерфейс для работы с json-функциональностью объектов
///
struct INTERACTION_PROTOCOL_API IJsonable {
    IJsonable(){}
    ///
    /// \brief type значение (код) типа объекта
    /// \return значение (код)
    ///
    virtual EDataType type() const = 0;
    ///
    /// \brief toJsonObject сериализация объекта в json
    /// \return json-объект
    ///
    virtual QJsonObject toJsonObject() const = 0;
    ///
    /// \brief isValid проверка валидности объекта
    /// \return true - валидный
    ///
    virtual bool isValid() const = 0;    
protected:
    ///
    /// \brief toJsonObject сериализация в json значение (кода) типа объекта
    /// \param json json-объект
    ///
    void typeToJsonObject(QJsonObject& json) const;
    ///
    /// \brief fromJsonObject десериализация из json значение (кода) типа объекта
    /// \param json json-объект
    /// \return результат операции (true - успешно)
    ///
    bool typeFromJsonObject(const QJsonObject& json);
};

struct INTERACTION_PROTOCOL_API ICommonFields {
    ICommonFields(){}
    const QUuid& uidRequest() const;
    void setUidRequest(const QUuid& uid);
protected:
    QUuid mUidRequest = QUuid();
    void toJsonObject(QJsonObject& json) const;
    void fromJsonObject(const QJsonObject& json);
};

///
/// \brief The IResponseResultable struct интерфейс для работы с результатом ответа на запрос
///
struct INTERACTION_PROTOCOL_API IResponseResultable {
    IResponseResultable() {}
    EResult mResponseResult = EResult::None;    ///< результат ответа на запрос
protected:
    ///
    /// \brief toJsonObject сериализация в json значение (кода) типа объекта
    /// \param json json-объект
    ///
    void resultResponseToJsonObject(QJsonObject& json) const;
    ///
    /// \brief fromJsonObject десериализация из json значение (кода) типа объекта
    /// \param json json-объект
    /// \return результат операции (true - успешно)
    ///
    bool resultResponseFromJsonObject(const QJsonObject& json);
};

struct INTERACTION_PROTOCOL_API IRequestVR {
    IRequestVR(){}
    quint8 mVendor = 255;
    QString mVRJsonParameters = "";  ///< параметры видеорега в формате json
protected:
    void toJsonObject(QJsonObject& json) const;
    void fromJsonObject(const QJsonObject& json);
    template<class TRequest>
    void selfCopyIRequestVR(const TRequest& obj) {
        mVendor = obj.mVendor;
        mVRJsonParameters = obj.mVRJsonParameters;
    }
};

#endif // INTERFACES_H
