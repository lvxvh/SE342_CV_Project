#include "headers/skeletondialog.h"
#include "ui_skeletondialog.h"
#include "headers/mainwindow.h"
#include <QMessageBox>

SkeletonDialog::SkeletonDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SkeletonDialog)
{
    ui->setupUi(this);
    extracted = 0;
}

SkeletonDialog::~SkeletonDialog()
{
    delete ui;
}

void SkeletonDialog::on_extractButton_clicked()
{
    MainWindow *m = (MainWindow *)parentWidget();
    m->getIh()->skeleton(sn);
    extracted = 1;
}

void SkeletonDialog::on_rebuildButton_clicked()
{
    if(extracted){
        MainWindow *m = (MainWindow *)parentWidget();
        m->getIh()->skeletonRebuild(sn);
        extracted = 0;
    } else {
        QMessageBox::information(this, QObject::tr("提示"), QObject::tr("请先提取骨架"));
    }
}
