#ifndef WATERSHEDDIALOG_H
#define WATERSHEDDIALOG_H

#include <QDialog>

namespace Ui {
class WatershedDialog;
}

class WatershedDialog : public QDialog
{
    Q_OBJECT

public:
    explicit WatershedDialog(QWidget *parent = 0);
    ~WatershedDialog();

private slots:
    void on_cancelButton_clicked();

    void on_confirmButton_clicked();

private:
    Ui::WatershedDialog *ui;
protected:
    void closeEvent(QCloseEvent *);
};

#endif // WATERSHEDDIALOG_H
