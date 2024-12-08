#ifndef QYESNODLG_H
#define QYESNODLG_H

#include <QDialog>
#include <QString>

class QYesNoDlg : public QDialog
{
    Q_OBJECT
public:
    QYesNoDlg(QString text , QWidget *parent = nullptr, Qt::WindowFlags f = Qt::WindowFlags());
};

#endif // QYESNODLG_H
