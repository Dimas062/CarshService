#include "QEmploeeTasksDlg.h"
#include "common.h"
#include "service_widgets/qcalendardataselectdlg.h"
#include "service_widgets/qcsbaselistitemdelegate.h"
#include "service_widgets/qclicablelabel.h"
#include "carsh_service_widgets/qcarshserviceemploeecarddlg.h"
#include <QEasingCurve>
#include <QGuiApplication>
#include <QPushButton>
#include <QScroller>
#include <QVBoxLayout>
#include <tasks/qparkingtaskdialog.h>
#include <tasks/qpenaltyparkingdialog.h>
#include <tasks/qplatetaskdialog.h>
#include "tasks/qrettozonedialog.h"
#include "tasks/qsmenadlg.h"
#include "../CarshService/tasks/qdocstaskdlg.h"
#include <QSplashScreen>
#include "service_widgets/qfinddlg.h"
#include "service_widgets/qcsselectdialog.h"

extern QRect screenGeometry;
extern int iButtonHeight;

#ifdef Q_OS_MOBILE
    extern UserTypes CurrentUserType;
#endif

//#ifdef Q_OS_DESKTOP
    UserTypes CurrentUserType;
    QUuid uuidCurrentPartner;
    QColor currentWorkdayColor;
//#endif

