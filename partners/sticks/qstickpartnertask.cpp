#include "qStickpartnertask.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QDateTime>
#include "service_widgets/qcsselectdialog.h"
#include "service_widgets/qcalendardataselectdlg.h"
#include "common.h"
#include "BDPatterns.h"

extern QRect screenGeometry;
extern QUuid uuidCurrentPartner;
extern int iButtonHeight;
extern QColor currentWorkdayColor;

QStickPartnerTask::QStickPartnerTask(QWidget *parent, Qt::WindowFlags f ):QCSBaseDialog(parent , f)
{
    m_uuidSourseRecord = QUuid();

    QVBoxLayout * pVMainLayout = new QVBoxLayout;

    strIdPoint = QString(" ");
    m_selDate = QDate::currentDate();


    pVMainLayout->addSpacing(5);
    m_pTopLabel = new QLabel(QString("<b>Оклейка. %1</b>").arg(QDateTime::currentDateTime().toString("dd.MM.yyyy hh:mm")));
    pVMainLayout->addWidget(m_pTopLabel);

    m_pSubtaskButton = new QPushButton("Работы");
    m_pSubtaskButton->setIconSize(QSize(iButtonHeight*0.75 , iButtonHeight*0.75));
    pVMainLayout->addWidget(m_pSubtaskButton);
    connect(m_pSubtaskButton,SIGNAL(released()),this,SLOT(OnSubtaskPressedSlot()));

    m_pCommentLineText = new QLineText("Комментарий:");
    pVMainLayout->addWidget(m_pCommentLineText);

    m_pNumberLineText = new QLineText("Гос. номер:");
    pVMainLayout->addWidget(m_pNumberLineText);

    QHBoxLayout * pHCalendarLayout = new QHBoxLayout;

    m_pCalendarLabel = new QLabel(QString("Дата: %1").arg(m_selDate.toString("dd.MM.yyyy")));
    pHCalendarLayout->addWidget(m_pCalendarLabel);

    m_pToCalendarButton = new QPushButton("");
    m_pToCalendarButton->setIcon(QIcon(":/icons/to_calendar_icon_256.png"));
    m_pToCalendarButton->setIconSize(QSize(iButtonHeight*0.75 , iButtonHeight*0.75));
    connect(m_pToCalendarButton,SIGNAL(pressed()),this,SLOT(OnToCalendatButtonPressed()));
    m_pToCalendarButton->setFixedHeight(iButtonHeight);
    m_pToCalendarButton->setFixedWidth(iButtonHeight);
    pHCalendarLayout->addWidget(m_pToCalendarButton);
    pVMainLayout->addLayout(pHCalendarLayout);

    m_pPointButton = new QPushButton("Точка");
    m_pPointButton->setIconSize(QSize(iButtonHeight*0.75 , iButtonHeight*0.75));
    pVMainLayout->addWidget(m_pPointButton);
    connect(m_pPointButton,SIGNAL(released()),this,SLOT(OnPointPressedSlot()));

    m_pLoadAutoFotoDlg = new QLoadDocsDlg;
    m_pLoadAutoFotoButton = new QPushButton("Фото автомобиля");
    connect(m_pLoadAutoFotoButton,SIGNAL(released()),this,SLOT(OnLoadAutoFotoButtonPressed()));
    m_pLoadAutoFotoButton->setFixedHeight(iButtonHeight);
    m_pLoadAutoFotoButton->setFixedHeight(iButtonHeight);
    pVMainLayout->addWidget(m_pLoadAutoFotoButton, 0 , Qt::AlignHCenter);

    m_pSelProviderCarshWidget = new QSelProviderCarshWidget();
    pVMainLayout->addWidget(m_pSelProviderCarshWidget);
    connect(m_pSelProviderCarshWidget , SIGNAL(CarshChanged()) , this , SLOT(OnCarshChanged()));

    QPushButton * pApplyButton = new QPushButton("Внести");
    pApplyButton->setIcon(QIcon(":/icons/done_icon.png"));
    pApplyButton->setIconSize(QSize(iButtonHeight*0.75 , iButtonHeight*0.75));
    pVMainLayout->addWidget(pApplyButton);
    connect(pApplyButton,SIGNAL(released()),this,SLOT(OnApplyPressedSlot()));

    this->setLayout(pVMainLayout);
}

