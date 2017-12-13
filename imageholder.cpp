#include <imageholder.h>
#include "ui_MainWindow.h"
#include <QFileDialog>
#include <QMessageBox>
#include <QObject>
#include "qhsl.h"

ImageHolder::ImageHolder(MainWindow *mw)
{
    m = mw;
    displayHeight = 0;
    displayWidth = 0;
    reseted = 0;
    imgPtr = -1;
}

ImageHolder::~ImageHolder()
{
    images.clear();
}

bool ImageHolder::loadImage()
{
    if (!images.isEmpty()) images.clear();
    filename = QFileDialog::getOpenFileName(m, QObject::tr("选择图像"), "", QObject::tr("Images (*.png *.bmp *.jpg *.tif *.GIF )"));
    if(!filename.isEmpty()) {
        QImage originImage;
        if(originImage.load(filename)) {
            displayImage = originImage;
            cacheImage(QObject::tr("打开"));
            draw();

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

bool ImageHolder::saveAs()
{
    QString newName = QFileDialog::getSaveFileName(m, "存储为");
    if(newName.isEmpty()) return false;
    return displayImage.save(newName);
}

void ImageHolder::fitScreen()
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
    cacheImage(QObject::tr("适应屏幕"));
    //tmpImage = tmpImage.scaled(displayWidth, displayHeight, Qt::IgnoreAspectRatio);
    draw();
}

void ImageHolder::actualPix()
{   
    displayWidth = images[0].width();
    displayHeight = images[0].height();
    displayImage = displayImage.scaled(displayWidth, displayHeight, Qt::IgnoreAspectRatio);
    cacheImage(QObject::tr("实际尺寸"));
    //tmpImage = tmpImage.scaled(displayWidth, displayHeight, Qt::IgnoreAspectRatio);
    draw();


}

void ImageHolder::rgbChannel(qint32 color)
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

    draw();

}

void ImageHolder::toGray()
{
    if(!displayImage.allGray()){
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
        cacheImage(QObject::tr("转为灰度图像"));
        draw();
    }
}

void ImageHolder::changeHsl(int hOffset, int sOffset, int lOffset)
{
    displayImage = images[imgPtr];
    float h, s, l;
    for(int y = 0; y < displayHeight; ++y){
        for(int x = 0;x < displayWidth; ++x){
            QRgb pixel = displayImage.pixel(x, y);
            QHsl hsl = QHsl(pixel);
            h = hsl.getHue();
            s = hsl.getSaturation();
            l = hsl.getLightness();

            if(hOffset != 0){
                hsl.setHue(h + hOffset);
            }

            if(sOffset != 0){
                float percent = sOffset/100.0f;
                if(percent >= 0) {
                    hsl.setSaturation(s + ((1-s)/100)*sOffset);
                } else {
                    hsl.setSaturation(s + (s/100)*sOffset);
                }
            }

            if(lOffset != 0){
                float percent = lOffset/100.0f;
                if(percent >= 0) {
                    hsl.setLightness(l + ((1-l)/100)*lOffset);
                } else {
                    hsl.setLightness(l + (l/100)*lOffset);
                }
            }

            displayImage.setPixel(x, y, hsl.toRgb());
        }
    }
    draw();
}

void ImageHolder::Otsu()
{
    int threshold = getOtsuThreshold();
    for(int y = 0;y < displayHeight;++y){
        for(int x = 0;x < displayWidth;++x){
            if(qRed(displayImage.pixel(x, y)) > threshold) {
                displayImage.setPixel(x,y,qRgb(255,255,255));
            } else {
                displayImage.setPixel(x,y,qRgb(0, 0, 0));
            }
        }
    }

    cacheImage(QObject::tr("Otsu"));
    draw();
}

int ImageHolder::getOtsuThreshold()
{

    float histogram[256] = {0};
    for(int y = 0;y < displayHeight;++y){
        for(int x = 0;x < displayWidth;++x){
            histogram[qRed(displayImage.pixel(x, y))]++;
        }
    }

    //normalize histogram & average gray
    int size = displayHeight*displayWidth;
    float u = 0;  //average gray
    for(int i = 0;i < 256;++i){
        histogram[i] = histogram[i]/size;
        u += i*histogram[i];
    }

    int threshold;
    float maxVariance = 0;
    float w0 = 0, totalGray = 0;
    for(int i = 0;i < 256;++i){
        w0 += histogram[i];
        totalGray += i*histogram[i];   //u0 = totalGray/w0

        float t = totalGray/w0 - u; // t = u0 - u
        float variance = t*t*w0/(1 - w0);
        if(variance > maxVariance){
            maxVariance = variance;
            threshold = i;
        }
    }
    return threshold;
}

void ImageHolder::dThreshold(int lo, int hi)
{
    displayImage = images[imgPtr];
    for(int y = 0;y < displayHeight;++y){
        for(int x = 0;x < displayWidth;++x){
            if(qRed(displayImage.pixel(x, y)) > lo && qRed(displayImage.pixel(x, y)) < hi) {
                displayImage.setPixel(x,y,qRgb(255,255,255));
            } else {
                displayImage.setPixel(x,y,qRgb(0, 0, 0));
            }
        }
    }
    draw();
}

void ImageHolder::cacheImage(QString msg)
{
    if(reseted) {
        images.erase(images.begin() + (imgPtr + 1), images.end());
        logs.erase(logs.begin() + (imgPtr + 1), logs.end());
        reseted = 0;
    }
    images.push_back(displayImage);
    logs.push_back(msg);
    imgPtr++;
    m->emitLogsignal();
}

void ImageHolder::draw()
{
    QPixmap pix = QPixmap::fromImage(displayImage);
    Ui::MainWindow *ui = m->getUi();
    ui->image->setPixmap(pix);
}

void ImageHolder::originImage()
{
    if(imgPtr > 0){
        displayImage = images[0];
        reseted = 1;
        imgPtr = 0;
        draw();

    }
}

void ImageHolder::resetImage()
{
    displayImage = images[imgPtr];
    draw();
}

void ImageHolder::changeVersion(int ptr)
{
    if(ptr != imgPtr) {
        displayImage = images[ptr];
        reseted = 1;
        imgPtr = ptr;
        draw();
    }
}

bool ImageHolder::isGray()
{
    return displayImage.allGray();
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

void ImageHolder::log(QString msg)
{
    logs.push_back(msg);
}

int ImageHolder::getImgPtr() const
{
    return imgPtr;
}

QVector<QString> ImageHolder::getLogs() const
{
    return logs;
}

