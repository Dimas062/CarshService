#ifndef QCARSHSERVICEEMPLOEECARDDLG_H
#define QCARSHSERVICEEMPLOEECARDDLG_H

#include "service_widgets/qcsbasedialog.h"
#include <QObject>
#include <QUuid>
#include <QLabel>
#include <QPushButton>
#include "pictures/qpiclabel.h"

class QCarshServiceEmploeeCardDlg : public QCSBaseDialog
{
    Q_OBJECT
public:
    QCarshServiceEmploeeCardDlg(QUuid uuidUser, QWidget *parent = nullptr, Qt::WindowFlags f = Qt::WindowFlags());
    QUuid m_userUuid;
protected:
    QLabel * m_pLabelActive;
    QPushButton * m_pActivationButton;
    QPicLabel * m_pFotoPicLabel;
    QImage m_FotoImage;
    bool m_IsActive;
public slots:
    void OnDriverCardPressed();
    void OnPassportPressed();
    void OnSertPressed();
    void OnActivPressed();
   // void OnTasksPressed();
    void OnFotoPictureClik();
    void OnRemovePressed();

};

#endif // QCARSHSERVICEEMPLOEECARDDLG_H
