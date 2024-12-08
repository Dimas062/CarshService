#ifndef BDPATTERNS_H
#define BDPATTERNS_H

#include <QUuid>
#include "common.h"
#include <QImage>


QUuid CreatePayRecord(double dblSum , PayTypes iPayType);

void UpdatePayRecord(QUuid uuidPay , double dblSum , PayTypes iPayType);

QUuid CreatePayDocRecord(QUuid uuidPay , QString strImg);

void RemovePayDocs(QUuid uuidPay);

QUuid CreateTaskDocRecord(QUuid uuidTask , QString strImg , QUuid uuidType=QUuid("94ec977e-0be0-4dd7-b1fc-682af124e0ac"));

void RemoveTaskDocs(QUuid uuidTask);

QString StrFromUuid(QString strUuid , QString strTableName , QString strColName="Название");

#endif // BDPATTERNS_H
