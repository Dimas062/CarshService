#include "licence.h"

#include <QByteArray>
#include <QtDebug>
#include <QtGlobal>
#include <QDateTime>
#include <QCryptographicHash>
#include <QDataStream>

#include <QtCore>
#include <QtGui>
#include <QtWidgets>

#include "dsa.h"
#include "osrng.h"
#include "base64.h"

using namespace CryptoPP;

#ifdef __GNUC__
#include <X11/Intrinsic.h>
#include <cpuid.h>
#elif _MSC_VER//MSVC
#include "intrin.h"
#endif

namespace Licensing {

Licence &Licence::getInstance()
{
    static Licence s;
    return s;
}

quint64 Licence::get_cpuId()
{
    QString cpu_id = "";
    unsigned int dwBuf[4] = {0};
    quint64 ret = 0;
    getcpuid(dwBuf, 1);
    ret = dwBuf[2];
    ret = (ret << 32) + dwBuf[0];
    return ret;
}

void Licence::getcpuid( unsigned int CPUInfo[4], unsigned int InfoType)
{
#if defined(__GNUC__)//GCC
    __cpuid(InfoType, CPUInfo[0], CPUInfo[1], CPUInfo[2], CPUInfo[3]);
#elif defined(_MSC_VER)//MSVC
#if _MSC_VER >= 1400 //VC2005 only supports __cpuid
    __cpuid((int*)(void*)CPUInfo, (int)(InfoType));
#else //Other uses getcpuidex
    getcpuidex(CPUInfo, InfoType, 0);
#endif
#endif
}
void getcpuidex( unsigned int CPUInfo[4], unsigned int InfoType, unsigned int ECXValue)
{
#if defined(_MSC_VER) //MSVC
#if defined(_WIN64) //64-bit does not support inline assembly. 1600: VS2010, it is said that __cpuidex is only supported after VC2008 SP1.
    __cpuidex((int*)(void*)CPUInfo , (int)InfoType, (int)ECXValue);
#else
    if (NULL==CPUInfo)   return ;
    _asm{
        //load. Read parameters to register.
        mov edi, CPUInfo;
        mov eax, InfoType;
        mov ecx, ECXValue;
        //CPUID
        cpuid;
        //save. Save the register to CPUInfo
        mov [edi], eax;
        mov [edi + 4], ebx;
        mov [edi + 8], ecx;
        mov [edi + 12], edx;
    }
#endif
#endif
}

QString Licence::getPcCpuId()
{
    auto ret = get_cpuId();
    QString hexvalue = QString("%1").arg(ret, 8, 16, QLatin1Char('0'));

    return hexvalue;
}

Licensing::LicenceProperties Licence::readLicence()
{
    QFile file("licence.vslic");
    QByteArray data;
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        return LicenceProperties(QDateTime(), QString(), QString(),
                                 false,
                                 QString(), QString(), QDateTime(),
                                 QString(),
                                 getPcCpuId(),
                                 QString(),
                                 LeErrNoLicenceFileOnServer);
    }

    data = file.readAll();
    QFileInfo fileInfo(file);
    bool veto = false;
    if (lastModified == QDateTime())
    {
        lastModified = fileInfo.lastModified();
    }
    else
    {
        if (lastModified == fileInfo.lastModified()){
            veto = true;
        }
    }

    uint key;
    uint i_h_high, i_h_low;
    char *data_char = data.data();
    QByteArray res;
    for (int n = 0; n < strlen(data); n+=2)
    {
        i_h_high = (data_char[n] << 8) - 0xffff0000;
        i_h_low = data_char[n + 1] - 0xffffff00;
        key = i_h_high == 0xdf00
              ? 0x07a4 : i_h_high == 0xcf00
                ? 0x1f24 : i_h_high == 0xde00
                  ? 0x07e4 : i_h_high == 0xce00
                    ? 0x1f24 : 0xcee4;
        ushort i_h = (i_h_high + i_h_low) ^ key;

        if (key == 52132)
        {
            i_h += 176;
        }
        auto i_h_h = i_h >> 8;

        if (i_h_h != 0xd8 && i_h_h != 0xd9 && i_h_h != 0x00)
        {
            res.append(i_h_h);
        }
        res.append(i_h);

        continue;
    }

