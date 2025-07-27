#ifndef QEMPLOEEDUTYDLG_H
#define QEMPLOEEDUTYDLG_H

#include "service_widgets/qcsbasedialog.h"
#include <QObject>
#include <QLabel>
#include <QMap>
#include <QString>

class QEmploeeDutyDlg : public QCSBaseDialog
{
    Q_OBJECT
public:
    QEmploeeDutyDlg();

    QLabel * m_pSector1Label;
    QLabel * m_pSector2Label;
    QLabel * m_pSector3Label;
    QLabel * m_pSector4Label;

protected:
    // Храним соответствие UUID секторов и меток
    QMap<QString, QLabel*> m_sectorLabels;

    void updateDutyLabels();

public slots:
    void OnSector1Pressed();
    void OnSector2Pressed();
    void OnSector3Pressed();
    void OnSector4Pressed();
};

#endif // QEMPLOEEDUTYDLG_H
