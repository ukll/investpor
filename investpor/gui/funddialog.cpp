#include "investpor/gui/funddialog.h"
#include "ui_funddialog.h"

#include "investpor/core/types.h"
#include "investpor/core/util.h"

using investpor::core::Operation;
using investpor::core::Util;

namespace investpor {

    namespace gui {

        FundDialog::FundDialog(QWidget *parent) :
            QDialog(parent),
            ui(new Ui::FundDialog)
        {
            ui->setupUi(this);
            ui->vlStatusBar->addWidget(&statusBar);
            fundCodeValidator.setRegExp(Util::fundCodeRegExp());
            ui->leCode->setValidator(&fundCodeValidator);
            fundNameValidator.setRegExp(Util::fundNameRegExp());
            ui->leName->setValidator(&fundNameValidator);
            ui->cbOperationType->addItem(Util::operationName(Operation::BUY));
            ui->cbOperationType->addItem(Util::operationName(Operation::SELL));

            QObject::connect(ui->cbOperationType, QOverload<int>::of(&QComboBox::currentIndexChanged),
                             [this](int index){ rearrangeDialog(index); });
            QObject::connect(ui->deOrderDate, &QDateEdit::dateChanged, ui->deOperationDate, &QDateEdit::setMinimumDate);
            QObject::connect(ui->bbTransactionApproval, &QDialogButtonBox::accepted, this, &FundDialog::accept);
        }

        FundDialog::~FundDialog()
        {
            delete ui;
        }

        void FundDialog::rearrangeDialog(int index)
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

        void FundDialog::accept()
        {
            QStringList errorMessageList;

            if(ui->leCode->text().simplified().isEmpty()) {
                errorMessageList << tr("Fund code cannot be empty!");
            } else if(!ui->leCode->hasAcceptableInput()) {
                errorMessageList << tr("Fund code is invalid!");
            }

            if(ui->cbOperationType->currentIndex() == Operation::BUY) {
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
            } else if(Util::doublesEqual(ui->dsbPrice->value(), 0.0)) {
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

            //Goal price cannot be invalid if it is not empty.
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

            transaction = FundTransaction(static_cast<Operation>(ui->cbOperationType->currentIndex()),
                                          ui->leCode->text().simplified(), ui->leName->text().simplified(),
                                          ui->dsbPrice->value(), static_cast<quint32>(ui->sbCount->value()),
                                          ui->deOrderDate->date(), ui->deOperationDate->date(), ui->dsbGoalPrice->value());

            //Passed the validation
            QDialog::accept();
        }

    }

}
