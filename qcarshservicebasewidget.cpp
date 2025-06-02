#include "common.h"
#include "qsettingsdlg.h"
#include "qcarshservicebasewidget.h"
#include <QCoreApplication>
#include <QGuiApplication>
#include <QHBoxLayout>
#ifdef Q_OS_ANDROID
#include <QJniEnvironment>
#include <QJniObject>
#include <QtCore/private/qandroidextras_p.h>
#endif
#include <QLabel>
#include <QPushButton>
#include <QScreen>
#include <QVBoxLayout>

#include <private/qobject_p.h>
#include <qpa/qplatformnativeinterface.h>
#include "qregisterdlg.h"

#include <QUuid>
#include "carsh_service_widgets/qcarshservicemaindlg.h"
#include "emploee_widgets/qemploeemaindlg.h"
#include "partners/plates/qplatepartnermaindlg.h"
#include "partners/sticks/qstickpartnermaindlg.h"
#include "partners/wash/qwashpartnermaindlg.h"


QRect screenGeometry;
int iAndroidStatusBarHeigth;
int iWindowedVideoWidth = 0;
int iWindowedVideoHeigth = 0;
int iButtonHeight;

QUuid uuidCurrentUser;
extern QUuid uuidCurrentPartner;
extern UserTypes CurrentUserType;

extern VSMobileSettings settings;

extern QColor currentWorkdayColor;
extern QColor defaultBackColor;

QCarshServiceBaseWidget::QCarshServiceBaseWidget(QWidget *parent)
    : QWidget{parent}
{
 #ifdef Q_OS_ANDROID
    QPlatformNativeInterface* interface = QGuiApplication::platformNativeInterface();
    jobject activity = (jobject)interface->nativeResourceForIntegration("QtActivity");
    if (activity)
    {
        m_Activity = new QJniObject(activity);
    }
#endif
   // int iGetNaviPanelHegith = m_Activity->callMethod<jint>("GetNaviPanelHegith");

    screenGeometry = QGuiApplication::primaryScreen()->availableGeometry();

    uuidCurrentUser = QUuid();

    CurrentUserType = UndefinedUserType;

    //screenGeometry.adjust(0 , 0, 0 , -iGetNaviPanelHegith);

#if defined Q_OS_IOS || defined Q_OS_WINDOWS || defined Q_OS_MACOS

    int iUnderButtonSpace = 4;

    iButtonHeight = (int)((screenGeometry.height()*0.7)/12)-iUnderButtonSpace;
#endif

#ifdef Q_OS_ANDROID
    int iUnderButtonSpace = 10;

    iButtonHeight = (int)((screenGeometry.height()*0.7)/14)-iUnderButtonSpace;
#endif

    QVBoxLayout * pVMainLayout = new QVBoxLayout(this);
    this->setLayout(pVMainLayout);

    pVMainLayout->addSpacing(5);

    QLabel * pLogoLabel = new QLabel();
    QPixmap topIconPixmap(":/icons/CarshServiceIcon.png");
    pLogoLabel->setPixmap(topIconPixmap.scaled(70,70));
    pLogoLabel->setAlignment(Qt::AlignCenter);

    pVMainLayout->addWidget(pLogoLabel);

    QLabel * pLogoTextLabel = new QLabel ("Zlobin CarshService mobile");
    pLogoTextLabel->setAlignment(Qt::AlignCenter);
    pVMainLayout->addWidget(pLogoTextLabel);
    QLabel * pVersionTextLabel = new QLabel (QString("Версия: %1").arg(QCoreApplication::applicationVersion()));
    pVersionTextLabel->setAlignment(Qt::AlignCenter);
    pVMainLayout->addWidget(pVersionTextLabel);



    pVMainLayout->addSpacing(10);

    m_pStatusLabel = new QLabel(this);
    m_pStatusLabel->setAlignment(Qt::AlignCenter);
    m_pStatusLabel->setWordWrap(true);
    m_pStatusLabel->setMaximumWidth(screenGeometry.width()*0.8);
    pVMainLayout->addWidget(m_pStatusLabel);

    pVMainLayout->addStretch();

    QLabel * pLoginLabel = new QLabel("Логин");
    pVMainLayout->addWidget(pLoginLabel);

    m_pLoginLineEdit = new QCSLineEdit;
    pVMainLayout->addWidget(m_pLoginLineEdit);

    QLabel * pPasswordLabel = new QLabel("Пароль");
    pVMainLayout->addWidget(pPasswordLabel);

    m_pPasswordLineEdit = new QCSLineEdit;
    pVMainLayout->addWidget(m_pPasswordLineEdit);

    pVMainLayout->addStretch();

    pVMainLayout->addSpacing(iUnderButtonSpace);
    QPushButton * pLoginButton = new QPushButton("Вход");
    connect(pLoginButton,SIGNAL(pressed()),this,SLOT(OnLoginPressed()));
    pLoginButton->setMaximumHeight(iButtonHeight*2);
    pLoginButton->setMinimumHeight(iButtonHeight*2);
    pVMainLayout->addWidget(pLoginButton);


    pVMainLayout->addSpacing(iUnderButtonSpace);
    QPushButton * pRegisterButton = new QPushButton("Регистрация");
    connect(pRegisterButton,SIGNAL(pressed()),this,SLOT(OnRegisterPressed()));
    pRegisterButton->setMaximumHeight(iButtonHeight*2);
    pRegisterButton->setMinimumHeight(iButtonHeight*2);
    pVMainLayout->addWidget(pRegisterButton);

    pVMainLayout->addSpacing(iUnderButtonSpace);
    QPushButton * pSettingsModeButton = new QPushButton("Настройки");
    connect(pSettingsModeButton,SIGNAL(pressed()),this,SLOT(OnSettingsModePressed()));
    pSettingsModeButton->setMaximumHeight(iButtonHeight*2);
    pSettingsModeButton->setMinimumHeight(iButtonHeight*2);
    pVMainLayout->addWidget(pSettingsModeButton);


//    pVMainLayout->addSpacing(iUnderButtonSpace);
//    QPushButton * pTestModeButton = new QPushButton("Тест");
//    connect(pTestModeButton,SIGNAL(pressed()),this,SLOT(OnTestModePressed()));
//    pTestModeButton->setMaximumHeight(iButtonHeight*2);
//    pTestModeButton->setMinimumHeight(iButtonHeight*2);
//    pVMainLayout->addWidget(pTestModeButton);

    qApp->inputMethod()->hide();

    connect(this , SIGNAL(OnMouseButtonPressedSignal()) , this , SLOT(OnMouseButtonPressedSlot()));
    m_bChildBackRealeseProcessed = true;
}

