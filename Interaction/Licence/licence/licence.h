/** @file
 *
 * \copyright   (c) CodLix LLC
 * \authors     Болотский Виктор
 * \version     1.0
 * \date        21.01.2022
 * Project:     VideoSystem
 * File:        licence.h
 *
 * @brief Класс лицензирования.
 *
 *
 */

#pragma once

#include <thread>
#include <atomic>
#include <mutex>

#include <QObject>
#include <QPainter>
#include <QPdfWriter>
#include <QTableWidget>
#include <QScrollBar>
#include <QHeaderView>
#include <QDateTime>
#include <QMutex>

#include "licence_global.h"


namespace Licensing
{

enum LICENCESHARED_EXPORT LicenceErrors : int {
    LeGood = 0x00000,                                 ///< Активна

    LeErrNoLicenceFileOnServer = 0x0001,              ///< Файл лицензии отсутствует на сервере
    LeErrVerifySignature = 0x0002,                    ///< Не удалось провести проверку подписи файла лицензии
    LeErrWrongCpuid = 0x0008,                         ///< Файл лицензии предназначен для другого ПК с CPUID =
    LeErrNoHaspPlugged = 0x0010,                      ///< Требуется физический носитель HASP ключа
    LeErrLicenceFileCorrupted = 0x0020,               ///< Файл лицензии повреждён
    LeError = LeErrNoLicenceFileOnServer | LeErrVerifySignature | LeErrWrongCpuid | LeErrNoHaspPlugged | LeErrLicenceFileCorrupted,

    LeWarnReadMotherboardSerial = 0x0004,             ///< Не удалось прочитать серийный номер материнской платы
    LeWarnServerNeedRights = 0x0040,                  ///< Сервер не обладает достаточными правами для чтения/записи
    LeWarnWrongHasp = 0x0080,                         ///< Файл лицензии предназначен для другого HASP ключа с ID =
    LeWarnNoHaspPlugged = 0x0100,                     ///< Требуется физический носитель HASP ключа с ID =
    LeWarnNoHaspDriver = 0x0200,                      ///< Произошла ошибка проверки HASP ключа, проверьте драйвер
    LeWarnLicenceExpired = 0x0400,                    ///< Срок действия лицензии истёк
    LeWarning = LeWarnReadMotherboardSerial | LeWarnServerNeedRights | LeWarnWrongHasp | LeWarnNoHaspPlugged | LeWarnNoHaspDriver | LeWarnLicenceExpired,

    LeOverCams = 0x0800,                              ///< Превышение разрешённого количества подключённых камер
    LeOverClients = 0x1000,                           ///< Превышение разрешённого количества подключённых клиентов
    LeOverCashboxes = 0x2000,                         ///< Превышение разрешённого количества подключённых касс
    LeOverPluginsCleanHands = 0x4000,                 ///< Превышение разрешённого количества подключённых плагинов ЧР
    LeOverPluginsFaceDet = 0x8000,                    ///< Превышение разрешённого количества подключённых плагинов ФД
    LeOver = LeOverCams | LeOverClients | LeOverCashboxes | LeOverPluginsCleanHands | LeOverPluginsFaceDet,

    LeEdgeCams = 0x10000,                             ///< Граничное количество подключённых камер
    LeEdgeCashboxes = 0x20000,                        ///< Граничное количество подключённых касс
    LeEdgePluginsCleanHands = 0x40000,                ///< Граничное количество подключённых плагинов ЧР
    LeEdgePluginsFaceDet = 0x80000                    ///< Граничное количество подключённых плагинов ФД
};

struct LICENCESHARED_EXPORT LicenceProperties {

    LicenceProperties();
    LicenceProperties(const QDateTime& generationDateTime,
                      const QString& user,
                      const QString& key,
                      bool keyType,
                      const QString& customer,
                      const QString& parameters,
                      const QDateTime& endDateTime,
                      const QString& currentState,
                      const QString& cpuId,
                      const QString& haspKey,
                      const LicenceErrors& licenceErrors);
    LicenceProperties(const LicenceProperties& other);
    LicenceProperties& operator =(const LicenceProperties &other);

    QDateTime mGenerationDateTime;              ///< Дата создания файла
    QString mUser;                              ///< user
    QString mKey;                               ///< Ключ (HASP/cpuid)
    bool mKeyType;                              ///< Тип ключа (0/1 - HASP/SOFT)
    QString mCustomer;                          ///< Заказчик
    QString mParameters;                        ///< параметры
    QDateTime mEndDateTime;                     ///< Дата окончания
    QString cCurrentState;                      ///< Текущее состояние сервера лицензирования
    QString cCpuid;                             ///< CPUID сервера
    QString cHaspKey;                           ///< Текущий подключённый ключ
    LicenceErrors cErrorCode;                   ///< Ошибка

    bool operator != (LicenceProperties that);
};

class LICENCESHARED_EXPORT Licence : public QObject
{
    Q_OBJECT
public:

    QString getPcCpuId();

    Q_INVOKABLE Licensing::LicenceProperties readLicence();

    static Licence& getInstance();

    QString getErrorMessageByCode(LicenceErrors le,
                                  Licensing::LicenceProperties mCurrentLicence);

    bool isIncludedInEnum(LicenceErrors value, LicenceErrors mask);

    bool isEnumContains(LicenceErrors value, LicenceErrors etalon);

signals:

private:

    void getcpuid( unsigned int CPUInfo[4], unsigned int InfoType);
    void getcpuidex(unsigned int CPUInfo[4], unsigned int InfoType, unsigned int ECXValue);
    quint64 get_cpuId();

    LicenceProperties mLicence;
    QDateTime lastModified = QDateTime();

    Licence();
    ~Licence();
    Licence(Licence const&) = delete;
    Licence& operator= (Licence const&) = delete;
};

}
