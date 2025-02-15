#include "qplatetaskdialog.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QDateTime>
#include <QUuid>
#include "common.h"
#include "BDPatterns.h"
#include "service_widgets/qyesnodlg.h"
#include <QMessageBox>

extern QRect screenGeometry;
extern QUuid uuidCurrentUser;
extern int iButtonHeight;
extern UserTypes CurrentUserType;
extern QColor currentWorkdayColor;

QPlateTaskDialog::QPlateTaskDialog(QWidget *parent, Qt::WindowFlags f ):QCSBaseDialog(parent , f)
{
    m_uuidSourseRecord = QUuid();

    QVBoxLayout * pVMainLayout = new QVBoxLayout;


    pVMainLayout->addSpacing(5);
    m_pTopLabel = new QLabel(QString("<b>Номера. %1</b>").arg(QDateTime::currentDateTime().toString("dd.MM.yyyy hh:mm")));
    pVMainLayout->addWidget(m_pTopLabel);

    m_pPlateLineText = new QLineText("Номер автомобиля");
    pVMainLayout->addWidget(m_pPlateLineText);

    QHBoxLayout * pHPlateCountLayout = new QHBoxLayout();

    m_pOnePlateButton = new QPushButton("1 рамка");
    m_pOnePlateButton->setCheckable(true);
    connect(m_pOnePlateButton,SIGNAL(pressed()),this,SLOT(OnOnePlatePressedSlot()));
    pHPlateCountLayout->addWidget(m_pOnePlateButton);

    m_pTwoPlateButton = new QPushButton("2 рамки");
    m_pTwoPlateButton->setCheckable(true);
    connect(m_pTwoPlateButton,SIGNAL(pressed()),this,SLOT(OnTwoPlatePressedSlot()));
    pHPlateCountLayout->addWidget(m_pTwoPlateButton);

    m_pZeroPlateButton = new QPushButton("0 рамок");
    m_pZeroPlateButton->setCheckable(true);
    connect(m_pZeroPlateButton,SIGNAL(pressed()),this,SLOT(OnZeroPlatePressedSlot()));
    pHPlateCountLayout->addWidget(m_pZeroPlateButton);

    pVMainLayout->addLayout(pHPlateCountLayout);

    m_pLineTextComment = new QLineText("Комментарий");
    pVMainLayout->addWidget(m_pLineTextComment);

    m_pLoadAutoFotoDlg = new QLoadDocsDlg;
    m_pLoadAutoFotoButton = new QPushButton("Фото автомобиля");
    connect(m_pLoadAutoFotoButton,SIGNAL(pressed()),this,SLOT(OnLoadAutoFotoButtonPressed()));
    m_pLoadAutoFotoButton->setMaximumHeight(iButtonHeight);
    m_pLoadAutoFotoButton->setMinimumHeight(iButtonHeight);
    pVMainLayout->addWidget(m_pLoadAutoFotoButton);

    pVMainLayout->addStretch();

    m_pSelProviderCarshWidget = new QSelProviderCarshWidget();
    pVMainLayout->addWidget(m_pSelProviderCarshWidget);
    connect(m_pSelProviderCarshWidget , SIGNAL(CarshChanged()) , this , SLOT(OnCarshChanged()));
    connect(m_pSelProviderCarshWidget , SIGNAL(ProviderChanged()) , this , SLOT(OnProviderChanged()));

    QPushButton * pApplyButton = new QPushButton("Внести");
    pApplyButton->setIcon(QIcon(":/icons/done_icon.png"));
    pApplyButton->setIconSize(QSize(iButtonHeight*0.75 , iButtonHeight*0.75));
    pVMainLayout->addWidget(pApplyButton);
    connect(pApplyButton,SIGNAL(released()),this,SLOT(OnApplyPressedSlot()));

    if(CurrentUserType == CarshService)
    {
        QPushButton * pRemoveButton = new QPushButton("Удалить");
        pRemoveButton->setIcon(QIcon(":/icons/remove_icon.png"));
        pRemoveButton->setIconSize(QSize(iButtonHeight*0.75 , iButtonHeight*0.75));
        pVMainLayout->addWidget(pRemoveButton);
        connect(pRemoveButton,SIGNAL(released()),this,SLOT(OnRemovePressedSlot()));
    }

    this->setLayout(pVMainLayout);
}

