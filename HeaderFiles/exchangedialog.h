#ifndef EXCHANGEDIALOG_H
#define EXCHANGEDIALOG_H

#include <QDialog>

namespace Ui {
    class ExchangeDialog;
}

class ExchangeDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ExchangeDialog(QWidget *parent = 0);
    ~ExchangeDialog();

private:
    Ui::ExchangeDialog *ui;
};

#endif // EXCHANGEDIALOG_H
