#include "qemplsalarydlg.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QScroller>
#include "service_widgets/qcsbaselistitemdelegate.h"
#include <QEasingCurve>
#include "common.h"
#include "BDPatterns.h"
#include <algorithm>
#include <QVector>
#include <QDateTime>
#include <QBrush>
#include "service_widgets/qmonthselectdlg.h"
#include "service_widgets/qcsselectdialog.h"
#include <QDate>
#include <QUuid>


extern QRect screenGeometry;
extern QUuid uuidCurrentUser;
extern int iButtonHeight;
extern QColor currentWorkdayColor;


QEmplSalaryDlg::QEmplSalaryDlg(QWidget *parent, Qt::WindowFlags f ):QCSBaseDialog(parent , f , false)
{
    m_currentDate = QDate::currentDate();

    QVBoxLayout * pVMainLayout = new QVBoxLayout;
    QHBoxLayout * pHFiltersLayout = new QHBoxLayout;

    m_pToCalendarButton = new QPushButton("");
    m_pToCalendarButton->setIcon(QIcon(":/icons/to_calendar_icon_256.png"));
    m_pToCalendarButton->setIconSize(QSize(iButtonHeight*0.75 , iButtonHeight*0.75));
    connect(m_pToCalendarButton,SIGNAL(clicked()),this,SLOT(OnToCalendarButtonClicked()));
    m_pToCalendarButton->setFixedHeight(iButtonHeight);
    m_pToCalendarButton->setFixedWidth(iButtonHeight);
    pHFiltersLayout->addWidget(m_pToCalendarButton);

    m_pToTaskTypeFilterButton = new QPushButton("");
    m_pToTaskTypeFilterButton->setIcon(QIcon(":/icons/filter_icon.png"));
    m_pToTaskTypeFilterButton->setIconSize(QSize(iButtonHeight*0.75 , iButtonHeight*0.75));
    connect(m_pToTaskTypeFilterButton,SIGNAL(clicked()),this,SLOT(OnToTaskTypeFilterButtonClicked()));
    m_pToTaskTypeFilterButton->setFixedHeight(iButtonHeight);
    m_pToTaskTypeFilterButton->setFixedWidth(iButtonHeight);
    pHFiltersLayout->addWidget(m_pToTaskTypeFilterButton);


    pVMainLayout->addLayout(pHFiltersLayout);

    m_pSalarysListWidget = new QCSBaseListWidget();
#ifdef Q_OS_ANDRIOD
    m_pTasksListWidget->setFixedHeight(screenGeometry.height() - 270 - iButtonHeight);
#endif
#if defined Q_OS_IOS || defined Q_OS_WINDOWS
    m_pSalarysListWidget->setFixedHeight(screenGeometry.height() - 270 - iButtonHeight);
#endif
    m_pSalarysListWidget->setItemDelegate(new QCSBaseListItemDelegate(m_pSalarysListWidget));

    QScrollerProperties sp;
    sp.setScrollMetric( QScrollerProperties::DragStartDistance, 0.001 );
    sp.setScrollMetric( QScrollerProperties::ScrollingCurve, QEasingCurve::Linear );
    QScroller* qs = QScroller::scroller( m_pSalarysListWidget );
    qs->setScrollerProperties( sp );

    QScroller::grabGesture(m_pSalarysListWidget, QScroller::TouchGesture);
    m_pSalarysListWidget->grabGesture(Qt::TapAndHoldGesture);
    m_pSalarysListWidget->grabGesture(Qt::TapGesture);
    m_pSalarysListWidget->setIconSize(QSize(47,27));
    m_pSalarysListWidget->setWordWrap(true);
    pVMainLayout->addWidget(m_pSalarysListWidget);
    //connect(m_pSalarysListWidget, SIGNAL(OnTapHoldGesture()), this, SLOT(OnTapHoldGesture()));
    //connect(m_pSalarysListWidget, SIGNAL(OnTapGesture()), this, SLOT(OnTapGesture()));

    m_pLabelSalary = new QLabel;
    m_pPenSalary = new QLabel;
    m_pPremSalary = new QLabel;
    m_pSummSalary = new QLabel;

    pVMainLayout->addWidget(m_pLabelSalary);
    pVMainLayout->addWidget(m_pPremSalary);
    pVMainLayout->addWidget(m_pPenSalary);
    pVMainLayout->addWidget(m_pSummSalary);

    UpdateSalarys();


    this->setLayout(pVMainLayout);
}

typedef struct
{
    QDateTime tm;
    QString str;
    QString id;
    bool bIsRed;

} SalaryItemStruct;

bool operator<(const SalaryItemStruct& a, const SalaryItemStruct& b) { return a.tm < b.tm; }

void QEmplSalaryDlg::OnToCalendarButtonClicked()
{
    QMonthSelectDlg dlg(m_currentDate);
    if(dlg.exec()==QDialog::Accepted)
    {
        m_currentDate = dlg.m_SelectedDate;
        showWait(true);
        UpdateSalarys();
        showWait(false);
    }
}

void QEmplSalaryDlg::OnToTaskTypeFilterButtonClicked()
{
    QCSSelectDialog dlg("Типы задач", "Тип" , false , true , QUuid() , "" , false , true);
    if(m_strCurrentTaskType.length()>10)
        dlg.SelectId(m_strCurrentTaskType);

    if(dlg.exec()==QDialog::Accepted)
        m_strCurrentTaskType = dlg.getCurId();
    else
        m_strCurrentTaskType = QString();

    UpdateSalarys();
}