    QTextStream resin(&res);
    resin.setCodec("UTF-8");
    auto QTS = resin.readAll();

#ifdef QT_DEBUG
    qDebug() << "QTS :" << QTS;
#endif

    QXmlStreamReader xml(QTS);
    QMap<QString, std::string> xmlElements;

    while (!xml.atEnd() && !xml.hasError())
    {
        QXmlStreamReader::TokenType token = xml.readNext();
        if (token == QXmlStreamReader::StartDocument)
        {
            continue;
        }
        if (token == QXmlStreamReader::StartElement)
        {
            if (xml.name() != "VSLicense" && xml.name() != "Data")
            {
                QString elementName = xml.name().toString();
                xml.readNext();

                QString elementText = xml.text().toString();
                elementText.replace('&', "&amp;");
                elementText.replace('<', "&lt;");
                elementText.replace('>', "&gt;");
                elementText.replace('\'', "&apos;");
                elementText.replace('\"', "&quot;");

                xmlElements.insert(elementName, elementText.toStdString());

#ifdef QT_DEBUG
                qDebug() << "elementName :" << elementName <<
                            "elementText" << elementText;
#endif
            }
        }
    }
    QList<QString> xmlKeys = xmlElements.keys();
    bool xmlKeysValidate = false;
    bool xmlKeyEndDateExists = false;

    if (xmlKeys.contains("generation_date") &&
        xmlKeys.contains("user") &&
        xmlKeys.contains("key") &&
        xmlKeys.contains("key_type") &&
        xmlKeys.contains("customer") &&
        xmlKeys.contains("parameters") &&
        xmlKeys.contains("PValue"))
    {
        if (xmlKeys.count() == 7)
        {
            xmlKeysValidate = true;
        }
        else if (xmlKeys.contains("end_date"))
        {
            xmlKeysValidate = true;
            xmlKeyEndDateExists = true;
        }
    }


    if (!xmlKeysValidate)
    {
        return LicenceProperties(QDateTime(), QString(), QString(),
                                 false,
                                 QString(), QString(), QDateTime(),
                                 QString(),
                                 getPcCpuId(),
                                 QString(),
                                 LeErrLicenceFileCorrupted);
    }

    std::string s1(1, 0xEF), s2(1, 0xBB), s3(1, 0xBF);
    std::string message;
    if (xmlKeyEndDateExists)
    {
        message = s1 + s2 + s3 +
                  "<?xml version=\"1.0\" encoding=\"utf-8\"?>" +
                  "\r\n<Data>" +
                  "\r\n  <generation_date>" + xmlElements.value("generation_date") + "</generation_date>" +
                  "\r\n  <user>" + xmlElements.value("user") + "</user>" +
                  "\r\n  <key>" + xmlElements.value("key") + "</key>" +
                  "\r\n  <key_type>" + xmlElements.value("key_type") + "</key_type>" +
                  "\r\n  <customer>" + xmlElements.value("customer") + "</customer>" +
                  "\r\n  <parameters>" + xmlElements.value("parameters") + "</parameters>" +
                  "\r\n  <end_date>" + xmlElements.value("end_date") + "</end_date>" +
                  "\r\n</Data>";
    }
    else
    {
        message = s1 + s2 + s3 +
                  "<?xml version=\"1.0\" encoding=\"utf-8\"?>" +
                  "\r\n<Data>" +
                  "\r\n  <generation_date>" + xmlElements.value("generation_date") + "</generation_date>" +
                  "\r\n  <user>" + xmlElements.value("user") + "</user>" +
                  "\r\n  <key>" + xmlElements.value("key") + "</key>" +
                  "\r\n  <key_type>" + xmlElements.value("key_type") + "</key_type>" +
                  "\r\n  <customer>" + xmlElements.value("customer") + "</customer>" +
                  "\r\n  <parameters>" + xmlElements.value("parameters") + "</parameters>" +
                  "\r\n</Data>";
    }
    std::string encodedSignature = xmlElements.value("PValue");

