#ifndef QREGISTEREMPLOEEDLG_H
#define QREGISTEREMPLOEEDLG_H

#include "pictures/imagepickerandroid.h"
#include "pictures/qpictureswidget.h"
#include "service_widgets/qcolumntext.h"
#include "service_widgets/qcsbasedialog.h"
#include "service_widgets/qlinetext.h"
#include "service_widgets/qloaddoclinewidget.h"
#include <QLineEdit>
#include <QObject>
#include <common.h>


class QRegisterEmploeeDlg : public QCSBaseDialog
{
    Q_OBJECT
public:
    QRegisterEmploeeDlg(QWidget *parent = nullptr, Qt::WindowFlags f = Qt::WindowFlags());

    QColumnText * m_pLoginColumnText;
    QColumnText * m_pPasswordColumnText;
    QLineText * m_pSurnameLineText;
    QLineText * m_pNameLineText;
    QLineText * m_pMiddlenameLineText;
    QLineText * m_pPhoneLineText;

    QLoadDocLineWidget * m_pLoadPassportWidget;
    QLoadDocLineWidget * m_pLoadDriverCardWidget;
    QLoadDocLineWidget * m_pLoadSertWidget;
    QLoadDocLineWidget * m_pLoadPhotoWidget;


protected:

signals:


public slots:
    void OnApplyPressed();
};

#endif // QREGISTEREMPLOEEDLG_H
