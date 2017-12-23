#ifndef HISTOGRAMDIALOG_H
#define HISTOGRAMDIALOG_H

#include <QDialog>

namespace Ui {
class HistogramDialog;
}

class HistogramDialog : public QDialog
{
    Q_OBJECT

public:
    explicit HistogramDialog(QWidget *parent = 0);
    ~HistogramDialog();

private slots:
    void on_confirmButton_clicked();

    void on_cancelButton_clicked();

    void on_equalButton_clicked();

private:
    Ui::HistogramDialog *ui;

    QVector<int> histogram;
    int max;
protected:
    void closeEvent(QCloseEvent *);
    void paintEvent(QPaintEvent *);
};

#endif // HISTOGRAMDIALOG_H
