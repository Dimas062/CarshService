QT +=core gui sql network core-private gui-private core5compat multimedia# multimediawidgets #quick

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets concurrent

CONFIG += c++17

VERSION = 0.1.25

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
    emploee_widgets/qemploeeinputtasksdlg.cpp \
    emploee_widgets/qemploeemaindlg.cpp \
    emploee_widgets/qemplsalarydlg.cpp \
    emploee_widgets/QSelectTaskEmploeer.cpp \
    main.cpp \
    native.cpp \
    partners/plates/qplatepartnermaindlg.cpp \
    partners/plates/qplatepartnertask.cpp \
    partners/plates/qplatepartnertaskslistdlg.cpp \
    partners/sticks/qstickpartnermaindlg.cpp \
    partners/sticks/qstickpartnertask.cpp \
    partners/sticks/qstickpartnertaskslistdlg.cpp \
    partners/wash/qcsselectwashtypesswidget.cpp \
    partners/wash/qcswashtypedlg.cpp \
    partners/wash/qcswashtypeselectdlg.cpp \
    partners/wash/qwashpartnermaindlg.cpp \
    partners/wash/qwashpartnerpendlg.cpp \
    partners/wash/qwashpartnerpenlistdlg.cpp \
    partners/wash/qwashpartnertask.cpp \
    partners/wash/qwashpartnertaskslistdlg.cpp \
    pictures/qpictureswidget.cpp \
    qsocketbd.cpp \
    qsocketbdnetclient.cpp \
    register_dlgs/qregisterpartnerstickdlg.cpp \
    register_dlgs/qregisterpartnerwashdlg.cpp \
    service_widgets/qclicablelabel.cpp \
    service_widgets/qcolumntext.cpp \
    service_widgets/qcsbasedialog.cpp \
    service_widgets/qcsbasedlgscrollwidget.cpp \
    service_widgets/qcsbaselistitemdelegate.cpp \
    service_widgets/qcsbaselistwidget.cpp \
    service_widgets/qcspaybasedialog.cpp \
    service_widgets/qcsscrollarea.cpp \
    service_widgets/qcsselectdialog.cpp \
    service_widgets/qcsselectdlgbuttonswidget.cpp \
    service_widgets/qfinddlg.cpp \
    service_widgets/qlinetext.cpp \
    service_widgets/qloaddoclinewidget.cpp \
    qregisterdlg.cpp \
    register_dlgs/qregisteremploeedlg.cpp \
    register_dlgs/qregisterpartnerPlatedlg.cpp \
    service_widgets/qcalendardataselectdlg.cpp \
    service_widgets/qloaddocsdlg.cpp \
    service_widgets/qmonthselectdlg.cpp \
    service_widgets/qnotecalendarwidget.cpp \
    qsettingsdlg.cpp \
    service_widgets/QCSButton.cpp \
    service_widgets/qparnerpointdlg.cpp \
    service_widgets/qpointlistdlg.cpp \
    service_widgets/qselprovidercarshwidget.cpp \
    service_widgets/qtimeselectdlg.cpp \
    qcarshservicebasewidget.cpp \
    pictures/imagepickerandroid.cpp \
    pictures/imagewidget.cpp \
    pictures/qfullscreenpicdialog.cpp \
    pictures/qpiclabel.cpp \
    service_widgets/qcolorselectdlg.cpp \
    qcarshserviceapplication.cpp \
    service_widgets/quldlg.cpp \
    service_widgets/qyesnodlg.cpp \
    settings_widgets/qsettingslistwidget.cpp \
    tasks/qcostsdialog.cpp \
    tasks/qdocstaskdlg.cpp \
    tasks/qparkingtaskdialog.cpp \
    tasks/qpenaltyparkingdialog.cpp \
    tasks/qplatetaskdialog.cpp \
    tasks/qrettozonedialog.cpp \
    tasks/qsmenadlg.cpp

ios {
SOURCES += \
    service_widgets/ios/CameraWrapper.mm \
    service_widgets/ios/PHPickerWrapper.mm \
    service_widgets/ios/QtCameraPicker.mm \
    service_widgets/ios/QtPHPicker.mm \
}

