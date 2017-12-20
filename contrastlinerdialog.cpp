#include "contrastlinerdialog.h"
#include "ui_contrastlinerdialog.h"
#include "mainwindow.h"
#include <QPainter>
#include <QLineF>
#include <QMouseEvent>

ContrastLinerDialog::ContrastLinerDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ContrastLinerDialog)
{
    ui->setupUi(this);
    // 画布大小为200*200，背景为白色


    setMouseTracking(true);
    points.push_back(QPoint(0, 255));
    points.push_back(QPoint(255, 0));
}

ContrastLinerDialog::~ContrastLinerDialog()
{
    delete ui;
}

bool ContrastLinerDialog::nearLine(QPoint p)
{
    if(!mouseInPix(p)) return false;
    for(int i = 0; i < points.size() - 1;++i){
        if (p.x() < points[i + 1].x()){ // near line pi-p(i + 1)
            {
                qreal angle = QLineF(points[i], p).angleTo(QLineF(points[i], points[i + 1]));
                qreal len = qAbs(sin(angle / 180 * M_PI)) * (QLineF(points[i], p).length());
                return (len < 20);
            }
        }
    }
    return false;
}

int ContrastLinerDialog::nearPoint(QPoint p)
{
    if(!mouseInPix(p)) return -1;
    int index = -1;
    QPoint mousePos = mapToPix(p);
    for(int i = 0;i < points.size();++i){
        if(qAbs(mousePos.x() - points[i].x()) <= 8 && qAbs(mousePos.y() - points[i].y()) <= 8) {
            index = i;
            break;
        }
    }
    return index;
}

MousePos ContrastLinerDialog::beforeOrAfterAll(QPoint p)
{
    if(!mouseInPix(p)) return other;
    QPoint mousePos = mapToPix(p);
    if(mousePos.x() < points.front().x()){
        return beforeAll;
    } else if (mousePos.x() > points.last().x()){
        return afterAll;
    }else {
        return other;
    }
}

bool ContrastLinerDialog::mouseInPix(QPoint m)
{
    return m.x() > PIX_X && m.y() > PIX_Y && m.x() < PIX_X + 256 && m.y() < PIX_X + 256;
}

QPoint ContrastLinerDialog::mapToPix(QPoint p)
{
    QPoint out;
    out.setX(p.x() - PIX_X);
    out.setY(p.y() - PIX_Y);
    return out;
}


void ContrastLinerDialog::paintEvent(QPaintEvent *)
{
    QPixmap pix = QPixmap(256, 256);
    pix.fill(qRgb(58,64,68));
    QPainter pp(&pix);



    pp.setPen(QColor(78,84,88));
    pp.drawLine(QPoint(63, 0), QPoint(63, 255));
    pp.drawLine(QPoint(127, 0), QPoint(127, 255));
    pp.drawLine(QPoint(190, 0), QPoint(190, 255));
    pp.drawLine(QPoint(0, 63), QPoint(255, 63));
    pp.drawLine(QPoint(0, 127), QPoint(255, 127));
    pp.drawLine(QPoint(0, 190), QPoint(255, 190));
    //line
    pp.setPen(QColor(178,184,188));
    QPoint leftBegin(0, points.front().y());
    QPoint rightEnd(255, points.last().y());
    pp.drawLine(leftBegin, points.front());
    pp.drawLine(points.last(), rightEnd);
    for(int i = 0; i < points.size() - 1;++i){
        pp.drawRect(points[i].x() - 2 , points[i]. y() - 2, 4, 4);
        pp.drawRect(points[i + 1].x() - 2 , points[i + 1]. y() - 2, 4, 4);
        pp.drawLine(points[i], points[i + 1]);
    }

    QPainter painter(this);
    painter.drawPixmap(PIX_X, PIX_Y, pix);
    QPen pen;
    pen.setWidth(2);
    pen.setColor(QColor(0, 160, 230));
    painter.setPen(pen);
    painter.drawRect(80, 80, 256, 256);
}

void ContrastLinerDialog::mouseMoveEvent(QMouseEvent *e)
{
    int curPoint = nearPoint(e->pos());
    MousePos ps = beforeOrAfterAll(e->pos());
    if(curPoint != -1){
        setCursor(Qt::SizeAllCursor);
        ms = drag;
    } else if (ps != other){
        setCursor(Qt::SizeAllCursor);
        ms = dragLine;
    }else if (nearLine(mapToPix(e->pos()))){
        setCursor(Qt::CrossCursor);
        ms = add;
    } else {
        setCursor(Qt::ArrowCursor);
        ms = none;
    }

    if(ms == drag && e->buttons() == Qt::LeftButton){
        QPoint newPoint = mapToPix(e->pos());
        if(curPoint == 0){
            if(newPoint.x() + 4 > points[curPoint + 1].x()){
                newPoint = points[curPoint];
            }
        } else if(curPoint == points.size() - 1){
            if(newPoint.x() - 4 < points[curPoint - 1].x()){
                newPoint = points[curPoint];
            }
        } else {
            if(newPoint.x() + 4 > points[curPoint + 1].x() ||
               newPoint.x() - 4 < points[curPoint - 1].x() ){
                newPoint = points[curPoint];
            }
        }
        points.erase(points.begin() + curPoint);
        points.insert(points.begin() + curPoint, newPoint);
        update();
    }

    if(ms == dragLine && e->buttons() == Qt::LeftButton){
        int newY = mapToPix(e->pos()).y();
        QPoint newPoint;
        if(ps == beforeAll){
            newPoint = QPoint(points.front().x(), newY);
            points.erase(points.begin());
            points.insert(points.begin(), newPoint);
        } else {
            newPoint = QPoint(points.last().x(), newY);
            points.erase(points.end() - 1);
            points.push_back(newPoint);
        }
        update();
    }
}

void ContrastLinerDialog::mousePressEvent(QMouseEvent *e)
{
    if(ms == add && e->button() == Qt::LeftButton){
        QPoint newPoint = mapToPix(e->pos());
        for(int i = 0; i < points.size() - 1;++i){
            if(newPoint.x() < points[i + 1].x()){
                points.insert(points.begin() + i + 1, newPoint);
                update();
                break;
            }
        }
    }

}
