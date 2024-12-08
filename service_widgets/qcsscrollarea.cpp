#include "qcsscrollarea.h"
#include<QDebug>
#include <QKeyEvent>
#include <QEvent>
#include <QMouseEvent>

QCSScrollArea::QCSScrollArea()

{
    //installEventFilter(viewport());
}


bool QCSScrollArea::event(QEvent *event)
{
    //qDebug()<<"QCSScrollArea event="<<event<< " type="<<event->type();
    return QScrollArea::event(event);
}

bool QCSScrollArea::viewportEvent(QEvent *event)
{
    //qDebug()<<"viewportEvent event="<<event<< " type="<<event->type();
    //event->accept();
    return QScrollArea::viewportEvent(event);
}
void QCSScrollArea::mousePressEvent(QMouseEvent *e)
{
    //qDebug()<<"mousePressEvent event="<<e;
}
