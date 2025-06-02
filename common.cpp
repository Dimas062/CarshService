#include "common.h"
#include "qpa/qplatformnativeinterface.h"
#include <QCoreApplication>
#include <QFile>
#include <QGuiApplication>
#include <QString>
#include <QStringList>
#include <QRegularExpression>
#ifdef Q_OS_ANDROID
#include <QJniEnvironment>
#include <QJniObject>
#include <QtCore/private/qandroidextras_p.h>
#endif
#include <qpa/qplatformnativeinterface.h>
 #include <QSqlQuery>
 #include <QSqlDatabase>
 #include <QSqlError>
#include <QMetaEnum>
#include <QBuffer>
#include <QPixmap>
#include <QTcpSocket>
#include "qsocketbd.h"
#include <QImageReader>
#include <QUuid>

#include <pictures/qfullscreenpicdialog.h>

extern QSqlDatabase ClientDb;
#ifdef Q_OS_ANDROID
extern QJniObject* pActivity;
#endif
//#if defined Q_OS_IOS || defined Q_OS_WINDOWS
QSocketBD * serverBD;
//#endif

// Задаем максимально допустимые размеры изображений в системе
const int maxImgWidth = 2560;
const int maxImgHeight = 2560;

extern VSMobileSettings settings;//Сейчас шарится между двух потоков (интерекшнклиент и главный)
extern QUuid uuidCurrentUser;

void Logging(QString str , int iWarning)
{
    QString strExec = QString("insert into Лог(id , Пользователь, ДатаВремя, Текст, Критичность) values (uuid_generate_v4() , '%1' , '%2' ,'%3' , '%4')").arg(uuidCurrentUser.toString()).arg(QDateTime::currentSecsSinceEpoch()).arg(str).arg(iWarning);
    execMainBDQueryUpdate(strExec);
}

bool reconnectToDatabase(QSqlDatabase &db) {
    if (db.isOpen()) {
        db.close();
    }
    if (db.open()) {
        qDebug() << "Reconnected to the database successfully.";
        return true;
    } else {
        qDebug() << "Failed to reconnect to the database:" << db.lastError().text();
        return false;
    }
}

QString wrapText(const QString& text, int maxLineLength) {
    if (text.isEmpty() || maxLineLength <= 0) {
        return QString();
    }

    // Разделяем текст на слова, игнорируя множественные пробелы
    QStringList words = text.split(QRegularExpression("\\s+"), Qt::SkipEmptyParts);

    if (words.isEmpty()) {
        return QString();
    }

    QStringList lines;
    QString currentLine = words.first();

    for (int i = 1; i < words.size(); ++i) {
        const QString& word = words.at(i);
        QString potentialLine = currentLine + " " + word;

        // Проверяем, не превысит ли новая строка максимальную длину
        if (potentialLine.length() <= maxLineLength) {
            currentLine = potentialLine;
        } else {
            lines.append(currentLine);
            currentLine = word;
        }
    }

    lines.append(currentLine); // Добавляем последнюю строку
    return lines.join("\n");   // Объединяем строки через перенос
}

QStringList extractCarNumbers(const QString &text) {
    QStringList result;
    if (text.isEmpty())
        return result;

    // Приводим текст к верхнему регистру
    QString upperText = text.toUpper();
    QString cleaned;

    // Оставляем только цифры и кириллические буквы (А-Я)
    for (const QChar &c : upperText) {
        ushort unicode = c.unicode();
        if (c.isDigit() || (unicode >= 1040 && unicode <= 1071)) {
            cleaned.append(c);
        }
    }

    // Минимальная длина для номера
    const int PLATE_LENGTH = 9;
    if (cleaned.length() < PLATE_LENGTH)
        return result;

    // Проверяем все возможные подстроки длиной 9 символов
    for (int i = 0; i <= cleaned.length() - PLATE_LENGTH; ++i) {
        QStringView candidate = QStringView(cleaned).mid(i, PLATE_LENGTH);

        // Проверка шаблона: XDDDXXDDD
        if (!candidate[0].isLetter()) continue;

        bool valid = true;
        // Проверка трех цифр (позиции 1-3)
        for (int j = 1; j <= 3; j++) {
            if (!candidate[j].isDigit()) {
                valid = false;
                break;
            }
        }
        if (!valid) continue;

        // Проверка двух букв (позиции 4-5)
        for (int j = 4; j <= 5; j++) {
            if (!candidate[j].isLetter()) {
                valid = false;
                break;
            }
        }
        if (!valid) continue;

        // Проверка трех цифр (позиции 6-8)
        for (int j = 6; j <= 8; j++) {
            if (!candidate[j].isDigit()) {
                valid = false;
                break;
            }
        }
        if (!valid) continue;

        // Добавляем найденный номер
        result.append(candidate.toString());
    }

    return result;
}

