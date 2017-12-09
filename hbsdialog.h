#ifndef HBSDIALOG_H
#define HBSDIALOG_H

#include <QDialog>

namespace Ui {
class hbsDialog;
}

class hbsDialog : public QDialog
{
    Q_OBJECT

public:
    explicit hbsDialog(QWidget *parent = 0);
    ~hbsDialog();

private:
    Ui::hbsDialog *ui;
};

#endif // HBSDIALOG_H
