#include "watersheddialog.h"
#include "ui_watersheddialog.h"
#include "mainwindow.h"

WatershedDialog::WatershedDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::WatershedDialog)
{
    ui->setupUi(this);
}

WatershedDialog::~WatershedDialog()
{
    delete ui;
}

void WatershedDialog::on_cancelButton_clicked()
{
    MainWindow *m = (MainWindow *)parentWidget();
    m->setIsMarking(false);
    m->getIh()->resetImage();
    this->close();
}

void WatershedDialog::on_confirmButton_clicked()
{
    MainWindow *m = (MainWindow *)parentWidget();
    m->getIh()->watershed();
    m->setIsMarking(false);
    this->close();
}

void WatershedDialog::closeEvent(QCloseEvent *)
{
    MainWindow *m = (MainWindow *)parentWidget();
    m->getIh()->resetImage();
    m->setIsMarking(false);
    this->close();
}

