#include "investpor/gui/exchangedialog.h"
#include "ui_exchangedialog.h"

#include "investpor/core/util.h"
#include "investpor/core/exchangetransaction.h"

using investpor::core::Util;

namespace investpor {

    namespace gui {

        ExchangeDialog::ExchangeDialog(QWidget *parent) :
            QDialog(parent), ui(new Ui::ExchangeDialog)
        {
            ui->setupUi(this);
            setWindowTitle(tr("Exchange Transaction"));
            ui->vlStatusBar->addWidget(&statusBar);

            for(int i = Util::BUY, cbOpIndex = 0; i <= Util::SELL; ++i, ++cbOpIndex)
            {
                ui->cbOperationType->addItem(Util::operationName(static_cast<Util::Operation>(i)));
                ui->cbOperationType->setItemData(cbOpIndex, i);
            }

            for(uint i = Util::ARS, cbCurrencyIndex = 0; i <= Util::ZAR; ++i, ++cbCurrencyIndex)
            {
                ui->cbCurrency->addItem(QString("%1 - %2")
                                        .arg(Util::currencySymbol(static_cast<Util::Currency>(i)).toUpper())
                                        .arg(Util::currencyName(static_cast<Util::Currency>(i))));
                ui->cbCurrency->setItemData(cbCurrencyIndex, i);
            }

            connect(ui->cbOperationType, SIGNAL(currentIndexChanged(int)), this, SLOT(rearrangeDialog()));
            connect(ui->bbTransactionApproval, &QDialogButtonBox::accepted, this, &ExchangeDialog::accept);
        }

        ExchangeDialog::~ExchangeDialog()
        {
            delete ui;
        }

        void ExchangeDialog::rearrangeDialog()
        {
            if(Util::BUY == ui->cbOperationType->currentData().toInt()) {
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
            } else if(Util::doubleEquality6DecPoints(ui->dsbPrice->value(), 0.0)) {
                errorMessageList << tr("Price cannot be 0!");
            } else if(ui->dsbAmount->text().simplified().isEmpty()) {
                errorMessageList << tr("Amount cannot be empty!");
            } else if(!ui->dsbAmount->hasAcceptableInput()) {
                errorMessageList << tr("Amount is invalid!");
            } else if(Util::doubleEquality6DecPoints(ui->dsbAmount->value(), 0.0)) {
                errorMessageList << tr("Amount cannot be 0!");
            } else if(ui->dteDateTime->text().simplified().isEmpty()) {
                errorMessageList << tr("Operation datetime cannot be empty!");
            } else if(!ui->dteDateTime->hasAcceptableInput()) {
                errorMessageList << tr("Operation datetime is invalid!");
            }

            if(Util::BUY == ui->cbOperationType->currentData().toInt())
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

            transaction = ExchangeTransaction(static_cast<Util::Operation>(ui->cbOperationType->currentData().toInt()),
                                              static_cast<Util::Currency>(ui->cbCurrency->currentData().toInt()),
                                              ui->dsbPrice->value(),
                                              ui->dsbAmount->value(),
                                              ui->dteDateTime->dateTime(),
                                              ui->dsbGoalPrice->value());

            //Passed the validation.
            QDialog::accept();
        }
    }

}
