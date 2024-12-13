#include "qcsbasedlgscrollwidget.h"
#include <QDebug>
#include <QEvent>
#include <QKeyEvent>


extern QRect screenGeometry;
QCSBaseDlgScrollWidget::QCSBaseDlgScrollWidget(QWidget *parent)
    : QWidget{parent}
{
    QRect geometry(QPoint(10, 10), QSize(screenGeometry.width() - 20, screenGeometry.height() -20 ));
    // geometry.moveCenter(screenGeometry.center());
    // setGeometry(geometry);

    setMinimumWidth ( geometry.width() ) ;
    setMaximumWidth ( geometry.width() ) ;
    setSizePolicy (QSizePolicy :: Fixed , QSizePolicy::Minimum) ;
}

bool QCSBaseDlgScrollWidget::event(QEvent *event)
{
    return QWidget::event(event);
}
