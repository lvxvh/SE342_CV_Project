#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "iconhelper.h"
#include "hsldialog.h"
#include "BinaryDialog.h"
#include "historydialog.h"
#include <QImage>
#include <QFileDialog>
#include <QMessageBox>
#include <QMouseEvent>
#include <QScrollBar>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    ih(new ImageHolder(this))
{
    ui->setupUi(this);
    IconHelper::Instance()->SetIcon(ui->detailButton, QChar(0xf0e2), 20);
    IconHelper::Instance()->SetIcon(ui->historyButton, QChar(0xf1da), 20);
}

MainWindow::~MainWindow()
{
    delete ui;
    delete ih;
}



void MainWindow::on_action_Open_triggered()
{
    ih->loadImage();
}

void MainWindow::on_action_fit_screen_triggered()
{
    ih->fitScreen();
}

void MainWindow::on_action_actual_pix_triggered()
{
    ih->actualPix();
}

void MainWindow::on_action_Save_triggered()
{
    ih->save();
}


void MainWindow::on_action_SaveAs_triggered()
{
    ih->saveAs();
}

void MainWindow::mouseMoveEvent(QMouseEvent *e)
{
    qint32 x=e->pos().x() - ui->image->pos().x() - 62 + (ui->scrollArea->horizontalScrollBar()->value());
    qint32 y=e->pos().y() - ui->image->pos().y() - 74 + (ui->scrollArea->verticalScrollBar()->value());

    if(x >= 0 && x < ih->getDisplayWidth() && y >= 0 && y < ih->getDisplayHeight()) {
        QRgb rgb = ih->getRgb(x, y);
        ui->statusBar->showMessage(tr("X:%1 Y:%2 R:%3 G:%4 B:%5").arg(x).arg(y).arg(qRed(rgb)).arg(qGreen(rgb)).arg(qBlue(rgb)));
    } else
        ui->statusBar->showMessage("");
}

void MainWindow::on_detailButton_clicked()
{
    ih->originImage();
}

void MainWindow::on_rButton_clicked()
{
    qint32 color = 0;
    if(ui->rgbButton->checkState() == Qt::Checked) {
        ui->rgbButton->setCheckState(Qt::Unchecked);
        color = RGB_G + RGB_B;
        ih->rgbChannel(color);
    } else {
        if(ui->rButton->checkState() == Qt::Checked){
            color += RGB_R;
        }
        if(ui->gButton->checkState() == Qt::Checked){
            color += RGB_G;
        }
        if(ui->bButton->checkState() == Qt::Checked){
            color += RGB_B;
        }
        if(color == RGB_R + RGB_G + RGB_B){
            ui->rgbButton->setCheckState(Qt::Checked);
        }
        if(color != 0) ih->rgbChannel(color);
        else ui->rButton->setCheckState(Qt::Checked);
    }
}

void MainWindow::on_rgbButton_clicked()
{
    if(ui->rgbButton->checkState() == Qt::Checked) {
        qint32 color = RGB_R + RGB_G + RGB_B;
        ui->rButton->setCheckState(Qt::Checked);
        ui->gButton->setCheckState(Qt::Checked);
        ui->bButton->setCheckState(Qt::Checked);
        ih->rgbChannel(color);

    } else {
        ui->rgbButton->setCheckState(Qt::Checked);
    }
}

void MainWindow::on_gButton_clicked()
{
    qint32 color = 0;
    if(ui->rgbButton->checkState() == Qt::Checked) {
        ui->rgbButton->setCheckState(Qt::Unchecked);
        color = RGB_R + RGB_B;
        ih->rgbChannel(color);
    } else {
        if(ui->rButton->checkState() == Qt::Checked){
            color += RGB_R;
        }
        if(ui->gButton->checkState() == Qt::Checked){
            color += RGB_G;
        }
        if(ui->bButton->checkState() == Qt::Checked){
            color += RGB_B;
        }
        if(color == RGB_R + RGB_G + RGB_B){
            ui->rgbButton->setCheckState(Qt::Checked);
        }
        if(color != 0) ih->rgbChannel(color);
        else ui->gButton->setCheckState(Qt::Checked);
    }
}

void MainWindow::on_bButton_clicked()
{
    qint32 color = 0;
    if(ui->rgbButton->checkState() == Qt::Checked) {
        ui->rgbButton->setCheckState(Qt::Unchecked);
        color = RGB_R + RGB_G;
        ih->rgbChannel(color);
    } else {
        if(ui->rButton->checkState() == Qt::Checked){
            color += RGB_R;
        }
        if(ui->gButton->checkState() == Qt::Checked){
            color += RGB_G;
        }
        if(ui->bButton->checkState() == Qt::Checked){
            color += RGB_B;
        }
        if(color == RGB_R + RGB_G + RGB_B){
            ui->rgbButton->setCheckState(Qt::Checked);
        }
        if(color != 0) ih->rgbChannel(color);
        else ui->bButton->setCheckState(Qt::Checked);
    }
}

void MainWindow::on_grayButton_clicked()
{
    ih->toGray();
}

void MainWindow::on_hbsButton_clicked()
{
    HslDialog *dlg = new HslDialog(this);
    dlg->show();
}

ImageHolder *MainWindow::getIh() const
{
    return ih;
}

void MainWindow::emitLogsignal()
{
    emit refreshLog();
}

void MainWindow::changeVersion(int ptr)
{
    ih->changeVersion(ptr);
}

Ui::MainWindow *MainWindow::getUi() const
{
    return ui;
}


void MainWindow::on_historyButton_clicked()
{
    HistoryDialog *dlg = new HistoryDialog(this);
    dlg->show();
}

void MainWindow::on_otsuButton_clicked()
{
    if(ih->isGray()) {
        ih->Otsu();
    } else {
        QMessageBox::information(this, QObject::tr("提示"), QObject::tr("只能处理灰度图像"));
    }
}

void MainWindow::on_thresholdButton_clicked()
{
    if(ih->isGray()) {
        BinaryDialog *dlg = new BinaryDialog(this);
        dlg->show();
    } else {
        QMessageBox::information(this, QObject::tr("提示"), QObject::tr("只能处理灰度图像"));
    }
}
