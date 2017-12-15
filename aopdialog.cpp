#include "aopdialog.h"
#include "mainwindow.h"
#include "ui_aopdialog.h"
#include <QMessageBox>

AOPDialog::AOPDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AOPDialog)
{  
    ui->setupUi(this);
    connect(parent, SIGNAL(sendLists(int)), this, SLOT(receiveLists(int)));
}

AOPDialog::~AOPDialog()
{
    delete ui;
}

void AOPDialog::receiveLists(int count)
{
    for(int i = 0;i < count;++i){
        ui->aBox->addItem(tr("图") + QString::number(i + 1, 10));
        ui->bBox->addItem(tr("图") + QString::number(i + 1, 10));
    }
}

void AOPDialog::on_confirmButton_clicked()
{
    int aIndex = ui->aBox->currentIndex();
    int bIndex = ui->bBox->currentIndex();
    if(aIndex == -1 || bIndex == -1){
        QMessageBox::information(this, QObject::tr("提示"), QObject::tr("请选择图像"));
    } else {
        MainWindow *ptr = (MainWindow *)parentWidget();
        if(ptr->sizeEqual(aIndex, bIndex)){

        } else {
            QMessageBox::information(this, QObject::tr("提示"), QObject::tr("图像尺寸不同！"));
        }
    }

}
