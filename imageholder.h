#ifndef IMAGEHOLDER_H
#define IMAGEHOLDER_H



#include <QString>
#include<QImage>
#include "mainwindow.h"

//channal
#define RGB_R 1
#define RGB_G 2
#define RGB_B 4
#define RGB_ALL 7
#define GRAY 0

class MainWindow;

namespace Ui {
class MainWindow;
}

class ImageHolder{
public:
    ImageHolder(MainWindow *mw);
    ~ImageHolder();

    bool loadImage();
    bool save();
    bool saveAs();
    void fitScreen();
    void actualPix();
    // color
    void rgbChannel( qint32 color);
    void toGray();
    void changeHsl(int hOffset, int sOffset, int lOffset);
    //binary
    void Otsu();
    int getOtsuThreshold();
    void dThreshold(int lo, int hi);
    //arithmetic and geometry ops
    void scale(float factor, bool biliner);
    void nearestNebr(float factor);
    void bilinerInt(float factor);
    void rotate(int angle, bool biliner);
    void nearestRotate(int angle);
    void bilinerIntRotate(int angle);
    //crop
    void drawCropRect(QRect rect);
    void crop(QRect rect);
    //contrast
    void contrastLiner(QVector<QPoint> points, int chanl);

    //helper
    void cacheImage(QString msg);
    void draw();
    void originImage();
    void resetImage();
    void changeVersion(int ptr);
    bool isGray();

    QRgb getRgb(qint32 x, qint32 y);

    qint32 getDisplayHeight() const;
    qint32 getDisplayWidth() const;


    QVector<QString> getLogs() const;
    void log(QString msg);

    int getImgPtr() const;

    QImage getDisplayImage() const;
    void setDisplayImage(const QImage &value);

    int getChannal() const;

    void setChannal(int value);

    QImage getOutImage() const;

private:
    MainWindow *m;

    QString filename;

    QVector<QImage> images;
    QVector<QString> logs;
    bool reseted;
    int imgPtr;

    QImage displayImage;
    QImage outImage;       //copy
    int channal;
    int channalCheckPoint;  //checkpoint when rgb img -> gray img used in change version

    qint32 displayWidth;
    qint32 displayHeight;

};

#endif // IMAGEHOLDER_H
