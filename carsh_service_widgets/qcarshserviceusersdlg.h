#ifndef QCARSHSERVICEUSERSDLG_H
#define QCARSHSERVICEUSERSDLG_H

#include "service_widgets/qcsbasedialog.h"
#include <QObject>
#include "service_widgets/qcsbaselistwidget.h"

class QCarshServiceUsersDlg : public QCSBaseDialog
{
    Q_OBJECT
public:
    QCarshServiceUsersDlg(QWidget *parent = nullptr, Qt::WindowFlags f = Qt::WindowFlags());
    QCSBaseListWidget * m_pUsersList;

protected:
    void UpdateUsersList();
public slots:
    void OnTapHoldGesture();
    void OnTapGesture();
};

#endif // QCARSHSERVICEUSERSDLG_H
