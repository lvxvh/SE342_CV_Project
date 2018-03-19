#include "mylabel.h"
#include <QPainter>
#include <QDebug>

MyLabel::MyLabel(QWidget *parent) :
    QLabel(parent){
}

QRect MyLabel::getRect() const
{
    return rect;
}

void MyLabel::setRect(const QRect &value)
{
    rect = value;
}

