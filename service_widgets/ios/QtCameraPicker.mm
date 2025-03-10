#include "QtCameraPicker.h"
#include "CameraWrapper.h"

QtCameraPicker* QtCameraPicker::s_instance = nullptr;

QtCameraPicker::QtCameraPicker(QObject *parent) : QObject(parent) {
    CameraWrapper *wrapper = [[CameraWrapper alloc] init];
    m_wrapper = (__bridge_retained void *)wrapper;

    wrapper.imageCaptured = [](const QString &path) {
        if (s_instance) {
            emit s_instance->imageCaptured(path);
        }
    };

    // Подключение callback для отмены
    wrapper.captureCancelled = []() {
        if (s_instance) {
            emit s_instance->captureCancelled();
        }
    };
}

QtCameraPicker::~QtCameraPicker() {
    CameraWrapper *wrapper = (__bridge_transfer CameraWrapper *)m_wrapper;
    wrapper = nil;
    s_instance = nullptr;
}

QtCameraPicker* QtCameraPicker::instance() {
    if (!s_instance) {
        s_instance = new QtCameraPicker();
    }
    return s_instance;
}

void QtCameraPicker::openCamera() {
    CameraWrapper *wrapper = (__bridge CameraWrapper *)m_wrapper;
    [wrapper openCamera];
}
