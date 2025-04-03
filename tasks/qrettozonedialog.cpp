#include "qrettozonedialog.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QDateTime>
#include <QUuid>
#include "common.h"
#include "BDPatterns.h"
#include "service_widgets/qyesnodlg.h"

extern QRect screenGeometry;
extern QUuid uuidCurrentUser;
extern int iButtonHeight;
extern UserTypes CurrentUserType;
extern QColor currentWorkdayColor;

QRetToZoneDialog::QRetToZoneDialog(QWidget *parent, Qt::WindowFlags f ):QCSBaseDialog(parent , f)
{

    m_uuidSourseRecord = QUuid();

    QVBoxLayout * pVMainLayout = new QVBoxLayout;


    pVMainLayout->addSpacing(5);
    m_pTopLabel = new QLabel(QString("<b>Возврат в зону. %1</b>").arg(QDateTime::currentDateTime().toString("dd.MM.yyyy hh:mm")));
    pVMainLayout->addWidget(m_pTopLabel);

    m_pPlateLineText = new QLineText("Гос. номер");
    pVMainLayout->addWidget(m_pPlateLineText);
    connect(m_pPlateLineText, &QLineText::textChanged, this, &QRetToZoneDialog::OnNumberTextInput);

    m_pLineTextComment = new QLineText("Комментарий");
    pVMainLayout->addWidget(m_pLineTextComment);
    connect(m_pLineTextComment, &QLineText::textChanged, this, &QRetToZoneDialog::OnCommentTextInput);

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

bool QRetToZoneDialog::isReady()
{
    bool retVal = true;

    if(!m_pPlateLineText->CheckColorLenght()) retVal = false;

    if(m_pLoadAutoFotoDlg->m_pPicturesWidget->m_Pictures.size()<4)
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

void QRetToZoneDialog::OnNumberTextInput(const QString &)
{
    isReady();
}

void QRetToZoneDialog::OnCommentTextInput(const QString &)
{
    isReady();
}


void QRetToZoneDialog::OnProviderChanged()
{
    isReady();
}

void QRetToZoneDialog::OnLoadAutoFotoButtonPressed()
{
    m_pLoadAutoFotoDlg->exec();
    isReady();
}


void QRetToZoneDialog::OnCarshChanged()
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

void QRetToZoneDialog::SaveDataToBD()
{
    qint64 iReadyTime=0;

    bool bIsReady = isReady();

    if(bIsReady) iReadyTime=QDateTime::currentSecsSinceEpoch();

    /*Устанавливаем оплату или нет в зависимости от завершённости задачи*/
    QString strSumm;

    if(bIsReady)
    {
        strSumm = " (select Цена from \"Типы задач\" where id='fe81daf9-a838-4bac-84aa-595e038d3a12') ";
    }
    else
    {
        strSumm = "0";
    }

    if(m_uuidSourseRecord == QUuid()) //Новая задача
    {
        /*Сама задача*/
        QUuid uuidTask = QUuid::createUuid();
        QUuid uuidExtention = QUuid::createUuid();



        QString strExec = QString("insert into \"Задачи\" (id,\"Дата Время\",\"Тип\",Комментарий, Расширение , Исполнитель, \"Время выполнения\" , Цена , Поставщик , Заказчик) values ('%1','%2','fe81daf9-a838-4bac-84aa-595e038d3a12','%3','%4','%5','%6',%7,'%8','%9')").arg(uuidTask.toString()).arg(QDateTime::currentSecsSinceEpoch()).arg(m_pLineTextComment->getText()).arg(uuidExtention.toString()).arg(uuidCurrentUser.toString()).arg(0).arg(0).arg(m_pSelProviderCarshWidget->m_uuidProvider.toString()).arg(m_pSelProviderCarshWidget->m_uuidCarsh.toString());
        execMainBDQueryUpdate(strExec);


        strExec = QString("insert into \"Расширение задачи Возврат в зону\" (id,\"Госномер\") values ('%1','%2')").arg(uuidExtention.toString()).arg(m_pPlateLineText->getText());
        execMainBDQueryUpdate(strExec);


        /*Фото/документы (4 шт)*/
        /*Перебрать и записать картинки*/
        for (int iPicCounter = 0; iPicCounter < m_pLoadAutoFotoDlg->m_pPicturesWidget->m_Pictures.size(); ++iPicCounter)
        {
            CreateTaskDocRecord(uuidTask , ImageToBase64(m_pLoadAutoFotoDlg->m_pPicturesWidget->m_Pictures.at(iPicCounter)));
        }

        strExec = QString("update \"Задачи\" set Цена = %1  where id='%2'").arg(strSumm).arg(uuidTask.toString());
        execMainBDQueryUpdate(strExec);

        strExec = QString("update \"Задачи\" set Комментарий = '%1' , \"Время выполнения\"='%2' where id='%3'").arg(m_pLineTextComment->getText()).arg(iReadyTime).arg(uuidTask.toString());
        execMainBDQueryUpdate(strExec);


    }
    else//Апдейтим загруженную задачу
    {
        QString strExec = QString("update \"Задачи\" set Поставщик = '%1'  where id='%2'").arg(m_pSelProviderCarshWidget->m_uuidProvider.toString()).arg(m_uuidSourseRecord.toString());
        execMainBDQueryUpdate(strExec);

        strExec = QString("update \"Задачи\" set Заказчик = '%1'  where id='%2'").arg(m_pSelProviderCarshWidget->m_uuidCarsh.toString()).arg(m_uuidSourseRecord.toString());
        execMainBDQueryUpdate(strExec);

        strExec = QString("update \"Расширение задачи Возврат в зону\" set Госномер = '%1' where id='%2')").arg(m_pPlateLineText->getText()).arg(m_uuidSourseExtention.toString());
        execMainBDQueryUpdate(strExec);


        /*Фото/документы*/
        /*Сначала удалим все старые*/
        RemoveTaskDocs(m_uuidSourseRecord);

        /*Затем перебрать и записать картинки*/
        for (int iPicCounter = 0; iPicCounter < m_pLoadAutoFotoDlg->m_pPicturesWidget->m_Pictures.size(); ++iPicCounter)
        {
            CreateTaskDocRecord(m_uuidSourseRecord , ImageToBase64(m_pLoadAutoFotoDlg->m_pPicturesWidget->m_Pictures.at(iPicCounter)));
        }

        strExec = QString("update \"Задачи\" set Цена = %1  where id='%2'").arg(strSumm).arg(m_uuidSourseRecord.toString());
        execMainBDQueryUpdate(strExec);

        strExec = QString("update \"Задачи\" set Комментарий = '%1' , \"Время выполнения\"='%2' where id='%3'").arg(m_pLineTextComment->getText()).arg(iReadyTime).arg(m_uuidSourseRecord.toString());
        execMainBDQueryUpdate(strExec);

    }

}

void QRetToZoneDialog::LoadDataFromBD(QUuid uuidSourseRecord)
{
    m_uuidSourseRecord=uuidSourseRecord;

    QString strExec = QString("select \"Дата Время\",\"Тип\",Комментарий, Расширение, Поставщик, Заказчик from \"Задачи\"  where id='%1'").arg(uuidSourseRecord.toString());


    QList<QStringList> resTasks = execMainBDQuery(strExec);
    for(int iTasksCounter = 0 ; iTasksCounter < resTasks.size() ; iTasksCounter++)
    {
        m_pTopLabel->setText(QString("<b>Возврат в зону. %1</b>").arg(QDateTime::fromSecsSinceEpoch(resTasks.at(iTasksCounter).at(0).toInt()).toString("dd.MM.yyyy hh:mm")));
        m_pLineTextComment->setText(resTasks.at(iTasksCounter).at(2));

        m_pSelProviderCarshWidget->m_uuidProvider = QUuid::fromString(resTasks.at(iTasksCounter).at(4));
        m_pSelProviderCarshWidget->m_uuidCarsh = QUuid::fromString(resTasks.at(iTasksCounter).at(5));
        OnCarshChanged();//Для раскраски при открытии задачи

        /*Загрузка расширения задачи*/
        m_uuidSourseExtention = QUuid::fromString(resTasks.at(iTasksCounter).at(3));

        QString strExtenExec = QString("select \"Госномер\" from \"Расширение задачи Возврат в зону\" where id='%1'").arg(m_uuidSourseExtention.toString());
        QList<QStringList> resExtTasks = execMainBDQuery(strExtenExec);
        for(int iExtTasksCounter = 0 ; iExtTasksCounter < resExtTasks.size() ; iExtTasksCounter++)
        {
            /*Госномер*/
            m_pPlateLineText->setText(resExtTasks.at(iTasksCounter).at(0));
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
}


void QRetToZoneDialog::OnApplyPressedSlot()
{
    isReady();

    if((m_pSelProviderCarshWidget->m_uuidCarsh==QUuid()) or (m_pSelProviderCarshWidget->m_uuidProvider==QUuid()))
    {
        QYesNoDlg dlg("Не указан поставщик или заказчик.\n Задача не сохранится.\n Все равно выйти?");
        if(dlg.exec() == QDialog::Accepted) reject();
        else return;
    }
    showWait(true);
    SaveDataToBD();
    showWait(false);
    accept();
}

void QRetToZoneDialog::OnRemovePressedSlot()
{
    QYesNoDlg dlg("Удалить задачу?");
    if(dlg.exec() == QDialog::Accepted)
    {
        QString strExec = QString("update \"Задачи\" set Удалено = 'true' where id='%1'").arg(m_uuidSourseRecord.toString());
        execMainBDQueryUpdate(strExec);
        accept();
    }
}
