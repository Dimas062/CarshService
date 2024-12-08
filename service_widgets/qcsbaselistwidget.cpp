#include "qcsbaselistwidget.h"
#include <QGuiApplication>
#include <QScrollerProperties>
#include <QScroller>
#include <QEasingCurve>
#include <QAbstractItemView>
#include "qcsbaselistitemdelegate.h"

QCSBaseListWidget::QCSBaseListWidget(QWidget *parent):QListWidget(parent)
{
    setVerticalScrollMode(QAbstractItemView::ScrollPerPixel);

    QScrollerProperties sp;
    sp.setScrollMetric( QScrollerProperties::DragStartDistance, 0.001 );
    sp.setScrollMetric( QScrollerProperties::ScrollingCurve, QEasingCurve::Linear );
    QScroller* qs = QScroller::scroller( this );
    qs->setScrollerProperties( sp );

    QScroller::grabGesture(this, QScroller::TouchGesture);
    this->grabGesture(Qt::TapAndHoldGesture);
    this->grabGesture(Qt::TapGesture);
    this->setWordWrap(true);
    this->setIconSize(QSize(45,45));

    setItemDelegate(new QCSBaseListItemDelegate(this));
}

bool QCSBaseListWidget::gestureEvent(QGestureEvent *event)
{
    if (QGesture * TapHoldGesture = event->gesture(Qt::TapAndHoldGesture))
    {
        if(TapHoldGesture->state() == Qt::GestureFinished)
        {
            emit OnTapHoldGesture();
        }
    }

    if (QGesture * TapHoldGesture = event->gesture(Qt::TapGesture))
    {
        if(TapHoldGesture->state() == Qt::GestureFinished)
        {
            emit OnTapGesture();
        }
    }

    return true;
}

bool QCSBaseListWidget::event(QEvent *event)
{
//#if QT_VERSION <= 0x060603
    static QMap<QPointer<QTapGesture>, bool> tapGestures;
    if (event->type() != QEvent::Gesture)
        return QListWidget::event(event);

    auto g_event = static_cast<QGestureEvent *>(event);


    if (auto g = qobject_cast<QTapGesture *>(g_event->gesture(Qt::TapGesture))) {
        // A TapAndHold was triggered during that tap... let's ignore it

        bool bSend = true;
        if (tapGestures.value(g))
        {
            g_event->ignore(g); // Or handle as you like
            bSend = false;
        }

        if (g->state() == Qt::GestureFinished || g->state() == Qt::GestureCanceled)
            tapGestures.remove(g);
        else if (!tapGestures.contains(g))
            tapGestures.insert(g, false);

        if(bSend) gestureEvent(static_cast<QGestureEvent*>(event));

        g_event->accept(g);

        return true;
    }

    if (auto g = qobject_cast<QTapAndHoldGesture *>(g_event->gesture(Qt::TapAndHoldGesture))) {
        // Probably not needed if the gesture handle doesn't conflict with another component
        if (g->state() == Qt::GestureFinished)
            g->setGestureCancelPolicy(QGesture::CancelAllInContext);

        // Mark all QTapGesture in progress to be ignored


        for (auto it = tapGestures.begin(); it != tapGestures.end(); ++it)
            it.value() = true;

        gestureEvent(static_cast<QGestureEvent*>(event));

        g_event->accept(g);

        return true;
    }
//#endif
    return QListWidget::event(event);
}

void QCSBaseListWidget::showEvent( QShowEvent* event )
{
    QWidget::showEvent(event);
    qApp->inputMethod()->hide();
}
