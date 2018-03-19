#ifndef MSLIDER_H
#define MSLIDER_H

#include <QSlider>
#include <QMouseEvent>

class MSlider : public QSlider {
    Q_OBJECT
public:
    explicit MSlider(QWidget *parent = 0);

signals:

public slots:

public:
    void mousePressEvent(QMouseEvent *ev);
};

#endif // MSLIDER_H
