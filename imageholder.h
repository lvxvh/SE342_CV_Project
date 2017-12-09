#ifndef IMAGEHOLDER_H
#define IMAGEHOLDER_H



#include <QString>
#include<QImage>

namespace Ui {
class MainWindow;
}

class ImageHolder {
public:
    ImageHolder();
    ~ImageHolder();

    bool loadImage(QWidget *m, Ui::MainWindow *ui);
    bool save();
    bool saveAs(QWidget *m);
    void fitScreen(Ui::MainWindow *ui);
    void actualPix(Ui::MainWindow *ui);
    void rgbChannel(Ui::MainWindow *ui, QString color);
    void toGray(Ui::MainWindow *ui);

    QRgb getRgb(qint32 x, qint32 y);

    qint32 getDisplayHeight() const;
    qint32 getDisplayWidth() const;

private:
    QString filename;
    QImage originImage;
    QImage displayImage;
    qint32 displayWidth;
    qint32 displayHeight;

    qint32 size;
};

#endif // IMAGEHOLDER_H
