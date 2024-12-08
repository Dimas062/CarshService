#ifndef INTERACTIONPROTOCOLEVENTS_H
#define INTERACTIONPROTOCOLEVENTS_H

#include "interfaces.h"
#include <QPicture>
#include "interactionprotocolcashcontrolservice.h"

///
/// \brief The InteractionProtocolEvent struct событие интеллектуального плагина
/// для отправки по сети необходимо его поместить в struct INTERACTION_PROTOCOL_API NetworkMessage
///
struct INTERACTION_PROTOCOL_API InteractionProtocolEvent: public IJsonable {
    InteractionProtocolEvent();
    InteractionProtocolEvent(const InteractionProtocolEvent &obj);
    InteractionProtocolEvent &operator =(const InteractionProtocolEvent &obj);
    InteractionProtocolEvent(const QJsonObject &json);

    QUuid mCameraStreamUuid = QUuid();
    QUuid mEventUuid = QUuid();
    QUuid mEventTypeUuid = QUuid();
    QString mEventText = "";
    qint64 mDateTime = -1;          ///< Дата/время в мсек от начала эпохи
    QColor mForeColor = Qt::black;  ///< цвет текста (RGB)
    QColor mBackColor = Qt::white;  ///< цвет фона (RGB)

protected:
    void selfCopy(const InteractionProtocolEvent &obj);

    // IJsonable interface
public:
    virtual EDataType type() const override;
    virtual QJsonObject toJsonObject() const override;
    virtual bool isValid() const override;
};

Q_DECLARE_METATYPE(InteractionProtocolEvent)

///
/// \brief The InteractionProtocolNotification struct оповещение интеллектуального плагина
/// для отправки по сети необходимо его поместить в struct INTERACTION_PROTOCOL_API NetworkMessage
///
struct INTERACTION_PROTOCOL_API InteractionProtocolNotification: public IJsonable {
    InteractionProtocolNotification();
    InteractionProtocolNotification(const InteractionProtocolNotification &obj);
    InteractionProtocolNotification &operator =(const InteractionProtocolNotification &obj);
    InteractionProtocolNotification(const QJsonObject &json);

    QUuid mCameraStreamUuid = QUuid();
    QUuid mEventTypeUuid = QUuid();
    qint64 mDateTime = -1;          ///< Дата/время в мсек от начала эпохи
    //QPicture mPicture = QPicture();

    QPicture picture();
    void setPicture(QPicture picture);
private:
    QByteArray mHexedPicture;

protected:
    void selfCopy(const InteractionProtocolNotification &obj);

    // IJsonable interface
public:
    virtual EDataType type() const override;
    virtual QJsonObject toJsonObject() const override;
    virtual bool isValid() const override;
};

///
/// \brief The InteractionProtocolIamPluginContainer struct я - плагин-контейнер
/// Плагин-контейнер после подключения к серверу - отправляет это сообщение
///
struct INTERACTION_PROTOCOL_API InteractionProtocolIamPluginContainer: public IJsonable {
    InteractionProtocolIamPluginContainer();
    InteractionProtocolIamPluginContainer(const InteractionProtocolIamPluginContainer &obj);
    InteractionProtocolIamPluginContainer &operator =(const InteractionProtocolIamPluginContainer &obj);
    InteractionProtocolIamPluginContainer(const QJsonObject &json);
protected:
    void selfCopy(const InteractionProtocolIamPluginContainer &obj);

    // IJsonable interface
public:
    virtual EDataType type() const override;
    virtual QJsonObject toJsonObject() const override;
    virtual bool isValid() const override;
};

///
/// \brief The InteractionProtocolIamClient struct я - клиент
/// при подключении клиент отрпавляет это сообщение, чтобы его сервер зарегестрировал
///
struct INTERACTION_PROTOCOL_API InteractionProtocolIamClient: public IJsonable {
    InteractionProtocolIamClient();
    InteractionProtocolIamClient(const InteractionProtocolIamClient &obj);
    InteractionProtocolIamClient &operator =(const InteractionProtocolIamClient &obj);
    InteractionProtocolIamClient(const QJsonObject &json);

    QUuid mClientUid; ///< uid (токен) его выдаёт сервер при авторизации (придёт клиенту в ответе на авторизацию)
protected:
    void selfCopy(const InteractionProtocolIamClient &obj);

    // IJsonable interface
public:
    virtual EDataType type() const override;
    virtual QJsonObject toJsonObject() const override;
    virtual bool isValid() const override;
};

///
/// \brief The InteractionProtocolFilter struct команды фильтрации оповещений для плагин-контейнера
/// serverApp подаёт её плагин-контейнеру для разрешения/запрета трансляции оповещений
///
struct INTERACTION_PROTOCOL_API InteractionProtocolFilter: public IJsonable {
    InteractionProtocolFilter();
    InteractionProtocolFilter(const InteractionProtocolFilter &obj);
    InteractionProtocolFilter &operator =(const InteractionProtocolFilter &obj);
    InteractionProtocolFilter(const QJsonObject &json);

    QUuid mCameraUuid = QUuid();        ///< uid камеры
    bool mBroadcastResolution = false;  ///< разрешение трансляции true - разрешено транслировать, false - запрещено транслировать
protected:
    void selfCopy(const InteractionProtocolFilter &obj);

    // IJsonable interface
public:
    virtual EDataType type() const override;
    virtual QJsonObject toJsonObject() const override;
    virtual bool isValid() const override;
};

///
/// \brief The InteractionProtocolCassyEvent struct событие от кассы
///
struct INTERACTION_PROTOCOL_API InteractionProtocolCassyEvent: public IJsonable {
    InteractionProtocolCassyEvent();
    InteractionProtocolCassyEvent(const InteractionProtocolCassyEvent &obj);
    InteractionProtocolCassyEvent &operator =(const InteractionProtocolCassyEvent &obj);
    InteractionProtocolCassyEvent(const QJsonObject &json);

    QUuid mCassyUuid = QUuid();                 ///< uid кассы
    InteractionProtocolCashControlService::EEventType mEventType = InteractionProtocolCashControlService::EEventType::None;   ///< Тип события
    QDateTime mDate = QDateTime();              ///< дата события
    QString mMessage= "";                       ///< сообщение для вывода в тирователь
    QColor mForeColor = Qt::black;              ///< цвет текста (RGB)
    QColor mBackColor = Qt::white;              ///< цвет фона (RGB)

protected:
    void selfCopy(const InteractionProtocolCassyEvent &obj);

    // IJsonable interface
public:
    virtual EDataType type() const override;
    virtual QJsonObject toJsonObject() const override;
    virtual bool isValid() const override;
};

Q_DECLARE_METATYPE(InteractionProtocolCassyEvent)

///
/// \brief The InteractionProtocolHeartbeat struct Heartbeat-сообщение (1 раз в 1 мин отправляется)
/// его просто игнорировать
///
struct INTERACTION_PROTOCOL_API InteractionProtocolHeartbeat: public IJsonable {
    InteractionProtocolHeartbeat();
    InteractionProtocolHeartbeat(const InteractionProtocolHeartbeat &obj);
    InteractionProtocolHeartbeat &operator =(const InteractionProtocolHeartbeat &obj);
    InteractionProtocolHeartbeat(const QJsonObject &json);

protected:
    void selfCopy(const InteractionProtocolHeartbeat &obj);

    // IJsonable interface
public:
    virtual EDataType type() const override;
    virtual QJsonObject toJsonObject() const override;
    virtual bool isValid() const override;
};

#endif // INTERACTIONPROTOCOLEVENTS_H
