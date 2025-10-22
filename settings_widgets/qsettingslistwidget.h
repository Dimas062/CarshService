#ifndef QSETTINGSLISTWIDGET_H
#define QSETTINGSLISTWIDGET_H

#include <QWidget>
#include <QGestureEvent>
#include "service_widgets/qcslineedit.h"

class QSettingsListWidget : public QWidget
{
    Q_OBJECT
public:
    QSettingsListWidget(QWidget *parent = nullptr);

    bool gestureEvent(QGestureEvent *event);
    bool event(QEvent *event);
    void showEvent( QShowEvent* event );

    void addWidget(QWidget *);

    //QCSLineEdit * m_pAdressLineEdit;
    QCSLineEdit * m_pLoginLineEdit;
    QCSLineEdit * m_pPasswordLineEdit;

public slots:
    void OnClearTempPressed();

signals:
    void OnTapHoldGesture();
    void OnTapGesture();

};

#endif // QSETTINGSLISTWIDGET_H
