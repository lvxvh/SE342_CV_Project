#include "hsldialog.h"
#include "mainwindow.h"
#include "ui_hsldialog.h"

#include <QMessageBox>

hslDialog::hslDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::hslDialog)
{
    setFixedSize(512,320);
    ui->setupUi(this);
}

hslDialog::~hslDialog()
{
    delete ui;
}

void hslDialog::on_hEdit_textEdited(const QString &arg1)
{
    bool ok;
    qint32 value = arg1.toInt(&ok, 10);

    if(value >= -180 && value <= 180) {
        ui->hSlider->setValue(value);
    }
}

void hslDialog::on_hSlider_valueChanged(int value)
{
    if(ui->hSlider->hasFocus()){
        ui->hEdit->setText(QString::number(value, 10));
    }

    MainWindow *ptr = (MainWindow*)parentWidget();
    ptr->changeHue(value);
}

void hslDialog::on_hEdit_editingFinished()
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


