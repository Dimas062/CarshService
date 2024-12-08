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


    // QColor redColor = QColor("PeachPuff");
    // QColor greenColor = QColor("LightGreen");
    // QBrush redBrush(redColor);
 //   QBrush greenBrush(greenColor);
//    QLinearGradient gradient(1,6,1,6);
//    gradient.setColorAt(0,redColor);
//    //gradient.setColorAt(0.499,redColor);
//    //gradient.setColorAt(0.5,greenColor);
//    gradient.setColorAt(1,greenColor);
//    QBrush red_greenBrush(gradient);
//    QSet<QDate> setRedDates;

    // if(type==CalendarTypes::DayTodos)
    // {
    //      QString queryString = QString("select DateTime,IsDone from DayTodos");

    //      QSqlQuery query;

    //      if(query.exec(queryString))
    //      {
    //          while(query.next())
    //          {
    //              QDate date = QDateTime::fromSecsSinceEpoch(query.value(0).toInt()).date();
    //              if(setRedDates.find(date) == setRedDates.end()) //Если дата один раз помечена как красная(есть не выполненнные задания), то следующие разы её не рассматриваем
    //              {
    //                  QTextCharFormat format;
    //                  if(query.value(1).toInt() == 0)
    //                  {
    //                      format.setBackground(redBrush);
    //                      setRedDates.insert(date);
    //                  }
    //                  else format.setBackground(greenBrush);
    //                  m_pCalendarWidget->setDateTextFormat(date , format);
    //              }
    //          }
    //      }

    //      queryString = QString("select DateTime from Notifications");
    //      if(query.exec(queryString))
    //      {
    //          while(query.next())
    //          {
    //              QDate date = QDateTime::fromSecsSinceEpoch(query.value(0).toInt()).date();
    //              m_pCalendarWidget->m_Props[date].bIsAlarmSeted = true;
    //          }
    //      }

    // }

    //m_pCalendarWidget->setFixedWidth(screenGeometry.width()*0.9);
    m_pCalendarWidget->setFixedHeight(screenGeometry.height()*0.5); //считаем, что по центру и по 150 сверху и снизу под рекламу
    m_pCalendarWidget->setGridVisible(true);

    m_pCalendarWidget->setNavigationBarVisible(false);

    pMainVLayout->addStretch();

    UpdateDateLabel();
}

void QCalendarDataSelectDlg::SetDatesPros(QMap<QDate, sDateProps> Props)
{

    m_pCalendarWidget->m_Props = Props;
}

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
