#ifndef QCSSELECTDIALOG_H
#define QCSSELECTDIALOG_H

#include "qcsbasedialog.h"
#include "qlinetext.h"
#include "qloaddoclinewidget.h"
#include <QObject>
#include <QPushButton>
#include <QLabel>
#include "pictures/qpictureswidget.h"
#include <QUuid>
#include "common.h"
#include <QPushButton>
#include <QVector>
#include "qcsselectdlgbuttonswidget.h"

class QCSSelectDialog : public QCSBaseDialog
{
    Q_OBJECT
public:
    QCSSelectDialog(QString strTableName , QString strColName = "Название", bool bChecable = true , bool bAutoChecable = false , QUuid uuidEmpl = QUuid(), QWidget *parent = nullptr, Qt::WindowFlags f = Qt::WindowFlags());
    QCSSelectDlgButtonsWidget selectWidget;
    QLabel * m_pTopLabel;
    QUuid m_userUUid;

    void SelectId(QString strId) {selectWidget.SelectId(strId);}
    void SelectId(QUuid uuidId) {selectWidget.SelectId(uuidId.toString());}
    QString getCurId(){return selectWidget.m_strId;}
    QString getCurText(){return selectWidget.m_strText;}
    QUuid getCurIdUUid(){return QUuid::fromString(selectWidget.m_strId);}


public slots:
    void OnApplyPressedSlot();
    void FioClicked();
};

#endif // QCSSELECTDIALOG_H
