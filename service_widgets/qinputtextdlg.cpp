#include "qinputtextdlg.h"
#include "QVBoxLayout"
#include "QHBoxLayout"
#include "QPushButton"
#include <QEasingCurve>
#include <QGuiApplication>


extern QRect screenGeometry;
extern int iButtonHeight;
QInputTextDlg::QInputTextDlg()
{
    QVBoxLayout * pVMainLayout = new QVBoxLayout;

    m_pTextLineEdit = new QCSLineEdit();

    pVMainLayout->addWidget(m_pTextLineEdit);

    QHBoxLayout * pHButtonsLayout = new QHBoxLayout;

    QPushButton * pInputButton = new QPushButton("Ввести");
    connect(pInputButton,SIGNAL(pressed()),this,SLOT(accept()));
    pInputButton->setFixedHeight(40);
    pHButtonsLayout->addWidget(pInputButton);

    QPushButton * pCloseButton = new QPushButton("Отменить");
    connect(pCloseButton,SIGNAL(pressed()),this,SLOT(reject()));
    pCloseButton->setFixedHeight(40);
    pHButtonsLayout->addWidget(pCloseButton);

    pVMainLayout->addLayout(pHButtonsLayout);

    this->setLayout(pVMainLayout);
}


QString QInputTextDlg::GetText() const
{
    if(m_pTextLineEdit != nullptr)
        return m_pTextLineEdit->text();
    return QString("");
}
