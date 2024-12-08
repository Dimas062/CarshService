#ifndef QCSBASEDIALOG_H
#define QCSBASEDIALOG_H

#include <QDialog>
#include "qcsbasedlgscrollwidget.h"
#include "qcsscrollarea.h"
#include <QVBoxLayout>

class QCSBaseDialog : public QDialog
{
    Q_OBJECT
public:
    QCSBaseDialog(QWidget *parent = nullptr, Qt::WindowFlags f = Qt::WindowFlags() , bool bScrollable = true);
    bool event(QEvent *event);
    bool m_bBackProcessed;
    void setLayout(QLayout *layout);
    QCSBaseDlgScrollWidget * m_pScrollWidget;
    QCSScrollArea * m_pScrollArea;
    bool m_bScrollable;

    QVBoxLayout * pCSMainLayout;

protected:
    bool eventFilter(QObject *obj, QEvent *event) override;

signals:
    void OnMouseButtonPressedSignal();

public slots:
    void OnMouseButtonPressedSlot();
};

#endif // QCSBASEDIALOG_H
