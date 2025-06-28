#ifndef QCOSTSDIALOG_H
#define QCOSTSDIALOG_H

#include "service_widgets/qcsbasedialog.h"
#include <QObject>
#include "service_widgets/qcspaybasedialog.h"
#include <QLabel>
#include <QObject>
#include <QPushButton>
#include "service_widgets/qlinetext.h"

class QCostsDialog : public QCSBaseDialog
{
    Q_OBJECT
public:
    QCostsDialog(QWidget *parent = nullptr, Qt::WindowFlags f = Qt::WindowFlags());

    void SaveDataToBD();
    void LoadDataFromBD(QUuid);

protected:
    QLabel * m_pTopLabel;
    QPushButton * m_pPayButton;
    QPushButton * m_pArticleButton;
    QPushButton * m_pItemButton;
    QCSPayBaseDialog m_PayDlg;
    bool isReady();
    QUuid m_uuidSourseRecord;
    QLineText * m_pLineTextCount;
    void UpdateButtonsText();

    QString m_strArticleId;
    QString m_strArticleText;

    QString m_strItemId;
    QString m_strItemText;


public slots:

    void OnPayButtonPressed();
    void OnArticleButtonPressed();
    void OnItemButtonPressed();
    void OnApplyPressedSlot();
    void OnRemovePressedSlot();
    void OnCountTextInput(const QString &text);
};

#endif // QCOSTSDIALOG_H
