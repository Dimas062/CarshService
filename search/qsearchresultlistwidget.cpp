#include "qsearchresultlistwidget.h"
#include <QGuiApplication>


QSearchResultListWidget::QSearchResultListWidget(QWidget *parent): QListWidget(parent)
{
    setVerticalScrollMode(QAbstractItemView::ScrollPerPixel);
}


bool QSearchResultListWidget::gestureEvent(QGestureEvent *event)
{
    if (QGesture * TapHoldGesture = event->gesture(Qt::TapAndHoldGesture))
        if(TapHoldGesture->state() == Qt::GestureFinished)
        {
            emit OnTapHoldGesture();
        }

    if (QGesture * TapHoldGesture = event->gesture(Qt::TapGesture))
        if(TapHoldGesture->state() == Qt::GestureFinished)
        {
            emit OnTapGesture();
        }

    return true;
}

bool QSearchResultListWidget::event(QEvent *event)
{
    if (event->type() == QEvent::Gesture)
    {
        return gestureEvent(static_cast<QGestureEvent*>(event));
    }
    return QListWidget::event(event);
}

void QSearchResultListWidget::showEvent( QShowEvent* event )
{
    QWidget::showEvent(event);
    qApp->inputMethod()->hide();
}
