#include "desktop/exchangedialog.h"
#include "ui_exchangedialog.h"

#include "lib/util.h"
#include "lib/exchangetransaction.h"

using lib::Util;

namespace desktop {

    ExchangeDialog::ExchangeDialog(QWidget *parent) :
        QDialog(parent), m_ui(new Ui::ExchangeDialog)
    {
        m_ui->setupUi(this);
        setWindowTitle(tr("Exchange Transaction"));
        m_ui->vlStatusBar->addWidget(&m_statusBar);

        for(int i = Util::BUY, cbOpIndex = 0; i <= Util::SELL; ++i, ++cbOpIndex)
        {
            m_ui->cbOperationType->addItem(Util::getOperationName(static_cast<Util::Operation>(i)));
            m_ui->cbOperationType->setItemData(cbOpIndex, i);
        }

        for(uint i = Util::ARS, cbCurrencyIndex = 0; i <= Util::ZAR; ++i, ++cbCurrencyIndex)
        {
            m_ui->cbCurrency->addItem(QString("%1 - %2")
                                      .arg(QVariant::fromValue(static_cast<Util::Currency>(i)).toString().toUpper())
                                      .arg(Util::getCurrencyName(static_cast<Util::Currency>(i))));
            m_ui->cbCurrency->setItemData(cbCurrencyIndex, i);
        }

        connect(m_ui->cbOperationType, SIGNAL(currentIndexChanged(int)), this, SLOT(rearrangeDialog()));
        connect(m_ui->bbTransactionApproval, &QDialogButtonBox::accepted, this, &ExchangeDialog::accept);
    }

    ExchangeDialog::~ExchangeDialog()
    {
        delete m_ui;
    }

    void ExchangeDialog::rearrangeDialog()
    {
        if(Util::BUY == m_ui->cbOperationType->currentData().toInt()) {
            m_ui->lblGoalPrice->setVisible(true);
            m_ui->dsbGoalPrice->setVisible(true);
        } else {
            m_ui->lblGoalPrice->setVisible(false);
            m_ui->dsbGoalPrice->setVisible(false);
        }
    }

    void ExchangeDialog::accept()
    {
        QStringList errorMessageList;

        if(m_ui->dsbPrice->text().simplified().isEmpty()) {
            errorMessageList << tr("Price cannot be empty!");
        } else if(!m_ui->dsbPrice->hasAcceptableInput()) {
            errorMessageList << tr("Price is invalid!");
        } else if(Util::checkDoubleEqualityIn6DecPoints(m_ui->dsbPrice->value(), 0.0)) {
            errorMessageList << tr("Price cannot be 0!");
        } else if(m_ui->dsbAmount->text().simplified().isEmpty()) {
            errorMessageList << tr("Amount cannot be empty!");
        } else if(!m_ui->dsbAmount->hasAcceptableInput()) {
            errorMessageList << tr("Amount is invalid!");
        } else if(Util::checkDoubleEqualityIn6DecPoints(m_ui->dsbAmount->value(), 0.0)) {
            errorMessageList << tr("Amount cannot be 0!");
        } else if(m_ui->dteDateTime->text().simplified().isEmpty()) {
            errorMessageList << tr("Operation datetime cannot be empty!");
        } else if(!m_ui->dteDateTime->hasAcceptableInput()) {
            errorMessageList << tr("Operation datetime is invalid!");
        }

        if(Util::BUY == m_ui->cbOperationType->currentData().toInt())
        {
            if(m_ui->dsbGoalPrice->text().simplified().isEmpty()) {
                errorMessageList << tr("Goal price cannot be empty!");
            } else if(!m_ui->dsbGoalPrice->hasAcceptableInput()) {
                errorMessageList << tr("Goal price is invalid!");
            }
        }

        if(!errorMessageList.isEmpty())
        {
            m_statusBar.showMessage(errorMessageList.at(0), 3000);
            return;
        }

        m_transaction = ExchangeTransaction(static_cast<Util::Operation>(m_ui->cbOperationType->currentData().toInt()),
                                            static_cast<Util::Currency>(m_ui->cbCurrency->currentData().toInt()),
                                            m_ui->dsbPrice->value(),
                                            m_ui->dsbAmount->value(),
                                            m_ui->dteDateTime->dateTime(),
                                            m_ui->dsbGoalPrice->value());

        //Passed the validation.
        QDialog::accept();
    }

}
