#ifndef PARAMETERDIALOG_H
#define PARAMETERDIALOG_H

#include <QDialog>

enum action {SOBEL, LAPLAS, CANNY, HOUGHLINE, HOUGHCIRCLE};

namespace Ui {
class ParameterDialog;
}

class ParameterDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ParameterDialog(action act, QWidget *parent = 0);
    ~ParameterDialog();

private slots:
    void on_confirmButton_clicked();

    void on_cancelButton_clicked();

    void on_houghTEdit_editingFinished();

    void on_htEdit_editingFinished();

    void on_ltEdit_editingFinished();

    void on_tEdit_editingFinished();

    void on_sigmaEdit_editingFinished();

private:
    Ui::ParameterDialog *ui;
    action a;
protected:
    void closeEvent(QCloseEvent *);
};

#endif // PARAMETERDIALOG_H
