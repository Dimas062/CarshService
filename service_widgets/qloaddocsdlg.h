#ifndef QLOADDOCSDLG_H
#define QLOADDOCSDLG_H

#include "qcsbasedialog.h"
#include "pictures/qpictureswidget.h"
#include "service_widgets/qloaddoclinewidget.h"

class QLoadDocsDlg : public QCSBaseDialog
{
    Q_OBJECT
public:
    QLoadDocLineWidget * m_pLoadPhotoWidget;
    QPicturesWidget * m_pPicturesWidget;
    QLoadDocsDlg(QWidget *parent = nullptr, Qt::WindowFlags f = Qt::WindowFlags());

public slots:
    void OnFotoGetet(QString);
    void OnFotoShowed(QImage &);
};

#endif // QLOADDOCSDLG_H
