#include "HeaderFiles/bonddialog.h"
#include "ui_bonddialog.h"

BondDialog::BondDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::BondDialog)
{
    ui->setupUi(this);
}

BondDialog::~BondDialog()
{
    delete ui;
}
