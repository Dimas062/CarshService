#ifndef QCALENDARDATASELECTDLG_H
#define QCALENDARDATASELECTDLG_H

#include <QDialog>
#include "qnotecalendarwidget.h"
#include <QDate>
#include <common.h>
#include "qlabel.h"


class QCalendarDataSelectDlg : public QDialog
{
    Q_OBJECT
public:
    QCalendarDataSelectDlg(QDate startDate , QWidget *parent = nullptr, Qt::WindowFlags f = Qt::WindowFlags());

    QDate m_SelectedDate;
    QLabel * m_pViewedDataLabel;

    bool event(QEvent *event);

    bool m_bChildBackRealeseProcessed;
    bool m_bBackRelesaeProcessed;
    void SetDatesPros(QMap<QDate, sDateProps>);


protected:
    QNoteCalendarWidget * m_pCalendarWidget;
    void UpdateDateLabel();
    void mousePressEvent(QMouseEvent *event) override;

public slots:
    void OnClickedDay(QDate);
    void OnCalendarBackPressed();
    void OnCalendarForwardPressed();
};

#endif // QCALENDARDATASELECTDLG_H
