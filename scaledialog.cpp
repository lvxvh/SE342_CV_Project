#include "scaledialog.h"
#include "ui_scaledialog.h"
#include "iconhelper.h"
#include "mainwindow.h"
#include <QMessageBox>

ScaleDialog::ScaleDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ScaleDialog)
{
    setFixedSize(260,253);
    ui->setupUi(this);
    IconHelper::Instance()->SetIcon(ui->zoomInButton, QChar(0xf00e), 40);
    IconHelper::Instance()->SetIcon(ui->zoomOutButton, QChar(0xf010), 40);
}

ScaleDialog::~ScaleDialog()
{
    delete ui;
}

void ScaleDialog::on_factorEdit_editingFinished()
{
    if(ui->factorEdit->hasFocus()){
        float value = ui->factorEdit->text().toFloat();
        if(value < 0.1f || value > 1600.0f) {
            QMessageBox::information(this, tr("错误"), tr("要求输入值在0.1~1600之间"));
            if(value < 0.1f) {
                ui->factorEdit->setText("1");
                value = 0.1f;
            } else {
                ui->factorEdit->setText("1600");
                value = 1600.0f;
            }
        }
        float factor = value/100;
        MainWindow *ptr = (MainWindow*)parentWidget();
        if(ui->bilinerButton->isChecked()) {
            ptr->getIh()->scale(factor, 1);
        } else {
            ptr->getIh()->scale(factor, 0);
        }
    }

}

void ScaleDialog::on_confirmButton_clicked()
{
    MainWindow *ptr = (MainWindow*)parentWidget();
    ptr->getIh()->cacheImage(QObject::tr("缩放"));
    this->close();
}

void ScaleDialog::closeEvent(QCloseEvent *)
{
    MainWindow *ptr = (MainWindow*)parentWidget();
    ptr->getIh()->resetImage();
}

void ScaleDialog::on_cancelButton_clicked()
{
    MainWindow *ptr = (MainWindow*)parentWidget();
    ptr->getIh()->resetImage();
    this->close();
}

void ScaleDialog::on_zoomInButton_clicked()
{
    float curScale = ui->factorEdit->text().toFloat();
    float factor;
    if(curScale < 0.2f) {
        factor = 0.2f;
        ui->factorEdit->setText("0.2");
    }
    else if(curScale < 0.3f) {
        factor = 0.3f;
        ui->factorEdit->setText("0.3");
    }
    else if(curScale < 0.4f){
        factor = 0.4f;
        ui->factorEdit->setText("0.4");
    }
    else if(curScale < 0.5f) {
        factor = 0.5f;
        ui->factorEdit->setText("0.5");
    }
    else if(curScale < 0.7f) {
        factor = 0.7f;
        ui->factorEdit->setText("0.7");
    }
    else if(curScale < 1) {
        factor = 1;
        ui->factorEdit->setText("1.0");
    }
    else if(curScale < 1.5f) {
        factor = 1.5f;
        ui->factorEdit->setText("1.5");
    }
    else if(curScale < 2) {
        factor = 2;
        ui->factorEdit->setText("2.0");
    }
    else if(curScale < 3) {
        factor = 3;
        ui->factorEdit->setText("3.0");
    }
    else if(curScale < 4) {
        factor = 4;
        ui->factorEdit->setText("4.0");
    }
    else if(curScale < 5) {
        factor = 5;
        ui->factorEdit->setText("5.0");
    }
    else if(curScale < 6.25f) {
        factor = 6.25f;
        ui->factorEdit->setText("6.25");
    }
    else if(curScale < 8.3f) {
        factor = 8.3f;
        ui->factorEdit->setText("8.3");
    }
    else if(curScale < 12.5f) {
        factor = 12.5f;
        ui->factorEdit->setText("12.5");
    }
    else if(curScale < 16.67f) {
        factor = 16.67f;
        ui->factorEdit->setText("16.67");
    }
    else if(curScale < 33.33f) {
        factor = 33.33f;
        ui->factorEdit->setText("33.33");
    }
    else if(curScale < 50) {
        factor = 50;
        ui->factorEdit->setText("50.0");
    }
    else if(curScale < 66.67f) {
        factor = 66.67f;
        ui->factorEdit->setText("66.67");
    }
    else if(curScale < 100) {
        factor = 100;
        ui->factorEdit->setText("100.0");
    }
    else if(curScale < 200) {
        factor = 200;
        ui->factorEdit->setText("200.0");
    }
    else if(curScale < 300) {
        factor = 300;
        ui->factorEdit->setText("300.0");
    }
    else if(curScale < 400) {
        factor = 400;
        ui->factorEdit->setText("400.0");
    }
    else if(curScale < 500) {
        factor = 500;
        ui->factorEdit->setText("500.0");
    }
    else if(curScale < 600) {
        factor = 600;
        ui->factorEdit->setText("600.0");
    }
    else if(curScale < 700) {
        factor = 700;
        ui->factorEdit->setText("700.0");
    }
    else if(curScale < 800) {
        factor = 800;
        ui->factorEdit->setText("800.0");
    }
    else if(curScale < 1200) {
        factor = 1200;
        ui->factorEdit->setText("1200.0");
    }
    else if(curScale < 1600) {
        factor = 1600;
        ui->factorEdit->setText("1600.0");
    } else {  //==1600
        return;
    }

    factor = factor/100;
    MainWindow *ptr = (MainWindow*)parentWidget();
    if(ui->bilinerButton->isChecked()) {
        ptr->getIh()->scale(factor, 1);
    } else {
        ptr->getIh()->scale(factor, 0);
    }
}


