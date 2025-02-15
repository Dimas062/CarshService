#include "qplatepartnertask.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QDateTime>
#include "service_widgets/qcsselectdialog.h"
#include "service_widgets/qcalendardataselectdlg.h"

extern QRect screenGeometry;
extern QUuid uuidCurrentPartner;
extern int iButtonHeight;
extern QColor currentWorkdayColor;

QPlatePartnerTask::QPlatePartnerTask(QWidget *parent, Qt::WindowFlags f ):QCSBaseDialog(parent , f)
{
    m_uuidSourseRecord = QUuid();

    QVBoxLayout * pVMainLayout = new QVBoxLayout;

    strIdPoint = QString(" ");
    m_selDate = QDate::currentDate();


    pVMainLayout->addSpacing(5);
    m_pTopLabel = new QLabel(QString("<b>Номера. %1</b>").arg(QDateTime::currentDateTime().toString("dd.MM.yyyy hh:mm")));
    pVMainLayout->addWidget(m_pTopLabel);

    m_pPlateCountLineText= new QLineText("Количество номеров:");
    pVMainLayout->addWidget(m_pPlateCountLineText);

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

void QPlatePartnerTask::OnApplyPressedSlot()
{
    if(!isReady()) return;

    SaveDataToBD();
    accept();
}


bool QPlatePartnerTask::isReady()
{
    bool retVal = true;

    if(strIdPoint.length()<10)
    {
        m_pPointButton->setStyleSheet("QPushButton {color: red;}");
        retVal = false;
    }
    else m_pPointButton->setStyleSheet("QPushButton {color: black;}");

    if(!m_pPlateCountLineText->CheckColorLenght()) retVal = false;

    if(!m_pSelProviderCarshWidget->isReadyColored())
    {
        retVal = false;
    }

    return retVal;
}

void QPlatePartnerTask::OnToCalendatButtonPressed()
{
    QCalendarDataSelectDlg calendarDlg(QDateTime::currentDateTime().date());
    if(calendarDlg.exec()==QDialog::Accepted)
    {
        m_selDate = calendarDlg.m_SelectedDate;
        m_pCalendarLabel->setText(QString("Дата: %1").arg(m_selDate.toString("dd.MM.yyyy")));
    }
}


void QPlatePartnerTask::SaveDataToBD()
{
    if(m_uuidSourseRecord == QUuid()) //Новая задача
    {
        /*Сама задача*/
        QUuid uuidTask = QUuid::createUuid();

        QString strExec = QString("insert into \"Задачи партнера Номера\" (id, Партнер, ДатаВремя, Точка, Количество, \"Время выполнения\" , Комментарий, Заказчик) values ('%1','%2','%3','%4','%5','%6','%7','%8')").arg(uuidTask.toString()).arg(uuidCurrentPartner.toString()).arg(QDateTime::currentDateTime().toSecsSinceEpoch()).arg(strIdPoint).arg(m_pPlateCountLineText->getText()).arg(QDateTime(m_selDate, QTime(0,0,1)).toSecsSinceEpoch()).arg(m_pCommentLineText->getText()).arg(m_pSelProviderCarshWidget->m_uuidCarsh.toString());
        execMainBDQueryUpdate(strExec);
    }
    else//Апдейтим загруженную задачу
    {
        QString strExec = QString("update \"Задачи партнера Номера\" set Точка = '%1'  where id='%2'").arg(strIdPoint).arg(m_uuidSourseRecord.toString());
        execMainBDQueryUpdate(strExec);

        strExec = QString("update \"Задачи партнера Номера\" set Количество = '%1'  where id='%2'").arg(m_pPlateCountLineText->getText()).arg(m_uuidSourseRecord.toString());
        execMainBDQueryUpdate(strExec);

        strExec = QString("update \"Задачи партнера Номера\" set \"Время выполнения\" = '%1'  where id='%2'").arg(QDateTime(m_selDate, QTime(0,0,1)).toSecsSinceEpoch()).arg(m_uuidSourseRecord.toString());
        execMainBDQueryUpdate(strExec);

        strExec = QString("update \"Задачи партнера Номера\" set Комментарий = '%1'  where id='%2'").arg(m_pCommentLineText->getText()).arg(m_uuidSourseRecord.toString());
        execMainBDQueryUpdate(strExec);

        strExec = QString("update \"Задачи партнера Номера\" set Партнер = '%1'  where id='%2'").arg(uuidCurrentPartner.toString()).arg(m_uuidSourseRecord.toString());
        execMainBDQueryUpdate(strExec);

        strExec = QString("update \"Задачи партнера Номера\" set Заказчик = '%1'  where id='%2'").arg(m_pSelProviderCarshWidget->m_uuidCarsh.toString()).arg(m_uuidSourseRecord.toString());
        execMainBDQueryUpdate(strExec);
    }
}

void QPlatePartnerTask::LoadDataFromBD(QUuid taskUuid)
{
    m_uuidSourseRecord=taskUuid;

    QString strExec = QString("select ДатаВремя, Точка, Количество, \"Время выполнения\" , Комментарий , Заказчик from \"Задачи партнера Номера\"  where id='%1'").arg(m_uuidSourseRecord.toString());

    QList<QStringList> resTasks = execMainBDQuery(strExec);
    for(int iTasksCounter = 0 ; iTasksCounter < resTasks.size() ; iTasksCounter++)
    {
        m_pTopLabel->setText(QString("<b>Номера. %1</b>").arg(QDateTime::fromSecsSinceEpoch(resTasks.at(iTasksCounter).at(0).toInt()).toString("dd.MM.yyyy hh:mm")));

        strIdPoint = resTasks.at(iTasksCounter).at(1);

        m_pPlateCountLineText->setText(resTasks.at(iTasksCounter).at(2));

        m_selDate = QDateTime::fromSecsSinceEpoch(resTasks.at(iTasksCounter).at(3).toInt()).date();
        m_pCalendarLabel->setText(QString("Дата: %1").arg(m_selDate.toString("dd.MM.yyyy")));

        m_pCommentLineText->setText(resTasks.at(iTasksCounter).at(4));

        m_pSelProviderCarshWidget->m_uuidCarsh = QUuid::fromString(resTasks.at(iTasksCounter).at(5));
        OnCarshChanged();//Для раскраски при открытии задачи
    }
}


void QPlatePartnerTask::OnPointPressedSlot()
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

//По изменению заказчика только раскраска, сам заказчик запишется при сохранении
void QPlatePartnerTask::OnCarshChanged()
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
