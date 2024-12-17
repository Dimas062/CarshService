#ifndef QWashPARTNERMAINDLG_H
#define QWashPARTNERMAINDLG_H

#include "service_widgets/qcsbasedialog.h"
#include <QObject>
#include <QPushButton>

class QWashPartnerMainDlg : public QCSBaseDialog
{
    Q_OBJECT
public:
    QWashPartnerMainDlg(QWidget *parent = nullptr, Qt::WindowFlags f = Qt::WindowFlags());

    QPushButton * m_pCurrentTasksButton;
    QPushButton * m_pNewWashTaskButton;

public slots:
    void OnNewWashTaskPressed();
    void OnCurrentTaskPressed();
};

#endif // QWashPARTNERMAINDLG_H
