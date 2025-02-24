#include "qmonthselectdlg.h"
#include <QHBoxLayout>
#include <QSqlQuery>
#include <QDateTime>
#include <QTextCharFormat>
#include <QScreen>
#include <QSet>
#include <QKeyEvent>
#include "qapplication.h"
#include "qpushbutton.h"

extern double iButtonSize;
extern QRect screenGeometry;

QMonthSelectDlg::QMonthSelectDlg(QDate startDate , QWidget *parent, Qt::WindowFlags f):QDialog(parent , f)
{
    m_SelectedDate = startDate;
    
    QVBoxLayout * pMainVLayout = new QVBoxLayout();
    this->setLayout(pMainVLayout);

    QHBoxLayout * pHYearLayout = new QHBoxLayout;

    QPushButton * pLeftYearButton = new QPushButton(QIcon(":/icons/arrow_left_icon.png"),"",this);
    pLeftYearButton->setMinimumHeight(iButtonSize);
    pLeftYearButton->setMinimumWidth(iButtonSize);
    connect(pLeftYearButton , SIGNAL(clicked()) , this , SLOT(OnLeftYearButton()));
    pHYearLayout->addWidget(pLeftYearButton);
    
    m_pYearLabel = new QLabel(QString("<h1>%1</h1>").arg(m_SelectedDate.year()));
    m_pYearLabel->setAlignment(Qt::AlignCenter);
    m_pYearLabel->setAlignment(Qt::AlignHCenter);
    pHYearLayout->addWidget(m_pYearLabel);
    


    QPushButton * pRightYearButton = new QPushButton(QIcon(":/icons/arrow_right_icon.png"),"",this);
    pRightYearButton->setMinimumHeight(iButtonSize);
    pRightYearButton->setMinimumWidth(iButtonSize);
    connect(pRightYearButton , SIGNAL(clicked()) , this , SLOT(OnRightYearButton()));
    pHYearLayout->addWidget(pRightYearButton);
    
    pMainVLayout->addLayout(pHYearLayout);
    
    QVBoxLayout * pVMonthsLayout = new QVBoxLayout();

    
    QHBoxLayout * pHMonths1Layout = new QHBoxLayout();

    QPushButton * pMonth1Button = new QPushButton("Янв.");
    pMonth1Button->setProperty("Month" , QVariant(1));
    connect(pMonth1Button,SIGNAL(pressed()),this,SLOT(OnMonthClicked()));
    pHMonths1Layout->addWidget(pMonth1Button);

    QPushButton * pMonth2Button = new QPushButton("Фев.");
    pMonth2Button->setProperty("Month" , QVariant(2));
    connect(pMonth2Button,SIGNAL(pressed()),this,SLOT(OnMonthClicked()));
    pHMonths1Layout->addWidget(pMonth2Button);

    QPushButton * pMonth3Button = new QPushButton("Март");
    pMonth3Button->setProperty("Month" , QVariant(3));
    connect(pMonth3Button,SIGNAL(pressed()),this,SLOT(OnMonthClicked()));
    pHMonths1Layout->addWidget(pMonth3Button);

    QPushButton * pMonth4Button = new QPushButton("Апр.");
    pMonth4Button->setProperty("Month" , QVariant(4));
    connect(pMonth4Button,SIGNAL(pressed()),this,SLOT(OnMonthClicked()));
    pHMonths1Layout->addWidget(pMonth4Button);

    pVMonthsLayout->addLayout(pHMonths1Layout);



    QHBoxLayout * pHMonths2Layout = new QHBoxLayout();

    QPushButton * pMonth5Button = new QPushButton("Май");
    pMonth5Button->setProperty("Month" , QVariant(5));
    connect(pMonth5Button,SIGNAL(pressed()),this,SLOT(OnMonthClicked()));
    pHMonths2Layout->addWidget(pMonth5Button);

    QPushButton * pMonth6Button = new QPushButton("Июнь");
    pMonth6Button->setProperty("Month" , QVariant(6));
    connect(pMonth6Button,SIGNAL(pressed()),this,SLOT(OnMonthClicked()));
    pHMonths2Layout->addWidget(pMonth6Button);

    QPushButton * pMonth7Button = new QPushButton("Июль");
    pMonth7Button->setProperty("Month" , QVariant(7));
    connect(pMonth7Button,SIGNAL(pressed()),this,SLOT(OnMonthClicked()));
    pHMonths2Layout->addWidget(pMonth7Button);

    QPushButton * pMonth8Button = new QPushButton("Авг.");
    pMonth8Button->setProperty("Month" , QVariant(8));
    connect(pMonth8Button,SIGNAL(pressed()),this,SLOT(OnMonthClicked()));
    pHMonths2Layout->addWidget(pMonth8Button);

    pVMonthsLayout->addLayout(pHMonths2Layout);


    QHBoxLayout * pHMonths3Layout = new QHBoxLayout();

    QPushButton * pMonth9Button = new QPushButton("Сен.");
    pMonth9Button->setProperty("Month" , QVariant(9));
    connect(pMonth9Button,SIGNAL(pressed()),this,SLOT(OnMonthClicked()));
    pHMonths3Layout->addWidget(pMonth9Button);

    QPushButton * pMonth10Button = new QPushButton("Окт.");
    pMonth10Button->setProperty("Month" , QVariant(10));
    connect(pMonth10Button,SIGNAL(pressed()),this,SLOT(OnMonthClicked()));
    pHMonths3Layout->addWidget(pMonth10Button);

    QPushButton * pMonth11Button = new QPushButton("Ной.");
    pMonth11Button->setProperty("Month" , QVariant(11));
    connect(pMonth11Button,SIGNAL(pressed()),this,SLOT(OnMonthClicked()));
    pHMonths3Layout->addWidget(pMonth11Button);

    QPushButton * pMonth12Button = new QPushButton("Дек.");
    pMonth12Button->setProperty("Month" , QVariant(12));
    connect(pMonth12Button,SIGNAL(pressed()),this,SLOT(OnMonthClicked()));
    pHMonths3Layout->addWidget(pMonth12Button);

    pVMonthsLayout->addLayout(pHMonths3Layout);

    
    pMainVLayout->addLayout(pVMonthsLayout);

    QPushButton * pCloseButton = new QPushButton("Отменить");
    connect(pCloseButton,SIGNAL(pressed()),this,SLOT(reject()));
    pMainVLayout->addWidget(pCloseButton);
}

void QMonthSelectDlg::OnMonthClicked()
{
    QPushButton * pButton = (QPushButton *)sender();
    int iMonth = (pButton->property("Month")).value<int>();

    m_SelectedDate.setDate(m_SelectedDate.year() , iMonth , 15);
    accept();
}

void QMonthSelectDlg::OnLeftYearButton()
{
    m_SelectedDate = m_SelectedDate.addYears(-1);
    m_pYearLabel->setText(QString("<h1>%1</h1>").arg(m_SelectedDate.year()));
}

void QMonthSelectDlg::OnRightYearButton()
{
    m_SelectedDate = m_SelectedDate.addYears(-1);
    m_pYearLabel->setText(QString("<h1>%1</h1>").arg(m_SelectedDate.year()));
}

bool QMonthSelectDlg::event(QEvent *event)
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
