#ifndef BIANRYDIALOG_H
#define BIANRYDIALOG_H

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

private:
    Ui::BinaryDialog *ui;
};

#endif // BIANRYDIALOG_H
