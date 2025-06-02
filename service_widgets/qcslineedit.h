#ifndef QCSLINEEDIT_H
#define QCSLINEEDIT_H

#include <QLineEdit>
#include <QTimer>

class QCSLineEdit : public QLineEdit
{
    Q_OBJECT
public:
    explicit QCSLineEdit(QWidget *parent = nullptr);

protected:
    void mousePressEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;

private:
    QTimer *longPressTimer;
    const int longPressDuration = 500; // Время в миллисекундах для контекстного меню
};

#endif // QCSLINEEDIT_H