bool QPlateTaskDialog::isReady()
{
    bool retVal = true;



    if(m_pLoadAutoFotoDlg->m_pPicturesWidget->m_Pictures.size()<4)
    {
        //m_pLoadPhotoWidget->SetViewDone(false);
        retVal = false;
    }

    if(!m_pSelProviderCarshWidget->isReadyColored())
    {
        retVal = false;
    }

    return retVal;
}

void QPlateTaskDialog::OnProviderChanged()
{
    isReady();
}

void QPlateTaskDialog::OnLoadAutoFotoButtonPressed()
{
    m_pLoadAutoFotoDlg->exec();
    isReady();
}


void QPlateTaskDialog::OnCarshChanged()
{
    QString strExecColor = QString("select Цвет from Заказчики where id='%1'").arg(m_pSelProviderCarshWidget->m_uuidCarsh.toString());

    QList<QStringList> colorRes = execMainBDQuery(strExecColor);
    if(colorRes.size()>0)
    {
        currentWorkdayColor = colorRes.at(0).at(0).toLongLong();
        setStyleSheet(QString("QDialog , QScrollArea , QCSBaseDlgScrollWidget, QListWidget, QLabel , QCSSelectDlgButtonsWidget {background-color: rgb(%1,%2,%3)}").arg(currentWorkdayColor.red()).arg(currentWorkdayColor.green()).arg(currentWorkdayColor.blue()));
    }

    isReady();
}

