#include "qfinddlg.h"
#include "QVBoxLayout"
#include "QHBoxLayout"
#include "QPushButton"

QFindDlg::QFindDlg()
{
    QVBoxLayout * pVMainLayout = new QVBoxLayout;

    m_pTextLineEdit = new QLineEdit();

    pVMainLayout->addWidget(m_pTextLineEdit);

    QHBoxLayout * pHButtonsLayout = new QHBoxLayout;

    QPushButton * pFindButton = new QPushButton("Найти");
    connect(pFindButton,SIGNAL(pressed()),this,SLOT(accept()));
    pHButtonsLayout->addWidget(pFindButton);

    QPushButton * pCloseButton = new QPushButton("Отменить");
    connect(pCloseButton,SIGNAL(pressed()),this,SLOT(reject()));
    pHButtonsLayout->addWidget(pCloseButton);

    pVMainLayout->addLayout(pHButtonsLayout);

    this->setLayout(pVMainLayout);
}

QString QFindDlg::GetText() const
{
    if(m_pTextLineEdit != nullptr)
        return m_pTextLineEdit->text();
    return QString("");
}
