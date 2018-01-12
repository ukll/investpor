#include "HeaderFiles/exchangedialog.h"
#include "ui_exchangedialog.h"

ExchangeDialog::ExchangeDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ExchangeDialog)
{
    ui->setupUi(this);
}

ExchangeDialog::~ExchangeDialog()
{
    delete ui;
}
