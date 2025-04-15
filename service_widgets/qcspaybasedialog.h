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
    QCSPayBaseDialog(QWidget *parent = nullptr, Qt::WindowFlags f = Qt::WindowFlags() , bool bOneCheck = false , bool bNoPayButton=false);

    QLineText * m_pCashLineText;
    QPicturesWidget * m_pPicturesWidget;

    QPushButton * m_pCardPayButton;
    QPushButton * m_pBusinessPayButton;
    QPushButton * m_pNoPayButton;
    QPushButton * m_pCalendarButton;

    PayTypes GetSelectedPayType();
    QString getSumString() {return m_pCashLineText->getText();}

    void LoadFromBD(QUuid uuidPay);

    bool m_bOneCheck;
    qint64 m_iPayDate;
protected:
    QLoadDocLineWidget * m_pLoadPhotoWidget;

    QLabel * m_pTopLabel;

    QLabel * m_pDateLabel;

    void UpdateDateLabel(){m_pDateLabel->setText(QString("Дата чека: %1").arg(QDateTime::fromSecsSinceEpoch(m_iPayDate).toString("dd.MM.yyyy")));}


public slots:
    void OnFotoGetet(QString);
    void OnApplyPressedSlot();
    void OnCardPayPressedSlot();
    void OnBusinessPayPressedSlot();
    void OnNoPayPayPressedSlot();
    void OnCalendarPressedSlot();
};

#endif // QCSPAYBASEDIALOG_H
