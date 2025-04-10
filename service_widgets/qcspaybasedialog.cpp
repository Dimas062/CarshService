#include "qcspaybasedialog.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QDateTime>
#include <QUuid>
#include <QVector>
#include <QImage>
#include "common.h"
#include "service_widgets/qcalendardataselectdlg.h"

extern QRect screenGeometry;
extern QUuid uuidCurrentUser;
extern int iButtonHeight;

QCSPayBaseDialog::QCSPayBaseDialog(QWidget *parent, Qt::WindowFlags f , bool bOneCheck):QCSBaseDialog(parent , f)
{
    // int iUnderButtonSpace = 15;

    // int iButtonHeight = (int)((screenGeometry.height()*0.7)/8)-iUnderButtonSpace;

    QVBoxLayout * pVMainLayout = new QVBoxLayout;
    m_bOneCheck = bOneCheck;

    pVMainLayout->addSpacing(5);
    m_pTopLabel = new QLabel(QString("<b>Оплата</b>"));
    m_pTopLabel->setStyleSheet("font-size: 20px;");
    pVMainLayout->addWidget(m_pTopLabel);

    QHBoxLayout * pDateLayout = new QHBoxLayout;

    m_pDateLabel =  new QLabel("");
    m_pDateLabel->setStyleSheet("font-size: 20px;");
    pDateLayout->addWidget(m_pDateLabel);

    m_pCalendarButton = new QPushButton("");
    m_pCalendarButton->setIcon(QIcon(":/icons/to_calendar_icon_256.png"));
    m_pCalendarButton->setIconSize(QSize(iButtonHeight*0.75 , iButtonHeight*0.75));
    connect(m_pCalendarButton,SIGNAL(pressed()),this,SLOT(OnCalendarPressedSlot()));
    m_pCalendarButton->setFixedHeight(iButtonHeight);
    m_pCalendarButton->setFixedWidth(iButtonHeight);
    pDateLayout->addWidget(m_pCalendarButton);

    pVMainLayout->addLayout(pDateLayout);

    m_iPayDate=QDateTime::currentSecsSinceEpoch();
    UpdateDateLabel();

    m_pCashLineText = new QLineText("Сумма оплаты" , nullptr , true);
    pVMainLayout->addWidget(m_pCashLineText);

    QHBoxLayout * pHPayMetodLayout = new QHBoxLayout();

    m_pCardPayButton = new QPushButton("Наличные");
    m_pCardPayButton->setCheckable(true);
    connect(m_pCardPayButton,SIGNAL(pressed()),this,SLOT(OnCardPayPressedSlot()));
    pHPayMetodLayout->addWidget(m_pCardPayButton);

    m_pBusinessPayButton = new QPushButton("Безналичный");
    m_pBusinessPayButton->setCheckable(true);
    connect(m_pBusinessPayButton,SIGNAL(pressed()),this,SLOT(OnBusinessPayPressedSlot()));
    pHPayMetodLayout->addWidget(m_pBusinessPayButton);

    pVMainLayout->addLayout(pHPayMetodLayout);


    m_pLoadPhotoWidget = new QLoadDocLineWidget("Фото чека" , true , true);

    connect(m_pLoadPhotoWidget,SIGNAL(imageRecivedSignal(QString)),this,SLOT(OnFotoGetet(QString)));
    pVMainLayout->addWidget(m_pLoadPhotoWidget);

    m_pPicturesWidget = new QPicturesWidget(this);
#ifdef Q_OS_MOBILE
    m_pPicturesWidget->setMinimumHeight(screenGeometry.width());
#endif
#ifdef Q_OS_DESKTOP
    m_pPicturesWidget->setFixedHeight(screenGeometry.height()*0.45);
#endif

    pVMainLayout->addWidget(m_pPicturesWidget);

    pVMainLayout->addStretch();

    QPushButton * pApplyButton = new QPushButton("Внести");
    pApplyButton->setIcon(QIcon(":/icons/done_icon.png"));
    pApplyButton->setIconSize(QSize(iButtonHeight*0.75 , iButtonHeight*0.75));
    pVMainLayout->addWidget(pApplyButton);
    connect(pApplyButton,SIGNAL(released()),this,SLOT(OnApplyPressedSlot()));

    this->setLayout(pVMainLayout);
}

void QCSPayBaseDialog::LoadFromBD(QUuid uuidPay)
{

    QString strPays = QString("select \"Сумма\" , \"Тип оплаты\" , \"ДатаВремя\" from \"Платежи сотрудников\" where id='%1'").arg(uuidPay.toString());

    QList<QStringList> resPays = execMainBDQuery(strPays);

    for(int iPaysCounter = 0 ; iPaysCounter < resPays.size() ; iPaysCounter++)
    {
        /*Сумма*/
        if(resPays.at(iPaysCounter).at(0).length()>0)
        {
            m_pCashLineText->setText(resPays.at(iPaysCounter).at(0));
        }

        /*Дата платежа*/
        m_iPayDate = resPays.at(iPaysCounter).at(2).toInt();
        UpdateDateLabel();

        /*Тип оплаты*/
        m_pCardPayButton->setChecked(true);
        if(resPays.at(iPaysCounter).at(1) == "1368c945-6d5b-4a32-af29-007896fc5aba")
        {
            m_pCardPayButton->setChecked(true);
            m_pBusinessPayButton->setChecked(false);
        }

        if(resPays.at(iPaysCounter).at(1) == "c1a98e3d-c6a9-4991-9c2c-2e8771ccf37f")
        {
            m_pCardPayButton->setChecked(false);
            m_pBusinessPayButton->setChecked(true);
        }
        /*Фото чека*/
        m_pPicturesWidget->m_Pictures.clear();
        QString strChekPhotoExec = QString("select Изображение from Документы where id in (select Документ from \"Платеж сотрудника - Документы\" where Платеж = '%1')").arg(uuidPay.toString());
        QList<QStringList> resChekPhoto = execMainBDQuery(strChekPhotoExec);

        for(int iChekPhotoCounter = 0 ; iChekPhotoCounter < resChekPhoto.size() ; iChekPhotoCounter++)
        {
            QString strTempImg = resChekPhoto.at(iChekPhotoCounter).at(0);
            QImage tempImage = Base64ToImage(strTempImg);
            m_pPicturesWidget->AddImage(tempImage);
        }
    }
}

PayTypes QCSPayBaseDialog::GetSelectedPayType()
{
    if(m_pBusinessPayButton->isChecked()) return Business;
    if(m_pCardPayButton->isChecked()) return Card;
    return Undefined;
}

void QCSPayBaseDialog::OnFotoGetet(QString strFotoPath)
{

    if(m_bOneCheck) m_pPicturesWidget->m_Pictures.clear();
    m_pPicturesWidget->AddPicturePath(strFotoPath);
}

void QCSPayBaseDialog::OnCalendarPressedSlot()
{
    QCalendarDataSelectDlg calendarDlg(QDateTime::fromSecsSinceEpoch(m_iPayDate).date());
    if(calendarDlg.exec()==QDialog::Accepted)
    {
        m_iPayDate= QDateTime(calendarDlg.m_SelectedDate, QTime(0,0,0)).toSecsSinceEpoch();
        UpdateDateLabel();
    }
}

void QCSPayBaseDialog::OnApplyPressedSlot()
{
    accept();
}

void QCSPayBaseDialog::OnCardPayPressedSlot()
{
    m_pBusinessPayButton->setChecked(false);
}

void QCSPayBaseDialog::OnBusinessPayPressedSlot()
{
    m_pCardPayButton->setChecked(false);
}

