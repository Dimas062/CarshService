#include <QObject>
#include <QString>

class QtCameraPicker : public QObject {
    Q_OBJECT

public:
    explicit QtCameraPicker(QObject *parent = nullptr);
    ~QtCameraPicker();

    static QtCameraPicker* instance();
    Q_INVOKABLE void openCamera();

signals:
    void imageCaptured(const QString &path);
    void captureCancelled(); // Новый сигнал

private:
    void *m_wrapper;
    static QtCameraPicker *s_instance;
};
