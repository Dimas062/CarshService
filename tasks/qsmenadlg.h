#ifndef QSMENADLG_H
#define QSMENADLG_H

#include "service_widgets/qcsbasedialog.h"
#include <QObject>
#include <QLabel>
#include <QPushButton>
#include <QUuid>
#include <QString>
#include "service_widgets/qlinetext.h"
#include "service_widgets/qselprovidercarshwidget.h"

class QSmenaDlg : public QCSBaseDialog
{
    Q_OBJECT
public:
    QSmenaDlg(QWidget *parent = nullptr, Qt::WindowFlags f = Qt::WindowFlags());

    void SaveDataToBD();
    void LoadDataFromBD(QUuid);

protected:
    QLabel * m_pTopLabel;
    QLineText * m_pLineTextComment;
    QSelProviderCarshWidget * m_pSelProviderCarshWidget;
    QPushButton * m_pClockButton;

    bool isReady();
    QUuid m_uuidSourseRecord;
    QUuid m_uuidSourseExtention;

    QString m_strClockId;
    QString m_strClockText;

public slots:
    void OnApplyPressedSlot();
    void OnRemovePressedSlot();
    void OnCarshChanged();
    void OnProviderChanged();
    void OnClockPressed();
};

#endif // QSMENADLG_H
