#ifndef BINARYDIALOG_H
#define BINARYDIALOG_H

#include <QDialog>

namespace Ui {
class BinaryDialog;
}

class BinaryDialog : public QDialog
{
    Q_OBJECT

public:
    explicit BinaryDialog(QWidget *parent = 0);
    ~BinaryDialog();

private slots:
    void on_hEdit_textEdited(const QString &arg1);

    void on_hEdit_editingFinished();

    void on_hSlider_valueChanged(int value);

    void on_lEdit_textEdited(const QString &arg1);

    void on_lEdit_editingFinished();

    void on_lSlider_valueChanged(int value);

    void on_confirmButton_clicked();

    void on_cancelButton_clicked();

private:
    Ui::BinaryDialog *ui;

    void closeEvent(QCloseEvent *e);
};

#endif // BINARYDIALOG_H
