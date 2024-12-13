#ifndef QULDLG_H
#define QULDLG_H

#include "qcsbasedialog.h"
#include <QObject>
#include <QUuid>
#include "qlinetext.h"


class QULDlg : public QCSBaseDialog
{
    Q_OBJECT
public:
    QULDlg(QWidget *parent = nullptr, Qt::WindowFlags f = Qt::WindowFlags());

    QLineText * m_pNameLineText;
    QLineText * m_pAdressLineText;
    QLineText * m_pINNLineText;
    QLineText * m_pBankLineText;
    QLineText * m_pSchetLineText;

    void LoadFromBD(QUuid);
    QUuid SaveOrCreateToBD(QUuid);


public slots:
    void OnApplyPressedSlot();
};

#endif // QULDLG_H
