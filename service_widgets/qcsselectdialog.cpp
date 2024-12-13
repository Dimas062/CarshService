#include "qcsselectdialog.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QDateTime>
#include <QUuid>
#include "common.h"
#include <QScrollArea>
#include <QScroller>
#include "service_widgets/qclicablelabel.h"
#include "../carsh_service_widgets/qcarshserviceemploeecarddlg.h"


extern QRect screenGeometry;
extern QUuid uuidCurrentUser;
extern int iButtonHeight;
extern UserTypes CurrentUserType;

QCSSelectDialog::QCSSelectDialog(QString strTableName ,QString strColName ,  bool bChecable , bool bAutoChecable , QUuid uuidEmpl , QWidget *parent, Qt::WindowFlags f ):QCSBaseDialog(parent , f , false),selectWidget(strTableName , strColName , bChecable)
{
    QVBoxLayout * pVMainLayout = new QVBoxLayout;
    this->setLayout(pVMainLayout);

    m_userUUid = uuidEmpl;

    if(m_userUUid != QUuid())
    {
        pVMainLayout->addSpacing(5);

        QClicableLabel * pFioLabel = new QClicableLabel();

        if(CurrentUserType == CarshService)
            connect(pFioLabel , SIGNAL(clicked()) , this , SLOT(FioClicked()));

        pFioLabel->setAlignment(Qt::AlignHCenter);

        QString strFioOuery = QString("select Фамилия, Имя, Отчество from Пользователи where id='%1'").arg(m_userUUid.toString());

        QList<QStringList> res = execMainBDQuery(strFioOuery);

        if(res.size()>0)
        {
            pFioLabel->setStyleSheet("font-size: 20px;\
                                     color: black;");
            pFioLabel->setText(QString("<b>%1 %2 %3</b>").arg(res.at(0).at(0)).arg(res.at(0).at(1)).arg(res.at(0).at(2)));
        }

        pVMainLayout->addWidget(pFioLabel);
    }

   // pVMainLayout->addSpacing(5);
    m_pTopLabel = new QLabel(QString("<b>%1</b>").arg(strTableName));
    m_pTopLabel->setStyleSheet("font-size: 20px;\
                                     color: black;");
    m_pTopLabel->setAlignment(Qt::AlignHCenter);
    pVMainLayout->addWidget(m_pTopLabel);

    QScrollArea * pScrollArea = new QScrollArea(this);
    pScrollArea->setAlignment(Qt::AlignHCenter);

    pScrollArea->setVerticalScrollBarPolicy( Qt::ScrollBarAlwaysOff );


    pScrollArea->setHorizontalScrollBarPolicy( Qt::ScrollBarAlwaysOff );

    pScrollArea->setWidget(&selectWidget);

    QScroller::grabGesture(pScrollArea->viewport(), QScroller::TouchGesture);


    pVMainLayout->addWidget(pScrollArea);


    /*Попросили отключить автозакрытие при выборе*/
    if(bAutoChecable)
        connect(&selectWidget, SIGNAL(ButtonPushed()), this,SLOT(OnApplyPressedSlot()));
    else
    {
        QPushButton * pApplyButton = new QPushButton("Внести/выбрать");
        pApplyButton->setIcon(QIcon(":/icons/done_icon.png"));
        pApplyButton->setIconSize(QSize(iButtonHeight*0.75 , iButtonHeight*0.75));
        pVMainLayout->addWidget(pApplyButton);
        connect(pApplyButton,SIGNAL(released()),this,SLOT(OnApplyPressedSlot()));
    }


}

void QCSSelectDialog::FioClicked()
{
    QCarshServiceEmploeeCardDlg dlg(m_userUUid);
    dlg.exec();
}

void QCSSelectDialog::OnApplyPressedSlot()
{
    accept();
}