QEmploeeTasksDlg::QEmploeeTasksDlg(QUuid userUuid, QUuid taskTypeUuid , QWidget *parent, Qt::WindowFlags f ):QCSBaseDialog(parent , f , false)
{
#ifdef Q_OS_DESKTOP //На десктопе предполагаем, что всегда эти диалоги смотрит каршсервис
    CurrentUserType =UserTypes::CarshService;
#endif

    int iButtonHeight = (int)((screenGeometry.height()*0.7)/10)-10;

    m_userUuid = userUuid;

    strDateFilter = "";//CreateDateBDPeriodFromNow("Задачи.\"Дата Время\"" , 2);
    strFilter = "";

    if(taskTypeUuid == QUuid())
        strTaskTypesFilter = "";
    else strTaskTypesFilter=QString(" and \"Задачи\".\"Тип\"= '%1'").arg(taskTypeUuid.toString());

    QVBoxLayout * pVMainLayout = new QVBoxLayout;


    QClicableLabel * pFioLabel = new QClicableLabel();

    if(CurrentUserType == CarshService)
        connect(pFioLabel , SIGNAL(clicked()) , this , SLOT(FioClicked()));

    pFioLabel->setAlignment(Qt::AlignHCenter);

    QString strFioOuery = QString("select Фамилия, Имя, Отчество from Пользователи where id='%1'").arg(m_userUuid.toString());

    QList<QStringList> res = execMainBDQuery(strFioOuery);

    if(res.size()>0)
    {
        pFioLabel->setStyleSheet("font: bold 16px");
        pFioLabel->setText(QString("%1 %2 %3").arg(res.at(0).at(0)).arg(res.at(0).at(1)).arg(res.at(0).at(2)));
    }

    pVMainLayout->addWidget(pFioLabel);

    QHBoxLayout * pHFiltersLayout = new QHBoxLayout;

    m_pReadyButton = new QPushButton("");
    m_pReadyButton->setIcon(QIcon(":/icons/done_icon.png"));
    m_pReadyButton->setIconSize(QSize(iButtonHeight*0.75 , iButtonHeight*0.75));
    m_pReadyButton->setCheckable(true);
    connect(m_pReadyButton,SIGNAL(toggled(bool)),this,SLOT(OnReadyButtonTogled(bool)));
    m_pReadyButton->setFixedHeight(iButtonHeight);
    m_pReadyButton->setFixedWidth(iButtonHeight);
    pHFiltersLayout->addWidget(m_pReadyButton);

    m_pNotReadyButton = new QPushButton("");
    m_pNotReadyButton->setIcon(QIcon(":/icons/undone_icon.png"));
    m_pNotReadyButton->setIconSize(QSize(iButtonHeight*0.75 , iButtonHeight*0.75));
    m_pNotReadyButton->setCheckable(true);
    connect(m_pNotReadyButton,SIGNAL(toggled(bool)),this,SLOT(OnNotReadyButtonTogled(bool)));
    m_pNotReadyButton->setFixedHeight(iButtonHeight);
    m_pNotReadyButton->setFixedWidth(iButtonHeight);
    pHFiltersLayout->addWidget(m_pNotReadyButton);

    m_pTaskTypesButton = new QPushButton("");
    m_pTaskTypesButton->setIcon(QIcon(":/icons/list.png"));
    m_pTaskTypesButton->setIconSize(QSize(iButtonHeight*0.75 , iButtonHeight*0.75));
    m_pTaskTypesButton->setCheckable(true);
    connect(m_pTaskTypesButton,SIGNAL(toggled(bool)),this,SLOT(OnTaskTypeButtonTogled(bool)));
    m_pTaskTypesButton->setFixedHeight(iButtonHeight);
    m_pTaskTypesButton->setFixedWidth(iButtonHeight);
    pHFiltersLayout->addWidget(m_pTaskTypesButton);

    m_pToCalendarButton = new QPushButton("");
    m_pToCalendarButton->setIcon(QIcon(":/icons/to_calendar_icon_256.png"));
    m_pToCalendarButton->setIconSize(QSize(iButtonHeight*0.75 , iButtonHeight*0.75));
    m_pToCalendarButton->setCheckable(true);
    connect(m_pToCalendarButton,SIGNAL(toggled(bool)),this,SLOT(OnToCalendatButtonTogled(bool)));
    m_pToCalendarButton->setFixedHeight(iButtonHeight);
    m_pToCalendarButton->setFixedWidth(iButtonHeight);
    pHFiltersLayout->addWidget(m_pToCalendarButton);

    m_pFindButton = new QPushButton("");
    m_pFindButton->setIcon(QIcon(":/icons/search_icon.png"));
    m_pFindButton->setIconSize(QSize(iButtonHeight*0.75 , iButtonHeight*0.75));
    m_pFindButton->setCheckable(true);
    connect(m_pFindButton,SIGNAL(toggled(bool)),this,SLOT(OnFindButtonTogled(bool)));
    m_pFindButton->setFixedHeight(iButtonHeight);
    m_pFindButton->setFixedWidth(iButtonHeight);
    pHFiltersLayout->addWidget(m_pFindButton);

    pVMainLayout->addLayout(pHFiltersLayout);

    m_pTasksListWidget = new QCSBaseListWidget();
#ifdef Q_OS_ANDRIOD
    m_pTasksListWidget->setFixedHeight(screenGeometry.height() - 270 - iButtonHeight*2);
#endif
#if defined Q_OS_IOS || defined Q_OS_WINDOWS
    m_pTasksListWidget->setFixedHeight(screenGeometry.height() - 170 - iButtonHeight*2);
#endif
    m_pTasksListWidget->setItemDelegate(new QCSBaseListItemDelegate(m_pTasksListWidget));

    QScrollerProperties sp;
    sp.setScrollMetric( QScrollerProperties::DragStartDistance, 0.001 );
    sp.setScrollMetric( QScrollerProperties::ScrollingCurve, QEasingCurve::Linear );
    QScroller* qs = QScroller::scroller( m_pTasksListWidget );
    qs->setScrollerProperties( sp );

    QScroller::grabGesture(m_pTasksListWidget, QScroller::TouchGesture);
    m_pTasksListWidget->grabGesture(Qt::TapAndHoldGesture);
    m_pTasksListWidget->grabGesture(Qt::TapGesture);
    m_pTasksListWidget->setIconSize(QSize(47,27));
    m_pTasksListWidget->setWordWrap(true);
    pVMainLayout->addWidget(m_pTasksListWidget);
    connect(m_pTasksListWidget, SIGNAL(OnTapHoldGesture()), this, SLOT(OnTapHoldGesture()));
    connect(m_pTasksListWidget, SIGNAL(OnTapGesture()), this, SLOT(OnTapGesture()));
    //UpdateTasks();вместо обновления вызовем по умолчанию отметку невыполненых задач

    this->setLayout(pVMainLayout);
}

