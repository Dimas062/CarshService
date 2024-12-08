#include "qcarshservicemaindlg.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QGuiApplication>
#include <QPushButton>
#include "carsh_service_widgets/qcarshserviceusersdlg.h"


extern QString sStandartStoragePath;

extern QRect screenGeometry;
extern int iButtonHeight;

QCarshServiceMainDlg::QCarshServiceMainDlg(QWidget *parent, Qt::WindowFlags f ):QCSBaseDialog(parent , f)
{
    QVBoxLayout * pVMainLayout = new QVBoxLayout;

    pVMainLayout->addSpacing(5);

    QPushButton * pUsersButton = new QPushButton("Сотрудники");
    connect(pUsersButton,SIGNAL(pressed()),this,SLOT(OnUsersPressed()));
    pUsersButton->setMaximumHeight(iButtonHeight*2);
    pUsersButton->setMinimumHeight(iButtonHeight*2);
    pVMainLayout->addWidget(pUsersButton);

    QPushButton * pPartnersButton = new QPushButton("Партнеры");
    connect(pPartnersButton,SIGNAL(pressed()),this,SLOT(OnPartnersPressed()));
    pPartnersButton->setMaximumHeight(iButtonHeight*2);
    pPartnersButton->setMinimumHeight(iButtonHeight*2);
    pVMainLayout->addWidget(pPartnersButton);

    this->setLayout(pVMainLayout);
}

void QCarshServiceMainDlg::OnUsersPressed()
{
    QCarshServiceUsersDlg dlg;
    dlg.exec();
}

void QCarshServiceMainDlg::OnPartnersPressed()
{

}

