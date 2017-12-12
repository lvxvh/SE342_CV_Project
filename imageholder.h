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

class ImageHolder{
public:
    ImageHolder(MainWindow *mw);
    ~ImageHolder();

    bool loadImage();
    bool save();
    bool saveAs();
    void fitScreen();
    void actualPix();
    void rgbChannel( qint32 color);
    void toGray();
    void changeHsl( int hOffset, int sOffset, int lOffset);

    void Otsu();
    int getOtsuThreshold();

    void cacheImage(QString msg);
    void originImage();
    void resetImage();
    void changeVersion(int ptr);

    QRgb getRgb(qint32 x, qint32 y);

    qint32 getDisplayHeight() const;
    qint32 getDisplayWidth() const;


    QVector<QString> getLogs() const;
    void log(QString msg);

    int getImgPtr() const;


private:
    MainWindow *m;

    QString filename;

    QVector<QImage> images;
    QVector<QString> logs;
    bool reseted;
    int imgPtr;

    QImage displayImage;

    qint32 displayWidth;
    qint32 displayHeight;

};

#endif // IMAGEHOLDER_H
