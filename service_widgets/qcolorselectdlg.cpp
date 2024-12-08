#include "qcolorselectdlg.h"
#include <QGridLayout>
#include <QPushButton>
#include <QVariant>
#include <QMessageBox>

#include <QGesture>

double iButtonSize;

QColorSelectDlg::QColorSelectDlg(QWidget *parent, Qt::WindowFlags f):QDialog(parent , f)
{
    QGridLayout * pMainGridLayout = new QGridLayout();
    this->setLayout(pMainGridLayout);

   // setStyleSheet("{background-color: transparent;}");


  //  this->setGeometry(0,0,200,400);

    //TODO: Сделать нормальные размеры
    iButtonSize = 70;


    const int iButtonWidth = iButtonSize;
    const int iButtonHeight = iButtonSize;

    //m_pColorWidget = new QColorWidget(this);
    //connect(m_pColorWidget, SIGNAL(clicked(QDate)), this, SLOT(OnClickedDay(QDate)));

    QColor tempColor = QColor(QColorConstants::Svg::mediumblue);
    QPushButton * pColorButton11 = new QPushButton();
    pColorButton11->setStyleSheet(QString("background-color: %1").arg(tempColor.name()));
    pColorButton11->setProperty("color" , QVariant(tempColor));
    connect(pColorButton11,SIGNAL(pressed()),this,SLOT(OnColorPress()));
    pColorButton11->setMinimumHeight(iButtonHeight);
    pColorButton11->setMinimumWidth(iButtonWidth);
    pMainGridLayout->addWidget(pColorButton11 , 1 ,1);

    tempColor = QColor(QColorConstants::Svg::fuchsia);
    QPushButton * pColorButton12 = new QPushButton();
    pColorButton12->setStyleSheet(QString("background-color: %1").arg(tempColor.name()));
    pColorButton12->setProperty("color" , QVariant(tempColor));
    connect(pColorButton12,SIGNAL(pressed()),this,SLOT(OnColorPress()));
    pColorButton12->setMinimumHeight(iButtonHeight);
    pColorButton12->setMinimumWidth(iButtonWidth);
    pMainGridLayout->addWidget(pColorButton12 , 1 ,2);

    tempColor = QColor(QColorConstants::Svg::burlywood);
    QPushButton * pColorButton13 = new QPushButton();
    pColorButton13->setStyleSheet(QString("background-color: %1").arg(tempColor.name()));
    pColorButton13->setProperty("color" , QVariant(tempColor));
    connect(pColorButton13,SIGNAL(pressed()),this,SLOT(OnColorPress()));
    pColorButton13->setMinimumHeight(iButtonHeight);
    pColorButton13->setMinimumWidth(iButtonWidth);
    pMainGridLayout->addWidget(pColorButton13 , 1 ,3);

    tempColor = QColor(QColorConstants::Svg::lightsteelblue);
    QPushButton * pColorButton14 = new QPushButton();
    pColorButton14->setStyleSheet(QString("background-color: %1").arg(tempColor.name()));
    pColorButton14->setProperty("color" , QVariant(tempColor));
    connect(pColorButton14,SIGNAL(pressed()),this,SLOT(OnColorPress()));
    pColorButton14->setMinimumHeight(iButtonHeight);
    pColorButton14->setMinimumWidth(iButtonWidth);
    pMainGridLayout->addWidget(pColorButton14 , 1 ,4);

    tempColor = QColor(QColorConstants::Svg::lightgreen);
    QPushButton * pColorButton21 = new QPushButton();
    pColorButton21->setStyleSheet(QString("background-color: %1").arg(tempColor.name()));
    pColorButton21->setProperty("color" , QVariant(tempColor));
    connect(pColorButton21,SIGNAL(pressed()),this,SLOT(OnColorPress()));
    pColorButton21->setMinimumHeight(iButtonHeight);
    pColorButton21->setMinimumWidth(iButtonWidth);
    pMainGridLayout->addWidget(pColorButton21 , 2 ,1);

    tempColor = QColor(QColorConstants::Svg::lightskyblue);
    QPushButton * pColorButton22 = new QPushButton();
    pColorButton22->setStyleSheet(QString("background-color: %1").arg(tempColor.name()));
    pColorButton22->setProperty("color" , QVariant(tempColor));
    connect(pColorButton22,SIGNAL(pressed()),this,SLOT(OnColorPress()));
    pColorButton22->setMinimumHeight(iButtonHeight);
    pColorButton22->setMinimumWidth(iButtonWidth);
    pMainGridLayout->addWidget(pColorButton22 , 2 ,2);

    tempColor = QColor(QColorConstants::Svg::mediumseagreen);
    QPushButton * pColorButton23 = new QPushButton();
    pColorButton23->setStyleSheet(QString("background-color: %1").arg(tempColor.name()));
    pColorButton23->setProperty("color" , QVariant(tempColor));
    pColorButton23->setMinimumHeight(iButtonHeight);
    pColorButton23->setMinimumWidth(iButtonWidth);
    connect(pColorButton23,SIGNAL(pressed()),this,SLOT(OnColorPress()));
    pMainGridLayout->addWidget(pColorButton23 , 2 ,3);

    tempColor = QColor(QColorConstants::Svg::olive);
    QPushButton * pColorButton24 = new QPushButton();
    pColorButton24->setStyleSheet(QString("background-color: %1").arg(tempColor.name()));
    pColorButton24->setProperty("color" , QVariant(tempColor));
    connect(pColorButton24,SIGNAL(pressed()),this,SLOT(OnColorPress()));
    pColorButton24->setMinimumHeight(iButtonHeight);
    pColorButton24->setMinimumWidth(iButtonWidth);
    pMainGridLayout->addWidget(pColorButton24 , 2 ,4);

    tempColor = QColor(QColorConstants::Svg::orange);
    QPushButton * pColorButton31 = new QPushButton();
    pColorButton31->setStyleSheet(QString("background-color: %1").arg(tempColor.name()));
    pColorButton31->setProperty("color" , QVariant(tempColor));
    pColorButton31->setMinimumHeight(iButtonHeight);
    pColorButton31->setMinimumWidth(iButtonWidth);
    connect(pColorButton31,SIGNAL(pressed()),this,SLOT(OnColorPress()));
    pMainGridLayout->addWidget(pColorButton31 , 3 ,1);

    tempColor = QColor(QColorConstants::Svg::tomato);
    QPushButton * pColorButton32 = new QPushButton();
    pColorButton32->setStyleSheet(QString("background-color: %1").arg(tempColor.name()));
    pColorButton32->setProperty("color" , QVariant(tempColor));
    pColorButton32->setMinimumHeight(iButtonHeight);
    pColorButton32->setMinimumWidth(iButtonWidth);
    connect(pColorButton32,SIGNAL(pressed()),this,SLOT(OnColorPress()));
    pMainGridLayout->addWidget(pColorButton32 , 3 ,2);

    tempColor = QColor(QColorConstants::Svg::darkgray);
    QPushButton * pColorButton33 = new QPushButton();
    pColorButton33->setStyleSheet(QString("background-color: %1").arg(tempColor.name()));
    pColorButton33->setProperty("color" , QVariant(tempColor));
    connect(pColorButton33,SIGNAL(pressed()),this,SLOT(OnColorPress()));
    pColorButton33->setMinimumHeight(iButtonHeight);
    pColorButton33->setMinimumWidth(iButtonWidth);
    pMainGridLayout->addWidget(pColorButton33 , 3 ,3);

    /*Кнопка прозрачности (реально записываем чёрный 0,0,0 цвет*/
    tempColor = QColor(0,0,0);
    QPushButton * pColorButton34 = new QPushButton();
    //pColorButton34->setStyleSheet(QString("background-color: %1").arg(tempColor.name()));
    pColorButton34->setProperty("color" , QVariant(tempColor));
    connect(pColorButton34,SIGNAL(pressed()),this,SLOT(OnColorPress()));
    pColorButton34->setMinimumHeight(iButtonHeight);
    pColorButton34->setMinimumWidth(iButtonWidth);
    pMainGridLayout->addWidget(pColorButton34 , 3 ,4);

}


void QColorSelectDlg::OnColorPress()
{
    QPushButton * pColorButton = (QPushButton *)sender();
    m_Color = (pColorButton->property("color")).value<QColor>();
    accept();
}

