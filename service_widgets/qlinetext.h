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
    void SetToolTip(QString);

    QString getText() const;
    void setText(QString);

    QString getLabelText();

protected:
    QLabel * m_pLabel;
    QLineEdit * m_pLineEdit;
public slots:
    void OnTextLineEditChanged(const QString &text);
signals:
    void textChanged(const QString &text);
};

#endif // QLINETEXT_H
