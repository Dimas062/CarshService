#include "qselprovidercarshwidget.h"
#include "qcsselectdialog.h"
#include <QHBoxLayout>
#include "common.h"

extern int iButtonHeight;
extern QUuid uuidCurrentUser;
extern QUuid uuidCurrentPartner;
extern UserTypes CurrentUserType;

QSelProviderCarshWidget::QSelProviderCarshWidget(QUuid uuidProvider , QUuid uuidCarsh  , QWidget *parent)
    : QWidget{parent}
{
    m_uuidProvider = uuidProvider;
    m_uuidCarsh = uuidCarsh;

    QVBoxLayout * pVMainLayout = new QVBoxLayout;
    this->setLayout(pVMainLayout);

    pVMainLayout->addSpacing(5);

    if(CurrentUserType == Emploee || CurrentUserType == CarshService)
    {
        m_pProviderButton = new QPushButton("Поставщик");
        m_pProviderButton->setFixedHeight((int)(iButtonHeight*1.5));
        connect(m_pProviderButton,SIGNAL(pressed()),this,SLOT(OnProviderPressedSlot()));
        pVMainLayout->addWidget(m_pProviderButton);
    }

    pVMainLayout->addSpacing(5);

    m_pCarshButton = new QPushButton("Заказчик");
    m_pCarshButton->setFixedHeight((int)(iButtonHeight*1.5));
    connect(m_pCarshButton,SIGNAL(pressed()),this,SLOT(OnCarshPressedSlot()));
    pVMainLayout->addWidget(m_pCarshButton);

    pVMainLayout->addSpacing(5);
}

bool QSelProviderCarshWidget::isReadyColored()
{
    bool retVal = true;

    if(CurrentUserType == Emploee)
    {
        if(m_uuidProvider==QUuid())
        {
            m_pProviderButton->setStyleSheet("QPushButton {color: red;}");
            retVal = false;
        }
        else m_pProviderButton->setStyleSheet("QPushButton {color: black;}");
    }

    if(m_uuidCarsh==QUuid())
    {
        m_pCarshButton->setStyleSheet("QPushButton {color: red;}");
        retVal = false;
    }
    else m_pCarshButton->setStyleSheet("QPushButton {color: black;}");

    return retVal;
}


void QSelProviderCarshWidget::OnProviderPressedSlot()
{
    QCSSelectDialog dlg("Поставщики");

    dlg.SelectId(m_uuidProvider);
    if(dlg.exec()==QDialog::Accepted)
    {
        m_uuidProvider = dlg.getCurIdUUid();

        emit ProviderChanged();
    }
}

void QSelProviderCarshWidget::OnCarshPressedSlot()
{
    QString strAddCondition = QString(" where Удалено<>true");

    if(CurrentUserType == Emploee)
    {
        strAddCondition = QString(" where Удалено<>true and id in (select Заказчик from ИсполнителиЗаказчики where ИсполнительПартнер = '%1')").arg(uuidCurrentUser.toString());
    }

    if(CurrentUserType == PartnerWasher || CurrentUserType == PartnerPlate || CurrentUserType == PartnerStick)
    {
        strAddCondition = QString(" where Удалено<>true and id in (select Заказчик from ИсполнителиЗаказчики where ИсполнительПартнер = '%1')").arg(uuidCurrentPartner.toString());
    }

    QCSSelectDialog dlg("Заказчики" , "Название", true , false , QUuid() , strAddCondition);

    dlg.SelectId(m_uuidCarsh);
    if(dlg.exec()==QDialog::Accepted)
    {
        m_uuidCarsh = dlg.getCurIdUUid();

        emit CarshChanged();
    }
}
