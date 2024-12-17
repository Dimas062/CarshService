#ifndef QCSMULTISELECTDLG_H
#define QCSMULTISELECTDLG_H

#include "qcsbasedialog.h"
#include <QObject>
#include <QPushButton>
#include <QLabel>
#include <QUuid>
#include <QPushButton>
#include <QVector>
#include "qcsselectdlgbuttonswidget.h"


class QCSMultiSelectDlg : public QCSBaseDialog
{
    Q_OBJECT
public:
    QCSMultiSelectDlg(QString strTableName , QString strColName);

   // QCSSelectDlgButtonsWidget selectWidget;

    // void SelectId(QString strId) {selectWidget.SelectId(strId);}
    // void SelectId(QUuid uuidId) {selectWidget.SelectId(uuidId.toString());}
    // QString getCurId(){return selectWidget.m_strId;}
    // QString getCurText(){return selectWidget.m_strText;}

public slots:
    void OnApplyPressedSlot();

};

#endif // QCSMULTISELECTDLG_H
