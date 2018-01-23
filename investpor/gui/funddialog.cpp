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
            ui->cbOperationType->addItem(Util::operationName(Operation::BUY));
            ui->cbOperationType->addItem(Util::operationName(Operation::SELL));

            QObject::connect(ui->cbOperationType, QOverload<int>::of(&QComboBox::currentIndexChanged),
                             [this](int index){ rearrangeDialog(index); });
            QObject::connect(ui->deOrderDate, &QDateEdit::dateChanged, ui->deOperationDate, &QDateEdit::setMinimumDate);
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

    }

}