void QStickPartnerTask::OnApplyPressedSlot()
{
    if(!isReady()) return;
    showWait(true);
    SaveDataToBD();
    showWait(false);
    accept();
}

void QStickPartnerTask::OnLoadAutoFotoButtonPressed()
{
    m_pLoadAutoFotoDlg->exec();
    isReady();
}


bool QStickPartnerTask::isReady()
{
    bool retVal = true;

    if(!m_pNumberLineText->CheckColorLenght()) retVal = false;

    if(strIdPoint.length()<10)
    {
        m_pPointButton->setStyleSheet("QPushButton {color: red;}");
        retVal = false;
    }
    else m_pPointButton->setStyleSheet("QPushButton {color: black;}");

    if(m_vstrIdSubtasks.size()<1)
    {
        m_pSubtaskButton->setStyleSheet("QPushButton {color: red;}");
        retVal = false;
    }
    else m_pSubtaskButton->setStyleSheet("QPushButton {color: black;}");

    if(m_pLoadAutoFotoDlg->m_pPicturesWidget->m_Pictures.size()<2)
    {
        m_pLoadAutoFotoButton->setStyleSheet("QPushButton {color: red;}");
        retVal = false;
    }
    else m_pLoadAutoFotoButton->setStyleSheet("QPushButton {color: black;}");

    if(!m_pSelProviderCarshWidget->isReadyColored())
    {
        retVal = false;
    }

    return retVal;
}

void QStickPartnerTask::OnToCalendatButtonPressed()
{
    QCalendarDataSelectDlg calendarDlg(QDateTime::currentDateTime().date());
    if(calendarDlg.exec()==QDialog::Accepted)
    {
        m_selDate = calendarDlg.m_SelectedDate;
        m_pCalendarLabel->setText(QString("Дата: %1").arg(m_selDate.toString("dd.MM.yyyy")));
    }
}


