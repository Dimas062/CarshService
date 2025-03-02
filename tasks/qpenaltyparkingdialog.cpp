#include "qpenaltyparkingdialog.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QDateTime>
#include <QUuid>
#include "common.h"
#include "BDPatterns.h"
#include "service_widgets/qyesnodlg.h"
#include "service_widgets/qcsselectdialog.h"
#include "emploee_widgets/QSelectTaskEmploeer.h"


extern QRect screenGeometry;
extern QUuid uuidCurrentUser;
extern int iButtonHeight;
extern UserTypes CurrentUserType;
extern QColor currentWorkdayColor;

QPenaltyParkingDialog::QPenaltyParkingDialog(QWidget *parent, Qt::WindowFlags f ):QCSBaseDialog(parent , f /*, false*/)
{
    int iButtonWidth = screenGeometry.width()*0.6;
    m_uuidSourseRecord = QUuid();
    m_strPinaltiParkingId = QString("Undefined");
    m_strPinaltiParkingText = QString();
    m_strReasonId = QString("Undefined");
    m_strReasonText = QString();
    m_strGaiId = QString("Undefined");
    m_strGaiText = QString();

    QVBoxLayout * pVMainLayout = new QVBoxLayout;

    m_pTopLabel = new QLabel(QString("<b>Штрафстоянка.  %1<\b>").arg(QDateTime::currentDateTime().toString("dd.MM.yyyy hh:mm")));
    pVMainLayout->addWidget(m_pTopLabel);

    m_pPlateLineText = new QLineText("Гос. номер");
    pVMainLayout->addWidget(m_pPlateLineText);
    connect(m_pPlateLineText, &QLineText::textChanged, this, &QPenaltyParkingDialog::OnNumberTextInput);

    m_pPayButton = new QCSButton("Оплата");
    m_pPayButton->grabGesture(Qt::TapGesture);
    connect(m_pPayButton,SIGNAL(released()),this,SLOT(OnPayButtonPressed()));
    m_pPayButton->setMaximumHeight(iButtonHeight);
    m_pPayButton->setMinimumHeight(iButtonHeight);
    m_pPayButton->setFixedWidth(iButtonWidth);


    pVMainLayout->addWidget(m_pPayButton , 0 , Qt::AlignHCenter);

    m_pLoadActWidget= new QLoadDocLineWidget("Акт");
    pVMainLayout->addWidget(m_pLoadActWidget);
    m_pLoadProtocolWidget= new QLoadDocLineWidget("Протокол");
    pVMainLayout->addWidget(m_pLoadProtocolWidget);

    m_pLoadAutoFotoDlg = new QLoadDocsDlg;
    m_pLoadAutoFotoButton = new QPushButton("Фото автомобиля");
    connect(m_pLoadAutoFotoButton,SIGNAL(released()),this,SLOT(OnLoadAutoFotoButtonPressed()));
    m_pLoadAutoFotoButton->setMaximumHeight(iButtonHeight);
    m_pLoadAutoFotoButton->setMinimumHeight(iButtonHeight);
    m_pLoadAutoFotoButton->setFixedWidth(iButtonWidth);
    pVMainLayout->addWidget(m_pLoadAutoFotoButton, 0 , Qt::AlignHCenter);


    m_pGibddButton = new QPushButton("Отдел ГАИ");
    connect(m_pGibddButton,SIGNAL(released()),this,SLOT(OnGibddButtonPressed()));
    m_pGibddButton->setMaximumHeight(iButtonHeight);
    m_pGibddButton->setMinimumHeight(iButtonHeight);
    m_pGibddButton->setFixedWidth(iButtonWidth);
    pVMainLayout->addWidget(m_pGibddButton, 0 , Qt::AlignHCenter);

    m_pReasonButton = new QPushButton("Причина задержания");
    connect(m_pReasonButton,SIGNAL(released()),this,SLOT(OnReasonButtonPressed()));
    m_pReasonButton->setMaximumHeight(iButtonHeight);
    m_pReasonButton->setMinimumHeight(iButtonHeight);
    m_pReasonButton->setFixedWidth(iButtonWidth);
    pVMainLayout->addWidget(m_pReasonButton, 0 , Qt::AlignHCenter);

    m_pReturnToZoneButton = new QPushButton("Возврат в зону");
    connect(m_pReturnToZoneButton,SIGNAL(released()),this,SLOT(OnReturnToZoneButtonPressed()));
    m_pReturnToZoneButton->setMaximumHeight(iButtonHeight);
    m_pReturnToZoneButton->setMinimumHeight(iButtonHeight);
    m_pReturnToZoneButton->setCheckable(true);
    m_pReturnToZoneButton->setFixedWidth(iButtonWidth);
    pVMainLayout->addWidget(m_pReturnToZoneButton, 0 , Qt::AlignHCenter);

    m_pParkingButton = new QPushButton("Штрафстоянка");
    connect(m_pParkingButton,SIGNAL(released()),this,SLOT(OnParkingButtonPressed()));
    m_pParkingButton->setMaximumHeight(iButtonHeight);
    m_pParkingButton->setMinimumHeight(iButtonHeight);
    m_pParkingButton->setFixedWidth(iButtonWidth);
    pVMainLayout->addWidget(m_pParkingButton, 0 , Qt::AlignHCenter);

    m_pLineTextComment = new QLineText("Комментарий");
    pVMainLayout->addWidget(m_pLineTextComment);
    connect(m_pLineTextComment, &QLineText::textChanged, this, &QPenaltyParkingDialog::OnCommentTextInput);

    m_pSelProviderCarshWidget = new QSelProviderCarshWidget();
    pVMainLayout->addWidget(m_pSelProviderCarshWidget);
    connect(m_pSelProviderCarshWidget , SIGNAL(CarshChanged()) , this , SLOT(OnCarshChanged()));
    connect(m_pSelProviderCarshWidget , SIGNAL(ProviderChanged()) , this , SLOT(OnProviderChanged()));

    QPushButton * pApplyButton = new QPushButton("Внести");
    pApplyButton->setIcon(QIcon(":/icons/done_icon.png"));
    pApplyButton->setIconSize(QSize(iButtonHeight*0.75 , iButtonHeight*0.75));

    pVMainLayout->addWidget(pApplyButton, 0 , Qt::AlignHCenter);
    connect(pApplyButton,SIGNAL(released()),this,SLOT(OnApplyPressedSlot()));

    QPushButton * pHandOverButton = new QPushButton("Передать задачу");
    //pHandOverButton->setIcon(QIcon(":/icons/done_icon.png"));
    pHandOverButton->setIconSize(QSize(iButtonHeight*0.75 , iButtonHeight*0.75));
    pVMainLayout->addWidget(pHandOverButton, 0 , Qt::AlignHCenter);
    connect(pHandOverButton,SIGNAL(released()),this,SLOT(OnHandOverPressedSlot()));

    if(CurrentUserType == CarshService)
    {
        QPushButton * pRemoveButton = new QPushButton("Удалить");
        pRemoveButton->setIcon(QIcon(":/icons/remove_icon.png"));
        pRemoveButton->setIconSize(QSize(iButtonHeight*0.75 , iButtonHeight*0.75));
        pVMainLayout->addWidget(pRemoveButton, 0 , Qt::AlignHCenter);
        connect(pRemoveButton,SIGNAL(released()),this,SLOT(OnRemovePressedSlot()));
    }

    this->setLayout(pVMainLayout);
}

