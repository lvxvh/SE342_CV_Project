#include "cropdialog.h"
#include "mainwindow.h"
#include "ui_cropdialog.h"
#include <QMessageBox>
#include <QDebug>

CropDialog::CropDialog(int w, int h, QWidget *parent) :
    oWidth(w),
    oHeight(h),
    QDialog(parent),
    ui(new Ui::CropDialog)
{
    //setWindowFlags(Qt::WindowStaysOnTopHint);
    ui->setupUi(this);
    ui->widthLabel->setText(QString::number(oWidth, 10));
    ui->heightLabel->setText(QString::number(oHeight, 10));
    connect(parent, SIGNAL(sendRectGeo(int,int,int,int)), this, SLOT(receiveRecGeo(int,int,int,int)));
    connect(this, SIGNAL(sendEditedGeo(int,int,int,int)), parent, SLOT(receiveEditedGeo(int,int,int,int)));
}

CropDialog::~CropDialog()
{
    delete ui;
}

void CropDialog::receiveRecGeo(int x, int y, int w, int h)
{
    ui->xEdit->setText(QString::number(x, 10));
    ui->yEdit->setText(QString::number(y, 10));
    ui->widthEdit->setText(QString::number(w, 10));
    ui->heightEdit->setText(QString::number(h, 10));
}

void CropDialog::on_xEdit_editingFinished()
{
    if(ui->xEdit->hasFocus()){
        bool ok;
        qint32 value = ui->xEdit->text().toInt(&ok, 10);

        if(value > oWidth - 1) {
            QMessageBox::information(this, tr("错误"), tr("截图起点不在原图范围内"));
            ui->xEdit->setText(QString::number(0, 10));
        }
        reportChange();
    }
}

void CropDialog::on_yEdit_editingFinished()
{
    if(ui->yEdit->hasFocus()){
        bool ok;
        qint32 value = ui->yEdit->text().toInt(&ok, 10);

        if(value > oHeight - 1) {
            QMessageBox::information(this, tr("错误"), tr("截图起点不在原图范围内"));
            ui->yEdit->setText(QString::number(0, 10));
        }
        reportChange();

    }
}

void CropDialog::on_widthEdit_editingFinished()
{
    if(ui->widthEdit->hasFocus()){
        bool ok;
        qint32 value = ui->widthEdit->text().toInt(&ok, 10);
        qint32 base = ui->xEdit->text().toInt(&ok, 10);

        if(base + value > oWidth - 1) {
            QMessageBox::information(this, tr("错误"), tr("截图超出范围"));
            ui->widthEdit->setText(QString::number(0, 10));
        }
        reportChange();
    }
}

void CropDialog::on_heightEdit_editingFinished()
{
    if(ui->heightEdit->hasFocus()){
        bool ok;
        qint32 value = ui->heightEdit->text().toInt(&ok, 10);
        qint32 base = ui->yEdit->text().toInt(&ok, 10);

        if(base + value > oHeight - 1) {
            QMessageBox::information(this, tr("错误"), tr("截图超出范围"));
            ui->widthEdit->setText(QString::number(0, 10));
        }
        reportChange();
    }
}

void CropDialog::on_confirmButton_clicked()
{
    MainWindow *m = (MainWindow *)parentWidget();

    m->getIh()->crop(QRect(ui->xEdit->text().toInt(), ui->yEdit->text().toInt(),
                           ui->widthEdit->text().toInt(), ui->heightEdit->text().toInt()));
    this->close();
}

void CropDialog::on_cancelButton_clicked()
{
    MainWindow *m = (MainWindow *)parentWidget();
    m->setIsCropping(false);
    m->getIh()->resetImage();
    this->close();
}

void CropDialog::reportChange()
{
    sendEditedGeo(ui->xEdit->text().toInt(), ui->yEdit->text().toInt(),
                  ui->widthEdit->text().toInt(), ui->heightEdit->text().toInt());
}

void CropDialog::closeEvent(QCloseEvent *e)
{
    MainWindow *m = (MainWindow *)parentWidget();

    m->getIh()->resetImage();
    m->setIsCropping(false);
    this->close();
}
