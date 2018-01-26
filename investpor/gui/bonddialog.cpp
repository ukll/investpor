#include "investpor/gui/bonddialog.h"
#include "ui_bonddialog.h"

#include "investpor/core/types.h"
#include "investpor/core/util.h"
#include "investpor/core/discountbondtransaction.h"

#include <QStatusBar>

using investpor::core::Operation;
using investpor::core::Util;
using investpor::core::DiscountBondTransaction;

namespace investpor {

    namespace gui {

        BondDialog::BondDialog(QWidget *parent) :
            QDialog(parent),
            ui(new Ui::BondDialog)
        {
            ui->setupUi(this);
            ui->vlStatusBar->addWidget(&statusBar);
            ISINValidator.setRegExp(Util::bondISINRegExp());
            ui->leISINCode->setValidator(&ISINValidator);
            ui->cbOperationType->addItem(Util::operationName(Operation::BUY));
            ui->cbOperationType->addItem(Util::operationName(Operation::SELL));

            QObject::connect(ui->cbOperationType, QOverload<int>::of(&QComboBox::currentIndexChanged),
                             [this](int index){ rearrangeDialog(index); });
            QObject::connect(ui->deTerm, &QDateEdit::dateChanged, ui->deDate, &QDateEdit::setMaximumDate);

            QObject::connect(ui->bbTransactionApproval, &QDialogButtonBox::accepted, this, &BondDialog::accept);
        }

        BondDialog::~BondDialog()
        {
            delete ui;
        }

        void BondDialog::rearrangeDialog(int &index)
        {
            if(Operation::BUY == index) {
                ui->lblTerm->setVisible(true);
                ui->deTerm->setVisible(true);
                ui->lblNominalValue->setVisible(true);
                ui->dsbNominalValue->setVisible(true);
            } else {
                ui->lblTerm->setVisible(false);
                ui->deTerm->setVisible(false);
                ui->lblNominalValue->setVisible(false);
                ui->dsbNominalValue->setVisible(false);
            }
        }

        void BondDialog::accept()
        {
            QStringList errorMessageList;

            if(ui->leISINCode->text().simplified().isEmpty()) {
                errorMessageList << tr("ISIN code cannot be empty!");
            } else if(!ui->leISINCode->hasAcceptableInput()) {
                errorMessageList << tr("ISIN code is not valid!");
            }

            if(Operation::BUY == ui->cbOperationType->currentIndex()) {
                //If it is a BUY transacton, validate term and nominal value too.
                if(ui->deTerm->text().simplified().isEmpty()) {
                    errorMessageList << tr("Term date cannot be empty!");
                } else if(!ui->deTerm->hasAcceptableInput()) {
                    errorMessageList << tr("Term date is not valid!");
                } else if(ui->dsbNominalValue->text().simplified().isEmpty()) {
                    errorMessageList << tr("Nominal value cannot be empty!");
                } else if(!ui->dsbNominalValue->hasAcceptableInput()) {
                    errorMessageList << tr("Nominal value is not valid!");
                } else if(Util::doublesEqual(ui->dsbNominalValue->value(), 0.0)) {
                    errorMessageList << tr("Nominal value cannot be 0!");
                }
            }

            if(ui->dsbSalePrice->text().simplified().isEmpty()) {
                errorMessageList << tr("Sale price cannot be empty!");
            } else if(!ui->dsbSalePrice->hasAcceptableInput()) {
                errorMessageList << tr("Sale price is not valid!");
            } else if(Util::doublesEqual(ui->dsbSalePrice->value(), 0.0)) {
                errorMessageList << tr("Sale price cannot be 0!");
            } else if(ui->deDate->text().simplified().isEmpty()) {
                errorMessageList << tr("Operation date cannot be empty!");
            } else if(!ui->deDate->hasAcceptableInput()) {
                errorMessageList << tr("Operation date is not valid!");
            }

            //If there is an error, warn the user.
            if(!errorMessageList.isEmpty())
            {
                statusBar.showMessage(errorMessageList.at(0), 3000);
                return;
            }

            transaction = DiscountBondTransaction(static_cast<Operation>(ui->cbOperationType->currentIndex()),
                                                  ui->leISINCode->text(), ui->deTerm->date(), ui->dsbNominalValue->value(),
                                                  ui->dsbSalePrice->value(), ui->deDate->date());
            //Passed the validation
            QDialog::accept();
        }

    }

}