    std::string encodedStrP = "n32I4JvdaJfalDjK7KSlqqSJB+2O4v2P+D611MODdfMNLQndca5lKt2Js5NNMcLSmCMVWnPALC8iCe1zncC6yz8PcwrQZu4e/PQdVEU/N1IdlBu3xQhbb4i/lILkCdCqMaAXvSkjt4SzRPeqa75OT68ktjoRtiOy1JDJE8hCEUc=";
    std::string encodedStrQ = "+h9kJAhGA/h8UqE3SIBf11/IDa8=";
    std::string encodedStrG = "iaGYjkwGYEm1vjfxqu4EZ9ubpkLXFQVUP5+lU/ah65wQaOCCHQMa6JdKbaOkouP9asrCYbfK5iPlUsejvA7r8o6tTxsC43DceZRrUuM1ubgvP3G9VG4ENLqCkRtB5MCUPeHlQZ9M4YgboWZm4drp9EkK5QUJqPCR5th3owMim9c=";
    std::string encodedStrY = "aDM1YNpgA7n/RxRhXnboiEr29AUfRTb/rOn05kAL1hgyed/96nEtGLlDhqQSyrwI6Vge2Z8RQJ1W8EKtfBxHR3LzEE0PLEwkLBTygujY1cVbpL/lI6VgSTkow2rMkWMU+XLfOPGWJagR+bQxOzZWj7gLsQAp1RylOKTKYQbnQRI=";

    StringSource mod64(encodedStrP, true, new Base64Decoder());
    StringSource sub64(encodedStrQ, true, new Base64Decoder());
    StringSource gen64(encodedStrG, true, new Base64Decoder());
    StringSource pub64(encodedStrY, true, new Base64Decoder());

    Integer mod_integer(mod64, mod64.MaxRetrievable());
    Integer sub_integer(sub64, sub64.MaxRetrievable());
    Integer gen_integer(gen64, gen64.MaxRetrievable());
    Integer pub_integer(pub64, pub64.MaxRetrievable());

    std::string decoded_sig;
    Base64Decoder decoder;
    decoder.Attach(new StringSink(decoded_sig));
    decoder.Put((byte*)encodedSignature.data(), encodedSignature.size());
    decoder.MessageEnd();

    DSA::PublicKey publicKey;
    publicKey.Initialize(mod_integer, sub_integer, gen_integer, pub_integer);

    DSA::Verifier verifier(publicKey);
    bool result = false;
    StringSource ss2(message + decoded_sig,
                     true,
                     new SignatureVerificationFilter(
                         verifier,
                         new ArraySink((byte*)&result, sizeof(result)),
                         SignatureVerificationFilter::PUT_RESULT |
                         SignatureVerificationFilter::SIGNATURE_AT_END));

    if (!result)
    {
        if (veto)
        {
            return LicenceProperties(QDateTime(), QString(), QString(),
                                     false,
                                     QString(), QString(), QDateTime(),
                                     QString(),
                                     getPcCpuId(),
                                     QString(),
                                     LeErrNoHaspPlugged);
        }
        else{
            return LicenceProperties(QDateTime(), QString(), QString(),
                                     false,
                                     QString(), QString(), QDateTime(),
                                     QString(),
                                     getPcCpuId(),
                                     QString(),
                                     LeErrVerifySignature);
        }
    }

    QDateTime mGenerationDateTime =
            QDateTime::fromString(
                QString::fromStdString(
                    xmlElements.value("generation_date")), "yyyy-MM-ddThh:mm:ss");
    QString mUser = QString::fromStdString(xmlElements.value("user"));
    QString mKey = QString::fromStdString(xmlElements.value("key"));
    bool mKeyType =
            QString::fromStdString(
                xmlElements.value("key_type")).toInt() ? true : false;
    QString mCustomer = QString::fromStdString(xmlElements.value("customer"));
    QString mParameters = QString::fromStdString(xmlElements.value("parameters"));
    QDateTime mEndDateTime;
    if (xmlKeyEndDateExists)
    {
        mEndDateTime =
                QDateTime::fromString(
                    QString::fromStdString(
                        xmlElements.value("end_date")),"yyyy-MM-ddThh:mm:ss");
    }
    else
    {
        mEndDateTime = QDateTime(QDate(292278994, 0, 0));
    }