void QEmploeeTasksDlg::checkNotReadyButton()
{
    m_pNotReadyButton->toggle();
}

void QEmploeeTasksDlg::OnFindButtonTogled(bool bChecked)
{
    if(bChecked)
    {
        QFindDlg dlg;
        if(dlg.exec()==QDialog::Accepted)
        {
            m_strFindFilter = "";
            if(dlg.GetText().length()>0)
            {
                m_strFindFilter=QString(" and Задачи.\"Расширение\" in ((select id from \"Расширение задачи Возврат в зону\" where Госномер ilike '%%1%')  union  (select id from \"Расширение задачи Номера\" where Госномер ilike '%%1%') union  (select id from \"Расширение задачи Парковка\" where Госномер ilike '%%1%') union  (select id from \"Расширение задачи ШС\" where Госномер ilike '%%1%'))").arg(dlg.GetText());
            }
        }
    }
    else m_strFindFilter="";
    showWait(true);
    UpdateTasks();
    showWait(false);
}

void QEmploeeTasksDlg::OnTaskTypeButtonTogled(bool bChecked)
{
    if(bChecked)
    {
        QCSSelectDialog selDlg("Типы задач" , "Тип" , false , true);
        if(selDlg.exec()==QDialog::Accepted)
        {
            strTaskTypesFilter =  QString(" and Задачи.Тип='%1' ").arg(selDlg.getCurId());
        }
    }
    else strTaskTypesFilter="";
    showWait(true);
    UpdateTasks();
    showWait(false);
}

void QEmploeeTasksDlg::UpdateTasks()
{
    m_pTasksListWidget->clear();

    QString strCurrentUpdateDateFilter(strDateFilter);

    if(m_strFindFilter.length()>2 && m_pFindButton->isChecked())
        strCurrentUpdateDateFilter="";


    QString strExec= QString("SELECT Задачи.id, Задачи.\"Дата Время\", \"Типы задач\".\"Тип\" , \"Типы задач\".id , Задачи.\"Время выполнения\" , Заказчики.Название FROM \"Типы задач\", Задачи, Заказчики where Заказчики.id=Задачи.Заказчик and Задачи.Тип = \"Типы задач\".id and Задачи.Удалено<> 'true' and Задачи.Исполнитель='%1' %2 %3 %4 %5 order by Задачи.\"Дата Время\" desc").arg(m_userUuid.toString()).arg(strFilter).arg(strCurrentUpdateDateFilter).arg(strTaskTypesFilter).arg(m_strFindFilter);

    QList<QStringList> resTasks = execMainBDQuery(strExec);

    for(int iTaskCounter = 0 ; iTaskCounter < resTasks.size() ; iTaskCounter++)
    {

        QListWidgetItem * pItem = new QListWidgetItem();

        QString strNumber = " ";

        if(QUuid::fromString(resTasks.at(iTaskCounter).at(3)) == QUuid::fromString(QString("8078b7ce-e423-49ae-9ce6-17758b852b33"))) //Тип Штрафстоянка
        {
            QString strNumExec = QString("SELECT \"Расширение задачи ШС\".Госномер From \"Расширение задачи ШС\" , Задачи where Задачи.Расширение=\"Расширение задачи ШС\".id and Задачи.id='%1'").arg(resTasks.at(iTaskCounter).at(0));

            QList<QStringList> resNumber = execMainBDQuery(strNumExec);

            if(resNumber.size()>0) strNumber = resNumber.at(0).at(0);
        }

        if(QUuid::fromString(resTasks.at(iTaskCounter).at(3)) == QUuid::fromString(QString("fe81daf9-a838-4bac-84aa-595e038d3a12"))) //Тип возврат в зону
        {
            QString strNumExec = QString("SELECT \"Расширение задачи Возврат в зону\".Госномер From \"Расширение задачи Возврат в зону\" , Задачи where Задачи.Расширение=\"Расширение задачи Возврат в зону\".id and Задачи.id='%1'").arg(resTasks.at(iTaskCounter).at(0));

            QList<QStringList> resNumber = execMainBDQuery(strNumExec);

            if(resNumber.size()>0) strNumber = resNumber.at(0).at(0);
        }

        if(QUuid::fromString(resTasks.at(iTaskCounter).at(3)) == QUuid::fromString(QString("057b3b6f-2848-479b-a546-3f16cb531ffe"))) //Закрытая территория
        {
            QString strNumExec = QString("SELECT \"Расширение задачи Парковка\".Госномер From \"Расширение задачи Парковка\" , Задачи where Задачи.Расширение=\"Расширение задачи Парковка\".id and Задачи.id='%1'").arg(resTasks.at(iTaskCounter).at(0));

            QList<QStringList> resNumber = execMainBDQuery(strNumExec);

            if(resNumber.size()>0) strNumber = resNumber.at(0).at(0);
        }

        QString strTask = QString("%1 - %2 (%3) <b>%4</b> ")
                              .arg(QDateTime::fromSecsSinceEpoch(resTasks.at(iTaskCounter).at(1).toInt()).toString("dd.MM.yyyy hh:mm"))
                              .arg(resTasks.at(iTaskCounter).at(2))
                              .arg(resTasks.at(iTaskCounter).at(5))
                              .arg(strNumber);
        pItem->setText(strTask);
        if(resTasks.at(iTaskCounter).at(4).toInt() != 0) pItem->setIcon(QIcon(":/icons/done_icon.png"));
        pItem->setFlags(pItem->flags() & ~Qt::ItemIsSelectable);
        pItem->setData(Qt::UserRole , QUuid(resTasks.at(iTaskCounter).at(0)));//uuid задачи
        pItem->setData(Qt::UserRole+1 , QUuid(resTasks.at(iTaskCounter).at(3)));//тип задачи

        m_pTasksListWidget->addItem(pItem);
    }
}

