#include "quldlg.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QDateTime>
#include <QUuid>
#include <QVector>
#include <QImage>
#include <QPushButton>
#include "common.h"

extern QRect screenGeometry;
extern QUuid uuidCurrentUser;
extern int iButtonHeight;



QULDlg::QULDlg(QWidget *, Qt::WindowFlags)
{
    QVBoxLayout * pVMainLayout = new QVBoxLayout;


    pVMainLayout->addSpacing(5);
    QLabel * pTopLabel = new QLabel(QString("<b>Данные ЮЛ</b>"));
    pTopLabel->setStyleSheet("font-size: 20px;");
    pVMainLayout->addWidget(pTopLabel);

    m_pNameLineText = new QLineText("Название:");
    pVMainLayout->addWidget(m_pNameLineText);

    m_pAdressLineText = new QLineText("Адрес:");
    pVMainLayout->addWidget(m_pAdressLineText);

    m_pINNLineText = new QLineText("ИНН:");
    pVMainLayout->addWidget(m_pINNLineText);

    m_pBankLineText = new QLineText("Банк:");
    pVMainLayout->addWidget(m_pBankLineText);

    m_pSchetLineText = new QLineText("р/с:");
    pVMainLayout->addWidget(m_pSchetLineText);

    QPushButton * pApplyButton = new QPushButton("Внести");
    pApplyButton->setIcon(QIcon(":/icons/done_icon.png"));
    pApplyButton->setIconSize(QSize(iButtonHeight*0.75 , iButtonHeight*0.75));
    pVMainLayout->addWidget(pApplyButton);
    connect(pApplyButton,SIGNAL(released()),this,SLOT(OnApplyPressedSlot()));

    this->setLayout(pVMainLayout);


}

void QULDlg::LoadFromBD(QUuid idUl)
{
    QString strExec = QString("select \"Название\" , \"Адрес\" , \"ИНН\" , \"Банк\" , \"Счет\" from \"ЮЛ\" where id='%1'").arg(idUl.toString());

    QList<QStringList> resUls = execMainBDQuery(strExec);
    for(int iUlsCounter = 0 ; iUlsCounter < resUls.size() ; iUlsCounter++)
    {
        m_pNameLineText->setText(resUls.at(iUlsCounter).at(0));
        m_pAdressLineText->setText(resUls.at(iUlsCounter).at(0));
        m_pINNLineText->setText(resUls.at(iUlsCounter).at(0));
        m_pBankLineText->setText(resUls.at(iUlsCounter).at(0));
        m_pSchetLineText->setText(resUls.at(iUlsCounter).at(0));
    }

}

QUuid QULDlg::SaveOrCreateToBD(QUuid idUl)
{

    if(idUl == QUuid())
    {
        idUl = QUuid::createUuid();

        QString strExec = QString("insert into ЮЛ (id , Название , Адрес , ИНН , Банк , Счет) values ('%1' , '%2' , '%3' , '%4' , '%5' , '%6')").arg(idUl.toString()).arg(m_pNameLineText->getText()).arg(m_pAdressLineText->getText()).arg(m_pINNLineText->getText()).arg(m_pBankLineText->getText()).arg(m_pSchetLineText->getText());

        execMainBDQueryUpdate(strExec);
    }
    else
    {
        QString strExec = QString("update ЮЛ set Название = '%2' , Адрес = '%3' , ИНН = '%4' , Банк = '%5' , Счет = '%6' where id='%1'").arg(idUl.toString()).arg(m_pNameLineText->getText()).arg(m_pAdressLineText->getText()).arg(m_pINNLineText->getText()).arg(m_pBankLineText->getText()).arg(m_pSchetLineText->getText());

        execMainBDQueryUpdate(strExec);
    }

    return idUl;
}


void QULDlg::OnApplyPressedSlot()
{

    accept();
}