    LicenceErrors error;
    if (mKeyType)
    {
        if (getPcCpuId() == mKey)
        {
            error = LeGood;
        }
        else
        {
            error = LeErrWrongCpuid;
        }
    }
    else
    {
        error = LeErrNoHaspPlugged;
        mKey = QString("%1").arg(mKey.toInt(), 8, 16, QLatin1Char('0'));
    }
    return LicenceProperties(mGenerationDateTime, mUser, mKey,
                             mKeyType,
                             mCustomer, mParameters, mEndDateTime,
                             QString(),
                             getPcCpuId(),
                             QString(),
                             error);
}

Licence::Licence() : QObject()
{

}

Licence::~Licence()
{

}

QString Licence::getErrorMessageByCode(
        LicenceErrors le,
        Licensing::LicenceProperties mCurrentLicence)
{
    if (le == LeGood ||
        (!isIncludedInEnum(le, LeError) &&
         !isIncludedInEnum(le, LeWarning) &&
         !isIncludedInEnum(le, LeOver)))
    {
        return QObject::tr("Активна");
    }
    QString ret_urn = QString();
    if (isIncludedInEnum(le, LeError))
    {
        if (isEnumContains(le, LeErrNoLicenceFileOnServer))
        {
            if (ret_urn != QString())
            {
                ret_urn += "\n";
            }
            ret_urn += QObject::tr("Файл лицензии отсутствует на сервере");
        }
        if (isEnumContains(le, LeErrVerifySignature))
        {
            if (ret_urn != QString())
            {
                ret_urn += "\n";
            }
            ret_urn += QObject::tr("Не удалось провести проверку подписи файла лицензии");
        }

        if (isEnumContains(le, LeErrWrongCpuid))
        {
            if (ret_urn != QString())
            {
                ret_urn += "\n";
            }
            ret_urn += QObject::tr("Файл лицензии предназначен для другого ПК с CPUID = ") + mCurrentLicence.mKey;
        }
        if (isEnumContains(le, LeErrNoHaspPlugged))
        {
            if (ret_urn != QString())
            {
                ret_urn += "\n";
            }
            ret_urn += QObject::tr("Требуется физический носитель HASP ключа");
        }
        if (isEnumContains(le, LeErrLicenceFileCorrupted))
        {
            if (ret_urn != QString())
            {
                ret_urn += "\n";
            }
            ret_urn += QObject::tr("Файл лицензии повреждён");
        }
    }
    if (isIncludedInEnum(le, LeWarning))
    {
        if (isEnumContains(le, LeWarnReadMotherboardSerial))
        {
            if (ret_urn != QString())
            {
                ret_urn += "\n";
            }
            ret_urn += QObject::tr("Не удалось прочитать серийный номер материнской платы");
        }
        if (isEnumContains(le, LeWarnServerNeedRights))
        {
            if (ret_urn != QString())
            {
                ret_urn += "\n";
            }
            ret_urn += QObject::tr("Сервер лицензирования не обладает достаточными правами для чтения/записи");
        }
        if (isEnumContains(le,  LeWarnWrongHasp))
        {
            if (ret_urn != QString())
            {
                ret_urn += "\n";
            }
            ret_urn += QObject::tr("Файл лицензии предназначен для другого HASP ключа с ID = ") + mCurrentLicence.mKey;
        }
        if (isEnumContains(le,  LeWarnNoHaspPlugged))
        {
            if (ret_urn != QString())
            {
                ret_urn += "\n";
            }
            ret_urn += QObject::tr("Требуется физический носитель HASP ключа с ID = ") + mCurrentLicence.mKey;
        }
        if (isEnumContains(le,  LeWarnNoHaspDriver))
        {
            if (ret_urn != QString())
            {
                ret_urn += "\n";
            }
            ret_urn += QObject::tr("Произошла ошибка проверки HASP ключа, проверьте драйвер");
        }
        if (isEnumContains(le,  LeWarnLicenceExpired))
        {
            if (ret_urn != QString())
            {
                ret_urn += "\n";
            }
            ret_urn += QObject::tr("Срок действия лицензии истёк");
        }
    }
    if (isIncludedInEnum(le, LeOver))
    {
        if (ret_urn != QString())
        {
            ret_urn += "\n";
        }
        QString welcome = QObject::tr("Превышение разрешённого количества подключённых:");
        ret_urn += welcome;
        if (isEnumContains(le, LeOverCams))
        {
            ret_urn += QObject::tr("\n    камер");
        }
        if (isEnumContains(le, LeOverClients))
        {
            ret_urn += QObject::tr("\n    клиентов");
        }
        if (isEnumContains(le, LeOverCashboxes))
        {
            ret_urn += QObject::tr("\n    касс");
        }
        if (isEnumContains(le, LeOverPluginsCleanHands) ||
            isEnumContains(le, LeOverPluginsFaceDet))
        {
            ret_urn += QObject::tr("\n    плагинов:");
        }
        if (isEnumContains(le, LeOverPluginsCleanHands))
        {
            ret_urn += QObject::tr("\n        Чистые руки");
        }
        if (isEnumContains(le, LeOverPluginsFaceDet))
        {
            ret_urn += QObject::tr("\n        Детектирование лиц");
        }
    }
    if (ret_urn != QString())
    {
        return ret_urn;
    }
    return QObject::tr("Произошла непредвиденная ошибка");
}

