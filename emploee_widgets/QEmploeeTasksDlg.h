#ifndef QEmploeeTasksDlg_H
#define QEmploeeTasksDlg_H

#include "service_widgets/qcsbasedialog.h"
#include <QObject>
#include "service_widgets/qcsbaselistwidget.h"
#include <QUuid>

class QEmploeeTasksDlg : public QCSBaseDialog
{
    Q_OBJECT
public:
    QEmploeeTasksDlg(QUuid userUuid, QUuid taskTypeUuid = QUuid(), QWidget *parent = nullptr, Qt::WindowFlags f = Qt::WindowFlags());

    void checkNotReadyButton();
protected:
    QCSBaseListWidget * m_pTasksListWidget;
    QPushButton * m_pReadyButton;
    QPushButton * m_pNotReadyButton;
    QPushButton * m_pToCalendarButton;
    QPushButton * m_pTaskTypesButton;
    void UpdateTasks();
    QUuid m_userUuid;
    QString strFilter;
    QString strDateFilter;
    QString strTaskTypesFilter;

public slots:
    void OnTapHoldGesture();
    void OnTapGesture();
    void OnReadyButtonTogled(bool);
    void OnNotReadyButtonTogled(bool);
    void OnToCalendatButtonTogled(bool);
    void FioClicked();
};

#endif // QEmploeeTasksDlg_H
