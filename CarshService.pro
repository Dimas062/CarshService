QT +=core gui sql network core-private gui-private core5compat multimedia# multimediawidgets #quick

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17


VERSION = 0.1.4

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    BDPatterns.cpp \
    carsh_service_widgets/qcarshcarddlg.cpp \
    carsh_service_widgets/qcarshserviceemploeecarddlg.cpp \
    carsh_service_widgets/qcarshservicemaindlg.cpp \
    carsh_service_widgets/qcarshserviceusersdlg.cpp \
    common.cpp \
    emploee_widgets/QEmploeeTasksDlg.cpp \
    emploee_widgets/qemplcostsdlg.cpp \
    emploee_widgets/qemploeemaindlg.cpp \
    main.cpp \
    native.cpp \
    pictures/qpictureswidget.cpp \
    qsocketbd.cpp \
    qsocketbdnetclient.cpp \
    service_widgets/qclicablelabel.cpp \
    service_widgets/qcolumntext.cpp \
    service_widgets/qcsbasedialog.cpp \
    service_widgets/qcsbasedlgscrollwidget.cpp \
    service_widgets/qcsbaselistitemdelegate.cpp \
    service_widgets/qcsbaselistwidget.cpp \
    service_widgets/qcsmultiselectdlg.cpp \
    service_widgets/qcspaybasedialog.cpp \
    service_widgets/qcsscrollarea.cpp \
    service_widgets/qcsselectdialog.cpp \
    service_widgets/qcsselectdlgbuttonswidget.cpp \
    service_widgets/qlinetext.cpp \
    service_widgets/qloaddoclinewidget.cpp \
    qregisterdlg.cpp \
    qregisteremploeedlg.cpp \
    qregisterpartnerPlatedlg.cpp \
    service_widgets/qcalendardataselectdlg.cpp \
    service_widgets/qloaddocsdlg.cpp \
    service_widgets/qnotecalendarwidget.cpp \
    qsettingsdlg.cpp \
    service_widgets/QCSButton.cpp \
    service_widgets/qselprovidercarshwidget.cpp \
    service_widgets/qtimeselectdlg.cpp \
    qcarshservicebasewidget.cpp \
    pictures/imagepickerandroid.cpp \
    pictures/imagewidget.cpp \
    pictures/qfullscreenpicdialog.cpp \
    pictures/qpiclabel.cpp \
    service_widgets/qcolorselectdlg.cpp \
    qcarshserviceapplication.cpp \
    service_widgets/qyesnodlg.cpp \
    settings_widgets/qsettingslistwidget.cpp \
    tasks/qcostsdialog.cpp \
    tasks/qparkingtaskdialog.cpp \
    tasks/qpenaltyparkingdialog.cpp \
    tasks/qplatetaskdialog.cpp \
    tasks/qrettozonedialog.cpp

HEADERS += \
    BDPatterns.h \
    carsh_service_widgets/qcarshcarddlg.h \
    carsh_service_widgets/qcarshserviceemploeecarddlg.h \
    carsh_service_widgets/qcarshservicemaindlg.h \
    carsh_service_widgets/qcarshserviceusersdlg.h \
    common.h \
    emploee_widgets/QEmploeeTasksDlg.h \
    emploee_widgets/qemplcostsdlg.h \
    emploee_widgets/qemploeemaindlg.h \
    native.h \
    pictures/qpictureswidget.h \
    qsocketbd.h \
    qsocketbdnetclient.h \
    service_widgets/qclicablelabel.h \
    service_widgets/qcolumntext.h \
    service_widgets/qcsbasedialog.h \
    service_widgets/qcsbasedlgscrollwidget.h \
    service_widgets/qcsbaselistitemdelegate.h \
    service_widgets/qcsbaselistwidget.h \
    service_widgets/qcsmultiselectdlg.h \
    service_widgets/qcspaybasedialog.h \
    service_widgets/qcsscrollarea.h \
    service_widgets/qcsselectdialog.h \
    service_widgets/qcsselectdlgbuttonswidget.h \
    service_widgets/qlinetext.h \
    service_widgets/qloaddoclinewidget.h \
    qregisterdlg.h \
    qregisteremploeedlg.h \
    qregisterpartnerPlatedlg.h \
    service_widgets/qcalendardataselectdlg.h \
    service_widgets/qloaddocsdlg.h \
    service_widgets/qnotecalendarwidget.h \
    qsettingsdlg.h \
    service_widgets/QCSButton.h \
    service_widgets/qselprovidercarshwidget.h \
    service_widgets/qtimeselectdlg.h \
    qcarshservicebasewidget.h \
    pictures/imagepickerandroid.h \
    pictures/imagewidget.h \
    pictures/qfullscreenpicdialog.h \
    pictures/qpiclabel.h \
    service_widgets/qcolorselectdlg.h \
    qcarshserviceapplication.h \
    service_widgets/qyesnodlg.h \
    settings_widgets/qsettingslistwidget.h \
    tasks/qcostsdialog.h \
    tasks/qparkingtaskdialog.h \
    tasks/qpenaltyparkingdialog.h \
    tasks/qplatetaskdialog.h \
    tasks/qrettozonedialog.h



# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

 ios {
     #QTPLUGIN += qiosnsphotolibrarysupport


     QMAKE_TARGET_BUNDLE_PREFIX = "ru.dimas062"
     QMAKE_BUNDLE = "CarshService"
     TARGET = "CarshService"

     QMAKE_IOS_DEPLOYMENT_TARGET =14.0
     QMAKE_ASSET_CATALOGS += ios/Assets.xcassets

     QMAKE_INFO_PLIST = ios/Info.plist
 }

android {
    DISTFILES += \
        android/AndroidManifest.xml \
        android/build.gradle \
        android/gradle.properties \
        android/gradle/wrapper/gradle-wrapper.jar \
        android/gradle/wrapper/gradle-wrapper.properties \
        android/gradlew \
        android/gradlew.bat \
        android/res/values/libs.xml \
        android/res/values/strings.xml \
        #android/src/org/nlb/VideoSapiens/NoteBookBootReceiver.java \
        #android/src/org/nlb/VideoSapiens/NotificationActivity.java \
        #android/src/org/nlb/VideoSapiens/PermissionUtils.java \
        android/src/org/zlo/CarshService/QtAdMobActivity.java \
        Заметки


    contains(ANDROID_TARGET_ARCH,arm64-v8a) {
    #contains(ANDROID_TARGET_ARCH,armeabi-v7a) {
        ANDROID_PACKAGE_SOURCE_DIR = \
            $$PWD/android
    }
}

RESOURCES += \
    resources.qrc

DISTFILES += \
    ios/Info.plist
