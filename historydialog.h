#ifndef HISTORYDIALOG_H
#define HISTORYDIALOG_H

#include <QDialog>

namespace Ui {
class historyDialog;
}

class historyDialog : public QDialog
{
    Q_OBJECT

public:
    explicit historyDialog(QWidget *parent = 0);
    ~historyDialog();

private:
    Ui::historyDialog *ui;
};

#endif // HISTORYDIALOG_H
