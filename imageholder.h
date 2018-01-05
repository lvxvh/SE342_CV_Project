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
    void sobel(int gaussianSize, float sigma);
    void getSobelMagnitude(QVector<QVector<int>> &magnitude, QVector<QVector<int>> &direction);
    void laplace(int gaussianSize, float sigma, int threshold);
    void canny(int gaussianSize, float sigma, int ht, int lt);
    //hough
    void houghLine(int gaussianSize, float sigma, int ht, int lt, float t_ratio, int hough_space);
    void houghCircle(int gaussianSize, float sigma, int ht, int lt, float t_ratio, int sitaSize, int rSize, int rMax, int rMin);
    //morphology
    void genSe(int type, QSize size, QVector<QVector<int>> &se);
    void morphoBasic(int type, QVector<QVector<int>> &se, QPoint origin);
    void dilation(QImage &image, QVector<QVector<int>> &se, QPoint origin= QPoint(-1, -1),
                    bool record = false, QVector<QPoint> *diladed = NULL);
    void erosion(QImage &image, QVector<QVector<int>> &se, QPoint origin= QPoint(-1, -1),
                    bool record = false, QVector<QPoint> *eroded = NULL);
    void morphoOpen(QImage &image, QVector<QVector<int>> &se, QPoint origin= QPoint(-1, -1));
    void morphoClose(QImage &image, QVector<QVector<int>> &se, QPoint origin= QPoint(-1, -1));
    void hitOrMiss(QImage &image, QVector<QVector<int>> &se);
    void thinning();
    void thickening();
    void distanceTrans(int seType, int size);
    void skeleton(QVector<QImage> &sn);
    void skeletonRebuild(QVector<QImage> &sn);
    void morphoRebuild(int type, QVector<QVector<int>> &se, QPoint origin);
    void geoDilation(QImage &image, QImage &tmplate,QVector<QVector<int>> &se, QPoint origin= QPoint(-1, -1));
    void geoErosion(QImage &image, QImage &tmplate,QVector<QVector<int>> &se, QPoint origin= QPoint(-1, -1));
    void rebuildDilation(QImage &tmplate);
    void rebuildErosion(QImage &tmplate);
    void rebuildOpen(QImage &image, QVector<QVector<int>> &se, QPoint origin= QPoint(-1, -1));
    void rebuildClose(QImage &image, QVector<QVector<int>> &se, QPoint origin= QPoint(-1, -1));
    //gray morphology
    void grayMorphBasic(int type, QVector<QVector<int>> &se, QPoint origin);
    void grayDilation(QImage &image, QVector<QVector<int>> &se, QPoint origin= QPoint(-1, -1));
    void grayErosion(QImage &image, QVector<QVector<int>> &se, QPoint origin= QPoint(-1, -1));
    void grayOpen(QImage &image, QVector<QVector<int>> &se, QPoint origin= QPoint(-1, -1));
    void grayClose(QImage &image, QVector<QVector<int>> &se, QPoint origin= QPoint(-1, -1));
    void grayRebuild(int type, QVector<QVector<int>> &se, QPoint origin);
    void grayGeoDilation(QImage &image, QImage &tmplate,QVector<QVector<int>> &se, QPoint origin= QPoint(-1, -1));
    void grayGeoErosion(QImage &image, QImage &tmplate,QVector<QVector<int>> &se, QPoint origin= QPoint(-1, -1));
    void grayRebuildDilation(QImage &tmplate);
    void grayRebuildErosion(QImage &tmplate);
    void grayRebuildOpen(QImage &image, QVector<QVector<int>> &se, QPoint origin= QPoint(-1, -1));
    void grayRebuildClose(QImage &image, QVector<QVector<int>> &se, QPoint origin= QPoint(-1, -1));
    void watershed();
    void drawMark(QPoint p);
    //helper
    void cacheImage(QString msg);
    void draw();
    void undo();
    void resetImage();
    void changeVersion(int ptr);
    bool isGray();
    bool isBinary();

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


    void setGrayCheckPoint(int value);

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
    int grayCheckPoint;  //checkpoint when rgb img -> gray img used in change version

    qint32 displayWidth;
    qint32 displayHeight;

};

#endif // IMAGEHOLDER_H
