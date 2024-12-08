#include "qtimeselectdlg.h"
#include <QHBoxLayout>
//#include <QSqlQuery>
#include <QDateTime>
#include <QTextCharFormat>
#include <QGuiApplication>
#include <QScreen>
#include <QKeyEvent>
#include <QSet>
#include "qapplication.h"
#include "qpushbutton.h"

extern double iButtonSize;

QTimeSelectDlg::QTimeSelectDlg(QTime startTime , QWidget *parent, Qt::WindowFlags f):QDialog(parent , f)
{
    QVBoxLayout * pMainVLayout = new QVBoxLayout();
    this->setLayout(pMainVLayout);

    m_bChildBackRealeseProcessed = true;
    m_bBackRelesaeProcessed = true;

    m_SelectedTime = startTime;

    const QRect screenGeometry = QGuiApplication::primaryScreen()->availableGeometry();
    QRect geometry(QPoint(0, 0), QSize(screenGeometry.width(), screenGeometry.height()));
    geometry.moveCenter(screenGeometry.center());
    setGeometry(geometry);

    pMainVLayout->setContentsMargins(15,25,15,0);
    pMainVLayout->addStretch();

    QHBoxLayout * pHHourLayout = new QHBoxLayout;

    QPushButton * pHourLeftButton = new QPushButton(QIcon(":/icons/arrow_left_icon.png"),"", this);
    pHourLeftButton->setMinimumHeight(iButtonSize*1.6);
    pHourLeftButton->setMinimumWidth(iButtonSize*1.5);
    pHHourLayout->addWidget(pHourLeftButton);
    connect(pHourLeftButton,SIGNAL(pressed()),this,SLOT(OnHourLeftPressed()));

    pHHourLayout->addStretch();

    m_pHourLabel = new QLabel();
    pHHourLayout->addWidget(m_pHourLabel);

    pHHourLayout->addStretch();

    QPushButton * pHourRightButton = new QPushButton(QIcon(":/icons/arrow_right_icon.png"),"", this);
    pHourRightButton->setMinimumHeight(iButtonSize*1.6);
    pHourRightButton->setMinimumWidth(iButtonSize*1.5);
    pHHourLayout->addWidget(pHourRightButton);
    connect(pHourRightButton,SIGNAL(pressed()),this,SLOT(OnHourRightPressed()));

    pMainVLayout->addLayout(pHHourLayout);

    QHBoxLayout * pHMinuteLayout = new QHBoxLayout;

    QPushButton * pMinuteLeftButton = new QPushButton(QIcon(":/icons/arrow_left_icon.png"),"", this);
    pMinuteLeftButton->setMinimumHeight(iButtonSize*1.6);
    pMinuteLeftButton->setMinimumWidth(iButtonSize*1.5);
    pHMinuteLayout->addWidget(pMinuteLeftButton);
    connect(pMinuteLeftButton,SIGNAL(pressed()),this,SLOT(OnMinuteLeftPressed()));

    pHMinuteLayout->addStretch();

    m_pMinuteLabel = new QLabel();
    pHMinuteLayout->addWidget(m_pMinuteLabel);

    pHMinuteLayout->addStretch();

    QPushButton * pMinuteRightButton = new QPushButton(QIcon(":/icons/arrow_right_icon.png"),"", this);
    pMinuteRightButton->setMinimumHeight(iButtonSize*1.6);
    pMinuteRightButton->setMinimumWidth(iButtonSize*1.5);
    pHMinuteLayout->addWidget(pMinuteRightButton);
    connect(pMinuteRightButton,SIGNAL(pressed()),this,SLOT(OnMinuteRightPressed()));

    pMainVLayout->addLayout(pHMinuteLayout);

    UpdateTimeWidgets();


    pMainVLayout->addStretch();

    QPushButton * pApplyButton = new QPushButton("Применить");
    connect(pApplyButton , SIGNAL(clicked()) , this , SLOT(OnApply()));

    pMainVLayout->addWidget(pApplyButton);


}

void QTimeSelectDlg::OnApply()
{
    accept();
}

void QTimeSelectDlg::UpdateTimeWidgets()
{
    m_pHourLabel->setText("<b>" + m_SelectedTime.toString("HH")+ " часов</b>");
    m_pHourLabel->setStyleSheet("font-size: 16px;");
    m_pMinuteLabel->setText("<b>" + m_SelectedTime.toString("mm") + " минут</b>");
    m_pMinuteLabel->setStyleSheet("font-size: 16px;");
}

void QTimeSelectDlg::OnHourLeftPressed()
{
    m_SelectedTime = m_SelectedTime.addSecs(-3600);
    UpdateTimeWidgets();
}

void QTimeSelectDlg::OnHourRightPressed()
{
    m_SelectedTime = m_SelectedTime.addSecs(3600);
    UpdateTimeWidgets();
}

void QTimeSelectDlg::OnMinuteLeftPressed()
{
    m_SelectedTime = m_SelectedTime.addSecs(300);
    UpdateTimeWidgets();
}

void QTimeSelectDlg::OnMinuteRightPressed()
{
    m_SelectedTime = m_SelectedTime.addSecs(300);
    UpdateTimeWidgets();
}

bool QTimeSelectDlg::event(QEvent *event)
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
