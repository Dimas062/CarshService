#include "qWashpartnertask.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QDateTime>
#include "service_widgets/qcalendardataselectdlg.h"
#include "service_widgets/qcsselectdialog.h"
#include "common.h"
#include "BDPatterns.h"

extern QRect screenGeometry;
extern QUuid uuidCurrentPartner;
extern int iButtonHeight;

QWashPartnerTask::QWashPartnerTask(QWidget *parent, Qt::WindowFlags f ):QCSBaseDialog(parent , f)
{
    m_uuidSourseRecord = QUuid();

    QVBoxLayout * pVMainLayout = new QVBoxLayout;

    strIdPoint = QString(" ");
    m_selDate = QDate::currentDate();


    pVMainLayout->addSpacing(5);
    m_pTopLabel = new QLabel(QString("<b>Мойка. %1</b>").arg(QDateTime::currentDateTime().toString("dd.MM.yyyy hh:mm")));
    pVMainLayout->addWidget(m_pTopLabel);

    m_pSubtaskButton = new QPushButton("Работы");
    m_pSubtaskButton->setIconSize(QSize(iButtonHeight*0.75 , iButtonHeight*0.75));
    pVMainLayout->addWidget(m_pSubtaskButton);
    connect(m_pSubtaskButton,SIGNAL(released()),this,SLOT(OnSubtaskPressedSlot()));

    m_pCommentLineText = new QLineText("Комментарий:");
    pVMainLayout->addWidget(m_pCommentLineText);



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

    m_pLoadVedomostDlg = new QLoadDocsDlg;
    m_pLoadVedomostButton = new QPushButton("Фото ведомости");
    connect(m_pLoadVedomostButton,SIGNAL(released()),this,SLOT(OnLoadVedomostButtonPressed()));
    m_pLoadVedomostButton->setFixedHeight(iButtonHeight);
    m_pLoadVedomostButton->setFixedHeight(iButtonHeight);
    pVMainLayout->addWidget(m_pLoadVedomostButton, 0 , Qt::AlignHCenter);

    QPushButton * pApplyButton = new QPushButton("Внести");
    pApplyButton->setIcon(QIcon(":/icons/done_icon.png"));
    pApplyButton->setIconSize(QSize(iButtonHeight*0.75 , iButtonHeight*0.75));
    pVMainLayout->addWidget(pApplyButton);
    connect(pApplyButton,SIGNAL(released()),this,SLOT(OnApplyPressedSlot()));

    this->setLayout(pVMainLayout);
}

void QWashPartnerTask::OnApplyPressedSlot()
{
    if(!isReady()) return;

    SaveDataToBD();
    accept();
}

void QWashPartnerTask::OnLoadVedomostButtonPressed()
{
    m_pLoadVedomostDlg->exec();
    isReady();
}


bool QWashPartnerTask::isReady()
{
    bool retVal = true;

    if(strIdPoint.length()<10)
    {
        m_pPointButton->setStyleSheet("QPushButton {color: red;}");
        retVal = false;
    }
    else m_pPointButton->setStyleSheet("QPushButton {color: black;}");

    // if(m_vstrIdSubtasks.size()<1)
    // {
    //     m_pSubtaskButton->setStyleSheet("QPushButton {color: red;}");
    //     retVal = false;
    // }
   // else m_pSubtaskButton->setStyleSheet("QPushButton {color: black;}");

    if(m_pLoadVedomostDlg->m_pPicturesWidget->m_Pictures.size()<2)
    {
        m_pLoadVedomostButton->setStyleSheet("QPushButton {color: red;}");
        retVal = false;
    }
    else m_pLoadVedomostButton->setStyleSheet("QPushButton {color: black;}");

    return retVal;
}

void QWashPartnerTask::OnToCalendatButtonPressed()
{
    QCalendarDataSelectDlg calendarDlg(QDateTime::currentDateTime().date());
    if(calendarDlg.exec()==QDialog::Accepted)
    {
        m_selDate = calendarDlg.m_SelectedDate;
        m_pCalendarLabel->setText(QString("Дата: %1").arg(m_selDate.toString("dd.MM.yyyy")));
    }
}


