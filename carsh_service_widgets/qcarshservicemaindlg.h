#ifndef QCARSHSERVICEMAINDLG_H
#define QCARSHSERVICEMAINDLG_H

#include "service_widgets/qcsbasedialog.h"

class QCarshServiceMainDlg : public QCSBaseDialog
{
     Q_OBJECT
public:
    QCarshServiceMainDlg(QWidget *parent = nullptr, Qt::WindowFlags f = Qt::WindowFlags());
public slots:
    void OnUsersPressed();
    void OnPartnersPressed();
};

#endif // QCARSHSERVICEMAINDLG_H
