#include "qcalendardataselectdlg.h"
#include <QHBoxLayout>
#include <QSqlQuery>
#include <QDateTime>
#include <QTextCharFormat>
#include <QScreen>
#include <QSet>
#include <QKeyEvent>
#include "qapplication.h"
#include "qpushbutton.h"

extern int iADHegith;
extern double iButtonSize;
extern QRect screenGeometry;

QCalendarDataSelectDlg::QCalendarDataSelectDlg(QDate startDate , QWidget *parent, Qt::WindowFlags f):QDialog(parent , f)
{
    QVBoxLayout * pMainVLayout = new QVBoxLayout();
    this->setLayout(pMainVLayout);

    m_SelectedDate = startDate;


    m_bChildBackRealeseProcessed = true;
    m_bBackRelesaeProcessed = true;


    QRect geometry(QPoint(0, 0), QSize(screenGeometry.width(), screenGeometry.height()));
    geometry.moveCenter(screenGeometry.center());
    setGeometry(geometry);

    pMainVLayout->setContentsMargins(15,25,15,0);
    pMainVLayout->addStretch();

    QHBoxLayout * pNavigationPanelLayout = new QHBoxLayout;
    QPushButton * pCalendarBackButton = new QPushButton(QIcon(":/icons/arrow_left_icon.png"),"", this);
    pCalendarBackButton->setMinimumHeight(iButtonSize);
    pCalendarBackButton->setMinimumWidth(iButtonSize*1.3);
    pNavigationPanelLayout->addWidget(pCalendarBackButton);
    connect(pCalendarBackButton,SIGNAL(pressed()),this,SLOT(OnCalendarBackPressed()));

    pNavigationPanelLayout->addStretch();

    m_pViewedDataLabel = new QLabel(this);
    pNavigationPanelLayout->addWidget(m_pViewedDataLabel);

    pNavigationPanelLayout->addStretch();

    pNavigationPanelLayout->setContentsMargins(10,0,10,0);

    QPushButton * pCalendarForwardButton = new QPushButton(QIcon(":/icons/arrow_right_icon.png"),"", this);
    pCalendarForwardButton->setMinimumHeight(iButtonSize);
    pCalendarForwardButton->setMinimumWidth(iButtonSize*1.3);
    pNavigationPanelLayout->addWidget(pCalendarForwardButton);
    connect(pCalendarForwardButton,SIGNAL(pressed()),this,SLOT(OnCalendarForwardPressed()));


    if(screenGeometry.width() < (140 + (80 + 10 + 15) *2))
    {

        int iButtonWidth = (screenGeometry.width() - 140 - ((10 + 10 + 15) *2))/2;

        pCalendarBackButton->setMinimumWidth(iButtonWidth);
        pCalendarForwardButton->setMinimumWidth(iButtonWidth);
        pCalendarBackButton->setMaximumWidth(iButtonWidth);
        pCalendarForwardButton->setMaximumWidth(iButtonWidth);
    }

    pMainVLayout->addLayout(pNavigationPanelLayout);

    m_pCalendarWidget = new QNoteCalendarWidget(this);
    m_pCalendarWidget->setSelectedDate(m_SelectedDate);
    connect(m_pCalendarWidget, SIGNAL(clicked(QDate)), this, SLOT(OnClickedDay(QDate)));


    pMainVLayout->addWidget(m_pCalendarWidget);


    m_pCalendarWidget->setFixedHeight(screenGeometry.height()*0.5); //считаем, что по центру и по 150 сверху и снизу под рекламу
    m_pCalendarWidget->setGridVisible(true);

    m_pCalendarWidget->setNavigationBarVisible(false);

    pMainVLayout->addStretch();

    UpdateDateLabel();
}

// void QCalendarDataSelectDlg::SetDatesPros(QMap<QDate, sDateProps> Props)
// {

//     m_pCalendarWidget->m_Props = Props;
// }

void QCalendarDataSelectDlg::UpdateDateLabel()
{
    m_pViewedDataLabel->setText(QString("%1 %2").arg(month(m_pCalendarWidget->monthShown())).arg((m_pCalendarWidget->yearShown())));
}

void QCalendarDataSelectDlg::OnCalendarBackPressed()
{
    m_pCalendarWidget->showPreviousMonth();
    UpdateDateLabel();
}

void QCalendarDataSelectDlg::OnCalendarForwardPressed()
{
     m_pCalendarWidget->showNextMonth();
     UpdateDateLabel();
}

void QCalendarDataSelectDlg::mousePressEvent(QMouseEvent *event)
{
    reject();
    QDialog::mousePressEvent(event);
}

void QCalendarDataSelectDlg::OnClickedDay(QDate date)
{
    m_SelectedDate = date;
    accept();
}

bool QCalendarDataSelectDlg::event(QEvent *event)
{
    if(((QKeyEvent *)event)->key() == Qt::Key_Back)
    {
        // if(event->type()==QEvent::ShortcutOverride)
        // {

        // }
        if(event->type()==QEvent::KeyRelease)
        {

            if(m_bChildBackRealeseProcessed == false)
            {
                m_bChildBackRealeseProcessed = true;
                return true;
            }
            m_bBackRelesaeProcessed = true;
            reject();
            return true;
        }
        if(event->type()==QEvent::KeyPress)
        {
            m_bBackRelesaeProcessed = false;
            return true;
        }
    }
    if(event->type()==QEvent::KeyPress)
        if(((QKeyEvent *)event)->key() == Qt::Key_Return)
        {
            return true;
        }

    return QDialog::event(event);
}
