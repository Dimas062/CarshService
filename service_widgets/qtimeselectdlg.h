#ifndef QTIMESELECTDLG_H
#define QTIMESELECTDLG_H

#include <QDialog>
#include <QLabel>
#include <QTime>

class QTimeSelectDlg : public QDialog
{
    Q_OBJECT
public:
    QTimeSelectDlg(QTime startTime , QWidget *parent = nullptr, Qt::WindowFlags f = Qt::WindowFlags());


    bool m_bChildBackRealeseProcessed;
    bool m_bBackRelesaeProcessed;

    QTime m_SelectedTime;

    QLabel * m_pHourLabel;
    QLabel * m_pMinuteLabel;

    void UpdateTimeWidgets();

    bool event(QEvent *event);

public slots:
    void OnApply();
    void OnHourLeftPressed();
    void OnHourRightPressed();
    void OnMinuteLeftPressed();
    void OnMinuteRightPressed();
};

#endif // QTIMESELECTDLG_H
