#include "qsmenadlg.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QDateTime>
#include <QUuid>
#include "common.h"
#include "service_widgets/qyesnodlg.h"
#include "service_widgets/qcsselectdialog.h"

extern QRect screenGeometry;
extern QUuid uuidCurrentUser;
extern int iButtonHeight;
extern UserTypes CurrentUserType;
extern QColor currentWorkdayColor;

QSmenaDlg::QSmenaDlg(QWidget *parent, Qt::WindowFlags f ):QCSBaseDialog(parent , f)
{
    m_uuidSourseRecord = QUuid();
    int iButtonWidth = screenGeometry.width()*0.6;

    m_strClockId = QString("Undefined");
    m_strClockText = QString();

    QVBoxLayout * pVMainLayout = new QVBoxLayout;


    pVMainLayout->addSpacing(5);
    m_pTopLabel = new QLabel(QString("<b>Смена. %1</b>").arg(QDateTime::currentDateTime().toString("dd.MM.yyyy hh:mm")));
    pVMainLayout->addWidget(m_pTopLabel);

    m_pLineTextComment = new QLineText("Комментарий");
    pVMainLayout->addWidget(m_pLineTextComment);
    connect(m_pLineTextComment, &QLineText::textChanged, this, &QSmenaDlg::OnCommentTextInput);

    m_pClockButton = new QPushButton("Часов");
    connect(m_pClockButton,SIGNAL(released()),this,SLOT(OnClockPressed()));
    m_pClockButton->setMaximumHeight(iButtonHeight);
    m_pClockButton->setMinimumHeight(iButtonHeight);
    m_pClockButton->setFixedWidth(iButtonWidth);
    pVMainLayout->addWidget(m_pClockButton, 0 , Qt::AlignHCenter);

    m_pSelProviderCarshWidget = new QSelProviderCarshWidget();
    pVMainLayout->addWidget(m_pSelProviderCarshWidget);
    connect(m_pSelProviderCarshWidget , SIGNAL(CarshChanged()) , this , SLOT(OnCarshChanged()));
    connect(m_pSelProviderCarshWidget , SIGNAL(ProviderChanged()) , this , SLOT(OnProviderChanged()));

    QPushButton * pApplyButton = new QPushButton("Внести");
    pApplyButton->setIcon(QIcon(":/icons/done_icon.png"));
    pApplyButton->setIconSize(QSize(iButtonHeight*0.75 , iButtonHeight*0.75));
    pVMainLayout->addWidget(pApplyButton);
    connect(pApplyButton,SIGNAL(released()),this,SLOT(OnApplyPressedSlot()));

    // if(CurrentUserType == CarshService)
    // {
        QPushButton * pRemoveButton = new QPushButton("Удалить");
        pRemoveButton->setIcon(QIcon(":/icons/remove_icon.png"));
        pRemoveButton->setIconSize(QSize(iButtonHeight*0.75 , iButtonHeight*0.75));
        pVMainLayout->addWidget(pRemoveButton);
        connect(pRemoveButton,SIGNAL(released()),this,SLOT(OnRemovePressedSlot()));
    // }

    this->setLayout(pVMainLayout);
}

bool QSmenaDlg::isReady()
{
    bool retVal = true;

    if(!m_pLineTextComment->CheckColorLenght()) retVal = false;

    if(m_strClockId.length()<30)
    {
        m_pClockButton->setStyleSheet("QPushButton {color: red;}");
        retVal = false;
    }
    else m_pClockButton->setStyleSheet("QPushButton {color: black;}");

    if(!m_pSelProviderCarshWidget->isReadyColored())
    {
        retVal = false;
    }


    return retVal;
}

void QSmenaDlg::OnCommentTextInput(const QString &)
{
    isReady();
}

