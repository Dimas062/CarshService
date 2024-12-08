#ifndef QNOTECALENDARWIDGET_H
#define QNOTECALENDARWIDGET_H

#include <QCalendarWidget>
#include <QObject>
#include <QMap>
#include <QDate>

struct sDateProps
{
    bool bIsArchive = false;
};

class QNoteCalendarWidget : public QCalendarWidget
{
    Q_OBJECT
public:
    QNoteCalendarWidget( QWidget *parent );

    QMap<QDate, sDateProps> m_Props;


protected:
    void paintCell(QPainter *painter, const QRect &rect, const QDate date) const;



};

#endif // QNOTECALENDARWIDGET_H
