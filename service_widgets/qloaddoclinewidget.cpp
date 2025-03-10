#include "qloaddoclinewidget.h"
#include <QHBoxLayout>
#include <QPushButton>
#include <common.h>
#include "pictures/qfullscreenpicdialog.h"
#include <QImageReader>
#include <QStandardPaths>
#include <QFileDialog>
#include <QImageWriter>
#include <QMediaDevices>
#include <QCameraDevice>
#include <QCamera>
#include <QMediaCaptureSession>
#include <QImageCapture>
#include <QPermission>
#include <QThread>
#include "ios/QtPHPicker.h"
#include "ios/QtCameraPicker.h"

extern QRect screenGeometry;
extern int iButtonHeight;

QLoadDocLineWidget::QLoadDocLineWidget(QString strLabel, bool noMarker , bool noView, QWidget *parent , bool bSingleSelect): QWidget{parent}
{
    m_strImg = QString("");
    m_bNoMarker = noMarker;
    m_bSingleSelect = bSingleSelect;
 #ifdef Q_OS_ANDROID
    m_pImagePickerAndroid = new imagePickerAndroid();
    connect(m_pImagePickerAndroid, SIGNAL(imageRecivedSignal(QString)), this, SLOT(imageRecivedSlot(QString)));
#endif
    m_StrLabelText = strLabel;

    QHBoxLayout * pHBoxLayout = new QHBoxLayout;

    m_pLabel = new QLabel(strLabel);
    m_pLabel->setTextFormat(Qt::RichText);
    pHBoxLayout->addWidget(m_pLabel);

    if(noView == false)
    {
        QPushButton * pViewButton = new QPushButton(QIcon(":/icons/picture_icon.png"), "" , this);
        connect(pViewButton,SIGNAL(pressed()),this,SLOT(OnViewPressed()));
        pViewButton->setMaximumHeight(iButtonHeight);
        pViewButton->setIconSize(QSize(iButtonHeight*0.75,iButtonHeight*0.75));
        pViewButton->setMinimumHeight(iButtonHeight);
        pHBoxLayout->addWidget(pViewButton);
    }

    m_pOpenButton = new QPushButton(QIcon(":/icons/folder_open2.png"), "" , this);
    connect(m_pOpenButton,SIGNAL(pressed()),this,SLOT(OnOpenPressed()));
    m_pOpenButton->setIconSize(QSize(iButtonHeight*0.75,iButtonHeight*0.75));
    m_pOpenButton->setMaximumHeight(iButtonHeight);
    m_pOpenButton->setMinimumHeight(iButtonHeight);
    pHBoxLayout->addWidget(m_pOpenButton);

    m_pPhotoButton = new QPushButton(QIcon(":/icons/photo_icon.png"), "" , this);
    connect(m_pPhotoButton,SIGNAL(pressed()),this,SLOT(OnPhotoPressed()));
    m_pPhotoButton->setMaximumHeight(iButtonHeight);
    m_pPhotoButton->setMinimumHeight(iButtonHeight);
    m_pPhotoButton->setIconSize(QSize(iButtonHeight*0.75,iButtonHeight*0.75));
    pHBoxLayout->addWidget(m_pPhotoButton);

    //m_pOpenDlg = new QFileDialog();

    this->setLayout(pHBoxLayout);
}

#ifdef Q_OS_IOS
void QLoadDocLineWidget::checkCameraPermission(void)
{
#if QT_CONFIG(permissions)

    QCameraPermission cameraPermission;
    switch (qApp->checkPermission(cameraPermission)) {
    case Qt::PermissionStatus::Undetermined:
        qApp->requestPermission(cameraPermission, this, &QLoadDocLineWidget::checkCameraPermission);
        return;
    case Qt::PermissionStatus::Denied:
        qDebug() << "Разрешение на доступ к камере не предоставлено!";
        return;
    case Qt::PermissionStatus::Granted:
        qDebug() << "Разрешение на доступ к камере предоставлено!";
        break;
    }
#endif
}


void QLoadDocLineWidget::checkAuthorizationStatus(void)
{
#if QT_CONFIG(permissions)

    QCameraPermission cameraPermission;
    Qt::PermissionStatus auth_status = Qt::PermissionStatus::Undetermined;
    while(true)
    {
        QThread::msleep(1);
        auth_status = qApp->checkPermission(cameraPermission);

        if(auth_status == Qt::PermissionStatus::Undetermined)
            continue;

        break;
    }

#endif // if QT_CONFIG
}

