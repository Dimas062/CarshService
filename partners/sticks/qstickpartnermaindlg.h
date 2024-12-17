#ifndef QStickPARTNERMAINDLG_H
#define QStickPARTNERMAINDLG_H

#include "service_widgets/qcsbasedialog.h"
#include <QObject>
#include <QPushButton>

class QStickPartnerMainDlg : public QCSBaseDialog
{
    Q_OBJECT
public:
    QStickPartnerMainDlg(QWidget *parent = nullptr, Qt::WindowFlags f = Qt::WindowFlags());

    QPushButton * m_pCurrentTasksButton;
    QPushButton * m_pNewStickTaskButton;

public slots:
    void OnNewStickTaskPressed();
    void OnCurrentTaskPressed();
};

#endif // QStickPARTNERMAINDLG_H
