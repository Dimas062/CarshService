#ifndef NETWORKPARSERMACHINE_H
#define NETWORKPARSERMACHINE_H

#include "interactionprotocollib.h"
#include "interactionprotocol.h"

#include <QObject>
#include <QVector>
#include <QTcpSocket>

///
/// \brief The NetworkParserMachine class парсер сетевый сообщений NetworkMessage из входного потока данных
///
class INTERACTION_PROTOCOL_API NetworkParserMachine
{
public:
    NetworkParserMachine();
    ///
    /// \brief step очередной шаг разбора
    /// \param data входные данные из потока
    /// \return сетевые сообщения
    ///
    QVector<NetworkMessage> step(const QByteArray& data);
    ///
    /// \brief reset сброс парсера
    ///
    void reset();
private:
    NetworkParserMachine(NetworkParserMachine const&) = delete;
    NetworkParserMachine& operator= (NetworkParserMachine const&) = delete;
private:
    QByteArray mPrevData;   ///< накопленные данные
};

/** @code

  NetworkParserMachine parser;

  //...

  void onReadyRead() {
    QTcpSocket* socket = static_cast<QTcpSocket*>(sender());
    QVector<NetworkMessage> messages = parser.step(socketRecv->readAll());
    //... // работа с командами
  }

 **/

#endif // NETWORKPARSERMACHINE_H
