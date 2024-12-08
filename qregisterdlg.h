#ifndef QREGISTERDLG_H
#define QREGISTERDLG_H

#include "service_widgets/qcsbasedialog.h"
#include <QObject>


class QRegisterDlg : public QCSBaseDialog
{
    Q_OBJECT
public:
    QRegisterDlg(QWidget *parent = nullptr, Qt::WindowFlags f = Qt::WindowFlags());


signals:
    // void OnBackPressedSignal();
    // void OnBackRealesedSignal();
    // void OnReturnPressedSignal();
public slots:
    // void OnBackPressedSlot();
    // void OnApply();
    // void OnReturnPressedSlot();
    void OnPartnerPlateRegisterPressed();
    void OnPartnerWashRegisterPressed();
    void OnPartnerStickRegisterPressed();
    void OnCustomerPlateRegisterPressed();
    void OnEmployeeRegisterPressed();
    void OnWashPlateRegisterPressed();
    void OnStickPlateRegisterPressed();
};

#endif // QREGISTERDLG_H
