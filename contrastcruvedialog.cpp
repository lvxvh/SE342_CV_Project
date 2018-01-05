#include "contrastcruvedialog.h"
#include "ui_contrastcruvedialog.h"
#include "mainwindow.h"
#include <QMouseEvent>


ContrastCruveDialog::ContrastCruveDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ContrastCruveDialog)
{
    ui->setupUi(this);
    QPixmap pix;
    pix.load(":/images/exp.png");
    pix = pix.scaled(ui->tipLabel->width(), ui->tipLabel->height(), Qt::KeepAspectRatio);
    ui->tipLabel->setPixmap(pix);
    type = EXP;
    setMouseTracking(true);
    trans();
}

ContrastCruveDialog::~ContrastCruveDialog()
{
    delete ui;
}

bool ContrastCruveDialog::mouseInPix(QPoint m)
{
    return m.x() > 100 && m.y() > 110 && m.x() < 100 + 256 && m.y() < 110 + 256;
}

QPoint ContrastCruveDialog::mapToPix(QPoint p)
{
    QPoint out;
    out.setX(p.x() - 100);
    out.setY(p.y() - 110);
    return out;
}

void ContrastCruveDialog::trans()
{
    points.clear();
    float a = ui->aEdit->text().toFloat();
    float b = ui->bEdit->text().toFloat();
    float c = ui->cEdit->text().toFloat();
    if(type == EXP){
        for(int x = 0;x < 256;++x){
            int y = round(pow(b, c*(x - a))) - 1;
            if(y > 255) y = 255;
            if(y < 0) y = 0;
            points.push_back(QPoint(x, 255 - y));
        }
    } else {
        for(int x = 0;x < 256;++x){
            int y = round(a + (log(x + 1)/(b*log(c))));
            //qDebug() << y;
            if(y > 255) y = 255;
            if(y < 0) y = 0;
            points.push_back(QPoint(x, 255 - y));
        }
    }
    update();
    MainWindow *m = (MainWindow *)parentWidget();
    m->getIh()->contrastCurve(type,a,b,c);
}

void ContrastCruveDialog::paintEvent(QPaintEvent *)
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
    //curve
    pp.setPen(QColor(178,184,188));
    for(int i = 0;i < points.size();++i){
        //qDebug() << points[i];
        pp.drawPoint(points[i]);
    }
    QPainter painter(this);
    painter.drawPixmap(100, 110, pix);

    QPen pen;
    pen.setWidth(2);
    pen.setColor(QColor(0, 160, 230));
    painter.setPen(pen);
    painter.drawRect(100, 110, 256, 256);

}

void ContrastCruveDialog::closeEvent(QCloseEvent *)
{
    MainWindow *ptr = (MainWindow*)parentWidget();
    ptr->getIh()->resetImage();
}

void ContrastCruveDialog::mouseMoveEvent(QMouseEvent *e)
{
    QPoint mouse = e->pos();
    if(mouseInPix(mouse)){
        ui->inLabel->setText(QString::number(mapToPix(mouse).x()));
        ui->outLabel->setText(QString::number(255 - mapToPix(mouse).y()));
    } else {
        ui->inLabel->setText("");
        ui->outLabel->setText("");
    }
}

void ContrastCruveDialog::on_aEdit_editingFinished()
{
    if(ui->aEdit->hasFocus()){
        float value = ui->aEdit->text().toFloat();
        ui->aSlider->setValue(round(value));

    }
}

void ContrastCruveDialog::on_bEdit_editingFinished()
{
    if(ui->bEdit->hasFocus()){
        trans();
    }
}

void ContrastCruveDialog::on_cEdit_editingFinished()
{
    if(ui->cEdit->hasFocus()){
        trans();
    }
}

void ContrastCruveDialog::on_typeBox_currentIndexChanged(int index)
{
    if(index == 0){
        QPixmap pix;
        pix.load(":/images/exp.png");
        pix = pix.scaled(ui->tipLabel->width(), ui->tipLabel->height(), Qt::KeepAspectRatio);
        ui->tipLabel->setPixmap(pix);
        type = EXP;
        trans();
    } else{
        QPixmap pix;
        pix.load(":/images/log.png");
        pix = pix.scaled(ui->tipLabel->width(), ui->tipLabel->height(), Qt::KeepAspectRatio);
        ui->tipLabel->setPixmap(pix);
        type = LOG;
        trans();
    }
}

void ContrastCruveDialog::on_aSlider_valueChanged(int value)
{
    if(ui->aSlider->hasFocus()){
        ui->aEdit->setText(QString::number(value, 10));
    }

    trans();
}

void ContrastCruveDialog::on_bSlider_valueChanged(int value)
{
    if(ui->bSlider->hasFocus()){
        float b;
        if(type == EXP){
            b = 1 + value * 0.02f;
        } else {
            if(value < 100) b = 0.5 + 0.005*value;
            else b = 1 + 0.05*(value - 100);
        }
        ui->bEdit->setText(QString("%1").arg(b));
    }

    trans();
}

void ContrastCruveDialog::on_cSlider_valueChanged(int value)
{
    if(ui->cSlider->hasFocus()){
        float c;
        if(type == EXP){
            c = value * 0.005;
        } else {
            c = value * 0.0025 + 1;
        }
         ui->cEdit->setText(QString("%1").arg(c));
    }

    trans();
}

void ContrastCruveDialog::on_confirmButton_clicked()
{
    MainWindow *ptr = (MainWindow*)parentWidget();
    ptr->getIh()->cacheImage(QObject::tr("对比度非线性调节"));
    this->close();
}

void ContrastCruveDialog::on_cancelButton_clicked()
{
    MainWindow *ptr = (MainWindow*)parentWidget();
    ptr->getIh()->resetImage();
    this->close();
}
