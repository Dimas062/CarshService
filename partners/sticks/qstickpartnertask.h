#ifndef QStickPARTNERTASK_H
#define QStickPARTNERTASK_H

#include "service_widgets/qcsbasedialog.h"
#include "service_widgets/qlinetext.h"
#include "service_widgets/qloaddocsdlg.h"
#include <QObject>
#include <QPushButton>
#include <QLabel>
#include <QUuid>
#include <QString>
#include <QDate>
#include <QVector>
#include "service_widgets/qselprovidercarshwidget.h"

class QStickPartnerTask : public QCSBaseDialog
{
    Q_OBJECT
public:
    QStickPartnerTask(QWidget *parent = nullptr, Qt::WindowFlags f = Qt::WindowFlags());

    void SaveDataToBD();
    void LoadDataFromBD(QUuid);

protected:
    QLabel * m_pTopLabel;
    QLineText * m_pCommentLineText;
    QLineText * m_pNumberLineText;
    QVector<QString> m_vstrIdSubtasks;
    QString strIdPoint;

    QPushButton * m_pPointButton;
    QPushButton * m_pSubtaskButton;
    QPushButton * m_pToCalendarButton;
    QLabel * m_pCalendarLabel;

    QLoadDocsDlg * m_pLoadAutoFotoDlg;
    QPushButton * m_pLoadAutoFotoButton;

    QDate m_selDate;
    QSelProviderCarshWidget * m_pSelProviderCarshWidget;

    bool isReady();
    QUuid m_uuidSourseRecord;

public slots:
    void OnApplyPressedSlot();
    void OnPointPressedSlot();
    void OnSubtaskPressedSlot();
    void OnToCalendatButtonPressed();
    void OnLoadAutoFotoButtonPressed();
    void OnCarshChanged();
};

#endif // QStickPARTNERTASK_H
