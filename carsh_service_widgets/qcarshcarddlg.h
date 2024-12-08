#ifndef QCARSHCARDDLG_H
#define QCARSHCARDDLG_H

#include "service_widgets/qcsbasedialog.h"
#include <QObject>
#include <QUuid>
#include <QLabel>
#include <QPushButton>

class QCarshCardDlg : public QCSBaseDialog
{
    Q_OBJECT
public:
    QCarshCardDlg(QUuid uuidUser, QWidget *parent = nullptr, Qt::WindowFlags f = Qt::WindowFlags());
    QUuid m_userUuid;
protected:
    QLabel * m_pLabelActive;
    QPushButton * m_pActivationButton;
    bool m_IsActive;

public slots:
    void OnActivPressed();
    void OnRemovePressed();
};

#endif // QCARSHCARDDLG_H