void QPenaltyParkingDialog::OnNumberTextInput(const QString &)
{
    isReady();
}

void QPenaltyParkingDialog::OnCommentTextInput(const QString &)
{
    isReady();
}

void QPenaltyParkingDialog::OnHandOverPressedSlot()
{
    this->showWait(true);
    SaveDataToBD();
    this->showWait(false);
    QSelectTaskEmploeer dlg(nullptr , Qt::WindowFlags() , m_uuidSourseRecord.toString());
    if(dlg.exec() == QDialog::Accepted)
        accept();
}

void QPenaltyParkingDialog::OnProviderChanged()
{
    isReady();
}

void QPenaltyParkingDialog::OnCarshChanged()
{
    QString strExecColor = QString("select Цвет from Заказчики where id='%1'").arg(m_pSelProviderCarshWidget->m_uuidCarsh.toString());

    QList<QStringList> colorRes = execMainBDQuery(strExecColor);
    if(colorRes.size()>0)
    {
        currentWorkdayColor = colorRes.at(0).at(0).toLongLong();
        setStyleSheet(QString("QDialog , QScrollArea , QCSBaseDlgScrollWidget, QListWidget, QLabel , QCSSelectDlgButtonsWidget {background-color: rgb(%1,%2,%3)}").arg(currentWorkdayColor.red()).arg(currentWorkdayColor.green()).arg(currentWorkdayColor.blue()));
        m_PayDlg.setStyleSheet(QString("QDialog , QScrollArea , QCSBaseDlgScrollWidget, QListWidget, QLabel , QCSSelectDlgButtonsWidget {background-color: rgb(%1,%2,%3)}").arg(currentWorkdayColor.red()).arg(currentWorkdayColor.green()).arg(currentWorkdayColor.blue()));
        m_pLoadAutoFotoDlg->setStyleSheet(QString("QDialog , QScrollArea , QCSBaseDlgScrollWidget, QListWidget, QLabel , QCSSelectDlgButtonsWidget {background-color: rgb(%1,%2,%3)}").arg(currentWorkdayColor.red()).arg(currentWorkdayColor.green()).arg(currentWorkdayColor.blue()));
    }

    isReady();
}

