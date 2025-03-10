#ifndef QEMPLOEEINPUTTASKSDLG_H
#define QEMPLOEEINPUTTASKSDLG_H

#include "service_widgets/qcsbasedialog.h"
#include <QObject>
#include "service_widgets/qcsbaselistwidget.h"
#include <QUuid>
#include <QPushButton>

class QEmploeeInputTasksDlg : public QCSBaseDialog
{
    Q_OBJECT
public:
    QEmploeeInputTasksDlg(QUuid userUuid,  QWidget *parent = nullptr, Qt::WindowFlags f = Qt::WindowFlags());
    QString m_strApplyedTaskUuid;
    QString m_strApplyedTaskTypeUuid;
    QString m_strApplyedNumber;
    QString m_strApplyedPenParkUuid;
    QString m_strApplyedZakazchikUuid;
protected:
    QCSBaseListWidget * m_pTasksListWidget;
    void UpdateTasks();
    QPushButton * m_pApplyTaskButton;
    QUuid m_userUuid;
    QPushButton * m_pToCalendarButton;
    QPushButton * m_pFindButton;
    QString m_strDateFilter;
    QString m_strFindFilter;

public slots:
    void OnApplyTaskPressed();
    void FioClicked();
    void OnToCalendatButtonTogled(bool);
    void OnFindButtonTogled(bool);
};

#endif // QEMPLOEEINPUTTASKSDLG_H