bool executeQueryWithReconnect(QSqlQuery & query ,const QString &queryString) {
    if (!query.exec(queryString)) {
        QSqlError error = query.lastError();
        if (error.type() == QSqlError::ConnectionError) {
            // Попытка переподключения
            QSqlDatabase db = QSqlDatabase::database();
            if (reconnectToDatabase(db)) {
                // Повторное выполнение запроса после переподключения
                return query.exec(queryString);
            } else {
                qDebug() << "Failed to execute query after reconnection.";
                return false;
            }
        } else {
            qDebug() << "Query execution failed:" << error.text();
            return false;
        }
    }
    return true;
}

QString bool_to_str(bool b)
{
    if(b) return "true";
    else return "false";
}

QString GenNextShcetActNumber()
{
    QString strUuidMonth("f149f490-dae9-4171-a967-68644e952c12");
    QString strUuidNumber("e408ffca-c786-4009-b1a1-a270c9a0d925");
    QSqlQuery query;
    int iMonth = 0;
    int iNumber = 0;

    query.exec(QString("select Значение from Настройки where id='%1'").arg(strUuidMonth));
    while(query.next()) iMonth = query.value(0).toInt();

    query.exec(QString("select Значение from Настройки where id='%1'").arg(strUuidNumber));
    while(query.next()) iNumber = query.value(0).toInt();

    int iCurMonth = QDate::currentDate().month();
    if(iMonth == iCurMonth) iNumber++;
    else
    {
        iMonth = iCurMonth;
        iNumber = 1;
    }

    query.exec(QString("update Настройки set Значение ='%1' where id='%2'").arg(iNumber).arg(strUuidNumber));
    query.exec(QString("update Настройки set Значение ='%1' where id='%2'").arg(iMonth).arg(strUuidMonth));

    return QString("%1").arg(iNumber);
}

//----
/*Перевод числа в строку-слова*/
//----
std::vector<QString> rubles = { QString(" рубль"), QString(" рубля"), QString(" рублей") };
std::vector<QString> thousands = { " тысяча", " тысячи", " тысяч" };
std::vector<QString> millions = { " миллион", " миллиона", " миллионов" };


std::vector<QString> one = { "", " одна", " две", " три", " четыре", " пять", " шесть", " семь", " восемь", " девять" };
std::vector<QString> ones = { "", " один", " два", " три", " четыре", " пять", " шесть", " семь", " восемь", " девять" };
std::vector<QString> teens = { " десять", " одиннадцать", " двенадцать", " тринадцать", " четырнадцать", " пятнадцать", " шестнадцать", " семнадцать", " восемнадцать", " девятнадцать" };
std::vector<QString> tens = { "", "", " двадцать", " тридцать", " сорок", " пятьдесят", " шестьдесят", " семьдесят", " восемьдесят", " девяносто" };
std::vector<QString> hundredth = { ""," сто", " двести", " триста", " четыреста", " пятьсот", " шестьсот", " семьсот", " восемьсот", " девятьсот",};

QString Ending(long long number , std::vector<QString> ends) {
    int lastDigit = number % 10;
    int penultimateDigit = (number / 10) % 10;

    if (penultimateDigit == 1) {  // Для чисел 10-19 всегда "тысяч"
        return ends[2];
    }
    else if (lastDigit == 1) {  // Для чисел, оканчивающихся на 1 (кроме 11), "тысяча"
        return ends[0];
    }
    else if (lastDigit >= 2 && lastDigit <= 4) {  // Для чисел, оканчивающихся на 2-4 (кроме 12-14), "тысячи"
        return ends[1];
    }
    else {  // Во всех остальных случаях "тысяч"
        return ends[2];
    }
}

