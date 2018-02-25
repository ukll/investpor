#include "investpor/gui/discountbonddialog.h"
#include "ui_discountbonddialog.h"

#include "investpor/core/util.h"
#include "investpor/core/discountbondtransaction.h"

#include <QStatusBar>

using investpor::core::Util;
using investpor::core::DiscountBondTransaction;

namespace investpor {

    namespace gui {

        DiscountBondDialog::DiscountBondDialog(QWidget *parent) :
            QDialog(parent), ui(new Ui::DiscountBondDialog)
        {
            ui->setupUi(this);
            setWindowTitle(tr("Discount Bond Transaction"));
            ui->vlStatusBar->addWidget(&statusBar);
            ISINValidator.setRegularExpression(Util::bondISINRegularExpression());
            ui->leISINCode->setValidator(&ISINValidator);

            for(int i = Util::BUY, cbOpIndex = 0; i <= Util::SELL; ++i, ++cbOpIndex)
            {
                ui->cbOperationType->addItem(Util::operationName(static_cast<Util::Operation>(i)));
                ui->cbOperationType->setItemData(cbOpIndex, i);
            }

            connect(ui->cbOperationType, SIGNAL(currentIndexChanged(int)), this, SLOT(rearrangeDialog()));
            connect(ui->deTerm, &QDateEdit::dateChanged, ui->deDate, &QDateEdit::setMaximumDate);
            connect(ui->bbTransactionApproval, &QDialogButtonBox::accepted, this, &DiscountBondDialog::accept);
        }

        DiscountBondDialog::~DiscountBondDialog()
        {
            delete ui;
        }

        void DiscountBondDialog::rearrangeDialog()
        {
            if(Util::BUY == ui->cbOperationType->currentData().toInt()) {
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

        void DiscountBondDialog::accept()
        {
            QStringList errorMessageList;

            if(ui->leISINCode->text().simplified().isEmpty()) {
                errorMessageList << tr("ISIN code cannot be empty!");
            } else if(!ui->leISINCode->hasAcceptableInput()) {
                errorMessageList << tr("ISIN code is not valid!");
            }

            if(Util::BUY == ui->cbOperationType->currentData().toInt()) {
                //If it is a BUY transacton, validate term and nominal value too.
                if(ui->deTerm->text().simplified().isEmpty()) {
                    errorMessageList << tr("Term date cannot be empty!");
                } else if(!ui->deTerm->hasAcceptableInput()) {
                    errorMessageList << tr("Term date is not valid!");
                } else if(ui->dsbNominalValue->text().simplified().isEmpty()) {
                    errorMessageList << tr("Nominal value cannot be empty!");
                } else if(!ui->dsbNominalValue->hasAcceptableInput()) {
                    errorMessageList << tr("Nominal value is not valid!");
                } else if(Util::doubleEquality6DecPoints(ui->dsbNominalValue->value(), 0.0)) {
                    errorMessageList << tr("Nominal value cannot be 0!");
                }
            }

            if(ui->dsbSalePrice->text().simplified().isEmpty()) {
                errorMessageList << tr("Sale price cannot be empty!");
            } else if(!ui->dsbSalePrice->hasAcceptableInput()) {
                errorMessageList << tr("Sale price is not valid!");
            } else if(Util::doubleEquality6DecPoints(ui->dsbSalePrice->value(), 0.0)) {
                errorMessageList << tr("Sale price cannot be 0!");
            } else if(ui->sbCount->text().simplified().isEmpty()) {
                errorMessageList << tr("Count cannot be empty!");
            } else if(!ui->sbCount->hasAcceptableInput()) {
                errorMessageList << tr("Count is not valid!");
            } else if(ui->sbCount->value() == 0) {
                errorMessageList << tr("Count cannot be 0!");
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

            transaction = DiscountBondTransaction(static_cast<Util::Operation>(ui->cbOperationType->currentData().toInt()),
                                                  ui->leISINCode->text(),
                                                  ui->deTerm->date(),
                                                  ui->dsbNominalValue->value(),
                                                  ui->dsbSalePrice->value(),
                                                  ui->sbCount->value(),
                                                  ui->deDate->date());
            //Passed the validation
            QDialog::accept();
        }

    }

}
