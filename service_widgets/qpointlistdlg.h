#ifndef QPOINTLISTDLG_H
#define QPOINTLISTDLG_H

#include "service_widgets/qcsbasedialog.h"
#include <QObject>
#include "service_widgets/qcsbaselistwidget.h"
#include <QUuid>
#include <QPushButton>

class QPointListDlg : public QCSBaseDialog
{
    Q_OBJECT
public:
    QPointListDlg(QWidget *parent = nullptr, Qt::WindowFlags f = Qt::WindowFlags());


    void LoadFromBD(QUuid uuidPartner);
    void SaveUpdateToBD(QUuid uuidPartner);
protected:
    QCSBaseListWidget * m_pPointsListWidget;
    QPushButton * m_pAddButton;
    QPushButton * m_pRemoveButton;


    QUuid m_uuidPartner;

public slots:

    void OnAddPressed();
    void OnRemovePressed();


    void OnTapGesture();
};

#endif // QPOINTLISTDLG_H
