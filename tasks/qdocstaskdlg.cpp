#include "qdocstaskdlg.h"
#include "service_widgets/qyesnodlg.h"
#include "service_widgets/qcsselectdialog.h"
#include "service_widgets/qstringlistdlg.h"
#include "common.h"
#include "BDPatterns.h"


#define IS_STS QUuid::fromString(m_strDocId) == QUuid(QString("d7e6ca81-d6fe-405e-8a39-961ceb9bd1f6"))

extern QRect screenGeometry;
extern QUuid uuidCurrentUser;
extern int iButtonHeight;
extern UserTypes CurrentUserType;
extern QColor currentWorkdayColor;

QDocsTaskDlg::QDocsTaskDlg(QWidget *parent, Qt::WindowFlags f ):QCSBaseDialog(parent , f /*, false*/)
{
    int iButtonWidth = screenGeometry.width()*0.6;
    m_uuidSourseRecord = QUuid();

    m_strDocId = QString("Undefined");
    m_strDocText = QString();

    QVBoxLayout * pVMainLayout = new QVBoxLayout;

    m_pTopLabel = new QLabel(QString("<b>Документы.  %1<\b>").arg(QDateTime::currentDateTime().toString("dd.MM.yyyy hh:mm")));
    pVMainLayout->addWidget(m_pTopLabel);

    m_pDocsCountText = new QLineText("Количество");
    pVMainLayout->addWidget(m_pDocsCountText);
    connect(m_pDocsCountText, &QLineText::textChanged, this, &QDocsTaskDlg::OnCountTextInput);

    m_pPayButton = new QCSButton("Оплата");
    m_pPayButton->grabGesture(Qt::TapGesture);
    connect(m_pPayButton,SIGNAL(released()),this,SLOT(OnPayButtonPressed()));
    m_pPayButton->setMaximumHeight(iButtonHeight);
    m_pPayButton->setMinimumHeight(iButtonHeight);
    m_pPayButton->setFixedWidth(iButtonWidth);
    m_pPayButton->setEnabled(false);
    pVMainLayout->addWidget(m_pPayButton , 0 , Qt::AlignHCenter);

    m_pGRZsButton = new QCSButton("Номера");
    m_pGRZsButton->grabGesture(Qt::TapGesture);
    connect(m_pGRZsButton,SIGNAL(released()),this,SLOT(OnGRZsButtonPressed()));
    m_pGRZsButton->setMaximumHeight(iButtonHeight);
    m_pGRZsButton->setMinimumHeight(iButtonHeight);
    m_pGRZsButton->setFixedWidth(iButtonWidth);
    m_pGRZsButton->setEnabled(false);
    pVMainLayout->addWidget(m_pGRZsButton , 0 , Qt::AlignHCenter);


    m_pDocTypeButton = new QPushButton("Тип документа");
    connect(m_pDocTypeButton,SIGNAL(released()),this,SLOT(OnDocButtonPressed()));
    m_pDocTypeButton->setMaximumHeight(iButtonHeight);
    m_pDocTypeButton->setMinimumHeight(iButtonHeight);
    m_pDocTypeButton->setFixedWidth(iButtonWidth);
    pVMainLayout->addWidget(m_pDocTypeButton, 0 , Qt::AlignHCenter);

    m_pLineTextComment = new QLineText("Комментарий");
    pVMainLayout->addWidget(m_pLineTextComment);
    connect(m_pLineTextComment, &QLineText::textChanged, this, &QDocsTaskDlg::OnCommentTextInput);

    m_pSelProviderCarshWidget = new QSelProviderCarshWidget();
    pVMainLayout->addWidget(m_pSelProviderCarshWidget);
    connect(m_pSelProviderCarshWidget , SIGNAL(CarshChanged()) , this , SLOT(OnCarshChanged()));
    connect(m_pSelProviderCarshWidget , SIGNAL(ProviderChanged()) , this , SLOT(OnProviderChanged()));

    QPushButton * pApplyButton = new QPushButton("Внести");
    pApplyButton->setIcon(QIcon(":/icons/done_icon.png"));
    pApplyButton->setIconSize(QSize(iButtonHeight*0.75 , iButtonHeight*0.75));

    pVMainLayout->addWidget(pApplyButton, 0 , Qt::AlignHCenter);
    connect(pApplyButton,SIGNAL(released()),this,SLOT(OnApplyPressedSlot()));


    QPushButton * pRemoveButton = new QPushButton("Удалить");
    pRemoveButton->setIcon(QIcon(":/icons/remove_icon.png"));
    pRemoveButton->setIconSize(QSize(iButtonHeight*0.75 , iButtonHeight*0.75));
    pVMainLayout->addWidget(pRemoveButton, 0 , Qt::AlignHCenter);
    connect(pRemoveButton,SIGNAL(released()),this,SLOT(OnRemovePressedSlot()));


    this->setLayout(pVMainLayout);
}

