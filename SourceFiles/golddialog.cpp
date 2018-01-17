#include "HeaderFiles/golddialog.h"
#include "ui_golddialog.h"

#include "HeaderFiles/types.h"
#include "HeaderFiles/util.h"

using Investpor::Gold;
using Investpor::Operation;
using Investpor::Util;

GoldDialog::GoldDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::GoldDialog)
{
    ui->setupUi(this);
    ui->cbOperationType->addItem(Util::operationName(Operation::BUY));
    ui->cbOperationType->addItem(Util::operationName(Operation::SELL));

    for(uint i = Gold::GRAMS; i <= Gold::ONS; ++i)
    {
        ui->cbGoldType->addItem(Util::goldName(Gold(i)));
    }

    QObject::connect(ui->cbOperationType, QOverload<int>::of(&QComboBox::currentIndexChanged),
                     [this](int index){ rearrangeDialog(index); });

}

GoldDialog::~GoldDialog()
{
    delete ui;
}

void GoldDialog::rearrangeDialog(int index)
{
    if(index == 0) {
        ui->lblGoalPrice->setVisible(true);
        ui->dsbGoalPrice->setVisible(true);
    } else {
        ui->lblGoalPrice->setVisible(false);
        ui->dsbGoalPrice->setVisible(false);
    }
}
