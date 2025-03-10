#include "qregisterpartnerWashdlg.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QGuiApplication>
#include <QKeyEvent>
#include <QPushButton>
#include <common.h>
#include <QString>

#include "service_widgets/qcsselectdialog.h"

extern QRect screenGeometry;

QRegisterPartnerWashDlg::QRegisterPartnerWashDlg(QWidget *parent, Qt::WindowFlags f ):QCSBaseDialog(parent , f)
{
    QVBoxLayout * pVMainLayout = new QVBoxLayout;


    pVMainLayout->addSpacing(5);
    QLabel *  pTopLabel = new QLabel(QString("<b>Регистрация партнера Мойка</b>"));
    pTopLabel->setStyleSheet("font-size: 20px;");
    pVMainLayout->addWidget(pTopLabel);

    m_pULButton = new QPushButton("Данные ЮЛ");
    connect(m_pULButton,SIGNAL(pressed()),this,SLOT(OnUlPressedSlot()));
    pVMainLayout->addWidget(m_pULButton);

    m_pPointsButton = new QPushButton("Точки партнера");
    connect(m_pPointsButton,SIGNAL(pressed()),this,SLOT(OnPointsPressedSlot()));
    pVMainLayout->addWidget(m_pPointsButton);

    m_pPostavshikButton= new QPushButton("Заказчик");
    connect(m_pPostavshikButton,SIGNAL(pressed()),this,SLOT(OnPostavPressedSlot()));
    pVMainLayout->addWidget(m_pPostavshikButton);

    m_pLoginLineText = new QLineText("Логин");
    pVMainLayout->addWidget(m_pLoginLineText);

    m_pPasswordLineText = new QLineText("Пароль");
    pVMainLayout->addWidget(m_pPasswordLineText);

    pVMainLayout->addStretch();

    QPushButton * pApplyButton = new QPushButton("Отправить");
    connect(pApplyButton,SIGNAL(pressed()),this,SLOT(OnApplyPressed()));
    pVMainLayout->addWidget(pApplyButton);

    this->setLayout(pVMainLayout);
}

void QRegisterPartnerWashDlg::OnPointsPressedSlot()
{
    m_PointListdlg.exec();
    isReady();
}

void QRegisterPartnerWashDlg::OnUlPressedSlot()
{
    m_ULdlg.exec();
    isReady();
}

bool QRegisterPartnerWashDlg::isReady()
{
    bool retVal = true;

    if(m_strPostavId.length()<20)
    {
        m_pPostavshikButton->setStyleSheet("QPushButton {color: red;}");
        retVal = false;
    }
    else m_pPostavshikButton->setStyleSheet("QPushButton {color: black;}");

    if( (m_ULdlg.m_pNameLineText->getText().length()<3) || (m_ULdlg.m_pINNLineText->getText().length()<3))
    {
        m_pULButton->setStyleSheet("QPushButton {color: red;}");
        retVal = false;
    }
    m_pULButton->setStyleSheet("QPushButton {color: black;}");

    if(!m_pLoginLineText->CheckColorLenght()) retVal = false;
    if(!m_pPasswordLineText->CheckColorLenght()) retVal = false;


    return retVal;
}

void QRegisterPartnerWashDlg::OnPostavPressedSlot()
{
    QCSSelectDialog PostavSelDlg("Поставщики" , "Название");
    PostavSelDlg.selectWidget.SelectId(m_strPostavId);
    if(PostavSelDlg.exec()==QDialog::Accepted)
    {
        m_strPostavId = PostavSelDlg.getCurId();
        m_strPostavText = PostavSelDlg.getCurText();
        isReady();
    }
}

void QRegisterPartnerWashDlg::OnApplyPressed()
{
    if(isReady())
    {
        showWait(true);

        QUuid newParnerId = QUuid::createUuid();

        QUuid idUl = m_ULdlg.SaveOrCreateToBD(QUuid());

        m_PointListdlg.SaveUpdateToBD(newParnerId);

        QString strInsExec = QString("insert into Партнеры (id , Тип , ЮЛ , Поставщик , Логин, Пароль) values ('%1' , '932a4dc1-238b-478d-8911-3de46dd8da65' , '%2' , '%3' , '%4', '%5' )").arg(newParnerId.toString()).arg(idUl.toString()).arg(m_strPostavId).arg(m_pLoginLineText->getText()).arg(m_pPasswordLineText->getText());

        execMainBDQueryUpdate(strInsExec);

        showWait(false);

        accept();
    }
}


