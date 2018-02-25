#include "investpor/gui/golddialog.h"
#include "ui_golddialog.h"

#include "investpor/core/util.h"

using investpor::core::Util;

namespace investpor {

    namespace gui {

        GoldDialog::GoldDialog(QWidget *parent) :
            QDialog(parent), ui(new Ui::GoldDialog)
        {
            ui->setupUi(this);
            setWindowTitle(tr("Gold Transaction"));
            ui->vlStatusBar->addWidget(&statusBar);

            for(int i = Util::BUY, cbOpIndex = 0; i <= Util::SELL; ++i, ++cbOpIndex)
            {
                ui->cbOperationType->addItem(Util::operationName(static_cast<Util::Operation>(i)));
                ui->cbOperationType->setItemData(cbOpIndex, i);
            }

            for(uint i = Util::GRAM, cbGoldIndex = 0; i <= Util::OUNCE; ++i, ++cbGoldIndex)
            {
                ui->cbGoldType->addItem(Util::goldName(static_cast<Util::Gold>(i)));
                ui->cbGoldType->setItemData(cbGoldIndex, i);
            }

            connect(ui->cbOperationType, SIGNAL(currentIndexChanged(int)), this, SLOT(rearrangeDialog()));
            connect(ui->bbTransactionApproval, &QDialogButtonBox::accepted, this, &GoldDialog::accept);
        }

        GoldDialog::~GoldDialog()
        {
            delete ui;
        }

        void GoldDialog::rearrangeDialog()
        {
            if(Util::BUY == ui->cbOperationType->currentData().toInt()) {
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
            if(Util::BUY == ui->cbOperationType->currentData().toInt())
            {
                if(!ui->dsbGoalPrice->text().simplified().isEmpty() && !ui->dsbGoalPrice->hasAcceptableInput())
                {
                    errorMessageList << tr("Goal price is invalid!");
                }
            }

            transaction = GoldTransaction(static_cast<Util::Operation>(ui->cbOperationType->currentData().toInt()),
                                          static_cast<Util::Gold>(ui->cbGoldType->currentData().toInt()),
                                          ui->dsbPrice->value(),
                                          ui->dsbAmount->value(),
                                          ui->dteDateTime->dateTime(),
                                          ui->dsbGoalPrice->value());

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
