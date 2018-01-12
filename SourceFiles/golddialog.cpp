#include "HeaderFiles/golddialog.h"
#include "ui_golddialog.h"

GoldDialog::GoldDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::GoldDialog)
{
    ui->setupUi(this);
}

GoldDialog::~GoldDialog()
{
    delete ui;
}
