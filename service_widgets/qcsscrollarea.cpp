#include "qcsscrollarea.h"
#include <QKeyEvent>
#include <QEvent>
#include <QMouseEvent>

QCSScrollArea::QCSScrollArea()

{
    //installEventFilter(viewport());
}


bool QCSScrollArea::event(QEvent *event)
{
    return QScrollArea::event(event);
}

bool QCSScrollArea::viewportEvent(QEvent *event)
{
    //event->accept();
    return QScrollArea::viewportEvent(event);
}
void QCSScrollArea::mousePressEvent(QMouseEvent *e)
{
}