void QDocsTaskDlg::OnCountTextInput(const QString &text)
{
    isReady();
}

void QDocsTaskDlg::OnCommentTextInput(const QString &text)
{
    isReady();
}


bool QDocsTaskDlg::isReady()
{
    bool retVal = true;


    if(!m_pSelProviderCarshWidget->isReadyColored())
    {
        retVal = false;
    }

    if(IS_STS)
    {
        //Оплата
        bool bPayDone = true;

        if(m_PayDlg.m_pCashLineText->getText().length()<2)
        {
            retVal = false;
            bPayDone = false;
        }

        // if(m_PayDlg.m_pPicturesWidget->m_Pictures.size()<1)
        // {
        //     retVal = false;
        //     bPayDone = false;
        // } - оплата нужна, но чек гаишники не дают, поэтому не требуется

        if(m_PayDlg.GetSelectedPayType()==Undefined)
        {
            retVal = false;
            bPayDone = false;
        }

        if(!bPayDone) m_pPayButton->setStyleSheet("QPushButton {color: red;}");
        else m_pPayButton->setStyleSheet("QPushButton {color: black;}");

        //Номера
        int iSTSCount = m_pDocsCountText->getText().toInt();
        if(m_strListGRZs.length() != iSTSCount)
        {
            m_pGRZsButton->setStyleSheet("QPushButton {color: red;}");
            retVal = false;
        }
        else
            m_pGRZsButton->setStyleSheet("QPushButton {color: black;}");

    }

    if(m_strDocId.length()<33)
    {
        m_pDocTypeButton->setStyleSheet("QPushButton {color: red;}");
        retVal = false;
    }
    else m_pDocTypeButton->setStyleSheet("QPushButton {color: black;}");

    // if(!(m_pLineTextComment->CheckColorLenght()))
    // {
    //     retVal = false;
    // } - комментарий тоже не обязательно

    if(!(m_pDocsCountText->CheckColorLenght()))
    {
        retVal = false;
    }

     if(m_PayDlg.getSumString().length()>1) m_pPayButton->setText(QString("Оплата: %1 р.").arg(m_PayDlg.getSumString()));

    return retVal;
}

