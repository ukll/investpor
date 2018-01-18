#include "../HeaderFiles/golddialog.h"
#include "ui_golddialog.h"

#include "../../core/HeaderFiles/types.h"
#include "../../core/HeaderFiles/util.h"

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
            ui->cbOperationType->addItem(Util::operationName(Operation::BUY));
            ui->cbOperationType->addItem(Util::operationName(Operation::SELL));

            for(uint i = Gold::GRAMS; i <= Gold::ONS; ++i)
            {
                ui->cbGoldType->addItem(Util::goldName(static_cast<Gold>(i)));
            }

            QObject::connect(ui->cbOperationType, QOverload<int>::of(&QComboBox::currentIndexChanged),
                             [this](int index){ rearrangeDialog(index); });

        }

        GoldDialog::~GoldDialog()
        {
            delete ui;
        }

        void GoldDialog::rearrangeDialog(int index)
        {
            if(Operation::BUY == index) {
                ui->lblGoalPrice->setVisible(true);
                ui->dsbGoalPrice->setVisible(true);
            } else {
                ui->lblGoalPrice->setVisible(false);
                ui->dsbGoalPrice->setVisible(false);
            }
        }

    }

}
