#ifndef CROPDIALOG_H
#define CROPDIALOG_H

#include <QDialog>

namespace Ui {
class CropDialog;
}

class CropDialog : public QDialog
{
    Q_OBJECT

public:
    explicit CropDialog(int w, int h, QWidget *parent = 0);
    ~CropDialog();

signals:
    void sendEditedGeo(int x, int y, int w, int h);

private slots:
    void receiveRecGeo(int x, int y, int w, int h);
    void on_xEdit_editingFinished();

    void on_yEdit_editingFinished();

    void on_widthEdit_editingFinished();

    void on_heightEdit_editingFinished();

    void on_confirmButton_clicked();

    void on_cancelButton_clicked();

private:
    void reportChange();
    Ui::CropDialog *ui;
    int oWidth;
    int oHeight;
protected:
    void closeEvent(QCloseEvent *e);
};

#endif // CROPDIALOG_H
