#ifndef COMMON_H
#define COMMON_H

#include <QtGlobal>

#if defined Q_OS_BLACKBERRY || defined Q_OS_ANDROID || defined Q_OS_IOS || defined Q_OS_WP
#define Q_OS_MOBILE
#else
#define Q_OS_DESKTOP
#endif

#include <QTime>
#include <QString>
#include <QList>
#include <QLineEdit>
#include <QLabel>
#include <QImage>
#include <QIcon>
#include <QSqlQuery>

const int _24H = 24*60*60*1000;
const int _12H = 12*60*60*1000;
const int _6H  = 6*60*60*1000;
const int _2H  = 2*60*60*1000;
const int _1H  = 1*60*60*1000;
const int _30M  = 30*60*1000;
const int _15M  = 15*60*1000;
const int _5M  = 5*60*1000;

#define DIALOG_RET_GOTO_ARCHIVE 2
#define DIALOG_RET_GOTO_ONLINE 3

enum class PhotoTypes {DriverCard,    //Права
                 Passport,      //Паспорт
                 FLSert         //Свидетельство о ИП или самозанятости
                 };

enum     UserTypes {    Emploee,         //Сотрудник
                        CarshService,    //Карш-сервис
                        Carsh,           //Карш-служба
                        PartnerWasher,   //Партнёр мойка
                        PartnerPlate,    //Партнер номера
                        PartnerStick,    //Партнер оклейка
                        UndefinedUserType
};

enum PayTypes {
    Card,
    Business,
    NoPay,
    Undefined = -1
};



struct VSMobileSettings
{
    QString strServAdress;
    QString strServLogin;
    QString strServPassword;
    bool isConnected;//Удалось подключиться
};

QString bool_to_str(bool b);

bool executeQueryWithReconnect(QSqlQuery &query, const QString &queryString);

QString GenNextShcetActNumber();


QString rublesForNumber(long long number);

QString GenNextShcetActNumber();

void Logging(QString str , int iWarning = 1);

bool IsUUidInVector(QVector<QUuid> , QUuid);

QIcon IconByNumber(int iNumb);

bool CheckLineEditLenSetLabel(QLineEdit * pLineEdit , QLabel * pLabel);//Проверяет длинну текста в едите, если меньше 3х, то красит лейбл в красный и возвращает ложь

int IsCameraPrenissionAndRequest();

QString CreateDateBDPeriodFromNow(QString strBdDateField , int iDays);

QString PictureFileToBase64(QString strPath);

QImage Base64ToImage(QString & base64Str);

QString ImageToBase64(const QImage & img);

QString ListToString(QList<QString> list);

QString ListListToString(QList<QStringList> list);

QList<QStringList> execMainBDQuery(QString query);

int execMainBDQueryUpdate(QString query);


void debug_TimeStamp(QString pred =  "");

template<typename EnumType>
QString EnumToString(const EnumType& enumValue);


bool SendToWhatsapp2(QString text , QVector<QString> picturesPaths);

bool SendToTelegram2(QString text , QVector<QString> picturesPaths);

bool SendToWhatsapp(QString text);

bool SendToTelegram(QString text);

bool IsAlarmPrenission();

int IsAlarmPrenissionAndRequest();

int IsCameraPrenissionAndRequest();

bool SetAlarmClock(QString strText , int iNotifiId , long iTimeSec);

bool CancelAlarm(int iNotifiId);


bool OpenServerBD();

QString month(int num);


#endif // COMMON_H
