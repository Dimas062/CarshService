#ifndef QSETTINGSDLG_H
#define QSETTINGSDLG_H

#include "service_widgets/qcsbasedialog.h"
#include "settings_widgets/qsettingslistwidget.h"

class QSettingsDlg : public QCSBaseDialog
{
    Q_OBJECT
public:
    QSettingsDlg(QWidget *parent = nullptr, Qt::WindowFlags f = Qt::WindowFlags());


    QSettingsListWidget * m_pSettingsListWidget;

private slots:
    void OnApply();
};

#endif // QSETTINGSDLG_H