QString nameForNumber(long long number, bool flag=false) {
    //единицы
    if (number < 10) {
        return flag ? one[number] : ones[number];
    }
    //числительные
    else if (number < 20) {
        return teens[number - 10];
    }
    //десятки
    else if (number < 100) {
        return tens[number / 10] + nameForNumber(number % 10);
    }
    //сотни
    else if (number < 1000) {
        return hundredth[number / 100] +  nameForNumber(number % 100);
    }
    //тысячи
    else if (number < 1000000) {
        return nameForNumber(number / 1000, true) + Ending(number / 1000 , thousands) + nameForNumber(number % 1000);//Тут ошибка от 10к до 100к
    }
    //миллионы
    else if (number < 1000000000) {
        return nameForNumber(number / 1000000) + Ending(number / 1000000 , millions) + nameForNumber(number % 1000000);
    }
    //миллиарды
    else if (number < 1000000000000) {
        return nameForNumber(number / 1000000000) + " миллиардов" + nameForNumber(number % 1000000000);//еще не доделалано
    }
    return "error";
}

QString rublesForNumber(long long number)
{
    QString rVal = nameForNumber(number) + Ending(number % 100 , rubles);
    //rVal.removeFirst();
    rVal.remove(0, 1);
    rVal.front() = rVal.front().toUpper();

    return rVal;
}
//----
/*Перевод числа в строку-слова*/
//----


QIcon IconByNumber(int iNumb)
{
    if(iNumb == 0 ) return QIcon();
    if(iNumb == 1 ) return QIcon(":/icons/1.png");
    if(iNumb == 2 ) return QIcon(":/icons/2.png");
    if(iNumb == 3 ) return QIcon(":/icons/3.png");
    if(iNumb == 4 ) return QIcon(":/icons/4.png");
    if(iNumb == 5 ) return QIcon(":/icons/5.png");
    if(iNumb == 6 ) return QIcon(":/icons/6.png");
    if(iNumb == 7 ) return QIcon(":/icons/7.png");
    if(iNumb == 8 ) return QIcon(":/icons/8.png");
    if(iNumb == 9 ) return QIcon(":/icons/9.png");

    return QIcon(":/icons/more_icon.png");
}

bool IsUUidInVector(QVector<QUuid> vector, QUuid val)
{
    foreach(QUuid id , vector)
    {
        if(id == val) return true;
    }
    return false;
}

void debug_TimeStamp(QString pred)
{
    qDebug()<<" TimeStamp="<<QTime::currentTime().toString("hh:mm:ss.zzz ")<<pred;
}



void ResizeImage(QImage* image) {
    // Проверка на валидность указателя и изображения
    if (!image || image->isNull()) {
        return;
    }

    // Проверяем, нужно ли масштабировать
    if (image->width() > maxImgWidth || image->height() > maxImgHeight) {
        // Масштабируем с сохранением пропорций и сглаживанием
        *image = image->scaled(
            QSize(maxImgWidth, maxImgHeight),
            Qt::KeepAspectRatio,
            Qt::SmoothTransformation
            );
    }
}

QByteArray fromHEICToJPEG(const QByteArray &imageData) {
    QBuffer buffer;
    buffer.setData(imageData);
    QImageReader imageReader(&buffer);
    imageReader.setAutoTransform(true);
    // ^^Qt auto detects the "heic" format
    QImage resizeImage = imageReader.read();
    ResizeImage(&resizeImage);
    QByteArray outBa;
    QBuffer outBuffer(&outBa);
    outBuffer.open(QIODevice::WriteOnly);
    resizeImage.save(&outBuffer, "JPEG");
    return outBa;
}

QString PictureFileToBase64(QString strPath)
{

    QFile CurrentFile(strPath);
    if(!CurrentFile.open(QIODevice::ReadOnly))
    {
        qDebug()<<"!CurrentFile.open error strPath="<<strPath<<" error="<<CurrentFile.errorString()<<" error code="<<CurrentFile.error();
        return QString();
    }
    QByteArray imageData = CurrentFile.readAll();

    QBuffer buffer;
    buffer.setData(imageData);
    QImageReader imageReader(&buffer);

    imageReader.setAutoTransform(true);
    // ^^Qt auto detects the "heic" format
    QImage resizeImage = imageReader.read();

    ResizeImage(&resizeImage);

    QByteArray outBa;
    QBuffer outBuffer(&outBa);

    outBuffer.open(QIODevice::WriteOnly);
    resizeImage.save(&outBuffer, "JPEG");

   return outBuffer.data().toBase64();

}

