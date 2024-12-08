#include "networkparsermachine.h"

#include <QDataStream>

#define NETWORK_HEADER_SIZE (4+4+4)

NetworkParserMachine::NetworkParserMachine()
{
}

QVector<NetworkMessage> NetworkParserMachine::step(const QByteArray &data)
{
    QByteArray currentData;// текущие данные
    // учёт предыдущих данных (на предыдущем шаге)
    if (!mPrevData.isEmpty()) {
        currentData = mPrevData.append(data);
    } else {
        currentData = data;
    }
    QVector<NetworkMessage> messages; // список разобранных сообщений
    // Цикл разбора сообщения
    while(currentData.length() > 0) { // пока есть что обрабатывать
        if (currentData.length() < NETWORK_HEADER_SIZE) { // если предположительно нет заголовка - разбирать нечего!          
            break;
        } else { // Предположительно, заголовок есть - начинаем разбирать сообщение!
            bool isSynchronization = false;
            {
                QDataStream stream(&currentData, QIODevice::ReadOnly);  // Поток чтения данных из сообщения
                quint32 synchroSequence;
                quint32 id;
                quint32 len;
                stream >> synchroSequence;
                stream >> id;
                stream >> len;
                int lenData = len;
                if (synchroSequence == NetworkMessage::cSyncroSequence) { // данные корректны
                    if (currentData.length() >= lenData) { // если команда пришла полностью
                        try {
                            char* data = new char [lenData];
                            stream.readRawData(data, lenData);
                            NetworkMessage message(static_cast<EDataType>(id), QByteArray(data, lenData));
                            delete[] data;
                            currentData = currentData.remove(0, len + NETWORK_HEADER_SIZE);
                            messages.append(message);
                        }  catch (...) {
                            qDebug("***** ***** NetworkParserMachine::step - exeption");
                            isSynchronization = true;
                        }
                    } else { // поле "Данные" - пришло НЕ полностью - обработать на данном шаге НЕВОЗМОЖНО!
                        break;
                    }
                } else { // пришла хрень - надо выравниваться по синхропоследовательности
                    qDebug("***** ***** NetworkParserMachine::step - bad cSyncroSequence");
                    isSynchronization = true;
                }
            }
            if (isSynchronization) {
                qDebug("***** ***** NetworkParserMachine::step - isSynchronization = true");
                isSynchronization = false;
                mPrevData.clear();
                auto indexOfSyncroSequence = [](QByteArray& data)->int {
                    for (auto index=0; index<data.length()-4; index++) {
                        auto value = *((quint32*)data.constData());
                        if (value == NetworkMessage::cSyncroSequence) {
                            return index;
                        }
                    }
                    return -1;
                };
                auto index = indexOfSyncroSequence(currentData);
                if (index != -1) {
                    currentData = currentData.remove(0, index);
                    qDebug("***** ***** NetworkParserMachine::step - indexOfSyncroSequence");
                }
                qDebug("***** ***** NetworkParserMachine::step - end isSynchronization = false");
                currentData.clear();
            }
        }
    }
    mPrevData = currentData;
    return messages;
}

void NetworkParserMachine::reset()
{
    mPrevData.clear();
}
