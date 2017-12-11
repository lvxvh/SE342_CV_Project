#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "imageholder.h"

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
    void changeHue(int offset);
    void changeSaturation(int para);

    Ui::MainWindow *getUi() const;
    void setUi(Ui::MainWindow *value);

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

private:
    Ui::MainWindow *ui;
    ImageHolder *ih;

protected:
    void mouseMoveEvent(QMouseEvent *);
};

#endif // MAINWINDOW_H