QString ImageToBase64(const QImage & img)
{
    // Проверяем, нужно ли масштабировать
    if (img.width() > maxImgWidth || img.height() > maxImgHeight)
    {
        QImage resizeImage(img);
        ResizeImage(&resizeImage);

        QBuffer buffer;
        buffer.open(QIODevice::WriteOnly);

        resizeImage.save(&buffer, "JPG");

        return buffer.data().toBase64();
    }

    QBuffer buffer;
    buffer.open(QIODevice::WriteOnly);

    img.save(&buffer, "JPG");

    return buffer.data().toBase64();
}

QImage Base64ToImage(QString & base64Str)
{
    //TODO:  дописать
    //qDebug()<<"strlen="<<base64Str.length()<<" Base64ToImage before remove base64Str="<<base64Str;

    QByteArray arr = QByteArray::fromBase64(base64Str.toLatin1());

    return QImage::fromData(arr, "JPG");
}


QString CreateDateBDPeriodFromNow(QString strBdDateField , int iDays)
{
    qint64 iCurrentTime = QDateTime::currentSecsSinceEpoch();
    QString retVal = QString("and %1>'%2' and %1<='%3'").arg(strBdDateField).arg(iCurrentTime-iDays*86400).arg(iCurrentTime);
    return retVal;
}


bool OpenServerBD()
{

     int result = 0;

#ifdef Q_OS_ANDROID__111
    /*Открытие серверной БД*/
    QJniObject jTextHost = QJniObject::fromString(settings.strServAdress);

    result = pActivity->callMethod<jint>("OpenServerBD" , "(Ljava/lang/String;)I" , jTextHost.object());
#endif
//#if defined Q_OS_IOS || defined Q_OS_WINDOWS

    serverBD = new QSocketBD;

//#endif

    return result;
}

int execMainBDQueryUpdate(QString query)
{
    int res = 0;
//#if defined Q_OS_IOS || defined Q_OS_WINDOWS
    res = serverBD->execMainBDQueryUpdate(query);
//#endif
#ifdef Q_OS_ANDROID___1111
    QJniObject jTextQuery = QJniObject::fromString(query);
    res = pActivity->callMethod<jint>("execQueryUpdate","(Ljava/lang/String;)I",jTextQuery.object());
#endif

    return res;

}

QList<QStringList> execMainBDQuery(QString query)
{
    QList<QStringList> retVal;

//#if defined Q_OS_IOS || defined Q_OS_WINDOWS

    retVal = serverBD->execMainBDQuery(query);

//#endif



#ifdef Q_OS_ANDROID_111
    QJniObject jTextQuery = QJniObject::fromString(query);
    QJniObject QueryResult  =  pActivity->callObjectMethod("execQuery","(Ljava/lang/String;)[Ljava/lang/String;",jTextQuery.object());

    if(QueryResult != NULL)
    {

        jobjectArray strArray = QueryResult.object<jobjectArray>();

        QJniEnvironment env;

        int resultStringCount = env.jniEnv()->GetArrayLength(strArray);

        for(int iResultStringCounter = 0 ; iResultStringCounter<resultStringCount ; iResultStringCounter++)
        {
            QJniObject Result1 = env.jniEnv()->GetObjectArrayElement(strArray , iResultStringCounter);

            QStringList retValList = Result1.toString().split("##--**");

            retValList.removeLast();

            retVal.append(retValList);
        }
    }
#endif
    return retVal;
}

bool CheckLineEditLenSetLabel(QLineEdit * pLineEdit , QLabel * pLabel)
{
    if(pLineEdit->text().size()<3)
    {
        pLabel->setStyleSheet("QLabel { color : red; }");
        return false;
    }
    else
    {
        pLabel->setStyleSheet("QLabel { color : black; }");
    }
    return true;
}


#ifdef Q_OS_ANDROID
int IsCameraPrenissionAndRequest()
{
    QPlatformNativeInterface* interface = QGuiApplication::platformNativeInterface();
    jobject activity = (jobject)interface->nativeResourceForIntegration("QtActivity");
    QJniObject * pActivity;

    QJniObject context = QNativeInterface::QAndroidApplication::context();

    if (activity)
    {
        pActivity = new QJniObject(activity);

        int iRes = pActivity->callMethod<jint>("IsCameraPremissionAndRequest","(Landroid/content/Context;)I",context.object<jobject>());

        return (iRes);
    }
    return /*false*/7;
}
#endif




