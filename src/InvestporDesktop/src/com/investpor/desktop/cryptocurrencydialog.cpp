#include "desktop/cryptocurrencydialog.h"
#include "ui_cryptocurrencydialog.h"

#include "lib/util.h"
#include "lib/cryptocurrencytransaction.h"

using lib::Util;
using lib::CryptocurrencyTransaction;

namespace desktop {

    CryptocurrencyDialog::CryptocurrencyDialog(QWidget *parent) :
        QDialog(parent), m_ui(new Ui::CryptocurrencyDialog)
    {
        m_ui->setupUi(this);
        setWindowTitle(tr("Cryptocurrency Transaction"));
        m_ui->vlStatusBar->addWidget(&m_statusBar);

        //Fill operation combo box
        for(int i = Util::BUY, cbOpIndex = 0; i <= Util::SELL; ++i, ++cbOpIndex)
        {
            m_ui->cbOperationType->addItem(Util::getOperationName(static_cast<Util::Operation>(i)));
            m_ui->cbOperationType->setItemData(cbOpIndex, i);
        }

        //Fill cryptocurrency combo box
        for(int i = Util::BCH, cbCryptIndex = 0; i <= Util::XRP; ++i, ++cbCryptIndex)
        {
            m_ui->cbCryptocurrency->addItem(QString("%1 - %2")
                                            .arg(QVariant::fromValue(static_cast<Util::Currency>(i)).toString().toUpper())
                                            .arg(Util::getCurrencyName(static_cast<Util::Currency>(i))));
            m_ui->cbCryptocurrency->setItemData(cbCryptIndex, i);
        }

        //Fill base currency combo box
        for(int i = Util::ARS, cbBaseCurIndex = 0; i <= Util::ZAR; ++i, ++cbBaseCurIndex)
        {
            m_ui->cbBaseCurrency->addItem(QString("%1 - %2")
                                          .arg(QVariant::fromValue(static_cast<Util::Currency>(i)).toString().toUpper())
                                          .arg(Util::getCurrencyName(static_cast<Util::Currency>(i))));
            m_ui->cbBaseCurrency->setItemData(cbBaseCurIndex, i);
        }

        m_ui->dteDateTime->setDate(QDate::currentDate());

        connect(m_ui->cbOperationType, SIGNAL(currentIndexChanged(int)), this, SLOT(rearrangeDialog()));
        connect(m_ui->bbTransactionApproval, &QDialogButtonBox::accepted, this, &CryptocurrencyDialog::accept);
    }

    CryptocurrencyDialog::~CryptocurrencyDialog()
    {
        delete m_ui;
    }

    void CryptocurrencyDialog::accept()
    {
        QStringList errorMessageList;

        if(m_ui->dsbAmount->text().simplified().isEmpty()) {
            errorMessageList << tr("Amount cannot be empty!");
        } else if(!m_ui->dsbAmount->hasAcceptableInput()) {
            errorMessageList << tr("Amount is invalid!");
        } else if(Util::checkDoubleEqualityIn10DecPoints(m_ui->dsbAmount->value(), 0.0)) {
            errorMessageList << tr("Amount cannot be 0!");
        } else if(m_ui->dsbPrice->text().simplified().isEmpty()) {
            errorMessageList << tr("Price cannot be empty!");
        } else if(!m_ui->dsbPrice->hasAcceptableInput()) {
            errorMessageList << tr("Price is invalid!");
        } else if(Util::checkDoubleEqualityIn6DecPoints(m_ui->dsbPrice->value(), 0.0)) {
            errorMessageList << tr("Price cannot be 0!");
        } else if(!m_ui->dsbExtraExpenses->hasAcceptableInput()) {
            errorMessageList << tr("Extra expense is not valid!");
        } else if(m_ui->dteDateTime->text().simplified().isEmpty()) {
            errorMessageList << tr("Operation datetime cannot be emtpy!");
        } else if(!m_ui->dteDateTime->hasAcceptableInput()) {
            errorMessageList << tr("Operation datetime is not valid!");
        }

        //Check goal price validity if it is a buy operation.
        if(Util::BUY == m_ui->cbOperationType->currentData().toInt())
        {
            if(m_ui->dsbGoalPrice->text().simplified().isEmpty()) {
                errorMessageList << tr("Goal price cannot be empty!");
            } else if(!m_ui->dsbGoalPrice->hasAcceptableInput()) {
                errorMessageList << tr("Goal price is invalid!");
            }
        }

        //If there is an error, warn the user.
        if(!errorMessageList.isEmpty())
        {
            m_statusBar.showMessage(errorMessageList.at(0), 3000);
            return;
        }

        m_transaction.setOperationType(static_cast<Util::Operation>(m_ui->cbOperationType->currentData().toInt()));
        m_transaction.setCryptocurrency(static_cast<Util::Currency>(m_ui->cbCryptocurrency->currentData().toInt()));
        m_transaction.setAmount(m_ui->dsbAmount->value());
        m_transaction.setBaseCurrency(static_cast<Util::Currency>(m_ui->cbBaseCurrency->currentData().toInt()));
        m_transaction.setPrice(m_ui->dsbPrice->value());
        m_transaction.setExtraExpenses(m_ui->dsbExtraExpenses->value());
        m_transaction.setOperationDateTime(m_ui->dteDateTime->dateTime());
        m_transaction.setGoalPrice(m_ui->dsbGoalPrice->value());

        //Values are valid.
        QDialog::accept();
    }

    void CryptocurrencyDialog::rearrangeDialog()
    {
        if(Util::BUY == m_ui->cbOperationType->currentData().toInt()) {
            m_ui->lblGoalPrice->setVisible(true);
            m_ui->dsbGoalPrice->setVisible(true);
        } else {
            m_ui->lblGoalPrice->setVisible(false);
            m_ui->dsbGoalPrice->setVisible(false);
        }
    }

}