void QPlateTaskDialog::SaveDataToBD()
{
    qint64 iReadyTime=0;

    bool bIsReady = isReady();

    if(bIsReady) iReadyTime=QDateTime::currentSecsSinceEpoch();

    if(m_uuidSourseRecord == QUuid()) //Новая задача
    {
        /*Сама задача*/
        QUuid uuidTask = QUuid::createUuid();
        QUuid uuidExtention = QUuid::createUuid();

        /*Устанавливаем оплату или нет в зависимости от завершённости задачи*/
        QString strSumm;

        if(bIsReady)
        {
            strSumm = " (select Цена from \"Типы задач\" where id='99b4e860-5a7b-42a4-9136-f96252ef4192') ";
        }
        else
        {
            strSumm = "0";
        }

        QString strExec = QString("insert into \"Задачи\" (id,\"Дата Время\",\"Тип\",Комментарий, Расширение , Исполнитель , \"Время выполнения\", Поставщик , Заказчик , Цена) values ('%1','%2','99b4e860-5a7b-42a4-9136-f96252ef4192','%3','%4','%5','%6','%7','%8',%9)").arg(uuidTask.toString()).arg(QDateTime::currentSecsSinceEpoch()).arg(m_pLineTextComment->getText()).arg(uuidExtention.toString()).arg(uuidCurrentUser.toString()).arg(iReadyTime).arg(m_pSelProviderCarshWidget->m_uuidProvider.toString()).arg(m_pSelProviderCarshWidget->m_uuidCarsh.toString()).arg(strSumm);
        execMainBDQueryUpdate(strExec);

        /*Расширение (номер, количество рамок)*/
        int iPlateCount = 0;
        if (m_pOnePlateButton->isChecked()) iPlateCount = 1;
        if (m_pTwoPlateButton->isChecked()) iPlateCount = 2;
        strExec = QString("insert into \"Расширение задачи Номера\" (id ,  \"Количество рамок\" , \"Госномер\") values ('%1' , '%2' , '%3')").arg(uuidExtention.toString()).arg(iPlateCount).arg(m_pPlateLineText->getText());
        execMainBDQueryUpdate(strExec);

        /*Фото/документы*/
        /*Перебрать и записать картинки*/
        for (int iPicCounter = 0; iPicCounter < m_pLoadAutoFotoDlg->m_pPicturesWidget->m_Pictures.size(); ++iPicCounter)
        {
            QUuid uuidDocument = QUuid::createUuid();
            QString strExec = QString("insert into \"Документы\" (id,\"Изображение\",\"Тип\") values ('%1','%2','94ec977e-0be0-4dd7-b1fc-682af124e0ac')").arg(uuidDocument.toString()).arg(ImageToBase64(m_pLoadAutoFotoDlg->m_pPicturesWidget->m_Pictures.at(iPicCounter)));
            execMainBDQueryUpdate(strExec);

            QUuid uuidDocTask = QUuid::createUuid();
            strExec = QString("insert into \"Задача-Документы задач\" (id,\"Задача\",\"Документ\") values ('%1','%2','%3')").arg(uuidDocTask.toString()).arg(uuidTask.toString()).arg(uuidDocument.toString());
            execMainBDQueryUpdate(strExec);
        }
    }
    else //Апдейтим загруженную задачу
    {
        /*Устанавливаем оплату или нет в зависимости от завершённости задачи*/
        QString strSumm;

        if(bIsReady)
        {
            strSumm = " (select Цена from \"Типы задач\" where id='99b4e860-5a7b-42a4-9136-f96252ef4192') ";
        }
        else
        {
            strSumm = "0";
        }


        QString strExec = QString("update \"Задачи\" set Цена = %1  where id='%2'").arg(strSumm).arg(m_uuidSourseRecord.toString());
        execMainBDQueryUpdate(strExec);

        strExec = QString("update \"Задачи\" set Поставщик = '%1'  where id='%2'").arg(m_pSelProviderCarshWidget->m_uuidProvider.toString()).arg(m_uuidSourseRecord.toString());
        execMainBDQueryUpdate(strExec);

        strExec = QString("update \"Задачи\" set Заказчик = '%1'  where id='%2'").arg(m_pSelProviderCarshWidget->m_uuidCarsh.toString()).arg(m_uuidSourseRecord.toString());
        execMainBDQueryUpdate(strExec);

        strExec = QString("update \"Задачи\" set Комментарий = '%1' , \"Время выполнения\"='%2' where id='%3'").arg(m_pLineTextComment->getText()).arg(iReadyTime).arg(m_uuidSourseRecord.toString());
        execMainBDQueryUpdate(strExec);

        /*Расширение (номер, количество рамок)*/
        int iPlateCount = 0;
        if (m_pOnePlateButton->isChecked()) iPlateCount = 1;
        if (m_pTwoPlateButton->isChecked()) iPlateCount = 2;

        strExec = QString("update \"Расширение задачи Номера\" set \"Количество рамок\"='%1' , \"Госномер\"='%2' where id='%3'").arg(iPlateCount).arg(m_pPlateLineText->getText()).arg(m_uuidSourseExtention.toString());
        execMainBDQueryUpdate(strExec);

        /*Фото/документы*/
        RemoveTaskDocs(m_uuidSourseRecord);

        /*Затем перебрать и записать картинки*/
        for (int iPicCounter = 0; iPicCounter < m_pLoadAutoFotoDlg->m_pPicturesWidget->m_Pictures.size(); ++iPicCounter)
        {
            CreateTaskDocRecord(m_uuidSourseRecord , ImageToBase64(m_pLoadAutoFotoDlg->m_pPicturesWidget->m_Pictures.at(iPicCounter)));
        }
    }
}

