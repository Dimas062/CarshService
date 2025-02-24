#ifndef QPARKINGTASKDIALOG_H
#define QPARKINGTASKDIALOG_H

#include "service_widgets/qcsbasedialog.h"
#include "service_widgets/qlinetext.h"
#include "service_widgets/qloaddocsdlg.h"
#include "service_widgets/qselprovidercarshwidget.h"
#include "service_widgets/qcspaybasedialog.h"
#include <QLabel>
#include <QObject>
#include <QPushButton>


class QParkingTaskDialog : public QCSBaseDialog
{
    Q_OBJECT
public:
    QParkingTaskDialog(QWidget *parent = nullptr, Qt::WindowFlags f = Qt::WindowFlags());

    void SaveDataToBD();
    void LoadDataFromBD(QUuid);


protected:
    QLabel * m_pTopLabel;
    QLineText * m_pPlateLineText;
    QPushButton * m_pPayButton;


    QLoadDocsDlg * m_pLoadAutoFotoDlg;
    QPushButton * m_pLoadAutoFotoButton;
    QLineText * m_pLineTextComment;
    QSelProviderCarshWidget * m_pSelProviderCarshWidget;

    QCSPayBaseDialog m_PayDlg;

    bool isReady();
    QUuid m_uuidSourseRecord;
    QUuid m_uuidSourseExtention;

public slots:
    void OnPayButtonPressed();
    void OnApplyPressedSlot();
    void OnRemovePressedSlot();
    void OnCarshChanged();
    void OnProviderChanged();
    void OnLoadAutoFotoButtonPressed();
    void OnNumberTextInput(const QString &text);
    void OnCommentTextInput(const QString &text);
};

#endif // QPARKINGTASKDIALOG_H
