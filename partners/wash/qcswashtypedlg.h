#ifndef QCSWASHTYPEDLG_H
#define QCSWASHTYPEDLG_H

#include "service_widgets/qcsbasedialog.h"
#include <QObject>
#include <QLabel>
#include <QPushButton>
#include <QString>
#include "service_widgets/qlinetext.h"

class QCSWashTypeDlg : public QCSBaseDialog
{
    Q_OBJECT
public:
    QCSWashTypeDlg(QString strType , QWidget *parent = nullptr, Qt::WindowFlags f = Qt::WindowFlags());
    QLabel * m_pTopLabel;
    QLineText * m_pDayNumberLineText;
    QPushButton * m_pDayButton;
    QLineText * m_pNigthNumberLineText;
    QPushButton * m_pNigthButton;

    QString m_strType;

    QString getText();

public slots:
    void OnApplyPressedSlot();
    void OnDayButtonToggled(bool);
    void OnNigthButtonToggled(bool);
};

#endif // QCSWASHTYPEDLG_H
