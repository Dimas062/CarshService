/** @file
\copyright   (c) CodLix LLC
\authors     Колосов В.В.
\version     1.0
Project:     VideoSystem
File:        interactionprotocoltypes.h
* @brief     Протокол взаимодействия клиента с сервером. Описание списка всех типов.
**/
#ifndef INTERACTIONPROTOCOLTYPES_H
#define INTERACTIONPROTOCOLTYPES_H

#include <QObject>

/// \brief сдвиг для генерации ответного (response) типа
#define RESPONSE_SHIFT 16


enum ServerCategory : quint8
{
    SC_UNKNOWN = 0,
    SC_MAIN,
    SC_CENTRAL,
    SC_UNITED
};
Q_DECLARE_METATYPE(ServerCategory)

///
/// \brief The EDataType enum идентификатор типа данных
///
enum class EDataType : quint32 {
    None = 0,
    /// \remark запросы/ответы - действия с пользователями
    RequestAuthorization = 1,                                                           ///< авторизация - запрос
    ResponseAuthorization = RequestAuthorization << RESPONSE_SHIFT,                     ///< авторизация - ответ
    RequestSetStreamsUrls = 2,                                                          ///< установить список урлов потоков - запрос
    ResponseSetStreamsUrls = RequestSetStreamsUrls << RESPONSE_SHIFT,                   ///< установить список урлов потоков - ответ
    /// \remark управление параметрами сервера
    RequestSetConfigParam = 3, ///< установить параметр
    RequestGetConfigParam = 4, ///< получить параметр
    ResponseSetConfigParam = RequestSetConfigParam << RESPONSE_SHIFT, ///< установить параметр
    ResponseGetConfigParam = RequestGetConfigParam << RESPONSE_SHIFT, ///< получить параметр
    /// \remark файловая система сервера
    RequestDirectoryContent = 10,                                                       ///< запрос - получить содержимое директории на сервере
    ResponseDirectoryContent = RequestDirectoryContent << RESPONSE_SHIFT,               ///< ответ - получить содержимое директории на сервере
    RequestUpdateVirtualPath = 11,                                                       ///< запрос - обновить виртуальные пути на сервере
    ResponseUpdateVirtualPath = RequestUpdateVirtualPath << RESPONSE_SHIFT,               ///< ответ - обновить виртуальные пути на сервере
    /// \remark запросы/ответы - действия с камерами
    RequestListFreeCameras = 200,                                                       ///< получить список свободных (неприкреплённых) камер - запрос
    ResponseListFreeCameras = RequestListFreeCameras << RESPONSE_SHIFT,                 ///< получить список свободных (неприкреплённых) камер - ответ
    RequestListAvailableCameras = 201,                                                  ///< получить список доступных (подключенных к серверу) камер - запрос
    ResponseListAvailableCameras = RequestListAvailableCameras << RESPONSE_SHIFT,       ///< получить список доступных (подключенных к серверу) камер - ответ
    RequestListCamerasByZone = 202,                                                     ///< получить список камер для заданной зоны - запрос
    ResponseListCamerasByZone = RequestListCamerasByZone << RESPONSE_SHIFT,             ///< получить список камер для заданной зоны - ответ
    RequestStartRtspStreamCamera = 203,                                                 ///< создать и запустить вещание RTSP поток для заданного потока камеры - запрос
    ResponseStartRtspStreamCamera = RequestStartRtspStreamCamera << RESPONSE_SHIFT,     ///< создать и запустить вещание RTSP поток для заданного потока камеры - ответ
    RequestStopRtspStreamCamera = 204,                                                  ///< остановить вещание и удалить RTSP поток для заданного потока камеры - запрос
    ResponseStopRtspStreamCamera = RequestStopRtspStreamCamera << RESPONSE_SHIFT,       ///< остановить вещание и удалить RTSP поток для заданного потока камеры - ответ
    RequestAttachCameraToZone = 205,                                                    ///< прикрепить камеру к заданной зоне - запрос
    ResponseAttachCameraToZone = RequestAttachCameraToZone << RESPONSE_SHIFT,           ///< прикрепить камеру к заданной зоне - ответ
    RequestCameraInfo = 206,                                                            ///< инфо о камере - запрос
    ResponseCameraInfo = RequestCameraInfo << RESPONSE_SHIFT,                           ///< инфо о камере - ответ
    RequestStreamCameraStatus = 207,                                                    ///< статус потока камеры - запрос
    ResponseStreamCameraStatus = RequestStreamCameraStatus << RESPONSE_SHIFT,           ///< статус потока камеры - ответ
    RequestStreamCameraType = 208,                                                      ///< тип потока камеры - запрос
    ResponseCameraStreamType = RequestStreamCameraType << RESPONSE_SHIFT,               ///< тип потока камеры - ответ
    RequestStreamCameraStatusList = 209,                                                ///< список статусов потоков камеры - запрос
    ResponseStreamCameraStatusList = RequestStreamCameraStatusList << RESPONSE_SHIFT,   ///< список статусов потоков камеры - ответ
    RequestStreamCameraTypeList = 210,                                                  ///< список типов потоков камеры - запрос
    ResponseCameraStreamTypeList = RequestStreamCameraTypeList << RESPONSE_SHIFT,       ///< список типов потоков камеры  - ответ
    RequestServerList = 211,                                                            ///< список серверов - запрос
    ResponseServerList = RequestServerList << RESPONSE_SHIFT,                           ///< список серверов  - ответ
    /// \remark запросы/ответы - действия с архивными видео
    RequestListArhiveVideoByStreamCamera = 300,                                         ///< получить список видеозаписей для заданного потока камеры - запрос
    ResponseListArhiveVideoByStreamCamera = RequestListArhiveVideoByStreamCamera << RESPONSE_SHIFT, ///< получить список видеозаписей для заданного потока камеры - ответ
    RequestCreateRtspStreamVideo = 301,                                                 ///< создать RTSP поток для архивного видео - запрос
    ResponseCreateRtspStreamVideo = RequestCreateRtspStreamVideo << RESPONSE_SHIFT,     ///< создать RTSP поток для архивного видео - ответ
    RequestStartRtspStreamVideo = 302,                                                  ///< запустить вещание RTSP поток для архивного видео - запрос
    ResponseStartRtspStreamVideo = RequestStartRtspStreamVideo << RESPONSE_SHIFT,       ///< запустить вещание RTSP поток для архивного видео - ответ
    RequestStopRtspStreamVideo = 303,                                                   ///< остановить вещание и удалить RTSP поток для архивного видео - запрос
    ResponseStopRtspStreamVideo = RequestStopRtspStreamVideo << RESPONSE_SHIFT,         ///< остановить вещание и удалить RTSP поток для архивного видео - ответ