void QEmplSalaryDlg::UpdateSalarys()
{
    QDate dateFrom = QDate(m_currentDate.year() ,m_currentDate.month() , 1 ) ;
    QDateTime dtFrom = QDateTime(dateFrom , QTime(0 ,0 ,0, 1));
    qint64 timeFrom = dtFrom.toSecsSinceEpoch();
    qint64 timeTo = QDateTime::fromSecsSinceEpoch(timeFrom).addMonths(1).toSecsSinceEpoch();

    m_pSalarysListWidget->clear();

    QVector<SalaryItemStruct> SalaryItems;

    QString strCondition;
    if(m_strCurrentTaskType.length()>10 && (QUuid::fromString(m_strCurrentTaskType) != QUuid::fromString("00000000-0000-0000-0000-000000000000")))
        strCondition = QString(" and \"Типы задач\".id = '%1'").arg(m_strCurrentTaskType);

    QString strQuery =  QString("SELECT Задачи.id, Задачи.\"Время выполнения\", \"Типы задач\".\"Тип\" , Заказчики.Название , Задачи.Цена , %2 FROM \"Типы задач\", Задачи, Заказчики where Заказчики.id=Задачи.Заказчик and Задачи.Тип = \"Типы задач\".id and Задачи.Удалено<> 'true' and Задачи.Исполнитель='%1' and Задачи.\"Время выполнения\">%3 and Задачи.\"Время выполнения\"<%4 %5 order by Задачи.\"Время выполнения\" desc").arg(uuidCurrentUser.toString()).arg(NUMBER_BY_TASK).arg(timeFrom).arg(timeTo).arg(strCondition);

    qDebug()<<strQuery;

    QList<QStringList> resSalarys = execMainBDQuery(strQuery);

    double dblSalarySum = 0;
    int iSalaryCount = 0;

    for(int iSalaryCounter = 0 ; iSalaryCounter < resSalarys.size() ; iSalaryCounter++)
    {
        SalaryItemStruct salaryItem;
        salaryItem.tm = QDateTime::fromSecsSinceEpoch(resSalarys.at(iSalaryCounter).at(1).toInt());
        salaryItem.str = QString("%1: %2 %5 (%3) %4 р.").arg(salaryItem.tm.toString("dd.MM.yyyy ")).arg(resSalarys.at(iSalaryCounter).at(2)).arg(resSalarys.at(iSalaryCounter).at(3)).arg(resSalarys.at(iSalaryCounter).at(4)).arg(resSalarys.at(iSalaryCounter).at(5));
        salaryItem.id = resSalarys.at(iSalaryCounter).at(0);
        salaryItem.bIsRed = false;
        QString strSalarySum = resSalarys.at(iSalaryCounter).at(4);
        strSalarySum.replace('.',',');
        dblSalarySum = dblSalarySum + strSalarySum.toDouble();
        SalaryItems.push_back(salaryItem);
        iSalaryCount++;
    }

    strQuery =  QString("SELECT ДатаВремя, Значение , Комментарий FROM ПоощренияНаказания where Сотрудник='%1' and ДатаВремя>%2 and ДатаВремя<%3").arg(uuidCurrentUser.toString()).arg(timeFrom).arg(timeTo);
    QList<QStringList> resPens = execMainBDQuery(strQuery);


    double dblPensSum = 0;
    double dblPremsSum = 0;

    for(int iPenCounter = 0 ; iPenCounter < resPens.size() ; iPenCounter++)
    {
        SalaryItemStruct salaryItem;
        salaryItem.tm = QDateTime::fromSecsSinceEpoch(resPens.at(iPenCounter).at(0).toInt());
        int iPenBalls = resPens.at(iPenCounter).at(1).toInt();
        double dblPenSumm = dblSalarySum * 0.1 * iPenBalls;
        salaryItem.str = QString("%1: %2 - %4 р. (%3 балла)").arg(salaryItem.tm.toString("dd.MM.yyyy ")).arg(resPens.at(iPenCounter).at(2)).arg(iPenBalls).arg(dblPenSumm);
        salaryItem.id = resSalarys.at(iPenCounter).at(0);

        if(dblPenSumm < 0) dblPensSum = dblPensSum + dblPenSumm;
        if(dblPenSumm > 0) dblPremsSum = dblPremsSum + dblPenSumm;
        SalaryItems.push_back(salaryItem);
    }


    std::sort(SalaryItems.begin() , SalaryItems.end());

    foreach(SalaryItemStruct SalaryItem , SalaryItems)
    {
        QListWidgetItem * pItem = new QListWidgetItem(SalaryItem.str);

        QBrush brushBackground(Qt::red);

        if(SalaryItem.bIsRed) brushBackground.setColor(QColor::fromRgb(255 , 50 ,50));
        else brushBackground.setColor(QColor::fromRgb(50 , 255 ,50));

        m_pSalarysListWidget->addItem(pItem);
    }

    m_pLabelSalary->setText(QString("Задач %1 Начислено %2 руб.").arg(iSalaryCount).arg(dblSalarySum));
    m_pPremSalary->setText(QString("Премии %1 руб.").arg(dblPremsSum));
    m_pPenSalary->setText(QString("Штраф %1 руб.").arg(dblPensSum));
    m_pSummSalary->setText(QString("Итого %1 руб.").arg(dblSalarySum + dblPensSum + dblPremsSum));
}
