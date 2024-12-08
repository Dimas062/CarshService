#ifndef QCLICABLELABEL_H
#define QCLICABLELABEL_H

#include <QLabel>

class QClicableLabel : public QLabel
{
    Q_OBJECT
public:
     QClicableLabel(QWidget* parent = Q_NULLPTR, Qt::WindowFlags f = Qt::WindowFlags());
    ~QClicableLabel();

signals:
    void clicked();

protected:
    void mousePressEvent(QMouseEvent* event);
};

#endif // QCLICABLELABEL_H
