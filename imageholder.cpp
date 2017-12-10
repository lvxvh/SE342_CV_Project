#include <imageholder.h>
#include "ui_MainWindow.h"
#include <QFileDialog>
#include <QMessageBox>
#include <QObject>
#include "qhsl.h"

ImageHolder::ImageHolder()
{
    displayHeight = 0;
    displayWidth = 0;

}

ImageHolder::~ImageHolder()
{
}

bool ImageHolder::loadImage(MainWindow *m)
{
    filename = QFileDialog::getOpenFileName(m, QString::fromLocal8Bit("选择图像"), "", QObject::tr("Images (*.png *.bmp *.jpg *.tif *.GIF )"));
    if(!filename.isEmpty()) {
        if(originImage.load(filename)) {
            displayImage = originImage;
            tmpImage = originImage;
            QPixmap pix = QPixmap::fromImage(displayImage);
            Ui::MainWindow *ui = m->getUi();
            ui->image->setPixmap(pix);
            m->setUi(ui);
            displayWidth = displayImage.width();
            displayHeight = displayImage.height();
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
    return displayImage.save(filename);
}

bool ImageHolder::saveAs(MainWindow *m)
{
    QString newName = QFileDialog::getSaveFileName(m, "存储为");
    if(newName.isEmpty()) return false;
    return displayImage.save(newName);
}

void ImageHolder::fitScreen(MainWindow *m)
{
    qint32 iWidth = originImage.width();
    qint32 iHeight = originImage.height();
    Ui::MainWindow *ui = m->getUi();

    qreal areaWidth = ui->scrollArea->width();
    qreal areaHeight = ui->scrollArea->height();
    qreal scale = (iWidth/areaWidth > iHeight/areaHeight) ? iWidth/areaWidth : iHeight/areaHeight;
    displayWidth = floor(iWidth/scale);
    displayHeight = floor(iHeight/scale);
    displayImage = displayImage.scaled(displayWidth, displayHeight, Qt::KeepAspectRatio);
    tmpImage = tmpImage.scaled(displayWidth, displayHeight, Qt::KeepAspectRatio);
    QPixmap pix = QPixmap::fromImage(displayImage);
    ui->image->setPixmap(pix);

    m->setUi(ui);

}

void ImageHolder::actualPix(MainWindow *m)
{   
    displayWidth = originImage.width();
    displayHeight = originImage.height();
    displayImage = displayImage.scaled(displayWidth, displayHeight, Qt::KeepAspectRatio);
    tmpImage = tmpImage.scaled(displayWidth, displayHeight, Qt::KeepAspectRatio);
    QPixmap pix = QPixmap::fromImage(displayImage);
    Ui::MainWindow *ui = m->getUi();
    ui->image->setPixmap(pix);
    m->setUi(ui);

}

void ImageHolder::rgbChannel(MainWindow *m, qint32 color)
{
    switch (color) {
    case RGB_R:
        for(int y = 0;y < displayHeight; ++y){
            for(int x = 0;x < displayWidth; ++x){
                QRgb pixel = tmpImage.pixel(x,y);
                displayImage.setPixel(x, y, qRgb(qRed(pixel), qRed(pixel), qRed(pixel)));
            }
        }
        break;
    case RGB_G:
        for(int y = 0;y < displayHeight; ++y){
            for(int x = 0;x < displayWidth; ++x){
                QRgb pixel = tmpImage.pixel(x,y);
                displayImage.setPixel(x, y, qRgb(qGreen(pixel), qGreen(pixel), qGreen(pixel)));
            }
        }
        break;
    case RGB_B:
        for(int y = 0;y < displayHeight; ++y){
            for(int x = 0;x < displayWidth; ++x){
                QRgb pixel = tmpImage.pixel(x,y);
                displayImage.setPixel(x, y, qRgb(qBlue(pixel), qBlue(pixel), qBlue(pixel)));
            }
        }
        break;
    default:
        bool r = color & 1;
        bool g = (color >> 1) & 1;
        bool b = (color >> 2) & 1;
        for(int y = 0;y < displayHeight; ++y){
            for(int x = 0;x < displayWidth; ++x){
                QRgb pixel = tmpImage.pixel(x,y);
                displayImage.setPixel(x, y, qRgb(qRed(pixel)*r, qGreen(pixel)*g, qBlue(pixel)*b));
            }
        }
        break;
    }

    QPixmap pix = QPixmap::fromImage(displayImage);

    Ui::MainWindow *ui = m->getUi();
    ui->image->setPixmap(pix);
    m->setUi(ui);
}

void ImageHolder::toGray(MainWindow *m)
{
    for(int y = 0;y < displayHeight; ++y){
        for(int x = 0;x < displayWidth; ++x){
            QRgb pixel = tmpImage.pixel(x,y);
            qint32 r=qRed(pixel);
            qint32 g=qGreen(pixel);
            qint32 b=qBlue(pixel);
            qint32 gray = qGray(r, g, b); //Gray = (R * 11 + G * 16 + B * 5)/32
            displayImage.setPixel(x, y, qRgb(gray, gray, gray));
        }
    }
    QPixmap pix = QPixmap::fromImage(displayImage);

    Ui::MainWindow *ui = m->getUi();
    ui->image->setPixmap(pix);
    m->setUi(ui);
}

void ImageHolder::changeHue(MainWindow *m, int offset)
{
    for(int y = 0; y < displayHeight; ++y){
        for(int x = 0;x < displayWidth; ++x){
            QRgb pixel = tmpImage.pixel(x, y);
            QHsl hsl = QHsl(pixel);
            hsl.setHue(hsl.getHue() + offset);
            displayImage.setPixel(x, y, hsl.toRgb());
        }
    }
    QPixmap pix = QPixmap::fromImage(displayImage);

    Ui::MainWindow *ui = m->getUi();
    ui->image->setPixmap(pix);
    m->setUi(ui);
}

QRgb ImageHolder::getRgb(qint32 x, qint32 y)
{
    return displayImage.pixel(x, y);
}

qint32 ImageHolder::getDisplayHeight() const
{
    return displayHeight;
}

qint32 ImageHolder::getDisplayWidth() const
{
    return displayWidth;
}
