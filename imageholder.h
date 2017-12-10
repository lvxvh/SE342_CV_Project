#ifndef IMAGEHOLDER_H
#define IMAGEHOLDER_H



#include <QString>
#include<QImage>
#include "mainwindow.h"

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
    void rgbChannel(MainWindow *m, QString color);
    void toGray(MainWindow *m);

    QRgb getRgb(qint32 x, qint32 y);

    qint32 getDisplayHeight() const;
    qint32 getDisplayWidth() const;

private:
    QString filename;
    QImage originImage;
    QImage displayImage;
    qint32 displayWidth;
    qint32 displayHeight;

};

#endif // IMAGEHOLDER_H