QString month(int num)
{
    switch (num) {
        case 1: return "Январь";
        case 2: return "Февраль";
        case 3: return "Март";
        case 4: return "Апрель";
        case 5: return "Май";
        case 6: return "Июнь";
        case 7: return "Июль";
        case 8: return "Август";
        case 9: return "Сентябрь";
        case 10: return "Октябрь";
        case 11: return "Ноябрь";
        case 12: return "Декабрь";
        default: return "Месяц";
    }
}

// QString ListToString(QList<QString> list)
// {
//     QString retVal;

//     // QList<QString>::iterator itItems;

//     // for (itItems = list().begin(); itItems != list().end(); ++itItems)
//     // {
//     //     retVal.append(*itItems);
//     //     retVal.append(",");
//     // }

//     // retVal.chop(1); //удаляем последнюю запятую
//     return retVal;
// }

QString ListListToString(QList<QStringList> list)
{
    QStringList outerParts;
    for (const QStringList &innerList : list) {
        // Форматируем внутренний список: {"элемент1", "элемент2", ...}
        QString innerStr = "{ \"" + innerList.join("\", \"") + "\" }";
        outerParts << innerStr;
    }

    // Объединяем все внутренние списки в строку
    QString result = "{ " + outerParts.join(", ") + " }";

    return result;
}

template<typename EnumType>
QString EnumToString(const EnumType& enumValue)
{
    const char* enumName = qt_getEnumName(enumValue);
    const QMetaObject* metaObject = qt_getEnumMetaObject(enumValue);
    if (metaObject)
    {
        const int enumIndex = metaObject->indexOfEnumerator(enumName);
        return QString("%1::%2::%3").arg(metaObject->className(), enumName, metaObject->enumerator(enumIndex).valueToKey(enumValue));
    }

    return QString("%1::%2").arg(enumName).arg(static_cast<int>(enumValue));
}

bool SendToWhatsapp2(QString text , QVector<QString> picturesPaths)
{
    #ifdef Q_OS_ANDROID
        QPlatformNativeInterface* interface = QGuiApplication::platformNativeInterface();
        jobject activity = (jobject)interface->nativeResourceForIntegration("QtActivity");
        QJniObject * pActivity;

        if (activity)
        {
              pActivity = new QJniObject(activity);
        }
        else return false;

        QJniObject context = QNativeInterface::QAndroidApplication::context();

        QString strFilePaths;

        for(int iPictureCounter = 0; iPictureCounter < picturesPaths.size(); ++iPictureCounter)
        {
            QJniObject extDir = context.callObjectMethod("getExternalFilesDir", "(Ljava/lang/String;)Ljava/io/File;", NULL);


            //Абсолютный путь к каталогу для хранения файлов приложения в виде строки
            QJniObject extDirAbsPath = extDir.callObjectMethod("getAbsolutePath","()Ljava/lang/String;");

            //Добавим имя каталога для совместного использования файлов этого приложения другими приложениями. См. /res/xml/file_paths.xml
            extDirAbsPath = QJniObject::fromString(extDirAbsPath.toString() + "/shared");

            const QString extDirAbsPathStr = extDirAbsPath.toString();

            //Создать объект типа Файл для разделяемого каталога
            QJniObject sharedFolder=QJniObject("java.io.File","(Ljava/lang/String;)V",
                                                                  extDirAbsPath.object<jstring>());

             const jboolean sharedFolderCreated = sharedFolder.callMethod<jboolean>("mkdirs");
             Q_UNUSED(sharedFolderCreated);

            /*Путь к файлу, который будем отправлять*/
             QJniObject suggestedFilePath = QJniObject::fromString(extDirAbsPathStr+"/"+QString("%1").arg(iPictureCounter)+"_tmp.jpg");

             /*Скопируем в него отправляемый файл*/
             if (QFile::exists(suggestedFilePath.toString()))
             {
                 QFile::remove(suggestedFilePath.toString());
             }

             if(!QFile::copy(picturesPaths[iPictureCounter], suggestedFilePath.toString()))
             {
                 qDebug()<<"error coping "<<picturesPaths[iPictureCounter]<<" to "<< suggestedFilePath.toString();
             }

            strFilePaths+= suggestedFilePath.toString() +"|";

        }

        strFilePaths = strFilePaths.remove(strFilePaths.size() -1 ,1).trimmed();

        QJniObject jText = QJniObject::fromString(text);
        QJniObject jFilePaths = QJniObject::fromString(strFilePaths);

        pActivity->callMethod<void>("SendTextAndFilesWhatsAppMessage","(Ljava/lang/String;Ljava/lang/String;)V",jText.object<jstring>(),jFilePaths.object<jstring>());
    #endif
    return true;
}

