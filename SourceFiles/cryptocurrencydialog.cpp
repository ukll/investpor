#include "HeaderFiles/cryptocurrencydialog.h"
#include "ui_cryptocurrencydialog.h"

CryptocurrencyDialog::CryptocurrencyDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CryptocurrencyDialog)
{
    ui->setupUi(this);
}

CryptocurrencyDialog::~CryptocurrencyDialog()
{
    delete ui;
}
