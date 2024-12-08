#include "qemploeemaindlg.h"
#include "qemploeetasksdlg.h"
//#include "service_widgets/qcsselectdialog.h"
#include "tasks/qparkingtaskdialog.h"
#include "tasks/qpenaltyparkingdialog.h"
#include "tasks/qplatetaskdialog.h"
#include "tasks/qcostsdialog.h"
#include "tasks/qrettozonedialog.h"
#include "qemplcostsdlg.h"
#include <QGuiApplication>
#include <QHBoxLayout>
#include <QLabel>
#include <QVBoxLayout>
#include <QColor>
#include <QRgb>
#include <QMessageBox>
#include <QGroupBox>
#include "common.h"

extern QRect screenGeometry;
extern QUuid uuidCurrentUser;
extern int iButtonHeight;
QUuid uuidCurrentWorkday;
QColor currentWorkdayColor;
QColor defaultBackColor;



QEmploeeMainDlg::QEmploeeMainDlg(QWidget *parent, Qt::WindowFlags f ):QCSBaseDialog(parent , f)
{
    QVBoxLayout * pVMainLayout = new QVBoxLayout;

    pVMainLayout->addSpacing(5);

    QString strTaskCounts = QString("select \
                                    (select count(id) from Задачи where Тип='057b3b6f-2848-479b-a546-3f16cb531ffe' and \"Время выполнения\"=0 and Исполнитель = '%1'),\
                                    (select count(id) from Задачи where Тип='25695573-f5fe-43fd-93dc-76ee09e461fa' and \"Время выполнения\"=0 and Исполнитель = '%1'),\
                                    (select count(id) from Задачи where Тип='2ae68dd5-6f2e-406b-95b2-aa41a89d19c2' and \"Время выполнения\"=0 and Исполнитель = '%1'),\
                                    (select count(id) from Задачи where Тип='78850df8-814b-41c8-8977-945c085f3021' and \"Время выполнения\"=0 and Исполнитель = '%1'),\
                                    (select count(id) from Задачи where Тип='8078b7ce-e423-49ae-9ce6-17758b852b33' and \"Время выполнения\"=0 and Исполнитель = '%1'),\
                                    (select count(id) from Задачи where Тип='99b4e860-5a7b-42a4-9136-f96252ef4192' and \"Время выполнения\"=0 and Исполнитель = '%1'),\
                                    (select count(id) from Задачи where Тип='fe81daf9-a838-4bac-84aa-595e038d3a12' and \"Время выполнения\"=0 and Исполнитель = '%1')\
                                    ").arg(uuidCurrentUser.toString());


    QList<QStringList> resTaskCounts = execMainBDQuery(strTaskCounts);

    if(resTaskCounts.size()<1)
    {
        //QMessageBox::information(this , "Каршеринг сервис", "Разрыв соединения с базой данных или ошибка, попробуйте перезапустить приложение");
        return;
    }

    QGroupBox * pTaskButtonsGroupBox = new QGroupBox;

    QVBoxLayout * pVTaskButtonsLayout = new QVBoxLayout;

    m_pCostButton = new QPushButton("Расход");
    connect(m_pCostButton,SIGNAL(pressed()),this,SLOT(OnCostPressed()));
    m_pCostButton->setMaximumHeight(iButtonHeight*1.3);
    m_pCostButton->setMinimumHeight(iButtonHeight*1.3);
    //m_pCostButton->setIcon(IconByNumber(resTaskCounts.at(0).at(0).toInt()));
    pVTaskButtonsLayout->addWidget(m_pCostButton);

    m_pNumberPlateButton = new QPushButton("Номер");
    connect(m_pNumberPlateButton,SIGNAL(pressed()),this,SLOT(OnNumberPlateTaskPressed()));
    m_pNumberPlateButton->setMaximumHeight(iButtonHeight*1.3);
    m_pNumberPlateButton->setMinimumHeight(iButtonHeight*1.3);
    m_pNumberPlateButton->setIcon(IconByNumber(resTaskCounts.at(0).at(5).toInt()));
    pVTaskButtonsLayout->addWidget(m_pNumberPlateButton);


    m_pParkingButton = new QPushButton("Закрытая территория");
    connect(m_pParkingButton,SIGNAL(pressed()),this,SLOT(OnParkingTaskPressed()));
    m_pParkingButton->setMaximumHeight(iButtonHeight*1.3);
    m_pParkingButton->setMinimumHeight(iButtonHeight*1.3);
    m_pParkingButton->setIcon(IconByNumber(resTaskCounts.at(0).at(0).toInt()));
    pVTaskButtonsLayout->addWidget(m_pParkingButton);


    m_pPenaltyParkingButton = new QPushButton("Штраф.стоянка");
    connect(m_pPenaltyParkingButton,SIGNAL(pressed()),this,SLOT(OnPenaltyParkingTaskPressed()));
    m_pPenaltyParkingButton->setMaximumHeight(iButtonHeight*1.3);
    m_pPenaltyParkingButton->setMinimumHeight(iButtonHeight*1.3);
    m_pPenaltyParkingButton->setIcon(IconByNumber(resTaskCounts.at(0).at(4).toInt()));
    pVTaskButtonsLayout->addWidget(m_pPenaltyParkingButton);


    m_pDocsButton = new QPushButton("Документы");
    connect(m_pDocsButton,SIGNAL(pressed()),this,SLOT(OnDocsTaskPressed()));
    m_pDocsButton->setMaximumHeight(iButtonHeight*1.3);
    m_pDocsButton->setMinimumHeight(iButtonHeight*1.3);
    m_pDocsButton->setIcon(IconByNumber(resTaskCounts.at(0).at(1).toInt()));
    m_pDocsButton->setEnabled(false);
    pVTaskButtonsLayout->addWidget(m_pDocsButton);


    m_pReturnToZoneButton = new QPushButton("Возврат в зону");
    connect(m_pReturnToZoneButton,SIGNAL(pressed()),this,SLOT(OnReturnToZoneTaskPressed()));
    m_pReturnToZoneButton->setMaximumHeight(iButtonHeight*1.3);
    m_pReturnToZoneButton->setMinimumHeight(iButtonHeight*1.3);
    m_pReturnToZoneButton->setIcon(IconByNumber(resTaskCounts.at(0).at(6).toInt()));
    pVTaskButtonsLayout->addWidget(m_pReturnToZoneButton);

    pTaskButtonsGroupBox->setLayout(pVTaskButtonsLayout);
    pVMainLayout->addWidget(pTaskButtonsGroupBox);


    pVMainLayout->addSpacing(10);

    QGroupBox * pReadyButtonsGroupBox = new QGroupBox;

    QVBoxLayout * pVReadyButtonsLayout = new QVBoxLayout;

    m_pCurrentTasksButton = new QPushButton("Текущие задачи");
    connect(m_pCurrentTasksButton,SIGNAL(pressed()),this,SLOT(OnCurrentTaskPressed()));
    m_pCurrentTasksButton->setMaximumHeight(iButtonHeight*1.35);
    m_pCurrentTasksButton->setMinimumHeight(iButtonHeight*1.35);
    pVReadyButtonsLayout->addWidget(m_pCurrentTasksButton);

    m_pCostsButton = new QPushButton("Прошлые расходы");
    connect(m_pCostsButton,SIGNAL(pressed()),this,SLOT(OnCostsPressed()));
    m_pCostsButton->setMaximumHeight(iButtonHeight*1.35);
    m_pCostsButton->setMinimumHeight(iButtonHeight*1.35);
    pVReadyButtonsLayout->addWidget(m_pCostsButton);

    pReadyButtonsGroupBox->setLayout(pVReadyButtonsLayout);
    pVMainLayout->addWidget(pReadyButtonsGroupBox);


    this->setLayout(pVMainLayout);

    //WorkDayStatusCheck();
}

