#include "mslider.h"
#include <QDebug>

MSlider::MSlider(QWidget *parent) :
        QSlider(parent) {
}

void MSlider::mousePressEvent(QMouseEvent *ev) {
    QSlider::mousePressEvent(ev);
    double pos = ev->pos().x() / (double)width();
    setValue(pos * (maximum() - minimum()) + minimum());
    setSliderDown(true);
    setSliderDown(false);
}

