#ifndef QEMPLCOSTSDLG_H
#define QEMPLCOSTSDLG_H

#include "service_widgets/qcsbasedialog.h"
#include <QObject>
#include "service_widgets/qcsbaselistwidget.h"
#include <QUuid>

class QEmplCostsDlg : public QCSBaseDialog
{
    Q_OBJECT
public:
    QEmplCostsDlg(QUuid userUuid, QWidget *parent = nullptr, Qt::WindowFlags f = Qt::WindowFlags());

    QUuid m_userUuid;

    QCSBaseListWidget * m_pCostsListWidget;

    void UpdateCosts();

public slots:
    void OnTapGesture();
};

#endif // QEMPLCOSTSDLG_H
