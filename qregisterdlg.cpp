#include "qregisterdlg.h"
#include <QVBoxLayout>
#include <QLabel>
#include <QGuiApplication>
#include <QKeyEvent>
#include <QPushButton>
#include <qregisteremploeedlg.h>

extern QRect screenGeometry;
extern int iButtonHeight;


QRegisterDlg::QRegisterDlg(QWidget *parent, Qt::WindowFlags f ):QCSBaseDialog(parent , f)
{
    // int iUnderButtonSpace = 15;

    // int iButtonHeight = (int)((screenGeometry.height()*0.7)/6)-iUnderButtonSpace;


    QVBoxLayout * pVMainLayout = new QVBoxLayout;


    pVMainLayout->addSpacing(5);


    QLabel * pLogoLabel = new QLabel();
    QPixmap topIconPixmap(":/icons/CarshServiceIcon.png");
    pLogoLabel->setPixmap(topIconPixmap.scaled(70,70));
    pLogoLabel->setAlignment(Qt::AlignCenter);

    pVMainLayout->addWidget(pLogoLabel);

    QLabel * pLogoTextLabel = new QLabel ("Регистрация");
    pLogoTextLabel->setAlignment(Qt::AlignCenter);
    pVMainLayout->addWidget(pLogoTextLabel);


    pVMainLayout->addStretch();

    QPushButton * m_pPartnerPlateRegisterButton = new QPushButton("Партнёр \"Номера\"");
    connect(m_pPartnerPlateRegisterButton,SIGNAL(pressed()),this,SLOT(OnPartnerPlateRegisterPressed()));
    m_pPartnerPlateRegisterButton->setMaximumHeight(iButtonHeight);
    m_pPartnerPlateRegisterButton->setMinimumHeight(iButtonHeight);
    pVMainLayout->addWidget(m_pPartnerPlateRegisterButton);

    QPushButton * m_pWashPlateRegisterButton = new QPushButton("Партнёр \"Мойка\"");
    connect(m_pWashPlateRegisterButton,SIGNAL(pressed()),this,SLOT(OnWashPlateRegisterPressed()));
    m_pWashPlateRegisterButton->setMaximumHeight(iButtonHeight);
    m_pWashPlateRegisterButton->setMinimumHeight(iButtonHeight);
    pVMainLayout->addWidget(m_pWashPlateRegisterButton);

    QPushButton * m_pStickPlateRegisterButton = new QPushButton("Партнёр \"Оклейка\"");
    connect(m_pStickPlateRegisterButton,SIGNAL(pressed()),this,SLOT(OnStickPlateRegisterPressed()));
    m_pStickPlateRegisterButton->setMaximumHeight(iButtonHeight);
    m_pStickPlateRegisterButton->setMinimumHeight(iButtonHeight);
    pVMainLayout->addWidget(m_pStickPlateRegisterButton);

    QPushButton * m_pCustomerPlateRegisterButton = new QPushButton("Заказчик");
    connect(m_pCustomerPlateRegisterButton,SIGNAL(pressed()),this,SLOT(OnCustomerPlateRegisterPressed()));
    m_pCustomerPlateRegisterButton->setMaximumHeight(iButtonHeight);
    m_pCustomerPlateRegisterButton->setMinimumHeight(iButtonHeight);
    pVMainLayout->addWidget(m_pCustomerPlateRegisterButton);

    QPushButton * m_pEmployeeRegisterButton = new QPushButton("Сотрудник");
    connect(m_pEmployeeRegisterButton,SIGNAL(pressed()),this,SLOT(OnEmployeeRegisterPressed()));
    m_pEmployeeRegisterButton->setMaximumHeight(iButtonHeight);
    m_pEmployeeRegisterButton->setMinimumHeight(iButtonHeight);
    pVMainLayout->addWidget(m_pEmployeeRegisterButton);

    pVMainLayout->addStretch();
    this->setLayout(pVMainLayout);
}

void QRegisterDlg::OnPartnerPlateRegisterPressed()
{

}

void QRegisterDlg::OnPartnerWashRegisterPressed()
{

}

void QRegisterDlg::OnPartnerStickRegisterPressed()
{

}

void QRegisterDlg::OnCustomerPlateRegisterPressed()
{

}

void QRegisterDlg::OnWashPlateRegisterPressed()
{

}

void QRegisterDlg::OnStickPlateRegisterPressed()
{

}

void QRegisterDlg::OnEmployeeRegisterPressed()
{
    QRegisterEmploeeDlg dlg;
    dlg.exec();
}

