#include "HeaderFiles/cryptocurrencydialog.h"
#include "ui_cryptocurrencydialog.h"

#include "HeaderFiles/types.h"
#include "HeaderFiles/util.h"

using Investpor::Operation;
using Investpor::Cryptocurrency;
using Investpor::Util;

CryptocurrencyDialog::CryptocurrencyDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CryptocurrencyDialog)
{
    ui->setupUi(this);
    ui->cbOperationType->addItem(Util::operationName(Operation::BUY));
    ui->cbOperationType->addItem(Util::operationName(Operation::SELL));

    for(int i = Cryptocurrency::ETC; i <= Cryptocurrency::XRP; ++i)
    {
        ui->cbCryptocurrency->addItem(QString("%1 - %2").arg(Util::cryptoCurrencySymbol(Cryptocurrency(i)).toUpper())
                                                        .arg(Util::cryptoCurrencyName(Cryptocurrency(i)))
                                        );
    }

    QObject::connect(ui->cbOperationType, QOverload<int>::of(&QComboBox::currentIndexChanged),
                     [this](int index){ rearrangeDialog(index); });
}

CryptocurrencyDialog::~CryptocurrencyDialog()
{
    delete ui;
}

void CryptocurrencyDialog::rearrangeDialog(int index)
{
    if(index == 0) {
        ui->lblGoalPrice->setVisible(true);
        ui->dsbGoalPrice->setVisible(true);
    } else {
        ui->lblGoalPrice->setVisible(false);
        ui->dsbGoalPrice->setVisible(false);
    }
}
