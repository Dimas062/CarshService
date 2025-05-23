#ifndef QRETTOZONEDIALOG_H
#define QRETTOZONEDIALOG_H

#include "service_widgets/qcsbasedialog.h"
#include <QObject>

#include "service_widgets/qlinetext.h"
#include "service_widgets/qloaddocsdlg.h"
#include "service_widgets/qselprovidercarshwidget.h"

#include <QLabel>
#include <QObject>
#include <QPushButton>

class QRetToZoneDialog : public QCSBaseDialog
{
    Q_OBJECT
public:
    QRetToZoneDialog(QWidget *parent = nullptr, Qt::WindowFlags f = Qt::WindowFlags());

    void SaveDataToBD();
    void LoadDataFromBD(QUuid);

    //QPicturesWidget * m_pPicturesWidget;

protected:
    QLabel * m_pTopLabel;
    QLineText * m_pPlateLineText;
    QPushButton * m_pPayButton;


    QLoadDocsDlg * m_pLoadAutoFotoDlg;
    QPushButton * m_pLoadAutoFotoButton;
    QLineText * m_pLineTextComment;
    QSelProviderCarshWidget * m_pSelProviderCarshWidget;
    QPushButton * m_pParkingButton;


    bool isReady();
    QUuid m_uuidSourseRecord;
    QUuid m_uuidSourseExtention;

    QString m_strPinaltiParkingId;
    QString m_strPinaltiParkingText;

public slots:
    void OnApplyPressedSlot();
    void OnRemovePressedSlot();
    void OnCarshChanged();
    void OnParkingButtonPressed();
    void OnProviderChanged();
    void OnLoadAutoFotoButtonPressed();
    void OnNumberTextInput(const QString &text);
    void OnCommentTextInput(const QString &text);
};

#endif // QRETTOZONEDIALOG_H
