#include "bmbasicdialog.h"
#include "ui_bmbasicdialog.h"
#include "mainwindow.h"

#include <QPushButton>

BMBasicDialog::BMBasicDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::BMBasicDialog)
{
    ui->setupUi(this);
    button[0][0] = ui->button_00;
    button[0][1] = ui->button_01;
    button[0][2] = ui->button_02;
    button[1][0] = ui->button_10;
    button[1][1] = ui->button_11;
    button[1][2] = ui->button_12;
    button[2][0] = ui->button_20;
    button[2][1] = ui->button_21;
    button[2][2] = ui->button_22;
    for(int i = 0;i < 3;i++){
        for(int j = 0;j <3;j++){
            button[i][j]->setStyleSheet("background-color: rgb(255, 255, 255);color:rgb(0,0,0);");
        }
    }
    origin = QPoint(1,1);
    type = DIL;
}

BMBasicDialog::~BMBasicDialog()
{
    delete ui;
}

void BMBasicDialog::on_button_00_clicked()
{
    if(isChoosingOrigin){
        setCursor(Qt::ArrowCursor);
        button[0][0]->setText("+");
        button[origin.x()][origin.y()]->setText(" ");
        origin = QPoint(0,0);
    } else {
        if(se[0][0]){
            se[0][0] = 0;
            button[0][0]->setStyleSheet("background-color: rgb(255, 255, 255);color:rgb(0,0,0);");
        }else{
            se[0][0] = 1;
            button[0][0]->setStyleSheet("background-color: rgb(0,0,0);color:rgb(255, 255, 255);");
        }
    }
}

void BMBasicDialog::on_button_01_clicked()
{
    if(isChoosingOrigin){
        setCursor(Qt::ArrowCursor);
        button[0][1]->setText("+");
        button[origin.x()][origin.y()]->setText(" ");
        origin = QPoint(0,1);
        isChoosingOrigin = 0;
    } else {
        if(se[0][1]){
            se[0][1] = 0;
            button[0][1]->setStyleSheet("background-color: rgb(255, 255, 255);color:rgb(0,0,0);");
        }else{
            se[0][1] = 1;
            button[0][1]->setStyleSheet("background-color: rgb(0,0,0);color:rgb(255, 255, 255);");
        }
    }
}

void BMBasicDialog::on_button_02_clicked()
{
    if(isChoosingOrigin){
        setCursor(Qt::ArrowCursor);
        button[0][2]->setText("+");
        button[origin.x()][origin.y()]->setText(" ");
        origin = QPoint(0,2);
        isChoosingOrigin = 0;
    } else {
        if(se[0][2]){
            se[0][2] = 0;
            button[0][2]->setStyleSheet("background-color: rgb(255, 255, 255);color:rgb(0,0,0);");
        }else{
            se[0][2] = 1;
            button[0][2]->setStyleSheet("background-color: rgb(0,0,0);color:rgb(255, 255, 255);");
        }
    }
}

void BMBasicDialog::on_button_10_clicked()
{
    if(isChoosingOrigin){
        setCursor(Qt::ArrowCursor);
        button[1][0]->setText("+");
        button[origin.x()][origin.y()]->setText(" ");
        origin = QPoint(1,0);
        isChoosingOrigin = 0;
    } else {
        if(se[1][0]){
            se[1][0] = 0;
            button[1][0]->setStyleSheet("background-color: rgb(255, 255, 255);color:rgb(0,0,0);");
        }else{
            se[1][0] = 1;
            button[1][0]->setStyleSheet("background-color: rgb(0,0,0);color:rgb(255, 255, 255);");
        }
    }
}

void BMBasicDialog::on_button_11_clicked()
{
    if(isChoosingOrigin){
        setCursor(Qt::ArrowCursor);
        button[1][1]->setText("+");
        button[origin.x()][origin.y()]->setText(" ");
        origin = QPoint(1,1);
        isChoosingOrigin = 0;
    } else {
        if(se[1][1]){
            se[1][1] = 0;
            button[1][1]->setStyleSheet("background-color: rgb(255, 255, 255);color:rgb(0,0,0);");
        }else{
            se[1][1] = 1;
            button[1][1]->setStyleSheet("background-color: rgb(0,0,0);color:rgb(255, 255, 255);");
        }
    }
}

