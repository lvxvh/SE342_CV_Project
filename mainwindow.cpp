#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "iconhelper.h"
#include "hbsdialog.h"
#include <QImage>
#include <QFileDialog>
#include <QMessageBox>
#include <QMouseEvent>
#include <QScrollBar>

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
    ih->loadImage(this);
}

void MainWindow::on_action_fit_screen_triggered()
{
    ih->fitScreen(this);
}

void MainWindow::on_action_actual_pix_triggered()
{
    ih->actualPix(this);
}

void MainWindow::on_action_Save_triggered()
{
    ih->save();
}


void MainWindow::on_action_SaveAs_triggered()
{
    ih->saveAs(this);
}

void MainWindow::mouseMoveEvent(QMouseEvent *e)
{
    qint32 x=e->pos().x() - ui->image->pos().x() - 62 + (ui->scrollArea->horizontalScrollBar()->value());
    qint32 y=e->pos().y() - ui->image->pos().y() - 74 + (ui->scrollArea->verticalScrollBar()->value());

    printf("width is %d and height is %d\n",ih->getDisplayWidth(),ih->getDisplayHeight());
    if(x >= 0 && x < ih->getDisplayWidth() && y >= 0 && y < ih->getDisplayHeight()) {
        QRgb rgb = ih->getRgb(x, y);
        ui->statusBar->showMessage(tr("X:%1 Y:%2 R:%3 G:%4 B:%5").arg(x).arg(y).arg(qRed(rgb)).arg(qGreen(rgb)).arg(qBlue(rgb)));
    } else
        ui->statusBar->showMessage("");
}

void MainWindow::on_detailButton_clicked()
{
    QDialog *dlg = new QDialog(this);
    dlg->show();
}

void MainWindow::on_rButton_clicked()
{
    ih->rgbChannel(this, "red");
}

void MainWindow::on_rgbButton_clicked()
{
    ih->rgbChannel(this, "all");
}

void MainWindow::on_gButton_clicked()
{
    ih->rgbChannel(this, "green");
}

void MainWindow::on_bButton_clicked()
{
    ih->rgbChannel(this, "blue");
}

void MainWindow::on_grayButton_clicked()
{
    ih->toGray(this);
}

void MainWindow::on_hbsButton_clicked()
{
    hbsDialog *dlg = new hbsDialog(this);
    dlg->show();
}

Ui::MainWindow *MainWindow::getUi() const
{
    return ui;
}

void MainWindow::setUi(Ui::MainWindow *value)
{
    ui = value;
}
