#ifndef QCSBASEDLGSCROLLWIDGET_H
#define QCSBASEDLGSCROLLWIDGET_H

#include <QWidget>

class QCSBaseDlgScrollWidget : public QWidget
{
    Q_OBJECT
public:
    explicit QCSBaseDlgScrollWidget(QWidget *parent = nullptr);
    bool event(QEvent *event);
signals:
};

#endif // QCSBASEDLGSCROLLWIDGET_H
