#include <QApplication>
#include <QSql>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QStandardPaths>
#include <QSqlError>
#include "qcarshserviceapplication.h"
#include <QDebug>
#include <QFontDatabase>
#include <QFile>
#include <QDirIterator>
#include "common.h"
#include "qcarshservicebasewidget.h"

#ifdef Q_OS_ANDROID
#include <QJniObject>
#include <QJniEnvironment>
#include <QtCore/private/qandroidextras_p.h>
#endif

#include <QCoreApplication>
#include <qpa/qplatformnativeinterface.h>
#include <QGuiApplication>
#include <private/qobject_p.h>

#ifdef Q_OS_IOS
#include <QtCore/QtPlugin>

#endif

QSqlDatabase ClientDb;
QSqlDatabase ServerDb;

QString sStandartStoragePath;

#ifdef Q_OS_ANDROID
QJniObject* pActivity;
#endif

VSMobileSettings settings;

QCarshServiceBaseWidget * pCarshServiceBaseWidget;

extern QColor defaultBackColor;

/*Закрытие базы данных */
void closeLocalDataBase()
{
    ClientDb.close();
}

/*Открытие базы данных*/
bool openLocalDataBase()
{
    /* База данных открывается по заданному пути и имени базы данных, если она существует, если не существует, то копируется шаблон из ресурсов*/
    QFile DbFile;
    QString DatabaseDataStoragePath = sStandartStoragePath;

    /*Проверям на существование*/
    if(!QFile(DatabaseDataStoragePath +"/data.db").exists())
    {
        QFile(":/data.db").copy(DatabaseDataStoragePath +"/data.db");
    }

    DbFile.setFileName(DatabaseDataStoragePath +"/data.db");
    QFile::setPermissions(DatabaseDataStoragePath + "/data.db", QFile::WriteOwner | QFile::ReadOwner);

    /*Открываем базу*/
    ClientDb = QSqlDatabase::addDatabase("QSQLITE");

    ClientDb.setDatabaseName(DatabaseDataStoragePath + "/data.db");

    if(ClientDb.open()){

    } else {
        QSqlError err = ClientDb.lastError();
        qDebug()<<"BD not opened, err is "<<err;
        return false;
    }

    return true;
}

bool readSettingsFromBD()
{

    QString strQueryExec;
    QSqlQuery query(ClientDb);

    strQueryExec = QString("select Value from Settings where Name='Host'");


    if(query.exec(strQueryExec))
    {
       while(query.next())
        {
            settings.strServAdress = query.value(0).toString();
        }
    }

    strQueryExec = QString("select Value from Settings where Name='Password'");
    if(query.exec(strQueryExec))
    {
        while(query.next())
        {
            settings.strServPassword = query.value(0).toString();
        }
    }

    strQueryExec = QString("select Value from Settings where Name='Login'");
    if(query.exec(strQueryExec))
    {
        while(query.next())
        {
            settings.strServLogin = query.value(0).toString();
        }
    }

    return true;
}




int main(int argc, char *argv[])
{
    QCarshServiceApplication a(argc, argv);

    defaultBackColor= QColor(253,254,254);//см. :/Diplaytap.qss

#ifdef Q_OS_ANDROID
    sStandartStoragePath = QStandardPaths::writableLocation(QStandardPaths::StandardLocation::AppDataLocation);
#endif

#if defined Q_OS_IOS || defined Q_OS_WINDOWS
    sStandartStoragePath = QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation);
#endif
 //   checkPermission();


#ifdef Q_OS_ANDROID
    /*Активация "джавы"*/
    QPlatformNativeInterface* interface = QGuiApplication::platformNativeInterface();
    jobject activity = (jobject)interface->nativeResourceForIntegration("QtActivity");

    if (activity)
    {
        pActivity = new QJniObject(activity);
    }
#endif


    /*Установка стартового стиля (может позже сделаю настраиваемым)*/
    QFile styleFile(":/Diplaytap.qss");
    styleFile.open( QFile::ReadOnly );
    QString style( styleFile.readAll() );
    a.setStyleSheet( style );

    openLocalDataBase();
    readSettingsFromBD();

    OpenServerBD();


    QCarshServiceBaseWidget w;
    pCarshServiceBaseWidget = &w;
    w.show();



    int retVal = a.exec();

    closeLocalDataBase();


#ifdef Q_OS_ANDROID
    /*Закрытие серверной БД*/
    pActivity->callMethod<jint>("CloseServerBD", "()I");
#endif

    return retVal;
}
