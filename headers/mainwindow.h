#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "imageholder.h"
#include "croprect.h"
#include <QDebug>

class ImageHolder;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    Ui::MainWindow *getUi() const;

    ImageHolder *getIh() const;

    void emitLogsignal();
    void freshSide();
    bool sizeEqual(int image1, int image2);    
    void AOP(int i1, int i2, int op);

    void setIsCropping(bool value);

    void setIsMarking(bool value);

    ImageHolder *getIhByIndex(int index) const;

signals:
    void refreshLog();
    void sendLists(int count);
    void sendRectGeo(int x, int y, int w, int h);
public slots:
    void changeVersion(int ptr);
    void changeImage();
    void receiveEditedGeo(int x,int y,int w, int h);

private slots:

    void on_action_Open_triggered();
    void on_action_fit_screen_triggered();
    void on_action_actual_pix_triggered();
    void on_action_Save_triggered();
    void on_action_SaveAs_triggered();
    void on_detailButton_clicked();
    void on_rButton_clicked();
    void on_rgbButton_clicked();
    void on_gButton_clicked();
    void on_bButton_clicked();
    void on_grayButton_clicked();
    void on_hbsButton_clicked();
    void on_historyButton_clicked();
    void on_otsuButton_clicked();
    void on_thresholdButton_clicked();

    void on_ScaleButton_clicked();

    void on_rotateButton_clicked();

    void on_AOPButton_clicked();

    void on_cutButton_clicked();

    void on_copyButton_clicked();

    void on_closeButton_clicked();

    void on_toolBox_currentChanged(int index);

    void on_linerButton_clicked();

    void on_nonlinerButton_clicked();

    void on_HGButton_clicked();

    void on_filterButton_clicked();

    void on_sobelButton_clicked();

    void on_laplacianButton_clicked();

    void on_cannyButton_clicked();

    void on_houghLineButton_clicked();

    void on_houghCircleButton_clicked();

    void on_BMBasicButton_clicked();

    void on_thinButton_clicked();

    void on_thickenButton_clicked();

    void on_DTButton_clicked();

    void on_skeletonButton_clicked();

    void on_BMRebuildButton_clicked();

    void on_GBMBasicButton_clicked();

    void on_GMRButton_clicked();

    void on_watershedButton_clicked();

private:
    //cutting
    bool isInImg(QPoint pos);
    QPoint mapToImg(QPoint point);
    bool isCropping;
    bool isMarking;
    bool cropStarted;
    CropRect cropRect;

    Ui::MainWindow *ui;
    QVector<ImageHolder *> ihs;
    ImageHolder *ih;
    int curImg;

protected:
    void mouseMoveEvent(QMouseEvent *);
    void mousePressEvent(QMouseEvent *);
    void mouseReleaseEvent(QMouseEvent *);
};

#endif // MAINWINDOW_H
