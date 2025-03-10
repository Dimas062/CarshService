#include "QtPHPicker.h"
#include "PHPickerWrapper.h"

// Инициализация статической переменной
QtPHPicker* QtPHPicker::s_instance = nullptr;

QtPHPicker::QtPHPicker(QObject *parent) : QObject(parent) {
    PHPickerWrapper *wrapper = [[PHPickerWrapper alloc] init];
    m_wrapper = (__bridge_retained void *)wrapper;

    wrapper.filesSelected = [](const QStringList &paths) {
        if (s_instance) {
            emit s_instance->filesSelected(paths);
        }
    };
}

QtPHPicker::~QtPHPicker() {
    PHPickerWrapper *wrapper = (__bridge_transfer PHPickerWrapper *)m_wrapper;
    wrapper = nil;
    s_instance = nullptr;
}

// Определение метода instance()
QtPHPicker* QtPHPicker::instance() {
    if (!s_instance) {
        s_instance = new QtPHPicker();
    }
    return s_instance;
}

void QtPHPicker::openPicker(bool allowMultiple) {
    PHPickerWrapper *wrapper = (__bridge PHPickerWrapper *)m_wrapper;
    [wrapper openPHPickerWithMultipleSelection:allowMultiple];
}
