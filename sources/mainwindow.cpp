#include "headers/mainwindow.h"
#include "ui_mainwindow.h"
#include "headers/iconhelper.h"
#include "headers/hsldialog.h"
#include "headers/BinaryDialog.h"
#include "headers/historydialog.h"
#include "headers/scaledialog.h"
#include "headers/rotatedialog.h"
#include "headers/aopdialog.h"
#include "headers/cropdialog.h"
#include "headers/contrastlinerdialog.h"
#include "headers/contrastcruvedialog.h"
#include "headers/histogramdialog.h"
#include "headers/filterdialog.h"
#include "headers/croprect.h"
#include "headers/parameterdialog.h"
#include "headers/bmbasicdialog.h"
#include "headers/dtdialog.h"
#include "headers/skeletondialog.h"
#include "headers/watersheddialog.h"


#include <QImage>
#include <QFileDialog>
#include <QMessageBox>
#include <QMouseEvent>
#include <QPaintEvent>
#include <QScrollBar>
#include <QPainter>
#include <QDesktopWidget>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ih = NULL;
    curImg = -1;
    IconHelper::Instance()->SetIcon(ui->closeButton, QChar(0xf00d), 20);
    IconHelper::Instance()->SetIcon(ui->detailButton, QChar(0xf0e2), 20);
    IconHelper::Instance()->SetIcon(ui->historyButton, QChar(0xf1da), 20);
    IconHelper::Instance()->SetIcon(ui->copyButton, QChar(0xf0c5), 20);
    ui->toolBox->setCurrentIndex(9);
    ui->action_Save->setEnabled(false);
    ui->action_SaveAs->setEnabled(false);
    ui->closeButton->setEnabled(false);
    ui->copyButton->setEnabled(false);
    ui->historyButton->setEnabled(false);
    ui->detailButton->setEnabled(false);
    ui->action_actual_pix->setEnabled(false);
    ui->action_fit_screen->setEnabled(false);
    isCropping = 0;
    isMarking = 0;
    cropStarted = 0;
}

MainWindow::~MainWindow()
{
    delete ui;
    for(int i = 0;i < ihs.size();++i) delete ihs[i];
    ihs.clear();
}



void MainWindow::on_action_Open_triggered()
{
    ImageHolder *newIh = new ImageHolder(this);
    ImageHolder *oldIh = ih;
    ih = newIh;
    if(newIh->loadImage()){
        ihs.push_back(ih);
        curImg = ihs.size() - 1;
        ui->toolBox->setCurrentIndex(0);
        ui->action_Save->setEnabled(true);
        ui->action_SaveAs->setEnabled(true);
        ui->closeButton->setEnabled(true);
        ui->closeButton->setEnabled(true);
        ui->copyButton->setEnabled(true);
        ui->historyButton->setEnabled(true);
        ui->detailButton->setEnabled(true);
        ui->action_actual_pix->setEnabled(true);
        ui->action_fit_screen->setEnabled(true);
    } else {
       delete newIh;
       ih = oldIh;
    }

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
        QPoint imgPos = mapToImg(e->pos());
        int x = imgPos.x();
        int y = imgPos.y();
        if(isInImg(e->pos())) {
            QRgb rgb = ih->getRgb(x,y);
            int channal = ih->getChannal();
            bool r = 1,g = 1, b = 1;
            if(channal != GRAY) {
                r = channal & 1;
                g = (channal >> 1) & 1;
                b = (channal >> 2) & 1;
            }
            ui->statusBar->showMessage(tr("X:%1 Y:%2 R:%3 G:%4 B:%5").arg(x).arg(y).arg(qRed(rgb)*r).arg(qGreen(rgb)*g).arg(qBlue(rgb)*b));
        } else {
            ui->statusBar->showMessage("");
        }
        if ((e->buttons() == Qt::LeftButton) && cropStarted) {
            if (isInImg(e->pos())) {
                cropRect.setEnd(mapToImg(e->pos()));
                ih->drawCropRect(cropRect.getRect());
                int beginX = qMin(cropRect.startPoint().x(), cropRect.endPoint().x());
                int beginY = qMin(cropRect.startPoint().y(), cropRect.endPoint().y());
                sendRectGeo(beginX, beginY,
                            cropRect.width(), cropRect.height());
            }
        } else if ((e->buttons() == Qt::LeftButton) && isMarking){
               ih->drawMark(mapToImg(e->pos()));
        }
    }
}