void QStickPartnerTask::SaveDataToBD()
{
    if(m_uuidSourseRecord == QUuid()) //Новая задача
    {
        /*Сама задача*/
        QUuid uuidTask = QUuid::createUuid();

        QString strExec = QString("insert into \"Задачи партнера Оклейка\" (id, Партнер, ДатаВремя, Точка, \"Время выполнения\" , Комментарий , Номер , Заказчик) values ('%1','%2','%3','%4','%5','%6','%7','%8')").arg(uuidTask.toString()).arg(uuidCurrentPartner.toString()).arg(QDateTime::currentDateTime().toSecsSinceEpoch()).arg(strIdPoint).arg(QDateTime(m_selDate, QTime(0,0,1)).toSecsSinceEpoch()).arg(m_pCommentLineText->getText()).arg(m_pNumberLineText->getText()).arg(m_pSelProviderCarshWidget->m_uuidCarsh.toString());
        execMainBDQueryUpdate(strExec);

        /*Работы*/
        foreach(QString idSubtask , m_vstrIdSubtasks)
        {
            QUuid uuidTaskType = QUuid::createUuid();
            QString strExecTypes = QString("insert into \"Задача Оклейка - Типы\" (id, Задача, Тип) values ('%1' , '%2' , '%3' )").arg(uuidTaskType.toString()).arg(uuidTask.toString()).arg(idSubtask);
            execMainBDQueryUpdate(strExecTypes);
        }

        /*Фото машины*/
        /*Перебрать и записать картинки*/
        for (int iPicCounter = 0; iPicCounter < m_pLoadAutoFotoDlg->m_pPicturesWidget->m_Pictures.size(); ++iPicCounter)
        {
            CreateTaskDocRecord(uuidTask , ImageToBase64(m_pLoadAutoFotoDlg->m_pPicturesWidget->m_Pictures.at(iPicCounter)));
        }
    }
    else//Апдейтим загруженную задачу
    {
        QString strExec = QString("update \"Задачи партнера Оклейка\" set Точка = '%1'  where id='%2'").arg(strIdPoint).arg(m_uuidSourseRecord.toString());
        execMainBDQueryUpdate(strExec);

        strExec = QString("update \"Задачи партнера Оклейка\" set Номер = '%1'  where id='%2'").arg(m_pNumberLineText->getText()).arg(m_uuidSourseRecord.toString());
        execMainBDQueryUpdate(strExec);

        strExec = QString("update \"Задачи партнера Оклейка\" set \"Время выполнения\" = '%1'  where id='%2'").arg(QDateTime(m_selDate, QTime(0,0,1)).toSecsSinceEpoch()).arg(m_uuidSourseRecord.toString());
        execMainBDQueryUpdate(strExec);

        strExec = QString("update \"Задачи партнера Оклейка\" set Комментарий = '%1'  where id='%2'").arg(m_pCommentLineText->getText()).arg(m_uuidSourseRecord.toString());
        execMainBDQueryUpdate(strExec);

        strExec = QString("update \"Задачи партнера Оклейка\" set Партнер = '%1'  where id='%2'").arg(uuidCurrentPartner.toString()).arg(m_uuidSourseRecord.toString());
        execMainBDQueryUpdate(strExec);

        strExec = QString("update \"Задачи партнера Оклейка\" set Заказчик = '%1'  where id='%2'").arg(m_pSelProviderCarshWidget->m_uuidCarsh.toString()).arg(m_uuidSourseRecord.toString());
        execMainBDQueryUpdate(strExec);

        /*Работы*/
        /*Удалим старые работы*/
        strExec = QString("delete from \"Задача Оклейка - Типы\" where Задача= '%1'").arg(m_uuidSourseRecord.toString());
        execMainBDQueryUpdate(strExec);

        /*Новые работы*/
        foreach(QString idSubtask , m_vstrIdSubtasks)
        {
            QUuid uuidTaskType = QUuid::createUuid();
            QString strExecTypes = QString("insert into \"Задача Оклейка - Типы\" (id, Задача, Тип) values ('%1' , '%2' , '%3' )").arg(uuidTaskType.toString()).arg(m_uuidSourseRecord.toString()).arg(idSubtask);
            execMainBDQueryUpdate(strExecTypes);
        }

        /*Фото/документы*/
        /*Сначала удалим все старые (включая акт-протокол)*/
        RemoveTaskDocs(m_uuidSourseRecord);

        /*Затем перебрать и записать картинки*/
        for (int iPicCounter = 0; iPicCounter < m_pLoadAutoFotoDlg->m_pPicturesWidget->m_Pictures.size(); ++iPicCounter)
        {
            CreateTaskDocRecord(m_uuidSourseRecord , ImageToBase64(m_pLoadAutoFotoDlg->m_pPicturesWidget->m_Pictures.at(iPicCounter)));
        }
    }
}