bool Licence::isIncludedInEnum(LicenceErrors value, LicenceErrors mask)
{
    ///< Мы подаём value - enum и ищем его по маске mask. Если по маске перекрывается хотя бы один бит enum'а, то говорим true
    ///< value = 0x0020, mask = 0x1022 -> true
    ///< value = 0x0020, mask = 0x1002 -> false

    switch (mask){
    case LeGood:
        {
            bool one = (value == LeGood) ? true : false;
            bool two = (!isIncludedInEnum(value, LeError) &&
                        !isIncludedInEnum(value, LeWarning) &&
                        !isIncludedInEnum(value, LeOver)) ? true : false;
            bool ret_urn = (one || two) ? true : false;
            return ret_urn;
        }
    case LeError:
        {
            bool ret_urn = (isEnumContains(value, LeErrLicenceFileCorrupted) ||
                            isEnumContains(value, LeErrNoHaspPlugged) ||
                            isEnumContains(value, LeErrNoLicenceFileOnServer) ||
                            isEnumContains(value, LeErrVerifySignature) ||
                            isEnumContains(value, LeErrWrongCpuid)) ? true : false;
            return ret_urn;
        }
    case LeWarning:
        {
            bool ret_urn = (isEnumContains(value, LeWarnReadMotherboardSerial) ||
                            isEnumContains(value, LeWarnLicenceExpired) ||
                            isEnumContains(value, LeWarnNoHaspDriver) ||
                            isEnumContains(value, LeWarnNoHaspPlugged) ||
                            isEnumContains(value, LeWarnServerNeedRights) ||
                            isEnumContains(value, LeWarnWrongHasp)) ? true : false;
            return ret_urn;
        }
    case LeOver:
        {
            bool ret_urn = (isEnumContains(value, LeOverCams) ||
                            isEnumContains(value, LeOverCashboxes) ||
                            isEnumContains(value, LeOverClients) ||
                            isEnumContains(value, LeOverPluginsCleanHands) ||
                            isEnumContains(value, LeOverPluginsFaceDet)) ? true : false;
            return ret_urn;
        }
    default:
        {
            if (isEnumContains(value, LeEdgeCams))
            {
                value = static_cast<LicenceErrors>(static_cast<int>(value) -
                                                   static_cast<int>(LeEdgeCams));
            }
            if (isEnumContains(value, LeEdgeCashboxes))
            {
                value = static_cast<LicenceErrors>(static_cast<int>(value) -
                                                   static_cast<int>(LeEdgeCashboxes));
            }
            if (isEnumContains(value, LeEdgePluginsCleanHands))
            {
                value = static_cast<LicenceErrors>(static_cast<int>(value) -
                                                   static_cast<int>(LeEdgePluginsCleanHands));
            }
            if (isEnumContains(value, LeEdgePluginsFaceDet))
            {
                value = static_cast<LicenceErrors>(static_cast<int>(value) -
                                                   static_cast<int>(LeEdgePluginsFaceDet));
            }
            auto three = value & mask;
            bool ret_urn = (three == value) ? true : false;
            return ret_urn;
        }
    }
}

