#include "investpor/gui/HeaderFiles/exchangedialog.h"
#include "ui_exchangedialog.h"

#include "investpor/core/HeaderFiles/types.h"
#include "investpor/core/HeaderFiles/util.h"
#include "investpor/core/HeaderFiles/exchangetransaction.h"

using investpor::core::Currency;
using investpor::core::Operation;
using investpor::core::Util;

namespace investpor {

    namespace gui {

        ExchangeDialog::ExchangeDialog(QWidget *parent) :
            QDialog(parent),
            ui(new Ui::ExchangeDialog)
        {
            ui->setupUi(this);
            ui->vlStatusBar->addWidget(&statusBar);
            ui->cbOperationType->addItem(Util::operationName(Operation::BUY));
            ui->cbOperationType->addItem(Util::operationName(Operation::SELL));

            for(uint i = Currency::AUD; i <= Currency::USD; ++i)
            {
                ui->cbCurrency->addItem(QString("%1 - %2").arg(Util::currencySymbol(static_cast<Currency>(i)).toUpper())
                                        .arg(Util::currencyName(static_cast<Currency>(i))));
            }

            QObject::connect(ui->cbOperationType, QOverload<int>::of(&QComboBox::currentIndexChanged),
                             [this](int index){ rearrangeDialog(index); });
            QObject::connect(ui->bbTransactionApproval, &QDialogButtonBox::accepted, this, &ExchangeDialog::accept);
        }

        ExchangeDialog::~ExchangeDialog()
        {
            delete ui;
        }

        ExchangeTransaction ExchangeDialog::getTransaction()
        {
            return transaction;
        }

        void ExchangeDialog::rearrangeDialog(int index)
        {
            if(Operation::BUY == index) {
                ui->lblGoalPrice->setVisible(true);
                ui->dsbGoalPrice->setVisible(true);
            } else {
                ui->lblGoalPrice->setVisible(false);
                ui->dsbGoalPrice->setVisible(false);
            }
        }

        void ExchangeDialog::accept()
        {
            QStringList errorMessageList;

            if(ui->dsbPrice->text().simplified().isEmpty()) {
                errorMessageList << tr("Price cannot be empty!");
            } else if(!ui->dsbPrice->hasAcceptableInput()) {
                errorMessageList << tr("Price is invalid!");
            } else if(Util::doublesEqual(ui->dsbPrice->value(), 0.0)) {
                errorMessageList << tr("Price cannot be 0!");
            } else if(ui->dsbAmount->text().simplified().isEmpty()) {
                errorMessageList << tr("Amount cannot be empty!");
            } else if(!ui->dsbAmount->hasAcceptableInput()) {
                errorMessageList << tr("Amount is invalid!");
            } else if(Util::doublesEqual(ui->dsbAmount->value(), 0.0)) {
                errorMessageList << tr("Amount cannot be 0!");
            } else if(ui->dteDateTime->text().simplified().isEmpty()) {
                errorMessageList << tr("Operation datetime cannot be empty!");
            } else if(!ui->dteDateTime->hasAcceptableInput()) {
                errorMessageList << tr("Operation datetime is invalid!");
            }

            if(Operation::BUY == ui->cbOperationType->currentIndex())
            {
                if(ui->dsbGoalPrice->text().simplified().isEmpty()) {
                    errorMessageList << tr("Goal price cannot be empty!");
                } else if(!ui->dsbGoalPrice->hasAcceptableInput()) {
                    errorMessageList << tr("Goal price is invalid!");
                }
            }

            if(!errorMessageList.isEmpty())
            {
                statusBar.showMessage(errorMessageList.at(0), 3000);
                return;
            }

            transaction = ExchangeTransaction(static_cast<Operation>(ui->cbOperationType->currentIndex()),
                                              static_cast<Currency>(ui->cbCurrency->currentIndex()),
                                              ui->dsbPrice->value(), ui->dsbAmount->value(), ui->dteDateTime->dateTime(),
                                              ui->dsbGoalPrice->value());

            //Passed the validation.
            QDialog::accept();
        }
    }

}