void QStickPartnerTask::LoadDataFromBD(QUuid taskUuid)
{
    m_uuidSourseRecord=taskUuid;

    QString strExec = QString("select ДатаВремя, Точка, Номер , \"Время выполнения\" , Комментарий , Заказчик from \"Задачи партнера Оклейка\"  where id='%1'").arg(m_uuidSourseRecord.toString());

    QList<QStringList> resTasks = execMainBDQuery(strExec);
    for(int iTasksCounter = 0 ; iTasksCounter < resTasks.size() ; iTasksCounter++)
    {
        m_pTopLabel->setText(QString("<b>Оклейка. %1</b>").arg(QDateTime::fromSecsSinceEpoch(resTasks.at(iTasksCounter).at(0).toInt()).toString("dd.MM.yyyy hh:mm")));

        strIdPoint = resTasks.at(iTasksCounter).at(1);

        m_pNumberLineText->setText(resTasks.at(iTasksCounter).at(2));

        m_selDate = QDateTime::fromSecsSinceEpoch(resTasks.at(iTasksCounter).at(3).toInt()).date();
        m_pCalendarLabel->setText(QString("Дата: %1").arg(m_selDate.toString("dd.MM.yyyy")));

        m_pCommentLineText->setText(resTasks.at(iTasksCounter).at(4));

        m_pSelProviderCarshWidget->m_uuidCarsh = QUuid::fromString(resTasks.at(iTasksCounter).at(5));
        OnCarshChanged();//Для раскраски при открытии задачи

        /*Загружаем типы выполненных работ*/
        m_vstrIdSubtasks.clear();
        QString strTypesExec=QString("select Тип from \"Задача Оклейка - Типы\" where Задача = '%1'").arg(m_uuidSourseRecord.toString());
        QList<QStringList> resTypes = execMainBDQuery(strTypesExec);
        foreach(QStringList res , resTypes)
            m_vstrIdSubtasks.push_back(res.at(0));

        /*Загрузка картинок задачи*/
        QString strPicExec=QString("select \"Документы\".\"Изображение\" , \"Документы\".Тип from \"Документы\", \"Задача-Документы задач\", \"Задачи партнера Оклейка\" where Документы.id = \"Задача-Документы задач\".Документ and \"Задачи партнера Оклейка\".id = \"Задача-Документы задач\".Задача and \"Задачи партнера Оклейка\".id ='%1'").arg(m_uuidSourseRecord.toString());
        QList<QStringList> resPicTasks = execMainBDQuery(strPicExec);

        for(int iPicTasksCounter = 0 ; iPicTasksCounter < resPicTasks.size() ; iPicTasksCounter++)
        {
            if(QUuid(resPicTasks.at(iPicTasksCounter).at(1)) == QUuid("94ec977e-0be0-4dd7-b1fc-682af124e0ac"))
            {
                QString tmpStr = resPicTasks.at(iPicTasksCounter).at(0);
                QImage tmpImg = Base64ToImage(tmpStr);
                m_pLoadAutoFotoDlg->m_pPicturesWidget->AddImage(tmpImg);
            }
        }
    }

    isReady();
}

//По изменению заказчика только раскраска, сам заказчик запишется при сохранении
void QStickPartnerTask::OnCarshChanged()
{
    QString strExecColor = QString("select Цвет from Заказчики where id='%1'").arg(m_pSelProviderCarshWidget->m_uuidCarsh.toString());

    QList<QStringList> colorRes = execMainBDQuery(strExecColor);
    if(colorRes.size()>0)
    {
        currentWorkdayColor = colorRes.at(0).at(0).toLongLong();
        setStyleSheet(QString("QDialog , QScrollArea , QCSBaseDlgScrollWidget, QListWidget, QLabel , QCSSelectDlgButtonsWidget {background-color: rgb(%1,%2,%3)}").arg(currentWorkdayColor.red()).arg(currentWorkdayColor.green()).arg(currentWorkdayColor.blue()));
        //m_PayDlg.setStyleSheet(QString("QDialog , QScrollArea , QCSBaseDlgScrollWidget, QListWidget, QLabel , QCSSelectDlgButtonsWidget {background-color: rgb(%1,%2,%3)}").arg(currentWorkdayColor.red()).arg(currentWorkdayColor.green()).arg(currentWorkdayColor.blue()));
    }

    isReady();
}

void QStickPartnerTask::OnPointPressedSlot()
{
    QString strCondition = QString( " where Партнер='%1' and Удалено<>'true' ").arg(uuidCurrentPartner.toString());
    QCSSelectDialog dlg("Точки Партнеров" , "Название"  , true , false , QUuid() , strCondition);

    if(strIdPoint.length()>10)
        dlg.SelectId(strIdPoint);

    if(dlg.exec()==QDialog::Accepted)
    {
        strIdPoint = dlg.getCurId();
        isReady();
    }
}

void QStickPartnerTask::OnSubtaskPressedSlot()
{
    QCSSelectDialog dlg("Типы задач Оклейка" , "Тип"  , true , false , QUuid() , " " , true);
    if(m_vstrIdSubtasks.size()>0)
        dlg.SelectIds(m_vstrIdSubtasks);

    if(dlg.exec()==QDialog::Accepted)
    {
        m_vstrIdSubtasks = dlg.getCurIds();
        isReady();
    }
}