void QEmploeeTasksDlg::FioClicked()
{
    QCarshServiceEmploeeCardDlg dlg(m_userUuid);
    dlg.exec();
}

void QEmploeeTasksDlg::OnTapHoldGesture()
{

}

void QEmploeeTasksDlg::OnReadyButtonTogled(bool bChecked)
{
    if(bChecked)
    {
        m_pNotReadyButton->blockSignals(true);
        m_pNotReadyButton->setChecked(false);
        m_pNotReadyButton->blockSignals(false);
        strFilter= " and Задачи.\"Время выполнения\">0 ";
        if(strDateFilter.length() < 4) //Если пытатся показать выполеннные задачи без выбранного времени, то принудительно ставим 2 последних суток
            strDateFilter=CreateDateBDPeriodFromNow("Задачи.\"Дата Время\"" , 2);
    }
    else
    {
        if(m_pReadyButton->isChecked() || ((!m_pReadyButton->isChecked())&&(!m_pNotReadyButton->isChecked())))
            strDateFilter=CreateDateBDPeriodFromNow("Задачи.\"Дата Время\"" , 2);
        else
            strDateFilter="";
        strFilter = "";
    }
    showWait(true);
    UpdateTasks();
    showWait(false);
}

void QEmploeeTasksDlg::OnNotReadyButtonTogled(bool bChecked)
{
    if(bChecked)
    {
        m_pReadyButton->blockSignals(true);
        m_pReadyButton->setChecked(false);
        m_pReadyButton->blockSignals(false);
        strFilter= " and Задачи.\"Время выполнения\"=0 ";
        if(!m_pToCalendarButton->isChecked()) strDateFilter="";
    }
    else
    {
        strFilter = "";
        if(m_pReadyButton->isChecked() || ((!m_pReadyButton->isChecked())&&(!m_pNotReadyButton->isChecked())))
            strDateFilter=CreateDateBDPeriodFromNow("Задачи.\"Дата Время\"" , 2);
        else
            strDateFilter="";
    }
    showWait(true);
    UpdateTasks();
    showWait(false);
}

