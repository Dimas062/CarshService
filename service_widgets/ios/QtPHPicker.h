#include <QObject>
#include <QStringList>

class QtPHPicker : public QObject {
    Q_OBJECT

public:
    explicit QtPHPicker(QObject *parent = nullptr);
    ~QtPHPicker();

    // Добавьте объявление статического метода instance()
    static QtPHPicker* instance();

    Q_INVOKABLE void openPicker(bool allowMultiple);
    Q_INVOKABLE void clearTempFiles();

signals:
    void filesSelected(const QStringList &paths);

private:
    void *m_wrapper;
    static QtPHPicker *s_instance; // Статическая переменная
};
