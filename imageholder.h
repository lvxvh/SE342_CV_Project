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
    void toGray();
    void changeHsl(int hOffset, int sOffset, int lOffset);
    QImage getFilteredImage();
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
    void contrastCurve(int type, float a, float b, float c);
    QVector<int> equalization(QVector<int> histogram);
    QVector<int> getHistogram();
    //smooth filter
    QImage extendImage(int extLen);
    void getGaussianKernal(int size, float sigma, float **gaus);
    void filter(int size, float **kernal);
    void midFilter(int size);
    void gaussianSmooth(int size, float sigma);
    //edge dectect
    void sobel();
    void getSobelMagnitude(QVector<QVector<int>> &magnitude, QVector<QVector<int>> &direction);
    void laplace();
    void canny();
    //hough
    void houghLine();
    //helper
    void cacheImage(QString msg);
    void draw();
    void undo();
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