void QPenaltyParkingDialog::OnLoadAutoFotoButtonPressed()
{
    m_pLoadAutoFotoDlg->exec();
    isReady();
}

void QPenaltyParkingDialog::OnReasonButtonPressed()
{
    QCSSelectDialog ReasonSelDlg("Причины задержания");
    ReasonSelDlg.selectWidget.SelectId(m_strReasonId);
    if(ReasonSelDlg.exec()==QDialog::Accepted)
    {
        m_strReasonId = ReasonSelDlg.getCurId();
        m_strReasonText = ReasonSelDlg.getCurText();
    }
    isReady();
}

void QPenaltyParkingDialog::OnReturnToZoneButtonPressed()
{
    if(m_pReturnToZoneButton->isChecked())
    {
        QYesNoDlg dlg("Отменить возврат в зону?");
        if(dlg.exec()==QDialog::Accepted)
        {
            m_pReturnToZoneButton->setChecked(false);
        }
    }
    else
    {
        QYesNoDlg dlg("Установить возврат в зону?");
        if(dlg.exec()==QDialog::Accepted)
        {
            m_pReturnToZoneButton->setChecked(true);
        }
    }
}

void QPenaltyParkingDialog::OnGibddButtonPressed()
{

    QCSSelectDialog GaiSelDlg("Отделы ГИБДД");
    GaiSelDlg.selectWidget.SelectId(m_strGaiId);
    if(GaiSelDlg.exec()==QDialog::Accepted)
    {
        m_strGaiId = GaiSelDlg.getCurId();
        m_strGaiText = GaiSelDlg.getCurText();
    }
    isReady();
}

void QPenaltyParkingDialog::OnPayButtonPressed()
{
    m_PayDlg.exec();
    isReady();
}

void QPenaltyParkingDialog::OnParkingButtonPressed()
{
    QCSSelectDialog PinaltiParkingSelDlg("Штрафстоянки");
    PinaltiParkingSelDlg.selectWidget.SelectId(m_strPinaltiParkingId);
    if(PinaltiParkingSelDlg.exec()==QDialog::Accepted)
    {
        m_strPinaltiParkingId = PinaltiParkingSelDlg.getCurId();
        m_strPinaltiParkingText = PinaltiParkingSelDlg.getCurText();
    }
    isReady();
}

