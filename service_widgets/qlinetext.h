#ifndef QLINETEXT_H
#define QLINETEXT_H

#include <QWidget>
#include <QString>
#include <QLabel>
#include "service_widgets/qcslineedit.h"

class QLineText : public QWidget
{
    Q_OBJECT
public:
    explicit QLineText(QString strLabel, QWidget *parent = nullptr , bool bMoney= false);

    bool CheckColorLenght();
    bool m_bIsMoney;
    void SetEnabled(bool);
    void SetToolTip(QString);

    QString getText() const;
    void setText(QString);

    QString getLabelText();

protected:
    QLabel * m_pLabel;
    QCSLineEdit * m_pLineEdit;


public slots:
    void OnTextLineEditChanged(const QString &text);
signals:
    void textChanged(const QString &text);
};

#endif // QLINETEXT_H
