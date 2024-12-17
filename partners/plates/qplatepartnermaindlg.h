#ifndef QPLATEPARTNERMAINDLG_H
#define QPLATEPARTNERMAINDLG_H

#include "service_widgets/qcsbasedialog.h"
#include <QObject>
#include <QPushButton>

class QPlatePartnerMainDlg : public QCSBaseDialog
{
    Q_OBJECT
public:
    QPlatePartnerMainDlg(QWidget *parent = nullptr, Qt::WindowFlags f = Qt::WindowFlags());

    QPushButton * m_pCurrentTasksButton;
    QPushButton * m_pNewPlateTaskButton;

public slots:
    void OnNewPlateTaskPressed();
    void OnCurrentTaskPressed();
};

#endif // QPLATEPARTNERMAINDLG_H
