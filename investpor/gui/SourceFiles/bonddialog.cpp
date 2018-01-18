#include "../HeaderFiles/bonddialog.h"
#include "ui_bonddialog.h"

#include "../../core/HeaderFiles/types.h"
#include "../../core/HeaderFiles/util.h"

using investpor::core::Operation;
using investpor::core::Util;

namespace investpor {

    namespace gui {

        BondDialog::BondDialog(QWidget *parent) :
            QDialog(parent),
            ui(new Ui::BondDialog)
        {
            ui->setupUi(this);
            ui->cbOperationType->addItem(Util::operationName(Operation::BUY));
            ui->cbOperationType->addItem(Util::operationName(Operation::SELL));

            QObject::connect(ui->cbOperationType, QOverload<int>::of(&QComboBox::currentIndexChanged),
                             [this](int index){ rearrangeDialog(index); });
            QObject::connect(ui->deTerm, &QDateEdit::dateChanged, ui->deDate, &QDateEdit::setMaximumDate);
        }

        BondDialog::~BondDialog()
        {
            delete ui;
        }

        void BondDialog::rearrangeDialog(int index)
        {
            if(index == Operation::BUY) {
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

    }

}
