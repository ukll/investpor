#include "investpor/gui/funddialog.h"
#include "ui_funddialog.h"

#include "investpor/core/util.h"

using investpor::core::Util;

namespace investpor {

    namespace gui {

        FundDialog::FundDialog(QWidget *parent) :
            QDialog(parent), ui(new Ui::FundDialog)
        {
            ui->setupUi(this);
            setWindowTitle(tr("Fund Transaction"));
            ui->vlStatusBar->addWidget(&statusBar);
            fundCodeValidator.setRegularExpression(Util::fundCodeRegularExpression());
            ui->leCode->setValidator(&fundCodeValidator);
            fundNameValidator.setRegularExpression(Util::fundNameRegularExpression());
            ui->leName->setValidator(&fundNameValidator);

            for(int i = Util::BUY, cbOpIndex = 0; i <= Util::SELL; ++i, ++cbOpIndex)
            {
                ui->cbOperationType->addItem(Util::operationName(static_cast<Util::Operation>(i)));
                ui->cbOperationType->setItemData(cbOpIndex, i);
            }

            connect(ui->cbOperationType, SIGNAL(currentIndexChanged(int)), this, SLOT(rearrangeDialog()));
            connect(ui->deOrderDate, &QDateEdit::dateChanged, ui->deOperationDate, &QDateEdit::setMinimumDate);
            connect(ui->bbTransactionApproval, &QDialogButtonBox::accepted, this, &FundDialog::accept);
        }

        FundDialog::~FundDialog()
        {
            delete ui;
        }

        void FundDialog::rearrangeDialog()
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

        void FundDialog::accept()
        {
            QStringList errorMessageList;

            if(ui->leCode->text().simplified().isEmpty()) {
                errorMessageList << tr("Fund code cannot be empty!");
            } else if(!ui->leCode->hasAcceptableInput()) {
                errorMessageList << tr("Fund code is invalid!");
            }

            if(Util::BUY == ui->cbOperationType->currentData().toInt()) {
                if(ui->leName->text().simplified().isEmpty()) {
                    errorMessageList << tr("Fund name cannot be empty!");
                } else if(!ui->leName->hasAcceptableInput()) {
                    errorMessageList << tr("Fund name is invalid!");
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
            } else if(ui->deOrderDate->text().simplified().isEmpty()) {
                errorMessageList << tr("Order date cannot be empty!");
            } else if(!ui->deOrderDate->hasAcceptableInput()) {
                errorMessageList << tr("Order date is invalid!");
            } else if(ui->deOperationDate->text().simplified().isEmpty()) {
                errorMessageList << tr("Operation date cannot be empty!");
            } else if(!ui->deOperationDate->hasAcceptableInput()) {
                errorMessageList << tr("Operation date is invalid!");
            }

            //If it is a buy operation, check the validity of goal price.
            if(Util::BUY == ui->cbOperationType->currentData().toInt())
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

            transaction = FundTransaction(static_cast<Util::Operation>(ui->cbOperationType->currentData().toInt()),
                                          ui->leCode->text().simplified(),
                                          ui->leName->text().simplified(),
                                          ui->dsbPrice->value(),
                                          ui->sbCount->value(),
                                          ui->deOrderDate->date(),
                                          ui->deOperationDate->date(),
                                          ui->dsbGoalPrice->value());

            //Passed the validation
            QDialog::accept();
        }

    }

}
