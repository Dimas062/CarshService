#include "qcsselectdlgbuttonswidget.h"
#include <QVBoxLayout>
#include "common.h"
#include <QUuid>


extern QRect screenGeometry;
extern QUuid uuidCurrentUser;

QCSSelectDlgButtonsWidget::QCSSelectDlgButtonsWidget(QString strTableName, QString strColName , bool bChekable , QWidget *parent)
    : QWidget{parent}
{
    m_strId = "Undefined";

    QVBoxLayout * pVMainLayout = new QVBoxLayout;
    this->setLayout(pVMainLayout);

    m_bChekable = bChekable;

    QString strExec = QString("select id , \"%1\" from \"%2\"").arg(strColName).arg(strTableName);

    QList<QStringList> resData = execMainBDQuery(strExec);
    for(int iResCounter = 0 ; iResCounter < resData.size() ; iResCounter++)
    {
        QPushButton * pButton = new QPushButton(resData.at(iResCounter).at(1));
        connect(pButton,SIGNAL(pressed()),this,SLOT(OnButtonPress()));
        pButton->setMinimumWidth(screenGeometry.width()*0.6);
        pButton->setProperty("id",QVariant(QString(resData.at(iResCounter).at(0))));
        pButton->setCheckable(true);
        pVMainLayout->addWidget(pButton);
        m_vpButtons.push_back(pButton);
    }


}

void QCSSelectDlgButtonsWidget::SelectId(QString strId)
{
    foreach (QPushButton * pAllButton, m_vpButtons) {
        if(QUuid::fromString((pAllButton->property("id")).value<QString>()) != QUuid::fromString(strId))
        {
            pAllButton->setChecked(false);
        }
        else
        {
            pAllButton->setChecked(true);
            m_strId = strId;
            m_strText = pAllButton->text();
        }
    }
}

void QCSSelectDlgButtonsWidget::OnButtonPress()
{
    QPushButton * pButton = (QPushButton *)sender();
    m_strId = (pButton->property("id")).value<QString>();
    m_strText = pButton->text();
    foreach (QPushButton * pAllButton, m_vpButtons) {
        if(pAllButton != pButton)pAllButton->setChecked(false);
    }

    if(!m_bChekable) emit ButtonPushed();
   // pButton->setChecked(true);
}
