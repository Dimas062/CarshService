#include "common.h"
#include "qcarshserviceemploeecarddlg.h"
#include "qcarshcarddlg.h"
#include "qcarshserviceusersdlg.h"
#include <QGuiApplication>
#include <QString>
#include <QUuid>
#include <QVBoxLayout>
#include <QBrush>
#include "emploee_widgets/QEmploeeTasksDlg.h"
#include "service_widgets/qcsselectdialog.h"
#include "service_widgets/qyesnodlg.h"

QCarshServiceUsersDlg::QCarshServiceUsersDlg(QWidget *parent, Qt::WindowFlags f ):QCSBaseDialog(parent , f , false)
{
    QVBoxLayout * pVMainLayout = new QVBoxLayout;

    pVMainLayout->addSpacing(5);
    m_pUsersList = new QCSBaseListWidget();
    pVMainLayout->addWidget(m_pUsersList);
    UpdateUsersList();

    connect(m_pUsersList, SIGNAL(OnTapHoldGesture()), this, SLOT(OnTapHoldGesture()));
    connect(m_pUsersList, SIGNAL(OnTapGesture()), this, SLOT(OnTapGesture()));

    this->setLayout(pVMainLayout);
}

void QCarshServiceUsersDlg::UpdateUsersList()
{
    m_pUsersList->clear();

    QString strExec("SELECT Пользователи.id, Пользователи.Фамилия, \"Пользователи\".\"Имя\" , Пользователи.Отчество, \"Роли пользователей\".Название, Пользователи.Роль , Пользователи.Подтвержден FROM Пользователи, \"Роли пользователей\" where Пользователи.Роль = \"Роли пользователей\".id and Пользователи.Удалено<>'true'");

    QList<QStringList> resUsers = execMainBDQuery(strExec);

    QBrush notApplyedBrus(QColor("gray"));

    for(int iUserCounter = 0 ; iUserCounter < resUsers.size() ; iUserCounter++)
    {
        UserTypes userType;

        if( QUuid("80066f83-c025-410b-b439-f3e9b2299461") == QUuid(resUsers.at(iUserCounter).at(5)) ) userType = UserTypes::Emploee; //Сотрудник

        if( QUuid("512c50c1-c4a9-4542-932a-55280886715a") == QUuid(resUsers.at(iUserCounter).at(5)) ) userType = UserTypes::PartnerPlate; //Партнер номера

        if( QUuid("184f8f60-a865-4bcf-996e-b26ff21d1ee3") == QUuid(resUsers.at(iUserCounter).at(5)) ) userType = UserTypes::PartnerWasher; //Партнер мойка

        if( QUuid("4c476883-76b5-4f28-823a-966d69f51d46") == QUuid(resUsers.at(iUserCounter).at(5)) ) userType = UserTypes::PartnerStick; //Партнер оклейка

        if( QUuid("80d4f275-0b41-40d5-b3d7-07f63a500a22") == QUuid(resUsers.at(iUserCounter).at(5)) ) userType = UserTypes::CarshService; //Каршеринг-сервис

        if( QUuid("ec3f998f-f5f4-4f2d-83a7-588934c58ecf") == QUuid(resUsers.at(iUserCounter).at(5)) ) userType = UserTypes::Carsh; //Каршеринг

        QListWidgetItem * pItem = new QListWidgetItem();

        QString strSotr = QString("  %1 %2 %3,\n  %4").arg(resUsers.at(iUserCounter).at(1)).arg(resUsers.at(iUserCounter).at(2)).arg(resUsers.at(iUserCounter).at(3)).arg(resUsers.at(iUserCounter).at(4));
        if(resUsers.at(iUserCounter).at(6) == "f")
        {
            pItem->setBackground(notApplyedBrus);   //Не подтвержден
            strSotr.append(" (не активно)");
        }
        pItem->setText(strSotr);
        pItem->setFlags(pItem->flags() & ~Qt::ItemIsSelectable);
        pItem->setData(Qt::UserRole , QUuid(resUsers.at(iUserCounter).at(0)));//uuid пользователя
        pItem->setData(Qt::UserRole + 1 , QVariant(userType));//роль пользователя
        m_pUsersList->addItem(pItem);

    }

}

void QCarshServiceUsersDlg::OnTapHoldGesture()
{
    if(QListWidgetItem* item = m_pUsersList->currentItem())
    {
        switch(item->data(Qt::UserRole+1).toInt())
        {
        case Emploee:        //Сотрудник
        {
             QCarshServiceEmploeeCardDlg dlg(item->data(Qt::UserRole).toUuid());
             dlg.exec();

            // QCSSelectDialog selDlg("Типы задач" , "Тип" , false , true);
            // if(selDlg.exec()==QDialog::Accepted)
            // {
            //     QEmploeeTasksDlg dlg(item->data(Qt::UserRole).toUuid() , QUuid(selDlg.getCurId()));
            //     dlg.exec();
            // }
        }
        break;
        case PartnerWasher:   //Партнер мойка

            break;
        case PartnerStick:    //Партнер оклейка

            break;
        case PartnerPlate:    //Партнер номера

            break;
        case CarshService:    //Каршеринг-сервис

            break;
        case Carsh:           //Каршеринг
            // QCarshCardDlg dlg(item->data(Qt::UserRole).toUuid());
            // dlg.exec();
            break;
        }

    }
    qApp->inputMethod()->hide();
    UpdateUsersList();
}

void QCarshServiceUsersDlg::OnTapGesture()
{
    if(QListWidgetItem* item = m_pUsersList->currentItem())
    {
        switch(item->data(Qt::UserRole+1).toInt())
        {
        case Emploee:        //Сотрудник
            {
                // QCarshServiceEmploeeCardDlg dlg(item->data(Qt::UserRole).toUuid());
                // dlg.exec();

                QCSSelectDialog selDlg("Типы задач" , "Тип" , false , true , item->data(Qt::UserRole).toUuid());
                if(selDlg.exec()==QDialog::Accepted)
                {
                    QEmploeeTasksDlg dlg(item->data(Qt::UserRole).toUuid() , QUuid(selDlg.getCurId()));
                    dlg.exec();
                }
            }
            break;
        case PartnerWasher:   //Партнер мойка

            break;
        case PartnerStick:    //Партнер оклейка

            break;
        case PartnerPlate:    //Партнер номера

            break;
        case CarshService:    //Каршеринг-сервис

            break;
        case Carsh:           //Каршеринг
            QCarshCardDlg dlg(item->data(Qt::UserRole).toUuid());
            dlg.exec();
            break;
        }

    }
    qApp->inputMethod()->hide();
    UpdateUsersList();
}
