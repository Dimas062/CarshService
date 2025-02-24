#ifndef QCSBASEDIALOG_H
#define QCSBASEDIALOG_H

#include <QDialog>
#include "qcsbasedlgscrollwidget.h"
#include "qcsscrollarea.h"
#include <QVBoxLayout>
#include <QPainter>

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
    QPixmap m_iconWait;

    QVBoxLayout * pCSMainLayout;

    void showWait(bool);//Отобразить иконку ожидания вместо интерфейса
    bool m_bWaiting;

protected:
    bool eventFilter(QObject *obj, QEvent *event) override;

protected:
    void paintEvent(QPaintEvent *event) override
    {
        QDialog::paintEvent(event); // Вызываем базовую реализацию

        if(m_bWaiting)
            if (!m_iconWait.isNull()) {
                QPainter painter(this);

                // Вычисляем позицию для отрисовки иконки по центру
                int x = (width() - m_iconWait.width()) / 2;
                int y = (height() - m_iconWait.height()) / 2;

                // Рисуем иконку
                painter.drawPixmap(x, y, m_iconWait);
            }
    }

signals:
    void OnMouseButtonPressedSignal();

public slots:
    void OnMouseButtonPressedSlot();
};

#endif // QCSBASEDIALOG_H
