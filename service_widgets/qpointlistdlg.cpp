#include "qpointlistdlg.h"
#include <QEasingCurve>
#include <QGuiApplication>
#include <QPushButton>
#include <QScroller>
#include <QVBoxLayout>
#include <QLabel>
#include "common.h"
#include "service_widgets/qcsbaselistitemdelegate.h"
#include "service_widgets/qparnerpointdlg.h"

extern QRect screenGeometry;
extern int iButtonHeight;
extern UserTypes CurrentUserType;

QPointListDlg::QPointListDlg(QWidget *parent, Qt::WindowFlags f ):QCSBaseDialog(parent , f , false)
{
    m_uuidPartner = QUuid();

    QVBoxLayout * pVMainLayout = new QVBoxLayout;

    QLabel *  pTopLabel = new QLabel("<b>Точки партнера</b>");
    pTopLabel->setStyleSheet("font-size: 20px;");
    pVMainLayout->addWidget(pTopLabel);

    m_pPointsListWidget = new QCSBaseListWidget();
#ifdef Q_OS_ANDRIOD
    m_pPointsListWidget->setFixedHeight(screenGeometry.height() - 200 - iButtonHeight);
#endif
#if defined Q_OS_IOS || defined Q_OS_WINDOWS
    m_pPointsListWidget->setFixedHeight(screenGeometry.height() - 200 - iButtonHeight);
#endif
    m_pPointsListWidget->setItemDelegate(new QCSBaseListItemDelegate(m_pPointsListWidget));

    QScrollerProperties sp;
    sp.setScrollMetric( QScrollerProperties::DragStartDistance, 0.001 );
    sp.setScrollMetric( QScrollerProperties::ScrollingCurve, QEasingCurve::Linear );
    QScroller* qs = QScroller::scroller( m_pPointsListWidget );
    qs->setScrollerProperties( sp );

    QScroller::grabGesture(m_pPointsListWidget, QScroller::TouchGesture);
    m_pPointsListWidget->grabGesture(Qt::TapAndHoldGesture);
    m_pPointsListWidget->grabGesture(Qt::TapGesture);
    m_pPointsListWidget->setIconSize(QSize(47,27));
    m_pPointsListWidget->setWordWrap(true);
    pVMainLayout->addWidget(m_pPointsListWidget);
    connect(m_pPointsListWidget, SIGNAL(OnTapGesture()), this, SLOT(OnTapGesture()));

    QHBoxLayout * pButtonsHLayout = new QHBoxLayout;


    m_pAddButton = new QPushButton("Добавить");
    m_pAddButton->setIcon(QIcon(":/icons/add_plus_icon.png"));
    m_pAddButton->setIconSize(QSize(iButtonHeight*0.75 , iButtonHeight*0.75));
    connect(m_pAddButton,SIGNAL(pressed()),this,SLOT(OnAddPressed()));
    m_pAddButton->setMaximumHeight(iButtonHeight);
    m_pAddButton->setMinimumHeight(iButtonHeight);
    pButtonsHLayout->addWidget(m_pAddButton);

    m_pRemoveButton = new QPushButton("Удалить");
    m_pRemoveButton->setIcon(QIcon(":/icons/remove_icon.png"));
    m_pRemoveButton->setIconSize(QSize(iButtonHeight*0.75 , iButtonHeight*0.75));
    connect(m_pRemoveButton,SIGNAL(pressed()),this,SLOT(OnRemovePressed()));
    m_pRemoveButton->setMaximumHeight(iButtonHeight);
    m_pRemoveButton->setMinimumHeight(iButtonHeight);
    pButtonsHLayout->addWidget(m_pRemoveButton);

    pVMainLayout->addLayout(pButtonsHLayout);

    QPushButton * pApplyButton = new QPushButton("Отправить");
    connect(pApplyButton,SIGNAL(pressed()),this,SLOT(accept()));
    pVMainLayout->addWidget(pApplyButton);

    this->setLayout(pVMainLayout);
}


