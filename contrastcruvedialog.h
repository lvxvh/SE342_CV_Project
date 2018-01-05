#ifndef CONTRASTCRUVEDIALOG_H
#define CONTRASTCRUVEDIALOG_H

#include <QDialog>

enum transType {EXP, LOG};

namespace Ui {
class ContrastCruveDialog;
}

class ContrastCruveDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ContrastCruveDialog(QWidget *parent = 0);
    ~ContrastCruveDialog();

private:
    bool mouseInPix(QPoint m);
    QPoint mapToPix(QPoint p);
    Ui::ContrastCruveDialog *ui;
    transType type;
    void trans();
    QVector<QPoint> points;
protected:
    void paintEvent(QPaintEvent *);
    void closeEvent(QCloseEvent *);
    void mouseMoveEvent(QMouseEvent *e);
private slots:
    void on_aEdit_editingFinished();
    void on_bEdit_editingFinished();
    void on_cEdit_editingFinished();
    void on_typeBox_currentIndexChanged(int index);
    void on_aSlider_valueChanged(int value);
    void on_bSlider_valueChanged(int value);
    void on_cSlider_valueChanged(int value);
    void on_confirmButton_clicked();
    void on_cancelButton_clicked();
};

#endif // CONTRASTCRUVEDIALOG_H