void QCarshServiceBaseWidget::OnTestModePressed()
{
    QCSBaseDialog dlg;
    dlg.exec();
}


void QCarshServiceBaseWidget::OnMouseButtonPressedSlot()
{
    qApp->inputMethod()->hide();
}



void QCarshServiceBaseWidget::OnLoginPressed()
{
    QString strLoginStr;
    QString strPassStr;

    currentWorkdayColor = defaultBackColor;

    if((m_pLoginLineEdit->text().length() == 0)&&(m_pPasswordLineEdit->text().length() == 0))
    {
        strLoginStr=settings.strServLogin;
        strPassStr=settings.strServPassword;
    }
    else
    {
        strLoginStr = m_pLoginLineEdit->text();
        strPassStr = m_pPasswordLineEdit->text();
    }

    /*Поиск пользователя с заданным логином/паролем*/
    QString strUserExec = QString("select id , \"Роль\" , \"Подтвержден\" from Пользователи where Логин='%1' and Пароль='%2' and Удалено=false").arg(strLoginStr).arg(strPassStr);
    QList<QStringList> resUsers = execMainBDQuery(strUserExec);


    for(int iUserCounter = 0 ; iUserCounter < resUsers.size() ; iUserCounter++)
    {
        uuidCurrentUser = QUuid(resUsers.at(iUserCounter).at(0));

        if(resUsers.at(iUserCounter).at(2) == "f")
        {
            m_pStatusLabel->setText("<font color=\"red\">Ваша учётная запись не подтверждена или заблокирована</font>");
            Logging(QString("Попытка залогиниться с заблокированной учеткой логин:") +  strLoginStr + " пароль:"+strPassStr);
            return;
        }
        else m_pStatusLabel->setText(" ");



        if(QUuid(resUsers.at(iUserCounter).at(1)) == QUuid("80d4f275-0b41-40d5-b3d7-07f63a500a22")) //Каршсервис
        {
            CurrentUserType = CarshService;
            Logging(QString("Залогинился каршсервис логин:") +  strLoginStr + " пароль:"+strPassStr);
            QCarshServiceMainDlg dlg(NULL , /*Qt::Popup*/Qt::WindowFlags());

            m_bChildBackRealeseProcessed = false;
            dlg.exec();
            m_bChildBackRealeseProcessed = dlg.m_bBackProcessed;
            return;
        }

        if(QUuid(resUsers.at(iUserCounter).at(1)) == QUuid("80066f83-c025-410b-b439-f3e9b2299461")) //Сотрудник
        {
            CurrentUserType = Emploee;
            Logging(QString("Залогинился сотрудник логин:") +  strLoginStr + " пароль:"+strPassStr);
            QEmploeeMainDlg dlg(NULL , /*Qt::Popup*/Qt::WindowFlags());

            m_bChildBackRealeseProcessed = false;
            dlg.exec();
            m_bChildBackRealeseProcessed = dlg.m_bBackProcessed;
            return;
        }
    }

    /*Поиск партнера с заданным логином/паролем*/
    QString strPartnerExec = QString("select id , \"Подтвержден\" , Тип from Партнеры where Логин='%1' and Пароль='%2'  and Удалено=false").arg(strLoginStr).arg(strPassStr);
    QList<QStringList> resParners = execMainBDQuery(strPartnerExec);
    for(int iPartnerCounter = 0 ; iPartnerCounter < resParners.size() ; iPartnerCounter++)
    {
        uuidCurrentPartner = QUuid(resParners.at(iPartnerCounter).at(0));

        qDebug()<<"Подтвержден="<<resParners.at(iPartnerCounter).at(1);

        if(resParners.at(iPartnerCounter).at(1) == "f" || resParners.at(iPartnerCounter).at(1) == "false")
        {
            m_pStatusLabel->setText("<font color=\"red\">Ваша учётная запись не подтверждена или заблокирована</font>");
            return;
        }
        else m_pStatusLabel->setText(" ");

        if(QUuid(resParners.at(iPartnerCounter).at(2)) == QUuid("9c671ee9-2749-4717-a343-b18825855c29")) //Номера
        {
            CurrentUserType = PartnerPlate;
            Logging(QString("Залогинился партнер Номера логин:") +  strLoginStr + " пароль:"+strPassStr);
            QPlatePartnerMainDlg dlg;

            m_bChildBackRealeseProcessed = false;
            dlg.exec();
            m_bChildBackRealeseProcessed = dlg.m_bBackProcessed;
            return;
        }

        if(QUuid(resParners.at(iPartnerCounter).at(2)) == QUuid("082cf73c-6f6f-4167-ae89-b87c347091b2")) //Оклейка
        {
            CurrentUserType = PartnerStick;
            Logging(QString("Залогинился партнер Оклейка логин:") +  strLoginStr + " пароль:"+strPassStr);
            QStickPartnerMainDlg dlg;

            m_bChildBackRealeseProcessed = false;
            dlg.exec();
            m_bChildBackRealeseProcessed = dlg.m_bBackProcessed;
            return;
        }

        if(QUuid(resParners.at(iPartnerCounter).at(2)) == QUuid("932a4dc1-238b-478d-8911-3de46dd8da65")) //Мойка
        {
            CurrentUserType = PartnerWasher;
            Logging(QString("Залогинился партнер Мойка логин:") +  strLoginStr + " пароль:"+strPassStr);
            QWashPartnerMainDlg dlg;

            m_bChildBackRealeseProcessed = false;
            dlg.exec();
            m_bChildBackRealeseProcessed = dlg.m_bBackProcessed;
            return;
        }
    }


    Logging(QString("Неудачный логин логин:") +  strLoginStr + " пароль:"+strPassStr);
    m_pStatusLabel->setText("<font color=\"red\">Пользователь с заданным логином и паролем не найден</font>");
    return;

}

