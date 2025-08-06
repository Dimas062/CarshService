#include "qsocketbd.h"
#include <QByteArray>
#include <QSplashScreen>
#include <common.h>

QSocketBD::QSocketBD(QObject *parent)
    : QObject{parent}
{
    m_bIsConnected = false;

    QMetaObject::invokeMethod(&QSocketBDNetClient::getInstance() , "connectToHost");

}



QList<QStringList> QSocketBD::execMainBDQuery(QString query)
{

#ifdef Q_OS_WINDOWS
    QByteArray data = QString(query).toUtf8();
#else
    //debug_TimeStamp(" toLocal8Bit 1");
    QByteArray data = QString(query).toLocal8Bit();
    //debug_TimeStamp(" toLocal8Bit 2");
#endif
    
        
        //pServSocket->writeData(data);
        QTimer timer;
        timer.setSingleShot(true);
        QEventLoop loop;
        
        
        connect((&(QSocketBDNetClient::getInstance())), SIGNAL(dataReceived()), &loop, SLOT(quit()), Qt::QueuedConnection);
        
        connect(&timer, SIGNAL(timeout()), &loop, SLOT(quit()));
        
        
        QMetaObject::invokeMethod(&QSocketBDNetClient::getInstance() , "writeData" , Q_ARG(QByteArray , data));
        
        
        timer.start(60000);
        
        loop.exec(); //blocks untill either theSignalToWaitFor or timeout was fired
        
        QList<QStringList> retVal;
        
        if(!timer.isActive())
        {
            qDebug("timeout get data");
            return retVal;
        }
    
    QMutexLocker locker(&QSocketBDNetClient::getInstance().m_dataMutex);
#ifdef Q_OS_WINDOWS
    QString ResultData = QString::fromUtf8(QSocketBDNetClient::getInstance().m_LastData);
#else
    QString ResultData = QString::fromLocal8Bit(QSocketBDNetClient::getInstance().m_LastData);
#endif

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

