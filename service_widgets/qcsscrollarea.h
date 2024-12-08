#ifndef QCSSCROLLAREA_H
#define QCSSCROLLAREA_H

#include <QObject>
#include <QScrollArea>

class QCSScrollArea : public QScrollArea
{
    Q_OBJECT
public:
    QCSScrollArea();
    bool event(QEvent *event);
    bool viewportEvent(QEvent *event);
    void mousePressEvent(QMouseEvent *e);
};

#endif // QCSSCROLLAREA_H
