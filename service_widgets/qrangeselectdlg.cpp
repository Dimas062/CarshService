#include "qrangeselectdlg.h"
#include <QGridLayout>
#include <QPushButton>


QRangeSelectDlg::QRangeSelectDlg(QWidget *parent, Qt::WindowFlags f):QDialog(parent , f)
{
    QGridLayout * pMainGridLayout = new QGridLayout();
    this->setLayout(pMainGridLayout);
}
