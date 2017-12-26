#ifndef BMBASICDIALOG_H
#define BMBASICDIALOG_H

#include <QDialog>

enum MophoType {DIL, ERO, OPN, CLS};

namespace Ui {
class BMBasicDialog;
}

class BMBasicDialog : public QDialog
{
    Q_OBJECT

public:
    explicit BMBasicDialog(QWidget *parent = 0);
    ~BMBasicDialog();

private slots:
    void on_button_00_clicked();

    void on_button_01_clicked();

    void on_button_02_clicked();

    void on_button_10_clicked();

    void on_button_11_clicked();

    void on_button_12_clicked();

    void on_button_20_clicked();

    void on_button_21_clicked();

    void on_button_22_clicked();

    void on_originButton_clicked();

    void on_confirmButton_clicked();

    void on_cancelButton_clicked();

    void on_comboBox_currentIndexChanged(int index);

private:
    Ui::BMBasicDialog *ui;
    QPushButton *button[3][3];
    int se[3][3] = {{0}};
    QPoint origin;
    MophoType type;
    bool isChoosingOrigin = 0;
};

#endif // BMBASICDIALOG_H
