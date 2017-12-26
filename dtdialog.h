#ifndef DTDIALOG_H
#define DTDIALOG_H

#include <QDialog>

namespace Ui {
class DTDialog;
}

class DTDialog : public QDialog
{
    Q_OBJECT

public:
    explicit DTDialog(QWidget *parent = 0);
    ~DTDialog();

private slots:
    void on_confirmButton_clicked();

    void on_cancelButton_clicked();

private:
    Ui::DTDialog *ui;
};

#endif // DTDIALOG_H
