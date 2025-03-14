#include "qemploeemaindlg.h"
#include "qemploeetasksdlg.h"
//#include "service_widgets/qcsselectdialog.h"
#include "tasks/qparkingtaskdialog.h"
#include "tasks/qpenaltyparkingdialog.h"
#include "tasks/qplatetaskdialog.h"
#include "tasks/qcostsdialog.h"
#include "tasks/qrettozonedialog.h"
#include "tasks/qsmenadlg.h"
#include "tasks/qdocstaskdlg.h"
#include "emploee_widgets/qemplsalarydlg.h"
#include "emploee_widgets/qemploeeinputtasksdlg.h"
#include "qemplcostsdlg.h"
#include <QGuiApplication>
#include <QHBoxLayout>
#include <QLabel>
#include <QVBoxLayout>
#include <QColor>
#include <QRgb>
#include <QGroupBox>
#include "common.h"
#include "BDPatterns.h"

extern QRect screenGeometry;
extern QUuid uuidCurrentUser;
extern int iButtonHeight;
QUuid uuidCurrentWorkday;
QColor currentWorkdayColor;
QColor defaultBackColor;



QEmploeeMainDlg::QEmploeeMainDlg(QWidget *parent, Qt::WindowFlags f ):QCSBaseDialog(parent , f)
{
    QVBoxLayout * pVMainLayout = new QVBoxLayout;

    pVMainLayout->addSpacing(4);

    QGroupBox * pTaskButtonsGroupBox = new QGroupBox;

    QVBoxLayout * pVTaskButtonsLayout = new QVBoxLayout;

    m_pCostButton = new QPushButton("Расход");
    connect(m_pCostButton,SIGNAL(pressed()),this,SLOT(OnCostPressed()));
    m_pCostButton->setMaximumHeight(iButtonHeight*0.98);
    m_pCostButton->setMinimumHeight(iButtonHeight*0.98);
    //m_pCostButton->setIcon(IconByNumber(resTaskCounts.at(0).at(0).toInt()));
    pVTaskButtonsLayout->addWidget(m_pCostButton);

    m_pNumberPlateButton = new QPushButton("Номер");
    connect(m_pNumberPlateButton,SIGNAL(pressed()),this,SLOT(OnNumberPlateTaskPressed()));
    m_pNumberPlateButton->setMaximumHeight(iButtonHeight*0.98);
    m_pNumberPlateButton->setMinimumHeight(iButtonHeight*0.98);
    pVTaskButtonsLayout->addWidget(m_pNumberPlateButton);


    m_pParkingButton = new QPushButton("Закрытая территория");
    connect(m_pParkingButton,SIGNAL(pressed()),this,SLOT(OnParkingTaskPressed()));
    m_pParkingButton->setMaximumHeight(iButtonHeight*0.98);
    m_pParkingButton->setMinimumHeight(iButtonHeight*0.98);
    pVTaskButtonsLayout->addWidget(m_pParkingButton);


    m_pPenaltyParkingButton = new QPushButton("Штраф.стоянка");
    connect(m_pPenaltyParkingButton,SIGNAL(pressed()),this,SLOT(OnPenaltyParkingTaskPressed()));
    m_pPenaltyParkingButton->setMaximumHeight(iButtonHeight*0.98);
    m_pPenaltyParkingButton->setMinimumHeight(iButtonHeight*0.98);
    pVTaskButtonsLayout->addWidget(m_pPenaltyParkingButton);


    m_pDocsButton = new QPushButton("Документы");
    connect(m_pDocsButton,SIGNAL(pressed()),this,SLOT(OnDocsTaskPressed()));
    m_pDocsButton->setMaximumHeight(iButtonHeight*0.98);
    m_pDocsButton->setMinimumHeight(iButtonHeight*0.98);
    pVTaskButtonsLayout->addWidget(m_pDocsButton);

    m_pSmenaButton = new QPushButton("Смена");
    connect(m_pSmenaButton,SIGNAL(pressed()),this,SLOT(OnSmenaTaskPressed()));
    m_pSmenaButton->setMaximumHeight(iButtonHeight*0.98);
    m_pSmenaButton->setMinimumHeight(iButtonHeight*0.98);
    pVTaskButtonsLayout->addWidget(m_pSmenaButton);


    m_pReturnToZoneButton = new QPushButton("Возврат в зону");
    connect(m_pReturnToZoneButton,SIGNAL(pressed()),this,SLOT(OnReturnToZoneTaskPressed()));
    m_pReturnToZoneButton->setMaximumHeight(iButtonHeight*0.98);
    m_pReturnToZoneButton->setMinimumHeight(iButtonHeight*0.98);
    pVTaskButtonsLayout->addWidget(m_pReturnToZoneButton);

    pTaskButtonsGroupBox->setLayout(pVTaskButtonsLayout);
    pVMainLayout->addWidget(pTaskButtonsGroupBox);


    pVMainLayout->addSpacing(5);

    m_pFinButton = new QPushButton("Финансы");
    connect(m_pFinButton,SIGNAL(pressed()),this,SLOT(OnFinPressed()));
    m_pFinButton->setMaximumHeight(iButtonHeight*0.98);
    m_pFinButton->setMinimumHeight(iButtonHeight*0.98);
    pVTaskButtonsLayout->addWidget(m_pFinButton);

    QGroupBox * pReadyButtonsGroupBox = new QGroupBox;

    QVBoxLayout * pVReadyButtonsLayout = new QVBoxLayout;

    m_pCurrentTasksButton = new QPushButton("Текущие задачи");
    connect(m_pCurrentTasksButton,SIGNAL(pressed()),this,SLOT(OnCurrentTaskPressed()));
    m_pCurrentTasksButton->setMaximumHeight(iButtonHeight*0.98);
    m_pCurrentTasksButton->setMinimumHeight(iButtonHeight*0.98);
    pVReadyButtonsLayout->addWidget(m_pCurrentTasksButton);

    m_pInputTasksButton = new QPushButton("Заявки");
    connect(m_pInputTasksButton,SIGNAL(pressed()),this,SLOT(OnInputTasksPressed()));
    m_pInputTasksButton->setMaximumHeight(iButtonHeight*0.98);
    m_pInputTasksButton->setMinimumHeight(iButtonHeight*0.98);
    pVReadyButtonsLayout->addWidget(m_pInputTasksButton);

    m_pCostsButton = new QPushButton("Прошлые расходы");
    connect(m_pCostsButton,SIGNAL(pressed()),this,SLOT(OnCostsPressed()));
    m_pCostsButton->setMaximumHeight(iButtonHeight*0.98);
    m_pCostsButton->setMinimumHeight(iButtonHeight*0.98);
    pVReadyButtonsLayout->addWidget(m_pCostsButton);

    pReadyButtonsGroupBox->setLayout(pVReadyButtonsLayout);
    pVMainLayout->addWidget(pReadyButtonsGroupBox);


    this->setLayout(pVMainLayout);

    UpdateCountersIcons();

    //WorkDayStatusCheck();
}

