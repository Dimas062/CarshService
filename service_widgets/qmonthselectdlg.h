#ifndef QMONTHSELECTDLG_H
#define QMONTHSELECTDLG_H

#include <QDialog>
#include <QObject>
#include <QDate>
#include <common.h>
#include "qlabel.h"


class QMonthSelectDlg : public QDialog
{
    Q_OBJECT
public:
public:
    QMonthSelectDlg(QDate startDate , QWidget *parent = nullptr, Qt::WindowFlags f = Qt::WindowFlags());

    QDate m_SelectedDate;
    QLabel * m_pYearLabel;

    bool event(QEvent *event);

    bool m_bChildBackRealeseProcessed;
    bool m_bBackRelesaeProcessed;

public slots:
    void OnLeftYearButton();
    void OnRightYearButton();
    void OnMonthClicked();
};

#endif // QMONTHSELECTDLG_H
