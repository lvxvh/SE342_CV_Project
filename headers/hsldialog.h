#ifndef HBSDIALOG_H
#define HBSDIALOG_H

#include <QDialog>

namespace Ui {
class HslDialog;
}

class HslDialog : public QDialog
{
    Q_OBJECT

public:
    explicit HslDialog(QWidget *parent = 0);
    ~HslDialog();

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
    Ui::HslDialog *ui;

    void closeEvent(QCloseEvent *e);
};

#endif // HBSDIALOG_H