void QEmploeeMainDlg::UpdateCountersIcons()
{
    showWait(true);
    QString strTaskCounts = QString("select \
                                    (select count(id) from Задачи where Тип='057b3b6f-2848-479b-a546-3f16cb531ffe' and Задачи.Удалено<> 'true' and \"Время выполнения\"=0 and Исполнитель = '%1'),\
                                    (select count(id) from Задачи where Тип='25695573-f5fe-43fd-93dc-76ee09e461fa' and Задачи.Удалено<> 'true' and \"Время выполнения\"=0 and Исполнитель = '%1'),\
                                    (select count(id) from Задачи where Тип='2ae68dd5-6f2e-406b-95b2-aa41a89d19c2' and Задачи.Удалено<> 'true' and \"Время выполнения\"=0 and Исполнитель = '%1'),\
                                    (select count(id) from Задачи where Тип='78850df8-814b-41c8-8977-945c085f3021' and Задачи.Удалено<> 'true' and \"Время выполнения\"=0 and Исполнитель = '%1'),\
                                    (select count(id) from Задачи where Тип='8078b7ce-e423-49ae-9ce6-17758b852b33' and Задачи.Удалено<> 'true' and \"Время выполнения\"=0 and Исполнитель = '%1'),\
                                    (select count(id) from Задачи where Тип='99b4e860-5a7b-42a4-9136-f96252ef4192' and Задачи.Удалено<> 'true' and \"Время выполнения\"=0 and Исполнитель = '%1'),\
                                    (select count(id) from Задачи where Тип='fe81daf9-a838-4bac-84aa-595e038d3a12' and Задачи.Удалено<> 'true' and \"Время выполнения\"=0 and Исполнитель = '%1'),\
                                    (select count(id) from ЗадачиЗаказчикаШС where ПереведенаВЗадачу IS NULL and ЗадачиЗаказчикаШС.Заказчик in (select Заказчик from ИсполнителиЗаказчики where ИсполнительПартнер = '%1'))\
                                    ").arg(uuidCurrentUser.toString());


    QList<QStringList> resTaskCounts = execMainBDQuery(strTaskCounts);
    if(resTaskCounts.size()<1)
    {
        if(resTaskCounts.at(0).size()<8)
        {
            QString errStr = "Ошибка запроса " + strTaskCounts + " \n результат:" + ListListToString(resTaskCounts);
            Logging(errStr,2);
            return;
        }
    }

    m_pNumberPlateButton->setIcon(IconByNumber(resTaskCounts.at(0).at(5).toInt()));
    m_pParkingButton->setIcon(IconByNumber(resTaskCounts.at(0).at(0).toInt()));
    m_pPenaltyParkingButton->setIcon(IconByNumber(resTaskCounts.at(0).at(4).toInt()));
    m_pDocsButton->setIcon(IconByNumber(resTaskCounts.at(0).at(1).toInt()));
    m_pSmenaButton->setIcon(IconByNumber(resTaskCounts.at(0).at(3).toInt()));
    m_pReturnToZoneButton->setIcon(IconByNumber(resTaskCounts.at(0).at(6).toInt()));
    m_pInputTasksButton->setIcon(IconByNumber(resTaskCounts.at(0).at(7).toInt()));
    showWait(false);
}