bool SendToTelegram2(QString text , QVector<QString> picturesPaths)
{
    #ifdef Q_OS_ANDROID
        QPlatformNativeInterface* interface = QGuiApplication::platformNativeInterface();
        jobject activity = (jobject)interface->nativeResourceForIntegration("QtActivity");
        QJniObject * pActivity;

        if (activity)
        {
              pActivity = new QJniObject(activity);
        }
        else return false;

        QJniObject context = QNativeInterface::QAndroidApplication::context();

        QString strFilePaths;

        for(int iPictureCounter = 0; iPictureCounter < picturesPaths.size(); ++iPictureCounter)
        {
            QJniObject extDir = context.callObjectMethod("getExternalFilesDir", "(Ljava/lang/String;)Ljava/io/File;", NULL);


            //Абсолютный путь к каталогу для хранения файлов приложения в виде строки
            QJniObject extDirAbsPath = extDir.callObjectMethod("getAbsolutePath","()Ljava/lang/String;");

            //Добавим имя каталога для совместного использования файлов этого приложения другими приложениями. См. /res/xml/file_paths.xml
            extDirAbsPath = QJniObject::fromString(extDirAbsPath.toString() + "/shared");

            const QString extDirAbsPathStr = extDirAbsPath.toString();

            //Создать объект типа Файл для разделяемого каталога
            QJniObject sharedFolder=QJniObject("java.io.File","(Ljava/lang/String;)V",
                                                                  extDirAbsPath.object<jstring>());

             const jboolean sharedFolderCreated = sharedFolder.callMethod<jboolean>("mkdirs");
             Q_UNUSED(sharedFolderCreated);

            /*Путь к файлу, который будем отправлять*/
             QJniObject suggestedFilePath = QJniObject::fromString(extDirAbsPathStr+"/"+QString("%1").arg(iPictureCounter)+"_tmp.jpg");

             /*Скопируем в него отправляемый файл*/
             if (QFile::exists(suggestedFilePath.toString()))
             {
                 QFile::remove(suggestedFilePath.toString());
             }

             if(!QFile::copy(picturesPaths[iPictureCounter], suggestedFilePath.toString()))
             {
             }

            strFilePaths+= suggestedFilePath.toString() +"|";

        }

        strFilePaths = strFilePaths.remove(strFilePaths.size() -1 ,1).trimmed();

        QJniObject jText = QJniObject::fromString(text);
        QJniObject jFilePaths = QJniObject::fromString(strFilePaths);

        pActivity->callMethod<void>("SendTextAndFilesTelegramMessage","(Ljava/lang/String;Ljava/lang/String;)V",jText.object<jstring>(),jFilePaths.object<jstring>());
    #endif
    return true;
}

bool SendToWhatsapp(QString text)
{
    #ifdef Q_OS_ANDROID
        QJniObject ACTION_SEND = QJniObject::getStaticObjectField("android/content/Intent", "ACTION_SEND", "Ljava/lang/String;");
        QJniObject EXTRA_TEXT = QJniObject::getStaticObjectField("android/content/Intent", "EXTRA_TEXT", "Ljava/lang/String;");
        QJniObject intent = QJniObject("android/content/Intent", "(Ljava/lang/String;)V", ACTION_SEND.object());

        intent.callObjectMethod("putExtra", "(Ljava/lang/String;Ljava/lang/String;)Landroid/content/Intent;", EXTRA_TEXT.object(), QJniObject::fromString(text).object());

        intent.callObjectMethod("setType", "(Ljava/lang/String;)Landroid/content/Intent;", QJniObject::fromString(QString("text/plain")).object());

        intent.callObjectMethod("setPackage","(Ljava/lang/String;)Landroid/content/Intent;", QJniObject::fromString(QString("com.whatsapp")).object());

        auto chooserIntent = QJniObject::callStaticObjectMethod("android/content/Intent", "createChooser", "(Landroid/content/Intent;Ljava/lang/CharSequence;)Landroid/content/Intent;", intent.object(), QJniObject::fromString(QString("Куда послать?")).object());

        QtAndroidPrivate::startActivity(chooserIntent, 0, nullptr);
    #endif
    return true;

}

