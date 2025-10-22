#include "QtPHPicker.h"
#include "PHPickerWrapper.h"
#include <QDir>
#include <QDebug>

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

void QtPHPicker::clearTempFiles() {
    // Получаем путь к временной директории iOS
    NSString *tempDir = NSTemporaryDirectory();
    QString qTempDir = QString::fromNSString(tempDir);

    QDir directory(qTempDir);
    if (!directory.exists()) {
        qDebug() << "Temp directory does not exist";
        return;
    }

    // Фильтруем только JPG-файлы
    QStringList filters;
    filters << "*.jpg";
    directory.setNameFilters(filters);

    // Получаем список файлов и удаляем их
    QStringList files = directory.entryList();
    for (const QString &file : files) {
        QString path = directory.absoluteFilePath(file);
        if (QFile::remove(path)) {
            qDebug() << "Removed temp file:" << path;
        } else {
            qDebug() << "Failed to remove temp file:" << path;
        }
    }

    qDebug() << "Cleaned" << files.count() << "temp files";
}
