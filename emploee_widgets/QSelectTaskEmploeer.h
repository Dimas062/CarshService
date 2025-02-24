#ifndef QSelectTaskEmploeer_H
#define QSelectTaskEmploeer_H

#include "service_widgets/qcsbasedialog.h"
#include <QObject>
#include "service_widgets/qcsbaselistwidget.h"
#include <QUuid>
#include <QPushButton>

//Выбрать исполнителя задачи

class QSelectTaskEmploeer : public QCSBaseDialog
{
    Q_OBJECT
public:
    QSelectTaskEmploeer(QWidget *parent = nullptr, Qt::WindowFlags f = Qt::WindowFlags() , QString strUuidTask="");
    void UpdateEmplees();
protected:
    QPushButton * m_pApplyTaskButton;
    QCSBaseListWidget * m_pEmploeeListWidget;
    QString m_strUuidTask;

public slots:
    void OnApplyTaskPressed();

};

#endif // QSelectTaskEmploeer_H
