#include "headers/contrastlinerdialog.h"
#include "ui_contrastlinerdialog.h"
#include "headers/mainwindow.h"
#include <QPainter>
#include <QLineF>
#include <QMouseEvent>
#include <QMessageBox>

ContrastLinerDialog::ContrastLinerDialog(bool isGray, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ContrastLinerDialog)
{

    ui->setupUi(this);
    ui->inEdit->hide();
    ui->outEdit->hide();
    if(!isGray){
        ui->channalBox->addItem(tr("红"));
        ui->channalBox->addItem(tr("绿"));
        ui->channalBox->addItem(tr("蓝"));
    }
    // 画布大小为200*200，背景为白色
    removing = false;
    edit = false;
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
    QPoint mousePos = mapToPix(p);
    for(int i = 0; i < points.size() - 1;++i){
        if (mousePos.x() < points[i + 1].x()){ // near line pi-p(i + 1)
            {
                qreal angle = QLineF(points[i], mousePos).angleTo(QLineF(points[i], points[i + 1]));
                qreal len = qAbs(sin(angle / 180 * M_PI)) * (QLineF(points[i], mousePos).length());
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

void ContrastLinerDialog::setEditable(bool stat)
{
    if(stat == true){
        ui->inlabel->hide();
        ui->inEdit->show();
        ui->outLabel->hide();
        ui->outEdit->show();
        edit = true;
    } else {
        ui->inEdit->hide();
        ui->inlabel->show();
        ui->outEdit->hide();
        ui->outLabel->show();
        edit = false;
    }
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
    QPoint mouse = e->pos();
    int curPoint = nearPoint(mouse);
    MousePos ps = beforeOrAfterAll(e->pos());
    if(mouseInPix(mouse)){
        if(edit){
            ui->inEdit->setText(QString::number(points[curEditing].x()));
            ui->outEdit->setText(QString::number(255 - points[curEditing].y()));
         }else{
            ui->inlabel->setText(QString::number(mapToPix(mouse).x()));
            ui->outLabel->setText(QString::number(255 - mapToPix(mouse).y()));
        }
    } else {
        ui->inlabel->setText("");
        ui->outLabel->setText("");
    }
    if(removing == true){
        if(curPoint != -1){
            setCursor(Qt::PointingHandCursor);
            ms = del;
        } else {
            setCursor(Qt::ArrowCursor);
            ms = none;
        }
    } else if(curPoint != -1){
        setCursor(Qt::SizeAllCursor);
        ms = drag;
    } else if (ps != other){
        setCursor(Qt::SizeAllCursor);
        ms = dragLine;
    }else if (nearLine(mouse)){
        setCursor(Qt::CrossCursor);
        ms = add;
    } else {
        setCursor(Qt::ArrowCursor);
        ms = none;
    }

    if(ms == drag && e->buttons() == Qt::LeftButton){
        QPoint newPoint = mapToPix(mouse);
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
        int newY = mapToPix(mouse).y();
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
    if(ms == del && e->button() == Qt::LeftButton){
        removing = false;
        if(points.size() < 3) {
            QMessageBox::information(this, QObject::tr("提示"), QObject::tr("没点可删啦"));
            return;
        }
        int cur = nearPoint(e->pos());
        points.erase(points.begin() + cur);
        update();
    }
    if(ms == add && e->button() == Qt::LeftButton){
        setEditable(true);
        QPoint newPoint = mapToPix(e->pos());
        for(int i = 0; i < points.size() - 1;++i){
            if(newPoint.x() < points[i + 1].x()){
                points.insert(points.begin() + i + 1, newPoint);
                curEditing = i + 1;
                update();
                break;
            }
        }
    }
    if((ms == drag||ms == dragLine) && e->button() == Qt::LeftButton){
        if(e->pos().x() <= points[0].x()) curEditing = 0;
        else if(e->pos().x() >= points.last().x()) curEditing = points.size() - 1;
        else{
            curEditing = nearPoint(e->pos());
        }
        setEditable(true);
    }
    if(ms == none && e->button() == Qt::LeftButton){
        setEditable(false);
    }
}

void ContrastLinerDialog::mouseReleaseEvent(QMouseEvent *)
{
    int channal = ui->channalBox->currentIndex();
    if (channal == 3) channal = 4;
    MainWindow *m = (MainWindow *)parentWidget();
    m->getIh()->contrastLiner(points, channal);
}

void ContrastLinerDialog::closeEvent(QCloseEvent *)
{
    MainWindow *ptr = (MainWindow*)parentWidget();
    ptr->getIh()->resetImage();
}



void ContrastLinerDialog::on_deleteButton_clicked()
{
    setEditable(false);
    removing = true;
}

void ContrastLinerDialog::on_inEdit_editingFinished()
{
    if(ui->inEdit->hasFocus()){
        int x = ui->inEdit->text().toInt();
        int upperbound;
        int lowerbound;
        if(curEditing  == 0){
            upperbound = points[1].x() - 4;
            lowerbound = 0;
        } else if(curEditing == points.size() - 1){
            upperbound = points[curEditing + 1].x() - 4;
            lowerbound = points[curEditing - 1].x() + 4;
        } else {
            upperbound = 255;
            lowerbound = points[curEditing - 1].x() + 4;
        }
        if(x > upperbound || x < lowerbound){
            QMessageBox::information(this, tr("错误"), tr("输入范围应当在%1~%2内").arg(lowerbound).arg(upperbound));
            if (x > upperbound) x = upperbound;
            else x = lowerbound;
        }

        QPoint newPoint = points[curEditing];
        newPoint.setX(x);
        points.erase(points.begin() + curEditing);
        points.insert(points.begin() + curEditing, newPoint);
        update();
        int channal = ui->channalBox->currentIndex();
        if (channal == 3) channal = 4;
        MainWindow *m = (MainWindow *)parentWidget();
        m->getIh()->contrastLiner(points, channal);
    }
}

void ContrastLinerDialog::on_outEdit_editingFinished()
{
    if(ui->outEdit->hasFocus()){
        int y = ui->inEdit->text().toInt();
        if(y > 255 || y < 0){
            QMessageBox::information(this, tr("错误"), tr("输入范围应当在0~255内"));
            if (y > 255) y = 255;
            else y = 0;
        }

        QPoint newPoint = points[curEditing];
        newPoint.setY(255 - y);
        points.erase(points.begin() + curEditing);
        points.insert(points.begin() + curEditing, newPoint);
        update();
        int channal = ui->channalBox->currentIndex();
        if (channal == 3) channal = 4;
        MainWindow *m = (MainWindow *)parentWidget();
        m->getIh()->contrastLiner(points, channal);
    }
}

void ContrastLinerDialog::on_confirmButton_clicked()
{
    MainWindow *ptr = (MainWindow*)parentWidget();
    ptr->getIh()->cacheImage(QObject::tr("对比度线性调节"));
    this->close();
}

void ContrastLinerDialog::on_cancelButton_clicked()
{
    MainWindow *ptr = (MainWindow*)parentWidget();
    ptr->getIh()->resetImage();
    this->close();
}