void ScaleDialog::on_zoomOutButton_clicked()
{
    float curScale = ui->factorEdit->text().toFloat();
    float factor;

    if(curScale > 1200) {
        factor = 1200;
        ui->factorEdit->setText("1200.0");
    }else if(curScale > 800) {
        factor = 800;
        ui->factorEdit->setText("800.0");
    }else if(curScale > 700) {
        factor = 700;
        ui->factorEdit->setText("700.0");
    }else if(curScale > 600) {
        factor = 600;
        ui->factorEdit->setText("600.0");
    }else if(curScale > 500) {
        factor = 500;
        ui->factorEdit->setText("500.0");
    }else if(curScale > 400) {
        factor = 400;
        ui->factorEdit->setText("400.0");
    }
    else if(curScale > 300) {
        factor = 300;
        ui->factorEdit->setText("300.0");
    }
    else if(curScale > 200) {
        factor = 200;
        ui->factorEdit->setText("200.0");
    }
    else if(curScale > 100) {
        factor = 100;
        ui->factorEdit->setText("100.0");
    }
    else if(curScale > 66.67f) {
        factor = 66.67f;
        ui->factorEdit->setText("66.67");
    }
    else if(curScale > 50) {
        factor = 50;
        ui->factorEdit->setText("50.0");
    }
    else if(curScale > 33.33f) {
        factor = 33.33f;
        ui->factorEdit->setText("33.33");
    }
    else if(curScale > 16.67f) {
        factor = 16.67f;
        ui->factorEdit->setText("16.67");
    }
    else if(curScale > 12.5f) {
        factor = 12.5f;
        ui->factorEdit->setText("12.5");
    }
    else if(curScale > 8.3f) {
        factor = 8.3f;
        ui->factorEdit->setText("8.3");
    }
    else if(curScale > 6.25f) {
        factor = 6.25f;
        ui->factorEdit->setText("6.25");
    }
    else if(curScale > 5) {
        factor = 5;
        ui->factorEdit->setText("5.0");
    }
    else if(curScale > 4) {
        factor = 4;
        ui->factorEdit->setText("4.0");
    }
    else if(curScale > 3) {
        factor = 3;
        ui->factorEdit->setText("3.0");
    }
    else if(curScale > 2) {
        factor = 2;
        ui->factorEdit->setText("2.0");
    }
    else if(curScale > 1.5f) {
        factor = 1.5f;
        ui->factorEdit->setText("1.5");
    }
    else if(curScale > 1) {
        factor = 1;
        ui->factorEdit->setText("1.0");
    }
    else if(curScale > 0.7f) {
        factor = 0.7f;
        ui->factorEdit->setText("0.7");
    }
    else if(curScale > 0.5f) {
        factor = 0.5f;
        ui->factorEdit->setText("0.5");
    }
    else if(curScale > 0.4f){
        factor = 0.4f;
        ui->factorEdit->setText("0.4");
    }
    else if(curScale > 0.3f) {
        factor = 0.3f;
        ui->factorEdit->setText("0.3");
    }
    else if(curScale > 0.2f) {
        factor = 0.2f;
        ui->factorEdit->setText("0.2");
    } else if(curScale >= 0.1f){
        factor = 0.1f;
        ui->factorEdit->setText("0.1");
    }

    factor = factor/100;
    MainWindow *ptr = (MainWindow*)parentWidget();
    if(ui->bilinerButton->isChecked()) {
        ptr->getIh()->scale(factor, 1);
    } else {
        ptr->getIh()->scale(factor, 0);
    }
}