bool QPenaltyParkingDialog::isReady()
{
    bool retVal = true;

    if(!(m_pPlateLineText->CheckColorLenght()))
    {
        retVal = false;
    }

    if(m_pLoadAutoFotoDlg->m_pPicturesWidget->m_Pictures.size()<4)
    {
        //m_pLoadPhotoWidget->SetViewDone(false);
        m_pLoadAutoFotoButton->setStyleSheet("QPushButton {color: red;}");
        retVal = false;
    }
    else m_pLoadAutoFotoButton->setStyleSheet("QPushButton {color: black;}");

    if(!m_pLoadActWidget->CheckColorData())
    {
        retVal = false;
    }

    if(!m_pSelProviderCarshWidget->isReadyColored())
    {
        retVal = false;
    }

    if(!m_pLoadProtocolWidget->CheckColorData())
    {
        retVal = false;
    }

    bool bPayDone = true;

    if(m_PayDlg.m_pCashLineText->getText().length()<2)
    {
        retVal = false;
        bPayDone = false;
    }

    if(m_PayDlg.m_pPicturesWidget->m_Pictures.size()<1)
    {
        retVal = false;
        bPayDone = false;
    }

    if(m_PayDlg.GetSelectedPayType()==Undefined)
    {
        retVal = false;
        bPayDone = false;
    }

    if(!bPayDone) m_pPayButton->setStyleSheet("QPushButton {color: red;}");
    else m_pPayButton->setStyleSheet("QPushButton {color: black;}");

    if(m_strPinaltiParkingId.length()<33)
    {
        m_pParkingButton->setStyleSheet("QPushButton {color: red;}");
        retVal = false;
    }
    else m_pParkingButton->setStyleSheet("QPushButton {color: black;}");

    if(m_strReasonId.length()<33)
    {
        m_pReasonButton->setStyleSheet("QPushButton {color: red;}");
        retVal = false;
    }
    else m_pReasonButton->setStyleSheet("QPushButton {color: black;}");


    if(m_strGaiId.length()<33)
    {
        m_pGibddButton->setStyleSheet("QPushButton {color: red;}");
        retVal = false;
    }
    else m_pGibddButton->setStyleSheet("QPushButton {color: black;}");

    if(m_strReasonText.length()>1) m_pReasonButton->setText(QString("Причина: %1").arg(m_strReasonText));
    if(m_strGaiText.length()>1) m_pGibddButton->setText(QString("Отдел ГАИ: %1").arg(m_strGaiText));
    if(m_strPinaltiParkingText.length()>1) m_pParkingButton->setText(QString("ШС: %1").arg(m_strPinaltiParkingText));
    if(m_PayDlg.getSumString().length()>1) m_pPayButton->setText(QString("Оплата: %1 р.").arg(m_PayDlg.getSumString()));

    return retVal;
}

