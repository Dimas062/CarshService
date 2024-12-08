#include "QCSButton.h"
#include <QEvent>
#include <QKeyEvent>
#include <QTouchEvent>



QCSButton::QCSButton(QWidget *parent):QPushButton(parent)
{

}

QCSButton::QCSButton(const QString &text, QWidget *parent):QPushButton(text,parent)
{

}
QCSButton::QCSButton(const QIcon &icon, const QString &text, QWidget *parent ):QPushButton(icon , text , parent)
{

}


void QCSButton::mouseDoubleClickEvent()
{
    qDebug()<<"mouseDoubleClickEvent";
    emit doubleClicked();
}
