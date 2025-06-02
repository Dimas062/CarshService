#include "qcslineedit.h"
#include <QMenu>

QCSLineEdit::QCSLineEdit(QWidget *parent)
    : QLineEdit(parent) {
    longPressTimer = new QTimer(this);
    longPressTimer->setSingleShot(true);

    setContextMenuPolicy(Qt::CustomContextMenu);
    setInputMethodHints(
        Qt::ImhNoAutoUppercase |    // Отключить авто-заглавные буквы
        Qt::ImhNoPredictiveText |   // Отключить предиктивный ввод
        Qt::ImhNoTextHandles        // Отключить системные "ручки" (лупу/выделение)
    );

    connect(longPressTimer, &QTimer::timeout, [this]() {
        // Показать контекстное меню
        createStandardContextMenu()->exec(mapToGlobal(QPoint(0, height())));
    });
}

void QCSLineEdit::mousePressEvent(QMouseEvent *event) {

    longPressTimer->start(longPressDuration);
    QLineEdit::mousePressEvent(event);
}

void QCSLineEdit::mouseReleaseEvent(QMouseEvent *event) {

    longPressTimer->stop();
    QLineEdit::mouseReleaseEvent(event);
}
