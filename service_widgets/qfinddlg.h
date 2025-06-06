#ifndef QFINDDLG_H
#define QFINDDLG_H

#include <QDialog>
#include <QObject>
#include "service_widgets/qcslineedit.h"
#include <QString>

class QFindDlg : public QDialog
{
    Q_OBJECT
public:
    QFindDlg();
    QString GetText() const;

protected:
    QCSLineEdit * m_pTextLineEdit;
};

#endif // QFINDDLG_H
