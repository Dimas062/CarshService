#include "qclicablelabel.h"

QClicableLabel::QClicableLabel(QWidget* parent, Qt::WindowFlags f)
    : QLabel(parent) {

}

QClicableLabel::~QClicableLabel() {}

void QClicableLabel::mousePressEvent(QMouseEvent* event) {
    emit clicked();
}
