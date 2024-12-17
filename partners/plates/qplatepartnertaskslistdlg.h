#ifndef QPLATEPARTNERTASKSLISTDLG_H
#define QPLATEPARTNERTASKSLISTDLG_H

#include "service_widgets/qcsbasedialog.h"
#include <QObject>
#include "service_widgets/qcsbaselistwidget.h"
#include <QUuid>


class QPlatePartnerTasksListDlg : public QCSBaseDialog
{
    Q_OBJECT
public:
    QPlatePartnerTasksListDlg(QWidget *parent = nullptr, Qt::WindowFlags f = Qt::WindowFlags());

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

#endif // QPLATEPARTNERTASKSLISTDLG_H
