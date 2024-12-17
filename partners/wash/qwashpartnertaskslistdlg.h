#ifndef QWashPARTNERTASKSLISTDLG_H
#define QWashPARTNERTASKSLISTDLG_H

#include "service_widgets/qcsbasedialog.h"
#include <QObject>
#include "service_widgets/qcsbaselistwidget.h"
#include <QUuid>


class QWashPartnerTasksListDlg : public QCSBaseDialog
{
    Q_OBJECT
public:
    QWashPartnerTasksListDlg(QWidget *parent = nullptr, Qt::WindowFlags f = Qt::WindowFlags());

protected:
    QCSBaseListWidget * m_pTasksListWidget;
    QPushButton * m_pToCalendarButton;
    void UpdateTasks();

    QString strDateFilter;

public slots:
    void OnTapHoldGesture();
    void OnTapGesture();
    void OnToCalendatButtonTogled(bool);
};

#endif // QWashPARTNERTASKSLISTDLG_H
