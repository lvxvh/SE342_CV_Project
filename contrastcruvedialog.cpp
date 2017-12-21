#include "contrastcruvedialog.h"
#include "ui_contrastcruvedialog.h"
#include "mainwindow.h"


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
    trans();
}

ContrastCruveDialog::~ContrastCruveDialog()
{
    delete ui;
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
        float value = ui->bEdit->text().toFloat();
        if(value < 1){
            ui->bSlider->setValue(round(value * 100));
        } else {
            ui->bSlider->setValue(value + 100);
        }

    }
}

void ContrastCruveDialog::on_cEdit_editingFinished()
{
    if(ui->cEdit->hasFocus()){
        float value = ui->cEdit->text().toFloat();
        if(value < 1){
            ui->cSlider->setValue(round(value * 100));
        } else {
            ui->cSlider->setValue(value + 100);
        }
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
        if(type == EXP){
            float b;
            b = 1 + value * 0.02f;
            ui->bEdit->setText(QString("%1").arg(b));
        } else {

        }
    }

    trans();
}

void ContrastCruveDialog::on_cSlider_valueChanged(int value)
{
    if(ui->cSlider->hasFocus()){
        if(type == EXP){
            float c;
            c = value * 0.005;
            ui->cEdit->setText(QString("%1").arg(c));
        } else {

        }
    }

    trans();
}
