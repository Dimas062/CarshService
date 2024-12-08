#ifndef INTERACTIONPROTOCOLCASHCONTROLSERVICE_H
#define INTERACTIONPROTOCOLCASHCONTROLSERVICE_H

#include <QObject>
#include <QByteArray>
#include <QUuid>
#include <QByteArray>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonDocument>
#include <QVariant>
#include <QVector>
#include <QPointF>
#include <QMap>
#include <QDateTime>
#include <QJsonParseError>
#include <QColor>
#include "interactionprotocollib.h"
#include "servicemacros.h"

namespace InteractionProtocolCashControlService {

///
/// \brief The Type enum типы сообщений
///
enum class Type {
    None = 0,
    Receipt = 1,        ///< сообщение-квитанция (ответ на сообщение)
    Ping = 2,           ///< сообщение пинг
    Config = 3,         ///< сообщение конфигурация
    Event = 4,          ///< сообщение событие от кассы
    CassyFilter = 5,    ///< сообщение фильтр событий от кассы
    CleanHandsEvent = 6 ///< cообщение - событие плагина ЧР
};

///
/// \brief The JsonStringParserMachine class парсер нуль-терминальных UTF-8 строк в формате JSON
///
class INTERACTION_PROTOCOL_API JsonStringParserMachine
{
public:
    JsonStringParserMachine() {}
    ///
    /// \brief step очередной шаг разбора
    /// \param data входные данные из потока
    /// \return JsonString сообщения
    ///
    QVector<QString> step(const QByteArray& data);
    ///
    /// \brief reset сброс парсера
    ///
    void reset();
private:
    QByteArray mPrevData;   ///< накопленные данные
};

///
/// \brief The IJsonStringable struct интерфейс сериализации и десериализации в нуль-терминальную UTF-8 строку в формате JSON
///
struct INTERACTION_PROTOCOL_API IJsonStringable {
    virtual QByteArray toJsonString() const = 0;
    virtual void fromJsonString(const QString& text) = 0;
protected:
    QByteArray fromJsonObject(const QJsonObject & object) const;
    QJsonObject toJsobObject(const QString &text, const Type& type) const;
    QJsonObject toJsobObject(const QString &text) const;
};

///
/// \brief The HeaderMessage struct заголовок любого сообщения
///
struct INTERACTION_PROTOCOL_API HeaderMessage : public IJsonStringable {
    HeaderMessage():IJsonStringable(){}
    HeaderMessage(const HeaderMessage &obj) { selfCopy(obj); }
    HeaderMessage &operator =(const HeaderMessage &obj) { OPERATOR_EQUAL_BODY; }
    Type mType = Type::None;
    QUuid mUidMessage = QUuid();
protected:
    void selfCopy(const HeaderMessage &obj) {
        mType = obj.mType;
        mUidMessage = obj.mUidMessage;
    }
    // IJsonStringable interface
public:
    virtual QByteArray toJsonString() const override;
    virtual void fromJsonString(const QString &text) override;
};

///
/// \brief The ReceiptMessage struct сообщение-квитанция
///
struct INTERACTION_PROTOCOL_API ReceiptMessage : public IJsonStringable {
    ReceiptMessage():IJsonStringable(){}
    ReceiptMessage(const ReceiptMessage &obj) { selfCopy(obj); }
    ReceiptMessage &operator =(const ReceiptMessage &obj) { OPERATOR_EQUAL_BODY; }
    const Type mType = Type::Receipt;
    QUuid mUidMessage = QUuid();
    Type mTypeMessage = Type::None;
protected:
    void selfCopy(const ReceiptMessage &obj) {
        mUidMessage = obj.mUidMessage;
        mTypeMessage = obj.mTypeMessage;
    }

    // IJsonStringable interface
public:
    virtual QByteArray toJsonString() const override;
    virtual void fromJsonString(const QString &text) override;
};

///
/// \brief The PingMessage struct пинг
///
struct INTERACTION_PROTOCOL_API PingMessage : public IJsonStringable {
    PingMessage():IJsonStringable(){}
    PingMessage(const PingMessage &obj) { selfCopy(obj); }
    PingMessage &operator =(const PingMessage &obj) { OPERATOR_EQUAL_BODY; }
    const Type mType = Type::Ping;
    QUuid mUidMessage = QUuid();
protected:
    void selfCopy(const PingMessage &obj) {
        mUidMessage = obj.mUidMessage;
    }

