#ifndef HBSDIALOG_H
#define HBSDIALOG_H

#include <QDialog>

namespace Ui {
class hslDialog;
}

class hslDialog : public QDialog
{
    Q_OBJECT

public:
    explicit hslDialog(QWidget *parent = 0);
    ~hslDialog();

private slots:

    void on_hEdit_textEdited(const QString &arg1);

    void on_hEdit_editingFinished();

    void on_hSlider_valueChanged(int value);

    void on_sEdit_textEdited(const QString &arg1);

    void on_sSlider_valueChanged(int value);

    void on_sEdit_editingFinished();

    void on_lEdit_textEdited(const QString &arg1);

    void on_lEdit_editingFinished();

    void on_lSlider_valueChanged(int value);

    void on_confirmButton_clicked();

    void on_cancelButton_clicked();

private:
    Ui::hslDialog *ui;
};

#endif // HBSDIALOG_H
