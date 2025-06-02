#include "qcswashtypeselectdlg.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QDateTime>
#include <QUuid>
#include "common.h"
#include <QScrollArea>
#include <QScroller>
#include <QPushButton>

extern QRect screenGeometry;
extern QUuid uuidCurrentUser;
extern int iButtonHeight;
extern UserTypes CurrentUserType;

QCSWashTypeSelectDlg::QCSWashTypeSelectDlg(QWidget *parent, Qt::WindowFlags f ):QCSBaseDialog(parent , f , false)
{
    QVBoxLayout * pVMainLayout = new QVBoxLayout;
    this->setLayout(pVMainLayout);

    m_pTopLabel = new QLabel(QString("<b>Задачи мойки</b>"));
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



    QPushButton * pApplyButton = new QPushButton("Внести/выбрать");
    pApplyButton->setIcon(QIcon(":/icons/done_icon.png"));
    pApplyButton->setIconSize(QSize(iButtonHeight*0.75 , iButtonHeight*0.75));
    pVMainLayout->addWidget(pApplyButton);
    connect(pApplyButton,SIGNAL(released()),this,SLOT(OnApplyPressedSlot()));

    setMinimumHeight(screenGeometry.height());

}

void QCSWashTypeSelectDlg::OnApplyPressedSlot()
{
    accept();
}
