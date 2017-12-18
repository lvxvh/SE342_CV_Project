#ifndef MYLABEL_H
#define MYLABEL_H

#include <QLabel>
#include <QPaintEvent>

class MyLabel : public QLabel {
    Q_OBJECT
public:
    explicit MyLabel(QWidget *parent = 0);

    QRect getRect() const;
    void setRect(const QRect &value);

private:
    QRect rect;

};

#endif // MYLABEL_H
