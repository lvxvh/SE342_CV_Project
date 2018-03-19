#ifndef FILTERDIALOG_H
#define FILTERDIALOG_H

#include <QDialog>
#include <QLineEdit>

enum filterType {AVE, MID, GAUS};

namespace Ui {
class FilterDialog;
}

class FilterDialog : public QDialog
{
    Q_OBJECT

public:
    explicit FilterDialog(QWidget *parent = 0);
    ~FilterDialog();

private slots:
    void on_confirmButton_clicked();

    void on_cancelButton_clicked();

    void on_sizeBox_currentIndexChanged(int index);

    void on_typeBox_currentIndexChanged(int index);

    void on_sigmaEdit_editingFinished();

private:
    void genMatrix();
    Ui::FilterDialog *ui;
    QLineEdit *edit[5][5];
    filterType type;
    int size;
    float sigma;

protected:
    void closeEvent(QCloseEvent *);
};

#endif // FILTERDIALOG_H
