#include "common.h"
#include "qsettingsdlg.h"
#include <QLabel>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QScreen>
#include <QKeyEvent>
#include <QGuiApplication>
#include <QScroller>
#include <QScrollBar>
#include <QEasingCurve>
#include <QSqlQuery>
#include <QSqlDatabase>

#include <QScrollArea>

extern QSqlDatabase ClientDb;
extern VSMobileSettings settings;

QSettingsDlg::QSettingsDlg(QWidget *parent, Qt::WindowFlags f):QCSBaseDialog(parent , f)
{
   //  QScrollArea * pScrollArea = new QScrollArea(this);
   //  pScrollArea->setAlignment(Qt::AlignHCenter);
   // // pScrollArea->grabGesture(Qt::TapGesture);


   //  pScrollArea->setVerticalScrollBarPolicy( Qt::ScrollBarAlwaysOff );


   //  pScrollArea->setHorizontalScrollBarPolicy( Qt::ScrollBarAlwaysOff );

   //  m_pSettingsListWidget = new QSettingsListWidget(this);
   //  pScrollArea->setWidget(m_pSettingsListWidget);
   // //pTestLabel->grabGesture(Qt::TapGesture);

   //  QScroller::grabGesture(pScrollArea->viewport(), QScroller::LeftMouseButtonGesture);


    QVBoxLayout * pVMainLayout = new QVBoxLayout(this);


    //pVMainLayout->addWidget(pScrollArea);
    m_pSettingsListWidget = new QSettingsListWidget(this);
    pVMainLayout->addWidget(m_pSettingsListWidget);


    QPushButton * pApplyButton = new QPushButton("Применить");
    connect(pApplyButton , SIGNAL(clicked()) , this , SLOT(OnApply()));

    pVMainLayout->addWidget(pApplyButton);

    this->setLayout(pVMainLayout);
    //pCSMainLayout->addItem(pVMainLayout);
}


void QSettingsDlg::OnApply()
{
    QString strQueryExec;
    QSqlQuery query(ClientDb);

    // strQueryExec = QString("update Settings set Value='%1' where Name='Host'").arg(m_pSettingsListWidget->m_pAdressLineEdit->text());
    // query.exec(strQueryExec);

    strQueryExec = QString("update Settings set Value='%1' where Name='Password'").arg(m_pSettingsListWidget->m_pPasswordLineEdit->text());
    query.exec(strQueryExec);

    strQueryExec = QString("update Settings set Value='%1' where Name='Login'").arg(m_pSettingsListWidget->m_pLoginLineEdit->text());
    query.exec(strQueryExec);

    // settings.strServAdress = m_pSettingsListWidget->m_pAdressLineEdit->text();
    settings.strServLogin = m_pSettingsListWidget->m_pLoginLineEdit->text();
    settings.strServPassword = m_pSettingsListWidget->m_pPasswordLineEdit->text();

    accept();
}
