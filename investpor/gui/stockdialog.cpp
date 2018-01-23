#include "investpor/gui/stockdialog.h"
#include "ui_stockdialog.h"

#include "investpor/core/types.h"
#include "investpor/core/util.h"

using investpor::core::Operation;
using investpor::core::StockMarket;
using investpor::core::Util;

namespace investpor {

    namespace gui {

        StockDialog::StockDialog(QWidget *parent) :
            QDialog(parent),
            ui(new Ui::StockDialog)
        {
            ui->setupUi(this);
            ui->cbOperationType->addItem(Util::operationName(Operation::BUY));
            ui->cbOperationType->addItem(Util::operationName(Operation::SELL));

            for(uint i = StockMarket::BIST; i <= StockMarket::NYSE; ++i)
            {
                ui->cbMarket->addItem(QString("%1 - %2").arg(Util::stockMarketSymbol(static_cast<StockMarket>(i))).toUpper()
                                      .arg(Util::stockMarketName(static_cast<StockMarket>(i))));
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
            if(Operation::BUY == index) {
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

    }

}
