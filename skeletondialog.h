#ifndef SKELETONDIALOG_H
#define SKELETONDIALOG_H

#include <QDialog>

namespace Ui {
class SkeletonDialog;
}

class SkeletonDialog : public QDialog
{
    Q_OBJECT

public:
    explicit SkeletonDialog(QWidget *parent = 0);
    ~SkeletonDialog();

    QVector<QImage> sn;
private slots:
    void on_extractButton_clicked();

    void on_rebuildButton_clicked();

private:
    Ui::SkeletonDialog *ui;
};

#endif // SKELETONDIALOG_H