void QPlateTaskDialog::LoadDataFromBD(QUuid uuidSourseRecord)
{
    m_uuidSourseRecord=uuidSourseRecord;

    QString strExec = QString("select \"Дата Время\",\"Тип\",Комментарий, Расширение, Поставщик, Заказчик from \"Задачи\"  where id='%1'").arg(uuidSourseRecord.toString());

    QList<QStringList> resTasks = execMainBDQuery(strExec);
    for(int iTasksCounter = 0 ; iTasksCounter < resTasks.size() ; iTasksCounter++)
    {
        m_pTopLabel->setText(QString("<b>Номера. %1</b>").arg(QDateTime::fromSecsSinceEpoch(resTasks.at(iTasksCounter).at(0).toInt()).toString("dd.MM.yyyy hh:mm")));
        m_pLineTextComment->setText(resTasks.at(iTasksCounter).at(2));

        m_pSelProviderCarshWidget->m_uuidProvider = QUuid::fromString(resTasks.at(iTasksCounter).at(4));
        m_pSelProviderCarshWidget->m_uuidCarsh = QUuid::fromString(resTasks.at(iTasksCounter).at(5));
        OnCarshChanged();//Для раскраски при открытии задачи

        /*Загрузка расширения задачи*/
        m_uuidSourseExtention = QUuid::fromString(resTasks.at(iTasksCounter).at(3));
        QString strExtenExec = QString("select \"Количество рамок\" , \"Госномер\" from \"Расширение задачи Номера\" where id='%1'").arg(m_uuidSourseExtention.toString());
        QList<QStringList> resExtTasks = execMainBDQuery(strExtenExec);
        for(int iExtTasksCounter = 0 ; iExtTasksCounter < resExtTasks.size() ; iExtTasksCounter++)
        {
            int iPlateCount = resExtTasks.at(iTasksCounter).at(0).toInt();

            if(iPlateCount == 0)
            {
                m_pZeroPlateButton->setChecked(true);
                OnZeroPlatePressedSlot();
            }
            if(iPlateCount == 1)
            {
                m_pOnePlateButton->setChecked(true);
                OnOnePlatePressedSlot();
            }
            if(iPlateCount == 2)
            {
                m_pTwoPlateButton->setChecked(true);
                OnTwoPlatePressedSlot();
            }

            m_pPlateLineText->setText(resExtTasks.at(iTasksCounter).at(1));
        }

        /*Загрузка картинок задачи*/
        QString strPicExec=QString("select \"Документы\".\"Изображение\" from \"Документы\", \"Задача-Документы задач\", Задачи where Документы.id = \"Задача-Документы задач\".Документ and Задачи.id = \"Задача-Документы задач\".Задача and Задачи.id ='%1'").arg(uuidSourseRecord.toString());
        QList<QStringList> resPicTasks = execMainBDQuery(strPicExec);
        for(int iPicTasksCounter = 0 ; iPicTasksCounter < resPicTasks.size() ; iPicTasksCounter++)
        {
            QString tmpStr = resPicTasks.at(iPicTasksCounter).at(0);
            QImage tmpImg = Base64ToImage(tmpStr);
            m_pLoadAutoFotoDlg->m_pPicturesWidget->AddImage(tmpImg);
        }
    }
    isReady();
}


void QPlateTaskDialog::OnApplyPressedSlot()
{
    isReady();

    if((m_pSelProviderCarshWidget->m_uuidCarsh==QUuid()) or (m_pSelProviderCarshWidget->m_uuidProvider==QUuid()))
    {
        QMessageBox::information(this , "КаршСервис" , "Укажите поставщика и заказчика");

        return;
    }
    SaveDataToBD();
    accept();
}

void QPlateTaskDialog::OnOnePlatePressedSlot()
{
    m_pTwoPlateButton->setChecked(false);
    m_pZeroPlateButton->setChecked(false);
}
void QPlateTaskDialog::OnTwoPlatePressedSlot()
{
    m_pZeroPlateButton->setChecked(false);
    m_pOnePlateButton->setChecked(false);
}
void QPlateTaskDialog::OnZeroPlatePressedSlot()
{
    m_pOnePlateButton->setChecked(false);
    m_pTwoPlateButton->setChecked(false);
}

void QPlateTaskDialog::OnRemovePressedSlot()
{
    QYesNoDlg dlg("Удалить задачу?");
    if(dlg.exec() == QDialog::Accepted)
    {
        QString strExec = QString("update \"Задачи\" set Удалено = 'true' where id='%1'").arg(m_uuidSourseRecord.toString());
        execMainBDQueryUpdate(strExec);
        accept();
    }
}
