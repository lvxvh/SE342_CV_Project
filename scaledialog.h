#ifndef SCALEDIALOG_H
#define SCALEDIALOG_H

#include <QDialog>

namespace Ui {
class ScaleDialog;
}

class ScaleDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ScaleDialog(QWidget *parent = 0);
    ~ScaleDialog();

private slots:
    void on_factorEdit_editingFinished();

    void on_confirmButton_clicked();

    void on_cancelButton_clicked();

    void on_zoomInButton_clicked();

    void on_zoomOutButton_clicked();

private:
    Ui::ScaleDialog *ui;

    void closeEvent(QCloseEvent *e);
};

#endif // SCALEDIALOG_H
