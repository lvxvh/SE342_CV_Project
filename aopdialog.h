#ifndef AOPDIALOG_H
#define AOPDIALOG_H

#include <QDialog>

namespace Ui {
class AOPDialog;
}

class AOPDialog : public QDialog
{
    Q_OBJECT

public:
    explicit AOPDialog(QWidget *parent = 0);
    ~AOPDialog();

private slots:
    void receiveLists(int count);

    void on_confirmButton_clicked();

private:
    Ui::AOPDialog *ui;
};

#endif // AOPDIALOG_H
