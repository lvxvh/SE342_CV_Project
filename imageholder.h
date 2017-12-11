#ifndef IMAGEHOLDER_H
#define IMAGEHOLDER_H



#include <QString>
#include<QImage>
#include "mainwindow.h"

#define RGB_R 1
#define RGB_G 2
#define RGB_B 4

class MainWindow;

namespace Ui {
class MainWindow;
}

class ImageHolder {
public:
    ImageHolder();
    ~ImageHolder();

    bool loadImage(MainWindow *m);
    bool save();
    bool saveAs(MainWindow *m);
    void fitScreen(MainWindow *m);
    void actualPix(MainWindow *m);
    void rgbChannel(MainWindow *m, qint32 color);
    void toGray(MainWindow *m);
    void changeHue(MainWindow *m, int offset);
    void changeSaturation(MainWindow *m, int para);
    void cacheImage(QImage image);
    void resetImage(MainWindow *m);

    QRgb getRgb(qint32 x, qint32 y);

    qint32 getDisplayHeight() const;
    qint32 getDisplayWidth() const;

private:
    QString filename;

    QVector<QImage> images;
    bool reseted;
    int imgPtr;
    /*QImage originImage;
    QImage tmpImage;*/
    QImage displayImage;

    qint32 displayWidth;
    qint32 displayHeight;

};

#endif // IMAGEHOLDER_H
