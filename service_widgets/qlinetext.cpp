#include "qlinetext.h"
#include <QHBoxLayout>


extern QRect screenGeometry;


QLineText::QLineText(QString strLabel,QWidget *parent): QWidget{parent}
{
    QHBoxLayout * pHBoxLayout = new QHBoxLayout;
    this->setLayout(pHBoxLayout);
    m_pLabel = new QLabel(strLabel);
    pHBoxLayout->addWidget(m_pLabel);
    m_pLineEdit = new QLineEdit;

    m_pLineEdit->setFixedWidth(screenGeometry.width()*0.6);

    pHBoxLayout->addStretch();
    pHBoxLayout->addWidget(m_pLineEdit);
}

void QLineText::SetEnabled(bool bEnabled)
{
    m_pLabel->setEnabled(bEnabled);
    m_pLineEdit->setEnabled(bEnabled);
}


bool QLineText::CheckColorLenght()
{
    if(m_pLineEdit->text().size() < 1)
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

void QLineText::setText(QString text)
{
    m_pLineEdit->setText(text);
}

QString QLineText::getText() const
{
    return m_pLineEdit->text();
}
