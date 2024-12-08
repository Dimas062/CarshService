#ifndef QCSPAYBASEDIALOG_H
#define QCSPAYBASEDIALOG_H

#include "qcsbasedialog.h"
#include "qlinetext.h"
#include "qloaddoclinewidget.h"
#include <QObject>
#include <QPushButton>
#include <QLabel>
#include "pictures/qpictureswidget.h"
#include <QUuid>
#include "common.h"

class QCSPayBaseDialog : public QCSBaseDialog
{
    Q_OBJECT
public:
    QCSPayBaseDialog(QWidget *parent = nullptr, Qt::WindowFlags f = Qt::WindowFlags() , bool bOneCheck = false);

    QLineText * m_pCashLineText;
    QPicturesWidget * m_pPicturesWidget;

    QPushButton * m_pCardPayButton;
    QPushButton * m_pBusinessPayButton;

    PayTypes GetSelectedPayType();
    QString getSumString() {return m_pCashLineText->getText();}

    void LoadFromBD(QUuid uuidPay);

    bool m_bOneCheck;

protected:
    QLoadDocLineWidget * m_pLoadPhotoWidget;

    QLabel * m_pTopLabel;

public slots:
    void OnFotoGetet(QString);
    void OnApplyPressedSlot();
    void OnCardPayPressedSlot();
    void OnBusinessPayPressedSlot();
};

#endif // QCSPAYBASEDIALOG_H
