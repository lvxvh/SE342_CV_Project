#include "BinaryDialog.h"
#include "ui_binarydialog.h"
#include <QMessageBox>

BinaryDialog::BinaryDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::BinaryDialog)
{
    ui->setupUi(this);
}

BinaryDialog::~BinaryDialog()
{
    delete ui;
}

void BinaryDialog::on_hEdit_textEdited(const QString &arg1)
{
    bool ok;
    qint32 value = arg1.toInt(&ok, 10);

    if(value >= ui->lSlider->value() && value <= 255) {
        ui->hSlider->setValue(value);
    }
}

void BinaryDialog::on_hEdit_editingFinished()
{
    if(ui->hEdit->hasFocus()){
        bool ok;
        qint32 value = ui->hEdit->text().toInt(&ok, 10);

        if(value < ui->lSlider->value() || value > 255) {
            QMessageBox::information(this, tr("错误"), tr("要求输入值不小于低阈值且不大于255"));
            if(value < ui->lSlider->value()) {
                ui->hEdit->setText(QString::number(ui->lSlider->value(), 10));
                ui->hSlider->setValue(ui->lSlider->value());
            } else {
                ui->hEdit->setText(QString::number(255, 10));
                ui->hSlider->setValue(255);
            }
        }
    }
}

void BinaryDialog::on_hSlider_valueChanged(int value)
{

    if(ui->hSlider->hasFocus()){
        if(ui->hSlider->value() < ui->lSlider->value()) {
            ui->hSlider->setValue(ui->lSlider->value());
            ui->hEdit->setText(QString::number(ui->lSlider->value(), 10));
        } else{
            ui->hEdit->setText(QString::number(value, 10));
        }
    }

    //MainWindow *ptr = (MainWindow*)parentWidget();

}

void BinaryDialog::on_lEdit_textEdited(const QString &arg1)
{
    bool ok;
    qint32 value = arg1.toInt(&ok, 10);

    if(value >= 0 && value <= ui->hSlider->value()) {
        ui->lSlider->setValue(value);
    }
}

void BinaryDialog::on_lEdit_editingFinished()
{
    if(ui->lEdit->hasFocus()){
        bool ok;
        qint32 value = ui->lEdit->text().toInt(&ok, 10);

        if(value < 0 || value > ui->hSlider->value()) {
            QMessageBox::information(this, tr("错误"), tr("要求输入值不小于0且不大于高阈值"));
            if(value > ui->hSlider->value()) {
                ui->lEdit->setText(QString::number(ui->hSlider->value(), 10));
                ui->lSlider->setValue(ui->hSlider->value());
            } else {
                ui->lEdit->setText(QString::number(0, 10));
                ui->lSlider->setValue(0);
            }
        }
    }
}

void BinaryDialog::on_lSlider_valueChanged(int value)
{

    if(ui->lSlider->hasFocus()){
        if(ui->hSlider->value() < ui->lSlider->value()) {
            ui->lSlider->setValue(ui->hSlider->value());
            ui->lEdit->setText(QString::number(ui->hSlider->value(), 10));
        } else {
            ui->lEdit->setText(QString::number(value, 10));
        }
    }

    //MainWindow *ptr = (MainWindow*)parentWidget();
}