HEADERS += \
    BDPatterns.h \
    carsh_service_widgets/qcarshcarddlg.h \
    carsh_service_widgets/qcarshserviceemploeecarddlg.h \
    carsh_service_widgets/qcarshservicemaindlg.h \
    carsh_service_widgets/qcarshserviceusersdlg.h \
    common.h \
    emploee_widgets/QEmploeeTasksDlg.h \
    emploee_widgets/qemplcostsdlg.h \
    emploee_widgets/qemploeeinputtasksdlg.h \
    emploee_widgets/qemploeemaindlg.h \
    emploee_widgets/qemplsalarydlg.h \
    emploee_widgets/QSelectTaskEmploeer.h \
    native.h \
    partners/plates/qplatepartnermaindlg.h \
    partners/plates/qplatepartnertask.h \
    partners/plates/qplatepartnertaskslistdlg.h \
    partners/sticks/qstickpartnermaindlg.h \
    partners/sticks/qstickpartnertask.h \
    partners/sticks/qstickpartnertaskslistdlg.h \
    partners/wash/qcsselectwashtypesswidget.h \
    partners/wash/qcswashtypedlg.h \
    partners/wash/qcswashtypeselectdlg.h \
    partners/wash/qwashpartnermaindlg.h \
    partners/wash/qwashpartnerpendlg.h \
    partners/wash/qwashpartnerpenlistdlg.h \
    partners/wash/qwashpartnertask.h \
    partners/wash/qwashpartnertaskslistdlg.h \
    pictures/qpictureswidget.h \
    qsocketbd.h \
    qsocketbdnetclient.h \
    register_dlgs/qregisterpartnerstickdlg.h \
    register_dlgs/qregisterpartnerwashdlg.h \
    service_widgets/qclicablelabel.h \
    service_widgets/qcolumntext.h \
    service_widgets/qcsbasedialog.h \
    service_widgets/qcsbasedlgscrollwidget.h \
    service_widgets/qcsbaselistitemdelegate.h \
    service_widgets/qcsbaselistwidget.h \
    service_widgets/qcspaybasedialog.h \
    service_widgets/qcsscrollarea.h \
    service_widgets/qcsselectdialog.h \
    service_widgets/qcsselectdlgbuttonswidget.h \
    service_widgets/qfinddlg.h \
    service_widgets/qlinetext.h \
    service_widgets/qloaddoclinewidget.h \
    qregisterdlg.h \
    register_dlgs/qregisteremploeedlg.h \
    register_dlgs/qregisterpartnerPlatedlg.h \
    service_widgets/qcalendardataselectdlg.h \
    service_widgets/qloaddocsdlg.h \
    service_widgets/qmonthselectdlg.h \
    service_widgets/qnotecalendarwidget.h \
    qsettingsdlg.h \
    service_widgets/QCSButton.h \
    service_widgets/qparnerpointdlg.h \
    service_widgets/qpointlistdlg.h \
    service_widgets/qselprovidercarshwidget.h \
    service_widgets/qtimeselectdlg.h \
    qcarshservicebasewidget.h \
    pictures/imagepickerandroid.h \
    pictures/imagewidget.h \
    pictures/qfullscreenpicdialog.h \
    pictures/qpiclabel.h \
    service_widgets/qcolorselectdlg.h \
    qcarshserviceapplication.h \
    service_widgets/quldlg.h \
    service_widgets/qyesnodlg.h \
    settings_widgets/qsettingslistwidget.h \
    tasks/qcostsdialog.h \
    tasks/qdocstaskdlg.h \
    tasks/qparkingtaskdialog.h \
    tasks/qpenaltyparkingdialog.h \
    tasks/qplatetaskdialog.h \
    tasks/qrettozonedialog.h \
    tasks/qsmenadlg.h

ios {
    HEADERS += \
    service_widgets/ios/CameraWrapper.h \
    service_widgets/ios/PHPickerWrapper.h \
    service_widgets/ios/QtCameraPicker.h \
    service_widgets/ios/QtPHPicker.h \
}

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target


 ios {
     #QTPLUGIN += qiosnsphotolibrarysupport
     QMAKE_OBJCFLAGS += -fobjc-arc
     # убрать вместе с выбором просто файлов видимо -framework Foundation
     #LIBS += -framework PhotosUI -framework UIKit -framework MobileCoreServices
    LIBS += -framework PhotosUI
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

    #Магия про версию из интернета не работает
    # androidmanifestupdate.commands =  sed -i \'\' -E -e \'s/(versionName=)(\"([0-9]\.?)+\")/\\1\"$$VERSION\"/g\' $$ANDROID_PACKAGE_SOURCE_DIR/AndroidManifest.xml
    # QMAKE_EXTRA_TARGETS += androidmanifestupdate
    # PRE_TARGETDEPS += androidmanifestupdate
    }
}

RESOURCES += \
    resources.qrc

DISTFILES += \
    ios/Info.plist
