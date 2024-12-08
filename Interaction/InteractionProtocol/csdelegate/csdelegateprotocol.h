#ifndef CSDELEGATEPROTOCOL_H
#define CSDELEGATEPROTOCOL_H

#include <QObject>
#include <QUuid>
#include <QByteArray>
#include <QDataStream>
#include <QDateTime>
#include <QMap>
#include "interactionprotocollib.h"

namespace CsDelegateProtocol {

const int Port = 65003;

///
/// \brief The EMessageType enum типы сообщений логического уровня протокола сервера мониторинга
///
enum class EMessageType {
    None = 0,
    SendTelegramPhotoWithTextMessage    ///< сообщение - отправка фото+текст через тг цс делегата
};

/// \remark ТРАНСПОРТНЫЙ УРОВЕНЬ

///
/// \brief The Message class сообщение транспортного уровня протокола
///
class INTERACTION_PROTOCOL_API Message {
public:
    Message();
    Message(const Message &obj);
    Message &operator =(const Message &obj);
    void deserialize(const QByteArray& raw);    ///< десериализация
    void serialize(QByteArray& raw);            ///< сериализация

    int length() const;                 ///< получить размер сообщения
    const QUuid& uid() const;           ///< получить уид сообщения
    const QByteArray& payload() const;  ///< получить полезную нагрузка

    const EMessageType& type() const;   ///< получить тип сообщения

    static void registerMetatype();     ///< регистрация типов
    bool markBadVersionProtocol() const;
    ///
    /// \brief setPayload установить полезную нагрузку
    /// \param payload полезная нагрузка
    /// \return уникальный идентификатор запроса
    ///
    QUuid setPayload(const QByteArray& payload);
    ///
    /// \brief setUid установить уид сообщения
    /// \param uid уид сообщения
    ///
    void setUid(const QUuid& uid);
protected:
    void selfCopy(const Message &obj);
    EMessageType getType(const QByteArray& payload);
private:
    /// \remark ЗАГОЛОВОК
    int mLength = 0;        ///< размер сообщения
    QUuid mUid;             ///< уид сообщения
    const int cCurrentVersionProtocol = 0x01072024;
    bool mMarkBadVersionProtocol = false;
    /// \remark ПОЛЕЗНАЯ НАГРУЗКА
    QByteArray mPayload;    ///< полезная нагрузка
    EMessageType mType = EMessageType::None;    ///< тип сообщения
};

///
/// \brief The ParserMessageMachine class парсер сообщений
///
class INTERACTION_PROTOCOL_API ParserMessageMachine
{
public:
    ParserMessageMachine() {}
    QVector<CsDelegateProtocol::Message> step(const QByteArray& data);
    void reset();
private:
    QByteArray mPrevData;   ///< накопленные данные
};

/// \remark ЛОГИЧЕСКИЙ УРОВЕНЬ

///
/// \brief The LogicalMessage struct базовое сообщение логического уровня протокола
///
struct INTERACTION_PROTOCOL_API LogicalMessage {
    virtual EMessageType type() = 0;
    virtual void serialize(QByteArray& payload) = 0;
    virtual void deserialize(const QByteArray& payload) = 0;
protected:
    void readQUuid(QDataStream& rd, QUuid& uid);
    void writeQUuid(QDataStream& wr, const QUuid& uid);
};

///
/// \brief The SendTelegramPhotoWithTextMessage struct сообщение - отправка фото+текст через тг цс делегата
///
struct INTERACTION_PROTOCOL_API SendTelegramPhotoWithTextMessage : public LogicalMessage {
    SendTelegramPhotoWithTextMessage():LogicalMessage(){}
    SendTelegramPhotoWithTextMessage(const SendTelegramPhotoWithTextMessage &obj):LogicalMessage() { selfCopy(obj); }
    SendTelegramPhotoWithTextMessage &operator =(const SendTelegramPhotoWithTextMessage &obj) { if (this != &obj) { selfCopy(obj); } return *this; }
    virtual EMessageType type() { return EMessageType::SendTelegramPhotoWithTextMessage; }
    virtual void serialize(QByteArray& payload);
    virtual void deserialize(const QByteArray& payload);

    QString mTokenBot;
    QString mTokenChannel;
    QByteArray mImage;
    QString mText;

private:
    inline void selfCopy(const SendTelegramPhotoWithTextMessage &obj) {
        mTokenBot = obj.mTokenBot;
        mTokenChannel = obj.mTokenChannel;
        mImage = obj.mImage;
        mText = obj.mText;
    }
};

}

#endif // CSDELEGATEPROTOCOL_H
