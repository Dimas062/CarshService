#include "qfullscreenpicdialog.h"
#include "qapplication.h"
#include "qscreen.h"
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QPushButton>


QFullScreenPicDialog::QFullScreenPicDialog(QImage * pImage,QWidget *parent, Qt::WindowFlags f ):QDialog(parent , f)
{
#ifdef Q_OS_IOS
    QVBoxLayout * pMainVLayout = new QVBoxLayout(this);
    QHBoxLayout * pHBackButtonLayout = new QHBoxLayout(this);

    QPushButton * pBackButton = new QPushButton("< Назад");
    pBackButton->setStyleSheet("font-size: 20px;\
                                color: Blue;\
                                border: none;\
                                background-color: #fdfefe;\
                                padding: 1px 1px;");
    pHBackButtonLayout->addWidget(pBackButton);
    pHBackButtonLayout->addStretch();

    connect(pBackButton,SIGNAL(pressed()),this,SLOT(reject()));

    pMainVLayout->addLayout(pHBackButtonLayout);

    m_pImageWidget = new ImageWidget(pImage,this);
    QList<Qt::GestureType> gestures;
    gestures << Qt::PanGesture;
    gestures << Qt::PinchGesture;
    gestures << Qt::SwipeGesture;
    m_pImageWidget->grabGestures(gestures);

    const QRect screenGeometry = QGuiApplication::primaryScreen()->availableGeometry();
    QRect geometry(QPoint(0, 0), QSize(screenGeometry.width() /** 3 / 4*/, screenGeometry.height() /** 3 / 4*/));
    geometry.moveCenter(screenGeometry.center());
    setGeometry(geometry);
    QRect imgGeometry(QPoint(0, 0), QSize(screenGeometry.width() * 3 / 4, screenGeometry.height() / 3 / 4));
    m_pImageWidget->setGeometry(imgGeometry);

    pMainVLayout->addWidget(m_pImageWidget);

    setLayout(pMainVLayout);
#endif
#ifdef Q_OS_ANDROID
    m_pImageWidget = new ImageWidget(pImage,this);
    QList<Qt::GestureType> gestures;
    gestures << Qt::PanGesture;
    gestures << Qt::PinchGesture;
    gestures << Qt::SwipeGesture;
    m_pImageWidget->grabGestures(gestures);

    //setCentralWidget(m_pImageWidget);
    const QRect screenGeometry = QGuiApplication::primaryScreen()->availableGeometry();
    QRect geometry(QPoint(0, 0), QSize(screenGeometry.width() /** 3 / 4*/, screenGeometry.height() /** 3 / 4*/));
    geometry.moveCenter(screenGeometry.center());
    setGeometry(geometry);
    m_pImageWidget->setGeometry(geometry);
#endif
}
