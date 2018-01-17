#include "HeaderFiles/exchangedialog.h"
#include "ui_exchangedialog.h"

#include "HeaderFiles/types.h"
#include "HeaderFiles/util.h"

using Investpor::Currency;
using Investpor::Operation;
using Investpor::Util;

ExchangeDialog::ExchangeDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ExchangeDialog)
{
    ui->setupUi(this);
    ui->cbOperationType->addItem(Util::operationName(Operation::BUY));
    ui->cbOperationType->addItem(Util::operationName(Operation::SELL));

    for(uint i = Currency::AUD; i <= Currency::USD; ++i)
    {
        ui->cbCurrency->addItem(QString("%1 - %2").arg(Util::currencySymbol(static_cast<Currency>(i)).toUpper())
                                                  .arg(Util::currencyName(static_cast<Currency>(i))));
    }

    QObject::connect(ui->cbOperationType, QOverload<int>::of(&QComboBox::currentIndexChanged),
                     [this](int index){ rearrangeDialog(index); });
}

ExchangeDialog::~ExchangeDialog()
{
    delete ui;
}

void ExchangeDialog::rearrangeDialog(int index)
{
    if(index == Operation::BUY) {
        ui->lblGoalPrice->setVisible(true);
        ui->dsbGoalPrice->setVisible(true);
    } else {
        ui->lblGoalPrice->setVisible(false);
        ui->dsbGoalPrice->setVisible(false);
    }
}
