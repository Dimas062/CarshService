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

extern QRect screenGeometry;
extern int iButtonHeight;

QLoadDocLineWidget::QLoadDocLineWidget(QString strLabel, bool noMarker , bool noView, QWidget *parent): QWidget{parent}
{
    m_bNoMarker = noMarker;

    m_pImagePickerAndroid = new imagePickerAndroid();
    connect(m_pImagePickerAndroid, SIGNAL(imageRecivedSignal(QString)), this, SLOT(imageRecivedSlot(QString)));

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

    QPushButton * pOpenButton = new QPushButton(QIcon(":/icons/folder_open2.png"), "" , this);
    connect(pOpenButton,SIGNAL(pressed()),this,SLOT(OnOpenPressed()));
    pOpenButton->setIconSize(QSize(iButtonHeight*0.75,iButtonHeight*0.75));
    pOpenButton->setMaximumHeight(iButtonHeight);
    pOpenButton->setMinimumHeight(iButtonHeight);
    pHBoxLayout->addWidget(pOpenButton);

    QPushButton * pPhotoButton = new QPushButton(QIcon(":/icons/photo_icon.png"), "" , this);
    connect(pPhotoButton,SIGNAL(pressed()),this,SLOT(OnPhotoPressed()));
    pPhotoButton->setMaximumHeight(iButtonHeight);
    pPhotoButton->setMinimumHeight(iButtonHeight);
    pPhotoButton->setIconSize(QSize(iButtonHeight*0.75,iButtonHeight*0.75));
    pHBoxLayout->addWidget(pPhotoButton);

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
    checkAuthorizationStatus();
    QCamera * camera = new QCamera(QCameraDevice::BackFace);
    if(camera)
    {
        QMediaCaptureSession captureSession;
        captureSession.setCamera(camera);
        QImageCapture * pImageCapture = new QImageCapture;
        captureSession.setImageCapture(pImageCapture);

        camera->start();

        pImageCapture->captureToFile();
       // pImageCapture->
    }

#endif


}



void QLoadDocLineWidget::OnOpenPressed()
{
#ifdef Q_OS_ANDROID
    m_pImagePickerAndroid->getImage();
#endif

#ifdef Q_OS_IOS

    // QStringList files = QFileDialog::getOpenFileNames(
    //     this,
    //     "Select one or more files to open",
    //     "/home",
    //     "Images (*.png *.xpm *.jpg)");


    // return;


    qDebug()<<"QLoadDocLineWidget::OnOpenPressed()";

    QFileDialog dialog;

    QFileDialog::AcceptMode acceptMode = QFileDialog::AcceptOpen;
    const QStringList picturesLocations = QStandardPaths::standardLocations(QStandardPaths::PicturesLocation);
    dialog.setDirectory(picturesLocations.isEmpty() ? QDir::currentPath() : picturesLocations.last());

    QStringList mimeTypeFilters;
    const QByteArrayList supportedMimeTypes = acceptMode == QFileDialog::AcceptOpen
                                                  ? QImageReader::supportedMimeTypes() : QImageWriter::supportedMimeTypes();
    foreach (const QByteArray &mimeTypeName, supportedMimeTypes)
        mimeTypeFilters.append(mimeTypeName);
    mimeTypeFilters.sort();
    dialog.setMimeTypeFilters(mimeTypeFilters);
    dialog.selectMimeTypeFilter("image/jpeg");

    dialog.setFileMode(QFileDialog::ExistingFiles);
    //dialog.setViewMode()

    if (acceptMode == QFileDialog::AcceptSave)
        dialog.setDefaultSuffix("jpg");

    //dialog.setOption(QFileDialog::DontUseNativeDialog, true);

    QStringList fileNames;
   if (dialog.exec())
   {
        fileNames = dialog.selectedFiles();
        //fileNames = dialog.getOpenFileNames();

        for (int i = 0; i < fileNames.size(); ++i)
        {
            imageRecivedSlot(fileNames.at(i));
        }
   }
#endif
}

void QLoadDocLineWidget::getImgStr(QString & imgStr)
{
    imgStr = m_strImg;
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
    qDebug()<<"QLoadDocLineWidget::imageRecivedSlot str="<<str;
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
