#include "qnotecalendarwidget.h"
#include <QPainter>
#include <QMap>
#include <QIcon>
#include <QTextCharFormat>

QNoteCalendarWidget::QNoteCalendarWidget(QWidget *parent):QCalendarWidget(parent)
{

}


void QNoteCalendarWidget::paintCell(QPainter *painter, const QRect &rect, const QDate date) const
{
   QCalendarWidget::paintCell(painter, rect, date);

    if(m_Props[date].bIsArchive)
   {
       painter->save();

       QIcon(":/icons/video 3.png").paint(painter,rect.adjusted(0,0, - (rect.width()*0.7) , -(rect.height()*0.7)));

       painter->restore();
    }
}