void QEmploeeMainDlg::OnCostPressed()
{
    QCostsDialog dlg;
    dlg.exec();
}


void QEmploeeMainDlg::OnCurrentTaskPressed()
{
    debug_TimeStamp("QEmploeeMainDlg::OnCurrentTaskPressed() QEmploeeTasksDlg dlg(uuidCurrentUser);");
    QEmploeeTasksDlg dlg(uuidCurrentUser);
    debug_TimeStamp("QEmploeeMainDlg::OnCurrentTaskPressed() dlg.exec();");
    dlg.exec();
    currentWorkdayColor = defaultBackColor;
}

void QEmploeeMainDlg::OnNumberPlateTaskPressed()
{
    QPlateTaskDialog dlg;
    dlg.exec();
    currentWorkdayColor = defaultBackColor;
}

void QEmploeeMainDlg::OnParkingTaskPressed()
{
    QParkingTaskDialog dlg;
    dlg.exec();
    currentWorkdayColor = defaultBackColor;
}

void QEmploeeMainDlg::OnPenaltyParkingTaskPressed()
{
    QPenaltyParkingDialog dlg;
    dlg.exec();
    currentWorkdayColor = defaultBackColor;
}

void QEmploeeMainDlg::OnCostsPressed()
{
    qDebug()<<"QEmploeeMainDlg::OnCostsPressed()";
    QEmplCostsDlg dlg(uuidCurrentUser);
    dlg.exec();
}

void QEmploeeMainDlg::OnDocsTaskPressed()
{

}

void QEmploeeMainDlg::OnWorkdayTaskPressed()
{

}

void QEmploeeMainDlg::OnReturnToZoneTaskPressed()
{
    QRetToZoneDialog dlg;
    dlg.exec();
}
