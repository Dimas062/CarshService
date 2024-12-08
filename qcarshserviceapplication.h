#ifndef QCARSHSERVICEAPPLICATION_H
#define QCARSHSERVICEAPPLICATION_H

#include <QApplication>

class QCarshServiceApplication : public QApplication
{
    Q_OBJECT
public:
    QCarshServiceApplication(int &argc, char **argv) :  QApplication(argc,argv){};
    bool event(QEvent *event);
};

#endif // QCARSHSERVICEAPPLICATION_H
