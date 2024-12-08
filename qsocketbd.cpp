#include "qsocketbd.h"
#include <QByteArray>
#include <QSplashScreen>


QSocketBD::QSocketBD(QObject *parent)
    : QObject{parent}
{
    m_bIsConnected = false;

    QMetaObject::invokeMethod(&QSocketBDNetClient::getInstance() , "connectToHost");

}



QList<QStringList> QSocketBD::execMainBDQuery(QString query)
{

    QByteArray data = QString(query).toLocal8Bit();

    //pServSocket->writeData(data);
    QTimer timer;
    timer.setSingleShot(true);
    QEventLoop loop;



    connect((&(QSocketBDNetClient::getInstance())), SIGNAL(dataReceived()), &loop, SLOT(quit()));

    connect(&timer, SIGNAL(timeout()), &loop, SLOT(quit()));

    QMetaObject::invokeMethod(&QSocketBDNetClient::getInstance() , "writeData" , Q_ARG(QByteArray , data));

    timer.start(9000);

    loop.exec(); //blocks untill either theSignalToWaitFor or timeout was fired

    QList<QStringList> retVal;

    if(timer.isActive())
        qDebug("dataReceived");
    else
    {
        qDebug("timeout");
        return retVal;
    }


    QString ResultData = QString::fromLocal8Bit(QSocketBDNetClient::getInstance().m_LastData);

    //qDebug()<<"ResultData="<<ResultData;

    /*Нулевой результат*/
    if(ResultData == "##**NULLRESULT**##")
    {
        return retVal;
    }

    QStringList RowsList = ResultData.split("**--##ROW**--##");

    RowsList.removeLast();




    QString strRow;

    foreach (strRow, RowsList) {
        QStringList ColsList = strRow.split("##--**COL##--**");
        ColsList.removeLast();
        retVal.append(ColsList);
    }

    //splash.finish();
    return retVal;
}

int QSocketBD::execMainBDQueryUpdate(QString query)
{

    // QByteArray data = QString(query).toLocal8Bit();

    // QMetaObject::invokeMethod(&QSocketBDNetClient::getInstance() , "writeData" , Q_ARG(QByteArray , data));

    execMainBDQuery(query);

    return 1;
}

