#include "qloaddocsdlg.h"
#include <QVBoxLayout>
#include <QPushButton>

extern QRect screenGeometry;
extern QUuid uuidCurrentUser;
extern int iButtonHeight;
//extern UserTypes CurrentUserType;

QLoadDocsDlg::QLoadDocsDlg(QWidget *parent, Qt::WindowFlags f):QCSBaseDialog(parent , f)
{
    QVBoxLayout * pVMainLayout = new QVBoxLayout;


    m_pLoadPhotoWidget = new QLoadDocLineWidget("Фото автомобия" , true , true);

    connect(m_pLoadPhotoWidget,SIGNAL(imageRecivedSignal(QString)),this,SLOT(OnFotoGetet(QString)));
    pVMainLayout->addWidget(m_pLoadPhotoWidget);

    m_pPicturesWidget = new QPicturesWidget(this);
    m_pPicturesWidget->setMinimumHeight(screenGeometry.width()*0.5);
    pVMainLayout->addWidget(m_pPicturesWidget);

    QPushButton * pCloseButton = new QPushButton("Закрыть");
    connect(pCloseButton,SIGNAL(pressed()),this,SLOT(accept()));
    pVMainLayout->addWidget(pCloseButton);

    this->setLayout(pVMainLayout);
}

void QLoadDocsDlg::OnFotoGetet(QString strFotoPath)
{
    m_pPicturesWidget->AddPicturePath(strFotoPath);
}