bool Licence::isEnumContains(LicenceErrors value, LicenceErrors etalon)
{
    ///< Мы подаём value - enum и ищем в нём etalon. Если эталон есть, то говорим true
    ///< value = 0x1022, etalon = 0x1000 -> true
    ///< value = 0x1022, etalon = 0x0040 -> false

    switch (etalon){
    case LeGood:
        {
            bool one = (value == LeGood) ? true : false;
            bool two = (!isIncludedInEnum(value, LeError) &&
                        !isIncludedInEnum(value, LeWarning) &&
                        !isIncludedInEnum(value, LeOver)) ? true : false;
            bool ret_urn = (one || two) ? true : false;
            return ret_urn;
        }
    default:
        {
            auto three = value & etalon;
            bool ret_urn = (three == etalon) ? true : false;
            return ret_urn;
        }
    }
}

LicenceProperties::LicenceProperties()
{

}

LicenceProperties::LicenceProperties(const QDateTime& generationDateTime,
                                     const QString& user,
                                     const QString& key,
                                     bool keyType,
                                     const QString& customer,
                                     const QString& parameters,
                                     const QDateTime& endDateTime,
                                     const QString& currentState,
                                     const QString& cpuId,
                                     const QString& haspKey,
                                     const LicenceErrors& licenceErrors) :
    mGenerationDateTime(generationDateTime),
    mUser(user),
    mKey(key),
    mKeyType(keyType),
    mCustomer(customer),
    mParameters(parameters),
    mEndDateTime(endDateTime),
    cCurrentState(currentState),
    cCpuid(cpuId),
    cHaspKey(haspKey),
    cErrorCode(licenceErrors)
{

}

LicenceProperties::LicenceProperties(const LicenceProperties& other)
{
    mGenerationDateTime = other.mGenerationDateTime;
    mUser = other.mUser;
    mKey = other.mKey;
    mKeyType = other.mKeyType;
    mCustomer = other.mCustomer;
    mParameters = other.mParameters;
    mEndDateTime = other.mEndDateTime;
    cCurrentState = other.cCurrentState;
    cCpuid = other.cCpuid;
    cHaspKey = other.cHaspKey;
    cErrorCode = other.cErrorCode;
}

LicenceProperties& LicenceProperties::operator =(const LicenceProperties& other)
{
    mGenerationDateTime = other.mGenerationDateTime;
    mUser = other.mUser;
    mKey = other.mKey;
    mKeyType = other.mKeyType;
    mCustomer = other.mCustomer;
    mParameters = other.mParameters;
    mEndDateTime = other.mEndDateTime;
    cCurrentState = other.cCurrentState;
    cCpuid = other.cCpuid;
    cHaspKey = other.cHaspKey;
    cErrorCode = other.cErrorCode;

    return *this;
}

bool LicenceProperties::operator !=(LicenceProperties that)
{
    if (this->mGenerationDateTime == that.mGenerationDateTime &&
        this->mUser == that.mUser &&
        this->mKey == that.mKey &&
        this->mKeyType == that.mKeyType &&
        this->mCustomer == that.mCustomer &&
        this->mParameters == that.mParameters &&
        this->mEndDateTime == that.mEndDateTime &&
        this->cCurrentState == that.cCurrentState &&
        this->cCpuid == that.cCpuid &&
        this->cHaspKey == that.cHaspKey)
    {
        return false;
    }
    else
    {
        return true;
    }
}

}
