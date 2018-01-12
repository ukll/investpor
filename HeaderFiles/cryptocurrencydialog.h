#ifndef CRYPTOCURRENCYDIALOG_H
#define CRYPTOCURRENCYDIALOG_H

#include <QDialog>

namespace Ui {
    class CryptocurrencyDialog;
}

class CryptocurrencyDialog : public QDialog
{
    Q_OBJECT

public:
    explicit CryptocurrencyDialog(QWidget *parent = 0);
    ~CryptocurrencyDialog();

private:
    Ui::CryptocurrencyDialog *ui;
};

#endif // CRYPTOCURRENCYDIALOG_H
