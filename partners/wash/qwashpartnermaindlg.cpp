#include "qWashpartnermaindlg.h"
#include <QHBoxLayout>
#include <QLabel>
#include <QVBoxLayout>
#include "partners/wash/qwashpartnertask.h"
#include "partners/wash/qwashpartnertaskslistdlg.h"

extern int iButtonHeight;


QWashPartnerMainDlg::QWashPartnerMainDlg(QWidget *parent, Qt::WindowFlags f ):QCSBaseDialog(parent , f)
{
    QVBoxLayout * pVMainLayout = new QVBoxLayout;

    pVMainLayout->addSpacing(5);

    m_pNewWashTaskButton = new QPushButton("Новая задача");
    connect(m_pNewWashTaskButton,SIGNAL(pressed()),this,SLOT(OnNewWashTaskPressed()));
    m_pNewWashTaskButton->setMaximumHeight(iButtonHeight*1.30);
    m_pNewWashTaskButton->setMinimumHeight(iButtonHeight*1.30);
    pVMainLayout->addWidget(m_pNewWashTaskButton);

    m_pCurrentTasksButton = new QPushButton("Текущие задачи");
    connect(m_pCurrentTasksButton,SIGNAL(pressed()),this,SLOT(OnCurrentTaskPressed()));
    m_pCurrentTasksButton->setMaximumHeight(iButtonHeight*1.30);
    m_pCurrentTasksButton->setMinimumHeight(iButtonHeight*1.30);
    pVMainLayout->addWidget(m_pCurrentTasksButton);

    this->setLayout(pVMainLayout);
}

void QWashPartnerMainDlg::OnNewWashTaskPressed()
{
    QWashPartnerTask dlg;
    dlg.exec();
}
void QWashPartnerMainDlg::OnCurrentTaskPressed()
{
    QWashPartnerTasksListDlg dlg;
    dlg.exec();
}