void QPenaltyParkingDialog::SaveDataToBD()
{

    qint64 iReadyTime=0;

    bool bIsReady = isReady();

    if(bIsReady) iReadyTime=QDateTime::currentSecsSinceEpoch();

    /*Устанавливаем оплату или нет в зависимости от завершённости задачи*/
    QString strSumm;

    if(bIsReady)
    {
        strSumm = " (select Цена from \"Типы задач\" where id='8078b7ce-e423-49ae-9ce6-17758b852b33') ";
    }
    else
    {
        strSumm = "0";
    }

    QUuid uuidReturnToZone = QUuid();

    if(m_uuidSourseRecord == QUuid()) //Новая задача
    {
        /*Сама задача*/
        QUuid uuidTask = QUuid::createUuid();
        m_uuidSourseRecord = uuidTask;
        QUuid uuidExtention = QUuid::createUuid();
        m_uuidSourseExtention = uuidExtention;
        QString strExec = QString("insert into \"Задачи\" (id,\"Дата Время\",\"Тип\",Комментарий, Расширение , Исполнитель , \"Время выполнения\" , Цена , Поставщик , Заказчик) values ('%1','%2','8078b7ce-e423-49ae-9ce6-17758b852b33','%3','%4','%5','%6',%7,'%8','%9')").arg(uuidTask.toString()).arg(QDateTime::currentSecsSinceEpoch()).arg(m_pLineTextComment->getText()).arg(uuidExtention.toString()).arg(uuidCurrentUser.toString()).arg(iReadyTime).arg(strSumm).arg(m_pSelProviderCarshWidget->m_uuidProvider.toString()).arg(m_pSelProviderCarshWidget->m_uuidCarsh.toString());
        execMainBDQueryUpdate(strExec);

        /*Расширение (оплата парковки, госномер)*/
        /*Оплата*/
        QUuid uuidPay = CreatePayRecord(m_PayDlg.m_pCashLineText->getText().toDouble() , m_PayDlg.GetSelectedPayType());



        for (int iPicCounter = 0; iPicCounter <  m_PayDlg.m_pPicturesWidget->m_Pictures.size(); ++iPicCounter)
        {
            CreatePayDocRecord(uuidPay , ImageToBase64(m_PayDlg.m_pPicturesWidget->m_Pictures.at(iPicCounter)));
        }

        strExec = QString("insert into \"Расширение задачи ШС\" (id,\"Оплата парковки\",\"Госномер\") values ('%1','%2','%3')") .arg(uuidExtention.toString()).arg(uuidPay.toString()).arg(m_pPlateLineText->getText());
        execMainBDQueryUpdate(strExec);

        strExec = QString("update \"Расширение задачи ШС\" set \"Отдел ГАИ\"='%1' where id='%2'").arg(m_strGaiId).arg(uuidExtention.toString());
        execMainBDQueryUpdate(strExec);

        strExec = QString("update \"Расширение задачи ШС\" set \"Причина задержания\"='%1' where id='%2'").arg(m_strReasonId).arg(uuidExtention.toString());
        execMainBDQueryUpdate(strExec);

        strExec = QString("update \"Расширение задачи ШС\" set \"Штрафстоянка\"='%1' where id='%2'").arg(m_strPinaltiParkingId).arg(uuidExtention.toString());
        execMainBDQueryUpdate(strExec);


        if(m_pReturnToZoneButton->isChecked())
        {
            uuidReturnToZone = QUuid::createUuid();
            QUuid uuidExtensionReturnToZone = QUuid::createUuid();
            strExec = QString("update \"Расширение задачи ШС\" set \"Возврат в зону\"='%1' where id='%2'").arg(uuidReturnToZone.toString()).arg(uuidExtention.toString());
            execMainBDQueryUpdate(strExec);

            strExec = QString("insert into \"Задачи\" (id,\"Дата Время\",\"Тип\", Расширение , Исполнитель , \"Время выполнения\") values ('%1','%2','fe81daf9-a838-4bac-84aa-595e038d3a12','%3','%4','%5')").arg(uuidReturnToZone.toString()).arg(QDateTime::currentSecsSinceEpoch()).arg(uuidExtensionReturnToZone.toString()).arg(uuidCurrentUser.toString()).arg(iReadyTime);
            execMainBDQueryUpdate(strExec);

            strExec = QString("insert into \"Расширение задачи Возврат в зону\" (id , \"Госномер\",\"Количество\") values ('%1','%2','%3')").arg(uuidExtensionReturnToZone.toString()).arg(m_pPlateLineText->getText()).arg(1);
            execMainBDQueryUpdate(strExec);
        }
        else
        {
            strExec = QString("update \"Расширение задачи ШС\" set \"Возврат в зону\"='%1' where id='%2'").arg(uuidReturnToZone.toString()).arg(uuidExtention.toString());
            execMainBDQueryUpdate(strExec);
        }

        /*Акт, протокол*/
        QString tmpStr;
        if(m_pLoadActWidget->getImgStr(tmpStr))
            CreateTaskDocRecord(uuidTask , tmpStr , QUuid("0078e19e-dfab-4a81-a5a2-569e0e683c2f"));

        if(m_pLoadProtocolWidget->getImgStr(tmpStr))
            CreateTaskDocRecord(uuidTask , tmpStr , QUuid("14ae95dc-4b0a-4528-9892-732ec08c7fe6"));


        /*Фото/документы (4 шт)*/
        /*Перебрать и записать картинки*/
        for (int iPicCounter = 0; iPicCounter < m_pLoadAutoFotoDlg->m_pPicturesWidget->m_Pictures.size(); ++iPicCounter)
        {
            CreateTaskDocRecord(uuidTask , ImageToBase64(m_pLoadAutoFotoDlg->m_pPicturesWidget->m_Pictures.at(iPicCounter)));
        }
    }
    else//Апдейтим загруженную задачу
    {

        QString strExec = QString("update \"Задачи\" set Цена = %1  where id='%2'").arg(strSumm).arg(m_uuidSourseRecord.toString());
        execMainBDQueryUpdate(strExec);

        strExec = QString("update \"Задачи\" set Поставщик = '%1'  where id='%2'").arg(m_pSelProviderCarshWidget->m_uuidProvider.toString()).arg(m_uuidSourseRecord.toString());
        execMainBDQueryUpdate(strExec);

        strExec = QString("update \"Задачи\" set Заказчик = '%1'  where id='%2'").arg(m_pSelProviderCarshWidget->m_uuidCarsh.toString()).arg(m_uuidSourseRecord.toString());
        execMainBDQueryUpdate(strExec);

        strExec = QString("update \"Задачи\" set Комментарий = '%1' , \"Время выполнения\"='%2' where id='%3'").arg(m_pLineTextComment->getText()).arg(iReadyTime).arg(m_uuidSourseRecord.toString());
        execMainBDQueryUpdate(strExec);

        strExec = QString("update \"Расширение задачи ШС\" set \"Госномер\" = '%1' where id='%2'").arg(m_pPlateLineText->getText()).arg(m_uuidSourseExtention.toString());
        execMainBDQueryUpdate(strExec);

        strExec = QString("update \"Расширение задачи ШС\" set \"Отдел ГАИ\"='%1' where id='%2'").arg(m_strGaiId).arg(m_uuidSourseExtention.toString());
        execMainBDQueryUpdate(strExec);

        strExec = QString("update \"Расширение задачи ШС\" set \"Причина задержания\"='%1' where id='%2'").arg(m_strReasonId).arg(m_uuidSourseExtention.toString());
        execMainBDQueryUpdate(strExec);

        strExec = QString("update \"Расширение задачи ШС\" set \"Штрафстоянка\"='%1' where id='%2'").arg(m_strPinaltiParkingId).arg(m_uuidSourseExtention.toString());
        execMainBDQueryUpdate(strExec);

        if((m_pReturnToZoneButton->isChecked())&&(m_uuidReturnToZoneSource==QUuid())) //Если не было, но появилось, то создаём (если было и сейчас выбрано, то ничего не делае)
        {
            uuidReturnToZone = QUuid::createUuid();
            QUuid uuidExtensionReturnToZone = QUuid::createUuid();
            strExec = QString("update \"Расширение задачи ШС\" set \"Возврат в зону\"='%1' where id='%2'").arg(uuidReturnToZone.toString()).arg(m_uuidSourseExtention.toString());
            execMainBDQueryUpdate(strExec);

            strExec = QString("insert into \"Задачи\" (id,\"Дата Время\",\"Тип\", Расширение , Исполнитель , \"Время выполнения\") values ('%1','%2','fe81daf9-a838-4bac-84aa-595e038d3a12','%3','%4','%5')").arg(uuidReturnToZone.toString()).arg(QDateTime::currentSecsSinceEpoch()).arg(uuidExtensionReturnToZone.toString()).arg(uuidCurrentUser.toString()).arg(iReadyTime);
            execMainBDQueryUpdate(strExec);

            strExec = QString("insert into \"Расширение задачи Возврат в зону\" (id , \"Госномер\",\"Количество\") values ('%1','%2','%3')").arg(uuidExtensionReturnToZone.toString()).arg(m_pPlateLineText->getText()).arg(1);
            execMainBDQueryUpdate(strExec);
        }

        if((!m_pReturnToZoneButton->isChecked())&&(m_uuidReturnToZoneSource!=QUuid())) //Снято, но до этого было - удаляем (еслти не было и нет, то ничего не делаем)
            {
                strExec = QString("update \"Расширение задачи ШС\" set \"Возврат в зону\"='%1' where id='%2'").arg(QUuid().toString()).arg(m_uuidSourseExtention.toString());
                execMainBDQueryUpdate(strExec);

                strExec = QString("delete from \"Задачи\" where id='%1'").arg(m_uuidReturnToZoneSource.toString());
                execMainBDQueryUpdate(strExec);

                strExec = QString("delete from \"Расширение задачи Возврат в зону\" where id='%1'").arg(m_uuidReturnToZoneExtensionSource.toString());
                execMainBDQueryUpdate(strExec);
            }

        /*Получим id оплаты*/
        strExec = QString("select \"Оплата парковки\" from \"Расширение задачи ШС\" where id ='%1'").arg(m_uuidSourseExtention.toString());

        QList<QStringList> strPayResult = execMainBDQuery(strExec);

        if(strPayResult.size()<1) return;

        QUuid uuidPay = QUuid::fromString(strPayResult.at(0).at(0));


        UpdatePayRecord(uuidPay , m_PayDlg.m_pCashLineText->getText().toDouble() , m_PayDlg.GetSelectedPayType());

        /*Удалим чеки*/
        RemovePayDocs(uuidPay);

        /*Загрузим новые чеки*/
        for (int iPicCounter = 0; iPicCounter <  m_PayDlg.m_pPicturesWidget->m_Pictures.size(); ++iPicCounter)
        {
            CreatePayDocRecord(uuidPay , ImageToBase64(m_PayDlg.m_pPicturesWidget->m_Pictures.at(iPicCounter)));
        }

        /*Фото/документы*/
        /*Сначала удалим все старые (включая акт-протокол)*/
        RemoveTaskDocs(m_uuidSourseRecord);

        /*Затем перебрать и записать картинки*/
        for (int iPicCounter = 0; iPicCounter < m_pLoadAutoFotoDlg->m_pPicturesWidget->m_Pictures.size(); ++iPicCounter)
        {
            CreateTaskDocRecord(m_uuidSourseRecord , ImageToBase64(m_pLoadAutoFotoDlg->m_pPicturesWidget->m_Pictures.at(iPicCounter)));
        }

        /*Акт, протокол*/
        QString tmpStr;
        if(m_pLoadActWidget->getImgStr(tmpStr))
            CreateTaskDocRecord(m_uuidSourseRecord , tmpStr , QUuid("0078e19e-dfab-4a81-a5a2-569e0e683c2f"));

        if(m_pLoadProtocolWidget->getImgStr(tmpStr))
            CreateTaskDocRecord(m_uuidSourseRecord , tmpStr , QUuid("14ae95dc-4b0a-4528-9892-732ec08c7fe6"));

    }

}

