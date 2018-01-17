#include "HeaderFiles/stockdialog.h"
#include "ui_stockdialog.h"

#include "HeaderFiles/types.h"
#include "HeaderFiles/util.h"

using Investpor::Operation;
using Investpor::StockMarket;
using Investpor::Util;

StockDialog::StockDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::StockDialog)
{
    ui->setupUi(this);
    ui->cbOperationType->addItem(Util::operationName(Operation::BUY));
    ui->cbOperationType->addItem(Util::operationName(Operation::SELL));

    for(uint i = StockMarket::BIST; i <= StockMarket::NYSE; ++i)
    {
        ui->cbMarket->addItem(QString("%1 - %2").arg(Util::stockMarketSymbol(StockMarket(i))).toUpper()
                                                .arg(Util::stockMarketName(StockMarket(i))));
    }

    QObject::connect(ui->cbOperationType, QOverload<int>::of(&QComboBox::currentIndexChanged),
                     [this](int index){ rearrangeDialog(index); });
}

StockDialog::~StockDialog()
{
    delete ui;
}

void StockDialog::rearrangeDialog(int index)
{
    if(index == 0) {
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
