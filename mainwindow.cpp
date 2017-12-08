#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "iconhelper.h"
#include <QImage>
#include <QFileDialog>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    ih(new ImageHolder)
{
    ui->setupUi(this);
    IconHelper::Instance()->SetIcon(ui->detailButton, QChar(0xf05a), 20);
}

MainWindow::~MainWindow()
{
    delete ui;
    delete ih;
}


void MainWindow::on_action_Open_triggered()
{
    ih->loadImage(this, ui);
}

void MainWindow::on_action_fit_screen_triggered()
{
    ih->fitScreen(ui);
}

void MainWindow::on_action_actual_pix_triggered()
{
    ih->actualPix(ui);
}

void MainWindow::on_action_Save_triggered()
{
    ih->save();
}


void MainWindow::on_action_SaveAs_triggered()
{
    ih->saveAs(this);
}

void MainWindow::mouseMoveEvent(QMouseEvent *)
{

}
