#ifndef QWASHPARTNERPENDLG_H
#define QWASHPARTNERPENDLG_H

#include "service_widgets/qcsbasedialog.h"
#include <QObject>
#include <QUuid>

class QWashPartnerPenDlg : public QCSBaseDialog
{
    Q_OBJECT
public:
    QWashPartnerPenDlg(QUuid idPen, QWidget *parent = nullptr, Qt::WindowFlags f = Qt::WindowFlags());
};

#endif // QWASHPARTNERPENDLG_H
