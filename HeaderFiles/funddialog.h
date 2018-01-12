#ifndef FUNDDIALOG_H
#define FUNDDIALOG_H

#include <QDialog>

namespace Ui {
    class FundDialog;
}

class FundDialog : public QDialog
{
    Q_OBJECT

public:
    explicit FundDialog(QWidget *parent = 0);
    ~FundDialog();

private:
    Ui::FundDialog *ui;
};

#endif // FUNDDIALOG_H
