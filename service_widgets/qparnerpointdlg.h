#ifndef QPARNERPOINTDLG_H
#define QPARNERPOINTDLG_H

#include "service_widgets/qcsbasedialog.h"
#include <QObject>
#include "service_widgets/qlinetext.h"

class QParnerPointDlg : public QCSBaseDialog
{
    Q_OBJECT
public:
    QParnerPointDlg(QWidget *parent = nullptr, Qt::WindowFlags f = Qt::WindowFlags());

    QLineText * m_pLineTextName;
    QLineText * m_pLineTextAddr;
};

#endif // QPARNERPOINTDLG_H
