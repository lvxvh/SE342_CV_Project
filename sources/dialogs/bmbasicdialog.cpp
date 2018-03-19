#include "headers/bmbasicdialog.h"
#include "ui_bmbasicdialog.h"
#include "headers/mainwindow.h"

#include <QPushButton>
#include <QMessageBox>

BMBasicDialog::BMBasicDialog(BMType Ttype, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::BMBasicDialog)
{
    ui->setupUi(this);
    this->Ttype = Ttype;

    if(Ttype == BASIC || Ttype == GBM){
        type = DIL;
    } else {
        connect(parent, SIGNAL(sendLists(int)), this, SLOT(receiveLists(int)));
        for(int i = 3;i >=0;i--){
            ui->typeBox->removeItem(i);
        }
        ui->typeBox->addItem("重建开");
        ui->typeBox->addItem("重建闭");
        ui->typeBox->addItem("膨胀重建");
        ui->typeBox->addItem("腐蚀重建");
    }
    sType = SQR;
    ui->templateLabel->hide();
    ui->templateBox->hide();
}

BMBasicDialog::~BMBasicDialog()
{
    delete ui;
}

void BMBasicDialog::receiveLists(int count)
{
    for(int i = 0;i < count;++i){
        ui->templateBox->addItem(tr("图") + QString::number(i + 1, 10));
    }
}

void BMBasicDialog::on_confirmButton_clicked()
{
    MainWindow *ptr = (MainWindow*)parentWidget();
    QVector<QVector<int>> se;
    QSize size;
    size.setHeight(ui->heightEdit->text().toInt());
    size.setWidth(ui->widthEdit->text().toInt());
    QPoint origin;
    origin.setX(ui->yEdit->text().toInt());
    origin.setY(ui->xEdit->text().toInt());
    ptr->getIh()->genSe(sType, size, se);
    QImage tmp;
    if(Ttype == REBUILD || Ttype == GREBUILD){
        tmp = ptr->getIhByIndex(ui->templateBox->currentIndex())->getDisplayImage();
    }
    switch (type) {
    case DIL:
        if(Ttype == BASIC)
            ptr->getIh()->morphoBasic(0, se, origin);
        else
            ptr->getIh()->grayMorphBasic(0, se, origin);
        break;
    case ERO:
        if(Ttype == BASIC)
            ptr->getIh()->morphoBasic(1, se, origin);
        else
            ptr->getIh()->grayMorphBasic(1, se, origin);
        break;
    case OPN:
        if(Ttype == BASIC)
            ptr->getIh()->morphoBasic(2, se, origin);
        else
            ptr->getIh()->grayMorphBasic(2, se, origin);
        break;
    case CLS:
        if(Ttype == BASIC)
            ptr->getIh()->morphoBasic(3, se, origin);
        else
            ptr->getIh()->grayMorphBasic(3, se, origin);
        break;
    case OPNR:
        if(Ttype == REBUILD)
            ptr->getIh()->morphoRebuild(4, se, origin);
        else
            ptr->getIh()->grayRebuild(4, se, origin);
        break;
    case CLSR:
        if(Ttype == REBUILD)
            ptr->getIh()->morphoRebuild(5, se, origin);
        else
            ptr->getIh()->grayRebuild(5, se, origin);
        break;
    case DILR:
        if(tmp.size() != ptr->getIh()->getDisplayImage().size()){
            QMessageBox::information(this, QObject::tr("提示"), QObject::tr("图像尺寸不同！"));
            break;
        }
        if(Ttype == REBUILD){
            if(!ptr->getIhByIndex(ui->templateBox->currentIndex())->isBinary()){
                QMessageBox::information(this, QObject::tr("提示"), QObject::tr("模板不是二值图像！"));
                break;
            }
            ptr->getIh()->rebuildDilation(tmp);
        }
        else{
            if(!tmp.isGrayscale()){
                QMessageBox::information(this, QObject::tr("提示"), QObject::tr("模板不是灰度图像！"));
                break;
            }
            ptr->getIh()->grayRebuildDilation(tmp);
        }
        break;
    default:
        if(Ttype == REBUILD) {
            if(!ptr->getIhByIndex(ui->templateBox->currentIndex())->isBinary()){
                QMessageBox::information(this, QObject::tr("提示"), QObject::tr("模板不是二值图像！"));
                break;
            }
            ptr->getIh()->rebuildErosion(tmp);
        }
        else {
            if(!tmp.isGrayscale()){
                QMessageBox::information(this, QObject::tr("提示"), QObject::tr("模板不是灰度图像！"));
                break;
            }
            ptr->getIh()->grayRebuildErosion(tmp);
        }
        break;
    }
    this->close();
}

void BMBasicDialog::on_cancelButton_clicked()
{
    MainWindow *ptr = (MainWindow*)parentWidget();
    ptr->getIh()->resetImage();
    this->close();
}

void BMBasicDialog::on_typeBox_currentIndexChanged(int index)
{
    if(Ttype == BASIC || Ttype == GBM){
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
    } else {
        switch (index) {
        case 0:
            type = OPNR;
            break;
        case 1:
            type = CLSR;
            break;
        case 2:
            ui->templateBox->show();
            ui->templateLabel->show();
            type = DILR;
            break;
        default:
            ui->templateBox->show();
            ui->templateLabel->show();
            type = EROR;
            break;
        }
    }
}

void BMBasicDialog::on_seBox_currentIndexChanged(int index)
{
    switch (index) {
    case 0:
        sType = SQR;
        break;
    case 1:
        sType = CRS;
        break;
    default:
        sType = ELL;
        break;
    }

}

void BMBasicDialog::on_xEdit_editingFinished()
{
    if(ui->xEdit->hasFocus()){
        int width = ui->widthEdit->text().toInt();
        int x = ui->xEdit->text().toInt();
        if(x >= width){
            QMessageBox::information(this, tr("错误"), tr("要求输入值小于宽度"));
            ui->xEdit->setText(QString::number(width - 1, 10));
        }
    }
}

void BMBasicDialog::on_yEdit_editingFinished()
{
    if(ui->yEdit->hasFocus()){
        int height = ui->heightEdit->text().toInt();
        int y = ui->yEdit->text().toInt();
        if(y >= height){
            QMessageBox::information(this, tr("错误"), tr("要求输入值小于高度"));
            ui->xEdit->setText(QString::number(height - 1, 10));
        }
    }
}

void BMBasicDialog::on_centerButton_clicked()
{
    int width = ui->widthEdit->text().toInt();
    int height = ui->heightEdit->text().toInt();
    int centerX = width/2;
    int centerY = height/2;
    ui->xEdit->setText(QString::number(centerX, 10));
    ui->yEdit->setText(QString::number(centerY, 10));
}

void BMBasicDialog::on_widthEdit_editingFinished()
{
    if(ui->widthEdit->hasFocus()){
        int width = ui->widthEdit->text().toInt();
        if(width < 2){
            QMessageBox::information(this, tr("错误"), tr("要求输入值大于1"));
            ui->widthEdit->setText(QString::number(3, 10));
        }
    }
}

void BMBasicDialog::on_heightEdit_editingFinished()
{
    if(ui->heightEdit->hasFocus()){
        int height = ui->heightEdit->text().toInt();
        if(height < 2){
            QMessageBox::information(this, tr("错误"), tr("要求输入值大于1"));
            ui->heightEdit->setText(QString::number(3, 10));
        }
    }
}
