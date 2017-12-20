#ifndef CONTRASTLINERDIALOG_H
#define CONTRASTLINERDIALOG_H

#include <QDialog>
#include <QPaintEvent>
#include <QVector>

#define PIX_X 80
#define PIX_Y 80

enum MouseState {none, add, drag, dragLine};
enum MousePos {beforeAll, other, afterAll};

namespace Ui {
class ContrastLinerDialog;
}

class ContrastLinerDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ContrastLinerDialog(QWidget *parent = 0);
    ~ContrastLinerDialog();


private:
    bool nearLine(QPoint p);
    int nearPoint(QPoint p);
    MousePos beforeOrAfterAll(QPoint p);
    MouseState ms;
    bool mouseInPix(QPoint m);
    QPoint mapToPix(QPoint p);
    Ui::ContrastLinerDialog *ui;

    QVector<QPoint> points;

protected:
    void paintEvent(QPaintEvent *);
    void mouseMoveEvent(QMouseEvent *e);
    void mousePressEvent(QMouseEvent *e);
};

#endif //CONTRASTLINERDIALOG_H
