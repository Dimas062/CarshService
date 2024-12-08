#ifndef IMAGEPICKERANDROID_H
#define IMAGEPICKERANDROID_H

#include <QObject>
#ifdef Q_OS_ANDROID
#include <QtCore/private/qandroidextras_p.h>
#include <QJniObject>
#endif
class imagePickerAndroid : public QObject
#ifdef Q_OS_ANDROID
    , public QAndroidActivityResultReceiver
#endif
{
    Q_OBJECT
public:
    //imagePickerAndroid():QObject(parent),QAndroidActivityResultReceiver(){}

    void getImage();

    void takePhoto();

    static const int REQUEST_IMAGE_CAPTURE = 1;
    static const int REQUEST_TAKE_PHOTO = 2;
    static const int REQUEST_SHOW_PHOTO = 3;
#ifdef Q_OS_ANDROID
    virtual void handleActivityResult(int receiverRequestCode, int resultCode, const QJniObject & data) override;

   QJniObject* m_Activity;
#endif

signals:
    void imageRecivedSignal(QString);
};

#endif // IMAGEPICKERANDROID_H
