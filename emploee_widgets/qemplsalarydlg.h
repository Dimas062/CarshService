#ifndef QEMPLSALARYDLG_H
#define QEMPLSALARYDLG_H

#include "service_widgets/qcsbasedialog.h"
#include <QObject>
#include "service_widgets/qcsbaselistwidget.h"
#include <QUuid>
#include <QLabel>
#include <QDate>

class QEmplSalaryDlg : public QCSBaseDialog
{
    Q_OBJECT
public:
    QEmplSalaryDlg( QWidget *parent = nullptr, Qt::WindowFlags f = Qt::WindowFlags());
    QCSBaseListWidget * m_pSalarysListWidget;
    QPushButton * m_pToCalendarButton;
    QPushButton * m_pToTaskTypeFilterButton;

    QDate m_currentDate;
    QString m_strCurrentTaskType;

    void UpdateSalarys();

    QLabel * m_pLabelSalary;
    QLabel * m_pPenSalary;
    QLabel * m_pPremSalary;
    QLabel * m_pSummSalary;

public slots:
    void OnToCalendarButtonClicked();
    void OnToTaskTypeFilterButtonClicked();
};

#endif // QEMPLSALARYDLG_H
