#include "../HeaderFiles/cryptocurrencydialog.h"
#include "ui_cryptocurrencydialog.h"

#include "../../core/HeaderFiles/types.h"
#include "../../core/HeaderFiles/util.h"

using investpor::core::Operation;
using investpor::core::Cryptocurrency;
using investpor::core::Util;

namespace investpor {

    namespace gui {

        CryptocurrencyDialog::CryptocurrencyDialog(QWidget *parent) :
            QDialog(parent),
            ui(new Ui::CryptocurrencyDialog)
        {
            ui->setupUi(this);
            ui->cbOperationType->addItem(Util::operationName(Operation::BUY));
            ui->cbOperationType->addItem(Util::operationName(Operation::SELL));

            for(int i = Cryptocurrency::ETC; i <= Cryptocurrency::XRP; ++i)
            {
                ui->cbCryptocurrency->addItem(QString("%1 - %2").arg(Util::cryptoCurrencySymbol(static_cast<Cryptocurrency>(i)).toUpper())
                                              .arg(Util::cryptoCurrencyName(static_cast<Cryptocurrency>(i)))
                                              );
            }

            QObject::connect(ui->cbOperationType, QOverload<int>::of(&QComboBox::currentIndexChanged),
                             [this](int index){ rearrangeDialog(index); });
        }

        CryptocurrencyDialog::~CryptocurrencyDialog()
        {
            delete ui;
        }

        void CryptocurrencyDialog::rearrangeDialog(int index)
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
