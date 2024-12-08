#ifndef QSELPROVIDERCARSHWIDGET_H
#define QSELPROVIDERCARSHWIDGET_H

#include <QWidget>
#include <QPushButton>
#include <QUuid>

class QSelProviderCarshWidget : public QWidget
{
    Q_OBJECT
public:
    explicit QSelProviderCarshWidget(QUuid uuidProvider=QUuid() , QUuid uuidCarsh =QUuid() , QWidget *parent = nullptr);

    QPushButton * m_pProviderButton;
    QPushButton * m_pCarshButton;

    QUuid m_uuidProvider;
    QUuid m_uuidCarsh;

    bool isReadyColored();

public slots:
    void OnProviderPressedSlot();
    void OnCarshPressedSlot();

signals:
    void ProviderChanged();
    void CarshChanged();
};

#endif // QSELPROVIDERCARSHWIDGET_H