void QEmploeeTasksDlg::OnToCalendatButtonTogled(bool bChecked)
{
    if(bChecked)
    {
        QCalendarDataSelectDlg calendarDlg(QDateTime::currentDateTime().date());
        if(calendarDlg.exec()==QDialog::Accepted)
        {
            qint64 timeFrom = QDateTime(calendarDlg.m_SelectedDate, QTime(0,0,0)).toSecsSinceEpoch();
            qint64 timeTo = timeFrom + 86400;
            strDateFilter = QString(" and Задачи.\"Дата Время\">%1 and Задачи.\"Дата Время\"<%2 ").arg(timeFrom).arg(timeTo);

        }
        else
        {
            if(m_pReadyButton->isChecked() || ((!m_pReadyButton->isChecked())&&(!m_pNotReadyButton->isChecked())))
                strDateFilter=CreateDateBDPeriodFromNow("Задачи.\"Дата Время\"" , 2);
            else
                strDateFilter="";
            m_pToCalendarButton->setChecked(false);
        }
    }
    else
    {
        if(m_pReadyButton->isChecked())
            strDateFilter=CreateDateBDPeriodFromNow("Задачи.\"Дата Время\"" , 2);
        else
        {
            if(m_pReadyButton->isChecked() || ((!m_pReadyButton->isChecked())&&(!m_pNotReadyButton->isChecked())))
                strDateFilter=CreateDateBDPeriodFromNow("Задачи.\"Дата Время\"" , 2);
            else
                strDateFilter="";
        }
    }
    showWait(true);
    UpdateTasks();
    showWait(false);
}

void QEmploeeTasksDlg::OnTapGesture()
{
    if(QListWidgetItem* item = m_pTasksListWidget->currentItem())
    {
        if(item->data(Qt::UserRole+1).toUuid()  == QUuid("99b4e860-5a7b-42a4-9136-f96252ef4192"))
        {

            QPlateTaskDialog dlg(this);
            showWait(true);
            dlg.LoadDataFromBD(item->data(Qt::UserRole).toUuid());
            dlg.exec();
            showWait(false);
        }
        if(item->data(Qt::UserRole+1).toUuid()  == QUuid("057b3b6f-2848-479b-a546-3f16cb531ffe"))
        {

            QParkingTaskDialog dlg(this);
            showWait(true);
            dlg.LoadDataFromBD(item->data(Qt::UserRole).toUuid());
            dlg.exec();
            showWait(false);
        }
        if(item->data(Qt::UserRole+1).toUuid()  == QUuid("8078b7ce-e423-49ae-9ce6-17758b852b33"))
        {
            QPenaltyParkingDialog dlg(this);
            showWait(true);
            dlg.LoadDataFromBD(item->data(Qt::UserRole).toUuid());
            dlg.exec();
            showWait(false);
        }
        if(item->data(Qt::UserRole+1).toUuid()  == QUuid("fe81daf9-a838-4bac-84aa-595e038d3a12"))
        {
            QRetToZoneDialog dlg(this);
            showWait(true);
            dlg.LoadDataFromBD(item->data(Qt::UserRole).toUuid());
            dlg.exec();
            showWait(false);
        }
        if(item->data(Qt::UserRole+1).toUuid()  == QUuid("78850df8-814b-41c8-8977-945c085f3021"))
        {
            QSmenaDlg dlg(this);
            showWait(true);
            dlg.LoadDataFromBD(item->data(Qt::UserRole).toUuid());
            dlg.exec();
            showWait(false);
        }
        if(item->data(Qt::UserRole+1).toUuid()  == QUuid("25695573-f5fe-43fd-93dc-76ee09e461fa"))
        {
            QDocsTaskDlg dlg(this);
            showWait(true);
            dlg.LoadDataFromBD(item->data(Qt::UserRole).toUuid());
            dlg.exec();
            showWait(false);
        }
    }
    qApp->inputMethod()->hide();
    showWait(true);
    UpdateTasks();
    showWait(false);
}
