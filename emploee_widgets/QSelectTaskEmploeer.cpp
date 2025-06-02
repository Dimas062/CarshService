#include "QSelectTaskEmploeer.h"
#include <QEasingCurve>
#include <QGuiApplication>
#include <QPushButton>
#include <QScroller>
#include <QVBoxLayout>
#include "service_widgets/qcsbaselistitemdelegate.h"
#include "common.h"

extern QRect screenGeometry;


QSelectTaskEmploeer::QSelectTaskEmploeer(QWidget *parent, Qt::WindowFlags f, QString strUuidTask):QCSBaseDialog(parent , f )
{
    int iButtonHeight = (int)((screenGeometry.height()*0.7)/9)-10;
    m_strUuidTask = strUuidTask;

    QVBoxLayout * pVMainLayout = new QVBoxLayout;

    m_pEmploeeListWidget = new QCSBaseListWidget();


#ifdef Q_OS_ANDRIOD
    m_pEmploeeListWidget->setFixedHeight(screenGeometry.height() - 270 - iButtonHeight*2);
#endif
#if defined Q_OS_IOS || defined Q_OS_WINDOWS
    m_pEmploeeListWidget->setFixedHeight(screenGeometry.height() - 170 - iButtonHeight*2);
#endif
    m_pEmploeeListWidget->setItemDelegate(new QCSBaseListItemDelegate(m_pEmploeeListWidget));
    QScrollerProperties sp;
    sp.setScrollMetric( QScrollerProperties::DragStartDistance, 0.001 );
    sp.setScrollMetric( QScrollerProperties::ScrollingCurve, QEasingCurve::Linear );
    QScroller* qs = QScroller::scroller( m_pEmploeeListWidget );
    qs->setScrollerProperties( sp );

    QScroller::grabGesture(m_pEmploeeListWidget, QScroller::TouchGesture);
    m_pEmploeeListWidget->grabGesture(Qt::TapAndHoldGesture);
    m_pEmploeeListWidget->grabGesture(Qt::TapGesture);
    m_pEmploeeListWidget->setIconSize(QSize(47,27));
    m_pEmploeeListWidget->setWordWrap(true);
    pVMainLayout->addWidget(m_pEmploeeListWidget);

    QPushButton * pApplyButton = new QPushButton("Передать задачу");
    pApplyButton->setIcon(QIcon(":/icons/done_icon.png"));
    pApplyButton->setIconSize(QSize(iButtonHeight*0.75 , iButtonHeight*0.75));
    pVMainLayout->addWidget(pApplyButton);
    connect(pApplyButton,SIGNAL(released()),this,SLOT(OnApplyTaskPressed()));

    UpdateEmplees();

    this->setLayout(pVMainLayout);
}

void QSelectTaskEmploeer::UpdateEmplees()
{
    m_pEmploeeListWidget->clear();

    QString strExec= QString("select Пользователи.id , Фамилия, Имя, Отчество from Пользователи, ИсполнителиЗаказчики , Задачи where Роль = '80066f83-c025-410b-b439-f3e9b2299461' \
                            and Пользователи.Удалено <> true\
                            and ((Задачи.Заказчик in (select ИсполнителиЗаказчики.Заказчик from ИсполнителиЗаказчики where ИсполнителиЗаказчики.ИсполнительПартнер=Пользователи.id))\
                            or Задачи.Заказчик ISNULL) \
                            and Задачи.id='%1' GROUP BY Пользователи.id , Фамилия, Имя, Отчество ").arg(m_strUuidTask);
    QList<QStringList> resTasks = execMainBDQuery(strExec);


    for(int iTaskCounter = 0 ; iTaskCounter < resTasks.size() ; iTaskCounter++)
    {
        QListWidgetItem * pItem = new QListWidgetItem();
        QString strTask = QString(" %1 %2 %3").arg(resTasks.at(iTaskCounter).at(1)).arg(resTasks.at(iTaskCounter).at(2)).arg(resTasks.at(iTaskCounter).at(3));
        pItem->setText(strTask);
        pItem->setData(Qt::UserRole , QUuid::fromString(resTasks.at(iTaskCounter).at(0)));//uuid пользователя-сотрудника
        m_pEmploeeListWidget->addItem(pItem);
    }
}


void QSelectTaskEmploeer::OnApplyTaskPressed()
{
    if(QListWidgetItem* item = m_pEmploeeListWidget->currentItem())
    {
        //Получим текущего исполнителя
        QString strExec = QString("select Исполнитель  from Задачи where id='%1'").arg(m_strUuidTask);
        QList<QStringList> resTasks = execMainBDQuery(strExec);
        QString strCurUser = "";
        for(int iUserCounter = 0 ; iUserCounter < resTasks.size() ; iUserCounter++)
            strCurUser = resTasks.at(iUserCounter).at(0);


        //Перепишем задачу на выбранного
        strExec= QString("update Задачи set Исполнитель = '%1' where id='%2'").arg(item->data(Qt::UserRole).toString()).arg(m_strUuidTask);
        execMainBDQueryUpdate(strExec);

        //Сделаем отметку в журнале переписи задач
        QUuid newTransitUuid = QUuid::createUuid();
        qint64 iTime = QDateTime::currentSecsSinceEpoch();
        strExec= QString("insert into ПередачиЗадач (id, Задача, ИсполнительОт , ИсполнительК , ДатаВремя) values ('%1','%2','%3','%4','%5')")
                      .arg(newTransitUuid.toString())
                      .arg(m_strUuidTask)
                      .arg(strCurUser)
                      .arg(item->data(Qt::UserRole).toString())
                      .arg(iTime);
        execMainBDQueryUpdate(strExec);

        accept();
    }
}
