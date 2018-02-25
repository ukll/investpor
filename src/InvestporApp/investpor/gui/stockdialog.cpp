#include "investpor/gui/stockdialog.h"
#include "ui_stockdialog.h"

#include "investpor/core/util.h"

using investpor::core::Util;

namespace investpor {

    namespace gui {

        StockDialog::StockDialog(QWidget *parent) :
            QDialog(parent),
            ui(new Ui::StockDialog)
        {
            ui->setupUi(this);
            setWindowTitle(tr("Stock Transaction"));
            ui->vlStatusBar->addWidget(&statusBar);
            symbolValidator.setRegularExpression(Util::stockSymbolRegularExpression());
            ui->leSymbol->setValidator(&symbolValidator);
            nameValidator.setRegularExpression(Util::stockNameRegularExpression());
            ui->leName->setValidator(&nameValidator);

            for(int i = Util::BUY, cbOpIndex = 0; i <= Util::SELL; ++i, ++cbOpIndex)
            {
                ui->cbOperationType->addItem(Util::operationName(static_cast<Util::Operation>(i)));
                ui->cbOperationType->setItemData(cbOpIndex, i);
            }

            for(uint i = Util::BMEX, cbStockMarketIndex = 0; i <= Util::XTSE; ++i, ++cbStockMarketIndex)
            {
                ui->cbMarket->addItem(QString("%1 - %2")
                                      .arg(Util::stockMarketSymbol(static_cast<Util::StockMarket>(i))).toUpper()
                                      .arg(Util::stockMarketName(static_cast<Util::StockMarket>(i))));
                ui->cbMarket->setItemData(cbStockMarketIndex, i);
            }

            connect(ui->cbOperationType, SIGNAL(currentIndexChanged(int)), this, SLOT(rearrangeDialog()));
            connect(ui->bbTransactionApproval, &QDialogButtonBox::accepted, this, &StockDialog::accept);
        }

        StockDialog::~StockDialog()
        {
            delete ui;
        }

        void StockDialog::rearrangeDialog()
        {
            if(Util::BUY == ui->cbOperationType->currentData().toInt()) {
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

        void StockDialog::accept()
        {
            QStringList errorMessageList;

            if(ui->leSymbol->text().simplified().isEmpty()) {
                errorMessageList << tr("Symbol cannot be empty!");
            } else if(!ui->leSymbol->hasAcceptableInput()) {
                errorMessageList << tr("Symbol is invalid!");
            }

            if(Util::BUY == ui->cbOperationType->currentData().toInt())
            {
                if(ui->leName->text().simplified().isEmpty()) {
                    errorMessageList << tr("Stock name cannot be empty!");
                } else if(!ui->leName->hasAcceptableInput()) {
                    errorMessageList << tr("Stock name is invalid!");
                }
            }

            if(ui->dsbPrice->text().simplified().isEmpty()) {
                errorMessageList << tr("Price cannot be empty!");
            } else if(!ui->dsbPrice->hasAcceptableInput()) {
                errorMessageList << tr("Price is invalid!");
            } else if(Util::doubleEquality6DecPoints(ui->dsbPrice->value(), 0.0)) {
                errorMessageList << tr("Price cannot be 0!");
            } else if(ui->sbCount->text().simplified().isEmpty()) {
                errorMessageList << tr("Count cannot be empty!");
            } else if(!ui->sbCount->hasAcceptableInput()) {
                errorMessageList << tr("Count is invalid!");
            } else if(ui->sbCount->value() == 0) {
                errorMessageList << tr("Count cannot be 0!");
            } else if(ui->dsbCommissionRate->text().simplified().isEmpty()) {
                errorMessageList << tr("Commission rate cannot be empty!");
            } else if(!ui->dsbCommissionRate->hasAcceptableInput()) {
                errorMessageList << tr("Commission rate is invalid!");
            } else if(Util::doubleEquality6DecPoints(ui->dsbCommissionRate->value(), 0.0)) {
                errorMessageList << tr("Commission rate cannot be 0!");
            } else if(ui->dteDateTime->text().simplified().isEmpty()) {
                errorMessageList << tr("Operation datetime cannot be empty!");
            } else if(!ui->dteDateTime->hasAcceptableInput()) {
                errorMessageList << tr("Operation datetime is invalid!");
            }

            //If it is a buy operation, check the validity of goal price.
            if(Util::BUY == ui->cbOperationType->currentData().toInt())
            {
                if(!ui->dsbGoalPrice->text().simplified().isEmpty() && !ui->dsbGoalPrice->hasAcceptableInput()) {
                    errorMessageList << tr("Goal price is invalid!");
                }
            }

            transaction = StockTransaction(static_cast<Util::Operation>(ui->cbOperationType->currentData().toInt()),
                                           static_cast<Util::StockMarket>(ui->cbMarket->currentData().toInt()),
                                           ui->leSymbol->text(),
                                           ui->leName->text(),
                                           ui->dsbPrice->value(),
                                           ui->sbCount->value(),
                                           ui->dsbCommissionRate->value(),
                                           ui->dteDateTime->dateTime(),
                                           ui->dsbGoalPrice->value());

            //If there is an error, warn the user.
            if(!errorMessageList.isEmpty())
            {
                statusBar.showMessage(errorMessageList.at(0), 3000);
                return;
            }

            //Passed the validation
            QDialog::accept();
        }

    }

}