#include "headers/parameterdialog.h"
#include "ui_parameterdialog.h"
#include "headers/mainwindow.h"
#include <QMessageBox>

ParameterDialog::ParameterDialog(action act, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ParameterDialog)
{
    a = act;
    setFixedSize(340,429);
    ui->setupUi(this);

    if(a == SOBEL){
        ui->line_0->hide();
        ui->tresholdlabel->hide();
        ui->tEdit->hide();
        ui->tLabel->hide();
        ui->htEdit->hide();
        ui->ltEdit->hide();
        ui->htLabel->hide();
        ui->ltLabel->hide();
        ui->line_1->hide();
        ui->houghLabel->hide();
        ui->houghTEdit->hide();
        ui->houghTiLabel->hide();
        ui->houghTLabel->hide();
        ui->angleBox->hide();
        ui->angleiLabel->hide();
        ui->angleLabel->hide();
        ui->circlelabel->hide();
        ui->rMaxLabel->hide();
        ui->rMinEdit->hide();
        ui->rMinLabel->hide();
        ui->rMaxEdit->hide();
        ui->radiusLabel->hide();
        ui->radiusBox->hide();
    } else if(a == LAPLAS){
        ui->htEdit->hide();
        ui->ltEdit->hide();
        ui->htLabel->hide();
        ui->ltLabel->hide();
        ui->line_1->hide();
        ui->houghLabel->hide();
        ui->houghTEdit->hide();
        ui->houghTiLabel->hide();
        ui->houghTLabel->hide();
        ui->angleBox->hide();
        ui->angleiLabel->hide();
        ui->angleLabel->hide();
        ui->circlelabel->hide();
        ui->rMaxLabel->hide();
        ui->rMinEdit->hide();
        ui->rMinLabel->hide();
        ui->rMaxEdit->hide();
        ui->radiusLabel->hide();
        ui->radiusBox->hide();
    } else if(a == CANNY){
        ui->tEdit->hide();
        ui->tLabel->hide();
        ui->line_1->hide();
        ui->houghLabel->hide();
        ui->houghTEdit->hide();
        ui->houghTiLabel->hide();
        ui->houghTLabel->hide();
        ui->angleBox->hide();
        ui->angleiLabel->hide();
        ui->angleLabel->hide();
        ui->circlelabel->hide();
        ui->rMaxLabel->hide();
        ui->rMinEdit->hide();
        ui->rMinLabel->hide();
        ui->rMaxEdit->hide();
        ui->radiusLabel->hide();
        ui->radiusBox->hide();
    } else if(a == HOUGHLINE){
        ui->tEdit->hide();
        ui->tLabel->hide();
        ui->circlelabel->hide();
        ui->rMaxLabel->hide();
        ui->rMaxEdit->hide();
        ui->rMinLabel->hide();
        ui->rMinEdit->hide();
        ui->radiusLabel->hide();
        ui->radiusBox->hide();
    } else {
        ui->tEdit->hide();
        ui->tLabel->hide();
        ui->angleiLabel->setText("2π/");
    }
}

ParameterDialog::~ParameterDialog()
{
    delete ui;
}

void ParameterDialog::on_confirmButton_clicked()
{
    int gaussianSize = (ui->gaussBox->currentIndex() + 1) * 2 + 1;
    float sigma = ui->sigmaEdit->text().toFloat();
    int t = ui->tEdit->text().toInt();
    int ht = ui->htEdit->text().toInt();
    int lt = ui->ltEdit->text().toInt();
    float t_ratio = ui->houghTEdit->text().toFloat();
    int hough_space;
    if(ui->angleBox->currentIndex() == 0) hough_space = 500;
    else if(ui->angleBox->currentIndex() == 1) hough_space = 200;
    else hough_space = 100;
    int rSize;
    if(ui->radiusBox->currentIndex() == 0) rSize = 50;
    else if(ui->radiusBox->currentIndex() == 1) rSize = 20;
    else rSize = 10;
    int rMax = ui->rMaxEdit->text().toInt();
    int rMin = ui->rMinEdit->text().toInt();


    MainWindow *ptr = (MainWindow*)parentWidget();

    if(a == SOBEL){
        ptr->getIh()->sobel(gaussianSize, sigma);
        ptr->getIh()->cacheImage("Sobel");
        ptr->getIh()->draw();
    } else if(a == LAPLAS){
        ptr->getIh()->laplace(gaussianSize, sigma, t);
        ptr->getIh()->cacheImage("Laplacian");
        ptr->getIh()->draw();
    } else if(a == CANNY){
        ptr->getIh()->canny(gaussianSize, sigma, ht, lt);
        //canny is midium
        ptr->getIh()->cacheImage("Canny");
        ptr->getIh()->draw();
    } else if(a ==HOUGHLINE){
        ptr->getIh()->houghLine(gaussianSize, sigma, ht, lt, t_ratio, hough_space);
    } else{
        ptr->getIh()->houghCircle(gaussianSize, sigma, ht, lt, t_ratio, hough_space, rSize, rMax, rMin);
    }

    this->close();
}

