#include "qparnerpointdlg.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QDateTime>
#include <QUuid>
#include <QPushButton>

extern QRect screenGeometry;
extern QUuid uuidCurrentUser;
extern int iButtonHeight;
extern QColor currentWorkdayColor;

QParnerPointDlg::QParnerPointDlg(QWidget *parent, Qt::WindowFlags f ):QCSBaseDialog(parent , f)
{
    QVBoxLayout * pVMainLayout = new QVBoxLayout;

    QLabel *  pTopLabel = new QLabel("<b>Точки партнера</b>");
    pTopLabel->setStyleSheet("font-size: 20px;");
    pVMainLayout->addWidget(pTopLabel);

    m_pLineTextName = new QLineText("Название");
    pVMainLayout->addWidget(m_pLineTextName);

    m_pLineTextAddr = new QLineText("Адрес");
    pVMainLayout->addWidget(m_pLineTextAddr);

    QPushButton * pApplyButton = new QPushButton("Внести");
    pApplyButton->setIcon(QIcon(":/icons/done_icon.png"));
    pApplyButton->setIconSize(QSize(iButtonHeight*0.75 , iButtonHeight*0.75));

    pVMainLayout->addWidget(pApplyButton, 0 , Qt::AlignHCenter);
    connect(pApplyButton,SIGNAL(released()),this,SLOT(accept()));

    this->setLayout(pVMainLayout);
}
