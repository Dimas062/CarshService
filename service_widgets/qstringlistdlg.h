#ifndef QSTRINGLISTDLG_H
#define QSTRINGLISTDLG_H

#include "service_widgets/qcsbasedialog.h"
#include "service_widgets/qcsbaselistwidget.h"
#include <QObject>

class QStringListDlg : public QCSBaseDialog
{
    Q_OBJECT
public:
    QStringListDlg(QStringList strList , QString strTitle , QWidget *parent = nullptr, Qt::WindowFlags f = Qt::WindowFlags());
    QStringList m_strList;
protected:
    QCSBaseListWidget * m_pStrsListWidget;
    bool m_bIsGRZ;

public slots:
    void OnAddPressed();
    void OnRemPressed();
    void OnApplyPressedSlot();
};

#endif // QSTRINGLISTDLG_H
