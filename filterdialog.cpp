#include "filterdialog.h"
#include "ui_filterdialog.h"
#include "mainwindow.h"

FilterDialog::FilterDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::FilterDialog)
{
    ui->setupUi(this);   
    edit[0][0] = ui->Edit_00;
    edit[0][1] = ui->Edit_01;
    edit[0][2] = ui->Edit_02;
    edit[0][3] = ui->Edit_03;
    edit[0][4] = ui->Edit_04;
    edit[1][0] = ui->Edit_10;
    edit[1][1] = ui->Edit_11;
    edit[1][2] = ui->Edit_12;
    edit[1][3] = ui->Edit_13;
    edit[1][4] = ui->Edit_14;
    edit[2][0] = ui->Edit_20;
    edit[2][1] = ui->Edit_21;
    edit[2][2] = ui->Edit_22;
    edit[2][3] = ui->Edit_23;
    edit[2][4] = ui->Edit_24;
    edit[3][0] = ui->Edit_30;
    edit[3][1] = ui->Edit_31;
    edit[3][2] = ui->Edit_32;
    edit[3][3] = ui->Edit_33;
    edit[3][4] = ui->Edit_34;
    edit[4][0] = ui->Edit_40;
    edit[4][1] = ui->Edit_41;
    edit[4][2] = ui->Edit_42;
    edit[4][3] = ui->Edit_43;
    edit[4][4] = ui->Edit_44;

    sigma = 1;
    type = AVE;
    size = 3;
    genMatrix();
}

FilterDialog::~FilterDialog()
{
    delete ui;
}

void FilterDialog::on_confirmButton_clicked()
{
    MainWindow *ptr = (MainWindow*)parentWidget();
    if(type == MID){
        ptr->getIh()->midFilter(size);
    }else {
        float **out = new float *[size];
        for(int i = 0;i < size;++i){
            out[i]=new float[size];
        }
        int begin = (5-size)/2;
        for(int i = 0;i < size;i++){
            for(int j = 0;j < size;j++){
                out[i][j] = edit[begin + i][begin + j]->text().toFloat();
            }
        }
        ptr->getIh()->filter(size, out);
        for(int i = 0;i < size;++i){
            delete out[i];
            out[i] = NULL;
        }
        delete out;
        out = NULL;
    }
    ptr->getIh()->draw();
    ptr->getIh()->cacheImage(QObject::tr("滤波器"));
    this->close();
}

void FilterDialog::on_cancelButton_clicked()
{
    MainWindow *ptr = (MainWindow*)parentWidget();
    ptr->getIh()->resetImage();
    this->close();
}

void FilterDialog::on_sizeBox_currentIndexChanged(int index)
{
    if(index == 0){
        size = 3;
    }else {
        size = 5;
    }
    genMatrix();
}

void FilterDialog::on_typeBox_currentIndexChanged(int index)
{
    if(index == 0){ // average
        type = AVE;
    }else if(index == 1){   //middle
        type = MID;
    } else{ //gaussian
        type = GAUS;
    }
    genMatrix();
}


void FilterDialog::closeEvent(QCloseEvent *)
{
    MainWindow *ptr = (MainWindow*)parentWidget();
    ptr->getIh()->resetImage();
}

void FilterDialog::on_sigmaEdit_editingFinished()
{
    sigma = ui->sigmaEdit->text().toFloat();
    genMatrix();
}

void FilterDialog::genMatrix()
{
    MainWindow *m = (MainWindow *)parentWidget();
    if(size == 3){
        for(int i = 0;i < 5;i++){
            edit[0][i]->hide();
            edit[4][i]->hide();
        }
        for(int i = 1;i < 4;i++){
            edit[i][0]->hide();
            edit[i][4]->hide();
        }
    } else {
        for(int i = 0;i < 5;i++){
            edit[0][i]->show();
            edit[4][i]->show();
        }
        for(int i = 1;i < 4;i++){
            edit[i][0]->show();
            edit[i][4]->show();
        }
    }

    if(type == AVE){
        ui->sigmaEdit->hide();
        ui->sigmaLabel->hide();
        float value = 1.0f/(size*size);
        int begin = (5-size)/2;
        int end = 5-(5-size)/2;
        for(int i = begin;i < end;i++){
            for(int j = begin;j < end;j++){
                edit[i][j]->setText( QString("%1").arg(value));
            }
        }
    } else if(type == MID){
        ui->sigmaEdit->hide();
        ui->sigmaLabel->hide();
        for(int i = 0;i < 5;++i){
            for(int j = 0;j < 5;++j){
                edit[i][j]->clear();
                edit[i][j]->setReadOnly(true);
            }
        }
    } else {
        ui->sigmaEdit->show();
        ui->sigmaLabel->show();
        float **gaus = new float *[size];
        for(int i = 0;i < size;++i){
            gaus[i]=new float[size];
        }
        m->getIh()->getGaussianKernal(size, sigma, gaus);
        int begin = (5-size)/2;
        for(int i = 0;i < size;i++){
            for(int j = 0;j < size;j++){
                edit[begin + i][begin + j]->setText(QString::number(gaus[i][j], 'f', 7));
            }
        }
        for(int i = 0;i < size;++i){
            delete(gaus[i]);
            gaus[i] = NULL;
        }
        delete gaus;
        gaus = NULL;
    }
}
