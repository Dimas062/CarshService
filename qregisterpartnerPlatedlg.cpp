#include "qregisterpartnerplatedlg.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QGuiApplication>
#include <QKeyEvent>
#include <QPushButton>
#include <common.h>

extern QRect screenGeometry;

QRegisterPartnerPlateDlg::QRegisterPartnerPlateDlg(QWidget *parent, Qt::WindowFlags f ):QCSBaseDialog(parent , f)
{
    QVBoxLayout * pVMainLayout = new QVBoxLayout;
    this->setLayout(pVMainLayout);
}
