#ifndef QLOADDOCLINEWIDGET_H
#define QLOADDOCLINEWIDGET_H

#include <QWidget>
#include <QLabel>
#include "pictures/imagepickerandroid.h"
    #include <QFileDialog>

class QLoadDocLineWidget : public QWidget
{
    Q_OBJECT
public:
    explicit QLoadDocLineWidget(QString strLabel, bool noMarker = false , bool noView = false , QWidget *parent = nullptr , bool bSingleSelect = true);
    bool CheckColorData();
    void SetViewDone(bool);
    bool getImgStr(QString & imgStr);
    void SetImage(QString imgStr);


protected:
    QLabel * m_pLabel;
    QString m_StrLabelText;
    imagePickerAndroid * m_pImagePickerAndroid;
    QString m_strFileName;
    QString m_strImg;
    bool m_bSingleSelect;
    bool m_bNoMarker;//Автоматическки не выставлять маркер когда выбран путь
    QPushButton * m_pOpenButton;
    QPushButton * m_pPhotoButton;

#ifdef Q_OS_IOS
    void checkCameraPermission();
    //void checkAuthorizationStatus();
#endif
signals:
    void imageRecivedSignal(QString);
public slots:
    void OnPhotoPressed();
    void OnOpenPressed();
    void OnViewPressed();
    void imageRecivedSlot(QString);
};

#endif // QLOADDOCLINEWIDGET_H
