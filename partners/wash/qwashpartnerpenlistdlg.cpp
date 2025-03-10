#include "qwashpartnerpenlistdlg.h"
#include <QEasingCurve>
#include <QGuiApplication>
#include <QPushButton>
#include <QScroller>
#include <QVBoxLayout>
#include "service_widgets/qcsbaselistitemdelegate.h"
#include "common.h"
#include "partners/wash/qwashpartnerpendlg.h"


extern QRect screenGeometry;

QWashPartnerPenListDlg::QWashPartnerPenListDlg(QUuid task , QWidget *parent, Qt::WindowFlags f ):QCSBaseDialog(parent , f , false)
{
    int iButtonHeight = (int)((screenGeometry.height()*0.7)/10)-10;

    m_uuidTask = task;
    QVBoxLayout * pVMainLayout = new QVBoxLayout;

    m_pPenListWidget = new QCSBaseListWidget();
#ifdef Q_OS_ANDRIOD
    m_pPenListWidget->setFixedHeight(screenGeometry.height() - 100 - iButtonHeight);
#endif
#if defined Q_OS_IOS || defined Q_OS_WINDOWS
    m_pPenListWidget->setFixedHeight(screenGeometry.height() - 100 - iButtonHeight);
#endif
    m_pPenListWidget->setItemDelegate(new QCSBaseListItemDelegate(m_pPenListWidget));

    QScrollerProperties sp;
    sp.setScrollMetric( QScrollerProperties::DragStartDistance, 0.001 );
    sp.setScrollMetric( QScrollerProperties::ScrollingCurve, QEasingCurve::Linear );
    QScroller* qs = QScroller::scroller( m_pPenListWidget );
    qs->setScrollerProperties( sp );

    QScroller::grabGesture(m_pPenListWidget, QScroller::TouchGesture);
    m_pPenListWidget->grabGesture(Qt::TapAndHoldGesture);
    m_pPenListWidget->grabGesture(Qt::TapGesture);
    m_pPenListWidget->setIconSize(QSize(47,27));
    m_pPenListWidget->setWordWrap(true);
    pVMainLayout->addWidget(m_pPenListWidget);
    connect(m_pPenListWidget, SIGNAL(OnTapGesture()), this, SLOT(OnTapGesture()));
    UpdatePens();

    this->setLayout(pVMainLayout);
}

void QWashPartnerPenListDlg::UpdatePens()
{

    QString strExec= QString("select \"Отмена Мойки\".id, \"Отмена Мойки\".Количество, \"Отмена Мойки\".Ночь , \"Типы задач Мойка\".Тип from \"Отмена Мойки\" , \"Типы задач Мойка\" where \"Отмена Мойки\".Тип = \"Типы задач Мойка\".id and \"Отмена Мойки\".Задача = '%1' and \"Отмена Мойки\".Удалено=false").arg(m_uuidTask.toString());

    QList<QStringList> resPens = execMainBDQuery(strExec);


    for(int iPensCounter = 0 ; iPensCounter < resPens.size() ; iPensCounter++)
    {

        QListWidgetItem * pItem = new QListWidgetItem();

        QString strNigth("День");
        if(resPens.at(iPensCounter).at(2) == "true") strNigth="Ночь";


        QString strPens  = QString("%1(%2) Количество: %3.").arg(resPens.at(iPensCounter).at(3)).arg(strNigth).arg(resPens.at(iPensCounter).at(1));


        pItem->setText(strPens);
        pItem->setFlags(pItem->flags() & ~Qt::ItemIsSelectable);
        pItem->setData(Qt::UserRole , QUuid(resPens.at(iPensCounter).at(0)));//uuid задачи

        m_pPenListWidget->addItem(pItem);
    }
}

void QWashPartnerPenListDlg::OnTapGesture()
{
    if(QListWidgetItem* item = m_pPenListWidget->currentItem())
    {
        QUuid taskId = item->data(Qt::UserRole).toUuid();
        QWashPartnerPenDlg dlg(taskId);
        dlg.exec();
        showWait(true);
        UpdatePens();
        showWait(false);
    }

}
