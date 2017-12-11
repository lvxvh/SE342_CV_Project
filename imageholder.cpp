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
    reseted = 0;
    imgPtr = -1;
}

ImageHolder::~ImageHolder()
{
    images.clear();
}

bool ImageHolder::loadImage(MainWindow *m)
{
    if (!images.isEmpty()) images.clear();
    filename = QFileDialog::getOpenFileName(m, QObject::tr("选择图像"), "", QObject::tr("Images (*.png *.bmp *.jpg *.tif *.GIF )"));
    if(!filename.isEmpty()) {
        QImage originImage;
        if(originImage.load(filename)) {
            cacheImage(originImage);
            displayImage = originImage;
            QPixmap pix = QPixmap::fromImage(displayImage);
            Ui::MainWindow *ui = m->getUi();
            ui->image->setPixmap(pix);
            m->setUi(ui);
            displayWidth = displayImage.width();
            displayHeight = displayImage.height();
            return true;
        } else {
            QMessageBox::information(m, QObject::tr("打开图像失败"), QObject::tr("打开图像失败!"));
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
    qint32 iWidth = displayImage.width();
    qint32 iHeight = displayImage.height();
    Ui::MainWindow *ui = m->getUi();

    qreal areaWidth = ui->scrollArea->width();
    qreal areaHeight = ui->scrollArea->height();
    qreal scale = (iWidth/areaWidth > iHeight/areaHeight) ? iWidth/areaWidth : iHeight/areaHeight;
    displayWidth = iWidth/scale;
    displayHeight = iHeight/scale;
    displayImage = displayImage.scaled(displayWidth, displayHeight, Qt::IgnoreAspectRatio);
    cacheImage(displayImage);
    //tmpImage = tmpImage.scaled(displayWidth, displayHeight, Qt::IgnoreAspectRatio);
    QPixmap pix = QPixmap::fromImage(displayImage);
    ui->image->setPixmap(pix);

    m->setUi(ui);

}

void ImageHolder::actualPix(MainWindow *m)
{   
    displayWidth = images[0].width();
    displayHeight = images[0].height();
    displayImage = displayImage.scaled(displayWidth, displayHeight, Qt::IgnoreAspectRatio);
    cacheImage(displayImage);
    //tmpImage = tmpImage.scaled(displayWidth, displayHeight, Qt::IgnoreAspectRatio);
    QPixmap pix = QPixmap::fromImage(displayImage);
    Ui::MainWindow *ui = m->getUi();
    ui->image->setPixmap(pix);
    m->setUi(ui);

}

void ImageHolder::rgbChannel(MainWindow *m, qint32 color)
{
    QImage oldImage = images[imgPtr];
    switch (color) {
    case RGB_R:
        for(int y = 0;y < displayHeight; ++y){
            for(int x = 0;x < displayWidth; ++x){
                QRgb pixel = oldImage.pixel(x,y);
                displayImage.setPixel(x, y, qRgb(qRed(pixel), qRed(pixel), qRed(pixel)));
            }
        }
        break;
    case RGB_G:
        for(int y = 0;y < displayHeight; ++y){
            for(int x = 0;x < displayWidth; ++x){
                QRgb pixel = oldImage.pixel(x,y);
                displayImage.setPixel(x, y, qRgb(qGreen(pixel), qGreen(pixel), qGreen(pixel)));
            }
        }
        break;
    case RGB_B:
        for(int y = 0;y < displayHeight; ++y){
            for(int x = 0;x < displayWidth; ++x){
                QRgb pixel = oldImage.pixel(x,y);
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
                QRgb pixel = oldImage.pixel(x,y);
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
            QRgb pixel = displayImage.pixel(x,y);
            qint32 r=qRed(pixel);
            qint32 g=qGreen(pixel);
            qint32 b=qBlue(pixel);
            qint32 gray = qGray(r, g, b); //Gray = (R * 11 + G * 16 + B * 5)/32
            displayImage.setPixel(x, y, qRgb(gray, gray, gray));
        }
    }
    cacheImage(displayImage);
    QPixmap pix = QPixmap::fromImage(displayImage);

    Ui::MainWindow *ui = m->getUi();
    ui->image->setPixmap(pix);
    m->setUi(ui);
}

void ImageHolder::changeHue(MainWindow *m, int offset)
{
    for(int y = 0; y < displayHeight; ++y){
        for(int x = 0;x < displayWidth; ++x){
            QRgb pixel = displayImage.pixel(x, y);
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

void ImageHolder::changeSaturation(MainWindow *m, int para)
{
    float percent = para/100.0f;
    float alpha, s, l;
    int r,g,b;
    for(int y = 0; y < displayHeight; ++y){
        for(int x = 0;x <displayWidth; ++x){
            QRgb pixel = displayImage.pixel(x, y);
            r = qRed(pixel);
            g = qGreen(pixel);
            b = qBlue(pixel);
            QHsl hsl = QHsl(pixel);
            s = hsl.getSaturation();
            l = hsl.getLightness();
            if(percent >= 0){
                if(percent + s >= 1){
                    alpha = s;
                } else {
                    alpha = 1 - percent;
                }
                alpha = 1/alpha - 1;               
                r = r + floor((r - floor(l * 255))*alpha);
                if (r < 0) r = 0;
                if (r > 255) r = 255;
                g = g + floor((g - floor(l * 255))*alpha);
                if (g < 0) g = 0;
                if (g > 255) g = 255;
                b = b + floor((b - floor(l * 255))*alpha);
                if (b < 0) b = 0;
                if (b > 255) b = 255;
            } else {
                alpha = percent;
                r = floor(l*255) + floor((r - floor(l * 255))*(1 + alpha));
                g = floor(l*255) + floor((g - floor(l * 255))*(1 + alpha));
                b = floor(l*255) + floor((b - floor(l * 255))*(1 + alpha));
            }
            displayImage.setPixel(x, y, qRgb(r,g,b));
        }
    }
    QPixmap pix = QPixmap::fromImage(displayImage);

    Ui::MainWindow *ui = m->getUi();
    ui->image->setPixmap(pix);
    m->setUi(ui);
}

void ImageHolder::cacheImage(QImage image)
{
    if(reseted) {
        images.erase(images.begin() + (imgPtr + 1));
        reseted = 0;
    }
    images.push_back(image);
    imgPtr++;
}

void ImageHolder::resetImage(MainWindow *m)
{
    if(imgPtr > 0){
        displayImage = images[0];
        reseted = 1;
        imgPtr = 0;
        QPixmap pix = QPixmap::fromImage(displayImage);

        Ui::MainWindow *ui = m->getUi();
        ui->image->setPixmap(pix);
        m->setUi(ui);
    }
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
