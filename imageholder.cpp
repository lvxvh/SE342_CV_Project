#include <imageholder.h>
#include "ui_MainWindow.h"
#include <QFileDialog>
#include <QMessageBox>
#include <QObject>

ImageHolder::ImageHolder()
{
}

ImageHolder::~ImageHolder()
{
}

bool ImageHolder::loadImage(QWidget *m, Ui::MainWindow *ui)
{
    filename = QFileDialog::getOpenFileName(m, QString::fromLocal8Bit("选择图像"), "", QObject::tr("Images (*.png *.bmp *.jpg *.tif *.GIF )"));
    if(!filename.isEmpty()) {
        if(image.load(filename)) {
            ui->image->setPixmap(QPixmap::fromImage(image));
            return true;
        } else {
            QMessageBox::information(m, QString::fromLocal8Bit("打开图像失败"), QString::fromLocal8Bit("打开图像失败!"));
            //delete image;
            return false;
        }
    } else {
       return false;
    }
}

bool ImageHolder::save()
{
    return image.save(filename);
}

bool ImageHolder::saveAs(QWidget *m)
{
    QString newName = QFileDialog::getSaveFileName(m, "存储为");
    if(newName.isEmpty()) return false;
    return image.save(newName);
}

void ImageHolder::fitScreen(Ui::MainWindow *ui)
{
    QPixmap pix = QPixmap::fromImage(image);
    qreal pixWidth = pix.width();
    qreal pixHeight = pix.height();
    qreal areaWidth = ui->scrollArea->width();
    qreal areaHeight = ui->scrollArea->height();
    qreal scale = (pixWidth/areaWidth > pixHeight/areaHeight) ? pixWidth/areaWidth : pixHeight/areaHeight;
    ui->image->setPixmap(QPixmap::fromImage(image).scaled(pixWidth/scale, pixHeight/scale, Qt::KeepAspectRatio));
}

void ImageHolder::actualPix(Ui::MainWindow *ui)
{
    QPixmap pix = QPixmap::fromImage(image);
    ui->image->setPixmap(QPixmap::fromImage(image));
}
