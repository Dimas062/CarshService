#ifndef QWashPARTNERTASK_H
#define QWashPARTNERTASK_H

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
#include "qcswashtypeselectdlg.h"

class QWashPartnerTask : public QCSBaseDialog
{
    Q_OBJECT
public:
    QWashPartnerTask(QWidget *parent = nullptr, Qt::WindowFlags f = Qt::WindowFlags());

    void SaveDataToBD();
    void LoadDataFromBD(QUuid);

protected:
    QLabel * m_pTopLabel;
    QLineText * m_pCommentLineText;

    QVector<WashTypeDatas> m_vWashDatas;

    QString strIdPoint;
    QCSWashTypeSelectDlg m_WashTypeSelectDlg;

    QPushButton * m_pPointButton;
    QPushButton * m_pSubtaskButton;
    QPushButton * m_pToCalendarButton;
    QLabel * m_pCalendarLabel;

    QLoadDocsDlg * m_pLoadVedomostDlg;
    QPushButton * m_pLoadVedomostButton;

    QDate m_selDate;


    bool isReady();
    QUuid m_uuidSourseRecord;

public slots:
    void OnApplyPressedSlot();
    void OnPointPressedSlot();
    void OnSubtaskPressedSlot();
    void OnToCalendatButtonPressed();
    void OnLoadVedomostButtonPressed();
};

#endif // QWashPARTNERTASK_H