void QWashPartnerTask::SaveDataToBD()
{
    if(m_uuidSourseRecord == QUuid()) //Новая задача
    {
        /*Сама задача*/
        QUuid uuidTask = QUuid::createUuid();

        QString strExec = QString("insert into \"Задачи партнера Мойка\" (id, Партнер, ДатаВремя, Точка, \"Время выполнения\" , Комментарий) values ('%1','%2','%3','%4','%5','%6')").arg(uuidTask.toString()).arg(uuidCurrentPartner.toString()).arg(QDateTime::currentDateTime().toSecsSinceEpoch()).arg(strIdPoint).arg(QDateTime(m_selDate, QTime(0,0,1)).toSecsSinceEpoch()).arg(m_pCommentLineText->getText());
        execMainBDQueryUpdate(strExec);

        /*Работы*/
        foreach(WashTypeDatas data , m_vWashDatas)
        {

            if(data.isSelected)
            {
                if(data.iDay>0)
                {
                    QUuid uuidTaskType = QUuid::createUuid();
                    QString strExecTypes = QString("insert into \"Задача Мойка - Типы\" (id, Задача, Тип , Ночь, Количество) values ('%1' , '%2' , '%3' , '%4' , '%5')").arg(uuidTaskType.toString()).arg(uuidTask.toString()).arg(data.id.toString()).arg("false").arg(data.iDay);
                    execMainBDQueryUpdate(strExecTypes);
                }
                if(data.iNigth>0)
                {
                    QUuid uuidTaskType = QUuid::createUuid();
                    QString strExecTypes = QString("insert into \"Задача Мойка - Типы\" (id, Задача, Тип , Ночь, Количество) values ('%1' , '%2' , '%3' , '%4' , '%5')").arg(uuidTaskType.toString()).arg(uuidTask.toString()).arg(data.id.toString()).arg("true").arg(data.iDay);
                    execMainBDQueryUpdate(strExecTypes);
                }
            }
        }

        /*Фото ведомости*/
        /*Перебрать и записать картинки*/
        for (int iPicCounter = 0; iPicCounter < m_pLoadVedomostDlg->m_pPicturesWidget->m_Pictures.size(); ++iPicCounter)
        {
            CreateTaskDocRecord(uuidTask , ImageToBase64(m_pLoadVedomostDlg->m_pPicturesWidget->m_Pictures.at(iPicCounter)));
        }
    }
    else//Апдейтим загруженную задачу
    {
        QString strExec = QString("update \"Задачи партнера Мойка\" set Точка = '%1'  where id='%2'").arg(strIdPoint).arg(m_uuidSourseRecord.toString());
        execMainBDQueryUpdate(strExec);

        strExec = QString("update \"Задачи партнера Мойка\" set \"Время выполнения\" = '%1'  where id='%2'").arg(QDateTime(m_selDate, QTime(0,0,1)).toSecsSinceEpoch()).arg(m_uuidSourseRecord.toString());
        execMainBDQueryUpdate(strExec);

        strExec = QString("update \"Задачи партнера Мойка\" set Комментарий = '%1'  where id='%2'").arg(m_pCommentLineText->getText()).arg(m_uuidSourseRecord.toString());
        execMainBDQueryUpdate(strExec);

        strExec = QString("update \"Задачи партнера Мойка\" set Партнер = '%1'  where id='%2'").arg(uuidCurrentPartner.toString()).arg(m_uuidSourseRecord.toString());
        execMainBDQueryUpdate(strExec);

        /*Работы*/
        /*Удалим старые работы*/
        strExec = QString("delete from \"Задача Мойка - Типы\" where Задача= '%1'").arg(m_uuidSourseRecord.toString());
        execMainBDQueryUpdate(strExec);

        /*Работы*/
        foreach(WashTypeDatas data , m_vWashDatas)
        {

            if(data.isSelected)
            {
                if(data.iDay>0)
                {
                    QUuid uuidTaskType = QUuid::createUuid();
                    QString strExecTypes = QString("insert into \"Задача Мойка - Типы\" (id, Задача, Тип , Ночь, Количество) values ('%1' , '%2' , '%3' , '%4' , '%5')").arg(uuidTaskType.toString()).arg(m_uuidSourseRecord.toString()).arg(data.id.toString()).arg("false").arg(data.iDay);
                    execMainBDQueryUpdate(strExecTypes);
                }
                if(data.iNigth>0)
                {
                    QUuid uuidTaskType = QUuid::createUuid();
                    QString strExecTypes = QString("insert into \"Задача Мойка - Типы\" (id, Задача, Тип , Ночь, Количество) values ('%1' , '%2' , '%3' , '%4' , '%5')").arg(uuidTaskType.toString()).arg(m_uuidSourseRecord.toString()).arg(data.id.toString()).arg("true").arg(data.iDay);
                    execMainBDQueryUpdate(strExecTypes);
                }
            }
        }

        /*Фото/документы*/
        /*Сначала удалим все старые*/
        RemoveTaskDocs(m_uuidSourseRecord);

        /*Затем перебрать и записать картинки*/
        for (int iPicCounter = 0; iPicCounter < m_pLoadVedomostDlg->m_pPicturesWidget->m_Pictures.size(); ++iPicCounter)
        {
            CreateTaskDocRecord(m_uuidSourseRecord , ImageToBase64(m_pLoadVedomostDlg->m_pPicturesWidget->m_Pictures.at(iPicCounter)));
        }
    }
}