    // IJsonStringable interface
public:
    virtual QByteArray toJsonString() const override;
    virtual void fromJsonString(const QString &text) override;
};

///
/// \brief The ConfigMessage struct конфигурация СКК
///
struct INTERACTION_PROTOCOL_API ConfigMessage : public IJsonStringable {
    ConfigMessage():IJsonStringable(){}
    ConfigMessage(const ConfigMessage &obj) { selfCopy(obj); }
    ConfigMessage &operator =(const ConfigMessage &obj) { OPERATOR_EQUAL_BODY; }
    const Type mType = Type::Config;
    QString mConnString= "";    ///< строка подключения к БД "Host=localhost;Username=postgres;Password=12345;Database=posdb"
    QString mLanguage= "";      ///< язык ("ru-RU", "en-US")
    struct {
        int mCashCnt=0;          ///< информация о лицензии (кол-во касс)
        int mRelayCnt=0;         ///< информация о лицензии (кол-во реле)
        bool mCentralServer=true;
        bool mAccessCS=true;
    } mLicense;
    struct {
        QString mID;
        QString mName;
        QString mAddress;

        QString mDistributor;
        QString mRegion;
        QString mDivision;
        QString mCluster;
        QString mCity;
    } mObjInfo;

protected:
    void selfCopy(const ConfigMessage &obj) {
        mConnString = obj.mConnString;
        mLicense = obj.mLicense;
        mLanguage = obj.mLanguage;
        mObjInfo = obj.mObjInfo;
    }

    // IJsonStringable interface
public:
    virtual QByteArray toJsonString() const override;
    virtual void fromJsonString(const QString &text) override;
};

enum class EEventType {
    None = 0,
    Transaction = 1,    ///< операция по чеку
    Violation = 2       ///< тревожное событие по кассе
};

///
/// \brief The EventMessage struct событие от кассы
///
struct INTERACTION_PROTOCOL_API EventMessage : public IJsonStringable {
    EventMessage():IJsonStringable(){}
    EventMessage(const EventMessage &obj) { selfCopy(obj); }
    EventMessage &operator =(const EventMessage &obj) { OPERATOR_EQUAL_BODY; }
    const Type mType = Type::Event;
    EEventType mEventType = EEventType::None;   ///< Тип события
    QUuid mID = QUuid();                        ///< идентификатор записи в БД
    QDateTime mDate = QDateTime();              ///< дата события
    QUuid mCashNo = QUuid();                    ///< uid кассы
    QString mMessage= "";                       ///< сообщение для вывода в тирователь
    QColor mForeColor = Qt::black;              ///< цвет текста (RGB)
    QColor mBackColor = Qt::white;              ///< цвет фона (RGB)

protected:
    void selfCopy(const EventMessage &obj) {
        mEventType = obj.mEventType;
        mID = obj.mID;
        mDate = obj.mDate;
        mCashNo = obj.mCashNo;
        mMessage = obj.mMessage;
        mForeColor = obj.mForeColor;
        mBackColor = obj.mBackColor;
    }

    // IJsonStringable interface
public:
    virtual QByteArray toJsonString() const override;
    virtual void fromJsonString(const QString &text) override;
};

///
/// \brief The CassyFilterMessage struct управление фильтром событий по кассе
///
struct INTERACTION_PROTOCOL_API CassyFilterMessage : public IJsonStringable {
    CassyFilterMessage():IJsonStringable(){}
    CassyFilterMessage(const CassyFilterMessage &obj) { selfCopy(obj); }
    CassyFilterMessage &operator =(const CassyFilterMessage &obj) { OPERATOR_EQUAL_BODY; }
    const Type mType = Type::CassyFilter;
    QUuid mUidMessage = QUuid();
    QUuid mUidCash = QUuid();                   ///< uid кассы
    bool mPermissionCashTransaction = false;    /// разрешение отправки событий от СКК по заданной кассе
protected:
    void selfCopy(const CassyFilterMessage &obj) {
        mUidMessage = obj.mUidMessage;
        mUidCash = obj.mUidCash;
        mPermissionCashTransaction = obj.mPermissionCashTransaction;
    }

    // IJsonStringable interface
public:
    virtual QByteArray toJsonString() const override;
    virtual void fromJsonString(const QString &text) override;
};

///
/// \brief The CleanHandsEventMessage struct событие от кассы
///
struct INTERACTION_PROTOCOL_API CleanHandsEventMessage : public IJsonStringable {
    CleanHandsEventMessage():IJsonStringable(){}
    CleanHandsEventMessage(const CleanHandsEventMessage &obj) { selfCopy(obj); }
    CleanHandsEventMessage &operator =(const CleanHandsEventMessage &obj) { OPERATOR_EQUAL_BODY; }
    const Type mType = Type::CleanHandsEvent;
    QUuid mUidMessage = QUuid();
    int mCashNum = 0;                           ///< код кассы
    QDateTime mDate = QDateTime();              ///< дата события

protected:
    void selfCopy(const CleanHandsEventMessage &obj) {
        mUidMessage = obj.mUidMessage;
        mDate = obj.mDate;
        mCashNum = obj.mCashNum;
    }

    // IJsonStringable interface
public:
    virtual QByteArray toJsonString() const override;
    virtual void fromJsonString(const QString &text) override;
};

}


#endif // INTERACTIONPROTOCOLCASHCONTROLSERVICE_H
