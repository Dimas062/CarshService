#ifndef QPLATETASKDIALOG_H
#define QPLATETASKDIALOG_H

#include "service_widgets/qcsbasedialog.h"
#include "service_widgets/qlinetext.h"
#include "service_widgets/qloaddocsdlg.h"
#include "service_widgets/qselprovidercarshwidget.h"
#include <QObject>
#include <QPushButton>
#include <QLabel>
#include <QUuid>

class QPlateTaskDialog : public QCSBaseDialog
{
    Q_OBJECT
public:
    QPlateTaskDialog(QWidget *parent = nullptr, Qt::WindowFlags f = Qt::WindowFlags());

    QLabel * m_pTopLabel;
    QLineText * m_pPlateLineText;

    QLoadDocsDlg * m_pLoadAutoFotoDlg;
    QPushButton * m_pLoadAutoFotoButton;
    QLineText * m_pLineTextComment;
    QSelProviderCarshWidget * m_pSelProviderCarshWidget;

    void SaveDataToBD();
    void LoadDataFromBD(QUuid);

    bool isReady();
protected:
    QPushButton * m_pOnePlateButton;
    QPushButton * m_pTwoPlateButton;
    QPushButton * m_pZeroPlateButton;

    QPushButton * m_pOneGRZButton;
    QPushButton * m_pTwoGRZButton;

    QUuid m_uuidSourseRecord;
    QUuid m_uuidSourseExtention;


public slots:
    void OnOnePlatePressedSlot(bool);
    void OnTwoPlatePressedSlot(bool);
    void OnZeroPlatePressedSlot(bool);
    void OnOneGRZPressedSlot(bool);
    void OnTwoGRZPressedSlot(bool);
    void OnApplyPressedSlot();
    void OnRemovePressedSlot();
    void OnCarshChanged();
    void OnProviderChanged();
    void OnLoadAutoFotoButtonPressed();
    void OnNumberTextInput(const QString &text);
    void OnCommentTextInput(const QString &text);
};

#endif // QPLATETASKDIALOG_H
