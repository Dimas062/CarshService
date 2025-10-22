#include "qcarshserviceemploeecarddlg.h"
#include <QVBoxLayout>
#include "common.h"
#include <QLabel>
#include <pictures/qfullscreenpicdialog.h>
#include <QString>
#include <QDateTime>
#include "emploee_widgets/QEmploeeTasksDlg.h"
#include "service_widgets/qcsselectdialog.h"
#include "service_widgets/qyesnodlg.h"

extern QRect screenGeometry;
extern int iButtonHeight;

QCarshServiceEmploeeCardDlg::QCarshServiceEmploeeCardDlg(QUuid uuidUser, QWidget *parent, Qt::WindowFlags f ):QCSBaseDialog(parent , f)
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
        pFIOLabel->setStyleSheet("font-size: 20px;");
        pFIOLabel->setWordWrap(true);
        pFIOLabel->setMaximumWidth(screenGeometry.width()*0.9);



        pVMainLayout->addWidget(pFIOLabel);

        m_IsActive = true;
        if(resUser.at(iUserCounter).at(3)=="f") m_IsActive=false;

        m_pLabelActive = new QLabel(this);
        if(m_IsActive)   m_pLabelActive->setText("Учётная запись активна");
        else m_pLabelActive->setText("Учётная запись не активна");

        pVMainLayout->addWidget(m_pLabelActive);


        QString strFotoPicture= resUser.at(iUserCounter).at(5);
        m_FotoImage = Base64ToImage(strFotoPicture);
        m_pFotoPicLabel = new QPicLabel();

        m_pFotoPicLabel->setStyleSheet("QLabel {"
                                          "border-style: solid;"
                                          "border-width: 1px;"
                                          "border-color: black;"
                                          "border-radius: 7px;"
                                          "}");
        m_pFotoPicLabel->setAlignment(Qt::AlignCenter);
        connect(m_pFotoPicLabel,SIGNAL(clicked()), this , SLOT(OnFotoPictureClik()));



        m_pFotoPicLabel->setFixedWidth(iButtonHeight*2);
        m_pFotoPicLabel->setFixedHeight(iButtonHeight*2);

        m_pFotoPicLabel->SetCurrentImage(&m_FotoImage);
        pVMainLayout->addWidget(m_pFotoPicLabel);

        // QPushButton * m_pTasksButton = new QPushButton("Задачи");
        // connect(m_pTasksButton,SIGNAL(pressed()),this,SLOT(OnTasksPressed()));
        // m_pTasksButton->setMaximumHeight(iButtonHeight);
        // m_pTasksButton->setMinimumHeight(iButtonHeight);
        // pVMainLayout->addWidget(m_pTasksButton);

        pVMainLayout->addSpacing(15);


        QPushButton * pDriverCardButton = new QPushButton("Права");
        connect(pDriverCardButton,SIGNAL(pressed()),this,SLOT(OnDriverCardPressed()));
        pDriverCardButton->setMaximumHeight(iButtonHeight);
        pDriverCardButton->setMinimumHeight(iButtonHeight);
        pVMainLayout->addWidget(pDriverCardButton);

        QPushButton * pPassportButton = new QPushButton("Паспорт");
        connect(pPassportButton,SIGNAL(pressed()),this,SLOT(OnPassportPressed()));
        pPassportButton->setMaximumHeight(iButtonHeight);
        pPassportButton->setMinimumHeight(iButtonHeight);
        pVMainLayout->addWidget(pPassportButton);

        QPushButton * pSertButton = new QPushButton("Лицензия");
        connect(pSertButton,SIGNAL(pressed()),this,SLOT(OnSertPressed()));
        pSertButton->setMaximumHeight(iButtonHeight);
        pSertButton->setMinimumHeight(iButtonHeight);
        pVMainLayout->addWidget(pSertButton);

        pVMainLayout->addSpacing(15);

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


void QCarshServiceEmploeeCardDlg::OnFotoPictureClik()
{
    QFullScreenPicDialog dlg(&m_FotoImage , this);

    dlg.exec();
}

void QCarshServiceEmploeeCardDlg::OnDriverCardPressed()
{
    QString strExec=QString("select Документы.Изображение from Документы, \"Пользователь-Документы\" where Документы.id=\"Пользователь-Документы\".Документ and \"Пользователь-Документы\".Пользователь='%1' and Документы.Тип='0f3d1416-cbf7-481e-8c1c-1e5b819e75f5'").arg(m_userUuid.toString());
    QList<QStringList> resPic = execMainBDQuery(strExec);
    if(resPic.size()>0)
    {
        QString strPicture= resPic.at(0).at(0);

        QImage Image = Base64ToImage(strPicture);

        QFullScreenPicDialog dlg(&Image , this);

        dlg.exec();
    }

}

void QCarshServiceEmploeeCardDlg::OnPassportPressed()
{
    QString strExec=QString("select Документы.Изображение from Документы, \"Пользователь-Документы\" where Документы.id=\"Пользователь-Документы\".Документ and \"Пользователь-Документы\".Пользователь='%1' and Документы.Тип='79e23c72-712b-4751-8a2b-4db82a270be3'").arg(m_userUuid.toString());
    QList<QStringList> resPic = execMainBDQuery(strExec);
    if(resPic.size()>0)
    {
        QString strPicture= resPic.at(0).at(0);

        QImage Image = Base64ToImage(strPicture);

        QFullScreenPicDialog dlg(&Image , this);

        dlg.exec();
    }
}
void QCarshServiceEmploeeCardDlg::OnSertPressed()
{
    QString strExec=QString("select Документы.Изображение from Документы, \"Пользователь-Документы\" where Документы.id=\"Пользователь-Документы\".Документ and \"Пользователь-Документы\".Пользователь='%1' and Документы.Тип='2e73791e-402d-4f7c-b777-bc3cc51e415b'").arg(m_userUuid.toString());
    QList<QStringList> resPic = execMainBDQuery(strExec);
    if(resPic.size()>0)
    {
        QString strPicture= resPic.at(0).at(0);

        QImage Image = Base64ToImage(strPicture);

        QFullScreenPicDialog dlg(&Image , this);

        dlg.exec();
    }
}

void QCarshServiceEmploeeCardDlg::OnActivPressed()
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

void QCarshServiceEmploeeCardDlg::OnRemovePressed()
{
    QYesNoDlg dlg("Удалить пользователя?");
    if(dlg.exec() == QDialog::Accepted)
    {
        QString strExec=QString("update Пользователи set Удалено='true' where id='%1'").arg(m_userUuid.toString());
        execMainBDQueryUpdate(strExec);
        accept();
    }
}

// void QCarshServiceEmploeeCardDlg::OnTasksPressed()
// {
//     QCSSelectDialog selDlg("Типы задач" , "Тип" , false , true);
//     if(selDlg.exec()==QDialog::Accepted)
//     {
//         QEmploeeTasksDlg dlg(m_userUuid , QUuid(selDlg.getCurId()));
//         dlg.exec();
//     }
// }