void QEmploeeMainDlg::OnCostPressed()
{
    showWait(true);
    QCostsDialog dlg;
    dlg.exec();
    showWait(false);
    UpdateCountersIcons();

}

void QEmploeeMainDlg::OnFinPressed()
{
    showWait(true);
    QEmplSalaryDlg dlg;
    dlg.exec();
    showWait(false);
    UpdateCountersIcons();

}


void QEmploeeMainDlg::OnCurrentTaskPressed()
{
    showWait(true);
    QEmploeeTasksDlg dlg(uuidCurrentUser);
    dlg.checkNotReadyButton();
    dlg.exec();
    currentWorkdayColor = defaultBackColor;
    showWait(false);
    UpdateCountersIcons();
}

void QEmploeeMainDlg::OnNumberPlateTaskPressed()
{
    showWait(true);
    QPlateTaskDialog dlg;
    dlg.exec();
    currentWorkdayColor = defaultBackColor;
    showWait(false);
    UpdateCountersIcons();
}

void QEmploeeMainDlg::OnParkingTaskPressed()
{
    showWait(true);
    QParkingTaskDialog dlg;
    dlg.exec();
    currentWorkdayColor = defaultBackColor;
    showWait(false);
    UpdateCountersIcons();
}

void QEmploeeMainDlg::OnPenaltyParkingTaskPressed()
{
    showWait(true);
    QPenaltyParkingDialog dlg;
    dlg.exec();
    currentWorkdayColor = defaultBackColor;
    showWait(false);
    UpdateCountersIcons();
}

void QEmploeeMainDlg::OnCostsPressed()
{
    showWait(true);
    QEmplCostsDlg dlg(uuidCurrentUser);
    dlg.exec();
    showWait(false);
    UpdateCountersIcons();
}

void QEmploeeMainDlg::OnSmenaTaskPressed()
{
    showWait(true);
    QSmenaDlg dlg;
    dlg.exec();
    showWait(false);
    UpdateCountersIcons();
}

void QEmploeeMainDlg::OnDocsTaskPressed()
{
    showWait(true);
    QDocsTaskDlg dlg;
    dlg.exec();
    showWait(false);
    UpdateCountersIcons();
}


void QEmploeeMainDlg::OnReturnToZoneTaskPressed()
{
    showWait(true);
    QRetToZoneDialog dlg;
    dlg.exec();
    showWait(false);
    UpdateCountersIcons();
}

void QEmploeeMainDlg::OnInputTasksPressed()
{
    showWait(true);
    QEmploeeInputTasksDlg dlg(uuidCurrentUser);
    if(dlg.exec() == QDialog::Accepted)
    {
        //Штрафстоянки
        if(QUuid::fromString(dlg.m_strApplyedTaskTypeUuid) == QUuid::fromString("8078b7ce-e423-49ae-9ce6-17758b852b33"))
        {

            //Создадим новую задачу
            QString strNewTaskUuid = QUuid::createUuid().toString();
            QString strNewTaskExtensionUuid = QUuid::createUuid().toString();
            QString strExec= QString("insert into Задачи (id , \"Дата Время\" , Тип , Расширение, Исполнитель, Заказчик) values ('%1' , '%2' ,'8078b7ce-e423-49ae-9ce6-17758b852b33' ,'%3' ,'%4' ,'%5')").arg(strNewTaskUuid).arg(QDateTime::currentSecsSinceEpoch()).arg(strNewTaskExtensionUuid).arg(uuidCurrentUser.toString()).arg(dlg.m_strApplyedZakazchikUuid);
            execMainBDQueryUpdate(strExec);


            QUuid uuidPay = CreatePayRecord(0 , PayTypes::Undefined);

            strExec= QString("insert into \"Расширение задачи ШС\" (id , Госномер , Штрафстоянка , \"Оплата парковки\") values ('%1' , '%2' , '%3' , '%4')").arg(strNewTaskExtensionUuid).arg(dlg.m_strApplyedNumber).arg(dlg.m_strApplyedPenParkUuid).arg(uuidPay.toString());
            execMainBDQueryUpdate(strExec);

            //Обновим заявку, установив текущего пользователя взявшим
            strExec= QString("Update ЗадачиЗаказчикаШС set ПереведенаВЗадачу='%1' where id='%2'").arg(strNewTaskUuid).arg(dlg.m_strApplyedTaskUuid);
            execMainBDQueryUpdate(strExec);

            //Заполним и откроем диалог ее редактирования
            QPenaltyParkingDialog dlg;
            dlg.LoadDataFromBD(QUuid::fromString(strNewTaskUuid));
            dlg.exec();
            currentWorkdayColor = defaultBackColor; 
        }
    }
    showWait(false);
    UpdateCountersIcons();
}
