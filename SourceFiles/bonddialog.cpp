#include "HeaderFiles/bonddialog.h"
#include "ui_bonddialog.h"

#include "HeaderFiles/types.h"
#include "HeaderFiles/util.h"

using Investpor::Operation;
using Investpor::Util;

BondDialog::BondDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::BondDialog)
{
    ui->setupUi(this);
    ui->cbOperationType->addItem(Util::operationName(Operation::BUY));
    ui->cbOperationType->addItem(Util::operationName(Operation::SELL));

    QObject::connect(ui->cbOperationType, QOverload<int>::of(&QComboBox::currentIndexChanged),
                     [this](int index){ rearrangeDialog(index); });
    QObject::connect(ui->deTerm, &QDateEdit::dateChanged,
                     [this](QDate date){ ui->deDate->setMaximumDate(date); });
}

BondDialog::~BondDialog()
{
    delete ui;
}

void BondDialog::rearrangeDialog(int index)
{
    if(index == 0) {
        ui->lblTerm->setVisible(true);
        ui->deTerm->setVisible(true);
        ui->lblNominalValue->setVisible(true);
        ui->dsbNominalValue->setVisible(true);
    } else {
        ui->lblTerm->setVisible(false);
        ui->deTerm->setVisible(false);
        ui->lblNominalValue->setVisible(false);
        ui->dsbNominalValue->setVisible(false);
    }
}
