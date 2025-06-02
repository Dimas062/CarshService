#ifndef QINPUTTEXTDLG_H
#define QINPUTTEXTDLG_H

#include <QDialog>
#include <QObject>
#include "service_widgets/qcslineedit.h"
#include <QString>

class QInputTextDlg : public QDialog
{
    Q_OBJECT
public:
    QInputTextDlg();
    QString GetText() const;

protected:
    QCSLineEdit * m_pTextLineEdit;
};

#endif // QINPUTTEXTDLG_H
