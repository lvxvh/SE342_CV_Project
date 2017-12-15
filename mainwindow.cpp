#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "iconhelper.h"
#include "hsldialog.h"
#include "BinaryDialog.h"
#include "historydialog.h"
#include "scaledialog.h"
#include "rotatedialog.h"
#include "aopdialog.h"
#include <QImage>
#include <QFileDialog>
#include <QMessageBox>
#include <QMouseEvent>
#include <QScrollBar>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ih = NULL;
    curImg = -1;
    IconHelper::Instance()->SetIcon(ui->detailButton, QChar(0xf0e2), 20);
    IconHelper::Instance()->SetIcon(ui->historyButton, QChar(0xf1da), 20);
}

MainWindow::~MainWindow()
{
    delete ui;
    for(int i = 0;i < ihs.size();++i) delete ihs[i];
    ihs.clear();
}



void MainWindow::on_action_Open_triggered()
{
    ih = new ImageHolder(this);
    ihs.push_back(ih);
    curImg = ihs.size() - 1;
    ih->loadImage();
    freshSide();
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
    if(ih != NULL){
        qint32 x=e->pos().x() - ui->image->pos().x() - 79 + (ui->scrollArea->horizontalScrollBar()->value());
        qint32 y=e->pos().y() - ui->image->pos().y() - 85 + (ui->scrollArea->verticalScrollBar()->value());

        if(x >= 0 && x < ih->getDisplayWidth() && y >= 0 && y < ih->getDisplayHeight()) {
            QRgb rgb = ih->getRgb(x, y);
            ui->statusBar->showMessage(tr("X:%1 Y:%2 R:%3 G:%4 B:%5").arg(x).arg(y).arg(qRed(rgb)).arg(qGreen(rgb)).arg(qBlue(rgb)));
        } else
            ui->statusBar->showMessage("");
    }
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
    dlg->exec();
}

ImageHolder *MainWindow::getIh() const
{
    return ih;
}

void MainWindow::emitLogsignal()
{
    emit refreshLog();
}

void MainWindow::freshSide()
{
    QVBoxLayout *vLayout;
    if(ui->sideBar->layout() != NULL) { //clean
        vLayout = (QVBoxLayout*)(ui->sideBar->layout());
        int itemCount = vLayout->count();
        for(int i = (itemCount - 1);i >= 0;--i) {
            QLayoutItem *item = vLayout->takeAt(i);
            if(item != 0) {
                vLayout->removeWidget(item->widget());
                delete item->widget();
            }
        }
        delete vLayout;
    }
    vLayout = new QVBoxLayout();
    vLayout->setMargin(0);
    vLayout->setSpacing(0);
    int imgCnts = ihs.size();
    for(int i = 0; i < imgCnts;i++){
        QPushButton *btn = new QPushButton(ui->sideBar);
        btn->setObjectName(QString::number(i, 10));
        if (i == curImg) {
            btn->setFocus();
            IconHelper::Instance()->SetIcon(btn, QChar(0xf03e), 22);
        } else {
            IconHelper::Instance()->SetIcon(btn, QChar(0xf03e), 15);
        }
        btn->setToolTip(tr("图") + QString::number(i + 1, 10));
        connect(btn, SIGNAL(clicked()), this, SLOT(changeImage()));
        vLayout->addWidget(btn);
    }
    vLayout->addStretch();
    ui->sideBar->setLayout(vLayout);
}

bool MainWindow::sizeEqual(int image1, int image2)
{
    int lwidth,lheight,rwidth,rheight;
    lwidth = ihs[image1]->getDisplayWidth();
    lheight = ihs[image1]->getDisplayHeight();
    rwidth = ihs[image2]->getDisplayWidth();
    rheight = ihs[image2]->getDisplayHeight();
    if(lwidth == rwidth && rwidth == rheight){
        return true;
    } else {
        return false;
    }
}

void MainWindow::changeVersion(int ptr)
{
    ih->changeVersion(ptr);
}

void MainWindow::changeImage()
{
    QPushButton *btn = (QPushButton*)sender();
    bool ok;
    int index = btn->objectName().toInt(&ok, 10);
    curImg = index;
    ih = ihs[curImg];
    ih->draw();
    freshSide();
}

Ui::MainWindow *MainWindow::getUi() const
{
    return ui;
}


void MainWindow::on_historyButton_clicked()
{
    HistoryDialog *dlg = new HistoryDialog(this);
    dlg->show();
    dlg->exec();
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

void MainWindow::on_ScaleButton_clicked()
{
    ScaleDialog *dlg = new ScaleDialog(this);
    dlg->show();
    dlg->exec();
}

void MainWindow::on_rotateButton_clicked()
{
    RotateDialog *dlg = new RotateDialog(this);
    dlg->show();
    dlg->exec();
}

void MainWindow::on_AOPButton_clicked()
{
    AOPDialog *dlg = new AOPDialog(this);


    int count = ihs.size();

    sendLists(count);
    dlg->show();
    dlg->exec();
}
