#include "investpor/gui/cryptocurrencydialog.h"
#include "ui_cryptocurrencydialog.h"

#include "investpor/core/util.h"
#include "investpor/core/cryptocurrencytransaction.h"

using investpor::core::Util;
using investpor::core::CryptocurrencyTransaction;

namespace investpor {

    namespace gui {

        CryptocurrencyDialog::CryptocurrencyDialog(QWidget *parent) :
            QDialog(parent),
            ui(new Ui::CryptocurrencyDialog)
        {
            ui->setupUi(this);
            setWindowTitle(tr("Cryptocurrency Transaction"));
            ui->vlStatusBar->addWidget(&statusBar);
            ui->cbOperationType->addItem(Util::operationName(Util::BUY));
            ui->cbOperationType->addItem(Util::operationName(Util::SELL));

            for(int i = Util::BCH; i <= Util::XRP; ++i)
            {
                ui->cbCryptocurrency->addItem(QString("%1 - %2").arg(Util::currencySymbol(static_cast<Util::Currency>(i)).toUpper())
                                              .arg(Util::currencyName(static_cast<Util::Currency>(i)))
                                              );
            }

            QObject::connect(ui->cbOperationType, QOverload<int>::of(&QComboBox::currentIndexChanged),
                             [this](int index){ rearrangeDialog(++index); });

            QObject::connect(ui->bbTransactionApproval, &QDialogButtonBox::accepted, this, &CryptocurrencyDialog::accept);
        }

        CryptocurrencyDialog::~CryptocurrencyDialog()
        {
            delete ui;
        }

        void CryptocurrencyDialog::rearrangeDialog(int &operationIndex)
        {
            if(Util::BUY == operationIndex) {
                ui->lblGoalPrice->setVisible(true);
                ui->dsbGoalPrice->setVisible(true);
            } else {
                ui->lblGoalPrice->setVisible(false);
                ui->dsbGoalPrice->setVisible(false);
            }
        }

        void CryptocurrencyDialog::accept()
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
            } else if(Util::doubleEquality10DecPoints(ui->dsbAmount->value(), 0.0)) {
                errorMessageList << tr("Amount cannot be 0!");
            } else if(ui->dteDateTime->text().simplified().isEmpty()) {
                errorMessageList << tr("Operation datetime cannot be emtpy!");
            } else if(!ui->dteDateTime->hasAcceptableInput()) {
                errorMessageList << tr("Operation datetime is not valid!");
            }


            if(Util::BUY == (ui->cbOperationType->currentIndex() + 1))
            {
                if(ui->dsbGoalPrice->text().simplified().isEmpty()) {
                    errorMessageList << tr("Goal price cannot be empty!");
                } else if(!ui->dsbGoalPrice->hasAcceptableInput()) {
                    errorMessageList << tr("Goal price is invalid!");
                }
            }

            //If there is an error, warn the user.
            if(!errorMessageList.isEmpty())
            {
                statusBar.showMessage(errorMessageList.at(0), 3000);
                return;
            }

            transaction = CryptocurrencyTransaction(static_cast<Util::Operation>(ui->cbOperationType->currentIndex() + 1),
                                                    static_cast<Util::Currency>(ui->cbCryptocurrency->currentIndex() + 1),
                                                    ui->dsbPrice->value(), ui->dsbAmount->value(), ui->dteDateTime->dateTime(),
                                                    ui->dsbGoalPrice->value());

            //Values are valid.
            QDialog::accept();
        }

    }

}
