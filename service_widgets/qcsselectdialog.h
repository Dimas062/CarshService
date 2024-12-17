#ifndef QCSSELECTDIALOG_H
#define QCSSELECTDIALOG_H

#include "qcsbasedialog.h"

#include <QObject>
#include <QPushButton>
#include <QLabel>
#include <QUuid>
#include <QPushButton>
#include <QVector>
#include "qcsselectdlgbuttonswidget.h"

class QCSSelectDialog : public QCSBaseDialog
{
    Q_OBJECT
public:
    QCSSelectDialog(QString strTableName , QString strColName = "Название", bool bChecable = true , bool bAutoChecable = false , QUuid uuidEmpl = QUuid(), QString strСondition =  " " , bool bMultiSelect = false , QWidget *parent = nullptr, Qt::WindowFlags f = Qt::WindowFlags());
    QCSSelectDlgButtonsWidget selectWidget;
    QLabel * m_pTopLabel;
    QUuid m_userUUid;
    bool m_bMultiSelect;

    void SelectId(QString strId) {selectWidget.SelectId(strId);}
    void SelectId(QUuid uuidId) {selectWidget.SelectId(uuidId.toString());}
    void SelectIds(QVector<QString> strIds) {selectWidget.SelectIds(strIds);}
    QString getCurId(){return selectWidget.m_strId;}
    QVector<QString> getCurIds(){return selectWidget.m_vstrId;}
    QString getCurText(){return selectWidget.m_strText;}
    QUuid getCurIdUUid(){return QUuid::fromString(selectWidget.m_strId);}


public slots:
    void OnApplyPressedSlot();
    void FioClicked();
};

#endif // QCSSELECTDIALOG_H
