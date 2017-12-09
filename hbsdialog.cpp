#include "hbsdialog.h"
#include "ui_hbsdialog.h"

hbsDialog::hbsDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::hbsDialog)
{
    setFixedSize(512,320);
    ui->setupUi(this);
}

hbsDialog::~hbsDialog()
{
    delete ui;
}
