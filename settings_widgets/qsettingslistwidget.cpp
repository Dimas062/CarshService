#include "qsettingslistwidget.h"
#include <QGuiApplication>
#include <QScrollBar>
#include <QVBoxLayout>
#include <QGroupBox>
#include <QLabel>
#include <QSqlQuery>
#include <QSqlError>

extern QSqlDatabase ClientDb;

QSettingsListWidget::QSettingsListWidget(QWidget *parent): QWidget(parent)
{
    // setVerticalScrollMode(QAbstractItemView::ScrollPerPixel);
    // setVerticalScrollBarPolicy( Qt::ScrollBarAlwaysOff );

    // setHorizontalScrollMode(QAbstractItemView::ScrollPerPixel);
    // setHorizontalScrollBarPolicy( Qt::ScrollBarAlwaysOff );

    // verticalScrollBar()->setSingleStep(1);

    const QRect screenGeometry = QGuiApplication::primaryScreen()->availableGeometry();

    QString strQueryExec;
    QSqlQuery query(ClientDb);



    QVBoxLayout * pMainLayout = new QVBoxLayout(this);
    pMainLayout->setAlignment(Qt::AlignHCenter);

    QGroupBox * pConnectGroupBox = new QGroupBox(this);
    pConnectGroupBox->setMaximumWidth(screenGeometry.width()-40);

    //pConnectGroupBox->setTitle("Подключение");

    QVBoxLayout * pVConnectLayout = new QVBoxLayout();



    pConnectGroupBox->setLayout(pVConnectLayout);

    // QHBoxLayout * pHAdressLoyout = new QHBoxLayout();

    // QLabel * pAdressLabel = new QLabel("Адрес сервера:");

    // m_pAdressLineEdit = new QLineEdit();

    // pHAdressLoyout->addWidget(pAdressLabel);
    // pHAdressLoyout->addWidget(m_pAdressLineEdit);
    // pVConnectLayout->addLayout(pHAdressLoyout);

    // strQueryExec = QString("select Value from Settings where Name='Host'");
    // if(query.exec(strQueryExec))
    // {
    //     while(query.next())
    //     {
    //         m_pAdressLineEdit->setText(query.value(0).toString());
    //     }
    // }
    // else
    //     qDebug()<<"BD Error " << query.lastError().text();

    QHBoxLayout * pHLoginLoyout = new QHBoxLayout();

    QLabel * pLoginLabel = new QLabel("Логин:");

    m_pLoginLineEdit = new QLineEdit();
    m_pLoginLineEdit->setContextMenuPolicy(Qt::NoContextMenu);

    pHLoginLoyout->addWidget(pLoginLabel);
    pHLoginLoyout->addWidget(m_pLoginLineEdit);
    pVConnectLayout->addLayout(pHLoginLoyout);

    strQueryExec = QString("select Value from Settings where Name='Login'");
    if(query.exec(strQueryExec))
    {
        while(query.next())
        {
            m_pLoginLineEdit->setText(query.value(0).toString());
        }
    }
    else
        qDebug()<<"BD Error " << query.lastError().text();


    QHBoxLayout * pHPasswordLoyout = new QHBoxLayout();

    QLabel * pPasswordLabel = new QLabel("Пароль:");

    m_pPasswordLineEdit = new QLineEdit();
    m_pPasswordLineEdit->setContextMenuPolicy(Qt::NoContextMenu);

    pHPasswordLoyout->addWidget(pPasswordLabel);
    pHPasswordLoyout->addWidget(m_pPasswordLineEdit);
    pVConnectLayout->addLayout(pHPasswordLoyout);

    strQueryExec = QString("select Value from Settings where Name='Password'");
    if(query.exec(strQueryExec))
    {
        while(query.next())
        {
            m_pPasswordLineEdit->setText(query.value(0).toString());
        }
    }
    else
        qDebug()<<"BD Error " << query.lastError().text();


    pMainLayout->addWidget(pConnectGroupBox);



    this->setLayout(pMainLayout);
}


bool QSettingsListWidget::gestureEvent(QGestureEvent *event)
{
    // if (QGesture * TapHoldGesture = event->gesture(Qt::TapAndHoldGesture))
    //     if(TapHoldGesture->state() == Qt::GestureFinished)
    //     {
    //         emit OnTapHoldGesture();
    //     }

    // if (QGesture * TapHoldGesture = event->gesture(Qt::TapGesture))
    //     if(TapHoldGesture->state() == Qt::GestureFinished)
    //     {
    //         emit OnTapGesture();
    //     }

    return true;
}

void QSettingsListWidget::addWidget(QWidget * )
{
    // QListWidgetItem* item = new QListWidgetItem(this);
    // addItem(item);
    // item->setFlags(item->flags() & ~Qt::ItemIsSelectable);

    // item->setSizeHint(QSize(w->width(),w->height()));
    // setItemWidget(item , w);
}

bool QSettingsListWidget::event(QEvent *event)
{
    //  return QListWidget::event(event);
    // static QMap<QPointer<QTapGesture>, bool> tapGestures;
    // if (event->type() != QEvent::Gesture)
    //     return QListWidget::event(event);

    // auto g_event = static_cast<QGestureEvent *>(event);


    // if (auto g = qobject_cast<QTapGesture *>(g_event->gesture(Qt::TapGesture))) {
    //     // A TapAndHold was triggered during that tap... let's ignore it
    //     bool bSend = true;
    //     if (tapGestures.value(g))
    //     {
    //         g_event->ignore(g); // Or handle as you like
    //         bSend = false;
    //     }

    //     if (g->state() == Qt::GestureFinished || g->state() == Qt::GestureCanceled)
    //         tapGestures.remove(g);
    //     else if (!tapGestures.contains(g))
    //         tapGestures.insert(g, false);

    //     if(bSend) gestureEvent(static_cast<QGestureEvent*>(event));

    //     g_event->accept(g);

    //     return true;
    // }

    // if (auto g = qobject_cast<QTapAndHoldGesture *>(g_event->gesture(Qt::TapAndHoldGesture))) {
    //     // Probably not needed if the gesture handle doesn't conflict with another component
    //     if (g->state() == Qt::GestureFinished)
    //         g->setGestureCancelPolicy(QGesture::CancelAllInContext);

    //     // Mark all QTapGesture in progress to be ignored


    //     for (auto it = tapGestures.begin(); it != tapGestures.end(); ++it)
    //         it.value() = true;

    //     gestureEvent(static_cast<QGestureEvent*>(event));

    //     g_event->accept(g);

    //     return true;
    // }

   // return QListWidget::event(event);

    return QWidget::event(event);

}

void QSettingsListWidget::showEvent( QShowEvent* event )
{
    QWidget::showEvent(event);
    qApp->inputMethod()->hide();
}