void QPenaltyParkingDialog::LoadDataFromBD(QUuid uuidSourseRecord)
{

    m_uuidSourseRecord=uuidSourseRecord;

    QString strExec = QString("select \"Дата Время\",\"Тип\",Комментарий, Расширение, Поставщик, Заказчик from \"Задачи\"  where id='%1'").arg(uuidSourseRecord.toString());

    QList<QStringList> resTasks = execMainBDQuery(strExec);
    for(int iTasksCounter = 0 ; iTasksCounter < resTasks.size() ; iTasksCounter++)
    {
        m_pTopLabel->setText(QString("<b>Штрафстоянка.  %1</b>").arg(QDateTime::fromSecsSinceEpoch(resTasks.at(iTasksCounter).at(0).toInt()).toString("dd.MM.yyyy hh:mm")));
        m_pLineTextComment->setText(resTasks.at(iTasksCounter).at(2));

        m_pSelProviderCarshWidget->m_uuidProvider = QUuid::fromString(resTasks.at(iTasksCounter).at(4));
        m_pSelProviderCarshWidget->m_uuidCarsh = QUuid::fromString(resTasks.at(iTasksCounter).at(5));

        /*Загрузка расширения задачи*/
        m_uuidSourseExtention = QUuid::fromString(resTasks.at(iTasksCounter).at(3));
        OnCarshChanged();//Для раскраски при открытии задачи

        QString strExtenExec = QString("select \"Расширение задачи ШС\".\"Оплата парковки\" , \"Расширение задачи ШС\".Госномер,\"Расширение задачи ШС\".\"Отдел ГАИ\",\"Расширение задачи ШС\".\"Причина задержания\", \"Расширение задачи ШС\".Штрафстоянка , \"Расширение задачи ШС\".\"Возврат в зону\" from \"Расширение задачи ШС\" where  \"Расширение задачи ШС\".id='%1'").arg(m_uuidSourseExtention.toString());

        QList<QStringList> resExtTasks = execMainBDQuery(strExtenExec);
        for(int iExtTasksCounter = 0 ; iExtTasksCounter < resExtTasks.size() ; iExtTasksCounter++)
        {

            /*Оплата парковки*/
            m_PayDlg.LoadFromBD(QUuid::fromString(resExtTasks.at(iTasksCounter).at(0)));


            /*Госномер*/
            m_pPlateLineText->setText(resExtTasks.at(iTasksCounter).at(1));

            m_strGaiId = (resExtTasks.at(iTasksCounter).at(2));

            m_strReasonId = (resExtTasks.at(iTasksCounter).at(3));

            m_strPinaltiParkingId = (resExtTasks.at(iTasksCounter).at(4));

            m_uuidReturnToZoneSource = QUuid(resExtTasks.at(iTasksCounter).at(5));


            m_strGaiText = StrFromUuid(m_strGaiId , "\"Отделы ГИБДД\"");
            m_strPinaltiParkingText = StrFromUuid(m_strPinaltiParkingId , "\"Штрафстоянки\"");
            m_strReasonText = StrFromUuid(m_strReasonId , "\"Причины задержания\"");

            if(m_uuidReturnToZoneSource!=QUuid())
            {
                m_pReturnToZoneButton->setChecked(true);

                strExtenExec = QString("select  Расширение from \"Задачи\"  where id='%1'").arg(m_uuidReturnToZoneSource.toString());
                QList<QStringList> resReturnToZoneExtTasks = execMainBDQuery(strExtenExec);
                m_uuidReturnToZoneExtensionSource = QUuid(resReturnToZoneExtTasks.at(iTasksCounter).at(0));
            }
            else
            {
                m_pReturnToZoneButton->setChecked(false);
                m_uuidReturnToZoneExtensionSource = QUuid();
            }
        }

        /*Загрузка картинок задачи*/
        QString strPicExec=QString("select \"Документы\".\"Изображение\" , \"Документы\".Тип from \"Документы\", \"Задача-Документы задач\", Задачи where Документы.id = \"Задача-Документы задач\".Документ and Задачи.id = \"Задача-Документы задач\".Задача and Задачи.id ='%1'").arg(uuidSourseRecord.toString());
        QList<QStringList> resPicTasks = execMainBDQuery(strPicExec);

        for(int iPicTasksCounter = 0 ; iPicTasksCounter < resPicTasks.size() ; iPicTasksCounter++)
        {
            if(QUuid(resPicTasks.at(iPicTasksCounter).at(1)) == QUuid("94ec977e-0be0-4dd7-b1fc-682af124e0ac"))
            {
                QString tmpStr = resPicTasks.at(iPicTasksCounter).at(0);
                QImage tmpImg = Base64ToImage(tmpStr);
                m_pLoadAutoFotoDlg->m_pPicturesWidget->AddImage(tmpImg);
            }

            if(QUuid(resPicTasks.at(iPicTasksCounter).at(1)) == QUuid("0078e19e-dfab-4a81-a5a2-569e0e683c2f"))  //Акт
            {
                QString tmpStr = resPicTasks.at(iPicTasksCounter).at(0);
                m_pLoadActWidget->SetImage(tmpStr);
            }

            if(QUuid(resPicTasks.at(iPicTasksCounter).at(1)) == QUuid("14ae95dc-4b0a-4528-9892-732ec08c7fe6"))  //Протокол
            {
                QString tmpStr = resPicTasks.at(iPicTasksCounter).at(0);
                m_pLoadProtocolWidget->SetImage(tmpStr);
            }
        }
    }
    isReady();
}

void QPenaltyParkingDialog::OnRemovePressedSlot()
{
    QYesNoDlg dlg("Удалить задачу?");
    if(dlg.exec() == QDialog::Accepted)
    {
        QString strExec = QString("update \"Задачи\" set Удалено = 'true' where id='%1'").arg(m_uuidSourseRecord.toString());
        execMainBDQueryUpdate(strExec);
        accept();
    }
}

void QPenaltyParkingDialog::OnApplyPressedSlot()
{
    if((m_pSelProviderCarshWidget->m_uuidCarsh==QUuid()) or (m_pSelProviderCarshWidget->m_uuidProvider==QUuid()))
    {
        qDebug()<<"before QYesNoDlg";
        QYesNoDlg dlg("Не указан поставщик или заказчик.\n Задача не сохранится.\n Все равно выйти?" , this);
        if(dlg.exec() == QDialog::Accepted)
        {
            qDebug()<<"QYesNoDlg accepted, reject";
            reject();
        }
        else
        {
            qDebug()<<"OnApplyPressedSlot SaveDataToBD and return";
            return;
        }
    }
    qDebug()<<"OnApplyPressedSlot accept()";
    showWait(true);
    SaveDataToBD();
    showWait(false);
    accept();
}