void QDocsTaskDlg::SaveDataToBD()
{
    qint64 iReadyTime=0;

    bool bIsReady = isReady();

    if(bIsReady) iReadyTime=QDateTime::currentSecsSinceEpoch();

    /*Устанавливаем оплату или нет в зависимости от завершённости задачи*/
    QString strSumm;

    if(bIsReady)
    {
        strSumm = " (select Цена from \"Типы задач\" where id='25695573-f5fe-43fd-93dc-76ee09e461fa') ";
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

        QString strExec = QString("insert into \"Задачи\" (id,\"Дата Время\",\"Тип\",Комментарий, Расширение , Исполнитель , \"Время выполнения\" , Цена , Поставщик , Заказчик) values ('%1','%2','25695573-f5fe-43fd-93dc-76ee09e461fa','%3','%4','%5','%6',%7,'%8','%9')").arg(uuidTask.toString()).arg(QDateTime::currentSecsSinceEpoch()).arg(m_pLineTextComment->getText()).arg(uuidExtention.toString()).arg(uuidCurrentUser.toString()).arg(0).arg(0).arg(m_pSelProviderCarshWidget->m_uuidProvider.toString()).arg(m_pSelProviderCarshWidget->m_uuidCarsh.toString());
        execMainBDQueryUpdate(strExec);

        /*Расширение (оплата парковки, госномер)*/
        strExec = QString("insert into \"Расширение задачи Документы\" (id,\"Количество\") values ('%1','%2')") .arg(uuidExtention.toString()).arg(m_pDocsCountText->getText());
        execMainBDQueryUpdate(strExec);

        strExec = QString("update \"Расширение задачи Документы\" set \"Документ\"='%1' where id='%2'").arg(m_strDocId).arg(uuidExtention.toString());
        execMainBDQueryUpdate(strExec);



        if(IS_STS)
        {
            /*Оплата*/
            QString strSum = m_PayDlg.m_pCashLineText->getText();
            strSum.replace(',','.');
            QUuid uuidPay = CreatePayRecord(strSum.toDouble() , m_PayDlg.GetSelectedPayType() , m_PayDlg.m_iPayDate);

            strExec = QString("update \"Расширение задачи Документы\" set \"Оплата\"='%1' where id='%2'").arg(uuidPay.toString()).arg(uuidExtention.toString());
            execMainBDQueryUpdate(strExec);

            for (int iPicCounter = 0; iPicCounter <  m_PayDlg.m_pPicturesWidget->m_Pictures.size(); ++iPicCounter)
            {
                CreatePayDocRecord(uuidPay , ImageToBase64(m_PayDlg.m_pPicturesWidget->m_Pictures.at(iPicCounter)));
            }

            /*Номера*/
            foreach (QString strNum, m_strListGRZs) {
                QUuid newNumGuid = QUuid::createUuid();
                strExec = QString("insert into \"Номера-ЗадачаДокументыСТС\" (id, Задача, Номер) values ('%1','%2','%3')").arg(newNumGuid.toString()).arg(uuidTask.toString()).arg(strNum);
                execMainBDQueryUpdate(strExec);
            }
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

        strExec = QString("update \"Расширение задачи Документы\" set \"Количество\" = '%1' where id='%2'").arg(m_pDocsCountText->getText()).arg(m_uuidSourseExtention.toString());
        execMainBDQueryUpdate(strExec);

        strExec = QString("update \"Расширение задачи Документы\" set \"Документ\"='%1' where id='%2'").arg(m_strDocId).arg(m_uuidSourseExtention.toString());
        execMainBDQueryUpdate(strExec);


        /*Получим id оплаты*/
        strExec = QString("select \"Оплата парковки\" from \"Расширение задачи ШС\" where id ='%1'").arg(m_uuidSourseExtention.toString());

        QList<QStringList> strPayResult = execMainBDQuery(strExec);

        if(IS_STS)
        {
            //Добовляем/обновляем оплату
            if(strPayResult.size()<1) //Если оплаты нет, то создадим новую
            {
                QString strSum = m_PayDlg.m_pCashLineText->getText();
                strSum.replace(',','.');
                QUuid uuidPay = CreatePayRecord(strSum.toDouble() , m_PayDlg.GetSelectedPayType() , m_PayDlg.m_iPayDate);

                strExec = QString("update \"Расширение задачи Документы\" set \"Оплата\"='%1' where id='%2'").arg(uuidPay.toString()).arg(m_uuidSourseExtention.toString());
                execMainBDQueryUpdate(strExec);

                for (int iPicCounter = 0; iPicCounter <  m_PayDlg.m_pPicturesWidget->m_Pictures.size(); ++iPicCounter)
                {
                    CreatePayDocRecord(uuidPay , ImageToBase64(m_PayDlg.m_pPicturesWidget->m_Pictures.at(iPicCounter)));
                }
            }
            else//Если оплата есть, то обновим ту, что есть
            {

                QUuid uuidPay = QUuid::fromString(strPayResult.at(0).at(0));

                QString strSum = m_PayDlg.m_pCashLineText->getText();
                strSum.replace(',','.');
                UpdatePayRecord(uuidPay , strSum.toDouble() , m_PayDlg.GetSelectedPayType() , m_PayDlg.m_iPayDate);

                /*Удалим чеки*/
                RemovePayDocs(uuidPay);

                /*Загрузим новые чеки*/
                for (int iPicCounter = 0; iPicCounter <  m_PayDlg.m_pPicturesWidget->m_Pictures.size(); ++iPicCounter)
                {
                    CreatePayDocRecord(uuidPay , ImageToBase64(m_PayDlg.m_pPicturesWidget->m_Pictures.at(iPicCounter)));
                }
            }
            //Добовляем/обновляем номера СТСок
            //Удаляем старые
            strExec = QString("delete from \"Номера-ЗадачаДокументыСТС\" where Задача='%1'").arg(m_uuidSourseRecord.toString());
            execMainBDQueryUpdate(strExec);

            //Добовляем текущие
            foreach (QString strNum, m_strListGRZs) {
                QUuid newNumGuid = QUuid::createUuid();
                strExec = QString("insert into \"Номера-ЗадачаДокументыСТС\" (id, Задача, Номер) values ('%1','%2','%3')").arg(newNumGuid.toString()).arg(m_uuidSourseRecord.toString()).arg(strNum);
                execMainBDQueryUpdate(strExec);
            }

        }
        else //Если не СТС, то удаляем оплаты и госномера
        {
            //Если оплата есть, то удаляем
            if(strPayResult.size()>1)
            {
                QUuid uuidPay = QUuid::fromString(strPayResult.at(0).at(0));

                /*Удалим чеки*/
                RemovePayDocs(uuidPay);

                /*Удалим саму запись оплаты*/
                strExec = QString("delete from  \"Платежи сотрудников\" where id='%1'").arg(uuidPay.toString());
                execMainBDQueryUpdate(strExec);

                /*Обнулим поле в записи расширения*/
                strExec = QString("update \"Расширение задачи Документы\" set \"Оплата\"='null' where id='%1'").arg(uuidPay.toString());
                execMainBDQueryUpdate(strExec);
            }

            //Удаляем номера СТСок
            strExec = QString("delete from \"Номера-ЗадачаДокументыСТС\" where Задача='%1'").arg(m_uuidSourseRecord.toString());
            execMainBDQueryUpdate(strExec);
        }

        strExec = QString("update \"Задачи\" set Цена = %1  where id='%2'").arg(strSumm).arg(m_uuidSourseRecord.toString());
        execMainBDQueryUpdate(strExec);

        strExec = QString("update \"Задачи\" set Комментарий = '%1' , \"Время выполнения\"='%2' where id='%3'").arg(m_pLineTextComment->getText()).arg(iReadyTime).arg(m_uuidSourseRecord.toString());
        execMainBDQueryUpdate(strExec);
    }
}

void QDocsTaskDlg::LoadDataFromBD(QUuid uuidSourseRecord)
{
    m_uuidSourseRecord=uuidSourseRecord;

    QString strExec = QString("select \"Дата Время\",\"Тип\",Комментарий, Расширение, Поставщик, Заказчик from \"Задачи\"  where id='%1'").arg(uuidSourseRecord.toString());

    QList<QStringList> resTasks = execMainBDQuery(strExec);
    for(int iTasksCounter = 0 ; iTasksCounter < resTasks.size() ; iTasksCounter++)
    {
        m_pTopLabel->setText(QString("<b>Документы.  %1</b>").arg(QDateTime::fromSecsSinceEpoch(resTasks.at(iTasksCounter).at(0).toInt()).toString("dd.MM.yyyy hh:mm")));
        m_pLineTextComment->setText(resTasks.at(iTasksCounter).at(2));

        m_pSelProviderCarshWidget->m_uuidProvider = QUuid::fromString(resTasks.at(iTasksCounter).at(4));
        m_pSelProviderCarshWidget->m_uuidCarsh = QUuid::fromString(resTasks.at(iTasksCounter).at(5));
        OnCarshChanged();//Для раскраски при открытии задачи
        /*Загрузка расширения задачи*/
        m_uuidSourseExtention = QUuid::fromString(resTasks.at(iTasksCounter).at(3));

        QString strExtenExec = QString("select Количество, Документ, Оплата from \"Расширение задачи Документы\" where id='%1'").arg(m_uuidSourseExtention.toString());

        QList<QStringList> resExtTasks = execMainBDQuery(strExtenExec);
        for(int iExtTasksCounter = 0 ; iExtTasksCounter < resExtTasks.size() ; iExtTasksCounter++)
        {

            /*Оплата парковки*/
            m_PayDlg.LoadFromBD(QUuid::fromString(resExtTasks.at(iTasksCounter).at(2)));

            m_pDocsCountText->setText(resExtTasks.at(iTasksCounter).at(0));

            m_strDocId = (resExtTasks.at(iTasksCounter).at(1));

            if(IS_STS)
            {
                m_pPayButton->setEnabled(true);
                m_pGRZsButton->setEnabled(true);
            }
            else
            {
                m_pPayButton->setEnabled(false);
                m_pGRZsButton->setEnabled(false);
            }

        }

        //Номера СТСок
        QString strGRZsExec = QString("select Номер from \"Номера-ЗадачаДокументыСТС\" where Задача = '%1'").arg(m_uuidSourseRecord.toString());
        QList<QStringList> resGRZs = execMainBDQuery(strGRZsExec);
        foreach (QStringList list, resGRZs) {
            m_strListGRZs<<list[0];
        }
    }
    isReady();


}

void QDocsTaskDlg::OnPayButtonPressed()
{
    m_PayDlg.exec();
    isReady();
}

void QDocsTaskDlg::OnGRZsButtonPressed()
{
    QStringListDlg dlg(m_strListGRZs , "Номера");
    if(dlg.exec() == QDialog::Accepted)
    {
        m_strListGRZs = dlg.m_strList;
    }
    isReady();
}

void QDocsTaskDlg::OnApplyPressedSlot()
{
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

void QDocsTaskDlg::OnDocButtonPressed()
{
    QCSSelectDialog DocSelDlg("Документы задачи документы" , "Документ");
    DocSelDlg.selectWidget.SelectId(m_strDocId);
    if(DocSelDlg.exec()==QDialog::Accepted)
    {
        m_strDocId = DocSelDlg.getCurId();
        m_strDocText = DocSelDlg.getCurText();

        /*Если документ СТС, то оплата*/
        if(IS_STS)
        {
            m_pPayButton->setEnabled(true);
            m_pGRZsButton->setEnabled(true);
        }
        else
        {
            m_pGRZsButton->setEnabled(false);
            m_pPayButton->setEnabled(false);
        }

        isReady();
    }
}

void QDocsTaskDlg::OnRemovePressedSlot()
{
    QYesNoDlg dlg("Удалить задачу?");
    if(dlg.exec() == QDialog::Accepted)
    {
        QString strExec = QString("update \"Задачи\" set Удалено = 'true' where id='%1'").arg(m_uuidSourseRecord.toString());
        execMainBDQueryUpdate(strExec);
        accept();
    }
}

void QDocsTaskDlg::OnProviderChanged()
{
    isReady();
}

void QDocsTaskDlg::OnCarshChanged()
{
    QString strExecColor = QString("select Цвет from Заказчики where id='%1'").arg(m_pSelProviderCarshWidget->m_uuidCarsh.toString());

    QList<QStringList> colorRes = execMainBDQuery(strExecColor);
    if(colorRes.size()>0)
    {
        currentWorkdayColor = colorRes.at(0).at(0).toLongLong();
        setStyleSheet(QString("QDialog , QScrollArea , QCSBaseDlgScrollWidget, QListWidget, QLabel , QCSSelectDlgButtonsWidget {background-color: rgb(%1,%2,%3)}").arg(currentWorkdayColor.red()).arg(currentWorkdayColor.green()).arg(currentWorkdayColor.blue()));
        m_PayDlg.setStyleSheet(QString("QDialog , QScrollArea , QCSBaseDlgScrollWidget, QListWidget, QLabel , QCSSelectDlgButtonsWidget {background-color: rgb(%1,%2,%3)}").arg(currentWorkdayColor.red()).arg(currentWorkdayColor.green()).arg(currentWorkdayColor.blue()));
    }

    isReady();
}
