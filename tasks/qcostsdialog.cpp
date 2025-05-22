#include "qcostsdialog.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QDateTime>
#include <QUuid>
#include "common.h"
#include "service_widgets/qyesnodlg.h"
#include "service_widgets/qcsselectdialog.h"
#include "BDPatterns.h"


extern QRect screenGeometry;
extern QUuid uuidCurrentUser;
extern int iButtonHeight;
extern UserTypes CurrentUserType;
extern QColor currentWorkdayColor;

QCostsDialog::QCostsDialog(QWidget *parent, Qt::WindowFlags f ):QCSBaseDialog(parent , f)
{
    QVBoxLayout * pVMainLayout = new QVBoxLayout;


    pVMainLayout->addSpacing(5);
    m_pTopLabel = new QLabel(QString("<b>Расходы. %1</b>").arg(QDateTime::currentDateTime().toString("dd.MM.yyyy hh:mm")));
    pVMainLayout->addWidget(m_pTopLabel);

    m_pPayButton = new QPushButton("Оплата");
    connect(m_pPayButton,SIGNAL(pressed()),this,SLOT(OnPayButtonPressed()));
    m_pPayButton->setMaximumHeight(iButtonHeight);
    m_pPayButton->setMinimumHeight(iButtonHeight);
    pVMainLayout->addWidget(m_pPayButton);

    m_pArticleButton = new QPushButton("Статья расходов");
    connect(m_pArticleButton,SIGNAL(pressed()),this,SLOT(OnArticleButtonPressed()));
    m_pArticleButton->setMaximumHeight(iButtonHeight);
    m_pArticleButton->setMinimumHeight(iButtonHeight);
    pVMainLayout->addWidget(m_pArticleButton);

    m_pItemButton = new QPushButton("Товар");
    connect(m_pItemButton,SIGNAL(pressed()),this,SLOT(OnItemButtonPressed()));
    m_pItemButton->setMaximumHeight(iButtonHeight);
    m_pItemButton->setMinimumHeight(iButtonHeight);
    pVMainLayout->addWidget(m_pItemButton);

    m_pLineTextCount = new QLineText("Количество");
    pVMainLayout->addWidget(m_pLineTextCount);
    connect(m_pLineTextCount, &QLineText::textChanged, this, &QCostsDialog::OnCountTextInput);

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

void QCostsDialog::OnCountTextInput(const QString &)
{
    isReady();
}

bool QCostsDialog::isReady()
{
    bool retVal = true;


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

    if(!(m_pLineTextCount->CheckColorLenght()))
    {
        retVal = false;
    }

    if(!bPayDone) m_pPayButton->setStyleSheet("QPushButton {color: red;}");
    else m_pPayButton->setStyleSheet("QPushButton {color: black;}");

    if(m_strArticleId.length()<33)
    {
        m_pArticleButton->setStyleSheet("QPushButton {color: red;}");
        retVal = false;
    }
    else m_pArticleButton->setStyleSheet("QPushButton {color: black;}");

    if(m_strItemId.length()<33)
    {
        m_pItemButton->setStyleSheet("QPushButton {color: red;}");
        retVal = false;
    }
    else m_pItemButton->setStyleSheet("QPushButton {color: black;}");

    return retVal;

}

void QCostsDialog::OnArticleButtonPressed()
{
    QCSSelectDialog ArticleSelDlg("Статьи расходов", "Статья расходов");
    ArticleSelDlg.selectWidget.SelectId(m_strArticleId);
    if(ArticleSelDlg.exec()==QDialog::Accepted)
    {
        m_strArticleId = ArticleSelDlg.getCurId();
        m_strArticleText = ArticleSelDlg.getCurText();
        isReady();
    }
}

void QCostsDialog::OnItemButtonPressed()
{
    QCSSelectDialog ItemSelDlg("Товары", "Товар");
    ItemSelDlg.selectWidget.SelectId(m_strArticleId);
    if(ItemSelDlg.exec()==QDialog::Accepted)
    {
        m_strItemId = ItemSelDlg.getCurId();
        m_strItemText = ItemSelDlg.getCurText();
        isReady();
    }
}

void QCostsDialog::OnPayButtonPressed()
{
    m_PayDlg.exec();
    isReady();
}

void QCostsDialog::SaveDataToBD()
{

    if(m_uuidSourseRecord == QUuid()) //Новая покупка
    {
        /*Сама задача*/
        QUuid uuidTask = QUuid::createUuid();

        /*Оплата*/
        QString strSum = m_PayDlg.m_pCashLineText->getText();
        strSum.replace(',','.');
        QUuid uuidPay = CreatePayRecord(strSum.toDouble() , m_PayDlg.GetSelectedPayType() , m_PayDlg.m_iPayDate);

        QString strExec = QString("insert into Расходы (id,Оплата,Статья,Товар,Количество,\"Дата Время\",Сотрудник) values ('%1','%2','%3','%4','%5','%6','%7')").arg(uuidTask.toString()).arg(uuidPay.toString()).arg(m_strArticleId).arg(m_strItemId).arg(m_pLineTextCount->getText()).arg(QDateTime::currentSecsSinceEpoch()).arg(uuidCurrentUser.toString());

        execMainBDQueryUpdate(strExec);

        /*Загрузим новые чеки*/
        for (int iPicCounter = 0; iPicCounter <  m_PayDlg.m_pPicturesWidget->m_Pictures.size(); ++iPicCounter)
        {
            CreatePayDocRecord(uuidPay , ImageToBase64(m_PayDlg.m_pPicturesWidget->m_Pictures.at(iPicCounter)));
        }

    }
    else //Апдейт покупки
    {
        /*Получим id оплаты*/
        QString strExec = QString("select Оплата from Расходы where id ='%1'").arg(m_uuidSourseRecord.toString());
        QList<QStringList> strPayResult = execMainBDQuery(strExec);
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

        strExec = QString("update Расходы set Статья = '%1'  where id='%2'").arg(m_strArticleId).arg(m_uuidSourseRecord.toString());
        execMainBDQueryUpdate(strExec);

        strExec = QString("update Расходы set Товар = '%1'  where id='%2'").arg(m_strItemId).arg(m_uuidSourseRecord.toString());
        execMainBDQueryUpdate(strExec);

        strExec = QString("update Расходы set Количество = '%1'  where id='%2'").arg(m_pLineTextCount->getText().toInt()).arg(m_uuidSourseRecord.toString());
        execMainBDQueryUpdate(strExec);
    }
}

void QCostsDialog::LoadDataFromBD(QUuid uuidSourseRecord)
{
    m_uuidSourseRecord=uuidSourseRecord;

    QString strExec = QString("select Оплата,Статья,Товар,Количество,\"Дата Время\",Сотрудник from Расходы  where id='%1'").arg(uuidSourseRecord.toString());

    QList<QStringList> resTasks = execMainBDQuery(strExec);
    for(int iTasksCounter = 0 ; iTasksCounter < resTasks.size() ; iTasksCounter++)
    {
        m_pTopLabel->setText(QString("<b>Расходы. %1</b>").arg(QDateTime::fromSecsSinceEpoch(resTasks.at(iTasksCounter).at(4).toInt()).toString("dd.MM.yyyy hh:mm")));

        /*Оплата*/
        m_PayDlg.LoadFromBD(QUuid::fromString(resTasks.at(iTasksCounter).at(0)));

        m_strArticleId = (resTasks.at(iTasksCounter).at(1));

        m_strItemId = (resTasks.at(iTasksCounter).at(2));

        m_pLineTextCount->setText(resTasks.at(iTasksCounter).at(3));
    }

    isReady();
}

void QCostsDialog::OnApplyPressedSlot()
{
    if(isReady())
    {
        showWait(true);
        SaveDataToBD();
        showWait(false);
        accept();

    }
}

void QCostsDialog::OnRemovePressedSlot()
{
    QYesNoDlg dlg("Удалить расход?");
    if(dlg.exec() == QDialog::Accepted)
    {
        QString strExec = QString("update \"Расходы\" set Удалено = 'true' where id='%1'").arg(m_uuidSourseRecord.toString());
        execMainBDQueryUpdate(strExec);
        accept();
    }
}