    /// \remark запросы/ответы - бэкапы
    RequestBackupList = 390,                                  ///< Получить список бэкапов - запрос
    ResponseBackupList = RequestBackupList << RESPONSE_SHIFT, ///< Получить список бэкапов - ответ

    RequestApplyBackup = 389,                                   ///< Применить бэкап - запрос
    ResponseApplyBackup = RequestApplyBackup << RESPONSE_SHIFT, ///< Применить бэкап - ответ

    RequestCreateBackup = 388,                                    ///< Создать бэкап - запрос
    ResponseCreateBackup = RequestCreateBackup << RESPONSE_SHIFT, ///< Создать бэкап - ответ

    RequestStateBackup = 391,                                    ///< Состояние бэкапа - запрос
    ResponseStateBackup = RequestStateBackup << RESPONSE_SHIFT,  ///< Состояние бэкапа - ответ

    /// \remark запросы - взаимодействие с видеорегистраторами (VR - VideoRecorder)
    RequestCreateRtspStreamVideoVR      = 400,      ///< создание трансляции архива
    RequestStartRtspStreamVideoVR       = 401,      ///< старт трансляции архива
    RequestStopRtspStreamVideoVR        = 402,      ///< останов трансляции архива
    RequestStartRtspStreamCameraVR      = 403,      ///< старт живого видео
    RequestStopRtspStreamCameraVR       = 404,      ///< останов живого видео
    RequestGetExistingArchiveTimelineVR = 405,      ///< получение наличия архива по интервалу
    RequestGetRecordingScheduleVR       = 406,      ///< получение расписания записи
    RequestSetRecordingScheduleVR       = 407,      ///< установка расписания записи
    RequestStartRecordVR                = 408,      ///< старт записи
    RequestStopRecordVR                 = 409,      ///< стоп записи
    RequestExportArchiveVR              = 410,      ///< экспорт видеоархива
    RequestGetChannelsVR                = 411,      ///< экспорт видеоархива
    RequestGetExistingArchiveTimelinesOfStreamsVR = 412,
    RequestDeleteTmpVideoFilesVR        = 413,
    RequestDownloadFragmentVR           = 414,
    RequestStopDownloadFragmentVR       = 418,
    /// \remark ответы - взаимодействие с видеорегистраторами (VR - VideoRecorder)
    ResponseCreateRtspStreamVideoVR      = RequestCreateRtspStreamVideoVR << RESPONSE_SHIFT,        ///< создание трансляции архива
    ResponseStartRtspStreamVideoVR       = RequestStartRtspStreamVideoVR << RESPONSE_SHIFT,         ///< старт трансляции архива
    ResponseStopRtspStreamVideoVR        = RequestStopRtspStreamVideoVR << RESPONSE_SHIFT,          ///< останов трансляции архива
    ResponseStartRtspStreamCameraVR      = RequestStartRtspStreamCameraVR << RESPONSE_SHIFT,        ///< старт живого видео
    ResponseStopRtspStreamCameraVR       = RequestStopRtspStreamCameraVR << RESPONSE_SHIFT,         ///< останов живого видео
    ResponseGetExistingArchiveTimelineVR = RequestGetExistingArchiveTimelineVR << RESPONSE_SHIFT,      ///< получение наличия архива по интервалу
    ResponseGetRecordingScheduleVR       = RequestGetRecordingScheduleVR << RESPONSE_SHIFT,         ///< получение расписания записи
    ResponseSetRecordingScheduleVR       = RequestSetRecordingScheduleVR << RESPONSE_SHIFT,         ///< установка расписания записи
    ResponseStartRecordVR                = RequestStartRecordVR << RESPONSE_SHIFT,                  ///< старт записи
    ResponseStopRecordVR                 = RequestStopRecordVR << RESPONSE_SHIFT,                   ///< стоп записи
    ResponseExportArchiveVR              = RequestExportArchiveVR << RESPONSE_SHIFT,                ///< экспорт видеоархива
    ResponseGetChannelsVR                = RequestGetChannelsVR << RESPONSE_SHIFT,                  ///< получить каналы видеорегистратора
    ResponseGetExistingArchiveTimelinesOfStreamsVR = RequestGetExistingArchiveTimelinesOfStreamsVR << RESPONSE_SHIFT,
    ResponseDeleteTmpVideoFilesVR        = RequestDeleteTmpVideoFilesVR << RESPONSE_SHIFT,
    ResponseDownloadFragmentStartedVR    = RequestDownloadFragmentVR << RESPONSE_SHIFT,
    ResponseDownloadFragmentProgressVR   = (RequestDownloadFragmentVR << RESPONSE_SHIFT) + 1,
    ResponseDownloadFragmentFinishedVR   = (RequestDownloadFragmentVR << RESPONSE_SHIFT) + 2,
    ResponseDownloadFragmentErrorVR      = (RequestDownloadFragmentVR << RESPONSE_SHIFT) + 3,
    ResponseStopDownloadFragmentVR       = RequestStopDownloadFragmentVR << RESPONSE_SHIFT,
    RequestUpdate = 513,
    ResponseUpdate = RequestUpdate << RESPONSE_SHIFT,
    RequestFaceUpdate = 514,
    ResponseFaceUpdate = RequestFaceUpdate << RESPONSE_SHIFT,
    /// \remark запрос/ответ - лицензия
    RequestLicence = 600,                                                               ///< лицензия основного сервера - запрос
    ResponseLicence = RequestLicence << RESPONSE_SHIFT,                                 ///< лицензия основного сервера - ответ
    RequestGetClients = 601,                                                            ///< список клиентов - запрос
    ResponseGetClients = RequestGetClients << RESPONSE_SHIFT,                           ///< список клиентов - ответ
    RequestKickClient = 602,                                                            ///< отключи клиента - запрос
    ResponseKickClient = RequestKickClient << RESPONSE_SHIFT,                           ///< отключи клиента - ответ
    RequestLicenceThroughCs = 603,                                                      ///< лицензия основного сервера через ЦС - запрос
    ResponseLicenceThroughCs = RequestLicenceThroughCs << RESPONSE_SHIFT,               ///< лицензия основного сервера через ЦС - ответ
    RequestCopyVideoFileToTmp = 701,                                                    ///< скопируй файл во временный (для экспорта пишущегося) - запрос
    ResponseCopyVideoFileToTmp = RequestCopyVideoFileToTmp << RESPONSE_SHIFT,           ///< скопируй файл во временный (для экспорта пишущегося) - ответ
    RequestDeleteTmpVideoFiles = 702,                                                   ///< удали временные файлы, использованные для экспорта - запрос
    ResponseDeleteTmpVideoFiles = RequestDeleteTmpVideoFiles << RESPONSE_SHIFT,         ///< удали временные файлы, использованные для экспорта - ответ
    /// \reamrk лента скриншотов
    RequestGetMiniScreenshots = 750,                                                    ///< Запрос "Список мини-скиншотов"
    ResponseGetMiniScreenshots = RequestGetMiniScreenshots << RESPONSE_SHIFT,           ///< Ответ "Список мини-скиншотов"
    RequestGetScreenshot = 751,                                                         ///< Запрос "Полноразмерный скриншот"
    ResponseGetScreenshot = RequestGetScreenshot << RESPONSE_SHIFT,                     ///< Ответ "Полноразмерный скриншот"
    /// \reamrk лента скриншотов (VR - VideoRecorder)
    RequestGetMiniScreenshotsVR = 752,                                                  ///< Запрос "Список мини-скиншотов"
    ResponseGetMiniScreenshotsVR = RequestGetMiniScreenshotsVR << RESPONSE_SHIFT,       ///< Ответ "Список мини-скиншотов"
    RequestGetScreenshotVR = 753,                                                       ///< Запрос "Полноразмерный скриншот"
    ResponseGetScreenshotVR = RequestGetScreenshotVR << RESPONSE_SHIFT,                 ///< Ответ "Полноразмерный скриншот"
    /// \remark РАЗНОЕ
    RequestKickselfToClient,
    RequestHeartbeat,
    RequestUseVideoStream,                                                              ///< извещение пка об использовании видеопотока
    RequestResetStreams,                                                                ///< указание от СА в РК - перезапусти запись и перезапроси потоки

