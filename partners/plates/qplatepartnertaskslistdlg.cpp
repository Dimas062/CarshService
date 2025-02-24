#include "qplatepartnertaskslistdlg.h"
#include "common.h"
#include "service_widgets/qcalendardataselectdlg.h"
#include "service_widgets/qcsbaselistitemdelegate.h"
#include "partners/plates/qplatepartnertask.h"
#include <QEasingCurve>
#include <QGuiApplication>
#include <QPushButton>
#include <QScroller>
#include <QVBoxLayout>

extern QUuid uuidCurrentPartner;
extern QRect screenGeometry;


QPlatePartnerTasksListDlg::QPlatePartnerTasksListDlg(QWidget *parent, Qt::WindowFlags f ):QCSBaseDialog(parent , f , false)
{
    int iButtonHeight = (int)((screenGeometry.height()*0.7)/10)-10;

    strDateFilter = CreateDateBDPeriodFromNow("\"Задачи партнера Номера\".\"ДатаВремя\"" , 2);

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
    m_pTasksListWidget->setFixedHeight(screenGeometry.height() - 100 - iButtonHeight);
#endif
#if defined Q_OS_IOS || defined Q_OS_WINDOWS
    m_pTasksListWidget->setFixedHeight(screenGeometry.height() - 100 - iButtonHeight);
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

void QPlatePartnerTasksListDlg::UpdateTasks()
{
    m_pTasksListWidget->clear();

    QString strExec= QString("select \"Задачи партнера Номера\".id , \"Задачи партнера Номера\".ДатаВремя, \"Точки Партнеров\".Название from \"Задачи партнера Номера\", \"Точки Партнеров\"  where \"Точки Партнеров\".id = \"Задачи партнера Номера\".Точка and \"Задачи партнера Номера\".Партнер='%1'").arg(uuidCurrentPartner.toString());

    QList<QStringList> resTasks = execMainBDQuery(strExec);


    for(int iTaskCounter = 0 ; iTaskCounter < resTasks.size() ; iTaskCounter++)
    {

        QListWidgetItem * pItem = new QListWidgetItem();

        QString strTask = QString("%1 - %2").arg(QDateTime::fromSecsSinceEpoch(resTasks.at(iTaskCounter).at(1).toInt()).toString("dd.MM.yyyy hh:mm")).arg(resTasks.at(iTaskCounter).at(2));
        pItem->setText(strTask);
        pItem->setFlags(pItem->flags() & ~Qt::ItemIsSelectable);
        pItem->setData(Qt::UserRole , QUuid(resTasks.at(iTaskCounter).at(0)));//uuid задачи

        m_pTasksListWidget->addItem(pItem);
    }
}

void QPlatePartnerTasksListDlg::OnTapHoldGesture()
{

}

void QPlatePartnerTasksListDlg::OnTapGesture()
{
    if(QListWidgetItem* item = m_pTasksListWidget->currentItem())
    {
        QPlatePartnerTask dlg;
        showWait(true);
        dlg.LoadDataFromBD(item->data(Qt::UserRole).toUuid());
        dlg.exec();
        showWait(false);
    }
    UpdateTasks();
}

void QPlatePartnerTasksListDlg::OnToCalendatButtonTogled(bool bChecked)
{
    if(bChecked)
    {
        QCalendarDataSelectDlg calendarDlg(QDateTime::currentDateTime().date());
        if(calendarDlg.exec()==QDialog::Accepted)
        {
            qint64 timeFrom = QDateTime(calendarDlg.m_SelectedDate, QTime(0,0,0)).toSecsSinceEpoch();
            qint64 timeTo = timeFrom + 86400;
            strDateFilter = QString(" and \"Задачи партнера Номера\".ДатаВремя>%1 and \"Задачи партнера Номера\".ДатаВремя<%2 ").arg(timeFrom).arg(timeTo);

        }
        else
        {
            strDateFilter=CreateDateBDPeriodFromNow("\"Задачи партнера Номера\".Дата Время" , 2);;
            m_pToCalendarButton->setChecked(false);
        }
    }
    else strDateFilter=CreateDateBDPeriodFromNow("\"Задачи партнера Номера\".Дата Время" , 2);
    UpdateTasks();
}
