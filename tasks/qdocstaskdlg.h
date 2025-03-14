#ifndef QDOCSTASKDLG_H
#define QDOCSTASKDLG_H

#include "service_widgets/qcsbasedialog.h"
#include "service_widgets/qcspaybasedialog.h"

#include "service_widgets/qlinetext.h"

#include "service_widgets/qselprovidercarshwidget.h"
#include <QLabel>
#include <QObject>
#include <QPushButton>
#include "service_widgets/QCSButton.h"

class QDocsTaskDlg : public QCSBaseDialog
{
    Q_OBJECT
public:
    QDocsTaskDlg(QWidget *parent = nullptr, Qt::WindowFlags f = Qt::WindowFlags());

    void SaveDataToBD();
    void LoadDataFromBD(QUuid);

    QCSButton * m_pPayButton;
    QLineText * m_pLineTextComment;
    QPushButton * m_pDocTypeButton;
    QLineText * m_pDocsCountText;
    QSelProviderCarshWidget * m_pSelProviderCarshWidget;
    QCSPayBaseDialog m_PayDlg;

    QString m_strDocId;
    QString m_strDocText;

    QUuid m_uuidSourseRecord;
    QUuid m_uuidSourseExtention;

    bool isReady();

protected:
    QLabel * m_pTopLabel;

public slots:
    void OnPayButtonPressed();
    void OnApplyPressedSlot();
    void OnDocButtonPressed();
    void OnRemovePressedSlot();
    void OnCarshChanged();
    void OnProviderChanged();
    void OnCountTextInput(const QString &text);
    void OnCommentTextInput(const QString &text);
};

#endif // QDOCSTASKDLG_H
