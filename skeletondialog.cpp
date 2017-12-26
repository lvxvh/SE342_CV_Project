#include "skeletondialog.h"
#include "ui_skeletondialog.h"
#include "mainwindow.h"

SkeletonDialog::SkeletonDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SkeletonDialog)
{
    ui->setupUi(this);
}

SkeletonDialog::~SkeletonDialog()
{
    delete ui;
}

void SkeletonDialog::on_extractButton_clicked()
{
    MainWindow *m = (MainWindow *)parentWidget();
    m->getIh()->skeleton(sn);
}

void SkeletonDialog::on_rebuildButton_clicked()
{
    MainWindow *m = (MainWindow *)parentWidget();
    m->getIh()->skeletonRebuild(sn);
}
