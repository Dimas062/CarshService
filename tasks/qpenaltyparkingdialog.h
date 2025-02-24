#ifndef QPENALTYPARKINGDIALOG_H
#define QPENALTYPARKINGDIALOG_H


#include "service_widgets/qcsbasedialog.h"
#include "service_widgets/qcspaybasedialog.h"

#include "service_widgets/qlinetext.h"
#include "service_widgets/qloaddoclinewidget.h"
#include "service_widgets/qloaddocsdlg.h"
#include "service_widgets/qselprovidercarshwidget.h"
#include <QLabel>
#include <QObject>
#include <QPushButton>
#include "service_widgets/qcsbutton.h"

class QPenaltyParkingDialog : public QCSBaseDialog
{
    Q_OBJECT
public:
    QPenaltyParkingDialog(QWidget *parent = nullptr, Qt::WindowFlags f = Qt::WindowFlags());

    void SaveDataToBD();
    void LoadDataFromBD(QUuid);

protected:
    QLabel * m_pTopLabel;

    QLineText * m_pPlateLineText;

    QLineText * m_pLineTextComment;
    QLoadDocLineWidget * m_pLoadActWidget;
    QLoadDocLineWidget * m_pLoadProtocolWidget;
    QLoadDocsDlg * m_pLoadAutoFotoDlg;
    QPushButton * m_pLoadAutoFotoButton;
    QCSButton * m_pPayButton;
    QPushButton * m_pGibddButton;
    QPushButton * m_pReasonButton;
    QPushButton * m_pParkingButton;
    QPushButton * m_pReturnToZoneButton;
    QPushButton * m_pZayavkiButton;
    QSelProviderCarshWidget * m_pSelProviderCarshWidget;

    QCSPayBaseDialog m_PayDlg;


    QString m_strPinaltiParkingId;
    QString m_strPinaltiParkingText;

    QString m_strReasonId;
    QString m_strReasonText;

    QString m_strGaiId;
    QString m_strGaiText;

    QUuid m_uuidSourseRecord;
    QUuid m_uuidSourseExtention;
    QUuid m_uuidReturnToZoneSource;
    QUuid m_uuidReturnToZoneExtensionSource;

    bool isReady();

public slots:
    void OnPayButtonPressed();
    void OnApplyPressedSlot();
    void OnGibddButtonPressed();
    void OnReasonButtonPressed();
    void OnParkingButtonPressed();
    void OnRemovePressedSlot();
    void OnReturnToZoneButtonPressed();
    void OnLoadAutoFotoButtonPressed();
    void OnCarshChanged();
    void OnProviderChanged();
    void OnHandOverPressedSlot();
    void OnNumberTextInput(const QString &text);
    void OnCommentTextInput(const QString &text);
};

#endif // QPENALTYPARKINGDIALOG_H
