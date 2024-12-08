#ifndef QSETTINGSLISTWIDGET_H
#define QSETTINGSLISTWIDGET_H

#include <QWidget>
#include <QGestureEvent>
#include <QLineEdit>

class QSettingsListWidget : public QWidget
{
    Q_OBJECT
public:
    QSettingsListWidget(QWidget *parent = nullptr);

    bool gestureEvent(QGestureEvent *event);
    bool event(QEvent *event);
    void showEvent( QShowEvent* event );

    void addWidget(QWidget *);

    QLineEdit * m_pAdressLineEdit;
    QLineEdit * m_pLoginLineEdit;
    QLineEdit * m_pPasswordLineEdit;

signals:
    void OnTapHoldGesture();
    void OnTapGesture();
};

#endif // QSETTINGSLISTWIDGET_H
