#include "qcarshcarddlg.h"
#include "common.h"
#include <QVBoxLayout>
#include <QLabel>
#include "service_widgets/qyesnodlg.h"

extern QRect screenGeometry;
extern int iButtonHeight;

QCarshCardDlg::QCarshCardDlg(QUuid uuidUser, QWidget *parent, Qt::WindowFlags f ):QCSBaseDialog(parent , f)
{
    int iButtonHeight = (int)((screenGeometry.height()*0.7)/9)-5;

    QVBoxLayout * pVMainLayout = new QVBoxLayout;

    m_userUuid = uuidUser;

    pVMainLayout->addSpacing(5);

    QString strExec=QString("SELECT Пользователи.Фамилия, \"Пользователи\".\"Имя\" , Пользователи.Отчество , Пользователи.Подтвержден , Пользователи.\"Дата регистрации\" , Пользователи.Фото  FROM Пользователи where Пользователи.id = '%1'").arg(uuidUser.toString());

    QList<QStringList> resUser = execMainBDQuery(strExec);

    for(int iUserCounter = 0 ; iUserCounter < resUser.size() ; iUserCounter++)
    {
        QLabel * pFIOLabel = new QLabel(QString("<b> %1 %2 %3</b>\nДата регистрации: %4").arg(resUser.at(iUserCounter).at(0)).arg(resUser.at(iUserCounter).at(1)).arg(resUser.at(iUserCounter).at(2)).arg(QDateTime::fromSecsSinceEpoch(resUser.at(iUserCounter).at(4).toInt()).toString("dd.MM.yyyy hh:mm")));
        pFIOLabel->setWordWrap(true);
        pFIOLabel->setMaximumWidth(screenGeometry.width()*0.9);



        pVMainLayout->addWidget(pFIOLabel);

        m_IsActive = true;
        if(resUser.at(iUserCounter).at(3)=="f") m_IsActive=false;

        m_pLabelActive = new QLabel(this);
        if(m_IsActive)   m_pLabelActive->setText("Учётная запись активна");
        else m_pLabelActive->setText("Учётная запись не активна");

        pVMainLayout->addWidget(m_pLabelActive);


        QPushButton * pRemoveButton = new QPushButton("Удалить");
        pRemoveButton->setIcon(QIcon(":/icons/remove_icon.png"));
        pRemoveButton->setIconSize(QSize(iButtonHeight*0.75 , iButtonHeight*0.75));
        connect(pRemoveButton,SIGNAL(pressed()),this,SLOT(OnRemovePressed()));
        pRemoveButton->setMaximumHeight(iButtonHeight);
        pRemoveButton->setMinimumHeight(iButtonHeight);
        pVMainLayout->addWidget(pRemoveButton);

        m_pActivationButton = new QPushButton("Активировать");
        connect(m_pActivationButton,SIGNAL(pressed()),this,SLOT(OnActivPressed()));
        m_pActivationButton->setMaximumHeight(iButtonHeight);
        m_pActivationButton->setMinimumHeight(iButtonHeight);
        pVMainLayout->addWidget(m_pActivationButton);
        if(m_IsActive) m_pActivationButton->setText("Деактивировать");



    }
    pVMainLayout->addStretch();
    this->setLayout(pVMainLayout);
}

void QCarshCardDlg::OnActivPressed()
{
    if(m_IsActive)
    {
        QString strExec=QString("update Пользователи set Подтвержден='false' where id='%1'").arg(m_userUuid.toString());
        execMainBDQueryUpdate(strExec);
        m_IsActive = false;
        m_pLabelActive->setText("Учётная запись не активна");
        m_pActivationButton->setText("Активировать");
    }
    else
    {
        QString strExec=QString("update Пользователи set Подтвержден='true' where id='%1'").arg(m_userUuid.toString());
        execMainBDQueryUpdate(strExec);
        m_IsActive = true;
        m_pLabelActive->setText("Учётная запись активна");
        m_pActivationButton->setText("Деактивировать");
    }
}

void QCarshCardDlg::OnRemovePressed()
{
    QYesNoDlg dlg("Удалить пользователя?");
    if(dlg.exec() == QDialog::Accepted)
    {
        QString strExec=QString("update Пользователи set Удалено='true' where id='%1'").arg(m_userUuid.toString());
        execMainBDQueryUpdate(strExec);
        accept();
    }
}
