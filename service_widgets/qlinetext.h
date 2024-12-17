#ifndef QLINETEXT_H
#define QLINETEXT_H

#include <QWidget>
#include <QString>
#include <QLabel>
#include <QLineEdit>

class QLineText : public QWidget
{
    Q_OBJECT
public:
    explicit QLineText(QString strLabel, QWidget *parent = nullptr);

    bool CheckColorLenght();
    void SetEnabled(bool);

    QString getText() const;
    void setText(QString);

protected:
    QLabel * m_pLabel;
    QLineEdit * m_pLineEdit;
signals:
};

#endif // QLINETEXT_H
