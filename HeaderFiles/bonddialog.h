#ifndef BONDDIALOG_H
#define BONDDIALOG_H

#include <QDialog>

namespace Ui {
    class BondDialog;
}

class BondDialog : public QDialog
{
    Q_OBJECT

public:
    explicit BondDialog(QWidget *parent = 0);
    ~BondDialog();

private:
    Ui::BondDialog *ui;

    void rearrangeDialog(int index);
};

#endif // BONDDIALOG_H
