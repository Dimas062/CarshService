#include "qStickpartnermaindlg.h"
#include <QHBoxLayout>
#include <QLabel>
#include <QVBoxLayout>
#include "partners/Sticks/qStickpartnertask.h"
#include "partners/Sticks/qStickpartnertaskslistdlg.h"

extern int iButtonHeight;


QStickPartnerMainDlg::QStickPartnerMainDlg(QWidget *parent, Qt::WindowFlags f ):QCSBaseDialog(parent , f)
{
    QVBoxLayout * pVMainLayout = new QVBoxLayout;

    pVMainLayout->addSpacing(5);

    m_pNewStickTaskButton = new QPushButton("Новая задача");
    connect(m_pNewStickTaskButton,SIGNAL(pressed()),this,SLOT(OnNewStickTaskPressed()));
    m_pNewStickTaskButton->setMaximumHeight(iButtonHeight*1.30);
    m_pNewStickTaskButton->setMinimumHeight(iButtonHeight*1.30);
    pVMainLayout->addWidget(m_pNewStickTaskButton);

    m_pCurrentTasksButton = new QPushButton("Текущие задачи");
    connect(m_pCurrentTasksButton,SIGNAL(pressed()),this,SLOT(OnCurrentTaskPressed()));
    m_pCurrentTasksButton->setMaximumHeight(iButtonHeight*1.30);
    m_pCurrentTasksButton->setMinimumHeight(iButtonHeight*1.30);
    pVMainLayout->addWidget(m_pCurrentTasksButton);

    this->setLayout(pVMainLayout);
}

void QStickPartnerMainDlg::OnNewStickTaskPressed()
{
    QStickPartnerTask dlg;
    dlg.exec();
}
void QStickPartnerMainDlg::OnCurrentTaskPressed()
{
    QStickPartnerTasksListDlg dlg;
    dlg.exec();
}
