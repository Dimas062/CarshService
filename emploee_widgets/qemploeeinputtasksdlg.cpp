#include "qemploeeinputtasksdlg.h"
#include "common.h"
#include "service_widgets/qclicablelabel.h"
#include "service_widgets/qcsbaselistitemdelegate.h"
#include "carsh_service_widgets/qcarshserviceemploeecarddlg.h"
#include <QEasingCurve>
#include <QGuiApplication>
#include <QPushButton>
#include <QScroller>
#include <QVBoxLayout>

extern QRect screenGeometry;
extern int iButtonHeight;
extern UserTypes CurrentUserType;
extern QUuid uuidCurrentUser;

QEmploeeInputTasksDlg::QEmploeeInputTasksDlg(QUuid userUuid, QWidget *parent, Qt::WindowFlags f ):QCSBaseDialog(parent , f , false)
{
    int iButtonHeight = (int)((screenGeometry.height()*0.7)/10)-10;

    m_userUuid = userUuid;

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

    QPushButton * pApplyButton = new QPushButton("Взять задачу");
    pApplyButton->setIcon(QIcon(":/icons/done_icon.png"));
    pApplyButton->setIconSize(QSize(iButtonHeight*0.75 , iButtonHeight*0.75));
    pVMainLayout->addWidget(pApplyButton);
    connect(pApplyButton,SIGNAL(released()),this,SLOT(OnApplyTaskPressed()));

    UpdateTasks();
    this->setLayout(pVMainLayout);
}

void QEmploeeInputTasksDlg::UpdateTasks()
{
    //штрафстоянки ситидрайв
    m_pTasksListWidget->clear();

    QString strExec= QString("SELECT ЗадачиЗаказчикаШС.id, Штрафстоянки.Название, ЗадачиЗаказчикаШС.Госномер , ЗадачиЗаказчикаШС.ДатаВремяПомещения, Заказчики.Название , ЗадачиЗаказчикаШС.Штрафстоянка , ЗадачиЗаказчикаШС.Заказчик FROM ЗадачиЗаказчикаШС, Штрафстоянки, Заказчики where Заказчики.id=ЗадачиЗаказчикаШС.Заказчик and Штрафстоянки.id = ЗадачиЗаказчикаШС.Штрафстоянка and ЗадачиЗаказчикаШС.ПереведенаВЗадачу IS NULL and ЗадачиЗаказчикаШС.Заказчик in (select Заказчик from ИсполнителиЗаказчики where ИсполнительПартнер = '%1') and ЗадачиЗаказчикаШС.ДатаВремяПомещения > '%2'").arg(uuidCurrentUser.toString()).arg(QDateTime::currentSecsSinceEpoch() - 4*24*60*60);

    QList<QStringList> resTasks = execMainBDQuery(strExec);


    for(int iTaskCounter = 0 ; iTaskCounter < resTasks.size() ; iTaskCounter++)
    {

        QListWidgetItem * pItem = new QListWidgetItem();

        QString strNumber = " ";

        QString strTask = QString("Штрафстоянка %1 %2 %3 (%4)").arg(resTasks.at(iTaskCounter).at(1)).arg(resTasks.at(iTaskCounter).at(2)).arg(QDateTime::fromSecsSinceEpoch(resTasks.at(iTaskCounter).at(3).toInt()).toString("dd.MM.yyyy hh:mm")).arg(resTasks.at(iTaskCounter).at(4));
        pItem->setText(strTask);
        //if(resTasks.at(iTaskCounter).at(4).toInt() != 0) pItem->setIcon(QIcon(":/icons/done_icon.png"));
        //pItem->setFlags(pItem->flags() & ~Qt::ItemIsSelectable);
        pItem->setData(Qt::UserRole , QUuid::fromString(resTasks.at(iTaskCounter).at(0)));//uuid задачи
        pItem->setData(Qt::UserRole + 1, QUuid::fromString("8078b7ce-e423-49ae-9ce6-17758b852b33"));//uuid типа задачи
        pItem->setData(Qt::UserRole + 2, QUuid::fromString(resTasks.at(iTaskCounter).at(5)));//uuid штрафстоянки
        pItem->setData(Qt::UserRole + 3, resTasks.at(iTaskCounter).at(2));//госномер
        pItem->setData(Qt::UserRole + 4, resTasks.at(iTaskCounter).at(6));//Заказчик
        m_pTasksListWidget->addItem(pItem);
    }
}

void QEmploeeInputTasksDlg::OnApplyTaskPressed()
{
    if(QListWidgetItem* item = m_pTasksListWidget->currentItem())
    {
        m_strApplyedTaskUuid = item->data(Qt::UserRole).toString();
        m_strApplyedTaskTypeUuid = item->data(Qt::UserRole + 1).toString();
        m_strApplyedNumber = item->data(Qt::UserRole + 3).toString();
        m_strApplyedPenParkUuid = item->data(Qt::UserRole + 2).toString();
        m_strApplyedZakazchikUuid = item->data(Qt::UserRole + 4).toString();
        accept();
    }
}

void QEmploeeInputTasksDlg::FioClicked()
{
    QCarshServiceEmploeeCardDlg dlg(m_userUuid);
    dlg.exec();
}
