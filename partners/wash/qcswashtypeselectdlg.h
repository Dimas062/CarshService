#ifndef QCSWASHTYPESELECTDLG_H
#define QCSWASHTYPESELECTDLG_H

#include "qcsselectwashtypesswidget.h"
#include "service_widgets/qcsbasedialog.h"
#include <QObject>
#include <QLabel>

class QCSWashTypeSelectDlg : public QCSBaseDialog
{
    Q_OBJECT
public:
    QCSWashTypeSelectDlg(QWidget *parent = nullptr, Qt::WindowFlags f = Qt::WindowFlags());

    QCSSelectWashTypessWidget selectWidget;
    QLabel * m_pTopLabel;

public slots:
    void OnApplyPressedSlot();
};

#endif // QCSWASHTYPESELECTDLG_H
