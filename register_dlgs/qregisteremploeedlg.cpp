#include "qregisteremploeedlg.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QGuiApplication>
#include <QKeyEvent>
#include <QPushButton>

#include <QFileInfo>
#include <QUuid>
// #include <QImageReader>
// #include <QBuffer>

extern QRect screenGeometry;
extern int iButtonHeight;

QRegisterEmploeeDlg::QRegisterEmploeeDlg(QWidget *parent, Qt::WindowFlags f ):QCSBaseDialog(parent , f)
{
    // int iUnderButtonSpace = 15;

    // int iButtonHeight = (int)((screenGeometry.height()*0.7)/8)-iUnderButtonSpace;


    QVBoxLayout * pVMainLayout = new QVBoxLayout;


    pVMainLayout->addSpacing(5);

    QHBoxLayout * pLoginPassHBoxLayout = new QHBoxLayout;

    m_pLoginColumnText = new QColumnText("Логин");
    pLoginPassHBoxLayout->addWidget(m_pLoginColumnText);

    m_pPasswordColumnText = new QColumnText("Пароль");
    pLoginPassHBoxLayout->addWidget(m_pPasswordColumnText);

    pVMainLayout->addLayout(pLoginPassHBoxLayout);

    m_pSurnameLineText = new QLineText("Фамилия");
    pVMainLayout->addWidget(m_pSurnameLineText);

    m_pNameLineText = new QLineText("Имя");
    pVMainLayout->addWidget(m_pNameLineText);

    m_pMiddlenameLineText = new QLineText("Отчество");
    pVMainLayout->addWidget(m_pMiddlenameLineText);

    m_pPhoneLineText = new QLineText("Телефон");
    pVMainLayout->addWidget(m_pPhoneLineText);

    m_pLoadPhotoWidget = new QLoadDocLineWidget("Фото");
    pVMainLayout->addWidget(m_pLoadPhotoWidget);

    m_pLoadPassportWidget = new QLoadDocLineWidget("Паспорт");
    pVMainLayout->addWidget(m_pLoadPassportWidget);

    m_pLoadDriverCardWidget = new QLoadDocLineWidget("Права");
    pVMainLayout->addWidget(m_pLoadDriverCardWidget);

    m_pLoadSertWidget = new QLoadDocLineWidget("Лицензия");
    pVMainLayout->addWidget(m_pLoadSertWidget);


    pVMainLayout->addStretch();

    QPushButton * pApplyButton = new QPushButton("Отправить");
    connect(pApplyButton,SIGNAL(pressed()),this,SLOT(OnApplyPressed()));
    pVMainLayout->addWidget(pApplyButton);

    pVMainLayout->addStretch();

    this->setLayout(pVMainLayout);
}


