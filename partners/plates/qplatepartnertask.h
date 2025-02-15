#ifndef QPLATEPARTNERTASK_H
#define QPLATEPARTNERTASK_H

#include "service_widgets/qcsbasedialog.h"
#include "service_widgets/qlinetext.h"
#include "service_widgets/qselprovidercarshwidget.h"

#include <QObject>
#include <QPushButton>
#include <QLabel>
#include <QUuid>
#include <QString>
#include <QDate>

class QPlatePartnerTask : public QCSBaseDialog
{
    Q_OBJECT
public:
    QPlatePartnerTask(QWidget *parent = nullptr, Qt::WindowFlags f = Qt::WindowFlags());

    void SaveDataToBD();
    void LoadDataFromBD(QUuid);

protected:
    QLabel * m_pTopLabel;
    QLineText * m_pPlateCountLineText;
    QLineText * m_pCommentLineText;
    QString strIdPoint;

    QPushButton * m_pPointButton;
    QPushButton * m_pToCalendarButton;
    QLabel * m_pCalendarLabel;
    QSelProviderCarshWidget * m_pSelProviderCarshWidget;

    QDate m_selDate;

    bool isReady();
    QUuid m_uuidSourseRecord;

public slots:
    void OnApplyPressedSlot();
    void OnPointPressedSlot();
    void OnToCalendatButtonPressed();
    void OnCarshChanged();
};

#endif // QPLATEPARTNERTASK_H
