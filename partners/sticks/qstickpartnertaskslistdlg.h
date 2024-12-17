#ifndef QStickPARTNERTASKSLISTDLG_H
#define QStickPARTNERTASKSLISTDLG_H

#include "service_widgets/qcsbasedialog.h"
#include <QObject>
#include "service_widgets/qcsbaselistwidget.h"
#include <QUuid>


class QStickPartnerTasksListDlg : public QCSBaseDialog
{
    Q_OBJECT
public:
    QStickPartnerTasksListDlg(QWidget *parent = nullptr, Qt::WindowFlags f = Qt::WindowFlags());

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

#endif // QStickPARTNERTASKSLISTDLG_H