void BMBasicDialog::on_button_12_clicked()
{
    if(isChoosingOrigin){
        setCursor(Qt::ArrowCursor);
        button[1][2]->setText("+");
        button[origin.x()][origin.y()]->setText(" ");
        origin = QPoint(1,2);
        isChoosingOrigin = 0;
    } else {
        if(se[1][2]){
            se[1][2] = 0;
            button[1][2]->setStyleSheet("background-color: rgb(255, 255, 255);color:rgb(0,0,0);");
        }else{
            se[1][2] = 1;
            button[1][2]->setStyleSheet("background-color: rgb(0,0,0);color:rgb(255, 255, 255);");
        }
    }
}

void BMBasicDialog::on_button_20_clicked()
{
    if(isChoosingOrigin){
        setCursor(Qt::ArrowCursor);
        button[2][0]->setText("+");
        button[origin.x()][origin.y()]->setText(" ");
        origin = QPoint(2,0);
        isChoosingOrigin = 0;
    } else {
        if(se[2][0]){
            se[2][0] = 0;
            button[2][0]->setStyleSheet("background-color: rgb(255, 255, 255);color:rgb(0,0,0);");
        }else{
            se[2][0] = 1;
            button[2][0]->setStyleSheet("background-color: rgb(0,0,0);color:rgb(255, 255, 255);");
        }
    }
}

void BMBasicDialog::on_button_21_clicked()
{
    if(isChoosingOrigin){
        setCursor(Qt::ArrowCursor);
        button[2][1]->setText("+");
        button[origin.x()][origin.y()]->setText(" ");
        origin = QPoint(2,1);
        isChoosingOrigin = 0;
    } else {
        if(se[2][1]){
            se[2][1] = 0;
            button[2][1]->setStyleSheet("background-color: rgb(255, 255, 255);color:rgb(0,0,0);");
        }else{
            se[2][1] = 1;
            button[2][1]->setStyleSheet("background-color: rgb(0,0,0);color:rgb(255, 255, 255);");
        }
    }
}

void BMBasicDialog::on_button_22_clicked()
{
    if(isChoosingOrigin){
        setCursor(Qt::ArrowCursor);
        button[2][2]->setText("+");
        button[origin.x()][origin.y()]->setText(" ");
        origin = QPoint(2,2);
        isChoosingOrigin = 0;
    } else {
        if(se[2][2]){
            se[2][2] = 0;
            button[2][2]->setStyleSheet("background-color: rgb(255, 255, 255);color:rgb(0,0,0);");
        }else{
            se[2][2] = 1;
            button[2][2]->setStyleSheet("background-color: rgb(0,0,0);color:rgb(255, 255, 255);");
        }
    }
}

void BMBasicDialog::on_originButton_clicked()
{
    setCursor(Qt::PointingHandCursor);
    isChoosingOrigin = 1;
}

void BMBasicDialog::on_confirmButton_clicked()
{
    MainWindow *ptr = (MainWindow*)parentWidget();
    if(type == DIL){
        ptr->getIh()->morphoBasic(0, se, origin);

    } else if(type == ERO){
        ptr->getIh()->morphoBasic(1, se, origin);

    } else if(type == OPN){
        ptr->getIh()->morphoBasic(2, se, origin);

    } else{
        ptr->getIh()->morphoBasic(3, se, origin);

    }
    this->close();
}

void BMBasicDialog::on_cancelButton_clicked()
{
    MainWindow *ptr = (MainWindow*)parentWidget();
    ptr->getIh()->resetImage();
    this->close();
}

void BMBasicDialog::on_comboBox_currentIndexChanged(int index)
{
    switch (index) {
    case 0:
        type = DIL;
        break;
    case 1:
        type = ERO;
        break;
    case 2:
        type = OPN;
        break;
    default:
        type = CLS;
        break;
    }
}