void QCarshServiceBaseWidget::OnRegisterPressed()
{
    QRegisterDlg dlg(NULL , /*Qt::Popup*/Qt::WindowFlags());

    m_bChildBackRealeseProcessed = false;
    dlg.exec();
    m_bChildBackRealeseProcessed = dlg.m_bBackProcessed;
}


void QCarshServiceBaseWidget::OnSettingsModePressed()
{
    //m_bChildBackRealeseProcessed = false;
    QSettingsDlg settDlg;
    int dlgRetVal = settDlg.exec();
    //m_bChildBackRealeseProcessed = settDlg.m_bBackProcessed;
    if(dlgRetVal == QDialog::Accepted)
    {
      //  QMetaObject::invokeMethod(&InteractionClient::getInstance() , "disconnect");//Переподключимся
    }

}

void QCarshServiceBaseWidget::showEvent( QShowEvent* e )
{
    qApp->inputMethod()->hide();
}

bool QCarshServiceBaseWidget::event(QEvent *event)
{
    if(event->type()==QEvent::MouseButtonPress)
    {
        emit OnMouseButtonPressedSignal();
    }

    if(((QKeyEvent *)event)->key() == Qt::Key_Back)
    {
        if(event->type()==QEvent::KeyRelease)
        {
            if(m_bChildBackRealeseProcessed == false)
            {
                m_bChildBackRealeseProcessed = true;
                return true;
            }
        }
    }
    return QWidget::event(event);
}

