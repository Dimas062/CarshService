#ifndef QSOCKETBD_H
#define QSOCKETBD_H

#include <QObject>
#include "qsocketbdnetclient.h"

class QSocketBD : public QObject
{
    Q_OBJECT
public:
    explicit QSocketBD(QObject *parent = nullptr);

    QList<QStringList> execMainBDQuery(QString query);
    int execMainBDQueryUpdate(QString query);

    bool m_bIsConnected;


public slots:


signals:
};

#endif // QSOCKETBD_H