void QPointListDlg::LoadFromBD(QUuid uuidPartner)
{
    m_uuidPartner = uuidPartner;
    if(m_uuidPartner != QUuid())
    {
        m_pPointsListWidget->clear();

        QString strPartnerPointQuery = QString("select id, Название, Адрес from \"Точки партнеров\" where Партнер = '%1' and Удалено<>'true'").arg(m_uuidPartner.toString());

        QList<QStringList> resPartnerPoints = execMainBDQuery(strPartnerPointQuery);

        for(int iPartnerPointCounter = 0 ; iPartnerPointCounter < resPartnerPoints.size() ; iPartnerPointCounter++)
        {
            QListWidgetItem * pItem = new QListWidgetItem();

            QString strPoint = QString("%1").arg(resPartnerPoints.at(iPartnerPointCounter).at(1));
            pItem->setText(strPoint);
            pItem->setFlags(pItem->flags() & ~Qt::ItemIsSelectable);
            pItem->setData(Qt::UserRole , resPartnerPoints.at(iPartnerPointCounter).at(0));
            pItem->setData(Qt::UserRole + 1, resPartnerPoints.at(iPartnerPointCounter).at(1));
            pItem->setData(Qt::UserRole + 2, resPartnerPoints.at(iPartnerPointCounter).at(2));
            m_pPointsListWidget->addItem(pItem);
        }
    }
}

void QPointListDlg::SaveUpdateToBD(QUuid uuidPartner)
{

    if(m_uuidPartner == QUuid())//new
    {
        int iItemCount = m_pPointsListWidget->count();

        for(int iItemCounter = 0 ; iItemCounter<iItemCount ; iItemCounter++)
        {
            QString strId = m_pPointsListWidget->item(iItemCounter)->data(Qt::UserRole).toString();
            QString strName = m_pPointsListWidget->item(iItemCounter)->data(Qt::UserRole+1).toString();
            QString strAddr = m_pPointsListWidget->item(iItemCounter)->data(Qt::UserRole+2).toString();

            QString strInsExec = QString("insert into \"Точки Партнеров\" (id , Название , Адрес, Партнер) values ('%1' , '%2' ,'%3' ,'%4')").arg(strId).arg(strName).arg(strAddr).arg(uuidPartner.toString());

            execMainBDQueryUpdate(strInsExec);
        }
    }
    else//update
    {
        int iItemCount = m_pPointsListWidget->count();

        /*Сначала пометим удаленными все точки данного партнера*/
        QString strDelExec = QString("update  \"Точки Партнеров\" set Удалено='true' where Партнер='%1' ").arg(uuidPartner.toString());

        execMainBDQueryUpdate(strDelExec);

        for(int iItemCounter = 0 ; iItemCounter<iItemCount ; iItemCounter++)
        {
            QString strId = m_pPointsListWidget->item(iItemCounter)->data(Qt::UserRole).toString();
            QString strName = m_pPointsListWidget->item(iItemCounter)->data(Qt::UserRole).toString();
            QString strAddr = m_pPointsListWidget->item(iItemCounter)->data(Qt::UserRole).toString();

            /*Добавим или обновим оставшиеся в списке*/


            QString strInsExec = QString("insert into \"Точки Партнеров\" (id , Название , Адрес, Партнер) values ('%1' , '%2' ,'%3' ,'%4') ON DUPLICATE KEY UPDATE Название='%2', Адрес='%3', Удалено = 'false' ").arg(strId).arg(strName).arg(strAddr).arg(uuidPartner.toString());

            execMainBDQueryUpdate(strInsExec);
        }
    }
}

void QPointListDlg::OnAddPressed()
{
    QParnerPointDlg dlg;
    if(dlg.exec() == QDialog::Accepted)
    {
        QListWidgetItem * pItem = new QListWidgetItem();

        QString strPoint = QString("%1").arg(dlg.m_pLineTextName->getText());
        pItem->setText(strPoint);
        pItem->setFlags(pItem->flags() & ~Qt::ItemIsSelectable);
        pItem->setData(Qt::UserRole , QUuid::createUuid().toString());
        pItem->setData(Qt::UserRole + 1, dlg.m_pLineTextName->getText());
        pItem->setData(Qt::UserRole + 2, dlg.m_pLineTextAddr->getText());
        m_pPointsListWidget->addItem(pItem);
    }
}

void QPointListDlg::OnRemovePressed()
{
    if(QListWidgetItem* item = m_pPointsListWidget->currentItem())
    {
        m_pPointsListWidget->removeItemWidget(item);
    }
}

void QPointListDlg::OnTapGesture()
{
    if(QListWidgetItem* item = m_pPointsListWidget->currentItem())
    {
        QParnerPointDlg dlg;
        dlg.m_pLineTextName->setText(item->data(Qt::UserRole + 1).toString());
        dlg.m_pLineTextAddr->setText(item->data(Qt::UserRole + 2).toString());
        if(dlg.exec() == QDialog::Accepted)
        {
            item->setText(dlg.m_pLineTextName->getText());
            item->setData(Qt::UserRole + 1, dlg.m_pLineTextName->getText());
            item->setData(Qt::UserRole + 2, dlg.m_pLineTextAddr->getText());
        }
    }

}