void MainWindow::mousePressEvent(QMouseEvent *e)
{
    if(ih != NULL) {
        /* i can't remember why i added reset here*/
        if(!isMarking)
            ih->resetImage();

        if(isCropping && e->buttons() == Qt::LeftButton) {
            if(isInImg(e->pos())){
                cropRect.setStart(mapToImg(e->pos()));
                cropRect.setEnd(mapToImg(e->pos()));
                cropStarted = true;
            }
        } else if ((e->buttons() == Qt::LeftButton) && isMarking){
            ih->drawMark(e->pos());
        }
    }
}

void MainWindow::mouseReleaseEvent(QMouseEvent *)
{
    cropStarted = false;
}

void MainWindow::on_detailButton_clicked()
{
    ih->undo();
}

void MainWindow::on_rButton_clicked()
{
    qint32 color = 0;
    if(ui->rgbButton->checkState() == Qt::Checked) {
        ui->rgbButton->setCheckState(Qt::Unchecked);
        color = RGB_G + RGB_B;
        ih->setChannal(color);
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
        if(color == RGB_ALL){
            ui->rgbButton->setCheckState(Qt::Checked);
        }
        if(color != 0) ih->setChannal(color);
        else ui->rButton->setCheckState(Qt::Checked);
    }
}

void MainWindow::on_rgbButton_clicked()
{
    if(ui->rgbButton->checkState() == Qt::Checked) {
        qint32 color = RGB_ALL;
        ui->rButton->setCheckState(Qt::Checked);
        ui->gButton->setCheckState(Qt::Checked);
        ui->bButton->setCheckState(Qt::Checked);
        ih->setChannal(color);

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
        ih->setChannal(color);
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
        if(color == RGB_ALL){
            ui->rgbButton->setCheckState(Qt::Checked);
        }
        if(color != 0) ih->setChannal(color);
        else ui->gButton->setCheckState(Qt::Checked);
    }
}

void MainWindow::on_bButton_clicked()
{
    qint32 color = 0;
    if(ui->rgbButton->checkState() == Qt::Checked) {
        ui->rgbButton->setCheckState(Qt::Unchecked);
        color = RGB_R + RGB_G;
        ih->setChannal(color);
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
        if(color == RGB_ALL){
            ui->rgbButton->setCheckState(Qt::Checked);
        }
        if(color != 0) ih->setChannal(color);
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
    if(lwidth == rwidth && lheight == rheight){
        return true;
    } else {
        return false;
    }
}

void MainWindow::AOP(int i1, int i2, int op)
{
    QImage image1 = ihs[i1]->getDisplayImage();
    QImage image2 = ihs[i2]->getDisplayImage();
    int width = image1.width();
    int height = image1.height();
    QImage outImage(width, height, QImage::Format_RGB32);
    QRgb p1,p2;
    int r1,g1,b1,r2,g2,b2,r,g,b;
    for(int y = 0;y < height;++y){
        for(int x = 0;x < width;++x){
            p1 = image1.pixel(x,y);
            r1 = qRed(p1);
            g1 = qGreen(p1);
            b1 = qBlue(p1);
            p2 = image2.pixel(x,y);
            r2 = qRed(p2);
            g2 = qGreen(p2);
            b2 = qBlue(p2);
            if(op == 0) {
                r = r1 + r2;
                if(r > 255) r = 255;
                g = g1 + g2;
                if(g > 255) g = 255;
                b = b1 + b2;
                if(b > 255) b = 255;

            } else if(op == 1){
                r = r1 - r2;
                if(r < 0) r = 0;
                g = g1 - g2;
                if(g < 0) g = 0;
                b = b1 - b2;
                if(b < 0) b = 0;
            } else {
                r = r1 * r2;
                if(r > 255) r = 255;
                g = g1 * g2;
                if(g > 255) g = 255;
                b = b1 * b2;
                if(b > 255) b = 255;
            }
            outImage.setPixel(x,y,qRgb(r,g,b));
        }
    }
    ih = new ImageHolder(this);
    ihs.push_back(ih);
    curImg = ihs.size() -1;
    ih->setDisplayImage(outImage);
    ih->cacheImage(tr("打开"));
    ih->draw();
    freshSide();
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
    refreshLog();
}

void MainWindow::receiveEditedGeo(int x, int y, int w, int h)
{
    cropRect.setStart(QPoint(x, y));
    cropRect.setEnd(QPoint(x + w, y + h));
    ih->drawCropRect(cropRect.getRect());
}

Ui::MainWindow *MainWindow::getUi() const
{
    return ui;
}


void MainWindow::on_historyButton_clicked()
{
    HistoryDialog *dlg = new HistoryDialog(this);
    dlg->setWindowTitle(tr("历史记录"));
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
        dlg->setWindowTitle(tr("双阈值"));
        dlg->exec();
    } else {
        QMessageBox::information(this, QObject::tr("提示"), QObject::tr("只能处理灰度图像"));
    }
}

