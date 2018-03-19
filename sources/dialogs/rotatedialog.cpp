#include "headers/rotatedialog.h"
#include "ui_rotatedialog.h"
#include "headers/mainwindow.h"
#include <QMessageBox>

RotateDialog::RotateDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::RotateDialog)
{
    setFixedSize(292,217);
    ui->setupUi(this);
}

RotateDialog::~RotateDialog()
{
    delete ui;
}

void RotateDialog::on_angleSlider_valueChanged(int value)
{
    if(ui->angleSlider->hasFocus()){
        ui->angleEdit->setText(QString::number(value, 10));
    }
    MainWindow * ptr = (MainWindow *)parentWidget();
    if(ui->bilinerButton->isChecked()){
        ptr->getIh()->rotate(value, 1);
    } else {
        ptr->getIh()->rotate(value, 0);
    }
}

void RotateDialog::on_angleEdit_editingFinished()
{
    if(ui->angleEdit->hasFocus()){
        bool ok;
        qint32 value = ui->angleEdit->text().toInt(&ok, 10);

        if(value < -180 || value > 180) {
            QMessageBox::information(this, tr("错误"), tr("要求输入值为-180~180范围内的整数，已插入最近数值"));
            if(value < -180) {
                ui->angleEdit->setText(QString::number(-180, 10));
                ui->angleSlider->setValue(-180);
            } else {
                ui->angleEdit->setText(QString::number(180, 10));
                ui->angleSlider->setValue(180);
            }
        }
    }
}

void RotateDialog::on_angleEdit_textEdited(const QString &arg1)
{
    bool ok;
    qint32 value = arg1.toInt(&ok, 10);

    if(value >= -180 && value <= 180) {
        ui->angleSlider->setValue(value);
    }
}

void RotateDialog::on_confirmButton_clicked()
{
    MainWindow *ptr = (MainWindow*)parentWidget();
    ptr->getIh()->cacheImage(QObject::tr("旋转"));
    this->close();
}

void RotateDialog::on_cancelButton_clicked()
{
    MainWindow *ptr = (MainWindow*)parentWidget();
    ptr->getIh()->resetImage();
    this->close();
}

void RotateDialog::closeEvent(QCloseEvent *)
{
    MainWindow *ptr = (MainWindow*)parentWidget();
    ptr->getIh()->resetImage();
}
