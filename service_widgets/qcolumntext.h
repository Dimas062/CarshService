#ifndef QCOLUMNTEXT_H
#define QCOLUMNTEXT_H

#include <QWidget>
#include <QString>
#include <QLabel>
#include <QLineEdit>

class QColumnText : public QWidget
{
    Q_OBJECT
public:
    explicit QColumnText(QString strLabel, QWidget *parent = nullptr);

    bool CheckColorLenght();

    QString getText() const;

protected:
    QLabel * m_pLabel;
    QLineEdit * m_pLineEdit;
signals:

signals:
};

#endif // QCOLUMNTEXT_H
