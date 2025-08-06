#include "qcslineedit.h"
#include <QMenu>
#include <QGuiApplication>
#include <QClipboard>

QCSLineEdit::QCSLineEdit(QWidget *parent)
    : QLineEdit(parent) {
    // longPressTimer = new QTimer(this);
    // longPressTimer->setSingleShot(true);

    // setContextMenuPolicy(Qt::CustomContextMenu);
    // setInputMethodHints(
    //     Qt::ImhNoAutoUppercase |    // Отключить авто-заглавные буквы
    //     Qt::ImhNoPredictiveText |   // Отключить предиктивный ввод
    //     Qt::ImhNoTextHandles        // Отключить системные "ручки" (лупу/выделение)
    // );

    // connect(longPressTimer, &QTimer::timeout, [this]() {
    //     // Показать контекстное меню
    //     createStandardContextMenu()->exec(mapToGlobal(QPoint(0, height())));
    // });

    // 1. Разрешаем все системные обработчики ввода
    setAttribute(Qt::WA_InputMethodEnabled);

    // 2. Сбрасываем все ограничения ввода
    setInputMethodHints(Qt::ImhNone);

    // 3. Включаем обработку мультитач-событий
    setAttribute(Qt::WA_AcceptTouchEvents);

    // 4. Разрешаем системное контекстное меню
    setContextMenuPolicy(Qt::DefaultContextMenu);

    // 5. Включаем оптимизацию для мобильных устройств
    setAttribute(Qt::WA_StaticContents);
}

void QCSLineEdit::mousePressEvent(QMouseEvent *event) {

   // longPressTimer->start(longPressDuration);
    QLineEdit::mousePressEvent(event);
}

void QCSLineEdit::mouseReleaseEvent(QMouseEvent *event) {

  //  longPressTimer->stop();
    QLineEdit::mouseReleaseEvent(event);
}
