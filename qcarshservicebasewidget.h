#ifndef QCARSHSERVICEBASEWIDGET_H
#define QCARSHSERVICEBASEWIDGET_H

#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include "service_widgets/qcslineedit.h"
#ifdef Q_OS_ANDROID
#include <QJniObject>
#endif
#include <QLineEdit>

class QCarshServiceBaseWidget : public QWidget
{
    Q_OBJECT
public:
    QCarshServiceBaseWidget(QWidget *parent = nullptr);


    bool event(QEvent *event);
    bool m_bChildBackRealeseProcessed;

protected:
    void showEvent( QShowEvent* event );

   // QLineEdit * m_pLoginLineEdit;
    QCSLineEdit * m_pLoginLineEdit;
    QCSLineEdit * m_pPasswordLineEdit;

    QLabel * m_pStatusLabel;

#ifdef Q_OS_ANDROID
    QJniObject* m_Activity;
#endif

signals:
    void OnMouseButtonPressedSignal();

public slots:
    void OnMouseButtonPressedSlot();
    void OnSettingsModePressed();
    void OnLoginPressed();
    void OnRegisterPressed();
    void OnTestModePressed();
   // void OnServerConnectStatusChanged(QString);
};

#endif // QCARSHSERVICEBASEWIDGET_H
