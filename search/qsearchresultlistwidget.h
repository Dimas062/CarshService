#ifndef QSEARCHRESULTLISTWIDGET_H
#define QSEARCHRESULTLISTWIDGET_H

#include <QListWidget>
#include <QWidget>
#include <QGestureEvent>


class QSearchResultListWidget : public QListWidget
{
    Q_OBJECT
public:
    QSearchResultListWidget(QWidget *parent = nullptr);

    bool gestureEvent(QGestureEvent *event);
    bool event(QEvent *event);
    void showEvent( QShowEvent* event );

signals:
    void OnTapHoldGesture();
    void OnTapGesture();

};

#endif // QSEARCHRESULTLISTWIDGET_H
