#ifndef QCLIENTAGREEMENTDLG_H
#define QCLIENTAGREEMENTDLG_H


#include <QObject>
#include "service_widgets/qcsbasedialog.h"
#include "service_widgets/qcspaybasedialog.h"

#include "service_widgets/qlinetext.h"
#include "service_widgets/qloaddoclinewidget.h"
#include "service_widgets/qloaddocsdlg.h"
#include "service_widgets/qselprovidercarshwidget.h"
#include <QLabel>
#include <QObject>
#include <QPushButton>
#include "service_widgets/QCSButton.h"


class QClientAgreementDlg : public QCSBaseDialog
{
    Q_OBJECT
public:
    QClientAgreementDlg(QWidget *parent = nullptr, Qt::WindowFlags f = Qt::WindowFlags());

protected:
    QLabel * m_pTopLabel;

    QLineText * m_pFIOLineText;
    QLineText * m_pGRZLineText;

    QLoadDocLineWidget * m_pLoadPassportWidget;
    QLoadDocLineWidget * m_pLoadPTSWidget;
    QLoadDocLineWidget * m_pLoadLicWidget;
};

#endif // QCLIENTAGREEMENTDLG_H
