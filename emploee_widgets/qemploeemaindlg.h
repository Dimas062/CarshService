#ifndef QEMPLOEEMAINDLG_H
#define QEMPLOEEMAINDLG_H

#include "service_widgets/qcsbasedialog.h"
#include <QPushButton>


class QEmploeeMainDlg : public QCSBaseDialog
{
    Q_OBJECT
public:
    QEmploeeMainDlg(QWidget *parent = nullptr, Qt::WindowFlags f = Qt::WindowFlags());

protected:
    // QPushButton * m_pStartWorkDayButton;
    // QPushButton * m_pFinishWorkDayButton;


    QPushButton * m_pCurrentTasksButton;
    QPushButton * m_pCostButton;
    QPushButton * m_pNumberPlateButton;
    QPushButton * m_pParkingButton;
    QPushButton * m_pPenaltyParkingButton;
    QPushButton * m_pDocsButton;
    QPushButton * m_pWorkdayButton;
    QPushButton * m_pReturnToZoneButton;
    QPushButton * m_pCostsButton;
    QPushButton * m_pSmenaButton;

public slots:
    void OnCurrentTaskPressed();
    void OnNumberPlateTaskPressed();
    void OnParkingTaskPressed();
    void OnPenaltyParkingTaskPressed();
    void OnDocsTaskPressed();
 //   void OnWorkdayTaskPressed();
    void OnReturnToZoneTaskPressed();
    void OnCostPressed();
    void OnCostsPressed();
    void OnSmenaTaskPressed();

};

#endif // QEMPLOEEMAINDLG_H
