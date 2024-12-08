#ifndef QCOLORSELECTDLG_H
#define QCOLORSELECTDLG_H

#include <QDialog>
#include <QColorDialog>
#include <QGestureEvent>
class QColorSelectDlg : public QDialog
{
    Q_OBJECT
public:
    QColorSelectDlg(QWidget *parent = nullptr, Qt::WindowFlags f = Qt::WindowFlags());

    QColor m_Color;



public slots:
   void OnColorPress();



};

#endif // QCOLORSELECTDLG_H
