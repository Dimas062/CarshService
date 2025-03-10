#ifndef QFINDDLG_H
#define QFINDDLG_H

#include <QDialog>
#include <QObject>
#include <QLineEdit>
#include <QString>

class QFindDlg : public QDialog
{
    Q_OBJECT
public:
    QFindDlg();
    QString GetText() const;

protected:
    QLineEdit * m_pTextLineEdit;
};

#endif // QFINDDLG_H
