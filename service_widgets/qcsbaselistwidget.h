#ifndef QCSBASELISTWIDGET_H
#define QCSBASELISTWIDGET_H

#include <QListWidget>
#include <QObject>
#include <QGestureEvent>

class QCSBaseListWidget : public QListWidget
{
    Q_OBJECT
public:
    QCSBaseListWidget(QWidget *parent = nullptr);

    bool gestureEvent(QGestureEvent *event);
    bool event(QEvent *event);
    void showEvent( QShowEvent* event );

signals:
    void OnTapHoldGesture();
    void OnTapGesture();
};

#endif // QCSBASELISTWIDGET_H
