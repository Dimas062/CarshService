#include "qplatepartnermaindlg.h"
#include <QHBoxLayout>
#include <QLabel>
#include <QVBoxLayout>
#include "partners/plates/qplatepartnertask.h"
#include "partners/plates/qplatepartnertaskslistdlg.h"

extern int iButtonHeight;


QPlatePartnerMainDlg::QPlatePartnerMainDlg(QWidget *parent, Qt::WindowFlags f ):QCSBaseDialog(parent , f)
{
    QVBoxLayout * pVMainLayout = new QVBoxLayout;

    pVMainLayout->addSpacing(5);

    m_pNewPlateTaskButton = new QPushButton("Новая задача");
    connect(m_pNewPlateTaskButton,SIGNAL(pressed()),this,SLOT(OnNewPlateTaskPressed()));
    m_pNewPlateTaskButton->setMaximumHeight(iButtonHeight*1.30);
    m_pNewPlateTaskButton->setMinimumHeight(iButtonHeight*1.30);
    pVMainLayout->addWidget(m_pNewPlateTaskButton);

    m_pCurrentTasksButton = new QPushButton("Текущие задачи");
    connect(m_pCurrentTasksButton,SIGNAL(pressed()),this,SLOT(OnCurrentTaskPressed()));
    m_pCurrentTasksButton->setMaximumHeight(iButtonHeight*1.30);
    m_pCurrentTasksButton->setMinimumHeight(iButtonHeight*1.30);
    pVMainLayout->addWidget(m_pCurrentTasksButton);

    this->setLayout(pVMainLayout);
}

void QPlatePartnerMainDlg::OnNewPlateTaskPressed()
{
    QPlatePartnerTask dlg;
    dlg.exec();
}
void QPlatePartnerMainDlg::OnCurrentTaskPressed()
{
    QPlatePartnerTasksListDlg dlg;
    dlg.exec();
}
