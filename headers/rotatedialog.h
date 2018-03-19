#ifndef ROTATEDIALOG_H
#define ROTATEDIALOG_H

#include <QDialog>

namespace Ui {
class RotateDialog;
}

class RotateDialog : public QDialog
{
    Q_OBJECT

public:
    explicit RotateDialog(QWidget *parent = 0);
    ~RotateDialog();

private slots:
    void on_angleSlider_valueChanged(int value);

    void on_angleEdit_editingFinished();

    void on_angleEdit_textEdited(const QString &arg1);

    void on_confirmButton_clicked();

    void on_cancelButton_clicked();

private:
    Ui::RotateDialog *ui;

    void closeEvent(QCloseEvent *e);
};

#endif // ROTATEDIALOG_H
