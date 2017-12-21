#ifndef CONTRASTLINERDIALOG_H
#define CONTRASTLINERDIALOG_H

#include <QDialog>
#include <QPaintEvent>
#include <QVector>

#define PIX_X 80
#define PIX_Y 80

enum MouseState {none, add, drag, dragLine, del};
enum MousePos {beforeAll, other, afterAll};

namespace Ui {
class ContrastLinerDialog;
}

class ContrastLinerDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ContrastLinerDialog(bool isGray, QWidget *parent = 0);
    ~ContrastLinerDialog();


private:

    bool nearLine(QPoint p);
    int nearPoint(QPoint p);
    MousePos beforeOrAfterAll(QPoint p);
    MouseState ms;
    bool removing;

    bool mouseInPix(QPoint m);

    bool edit;
    void setEditable(bool stat);
    int curEditing;
    QPoint mapToPix(QPoint p);
    Ui::ContrastLinerDialog *ui;

    QVector<QPoint> points;


protected:
    void paintEvent(QPaintEvent *);
    void mouseMoveEvent(QMouseEvent *e);
    void mousePressEvent(QMouseEvent *e);
    void mouseReleaseEvent(QMouseEvent *e);
    void closeEvent(QCloseEvent *);

private slots:
    void on_deleteButton_clicked();
    void on_inEdit_editingFinished();
    void on_outEdit_editingFinished();
    void on_confirmButton_clicked();
    void on_cancelButton_clicked();
};

#endif //CONTRASTLINERDIALOG_H
