#ifndef QCSSELECTDLGBUTTONSWIDGET_H
#define QCSSELECTDLGBUTTONSWIDGET_H

#include <QWidget>
#include <QString>
#include <QPushButton>
#include <QVector>

class QCSSelectDlgButtonsWidget : public QWidget
{
    Q_OBJECT
public:
    explicit QCSSelectDlgButtonsWidget(QString strTableName , QString strColName , bool bChekable , QString strCondition = " ", bool bMultiselect = false , QWidget *parent = nullptr);
    bool m_bMultiSelect;

    QVector<QPushButton *> m_vpButtons;
    QString m_strId;
    QString m_strText;

    QVector<QString> m_vstrId;
    QVector<QString> m_vstrText;

    bool m_bChekable;
    void SelectId(QString strId);
    void SelectIds(QVector<QString> vstrId);
public slots:
    void OnButtonPress(bool);

signals:
    void ButtonPushed();
};

#endif // QCSSELECTDLGBUTTONSWIDGET_H
