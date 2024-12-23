#ifndef QWASHPARTNERPENLISTDLG_H
#define QWASHPARTNERPENLISTDLG_H

#include "service_widgets/qcsbasedialog.h"
#include <QObject>
#include "service_widgets/qcsbaselistwidget.h"
#include <QUuid>

class QWashPartnerPenListDlg : public QCSBaseDialog
{
    Q_OBJECT
public:
    QWashPartnerPenListDlg(QUuid task , QWidget *parent = nullptr, Qt::WindowFlags f = Qt::WindowFlags());
    QCSBaseListWidget * m_pPenListWidget;
    QUuid m_uuidTask;

    void UpdatePens();
public slots:
    void OnTapGesture();
};

#endif // QWASHPARTNERPENLISTDLG_H