bool SendToTelegram(QString text)
{
    #ifdef Q_OS_ANDROID
        QJniObject ACTION_SEND = QJniObject::getStaticObjectField("android/content/Intent", "ACTION_SEND", "Ljava/lang/String;");
        QJniObject EXTRA_TEXT = QJniObject::getStaticObjectField("android/content/Intent", "EXTRA_TEXT", "Ljava/lang/String;");
        QJniObject intent = QJniObject("android/content/Intent", "(Ljava/lang/String;)V", ACTION_SEND.object());


        intent.callObjectMethod("putExtra", "(Ljava/lang/String;Ljava/lang/String;)Landroid/content/Intent;", EXTRA_TEXT.object(), QJniObject::fromString(text).object());

        intent.callObjectMethod("setType", "(Ljava/lang/String;)Landroid/content/Intent;", QJniObject::fromString(QString("text/plain")).object());

        intent.callObjectMethod("setPackage","(Ljava/lang/String;)Landroid/content/Intent;", QJniObject::fromString(QString("org.telegram.messenger")).object());

        auto chooserIntent = QJniObject::callStaticObjectMethod("android/content/Intent", "createChooser", "(Landroid/content/Intent;Ljava/lang/CharSequence;)Landroid/content/Intent;", intent.object(), QJniObject::fromString(QString("Куда послать?")).object());

        QtAndroidPrivate::startActivity(chooserIntent, 0, nullptr);
    #endif
    return true;
}




bool IsAlarmPrenission()
{
    #ifdef Q_OS_ANDROID
        QPlatformNativeInterface* interface = QGuiApplication::platformNativeInterface();
        jobject activity = (jobject)interface->nativeResourceForIntegration("QtActivity");
        QJniObject * pActivity;

        QJniObject context = QNativeInterface::QAndroidApplication::context();

        if (activity)
        {
            pActivity = new QJniObject(activity);

            /*Если будильник установили*/
            if(pActivity->callMethod<jint>("IsShedulerPremission","(Landroid/content/Context;)I",context.object<jobject>()))
            {
                return true;
            }
        }
    #endif

    return false;
}

int IsAlarmPrenissionAndRequest()
{
    #ifdef Q_OS_ANDROID
        QPlatformNativeInterface* interface = QGuiApplication::platformNativeInterface();
        jobject activity = (jobject)interface->nativeResourceForIntegration("QtActivity");
        QJniObject * pActivity;

        QJniObject context = QNativeInterface::QAndroidApplication::context();

        if (activity)
        {
            pActivity = new QJniObject(activity);

            int iRes = pActivity->callMethod<jint>("IsShedulerPrenissionAndRequest","(Landroid/content/Context;)I",context.object<jobject>());

            return (iRes);
        }
    #endif
    return /*false*/7;
}


bool SetAlarmClock(QString strText , int iNotifiId , long iTimeSec)
{
    #ifdef Q_OS_ANDROID
        QJniObject jText = QJniObject::fromString(strText);
        QJniObject jTitle = QJniObject::fromString(QString("Планы"));


        QPlatformNativeInterface* interface = QGuiApplication::platformNativeInterface();
        jobject activity = (jobject)interface->nativeResourceForIntegration("QtActivity");
        QJniObject * pActivity;

        QJniObject context = QNativeInterface::QAndroidApplication::context();

        if (activity)
        {
                pActivity = new QJniObject(activity);

                /*Если будильник установили*/
                if(pActivity->callMethod<jint>("SetAlarm","(Landroid/content/Context;Ljava/lang/String;Ljava/lang/String;IJ)I",context.object<jobject>() , jTitle.object() , jText.object() , jint(iNotifiId) , jlong(iTimeSec*1000)))
                {
                    return true;
                }
        }
    #endif
    return false;
}

bool CancelAlarm(int iNotifiId)
{
    #ifdef Q_OS_ANDROID
        QPlatformNativeInterface* interface = QGuiApplication::platformNativeInterface();
        jobject activity = (jobject)interface->nativeResourceForIntegration("QtActivity");
        QJniObject * pActivity;

        QJniObject context = QNativeInterface::QAndroidApplication::context();

        if (activity)
        {
                pActivity = new QJniObject(activity);

                /*Если будильник установили*/
                if(pActivity->callMethod<jint>("CancelAlarm","(Landroid/content/Context;I)I",context.object<jobject>() ,jint(iNotifiId)))
                {
                    return true;
                }
        }
    #endif
    return false;
}
