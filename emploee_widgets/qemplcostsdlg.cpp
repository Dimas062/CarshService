#include "qemplcostsdlg.h"
#include <QEasingCurve>
#include <QGuiApplication>
#include <QPushButton>
#include <QScroller>
#include <QVBoxLayout>
#include "common.h"
#include "service_widgets/qcsbaselistitemdelegate.h"
#include "tasks/qcostsdialog.h"

extern QRect screenGeometry;
extern int iButtonHeight;
extern UserTypes CurrentUserType;

QEmplCostsDlg::QEmplCostsDlg(QUuid userUuid, QWidget *parent, Qt::WindowFlags f ):QCSBaseDialog(parent , f , false)
{
    int iButtonHeight = (int)((screenGeometry.height()*0.7)/10)-10;

    m_userUuid = userUuid;

    QVBoxLayout * pVMainLayout = new QVBoxLayout;

    m_pCostsListWidget = new QCSBaseListWidget();
#ifdef Q_OS_ANDRIOD
    m_pCostsListWidget->setFixedHeight(screenGeometry.height() - 270 - iButtonHeight*2);
#endif
#if defined Q_OS_IOS || defined Q_OS_WINDOWS
    m_pCostsListWidget->setFixedHeight(screenGeometry.height() - 170 - iButtonHeight*2);
#endif
    m_pCostsListWidget->setItemDelegate(new QCSBaseListItemDelegate(m_pCostsListWidget));

    QScrollerProperties sp;
    sp.setScrollMetric( QScrollerProperties::DragStartDistance, 0.001 );
    sp.setScrollMetric( QScrollerProperties::ScrollingCurve, QEasingCurve::Linear );
    QScroller* qs = QScroller::scroller( m_pCostsListWidget );
    qs->setScrollerProperties( sp );

    QScroller::grabGesture(m_pCostsListWidget, QScroller::TouchGesture);
    m_pCostsListWidget->grabGesture(Qt::TapAndHoldGesture);
    m_pCostsListWidget->grabGesture(Qt::TapGesture);
    m_pCostsListWidget->setIconSize(QSize(47,27));
    m_pCostsListWidget->setWordWrap(true);
    pVMainLayout->addWidget(m_pCostsListWidget);
    connect(m_pCostsListWidget, SIGNAL(OnTapGesture()), this, SLOT(OnTapGesture()));
    UpdateCosts();

    this->setLayout(pVMainLayout);
}

void QEmplCostsDlg::UpdateCosts()
{

    m_pCostsListWidget->clear();

    QString strExec= QString("SELECT Расходы.id, Расходы.\"Дата Время\" , \"Платежи сотрудников\".Сумма , Товары.Товар  FROM Расходы, \"Платежи сотрудников\", Товары where Расходы.Удалено<>'true' and Расходы.Товар=Товары.id and Расходы.Оплата=\"Платежи сотрудников\".id and Расходы.Сотрудник='%1' order by Расходы.\"Дата Время\" desc").arg(m_userUuid.toString());

    QList<QStringList> resCosts = execMainBDQuery(strExec);


    for(int iCostCounter = 0 ; iCostCounter < resCosts.size() ; iCostCounter++)
    {
        QListWidgetItem * pItem = new QListWidgetItem();

        QString strTask = QString("%1 - %2 р. (%3)").arg(QDateTime::fromSecsSinceEpoch(resCosts.at(iCostCounter).at(1).toInt()).toString("dd.MM.yyyy hh:mm")).arg(resCosts.at(iCostCounter).at(2)).arg(resCosts.at(iCostCounter).at(3));
        pItem->setText(strTask);
        pItem->setFlags(pItem->flags() & ~Qt::ItemIsSelectable);
        pItem->setData(Qt::UserRole , QUuid(resCosts.at(iCostCounter).at(0)));//uuid задачи
        m_pCostsListWidget->addItem(pItem);
    }
}

void QEmplCostsDlg::OnTapGesture()
{
    if(QListWidgetItem* item = m_pCostsListWidget->currentItem())
    {

        QCostsDialog dlg(this);
        showWait(true);
        dlg.LoadDataFromBD(item->data(Qt::UserRole).toUuid());
        dlg.exec();
        showWait(false);
    }
    qApp->inputMethod()->hide();
    showWait(true);
    UpdateCosts();
    showWait(false);
}
