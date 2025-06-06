#ifndef QREGISTERPARTNERSTICKDLG_H
#define QREGISTERPARTNERSTICKDLG_H

#include "service_widgets/qcsbasedialog.h"
#include <QObject>
#include <QLineEdit>
#include <QPushButton>
#include "service_widgets/quldlg.h"
#include "service_widgets/qpointlistdlg.h"
#include "service_widgets/qlinetext.h"

class QRegisterPartnerStickDlg : public QCSBaseDialog
{
    Q_OBJECT
public:
    QRegisterPartnerStickDlg(QWidget *parent = nullptr, Qt::WindowFlags f = Qt::WindowFlags());

    QPushButton * m_pULButton;
    QPushButton * m_pPointsButton;
    QPushButton * m_pPostavshikButton;

    QLineText * m_pPasswordLineText;
    QLineText * m_pLoginLineText;

    QULDlg m_ULdlg;
    QPointListDlg m_PointListdlg;

    bool isReady();

    QString m_strPostavId;
    QString m_strPostavText;

public slots:
    void OnUlPressedSlot();
    void OnPointsPressedSlot();
    void OnPostavPressedSlot();
    void OnApplyPressed();
};

#endif // QREGISTERPARTNERSTICKDLG_H
