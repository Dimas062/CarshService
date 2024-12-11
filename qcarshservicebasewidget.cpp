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
#include <QUuid>


QRect screenGeometry;
int iAndroidStatusBarHeigth;
int iWindowedVideoWidth = 0;
int iWindowedVideoHeigth = 0;
int iButtonHeight;

QUuid uuidCurrentUser;
UserTypes CurrentUserType;

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

#if defined Q_OS_IOS || defined Q_OS_WINDOWS

    int iUnderButtonSpace = 4;

    iButtonHeight = (int)((screenGeometry.height()*0.7)/10)-iUnderButtonSpace;
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

    m_pLoginLineEdit = new QLineEdit;
    pVMainLayout->addWidget(m_pLoginLineEdit);

    QLabel * pPasswordLabel = new QLabel("Пароль");
    pVMainLayout->addWidget(pPasswordLabel);


    m_pPasswordLineEdit = new QLineEdit;
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





    qApp->inputMethod()->hide();

    connect(this , SIGNAL(OnMouseButtonPressedSignal()) , this , SLOT(OnMouseButtonPressedSlot()));
    m_bChildBackRealeseProcessed = true;
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
    QString strUserExec = QString("select id , \"Роль\" , \"Подтвержден\" from Пользователи where Логин='%1' and Пароль='%2'").arg(strLoginStr).arg(strPassStr);
    QList<QStringList> resUsers = execMainBDQuery(strUserExec);


    for(int iUserCounter = 0 ; iUserCounter < resUsers.size() ; iUserCounter++)
    {
        uuidCurrentUser = QUuid(resUsers.at(iUserCounter).at(0));

        if(resUsers.at(iUserCounter).at(2) == "f")
        {
            m_pStatusLabel->setText("<font color=\"red\">Ваша учётная запись не подтверждена или заблокирована</font>");
            return;
        }
        else m_pStatusLabel->setText(" ");



        if(QUuid(resUsers.at(iUserCounter).at(1)) == QUuid("80d4f275-0b41-40d5-b3d7-07f63a500a22")) //Каршсервис
        {
            CurrentUserType = CarshService;
            QCarshServiceMainDlg dlg(NULL , /*Qt::Popup*/Qt::WindowFlags());

            m_bChildBackRealeseProcessed = false;
            dlg.exec();
            m_bChildBackRealeseProcessed = dlg.m_bBackProcessed;
            return;
        }
        if(QUuid(resUsers.at(iUserCounter).at(1)) == QUuid("ec3f998f-f5f4-4f2d-83a7-588934c58ecf")) //Служба каршеринга
        {

            return;
        }
        if(QUuid(resUsers.at(iUserCounter).at(1)) == QUuid("512c50c1-c4a9-4542-932a-55280886715a")) //Партнер номера
        {

            return;
        }
        if(QUuid(resUsers.at(iUserCounter).at(1)) == QUuid("4c476883-76b5-4f28-823a-966d69f51d46")) //Партнер оклейка
        {

            return;
        }
        if(QUuid(resUsers.at(iUserCounter).at(1)) == QUuid("184f8f60-a865-4bcf-996e-b26ff21d1ee3")) //Партнер мойка
        {

            return;
        }
        if(QUuid(resUsers.at(iUserCounter).at(1)) == QUuid("80066f83-c025-410b-b439-f3e9b2299461")) //Сотрудник
        {
            CurrentUserType = Emploee;
            QEmploeeMainDlg dlg(NULL , /*Qt::Popup*/Qt::WindowFlags());

            m_bChildBackRealeseProcessed = false;
            dlg.exec();
            m_bChildBackRealeseProcessed = dlg.m_bBackProcessed;
            return;
        }
    }
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

