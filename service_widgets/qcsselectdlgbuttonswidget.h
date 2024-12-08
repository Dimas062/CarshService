#ifndef QCSSELECTDLGBUTTONSWIDGET_H
#define QCSSELECTDLGBUTTONSWIDGET_H

#include <QWidget>
#include <QString>
#include <QPushButton>

class QCSSelectDlgButtonsWidget : public QWidget
{
    Q_OBJECT
public:
    explicit QCSSelectDlgButtonsWidget(QString strTableName , QString strColName , bool bChekable , QWidget *parent = nullptr);
    QVector<QPushButton *> m_vpButtons;
    QString m_strId;
    QString m_strText;
    bool m_bChekable;
    void SelectId(QString strId);
public slots:
    void OnButtonPress();

signals:
    void ButtonPushed();
};

#endif // QCSSELECTDLGBUTTONSWIDGET_H
