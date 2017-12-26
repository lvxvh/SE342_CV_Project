#include "dtdialog.h"
#include "ui_dtdialog.h"
#include "mainwindow.h"

DTDialog::DTDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DTDialog)
{
    ui->setupUi(this);
    QPixmap pix;
    pix.load(":/images/square.png");
    pix = pix.scaled(ui->squareLabel->width(), ui->squareLabel->height(), Qt::KeepAspectRatio);
    ui->squareLabel->setPixmap(pix);
    pix.load(":/images/cross.png");
    pix = pix.scaled(ui->crossLabel->width(), ui->crossLabel->height(), Qt::KeepAspectRatio);
    ui->crossLabel->setPixmap(pix);
    pix.load(":/images/disk.png");
    pix = pix.scaled(ui->diskLabel->width(), ui->diskLabel->height(), Qt::KeepAspectRatio);
    ui->diskLabel->setPixmap(pix);
}

DTDialog::~DTDialog()
{
    delete ui;
}

void DTDialog::on_confirmButton_clicked()
{
    MainWindow *m = (MainWindow *)parentWidget();
    if(ui->squareButton->isChecked()){
        m->getIh()->distanceTrans(0);
    } else if(ui->crossButton->isChecked()){
        m->getIh()->distanceTrans(1);
    } else {
        m->getIh()->distanceTrans(2);
    }
    this->close();
}


void DTDialog::on_cancelButton_clicked()
{
    this->close();
}