#include "histogramdialog.h"
#include "ui_histogramdialog.h"
#include "mainwindow.h"

#include <QPainter>

HistogramDialog::HistogramDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::HistogramDialog)
{
    ui->setupUi(this);
    MainWindow *m = (MainWindow *)parent;
    histogram = m->getIh()->getHistogram();
    max = 0;
    for(int i = 0;i < 256;i++){
        max = (histogram[i] > max)? histogram[i]:max;
    }
    int yMax = max + 3 - max%3;
    ui->y1Label->setText(QString::number(yMax/3));
    ui->y2Label->setText(QString::number(yMax*2/3));
    ui->y3Label->setText(QString::number(yMax));
}

HistogramDialog::~HistogramDialog()
{
    delete ui;
}

void HistogramDialog::on_confirmButton_clicked()
{
    MainWindow *ptr = (MainWindow*)parentWidget();
    ptr->getIh()->cacheImage(QObject::tr("直方图调整"));
    this->close();
}

void HistogramDialog::on_cancelButton_clicked()
{
    MainWindow *ptr = (MainWindow*)parentWidget();
    ptr->getIh()->resetImage();
    this->close();
}

void HistogramDialog::closeEvent(QCloseEvent *)
{
    MainWindow *ptr = (MainWindow*)parentWidget();
    ptr->getIh()->resetImage();
}

void HistogramDialog::paintEvent(QPaintEvent *)
{
    QPixmap pix = QPixmap(256, 211);
    pix.fill(qRgb(58,64,68));
    QPainter pp(&pix);

    //histogram
    pp.setPen(QColor(178,184,188));
    int yMax = max + 3 - max%3;
    for(int i = 0;i < 256;++i){
        pp.drawLine(QPoint(i, 255), QPoint(i, 255 - histogram[i]*210/yMax));
    }

    pp.setPen(QColor(0, 160, 230));
    pp.drawLine(QPoint(50, 0), QPoint(50, 5));
    pp.drawLine(QPoint(100, 0), QPoint(100, 5));
    pp.drawLine(QPoint(150, 0), QPoint(150, 5));
    pp.drawLine(QPoint(200, 0), QPoint(200, 5));
    pp.drawLine(QPoint(250, 0), QPoint(250, 5));

    pp.drawLine(QPoint(50, 210), QPoint(50, 205));
    pp.drawLine(QPoint(100, 210), QPoint(100, 205));
    pp.drawLine(QPoint(150, 210), QPoint(150, 205));
    pp.drawLine(QPoint(200, 210), QPoint(200, 205));
    pp.drawLine(QPoint(250, 210), QPoint(250, 205));

    pp.drawLine(QPoint(0, 70), QPoint(5, 70));
    pp.drawLine(QPoint(0, 140), QPoint(5, 140));
    pp.drawLine(QPoint(255, 70), QPoint(250, 70));
    pp.drawLine(QPoint(255, 140), QPoint(250, 140));

    QPainter painter(this);
    painter.drawPixmap(90, 50, pix);

    QPen pen;
    pen.setWidth(2);
    pen.setColor(QColor(0, 160, 230));
    painter.setPen(pen);
    painter.drawRect(90, 50, 256, 211);
}

void HistogramDialog::on_equalButton_clicked()
{
    MainWindow *m = (MainWindow *)parentWidget();
    histogram = m->getIh()->equalization(histogram);
    for(int i = 0;i < 256;i++){
        max = (histogram[i] > max)? histogram[i]:max;
    }
    int yMax = max + 3 - max%3;
    ui->y1Label->setText(QString::number(yMax/3));
    ui->y2Label->setText(QString::number(yMax*2/3));
    ui->y3Label->setText(QString::number(yMax));
    ui->equalButton->hide();
    update();
}
