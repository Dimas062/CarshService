#include "qcolumntext.h"
#include <QVBoxLayout>

extern QRect screenGeometry;

QColumnText::QColumnText(QString strLabel,QWidget *parent): QWidget{parent}
{
    QVBoxLayout * pVBoxLayout = new QVBoxLayout;
    this->setLayout(pVBoxLayout);
    m_pLabel = new QLabel(strLabel);
    pVBoxLayout->addWidget(m_pLabel);
    m_pLineEdit = new QLineEdit;
    m_pLineEdit->setFixedWidth(screenGeometry.width()*0.3);
    pVBoxLayout->addStretch();
    pVBoxLayout->addWidget(m_pLineEdit);
}

bool QColumnText::CheckColorLenght()
{
    if(m_pLineEdit->text().size()<3)
    {
        m_pLabel->setStyleSheet("QLabel { color : red; }");
        return false;
    }
    else
    {
        m_pLabel->setStyleSheet("QLabel { color : black; }");
    }
    return true;
}

QString QColumnText::getText() const
{
    return m_pLineEdit->text();
}