#endif

void QLoadDocLineWidget::OnPhotoPressed()
{
    /*Проверка на разрешение*/
 #ifdef Q_OS_ANDROID
    int checkRes = IsCameraPrenissionAndRequest();
    if(checkRes!=1)
    {
        return;
    }

    m_pImagePickerAndroid->takePhoto();
 #endif

#ifdef Q_OS_IOS

    checkCameraPermission();

    m_pOpenButton->setEnabled(false);
    m_pPhotoButton->setEnabled(false);

    QtCameraPicker *pCameraDlg = QtCameraPicker::instance();

    QObject::disconnect(pCameraDlg, &QtCameraPicker::imageCaptured, nullptr, nullptr);
    QObject::disconnect(pCameraDlg, &QtCameraPicker::captureCancelled, nullptr, nullptr);

    connect(pCameraDlg, &QtCameraPicker::captureCancelled, this, [this]() {
        m_pOpenButton->setEnabled(true);
        m_pPhotoButton->setEnabled(true);
    });

    connect(pCameraDlg, &QtCameraPicker::imageCaptured, this, [this](const QString &path) {
        if (!path.isEmpty()) {

            imageRecivedSlot(path);

        } else {
            qDebug() << "Выбор отменен";
        }
        m_pOpenButton->setEnabled(true);
        m_pPhotoButton->setEnabled(true);
    });

    pCameraDlg->openCamera();



#endif
}



void QLoadDocLineWidget::OnOpenPressed()
{
#ifdef Q_OS_ANDROID
    m_pImagePickerAndroid->getImage();
#endif

#if defined Q_OS_IOS

    m_pOpenButton->setEnabled(false);
    m_pPhotoButton->setEnabled(false);

    QtPHPicker *pOpenDlg = QtPHPicker::instance();

    QObject::disconnect(pOpenDlg, &QtPHPicker::filesSelected, nullptr, nullptr);

    connect(pOpenDlg, &QtPHPicker::filesSelected, this, [this](const QStringList &paths) {
        if (!paths.isEmpty()) {
            //int i =0;
            for (const QString &path : paths) {
                //qDebug() << "File received:" << path<<" i="<<i++;
                imageRecivedSlot(path);
            }
        } else {
            qDebug() << "Выбор отменен";
        }
        m_pOpenButton->setEnabled(true);
        m_pPhotoButton->setEnabled(true);
    });

    pOpenDlg->openPicker(!m_bSingleSelect);

#endif
}

bool QLoadDocLineWidget::getImgStr(QString & imgStr)
{
    imgStr = m_strImg;
    if(imgStr.length()> 3) return true;
    return false;
}

void QLoadDocLineWidget::SetImage(QString imgStr)
{
    m_strImg = imgStr;
}

void QLoadDocLineWidget::SetViewDone(bool bDone)
{
    if(!bDone)
    {
        m_pLabel->setStyleSheet("QLabel { color : red; }");
        m_pLabel->setText(QString(m_StrLabelText));
    }
    else
    {
        m_pLabel->setStyleSheet("QLabel { color : black; }");
        m_pLabel->setText(QString("%1 <img src=\":/icons/done_icon.png\" width=\"15\" height=\"15\">").arg(m_StrLabelText));
    }
}

bool QLoadDocLineWidget::CheckColorData()
{
    if(m_strImg.size()<3)
    {
        m_pLabel->setStyleSheet("QLabel { color : red; }");
        m_pLabel->setText(QString(m_StrLabelText));
        return false;
    }
    else
    {
        m_pLabel->setStyleSheet("QLabel { color : black; }");
        m_pLabel->setText(QString("%1 <img src=\":/icons/done_icon.png\" width=\"15\" height=\"15\">").arg(m_StrLabelText));
    }
    return true;
}

void QLoadDocLineWidget::OnViewPressed()
{
    QImage CurrentImage = Base64ToImage(m_strImg);

    QFullScreenPicDialog dlg(&CurrentImage);
    dlg.exec();
}


void QLoadDocLineWidget::imageRecivedSlot(QString str)
{
    m_strFileName = str;

    if(m_strFileName.length() > 5)
    {
        if(m_bNoMarker == false)
        {
            SetViewDone(true);
        }

        emit imageRecivedSignal(m_strFileName);

        m_strImg = PictureFileToBase64(m_strFileName);
    }
}
