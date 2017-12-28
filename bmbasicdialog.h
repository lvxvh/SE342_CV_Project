#ifndef BMBASICDIALOG_H
#define BMBASICDIALOG_H

#include <QDialog>

enum MophoType {DIL, ERO, OPN, CLS, OPNR, CLSR};
enum SEType {SQR, CRS, ELL};
enum BMType {BASIC, REBUILD, GBM, GREBUILD};

namespace Ui {
class BMBasicDialog;
}

class BMBasicDialog : public QDialog
{
    Q_OBJECT

public:
    explicit BMBasicDialog(BMType Ttype, QWidget *parent = 0);
    ~BMBasicDialog();

private slots:


    void on_confirmButton_clicked();

    void on_cancelButton_clicked();

    void on_typeBox_currentIndexChanged(int index);

    void on_seBox_currentIndexChanged(int index);

    void on_xEdit_editingFinished();

    void on_yEdit_editingFinished();

    void on_centerButton_clicked();

    void on_widthEdit_editingFinished();

    void on_heightEdit_editingFinished();

private:
    Ui::BMBasicDialog *ui;
    MophoType type;
    SEType sType;
    BMType Ttype;
};

#endif // BMBASICDIALOG_H
