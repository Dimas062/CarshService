#ifndef INTERACTIONPROTOCOLBACKUPSERVICE_H
#define INTERACTIONPROTOCOLBACKUPSERVICE_H

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
#include "interfaces.h"

namespace InteractionProtocolBackupService {

/// типы сообщений
enum class Type {
    None = 0,

    GetBackupList = 1,     ///< получить список бэкапов
    CreateBackup = 2, ///< создать бэкап
    ApplyBackup = 3 ///< применить бэкап
};


/// парсер нуль-терминальных UTF-8 строк в формате JSON
class INTERACTION_PROTOCOL_API JsonStringParserMachine
{
public:
    JsonStringParserMachine() {}

    /**
     * @brief step очередной шаг разбора
     * @param data входные данные из потока
     * @return JsonString сообщения
     */
    QVector<QString> step(const QByteArray& data);

    /// сброс парсера
    void reset();

private:
    QByteArray mPrevData;   ///< накопленные данные
};


/// интерфейс сериализации и десериализации в нуль-терминальную UTF-8 строку в формате JSON
//struct INTERACTION_PROTOCOL_API IJsonable {
//    virtual QJsonObject toJsonObject() const = 0;
//    virtual void fromJsonString(const QString& text) = 0;
//protected:
//    QByteArray fromJsonObject(const QJsonObject & object) const;
//    QJsonObject toJsobObject(const QString &text, const Type& type) const;
//    QJsonObject toJsobObject(const QString &text) const;
//};

/// заголовок любого сообщения
struct INTERACTION_PROTOCOL_API HeaderMessage : public IJsonable, public ICommonFields {
    HeaderMessage():IJsonable(){}
    HeaderMessage(const HeaderMessage &obj) { selfCopy(obj); }
    HeaderMessage &operator =(const HeaderMessage &obj) { OPERATOR_EQUAL_BODY; }
    //Type mType = Type::None;
    EDataType mType = EDataType::None;
    QUuid mUidMessage = QUuid();
protected:
    void selfCopy(const HeaderMessage &obj) {
        mType = obj.mType;
        mUidMessage = obj.mUidMessage;
    }
    // IJsonable interface
public:
    virtual QJsonObject toJsonObject() const override;
    virtual QByteArray fromJsonObject(const QJsonObject &object) ;
};


/// получить список бэкапов
struct INTERACTION_PROTOCOL_API ReadListMessage
        : public IJsonable, public ICommonFields
{
    ReadListMessage():IJsonable(){}
    ReadListMessage(const ReadListMessage &obj) { selfCopy(obj); }
    ReadListMessage(const QJsonObject &jsObj);

    ReadListMessage &operator =(const ReadListMessage &obj) { OPERATOR_EQUAL_BODY; }
    const EDataType mType = EDataType::RequestBackupList;

    //const Type mType = Type::GetBackupList;
    QUuid mUidMessage = QUuid();

    /// Элемент списка бэкапов
    struct BackupProperties
    {
        QDateTime date;    ///< Дата, когда был сделан бэкап
        QString fileName;  ///< Название файла бэкапа
    };

    QString mBackupPath;  ///< Путь к файлам бэкапа
    QVector<BackupProperties> mBackupList;

protected:
    void selfCopy(const ReadListMessage &obj) {
        mBackupList = obj.mBackupList;
        mUidMessage = obj.mUidMessage;
    }

    // IJsonable interface
public:
    virtual EDataType type() const override;
    virtual QJsonObject toJsonObject() const override;
    virtual QByteArray fromJsonObject(const QJsonObject &object);
    virtual bool isValid() const override;
};



/// создать бэкап
struct INTERACTION_PROTOCOL_API RequestCreateBackup
        : public IJsonable, public ICommonFields
{
    RequestCreateBackup() : IJsonable() {}
    RequestCreateBackup(const RequestCreateBackup &obj) { selfCopy(obj); }
    RequestCreateBackup(const QJsonObject &jsObj);

    RequestCreateBackup &operator =(const RequestCreateBackup &obj) { OPERATOR_EQUAL_BODY; }
    const EDataType mType = EDataType::RequestCreateBackup;

    QUuid mUidMessage = QUuid();
    QString mStrPath="";

protected:
    void selfCopy(const RequestCreateBackup &obj) {
        mUidMessage = obj.mUidMessage;
        mStrPath = obj.mStrPath;
    }

    // IJsonable interface
public:
    virtual EDataType type() const override;
    virtual QJsonObject toJsonObject() const override;
    virtual bool isValid() const override;
};

/// проверить состояние бэкапа
struct INTERACTION_PROTOCOL_API RequestStateBackup
        : public IJsonable, public ICommonFields
{
    RequestStateBackup() : IJsonable() {}
    RequestStateBackup(const RequestStateBackup &obj) { selfCopy(obj); }
    RequestStateBackup(const QJsonObject &jsObj);

    RequestStateBackup &operator =(const RequestStateBackup &obj) { OPERATOR_EQUAL_BODY; }
    const EDataType mType = EDataType::RequestStateBackup;

    QUuid mUidMessage = QUuid();
    bool mStatusBackup=false;
    bool mStatusRestore=false;
    int mProgress=-1;

protected:
    void selfCopy(const RequestStateBackup &obj) {
        mUidMessage = obj.mUidMessage;
        mStatusBackup = obj.mStatusBackup;
        mStatusRestore = obj.mStatusRestore;
        mProgress = obj.mProgress;
    }

    // IJsonable interface
public:
    virtual EDataType type() const override;
    virtual QJsonObject toJsonObject() const override;
    virtual bool isValid() const override;
};
struct INTERACTION_PROTOCOL_API ResponseStateBackup
        : public IJsonable, public ICommonFields, public IResponseResultable
{
    ResponseStateBackup() : IJsonable(), ICommonFields(), IResponseResultable() {}
    ResponseStateBackup(const ResponseStateBackup &obj) { selfCopy(obj); }
    ResponseStateBackup(const QJsonObject &json);
    ResponseStateBackup &operator =(const ResponseStateBackup &obj) { OPERATOR_EQUAL_BODY; }
    QUuid mUidMessage = QUuid();
    bool mStatusBackup=false;
    bool mStatusRestore=false;
    int mProgress=-1;

protected:
    void selfCopy(const ResponseStateBackup &obj) {
        mUidMessage = obj.mUidMessage;
        mStatusBackup = obj.mStatusBackup;
        mStatusRestore = obj.mStatusRestore;
        mProgress = obj.mProgress;
    }

    // IJsonable interface
public:
    virtual EDataType type() const override;
    virtual QJsonObject toJsonObject() const override;
    virtual bool isValid() const override;
};

//процесс создания бэкапа
struct INTERACTION_PROTOCOL_API ResponseCreateBackup
        : public IJsonable, public ICommonFields, public IResponseResultable
{
    ResponseCreateBackup() : IJsonable(), ICommonFields(), IResponseResultable() {}
    ResponseCreateBackup(const ResponseCreateBackup &obj) { selfCopy(obj); }
    ResponseCreateBackup(const QJsonObject &json);
    ResponseCreateBackup &operator =(const ResponseCreateBackup &obj) { OPERATOR_EQUAL_BODY; }
    QUuid mUidMessage = QUuid();
    QString mStrPath="";
    bool mLaunchedBackup=false;
    bool mLaunchedRestor=false;
    int mProgress=-1;

protected:
    void selfCopy(const ResponseCreateBackup &obj) {
        mUidMessage = obj.mUidMessage;
        mStrPath = obj.mStrPath;
        mLaunchedBackup = obj.mLaunchedBackup;
        mLaunchedRestor = obj.mLaunchedRestor;
        mProgress = obj.mProgress;
    }

    // IJsonable interface
public:
    virtual EDataType type() const override;
    virtual QJsonObject toJsonObject() const override;
    virtual bool isValid() const override;
};

/// применить бэкап
struct INTERACTION_PROTOCOL_API RequestApplyBackup
        : public IJsonable, public ICommonFields
{
    RequestApplyBackup() : IJsonable() {}
    RequestApplyBackup(const RequestApplyBackup &obj) { selfCopy(obj); }
    RequestApplyBackup(const QJsonObject &object);

    RequestApplyBackup &operator =(const RequestApplyBackup &obj) { OPERATOR_EQUAL_BODY; }
    const EDataType mType = EDataType::RequestApplyBackup;

    QUuid mUidMessage = QUuid();
    QString mStrPath="";

protected:
    void selfCopy(const RequestApplyBackup &obj) {
        mUidMessage = obj.mUidMessage;
        mStrPath = obj.mStrPath;
    }

    // IJsonable interface
public:
    virtual EDataType type() const override;
    virtual QJsonObject toJsonObject() const override;
    virtual bool isValid() const override;
};

//процесс применения бэкапа
struct INTERACTION_PROTOCOL_API ResponseApplyBackup
        : public IJsonable, public ICommonFields, public IResponseResultable
{
    ResponseApplyBackup() : IJsonable(), ICommonFields(), IResponseResultable() {}
    ResponseApplyBackup(const ResponseApplyBackup &obj) { selfCopy(obj); }
    ResponseApplyBackup(const QJsonObject &json);

    ResponseApplyBackup &operator =(const ResponseApplyBackup &obj) { OPERATOR_EQUAL_BODY; }
    QUuid mUidMessage = QUuid();
    QString mStrPath="";
    bool mLaunchedBackup=false;
    bool mLaunchedRestor=false;
    int mProgress=-1;

protected:
    void selfCopy(const ResponseApplyBackup &obj) {
        mUidMessage = obj.mUidMessage;
        mStrPath = obj.mStrPath;
        mLaunchedBackup = obj.mLaunchedBackup;
        mLaunchedRestor = obj.mLaunchedRestor;
        mProgress = obj.mProgress;
    }

    // IJsonable interface
public:
    virtual EDataType type() const override;
    virtual QJsonObject toJsonObject() const override;
    virtual bool isValid() const override;
};

}


#endif // INTERACTIONPROTOCOLBACKUPSERVICE_H
