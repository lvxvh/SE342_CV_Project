#include <imageholder.h>
#include "ui_MainWindow.h"
#include <QFileDialog>
#include <QMessageBox>
#include <QObject>
#include "qhsl.h"

#define PI 3.1415926535
//角度到弧度转化
#define RADIAN(angle) ((angle)*PI/180.0)

ImageHolder::ImageHolder(MainWindow *mw)
{
    m = mw;
    displayHeight = 0;
    displayWidth = 0;
    reseted = 0;
    imgPtr = -1;
    channalCheckPoint = -1;
}

ImageHolder::~ImageHolder()
{
    images.clear();
}

bool ImageHolder::loadImage()
{
    //if (!images.isEmpty()) images.clear();
    filename = QFileDialog::getOpenFileName(m, QObject::tr("选择图像"), "", QObject::tr("Images (*.png *.bmp *.jpg *.tif *.GIF )"));
    if(!filename.isEmpty()) {
        QImage originImage;
        if(originImage.load(filename)) {
            displayImage = originImage;
            channal = RGB_ALL;
            cacheImage(QObject::tr("打开"));
            displayWidth = displayImage.width();
            displayHeight = displayImage.height();
            draw();
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

void ImageHolder::toGray()
{
    outImage = getFilteredImage();
    if(channal != RGB_R && channal != RGB_G && channal != RGB_B)
    {
        for(int y = 0;y < displayHeight; ++y){
            for(int x = 0;x < displayWidth; ++x){
                QRgb pixel = outImage.pixel(x,y);
                qint32 r=qRed(pixel);
                qint32 g=qGreen(pixel);
                qint32 b=qBlue(pixel);
                qint32 gray = qGray(r, g, b); //Gray = (R * 11 + G * 16 + B * 5)/32
                displayImage.setPixel(x, y, qRgb(gray, gray, gray));
            }
        }
    } else {
        for(int y = 0;y < displayHeight; ++y){
            for(int x = 0;x < displayWidth; ++x){
                QRgb pixel = outImage.pixel(x,y);
                qint32 r=qRed(pixel);
                qint32 g=qGreen(pixel);
                qint32 b=qBlue(pixel);
                qint32 gray = r*(channal == RGB_R) + g*(channal == RGB_G) + b*(channal == RGB_B);
                displayImage.setPixel(x, y, qRgb(gray, gray, gray));
            }
        }
    }
    channal = GRAY;
    cacheImage(QObject::tr("转为灰度图像"));
    channalCheckPoint = imgPtr;             //checkpoint

    Ui::MainWindow *ui = m->getUi();
    ui->toolBox->setCurrentIndex(1);

    draw();
    //切换page
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

QImage ImageHolder::getFilteredImage()
{
    outImage = displayImage;
    if(channal != GRAY && channal != RGB_ALL) {
        bool r = channal & 1;
        bool g = (channal >> 1) & 1;
        bool b = (channal >> 2) & 1;
        for(int y = 0;y < displayHeight; ++y){
            for(int x = 0;x < displayWidth; ++x){
                QRgb pixel = outImage.pixel(x,y);
                outImage.setPixel(x, y, qRgb(qRed(pixel)*r, qGreen(pixel)*g, qBlue(pixel)*b));
            }
        }
    }
    return outImage;
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

void ImageHolder::scale(float factor, bool biliner)
{
    if(biliner)  bilinerInt(factor);
    else nearestNebr(factor);
}

void ImageHolder::nearestNebr(float factor)
{
    /*
     *  0---1---2---3
     *  *2
     *  0-1-2-3-4-5-6-7
     *
     *  the last pixel should round floor
     */
    displayImage = images[imgPtr];
    //width and height will be modified so refresh here.
    displayWidth = displayImage.width();
    displayHeight = displayImage.height();

    int newWidth = floor(displayWidth * factor);
    int newHeight = floor(displayHeight * factor);
    int sourceX, sourceY;
    QImage newImage(newWidth, newHeight, QImage::Format_RGB32);
    for(int y = 0;y < newHeight;++y){
        for(int x = 0;x < newWidth;++x){
            sourceX = round(x/(newWidth/(displayWidth - 1.0f)));
            sourceY = round(y/(newHeight/(displayHeight - 1.0f)));
            newImage.setPixel(x,y,displayImage.pixel(sourceX,sourceY));
        }
    }
    displayImage = newImage;
    displayHeight = newHeight;
    displayWidth = newWidth;
    draw();
}

void ImageHolder::bilinerInt(float factor)
{
    //  pixel is the same as the prev one if it's on the border
    displayImage = images[imgPtr];
    displayWidth = displayImage.width();
    displayHeight = displayImage.height();

    int newWidth = floor(displayWidth * factor);
    int newHeight = floor(displayHeight * factor);
    float sourceX, sourceY, u, v;
    int leftX, topY;
    QRgb p1, p2, p3, p4;
    int r,g,b;
    QImage newImage(newWidth, newHeight, QImage::Format_RGB32);
    for(int y = 0;y < newHeight;++y){
        for(int x = 0;x < newWidth;++x){
            sourceX = x/(newWidth/(displayWidth - 1.0f));
            sourceY = y/(newHeight/(displayHeight - 1.0f));
            leftX = floor(sourceX);
            //if(leftX == displayWidth - 1) leftX = displayWidth - 2;
            topY = floor(sourceY);
            //if(bottomY == displayHeight - 1) bottomY = displayHeight - 2;
            u = sourceX - leftX;
            v = sourceY - topY;
            p1 = displayImage.pixel(leftX, topY);
            p2 = displayImage.pixel(leftX + 1, topY);
            p3 = displayImage.pixel(leftX, topY + 1);
            p4 = displayImage.pixel(leftX + 1, topY + 1);
            r = floor((1 - u)*(1 - v)*qRed(p1) + u*(1 - v)*qRed(p2) + v*(1 - u)*qRed(p3) + u*v*qRed(p4));
            g = floor((1 - u)*(1 - v)*qGreen(p1) + u*(1 - v)*qGreen(p2) + v*(1 - u)*qGreen(p3) + u*v*qGreen(p4));
            b = floor((1 - u)*(1 - v)*qBlue(p1) + u*(1 - v)*qBlue(p2) + v*(1 - u)*qBlue(p3) + u*v*qBlue(p4));
            newImage.setPixel(x,y,qRgb(r,g,b));
        }
    }
    displayImage = newImage;
    displayHeight = newHeight;
    displayWidth = newWidth;
    draw();
}

void ImageHolder::rotate(int angle, bool biliner)
{
    if(biliner) bilinerIntRotate(angle);
    else nearestRotate(angle);
}

void ImageHolder::nearestRotate(int angle)
{
    displayImage = images[imgPtr];
    displayWidth = displayImage.width();
    displayHeight = displayImage.height();
    // origin is the center of image
    // use 4 coner points compute new size
    QPoint p1, p2, p3, p4;
    p1.setX(-displayWidth/2);
    p1.setY(-displayHeight/2);
    p2.setX(displayWidth/2);
    p2.setY(-displayHeight/2);
    p3.setX(displayWidth/2);
    p3.setY(displayHeight/2);
    p4.setX(-displayWidth/2);
    p4.setY(displayHeight/2);

    QPoint np1, np2, np3, np4;

    double sina = sin(RADIAN(angle));

    double cosa = cos(RADIAN(angle));
    np1.setX(p1.x()*cosa - p1.y()*sina);
    np1.setY(p1.x()*sina + p1.y()*cosa);
    np2.setX(p2.x()*cosa - p2.y()*sina);
    np2.setY(p2.x()*sina + p2.y()*cosa);
    np3.setX(p3.x()*cosa - p3.y()*sina);
    np3.setY(p3.x()*sina + p3.y()*cosa);
    np4.setX(p4.x()*cosa - p4.y()*sina);
    np4.setY(p4.x()*sina + p4.y()*cosa);

    int newWidth = qMax(abs(np1.x() - np3.x()),abs(np2.x() - np4.x()));
    int newHeight = qMax(abs(np1.y() - np3.y()),abs(np2.y() - np4.y()));
    QImage newImage(newWidth, newHeight, QImage::Format_RGB32);
    for(int y = 0;y < newHeight;++y){
        for(int x = 0;x < newWidth;++x){
            int sourceX = round((x - newWidth/2)*cos(RADIAN(360 - angle)) - (y - newHeight/2)*sin(RADIAN(360 - angle)));
            int sourceY = round((x - newWidth/2)*sin(RADIAN(360 - angle)) + (y - newHeight/2)*cos(RADIAN(360 - angle)));
            if(sourceX > displayWidth/2 || sourceX < -displayWidth/2 ||
                    sourceY > displayHeight/2 || sourceY < -displayHeight/2){
                newImage.setPixel(x,y,qRgb(48,54,58));
            } else {
                sourceX += displayWidth/2;
                if(sourceX == displayWidth) sourceX = displayWidth - 1;
                sourceY += displayHeight/2;
                if(sourceY == displayHeight) sourceY = displayHeight - 1;
                newImage.setPixel(x, y, displayImage.pixel(sourceX, sourceY));
            }
        }
    }

    displayImage = newImage;
    displayHeight = newHeight;
    displayWidth = newWidth;
    draw();
}

void ImageHolder::bilinerIntRotate(int angle)
{
    displayImage = images[imgPtr];
    displayWidth = displayImage.width();
    displayHeight = displayImage.height();
    // origin is the center of image
    // use 4 coner points compute new size
    QPoint p1, p2, p3, p4;
    p1.setX(-displayWidth/2);
    p1.setY(-displayHeight/2);
    p2.setX(displayWidth/2);
    p2.setY(-displayHeight/2);
    p3.setX(displayWidth/2);
    p3.setY(displayHeight/2);
    p4.setX(-displayWidth/2);
    p4.setY(displayHeight/2);

    QPoint np1, np2, np3, np4;

    double sina = sin(RADIAN(angle));

    double cosa = cos(RADIAN(angle));
    np1.setX(p1.x()*cosa - p1.y()*sina);
    np1.setY(p1.x()*sina + p1.y()*cosa);
    np2.setX(p2.x()*cosa - p2.y()*sina);
    np2.setY(p2.x()*sina + p2.y()*cosa);
    np3.setX(p3.x()*cosa - p3.y()*sina);
    np3.setY(p3.x()*sina + p3.y()*cosa);
    np4.setX(p4.x()*cosa - p4.y()*sina);
    np4.setY(p4.x()*sina + p4.y()*cosa);

    int newWidth = qMax(abs(np1.x() - np3.x()),abs(np2.x() - np4.x()));
    int newHeight = qMax(abs(np1.y() - np3.y()),abs(np2.y() - np4.y()));
    QImage newImage(newWidth, newHeight, QImage::Format_RGB32);
    for(int y = 0;y < newHeight;++y){
        for(int x = 0;x < newWidth;++x){
            int sourceX = round((x - newWidth/2)*cos(RADIAN(360 - angle)) - (y - newHeight/2)*sin(RADIAN(360 - angle)));
            int sourceY = round((x - newWidth/2)*sin(RADIAN(360 - angle)) + (y - newHeight/2)*cos(RADIAN(360 - angle)));
            if(sourceX > displayWidth/2 || sourceX < -displayWidth/2 ||
                    sourceY > displayHeight/2 || sourceY < -displayHeight/2){
                newImage.setPixel(x,y,qRgb(48,54,58));
            } else {
                int leftX, topY;
                QRgb p1, p2, p3, p4;
                int r,g,b;
                float u,v;
                sourceX += displayWidth/2;
                sourceY += displayHeight/2;

                leftX = floor(sourceX);
                if(leftX >= displayWidth - 1) leftX = displayWidth - 2;
                topY = floor(sourceY);
                if(topY >= displayHeight - 1) topY = displayHeight - 2;
                u = sourceX - leftX;
                v = sourceY - topY;
                p1 = displayImage.pixel(leftX, topY);
                p2 = displayImage.pixel(leftX + 1, topY);
                p3 = displayImage.pixel(leftX, topY + 1);
                p4 = displayImage.pixel(leftX + 1, topY + 1);
                r = floor((1 - u)*(1 - v)*qRed(p1) + u*(1 - v)*qRed(p2) + v*(1 - u)*qRed(p3) + u*v*qRed(p4));
                g = floor((1 - u)*(1 - v)*qGreen(p1) + u*(1 - v)*qGreen(p2) + v*(1 - u)*qGreen(p3) + u*v*qGreen(p4));
                b = floor((1 - u)*(1 - v)*qBlue(p1) + u*(1 - v)*qBlue(p2) + v*(1 - u)*qBlue(p3) + u*v*qBlue(p4));

                newImage.setPixel(x, y, qRgb(r,g,b));
            }
        }
    }

    displayImage = newImage;
    displayHeight = newHeight;
    displayWidth = newWidth;
    draw();
}

void ImageHolder::cacheImage(QString msg)
{
    if(reseted) {
        images.erase(images.begin() + (imgPtr + 1), images.end());
        logs.erase(logs.begin() + (imgPtr + 1), logs.end());
        if(imgPtr < channalCheckPoint){
            channalCheckPoint = -1;
        }
        reseted = 0;
    }
    images.push_back(displayImage);
    logs.push_back(msg);
    imgPtr++;
    m->emitLogsignal();
}

void ImageHolder::draw()
{
    outImage = getFilteredImage();
    //gray or full color
    QPixmap pix = QPixmap::fromImage(outImage);
    Ui::MainWindow *ui = m->getUi();
    ui->image->setPixmap(pix);
}

void ImageHolder::originImage()
{
    if(imgPtr > 0){
        displayImage = images[0];
        displayHeight = displayImage.height();
        displayWidth = displayImage.width();
        reseted = 1;
        imgPtr = 0;
        draw();

    }
}

void ImageHolder::resetImage()
{
    displayImage = images[imgPtr];
    displayHeight = displayImage.height();
    displayWidth = displayImage.width();
    draw();
}

void ImageHolder::changeVersion(int ptr)
{
    if(ptr != imgPtr) {
        displayImage = images[ptr];
        displayHeight = displayImage.height();
        displayWidth = displayImage.width();
        reseted = 1;    //used in truncate
        imgPtr = ptr;
        Ui::MainWindow *ui = m->getUi();
        if (imgPtr >= channalCheckPoint){
            setChannal(GRAY);
            ui->toolBox->setCurrentIndex(1);
        } else{
            setChannal(RGB_ALL);
            ui->toolBox->setCurrentIndex(0);
        }
        draw();
    }
}

bool ImageHolder::isGray()
{
    return channal == GRAY;
}

void ImageHolder::drawCropRect(QRect rect)
{
    QImage tmp = images[imgPtr];

    QPainter pp;
    QPen pen; //画笔
    pen.setColor(QColor(255, 0, 0));
    pen.setStyle(Qt::DashLine);

    pp.begin(&tmp);
    pp.setPen(pen); //添加画笔

    pp.drawRect(rect);
    pp.end();

    setDisplayImage(tmp);
    draw();
}

void ImageHolder::crop(QRect rect)
{
    setDisplayImage(images[imgPtr].copy(rect));
    cacheImage("裁剪");
    draw();
}

void ImageHolder::contrastLiner(QVector<QPoint> points, int chanl)
{
    displayImage = images[imgPtr];
    if(chanl == GRAY){
        for(int y = 0;y < displayHeight; ++y){
            for(int x = 0;x < displayWidth; ++x){
                QRgb pixel = displayImage.pixel(x,y);
                for(int i = 0;i < points.size() - 1;++i){
                    if(qRed(pixel) <= points[i + 1].x()){
                        int a = points[i].x();
                        int b = points[i + 1].x();
                        int c = 255 - points[i].y();
                        int d = 255 - points[i + 1].y();
                        int out = round((d - c)*(qRed(pixel) - a)*1.0f/(b - a)) + c;
                        if(out > 255) out = 255;
                        displayImage.setPixel(x,y,qRgb(out, out, out));
                        break;
                    }
                }
            }
        }
    }
    draw();
}

void ImageHolder::contrastCurve(int type, float a, float b, float c)
{
    displayImage = images[imgPtr];
    int out;
    for(int y = 0;y < displayHeight; ++y){
        for(int x = 0;x < displayWidth; ++x){
            QRgb pixel = displayImage.pixel(x,y);
            if(type == 0){
                out = round(pow(b, c*(qRed(pixel) - a))) - 1;
                if(out > 255) out = 255;
                if(out < 0) out = 0;
            } else {
                out = round(a + (std::log(qRed(pixel) + 1)/(b*std::log(c))));
                if(out > 255) out = 255;
                if(out < 0) out = 0;
            }
            displayImage.setPixel(x,y,qRgb(out, out, out));
        }
    }
    draw();
}

QVector<int> ImageHolder::getHistogram()
{
    QVector<int> outHistogram(256, 0);
    for(int y = 0;y < displayHeight;++y){
        for(int x = 0;x < displayWidth;++x){
            outHistogram[qRed(displayImage.pixel(x, y))]++;
        }
    }
    return outHistogram;
}

QImage ImageHolder::extendImage(int extLen)
{
    QImage out(displayWidth + 2*extLen, displayHeight + 2*extLen, QImage::Format_RGB32);
    //top
    for(int i = 0;i < extLen;i++){
        for(int j = extLen;j < out.width() - extLen;j++){
            out.setPixel(j,i,displayImage.pixel( j - extLen, extLen - i - 1));
        }
    }
    //bottom
    for(int i = 0;i < extLen;i++){
        for(int j = extLen;j < out.width() - extLen;j++){
            out.setPixel(j,displayHeight + i,displayImage.pixel( j - extLen,displayHeight - 1 - i));
        }
    }
    //left
    for(int j = 0;j < extLen;j++){
        for(int i = extLen;i < out.height() - extLen;i++){
            out.setPixel(j,i,displayImage.pixel(extLen - j - 1,i - extLen));
        }
    }
    //right
    for(int j = 0;j < extLen;j++){
        for(int i = extLen;i < out.height() - extLen;i++){
            out.setPixel(j,i,displayImage.pixel(displayWidth - j - 1,i - extLen));
        }
    }
    //conor
    for(int i = 0;i <extLen; i++){
        for(int j = 0;j < extLen;j++){
            out.setPixel(j,i,displayImage.pixel(0,0));
        }
    }
    for(int i = 0;i < extLen; i++){
        for(int j = 0;j < extLen;j++){
            out.setPixel(j,i + displayHeight + extLen,displayImage.pixel(0,displayHeight - 1));
        }
    }
    for(int i = 0;i < extLen; i++){
        for(int j = 0;j < extLen;j++){
            out.setPixel(j + displayWidth + extLen,i + displayHeight + extLen,displayImage.pixel(displayWidth - 1,displayHeight - 1));
        }
    }
    for(int i = 0;i < extLen; i++){
        for(int j = 0;j < extLen;j++){
            out.setPixel(j + displayWidth + extLen,i,displayImage.pixel(displayWidth - 1,0));
        }
    }
    //other
    for(int i = 0;i < displayHeight;i++){
        for(int j = 0;j <displayWidth;j++){
            out.setPixel(j + extLen,i + extLen,displayImage.pixel(j,i));
        }
    }
    return out;
}

void ImageHolder::getGaussianKernal(int size, float sigma, float **gaus)
{
    int center=size/2;
    float sum = 0;
    for(int i=0;i<size;i++){
        for(int j=0;j<size;j++){
            gaus[i][j]=(1/(2*M_PI*sigma*sigma))*exp(-((i-center)*(i-center)+(j-center)*(j-center))/(2*sigma*sigma));
            sum += gaus[i][j];
        }
    }
    for(int i=0;i<size;i++){
        for(int j=0;j<size;j++){
            gaus[i][j]/=sum;
        }
    }
}

void ImageHolder::filter(int size, float **kernal)
{
    int pad = (size-1)/2;
    QImage tmp = extendImage(pad);
    for(int y = 0;y < displayHeight;++y){
        for(int x = 0;x < displayWidth;++x){
            float out = 0;
            for(int i = 0;i < size;i++){
                for(int j = 0;j < size;j++){
                    out += qRed(tmp.pixel(x + j,y + i)) * kernal[size - j - 1][size - i - 1];
                }
            }
            displayImage.setPixel(x, y, qRgb(round(out), round(out), round(out)));
        }
    }
}

void ImageHolder::midFilter(int size)
{
    int pad = (size-1)/2;
    QImage tmp = extendImage(pad);
    int len = size*size;
    int *value = new int [len];
    for(int y = 0;y < displayHeight;++y){
        for(int x = 0;x < displayWidth;++x){
            for(int i = 0;i < size;i++){
                for(int j = 0;j < size;j++){
                    value[i * size + j] = tmp.pixel(x + j,y + i);
                }
            }
            int temp;
            for (int i = 0; i < len - 1; i++){
                for (int j = 0; j < len - 1 - i; j++){
                    if (value[j] > value[j + 1]) {
                        temp = value[j];
                        value[j] = value[j + 1];
                        value[j + 1] = temp;
                    }
                }
            }
            int out = value[len/2 + 1];
            displayImage.setPixel(x, y, qRgb(out, out, out));
        }
    }
    delete value;
    value = NULL;
}

void ImageHolder::sobel()
{
    float **gaus = new float *[5];
    for(int i = 0;i < 5;++i){
        gaus[i]=new float[5];
    }

    getGaussianKernal(5, 1.0, gaus);
    filter(5, gaus);

    for(int i = 0;i < 5;++i){
        delete gaus[i];
        gaus[i] = NULL;
    }
    delete gaus;
    gaus = NULL;

    int sx[3][3] = {{-1, 0, 1},
                    {-2, 0, 2},
                    {-1, 0, 1}};
    int sy[3][3] = {{1, 2, 1},
                    {0, 0, 0},
                    {-1, -2, -1}};
    QImage tmp = extendImage(1);
    for(int y = 0;y < displayHeight;++y){
        for(int x = 0;x < displayWidth;++x){
            int gx = 0;
            int gy = 0;
            int g = 0;
            for(int i = 0;i < 3;i++){
                for(int j = 0;j < 3;j++){
                    gx += qRed(tmp.pixel(x + j,y + i)) * sx[3 - j - 1][3 - i - 1];
                    gy += qRed(tmp.pixel(x + j,y + i)) * sy[3 - j - 1][3 - i - 1];
                }
            }
            g = round(sqrt(gx*gx + gy*gy));
            displayImage.setPixel(x, y, qRgb(round(g), round(g), round(g)));
        }
    }
    cacheImage("Sobel");
    draw();
}

void ImageHolder::laplace()
{
    float **gaus = new float *[5];
    for(int i = 0;i < 5;++i){
        gaus[i]=new float[5];
    }

    getGaussianKernal(5, 1.0, gaus);
    filter(5, gaus);

    for(int i = 0;i < 5;++i){
        delete gaus[i];
        gaus[i] = NULL;
    }
    delete gaus;
    gaus = NULL;

    int t[3][3] = {{0, -1, 0},
                   {-1, 4, -1},
                   {0, -1, 0}};
    QImage tmp = extendImage(1);
    for(int y = 0;y < displayHeight;++y){
        for(int x = 0;x < displayWidth;++x){
            int out = 0;
            for(int i = 0;i < 3;i++){
                for(int j = 0;j < 3;j++){
                    out += qRed(tmp.pixel(x + j,y + i)) * t[3 - j - 1][3 - i - 1];
                }
            }
            out = qAbs(out);
            displayImage.setPixel(x, y, qRgb(out, out, out));
        }
    }
    cacheImage("Laplacian");
    draw();
}

void ImageHolder::canny()
{
    float **gaus = new float *[5];
    for(int i = 0;i < 5;++i){
        gaus[i]=new float[5];
    }

    getGaussianKernal(5, 1.0, gaus);
    filter(5, gaus);

    for(int i = 0;i < 5;++i){
        delete gaus[i];
        gaus[i] = NULL;
    }
    delete gaus;
    gaus = NULL;



    cacheImage("Canny");
    draw();
}

QVector<int> ImageHolder::equalization(QVector<int> histogram)
{
    QVector<float> p;      //r[i]'s p
    QVector<float> s;       //unrounded new gray level
    QVector<int> out(256,0);
    QMap<int, int> kmap;      //map[old level] = new level
    int total = displayHeight*displayWidth;
    //p
    p.resize(histogram.size());
    for(int i = 0;i < histogram.size();++i){
        p[i] = histogram[i]*1.0f/total;
    }
    //s
    s.resize(histogram.size());
    for(int i = 0;i < p.size();++i){
        if(i == 0){
            s[i] = p[i];
        } else {
            s[i] = p[i] + s[i - 1];
        }
    }
    //equalization
    for(int i = 0;i < s.size();++i){
        int sk = round(s[i] * 255);
        out[sk] += histogram[i];
        kmap[i] = sk;
    }
    //update image
    for(int y = 0;y < displayHeight;++y){
        for(int x = 0;x < displayWidth;++x){
            QRgb pixel = displayImage.pixel(x,y);
            int out = kmap[qRed(pixel)];
            displayImage.setPixel(x,y,qRgb(out, out, out));
        }
    }
    draw();
    return out;
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

QImage ImageHolder::getDisplayImage() const
{
    return displayImage;
}

void ImageHolder::setDisplayImage(const QImage &value)
{
    displayImage = value;
    displayHeight = value.height();
    displayWidth = value.width();
}

int ImageHolder::getChannal() const
{
    return channal;
}

void ImageHolder::setChannal(int value)
{
    channal = value;
    draw();
}

QImage ImageHolder::getOutImage() const
{
    return outImage;
}


QVector<QString> ImageHolder::getLogs() const
{
    return logs;
}