void QWashPartnerTask::LoadDataFromBD(QUuid taskUuid)
{
    m_uuidSourseRecord=taskUuid;

    QString strExec = QString("select ДатаВремя, Точка, \"Время выполнения\" , Комментарий , Партнер from \"Задачи партнера Мойка\"  where id='%1'").arg(m_uuidSourseRecord.toString());

    QList<QStringList> resTasks = execMainBDQuery(strExec);
    for(int iTasksCounter = 0 ; iTasksCounter < resTasks.size() ; iTasksCounter++)
    {
        m_pTopLabel->setText(QString("<b>Оклейка. %1</b>").arg(QDateTime::fromSecsSinceEpoch(resTasks.at(iTasksCounter).at(0).toInt()).toString("dd.MM.yyyy hh:mm")));

        strIdPoint = resTasks.at(iTasksCounter).at(1);

        m_selDate = QDateTime::fromSecsSinceEpoch(resTasks.at(iTasksCounter).at(2).toInt()).date();
        m_pCalendarLabel->setText(QString("Дата: %1").arg(m_selDate.toString("dd.MM.yyyy")));

        m_pCommentLineText->setText(resTasks.at(iTasksCounter).at(3));

        /*Загружаем типы выполненных работ*/
        /*Сначала получим массив всех возможных типов (возможно заполненных старыми значениями из диалога, но они будут все в массиве*/
        m_vWashDatas = m_WashTypeSelectDlg.selectWidget.GetData();

        /*После занулим все (отметим не выбранными), что бы читая построчно из БД отмечать только те, что есть в БД*/
        for(int iDatasCounter = 0 ; iDatasCounter < m_vWashDatas.count() ; iDatasCounter++)
        {
            m_vWashDatas[iDatasCounter].isSelected=false;
            m_vWashDatas[iDatasCounter].iDay = 0;
            m_vWashDatas[iDatasCounter].iNigth = 0;
        }

         QString strTypesExec=QString("select Тип , Ночь, Количество from \"Задача Мойка - Типы\" where Задача = '%1'").arg(m_uuidSourseRecord.toString());
         QList<QStringList> resTypes = execMainBDQuery(strTypesExec);
         foreach(QStringList res , resTypes)
         {
             for(int iDatasCounter = 0 ; iDatasCounter < m_vWashDatas.count() ; iDatasCounter++)
             {
                 if(m_vWashDatas[iDatasCounter].id == QUuid::fromString(res.at(0)))
                 {
                     m_vWashDatas[iDatasCounter].isSelected=true;
                     if(res.at(1) == 't')
                         m_vWashDatas[iDatasCounter].iNigth = res.at(2).toInt();
                     else
                         m_vWashDatas[iDatasCounter].iDay = res.at(2).toInt();
                 }
             }
         }


        /*Загрузка картинок задачи*/
        QString strPicExec=QString("select \"Документы\".\"Изображение\" , \"Документы\".Тип from \"Документы\", \"Задача-Документы задач\", \"Задачи партнера Мойка\" where Документы.id = \"Задача-Документы задач\".Документ and \"Задачи партнера Мойка\".id = \"Задача-Документы задач\".Задача and \"Задачи партнера Мойка\".id ='%1'").arg(m_uuidSourseRecord.toString());
        QList<QStringList> resPicTasks = execMainBDQuery(strPicExec);
        qDebug()<<"strPicExec = "<<strPicExec;

        for(int iPicTasksCounter = 0 ; iPicTasksCounter < resPicTasks.size() ; iPicTasksCounter++)
        {
            if(QUuid(resPicTasks.at(iPicTasksCounter).at(1)) == QUuid("94ec977e-0be0-4dd7-b1fc-682af124e0ac"))
            {
                QString tmpStr = resPicTasks.at(iPicTasksCounter).at(0);
                QImage tmpImg = Base64ToImage(tmpStr);
                m_pLoadVedomostDlg->m_pPicturesWidget->AddImage(tmpImg);
            }
        }
    }

    isReady();
}


void QWashPartnerTask::OnPointPressedSlot()
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

void QWashPartnerTask::OnSubtaskPressedSlot()
{
    m_WashTypeSelectDlg.selectWidget.SetData(m_vWashDatas);
    if(m_WashTypeSelectDlg.exec()==QDialog::Accepted)
    {
        m_vWashDatas = m_WashTypeSelectDlg.selectWidget.GetData();
        isReady();
    }
}