void ParameterDialog::on_cancelButton_clicked()
{
    MainWindow *ptr = (MainWindow*)parentWidget();
    ptr->getIh()->resetImage();
    this->close();
}

void ParameterDialog::on_houghTEdit_editingFinished()
{
    if(ui->houghTEdit->hasFocus()){
        float value = ui->houghTEdit->text().toFloat();
        if(value > 1.0f) {
            QMessageBox::information(this, tr("错误"), tr("要求输入值不大于1"));                                                                      QMessageBox::information(this, tr("错误"), tr("要求输入值为-180~180范围内的整数，已插入最近数值"));
            ui->houghTEdit->setText(QString::number(0.5));
        }
    }
}

void ParameterDialog::on_htEdit_editingFinished()
{
    if(ui->htEdit->hasFocus()){
        int hvalue = ui->htEdit->text().toInt();
        int lvalue = ui->ltEdit->text().toInt();
        if(hvalue > 255 || hvalue < lvalue) {
            QMessageBox::information(this, tr("错误"), tr("要求输入值在%1~255之间").arg(lvalue));                                                                      QMessageBox::information(this, tr("错误"), tr("要求输入值为-180~180范围内的整数，已插入最近数值"));
            if(hvalue > 255){
                ui->htEdit->setText(QString::number(255));
            } else {
                ui->htEdit->setText(QString::number(lvalue));
            }
        }
    }
}

void ParameterDialog::on_ltEdit_editingFinished()
{
    if(ui->ltEdit->hasFocus()){
        int hvalue = ui->htEdit->text().toInt();
        int lvalue = ui->ltEdit->text().toInt();
        if(lvalue > 255 || hvalue < lvalue) {
            QMessageBox::information(this, tr("错误"), tr("要求输入值不大于255且不大于%1").arg(hvalue));                                                                      QMessageBox::information(this, tr("错误"), tr("要求输入值为-180~180范围内的整数，已插入最近数值"));
            ui->ltEdit->setText(QString::number(hvalue));
        }
    }
}

void ParameterDialog::on_tEdit_editingFinished()
{
    if(ui->tEdit->hasFocus()){
        int value = ui->tEdit->text().toInt();
        if(value > 255) {
            QMessageBox::information(this, tr("错误"), tr("要求输入值在0~255之间"));                                                                      QMessageBox::information(this, tr("错误"), tr("要求输入值为-180~180范围内的整数，已插入最近数值"));
            ui->tEdit->setText(QString::number(10));
        }
    }
}

void ParameterDialog::on_sigmaEdit_editingFinished()
{

}

void ParameterDialog::closeEvent(QCloseEvent *)
{
    MainWindow *ptr = (MainWindow*)parentWidget();
    ptr->getIh()->resetImage();
}

void ParameterDialog::on_rMaxEdit_editingFinished()
{
    if(ui->rMaxEdit->hasFocus()){
        int max = ui->rMaxEdit->text().toInt();
        int min = ui->rMinEdit->text().toInt();
        if(max < min) {
            QMessageBox::information(this, tr("错误"), tr("不得小于最小值"));                                                                      QMessageBox::information(this, tr("错误"), tr("要求输入值为-180~180范围内的整数，已插入最近数值"));
            ui->rMaxEdit->setText(QString::number(min));
        }
    }
}

void ParameterDialog::on_rMinEdit_editingFinished()
{
    if(ui->rMinEdit->hasFocus()){
        int max = ui->rMaxEdit->text().toInt();
        int min = ui->rMinEdit->text().toInt();
        if(max < min) {
            QMessageBox::information(this, tr("错误"), tr("不得大于最大值"));                                                                      QMessageBox::information(this, tr("错误"), tr("要求输入值为-180~180范围内的整数，已插入最近数值"));
            ui->rMinEdit->setText(QString::number(max));
        }
    }
}
