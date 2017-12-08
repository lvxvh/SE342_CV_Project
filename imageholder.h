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

private:
    QString filename;
    QImage image;
};

#endif // IMAGEHOLDER_H