    /// \remark Camera Manage
    RequestGetCameraParameters,
    ResponseGetCameraParameters,
    RequestSetCameraParameters,
    ResponseSetCameraParameters,
    RequestRebootCamera,
    ResponseRebootCamera,

    /// \remark команды для/от РК
    RequestRestartStreamWriter,                                                         ///< команда рестарт писателя потока в РК
    RequestFreeFile,                                                                    ///< команда от РК в СА - освободи файл
    RequestEventNotification,                                                           ///< извещение о событии

    /// \remark ответ ResponseBadRequest
    ResponseBadRequest = 32769,                                                         ///< ответ на запрос - ошибка
    /// \remark подсистема оповещений от интеллектуальных модулей
    InteractionProtocolEvent,                                                           ///< события от интеллектуальных плагинов
    InteractionProtocolNotification,                                                    ///< оповещения от интеллектуальных плагинов
    InteractionProtocolIamPluginContainer,                                              ///< я - плагин-контейнер
    InteractionProtocolFilter,                                                          ///< управление разрешением трансляции оповещений плагин-контейнера
    InteractionProtocolCassyEvent,
    InteractionProtocolIamClient,
    InteractionProtocolHeartbeat,                                                       ///< heartbeat-сообщение
    /// \remark вспомогательные типы данных
    AvailableCameraProperties,                                                          ///< свойства обнаруженной камеры
    ZoneProperties,                                                                     ///< свойства зоны
    UserProperties,                                                                     ///< свойства пользователя
    NewZone,                                                                            ///< новая зона
    Group,                                                                              ///< группа
    AccessRightProperties,                                                              ///< свойства права доступа
    VideoProperties,                                                                    ///< свойства видеозаписи
    CameraProperties,                                                                   ///< свойства камеры
    StreamCameraProperties,                                                             ///< свойства потока камеры
    GroupProperties,                                                                    ///< свойства группы
    LayoutProperties,                                                                   ///< свойства раскладки
    UserProfileProperties,                                                              ///< свойства профиля пользователя
    LayoutItemProperties,                                                               ///< свойства элемента раскладки
    ProfileItemProperties,                                                              ///< свойства элемента профиля
    StreamCameraStatusProperties,                                                       ///< свойства статуса потока камеры
    StreamCameraTypeProperties,                                                         ///< свойства типа потока камеры
    ServerProperties,                                                                   ///< свойства сервера
    LicenceProperties,                                                                  ///< свойства лицензии
    ClientProperties,                                                                   ///< свойства клиента
    VRGetTimelineRequestParameters,                                                     ///< Параметры запроса шкалы архива видеорегистратора
    End
};

///
/// \brief The EResult enum результат операции
///
enum class EResult {
    None = 0,
    Good,
    Bad,
    NotRealised
};

///
/// \brief The EUserRole enum роли пользователя
///
enum class EUserRole : quint32 {
    None = 0,
    Observation,    ///< наблюдение
    Analytics,      ///< аналитика
    Administration,  ///< администрирование
    Security        ///< безопасность
};

///
/// \brief The EClientType enum тип клиента
///
enum class EClientType : quint32 {
    None = 0,
    ClientApp,  ///< клиент апп - нормальный клиент
    System,     ///< сервисный клиент (рекорд)
    PluginContainer ///< сервисный клиент (плагин)
};

enum class EServerConfigParam {
    None = 0,
    CentralIp
};

#endif // INTERACTIONPROTOCOLTYPES_H
