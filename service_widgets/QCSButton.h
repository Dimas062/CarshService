#ifndef QCSButton_H
#define QCSButton_H

#include <QObject>
#include <QPushButton>
#include <QString>
#include <QWidget>

class QCSButton : public QPushButton
{
    Q_OBJECT
public:

    QCSButton(QWidget *parent = nullptr);
    QCSButton(const QString &text, QWidget *parent = nullptr);
    QCSButton(const QIcon &icon, const QString &text, QWidget *parent = nullptr);

    void mouseDoubleClickEvent();

signals:
    void doubleClicked();

};

#endif // QCSButton_H
