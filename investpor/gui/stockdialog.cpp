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
            setWindowTitle(QString("%1 v%2 - Stock Transaction").arg(qApp->applicationName()).arg(qApp->applicationVersion()));
            ui->vlStatusBar->addWidget(&statusBar);
            symbolValidator.setRegExp(Util::stockSymbolRegExp());
            ui->leSymbol->setValidator(&symbolValidator);
            nameValidator.setRegExp(Util::stockNameRegExp());
            ui->leName->setValidator(&nameValidator);
            ui->cbOperationType->addItem(Util::operationName(Operation::BUY));
            ui->cbOperationType->addItem(Util::operationName(Operation::SELL));

            for(uint i = StockMarket::BIST; i <= StockMarket::NYSE; ++i)
            {
                ui->cbMarket->addItem(QString("%1 - %2").arg(Util::stockMarketSymbol(static_cast<StockMarket>(i))).toUpper()
                                      .arg(Util::stockMarketName(static_cast<StockMarket>(i))));
            }

            QObject::connect(ui->cbOperationType, QOverload<int>::of(&QComboBox::currentIndexChanged),
                             [this](int index){ rearrangeDialog(index); });
            QObject::connect(ui->bbTransactionApproval, &QDialogButtonBox::accepted, this, &StockDialog::accept);
        }

        StockDialog::~StockDialog()
        {
            delete ui;
        }

        void StockDialog::rearrangeDialog(int &index)
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

        void StockDialog::accept()
        {
            QStringList errorMessageList;

            if(ui->leSymbol->text().simplified().isEmpty()) {
                errorMessageList << tr("Symbol cannot be empty!");
            } else if(!ui->leSymbol->hasAcceptableInput()) {
                errorMessageList << tr("Symbol is invalid!");
            }

            if(ui->cbOperationType->currentIndex() == Operation::BUY)
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
            } else if(Util::doublesEqual(ui->dsbPrice->value(), 0.0)) {
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
            } else if(Util::doublesEqual(ui->dsbCommissionRate->value(), 0.0)) {
                errorMessageList << tr("Commission rate cannot be 0!");
            } else if(ui->dteDateTime->text().simplified().isEmpty()) {
                errorMessageList << tr("Operation datetime cannot be empty!");
            } else if(!ui->dteDateTime->hasAcceptableInput()) {
                errorMessageList << tr("Operation datetime is invalid!");
            }

            //If it is a buy operation, check the validity of goal price.
            if(ui->cbOperationType->currentIndex() == Operation::BUY)
            {
                if(!ui->dsbGoalPrice->text().simplified().isEmpty() && !ui->dsbGoalPrice->hasAcceptableInput()) {
                    errorMessageList << tr("Goal price is invalid!");
                }
            }

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
