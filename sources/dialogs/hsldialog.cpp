#include "headers/hsldialog.h"
#include "headers/mainwindow.h"
#include "ui_hsldialog.h"

#include <QMessageBox>

HslDialog::HslDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::HslDialog)
{
    setFixedSize(512,320);
    ui->setupUi(this);
}

HslDialog::~HslDialog()
{
    delete ui;
}

void HslDialog::on_hEdit_textEdited(const QString &arg1)
{
    bool ok;
    qint32 value = arg1.toInt(&ok, 10);

    if(value >= -180 && value <= 180) {
        ui->hSlider->setValue(value);
    }
}

void HslDialog::on_hSlider_valueChanged(int value)
{
    if(ui->hSlider->hasFocus()){
        ui->hEdit->setText(QString::number(value, 10));
    }

    MainWindow *ptr = (MainWindow*)parentWidget();
    ptr->getIh()->changeHsl(ui->hSlider->value(), ui->sSlider->value(), ui->lSlider->value());

}

void HslDialog::on_hEdit_editingFinished()
{
    if(ui->hEdit->hasFocus()){
        bool ok;
        qint32 value = ui->hEdit->text().toInt(&ok, 10);

        if(value < -180 || value > 180) {
            QMessageBox::information(this, tr("错误"), tr("要求输入值为-180~180范围内的整数，已插入最近数值"));
            if(value < -180) {
                ui->hEdit->setText(QString::number(-180, 10));
                ui->hSlider->setValue(-180);
            } else {
                ui->hEdit->setText(QString::number(180, 10));
                ui->hSlider->setValue(180);
            }
        }
    }
}



void HslDialog::on_sEdit_textEdited(const QString &arg1)
{
    bool ok;
    qint32 value = arg1.toInt(&ok, 10);

    if(value >= -100 && value <= 100) {
        ui->sSlider->setValue(value);
    }
}

void HslDialog::on_sSlider_valueChanged(int value)
{
    if(ui->sSlider->hasFocus()){
        ui->sEdit->setText(QString::number(value, 10));
    }

    MainWindow *ptr = (MainWindow*)parentWidget();
    ptr->getIh()->changeHsl(ui->hSlider->value(), ui->sSlider->value(), ui->lSlider->value());
}

void HslDialog::on_sEdit_editingFinished()
{
    if(ui->sEdit->hasFocus()){
        bool ok;
        qint32 value = ui->sEdit->text().toInt(&ok, 10);

        if(value < -100 || value > 100) {
            QMessageBox::information(this, tr("错误"), tr("要求输入值为-100~100范围内的整数，已插入最近数值"));
            if(value < -100) {
                ui->sEdit->setText(QString::number(-100, 10));
                ui->sSlider->setValue(-100);
            } else {
                ui->sEdit->setText(QString::number(100, 10));
                ui->sSlider->setValue(100);
            }
        }
    }
}


void HslDialog::on_lEdit_textEdited(const QString &arg1)
{
    bool ok;
    qint32 value = arg1.toInt(&ok, 10);

    if(value >= -100 && value <= 100) {
        ui->lSlider->setValue(value);
    }
}

void HslDialog::on_lEdit_editingFinished()
{
    if(ui->lEdit->hasFocus()){
        bool ok;
        qint32 value = ui->lEdit->text().toInt(&ok, 10);

        if(value < -100 || value > 100) {
            QMessageBox::information(this, tr("错误"), tr("要求输入值为-100~100范围内的整数，已插入最近数值"));
            if(value < -100) {
                ui->lEdit->setText(QString::number(-100, 10));
                ui->lSlider->setValue(-100);
            } else {
                ui->lEdit->setText(QString::number(100, 10));
                ui->lSlider->setValue(100);
            }
        }
    }
}

void HslDialog::on_lSlider_valueChanged(int value)
{
    if(ui->lSlider->hasFocus()){
        ui->lEdit->setText(QString::number(value, 10));
    }

    MainWindow *ptr = (MainWindow*)parentWidget();
    ptr->getIh()->changeHsl(ui->hSlider->value(), ui->sSlider->value(), ui->lSlider->value());
}

void HslDialog::on_confirmButton_clicked()
{
    MainWindow *ptr = (MainWindow*)parentWidget();
    ptr->getIh()->cacheImage(QObject::tr("色相/饱和度/亮度调整"));
    this->close();
}

void HslDialog::on_cancelButton_clicked()
{
    MainWindow *ptr = (MainWindow*)parentWidget();
    ptr->getIh()->resetImage();
    this->close();
}

void HslDialog::closeEvent(QCloseEvent *)
{
    MainWindow *ptr = (MainWindow*)parentWidget();
    ptr->getIh()->resetImage();

}

