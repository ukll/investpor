#include "HeaderFiles/funddialog.h"
#include "ui_funddialog.h"

#include "HeaderFiles/types.h"
#include "HeaderFiles/util.h"

using Investpor::Operation;
using Investpor::Util;

FundDialog::FundDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::FundDialog)
{
    ui->setupUi(this);
    ui->cbOperationType->addItem(Util::operationName(Operation::BUY));
    ui->cbOperationType->addItem(Util::operationName(Operation::SELL));

    QObject::connect(ui->cbOperationType, QOverload<int>::of(&QComboBox::currentIndexChanged),
                     [this](int index){ rearrangeDialog(index); });
    QObject::connect(ui->deOrderDate, &QDateEdit::dateChanged, ui->deOperationDate, &QDateEdit::setMinimumDate);
}

FundDialog::~FundDialog()
{
    delete ui;
}

void FundDialog::rearrangeDialog(int index)
{
    if(index == Operation::BUY) {
        ui->lblName->setVisible(true);
        ui->leName->setVisible(true);
        ui->lblGoalPrice->setVisible(true);
        ui->dsbGoalPrice->setVisible(true);
    } else {
        ui->lblName->setVisible(false);
        ui->leName->setVisible(false);
        ui->lblGoalPrice->setVisible(false);
        ui->dsbGoalPrice->setVisible(false);
    }
}