void MainWindow::on_ScaleButton_clicked()
{
    ScaleDialog *dlg = new ScaleDialog(this);
    dlg->setWindowTitle(tr("放缩"));
    dlg->exec();
}

void MainWindow::on_rotateButton_clicked()
{
    RotateDialog *dlg = new RotateDialog(this);
    dlg->setWindowTitle(tr("旋转"));
    dlg->exec();
}

void MainWindow::on_AOPButton_clicked()
{
    AOPDialog *dlg = new AOPDialog(this);
    dlg->setWindowTitle(tr("代数操作"));
    int count = ihs.size();

    sendLists(count);
    dlg->exec();
}

void MainWindow::on_cutButton_clicked()
{
    isCropping = 1;
    cropRect.reset();
    CropDialog *dlg = new CropDialog(ih->getDisplayWidth(), ih->getDisplayHeight(), this);
    dlg->setWindowTitle(tr("裁剪"));
    dlg->show();
}

bool MainWindow::isInImg(QPoint pos)
{

    qint32 x=pos.x() - ui->image->pos().x() - 79 + (ui->scrollArea->horizontalScrollBar()->value());
    qint32 y=pos.y() - ui->image->pos().y() - 85 + (ui->scrollArea->verticalScrollBar()->value());

    return x >= 0 && x < ih->getDisplayWidth() && y >= 0 && y < ih->getDisplayHeight();
}

QPoint MainWindow::mapToImg(QPoint point)
{
    qint32 x=point.x() - ui->image->pos().x() - 79 + (ui->scrollArea->horizontalScrollBar()->value());
    qint32 y=point.y() - ui->image->pos().y() - 85 + (ui->scrollArea->verticalScrollBar()->value());

    return QPoint(x, y);
}


void MainWindow::setIsMarking(bool value)
{
    isMarking = value;
}

ImageHolder *MainWindow::getIhByIndex(int index) const
{
    return ihs[index];
}

void MainWindow::setIsCropping(bool value)
{
    isCropping = value;
}


void MainWindow::on_copyButton_clicked()
{
    QImage cur = ih->getOutImage();
    ImageHolder *newIh = new ImageHolder(this);
    newIh->setChannal(ih->getChannal());
    if(newIh->getChannal() == GRAY){
        newIh->setGrayCheckPoint(0);
    }
    ihs.push_back(newIh);
    curImg = ihs.size() - 1;
    ih = newIh;
    ih->setDisplayImage(cur);
    ih->cacheImage("打开");
    ih->draw();
    freshSide();
}

void MainWindow::on_closeButton_clicked()
{
    delete ihs[curImg];
    ihs.erase(ihs.begin() + curImg);
    curImg = ihs.size() - 1;
    ui->toolBox->setCurrentIndex(9);
    if(curImg >= 0){
        ih = ihs[curImg];
        ih->draw();
    } else {
        ih = NULL;
        ui->image->clear();
        ui->action_Save->setEnabled(false);
        ui->action_SaveAs->setEnabled(false);
        ui->closeButton->setEnabled(false);
        ui->closeButton->setEnabled(false);
        ui->copyButton->setEnabled(false);
        ui->historyButton->setEnabled(false);
        ui->detailButton->setEnabled(false);
        ui->action_actual_pix->setEnabled(false);
        ui->action_fit_screen->setEnabled(false);
    }
    freshSide();
}

void MainWindow::on_toolBox_currentChanged(int index)
{
    if(ih == NULL) {
        ui->toolBox->setCurrentIndex(9);
    } else {
        int channal = ih->getChannal();
        if(index == 0){
            if (channal == GRAY){
                ui->toolBox->setCurrentIndex(4);
                QMessageBox::information(this, QObject::tr("提示"), QObject::tr("只能处理彩色图像"));
            } else {
                bool r = channal & 1;
                bool g = (channal >> 1) & 1;
                bool b = (channal >> 2) & 1;
                if(r){
                    ui->rButton->setCheckState(Qt::Checked);
                }
                if(g){
                    ui->rButton->setCheckState(Qt::Checked);
                }
                if(b){
                    ui->rButton->setCheckState(Qt::Checked);
                }
                if(r && g && b){
                    ui->rgbButton->setCheckState(Qt::Checked);
                }
            }
        } else if(index == 1 && channal == GRAY && ih->isBinary()) {
            ui->toolBox->setCurrentIndex(2);
            QMessageBox::information(this, QObject::tr("提示"), QObject::tr("已是二值图像"));
        } else if(index != 0 && index != 2 && index != 9 && channal != GRAY){
            ui->toolBox->setCurrentIndex(0);
            QMessageBox::information(this, QObject::tr("提示"), QObject::tr("只能处理灰度图像"));
        } else if(index == 7 && !ih->isBinary()){
            ui->toolBox->setCurrentIndex(1);
            QMessageBox::information(this, QObject::tr("提示"), QObject::tr("只能处理二值图像"));
        }
    }
}