void QSmenaDlg::SaveDataToBD()
{
    qint64 iReadyTime=0;

    bool bIsReady = isReady();

    if(bIsReady) iReadyTime=QDateTime::currentSecsSinceEpoch();

    /*Устанавливаем оплату или нет в зависимости от завершённости задачи*/
    QString strSumm;

    if(bIsReady)
    {
        strSumm = QString(" (select Цена*%1 from \"Типы задач\" where id='78850df8-814b-41c8-8977-945c085f3021') ").arg(m_strClockText);
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

        QString strExec = QString("insert into \"Задачи\" (id,\"Дата Время\",\"Тип\",Комментарий, Расширение , Исполнитель, \"Время выполнения\" , Цена , Поставщик , Заказчик) values ('%1','%2','78850df8-814b-41c8-8977-945c085f3021','%3','%4','%5','%6',%7,'%8','%9')").arg(uuidTask.toString()).arg(QDateTime::currentSecsSinceEpoch()).arg(m_pLineTextComment->getText()).arg(uuidExtention.toString()).arg(uuidCurrentUser.toString()).arg(iReadyTime).arg(strSumm).arg(m_pSelProviderCarshWidget->m_uuidProvider.toString()).arg(m_pSelProviderCarshWidget->m_uuidCarsh.toString());
        execMainBDQueryUpdate(strExec);

        strExec = QString("insert into \"Расширение задачи Смена\" (id,\"Количество часов\") values ('%1','%2')").arg(uuidExtention.toString()).arg(m_strClockId);
        execMainBDQueryUpdate(strExec);
    }
    else//Апдейтим загруженную задачу
    {
        QString strExec = QString("update \"Задачи\" set Поставщик = '%1'  where id='%2'").arg(m_pSelProviderCarshWidget->m_uuidProvider.toString()).arg(m_uuidSourseRecord.toString());
        execMainBDQueryUpdate(strExec);

        strExec = QString("update \"Задачи\" set Заказчик = '%1'  where id='%2'").arg(m_pSelProviderCarshWidget->m_uuidCarsh.toString()).arg(m_uuidSourseRecord.toString());
        execMainBDQueryUpdate(strExec);

        strExec = QString("update \"Расширение задачи Смена\" set \"Количество часов\" = '%1' where id='%2'").arg(m_strClockId).arg(m_uuidSourseExtention.toString());
        execMainBDQueryUpdate(strExec);

        strExec = QString("update \"Задачи\" set Комментарий = '%1' , \"Время выполнения\"='%2' where id='%3'").arg(m_pLineTextComment->getText()).arg(iReadyTime).arg(m_uuidSourseRecord.toString());
        execMainBDQueryUpdate(strExec);

        strExec = QString("update \"Задачи\" set Цена = %1  where id='%2'").arg(strSumm).arg(m_uuidSourseRecord.toString());
        execMainBDQueryUpdate(strExec);
    }
}

void QSmenaDlg::LoadDataFromBD(QUuid uuidSourseRecord)
{
    m_uuidSourseRecord=uuidSourseRecord;

    QString strExec = QString("select \"Дата Время\",\"Тип\",Комментарий, Расширение, Поставщик, Заказчик from \"Задачи\"  where id='%1'").arg(uuidSourseRecord.toString());


    QList<QStringList> resTasks = execMainBDQuery(strExec);
    for(int iTasksCounter = 0 ; iTasksCounter < resTasks.size() ; iTasksCounter++)
    {
        m_pTopLabel->setText(QString("<b>Смена. %1</b>").arg(QDateTime::fromSecsSinceEpoch(resTasks.at(iTasksCounter).at(0).toInt()).toString("dd.MM.yyyy hh:mm")));
        m_pLineTextComment->setText(resTasks.at(iTasksCounter).at(2));

        m_pSelProviderCarshWidget->m_uuidProvider = QUuid::fromString(resTasks.at(iTasksCounter).at(4));
        m_pSelProviderCarshWidget->m_uuidCarsh = QUuid::fromString(resTasks.at(iTasksCounter).at(5));
        OnCarshChanged();//Для раскраски при открытии задачи

        /*Загрузка расширения задачи*/
        m_uuidSourseExtention = QUuid::fromString(resTasks.at(iTasksCounter).at(3));

        QString strExtenExec = QString("select \"Расширение задачи Смена\".\"Количество часов\" , \"Количество часов в смене\".Количество from \"Расширение задачи Смена\",\"Количество часов в смене\" where \"Расширение задачи Смена\".\"Количество часов\"=\"Количество часов в смене\".id  and \"Расширение задачи Смена\".id='%1'").arg(m_uuidSourseExtention.toString());
        QList<QStringList> resExtTasks = execMainBDQuery(strExtenExec);
        for(int iExtTasksCounter = 0 ; iExtTasksCounter < resExtTasks.size() ; iExtTasksCounter++)
        {
            /*Часы*/
            m_strClockId = (resExtTasks.at(iTasksCounter).at(0));
            m_strClockText = (resExtTasks.at(iTasksCounter).at(1));
        }
    }

    isReady();
}

void QSmenaDlg::OnClockPressed()
{
    QCSSelectDialog ClockSelDlg("Количество часов в смене","Количество");
    ClockSelDlg.selectWidget.SelectId(m_strClockId);
    if(ClockSelDlg.exec()==QDialog::Accepted)
    {
        m_strClockId = ClockSelDlg.getCurId();
        m_strClockText = ClockSelDlg.getCurText();
        isReady();
    }
}

void QSmenaDlg::OnApplyPressedSlot()
{
    isReady();

    // if((m_pSelProviderCarshWidget->m_uuidCarsh==QUuid()) or (m_pSelProviderCarshWidget->m_uuidProvider==QUuid()))
    // {
    //     QYesNoDlg dlg("Не указан поставщик или заказчик.\n Задача не сохранится.\n Все равно выйти?");
    //     if(dlg.exec() == QDialog::Accepted) reject();
    //     else return;
    // }
    showWait(true);
    SaveDataToBD();
    showWait(false);
    accept();
}

void QSmenaDlg::OnRemovePressedSlot()
{
    QYesNoDlg dlg("Удалить задачу?");
    if(dlg.exec() == QDialog::Accepted)
    {
        QString strExec = QString("update \"Задачи\" set Удалено = 'true' where id='%1'").arg(m_uuidSourseRecord.toString());
        execMainBDQueryUpdate(strExec);
        accept();
    }
}

void QSmenaDlg::OnProviderChanged()
{
    isReady();
}

void QSmenaDlg::OnCarshChanged()
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
