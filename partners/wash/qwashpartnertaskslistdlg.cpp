#include "qWashpartnertaskslistdlg.h"
#include "common.h"
#include "service_widgets/qcalendardataselectdlg.h"
#include "service_widgets/qcsbaselistitemdelegate.h"
#include "partners/wash/qWashpartnertask.h"
#include <QEasingCurve>
#include <QGuiApplication>
#include <QPushButton>
#include <QScroller>
#include <QVBoxLayout>


#include <QProgressDialog>
#include <QFuture>
#include <QThread>
#include <QApplication>
#include <QtConcurrent>
#include <QSplashScreen>

extern QUuid uuidCurrentPartner;
extern QRect screenGeometry;


QWashPartnerTasksListDlg::QWashPartnerTasksListDlg(QWidget *parent, Qt::WindowFlags f ):QCSBaseDialog(parent , f , false)
{
    int iButtonHeight = (int)((screenGeometry.height()*0.7)/10)-10;

    m_strDateFilter = CreateDateBDPeriodFromNow("\"Задачи партнера Мойка\".\"ДатаВремя\"" , 2);

    QVBoxLayout * pVMainLayout = new QVBoxLayout;

    QHBoxLayout * pHFiltersLayout = new QHBoxLayout;

    m_pToCalendarButton = new QPushButton("");
    m_pToCalendarButton->setIcon(QIcon(":/icons/to_calendar_icon_256.png"));
    m_pToCalendarButton->setIconSize(QSize(iButtonHeight*0.75 , iButtonHeight*0.75));
    m_pToCalendarButton->setCheckable(true);
    connect(m_pToCalendarButton,SIGNAL(toggled(bool)),this,SLOT(OnToCalendatButtonTogled(bool)));
    m_pToCalendarButton->setFixedHeight(iButtonHeight);
    m_pToCalendarButton->setFixedWidth(iButtonHeight);
    pHFiltersLayout->addWidget(m_pToCalendarButton);

    pVMainLayout->addLayout(pHFiltersLayout);

    m_pTasksListWidget = new QCSBaseListWidget();
#ifdef Q_OS_ANDRIOD
    m_pTasksListWidget->setFixedHeight(screenGeometry.height() - 170 - iButtonHeight);
#endif
#if defined Q_OS_IOS || defined Q_OS_WINDOWS
    m_pTasksListWidget->setFixedHeight(screenGeometry.height() - 170 - iButtonHeight);
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
    UpdateTasks();

    this->setLayout(pVMainLayout);
}

void QWashPartnerTasksListDlg::UpdateTasks()
{
    m_pTasksListWidget->clear();

    //QString strExec= QString("select \"Задачи партнера Мойка\".id , \"Задачи партнера Мойка\".ДатаВремя, \"Точки Партнеров\".Название from \"Задачи партнера Мойка\", \"Точки Партнеров\"  where \"Точки Партнеров\".id = \"Задачи партнера Мойка\".Точка and \"Задачи партнера Мойка\".Партнер='%1' %2").arg(uuidCurrentPartner.toString()).arg(m_strDateFilter);
    QString strExec= QString("select \"Задачи партнера Мойка\".id, \"Задачи партнера Мойка\".ДатаВремя, \"Точки Партнеров\".Название , (select SUM(\"Отмена Мойки\".Количество * \"Типы задач Мойка\".Цена) from \"Отмена Мойки\" , \"Типы задач Мойка\" where \"Отмена Мойки\".Задача=\"Задачи партнера Мойка\".id and \"Отмена Мойки\".Тип=\"Типы задач Мойка\".id and \"Отмена Мойки\".Удалено=false) as Штрафы , (select  SUM(\"Типы задач Мойка\".Цена * \"Задача Мойка - Типы\".Количество) from \"Задача Мойка - Типы\" , \"Типы задач Мойка\"  where \"Типы задач Мойка\".id = \"Задача Мойка - Типы\".Тип and  \"Задача Мойка - Типы\".Задача = \"Задачи партнера Мойка\".id) as summ  from  \"Задачи партнера Мойка\", \"Точки Партнеров\"  where \"Точки Партнеров\".id = \"Задачи партнера Мойка\".Точка and \"Задачи партнера Мойка\".Партнер='%1' %2").arg(uuidCurrentPartner.toString()).arg(m_strDateFilter);
    QList<QStringList> resTasks = execMainBDQuery(strExec);


    for(int iTaskCounter = 0 ; iTaskCounter < resTasks.size() ; iTaskCounter++)
    {

        QListWidgetItem * pItem = new QListWidgetItem();

        QString strTask;
        if(resTasks.at(iTaskCounter).at(3).toInt() > 0)
        {
          strTask  = QString("%1 - %2\nСумма: %3 руб. \nАннуляция:%4").arg(QDateTime::fromSecsSinceEpoch(resTasks.at(iTaskCounter).at(1).toInt()).toString("dd.MM.yyyy hh:mm")).arg(resTasks.at(iTaskCounter).at(2)).arg(resTasks.at(iTaskCounter).at(4)).arg(resTasks.at(iTaskCounter).at(3));
          pItem->setIcon(QIcon(":/icons/remove_icon.png"));
        }
        else
        {
            strTask  = QString("%1 - %2\nСумма: %3 руб.").arg(QDateTime::fromSecsSinceEpoch(resTasks.at(iTaskCounter).at(1).toInt()).toString("dd.MM.yyyy hh:mm")).arg(resTasks.at(iTaskCounter).at(2)).arg(resTasks.at(iTaskCounter).at(4));
        }

        pItem->setText(strTask);
        pItem->setFlags(pItem->flags() & ~Qt::ItemIsSelectable);
        pItem->setData(Qt::UserRole , QUuid(resTasks.at(iTaskCounter).at(0)));//uuid задачи

        m_pTasksListWidget->addItem(pItem);
    }
}

void QWashPartnerTasksListDlg::OnTapHoldGesture()
{

}

void QWashPartnerTasksListDlg::OnTapGesture()
{
    debug_TimeStamp("QWashPartnerTasksListDlg::OnTapGesture()");
    if(QListWidgetItem* item = m_pTasksListWidget->currentItem())
    {
        QWashPartnerTask dlg;

        showWait(true);

        dlg.LoadDataFromBD(item->data(Qt::UserRole).toUuid());

        dlg.exec();

        UpdateTasks();

        showWait(false);

    }
}

void QWashPartnerTasksListDlg::OnToCalendatButtonTogled(bool bChecked)
{
    if(bChecked)
    {
        QCalendarDataSelectDlg calendarDlg(QDateTime::currentDateTime().date());
        if(calendarDlg.exec()==QDialog::Accepted)
        {
            qint64 timeFrom = QDateTime(calendarDlg.m_SelectedDate, QTime(0,0,0)).toSecsSinceEpoch();
            qint64 timeTo = timeFrom + 86400;
            m_strDateFilter = QString(" and \"Задачи партнера Мойка\".ДатаВремя>%1 and \"Задачи партнера Мойка\".ДатаВремя<%2 ").arg(timeFrom).arg(timeTo);

        }
        else
        {
            m_strDateFilter=CreateDateBDPeriodFromNow("\"Задачи партнера Мойка\".Дата Время" , 2);;
            m_pToCalendarButton->setChecked(false);
        }
    }
    else m_strDateFilter=CreateDateBDPeriodFromNow("\"Задачи партнера Мойка\".Дата Время" , 2);
    showWait(true);
    UpdateTasks();
    showWait(false);
}
