#include "qcsbasedialog.h"
#include <QGuiApplication>
#include <QKeyEvent>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QScroller>
#include <QPushButton>

extern QRect screenGeometry;
extern QColor currentWorkdayColor;

QCSBaseDialog::QCSBaseDialog(QWidget *parent, Qt::WindowFlags f , bool bScrollable):QDialog(parent , f)
{
    pCSMainLayout = new QVBoxLayout(this);

    m_bScrollable = bScrollable;
    m_bBackProcessed = true;
    connect(this , SIGNAL(OnMouseButtonPressedSignal()) , this , SLOT(OnMouseButtonPressedSlot()));


    QRect geometry(QPoint(0, 0), QSize(screenGeometry.width() , screenGeometry.height() ));
    geometry.moveCenter(screenGeometry.center());
    setGeometry(geometry);

    // setMinimumSize ( geometry.size() ) ;
    // setMaximumSize ( geometry.size() ) ;
    // setSizePolicy ( QSizePolicy :: Fixed , QSizePolicy :: Fixed ) ;

    if(m_bScrollable)
    {
        m_pScrollWidget = NULL;

        m_pScrollArea = new QCSScrollArea();
        m_pScrollArea->setAlignment(Qt::AlignHCenter);

        m_pScrollArea->setVerticalScrollBarPolicy( Qt::ScrollBarAlwaysOff );

        m_pScrollArea->setHorizontalScrollBarPolicy( Qt::ScrollBarAlwaysOff );


       // pScrollArea->setWidget(m_pSettingsListWidget);
        //pTestLabel->grabGesture(Qt::TapGesture);

       // QScroller::grabGesture(m_pScrollArea, QScroller::LeftMouseButtonGesture);
       // GrabGesture();

        //pCSMainLayout->addWidget(m_pScrollArea);
    }

    QDialog::setLayout(pCSMainLayout);

    //макось оказалась ... - закрытие диалога обычной кнопкой, системной кнопки назад нет
#if defined Q_OS_IOS || defined Q_OS_WINDOWS
    QHBoxLayout * pHBackButtonLayout = new QHBoxLayout(this);

    QPushButton * pBackButton = new QPushButton("<< Назад");
    pBackButton->setStyleSheet("font-size: 18px;\
                                color: Blue;\
                                border: 1px;\
                                background-color: #fdfdf0;\
                                padding: 1px 1px;");
    pHBackButtonLayout->addWidget(pBackButton);
    pHBackButtonLayout->addStretch();

    connect(pBackButton,SIGNAL(pressed()),this,SLOT(reject()));

    pCSMainLayout->addLayout(pHBackButtonLayout);
#endif
}

void QCSBaseDialog::setLayout(QLayout *layout)
{
    if(m_bScrollable)
    {
        if(!m_pScrollWidget) m_pScrollWidget = new QCSBaseDlgScrollWidget(this);
        m_pScrollWidget->setLayout(layout);
        m_pScrollArea->setWidget(m_pScrollWidget);
        QScroller::grabGesture(m_pScrollArea->viewport(), QScroller::TouchGesture);
        pCSMainLayout->addWidget(m_pScrollArea);


        //QVBoxLayout * pVMainLayout = new QVBoxLayout(this);
        //QDialog::setLayout(pVMainLayout);

    }
    else /*QDialog::setLayout(layout)*/ pCSMainLayout->addLayout(layout);
}


void QCSBaseDialog::OnMouseButtonPressedSlot()
{
    qApp->inputMethod()->hide();
}

bool QCSBaseDialog::eventFilter(QObject *obj, QEvent *event)
{

    if (event->type() == QEvent::MouseButtonPress)
    {
        return true;
    }
    else
    {
        // standard event processing
        return QObject::eventFilter(obj, event);
    }
}

bool QCSBaseDialog::event(QEvent *event)
{
    if(((QKeyEvent *)event)->key() == Qt::Key_Back)
    {
        if(event->type()==QEvent::KeyPress)
        {
            m_bBackProcessed = false;
            reject();

            return true;
        }
        if(event->type()==QEvent::KeyRelease)
        {
            m_bBackProcessed = true;
            return true;
        }
    }

    if(event->type()==QEvent::/*KeyRelease*/KeyPress)
        if(((QKeyEvent *)event)->key() == Qt::Key_Return)
        {
            event->accept();
            return true;
        }

    if(event->type()==QEvent::MouseButtonPress)
    {
        emit OnMouseButtonPressedSignal();
        event->accept();
        return true;
    }

    return QDialog::event(event);

}

