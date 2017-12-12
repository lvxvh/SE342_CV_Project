#include "mainwindow.h"
#include "historydialog.h"
#include "ui_historydialog.h"
#include <QPushButton>
#include <QBoxLayout>


historyDialog::historyDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::historyDialog)
{
    setFixedSize(200,250);
    ui->setupUi(this);
    freshLogs();
    connect(this, SIGNAL(sendIndex(int)), parent, SLOT(changeVersion(int)));
    connect(parent, SIGNAL(refreshLog()), this, SLOT(receiveRefreshSig()));
}

historyDialog::~historyDialog()
{
    delete ui;
}

void historyDialog::freshLogs()
{
    QVBoxLayout *vLayout;
    if(ui->histories->layout() != NULL) { //clean
        vLayout = (QVBoxLayout*)(ui->histories->layout());
        int itemCount = vLayout->count();
        for(int i = (itemCount - 1);i >= 0;--i) {
            QLayoutItem *item = vLayout->takeAt(i);
            if(item != 0) {
                vLayout->removeWidget(item->widget());
                delete item->widget();
            }
        }
        delete vLayout;
    }
    vLayout = new QVBoxLayout();
    vLayout->setMargin(0);
    vLayout->setSpacing(0);
    MainWindow *ptr = (MainWindow*)parentWidget();
    QVector<QString> logs = ptr->getIh()->getLogs();
    int cur = ptr->getIh()->getImgPtr();
    for(int i = 0; i < logs.size();i++){
        QPushButton *btn = new QPushButton(ui->histories);
        btn->setObjectName(QString::number(i, 10));
        if (i == cur) {
            btn->setFocus();
        }
        btn->setText(logs[i]);
        connect(btn, SIGNAL(clicked()), this, SLOT(chooseVersion()));
        vLayout->addWidget(btn);
    }
    vLayout->addStretch();
    ui->histories->setLayout(vLayout);
}

void historyDialog::receiveRefreshSig()
{
    freshLogs();
}

void historyDialog::chooseVersion()
{
    QPushButton *btn = (QPushButton*)sender();
    bool ok;
    int index = btn->objectName().toInt(&ok, 10);
    emit sendIndex(index);
}