void MainWindow::on_linerButton_clicked()
{
    ContrastLinerDialog *dlg = new ContrastLinerDialog(ih->isGray(), this);
    dlg->setWindowTitle(tr("对比度线性变换"));
    dlg->exec();
}

void MainWindow::on_nonlinerButton_clicked()
{
    ContrastCruveDialog *dlg = new ContrastCruveDialog(this);
    dlg->setWindowTitle(tr("对比度非线性变换"));
    dlg->exec();
}

void MainWindow::on_HGButton_clicked()
{
    HistogramDialog *dlg = new HistogramDialog(this);
    dlg->setWindowTitle(tr("直方图"));
    dlg->exec();
}

void MainWindow::on_filterButton_clicked()
{
    FilterDialog *dlg = new FilterDialog(this);
    dlg->setWindowTitle(tr("滤波器"));
    dlg->exec();
}

void MainWindow::on_sobelButton_clicked()
{
    ParameterDialog *dlg = new ParameterDialog(SOBEL, this);
    dlg->setWindowTitle(tr("Sobel参数调整"));
    dlg->exec();
}

void MainWindow::on_laplacianButton_clicked()
{
    ParameterDialog *dlg = new ParameterDialog(LAPLAS, this);
    dlg->setWindowTitle(tr("Laplacian参数调整"));
    dlg->exec();
}

void MainWindow::on_cannyButton_clicked()
{
    ParameterDialog *dlg = new ParameterDialog(CANNY, this);
    dlg->setWindowTitle(tr("Canny参数调整"));
    dlg->exec();
}

void MainWindow::on_houghLineButton_clicked()
{
    ParameterDialog *dlg = new ParameterDialog(HOUGHLINE, this);
    dlg->setWindowTitle(tr("霍夫直线检测参数调整"));
    dlg->exec();
}


void MainWindow::on_houghCircleButton_clicked()
{
    ParameterDialog *dlg = new ParameterDialog(HOUGHCIRCLE, this);
    dlg->setWindowTitle(tr("霍夫圆检测参数调整"));
    dlg->exec();
}

void MainWindow::on_BMBasicButton_clicked()
{
    BMBasicDialog *dlg = new BMBasicDialog(BASIC, this);
    dlg->setWindowTitle(tr("二值形态学基本操作"));
    dlg->exec();
}

void MainWindow::on_thinButton_clicked()
{
    ih->thinning();
}

void MainWindow::on_thickenButton_clicked()
{
    ih->thickening();
}

void MainWindow::on_DTButton_clicked()
{
    DTDialog *dlg = new DTDialog(this);
    dlg->setWindowTitle(tr("距离变换结构元素选择"));
    dlg->exec();
}

void MainWindow::on_skeletonButton_clicked()
{
    SkeletonDialog *dlg = new SkeletonDialog(this);
    dlg->setWindowTitle(tr("骨架"));
    dlg->exec();
}

void MainWindow::on_BMRebuildButton_clicked()
{
    BMBasicDialog *dlg = new BMBasicDialog(REBUILD, this);
    dlg->setWindowTitle(tr("二值形态学重建"));
    int count = ihs.size();
    sendLists(count);
    dlg->exec();
}

void MainWindow::on_GBMBasicButton_clicked()
{
    BMBasicDialog *dlg = new BMBasicDialog(GBM, this);
    dlg->setWindowTitle(tr("灰度形态学基本操作"));
    dlg->exec();
}


void MainWindow::on_GMRButton_clicked()
{
    BMBasicDialog *dlg = new BMBasicDialog(GREBUILD, this);
    dlg->setWindowTitle(tr("灰度形态学重建"));
    int count = ihs.size();
    sendLists(count);
    dlg->exec();
}

void MainWindow::on_watershedButton_clicked()
{
    isMarking = 1;
    WatershedDialog *dlg = new WatershedDialog(this);
    dlg->setWindowTitle(tr("分水岭标记"));
    dlg->show();
}
