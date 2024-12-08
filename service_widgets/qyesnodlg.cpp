#include "qyesnodlg.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QLabel>

QYesNoDlg::QYesNoDlg(QString text , QWidget *parent, Qt::WindowFlags f):QDialog(parent , f)

{
    QVBoxLayout * mainLayout = new QVBoxLayout;
    this->setLayout(mainLayout);

    QLabel * pTextLabel = new QLabel(text);
    mainLayout->addWidget(pTextLabel);

    QHBoxLayout * buttonsLayout = new QHBoxLayout;

    QPushButton * pYesButton = new QPushButton(QIcon(":/icons/done_icon.png"),"Да",this);
    connect(pYesButton , SIGNAL(clicked()) , this , SLOT(accept()));
    QPushButton * pNoButton = new QPushButton(QIcon(":/icons/remove_icon.png"),"Нет",this);
    connect(pNoButton , SIGNAL(clicked()) , this , SLOT(reject()));

    buttonsLayout->addWidget(pYesButton);
    buttonsLayout->addWidget(pNoButton);

    mainLayout->addLayout(buttonsLayout);
}
