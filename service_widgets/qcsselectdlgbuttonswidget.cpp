#include "qcsselectdlgbuttonswidget.h"
#include <QVBoxLayout>
#include "common.h"
#include <QUuid>


extern QRect screenGeometry;
extern QUuid uuidCurrentUser;

QCSSelectDlgButtonsWidget::QCSSelectDlgButtonsWidget(QString strTableName, QString strColName , bool bChekable , QString strСondition , bool bMultiSelect,  QWidget *parent)
    : QWidget{parent}
{
    m_strId = "Undefined";
    m_bMultiSelect = bMultiSelect;

    QVBoxLayout * pVMainLayout = new QVBoxLayout;
    this->setLayout(pVMainLayout);

    m_bChekable = bChekable;

    QString strExec = QString("select id , \"%1\" from \"%2\" %3").arg(strColName).arg(strTableName).arg(strСondition);


    qDebug()<<"QCSSelectDlgButtonsWidget strExec = "<<strExec;

    QList<QStringList> resData = execMainBDQuery(strExec);
    for(int iResCounter = 0 ; iResCounter < resData.size() ; iResCounter++)
    {
        QPushButton * pButton = new QPushButton(resData.at(iResCounter).at(1));
        connect(pButton,SIGNAL(toggled(bool)),this,SLOT(OnButtonPress(bool)));
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

void QCSSelectDlgButtonsWidget::SelectIds(QVector<QString> vstrId)
{
    QVector<QUuid> vIds;
    foreach (QString str, vstrId) {
        vIds.push_back(QUuid::fromString(str));
    }
    m_vstrId.clear();
    m_vstrId = vstrId;
    m_vstrText.clear();
    foreach (QPushButton * pAllButton, m_vpButtons) {
        if(IsUUidInVector(vIds , QUuid::fromString((pAllButton->property("id")).value<QString>())))
        {
            pAllButton->setChecked(true);
            m_vstrText.push_back(pAllButton->text());
        }
        else
        {
            pAllButton->setChecked(false);
        }
    }
}

void QCSSelectDlgButtonsWidget::OnButtonPress(bool)
{
    QPushButton * pButton = (QPushButton *)sender();
    m_strId = (pButton->property("id")).value<QString>();
    m_strText = pButton->text();
    if(!m_bMultiSelect)
    {
        foreach (QPushButton * pAllButton, m_vpButtons) {
            if(pAllButton != pButton)pAllButton->setChecked(false);
        }

        if(!m_bChekable) emit ButtonPushed();
    }
    else
    {
        m_vstrId.clear();
        m_vstrText.clear();
        foreach (QPushButton * pAllButton, m_vpButtons) {
            if(pAllButton->isChecked())
            {
                m_vstrId.push_back((pAllButton->property("id")).value<QString>());
                m_vstrText.push_back(pAllButton->text());
            }
        }
    }
   // pButton->setChecked(true);
}


