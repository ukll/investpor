#ifndef STOCKDIALOG_H
#define STOCKDIALOG_H

#include <QDialog>

namespace Ui {
    class StockDialog;
}

class StockDialog : public QDialog
{
    Q_OBJECT

public:
    explicit StockDialog(QWidget *parent = 0);
    ~StockDialog();

private:
    Ui::StockDialog *ui;

    void rearrangeDialog(int index);
};

#endif // STOCKDIALOG_H
