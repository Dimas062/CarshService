#ifndef QCSListWidget_H
#define QCSListWidget_H

#include <QListWidget>
#include <QGestureEvent>

class QCSListWidget : public QListWidget
{
    Q_OBJECT
public:
    explicit QCSListWidget(QWidget *parent = nullptr);

    bool gestureEvent(QGestureEvent *event);
    bool event(QEvent *event);
    void showEvent( QShowEvent* event );

signals:
    void OnTapHoldGesture();
    void OnTapGesture();
};

#endif // QCSListWidget_H
