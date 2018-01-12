#include "HeaderFiles/funddialog.h"
#include "ui_funddialog.h"

FundDialog::FundDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::FundDialog)
{
    ui->setupUi(this);
}

FundDialog::~FundDialog()
{
    delete ui;
}
