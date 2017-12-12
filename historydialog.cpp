#include "mainwindow.h"
#include "historydialog.h"
#include "ui_historydialog.h"
#include <QPushButton>
#include <QBoxLayout>


historyDialog::historyDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::historyDialog)
{
    setFixedSize(320,320);
    ui->setupUi(this);

    QVBoxLayout *vLayout = new QVBoxLayout();
    vLayout->setMargin(0);
    vLayout->setSpacing(0);
    MainWindow *ptr = (MainWindow*)parentWidget();
    QVector<QString> logs = ptr->getIh()->getLogs();
    int cur = ptr->getIh()->getImgPtr();
    for(int i = 0; i < logs.size();i++){
        QPushButton *btn = new QPushButton(ui->histories);
        if (i == cur) {
            btn->setFocus();
        }
        btn->setText(logs[i]);
        vLayout->addWidget(btn);
    }
    vLayout->addStretch();
    ui->histories->setLayout(vLayout);
}

historyDialog::~historyDialog()
{
    delete ui;
}
