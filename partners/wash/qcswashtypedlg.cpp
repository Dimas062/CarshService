#include "qcswashtypedlg.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGroupBox>

extern QRect screenGeometry;
extern QUuid uuidCurrentPartner;
extern int iButtonHeight;

QCSWashTypeDlg::QCSWashTypeDlg(QString strType ,  QWidget *parent, Qt::WindowFlags f ):QCSBaseDialog(parent , f )

{
    QVBoxLayout * pVMainLayout = new QVBoxLayout;
    m_pTopLabel = new QLabel(strType);
    pVMainLayout->addWidget(m_pTopLabel);

    m_strType = strType;


    QVBoxLayout * pDayLayout =  new QVBoxLayout;

    m_pDayButton= new QPushButton("День");
    connect(m_pDayButton,SIGNAL(toggled(bool)),this,SLOT(OnDayButtonToggled(bool)));
    m_pDayButton->setMinimumWidth(screenGeometry.width()*0.70);
    m_pDayButton->setCheckable(true);
    pDayLayout->addWidget(m_pDayButton);
    m_pDayNumberLineText = new QLineText("Количество:");
    pDayLayout->addWidget(m_pDayNumberLineText);
    m_pDayNumberLineText->SetEnabled(false);

    QGroupBox *pDayGroupBox = new QGroupBox;
    pDayGroupBox->setLayout(pDayLayout);
    pVMainLayout->addWidget(pDayGroupBox);


    QVBoxLayout * pNigthLayout =  new QVBoxLayout;

    m_pNigthButton= new QPushButton("Ночь");
    connect(m_pNigthButton,SIGNAL(toggled(bool)),this,SLOT(OnNigthButtonToggled(bool)));
    m_pNigthButton->setMinimumWidth(screenGeometry.width()*0.70);
    m_pNigthButton->setCheckable(true);
    pNigthLayout->addWidget(m_pNigthButton);
    m_pNigthNumberLineText = new QLineText("Количество:");
    pNigthLayout->addWidget(m_pNigthNumberLineText);
    m_pNigthNumberLineText->SetEnabled(false);

    QGroupBox *pNigthGroupBox = new QGroupBox;
    pNigthGroupBox->setLayout(pNigthLayout);
    pVMainLayout->addWidget(pNigthGroupBox);



    QPushButton * pApplyButton = new QPushButton("Внести");
    pApplyButton->setIcon(QIcon(":/icons/done_icon.png"));
    pApplyButton->setIconSize(QSize(iButtonHeight*0.75 , iButtonHeight*0.75));
    pVMainLayout->addWidget(pApplyButton);
    connect(pApplyButton,SIGNAL(released()),this,SLOT(OnApplyPressedSlot()));

    this->setLayout(pVMainLayout);
}

QString QCSWashTypeDlg::getText()
{
    QString retVal(m_strType);

    if(m_pDayButton->isChecked())
    {
        retVal = QString(m_strType + " День (%1)").arg(m_pDayNumberLineText->getText());
        if(m_pNigthButton->isChecked())
            retVal.append(QString("; Ночь (%1)").arg(m_pNigthNumberLineText->getText()));
    }
    else
        if(m_pNigthButton->isChecked())
        retVal = QString(m_strType + " Ночь (%1)").arg(m_pNigthNumberLineText->getText());

    return retVal;
}

void QCSWashTypeDlg::OnDayButtonToggled(bool bIsToggled)
{
    if(bIsToggled) m_pDayNumberLineText->SetEnabled(true);
    else m_pDayNumberLineText->SetEnabled(false);
}

void QCSWashTypeDlg::OnNigthButtonToggled(bool bIsToggled)
{
    if(bIsToggled) m_pNigthNumberLineText->SetEnabled(true);
    else m_pNigthNumberLineText->SetEnabled(false);
}

void QCSWashTypeDlg::OnApplyPressedSlot()
{

    accept();
}