void QRegisterEmploeeDlg::OnApplyPressed()
{
    bool bIsAllOk = true;

    bIsAllOk =  m_pLoginColumnText->CheckColorLenght()&bIsAllOk;
    bIsAllOk =  m_pPasswordColumnText->CheckColorLenght()&bIsAllOk;
    bIsAllOk =  m_pSurnameLineText->CheckColorLenght()&bIsAllOk;
    bIsAllOk =  m_pNameLineText->CheckColorLenght()&bIsAllOk;
    bIsAllOk =  m_pMiddlenameLineText->CheckColorLenght()&bIsAllOk;
    bIsAllOk =  m_pPhoneLineText->CheckColorLenght()&bIsAllOk;
    bIsAllOk =  m_pLoadPassportWidget->CheckColorData()&bIsAllOk;
    bIsAllOk =  m_pLoadDriverCardWidget->CheckColorData()&bIsAllOk;
    bIsAllOk =  m_pLoadSertWidget->CheckColorData()&bIsAllOk;

    if(bIsAllOk)
    {
        /*Сначала создаём документы, что бы потом одним запросом добавить пользователя*/

        /*Паспорт*/
        QUuid uuidPassport;
        if(m_pLoadPassportWidget->CheckColorData())
            uuidPassport = QUuid::createUuid();

        QUuid uuidDriverCard;
        if(m_pLoadDriverCardWidget->CheckColorData())
            uuidDriverCard = QUuid::createUuid();

        QUuid uuidSert;
        if(m_pLoadSertWidget->CheckColorData())
            uuidSert = QUuid::createUuid();

        QString imgTempStr;
        QString strExec;

        if(m_pLoadPassportWidget->getImgStr(imgTempStr))
        {
            strExec = QString("insert into \"Документы\" (id,\"Изображение\",\"Тип\") values ('%1','%2','79e23c72-712b-4751-8a2b-4db82a270be3')").arg(uuidPassport.toString()).arg(imgTempStr);
            execMainBDQueryUpdate(strExec);
        }

        if(m_pLoadDriverCardWidget->getImgStr(imgTempStr))
        {
            strExec = QString("insert into \"Документы\" (id,\"Изображение\",\"Тип\") values ('%1','%2','0f3d1416-cbf7-481e-8c1c-1e5b819e75f5')").arg(uuidDriverCard.toString()).arg(imgTempStr);
            execMainBDQueryUpdate(strExec);
        }

        if(m_pLoadSertWidget->getImgStr(imgTempStr))
        {
            strExec = QString("insert into \"Документы\" (id,\"Изображение\",\"Тип\") values ('%1','%2','2e73791e-402d-4f7c-b777-bc3cc51e415b')").arg(uuidSert.toString()).arg(imgTempStr);
            execMainBDQueryUpdate(strExec);
        }



        /*Пользователь*/
        m_pLoadPhotoWidget->getImgStr(imgTempStr);
        QUuid uuidNewUser = QUuid::createUuid();
        strExec = QString("insert into \"Пользователи\" (id , \"Фамилия\",\"Имя\",\"Отчество\",\"Пароль\",\"Логин\",\"Роль\",\"Дата регистрации\",Фото)"
                              "values ('%1','%2','%3','%4','%5','%6','80066f83-c025-410b-b439-f3e9b2299461','%7','%8')")
                              .arg(uuidNewUser.toString())
                              .arg(m_pSurnameLineText->getText())
                              .arg(m_pNameLineText->getText())
                              .arg(m_pMiddlenameLineText->getText())
                              .arg(m_pPasswordColumnText->getText())
                              .arg(m_pLoginColumnText->getText())
                              .arg(QDateTime::currentSecsSinceEpoch())
                              .arg(imgTempStr);
        execMainBDQueryUpdate(strExec);

        /*Документы-пользователь*/
        QUuid uuidDoc = QUuid::createUuid();
        strExec = QString("insert into \"Пользователь-Документы\" (id,\"Пользователь\",\"Документ\") values ('%1','%2','%3')").arg(uuidDoc.toString()).arg(uuidNewUser.toString()).arg(uuidPassport.toString());
        execMainBDQueryUpdate(strExec);

        uuidDoc = QUuid::createUuid();
        strExec = QString("insert into \"Пользователь-Документы\" (id,\"Пользователь\",\"Документ\") values ('%1','%2','%3')").arg(uuidDoc.toString()).arg(uuidNewUser.toString()).arg(uuidDriverCard.toString());
        execMainBDQueryUpdate(strExec);

        uuidDoc = QUuid::createUuid();
        strExec = QString("insert into \"Пользователь-Документы\" (id,\"Пользователь\",\"Документ\") values ('%1','%2','%3')").arg(uuidDoc.toString()).arg(uuidNewUser.toString()).arg(uuidSert.toString());
        execMainBDQueryUpdate(strExec);

        /*Телефон*/
        QUuid uuidPhone = QUuid::createUuid();
        strExec = QString("insert into \"Пользователь-Телефоны\" (id , \"Пользователь\" , \"Номер\" ) values ('%1' , '%2' , '%3')").arg(uuidPhone.toString()).arg(uuidNewUser.toString()).arg(m_pPhoneLineText->getText());
        execMainBDQueryUpdate(strExec);

        accept();
    }
}
