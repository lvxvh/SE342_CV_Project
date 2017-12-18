#ifndef PHOTOSHOTDIALOG_H
#define PHOTOSHOTDIALOG_H

#include <QDialog>
#include "cropdialog.h"

namespace Ui {
class PhotoShotDialog;
}

class PhotoShotDialog : public QDialog
{
    Q_OBJECT

public:
    explicit PhotoShotDialog(QRect rec,QWidget *parent = 0);
    ~PhotoShotDialog();

private:
    Ui::PhotoShotDialog *ui;
    CropDialog *cropDialog;
protected:
    void paintEvent(QPaintEvent *e);
};

#endif // PHOTOSHOTDIALOG_H
