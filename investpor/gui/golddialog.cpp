#include "investpor/gui/golddialog.h"
#include "ui_golddialog.h"

#include "investpor/core/types.h"
#include "investpor/core/util.h"

using investpor::core::Gold;
using investpor::core::Operation;
using investpor::core::Util;

namespace investpor {

    namespace gui {

        GoldDialog::GoldDialog(QWidget *parent) :
            QDialog(parent),
            ui(new Ui::GoldDialog)
        {
            ui->setupUi(this);
            setWindowTitle(tr("Gold Transaction"));
            ui->vlStatusBar->addWidget(&statusBar);
            ui->cbOperationType->addItem(Util::operationName(Operation::BUY));
            ui->cbOperationType->addItem(Util::operationName(Operation::SELL));

            for(uint i = Gold::GRAMS; i <= Gold::ONS; ++i)
            {
                ui->cbGoldType->addItem(Util::goldName(static_cast<Gold>(i)));
            }

            QObject::connect(ui->cbOperationType, QOverload<int>::of(&QComboBox::currentIndexChanged),
                             [this](int index){ rearrangeDialog(++index); });
            QObject::connect(ui->bbTransactionApproval, &QDialogButtonBox::accepted, this, &GoldDialog::accept);

        }

        GoldDialog::~GoldDialog()
        {
            delete ui;
        }

        void GoldDialog::rearrangeDialog(int &operationIndex)
        {
            if(Operation::BUY == operationIndex) {
                ui->lblGoalPrice->setVisible(true);
                ui->dsbGoalPrice->setVisible(true);
            } else {
                ui->lblGoalPrice->setVisible(false);
                ui->dsbGoalPrice->setVisible(false);
            }
        }

        void GoldDialog::accept()
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

            //If it is a buy operation, check the validity of goal price.
            if(ui->cbOperationType->currentIndex() == Operation::BUY)
            {
                if(!ui->dsbGoalPrice->text().simplified().isEmpty() && !ui->dsbGoalPrice->hasAcceptableInput())
                {
                    errorMessageList << tr("Goal price is invalid!");
                }
            }

            transaction = GoldTransaction(static_cast<Operation>(ui->cbOperationType->currentIndex() + 1),
                                          static_cast<Gold>(ui->cbGoldType->currentIndex() + 1),
                                          ui->dsbPrice->value(), ui->dsbAmount->value(),
                                          ui->dteDateTime->dateTime(), ui->dsbGoalPrice->value());

            if(!errorMessageList.isEmpty())
            {
                statusBar.showMessage(errorMessageList.at(0), 3000);
                return;
            }

            //Passed the validation.
            QDialog::accept();
        }

    }

}
