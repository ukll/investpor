#include "desktop/stockdialog.h"
#include "ui_stockdialog.h"

#include "lib/util.h"

using lib::Util;

namespace desktop {

    StockDialog::StockDialog(QWidget *parent) :
        QDialog(parent),
        m_ui(new Ui::StockDialog)
    {
        m_ui->setupUi(this);
        setWindowTitle(tr("Stock Transaction"));
        m_ui->vlStatusBar->addWidget(&m_statusBar);
        m_symbolValidator.setRegularExpression(Util::getStockSymbolRegularExpression());
        m_ui->leSymbol->setValidator(&m_symbolValidator);
        m_nameValidator.setRegularExpression(Util::getStockNameRegularExpression());
        m_ui->leName->setValidator(&m_nameValidator);

        for(int i = Util::BUY, cbOpIndex = 0; i <= Util::SELL; ++i, ++cbOpIndex)
        {
            m_ui->cbOperationType->addItem(Util::getOperationName(static_cast<Util::Operation>(i)));
            m_ui->cbOperationType->setItemData(cbOpIndex, i);
        }

        for(uint i = Util::BMEX, cbStockMarketIndex = 0; i <= Util::XTSE; ++i, ++cbStockMarketIndex)
        {
            m_ui->cbMarket->addItem(QString("%1 - %2")
                                    .arg(QVariant::fromValue(static_cast<Util::StockMarket>(i)).toString())
                                    .arg(Util::getStockMarketName(static_cast<Util::StockMarket>(i))));
            m_ui->cbMarket->setItemData(cbStockMarketIndex, i);
        }

        connect(m_ui->cbOperationType, SIGNAL(currentIndexChanged(int)), this, SLOT(rearrangeDialog()));
        connect(m_ui->bbTransactionApproval, &QDialogButtonBox::accepted, this, &StockDialog::accept);
    }

    StockDialog::~StockDialog()
    {
        delete m_ui;
    }

    void StockDialog::rearrangeDialog()
    {
        if(Util::BUY == m_ui->cbOperationType->currentData().toInt()) {
            m_ui->lblName->setVisible(true);
            m_ui->leName->setVisible(true);
            m_ui->lblGoalPrice->setVisible(true);
            m_ui->dsbGoalPrice->setVisible(true);
        } else {
            m_ui->lblName->setVisible(false);
            m_ui->leName->setVisible(false);
            m_ui->lblGoalPrice->setVisible(false);
            m_ui->dsbGoalPrice->setVisible(false);
        }
    }

    void StockDialog::accept()
    {
        QStringList errorMessageList;

        if(m_ui->leSymbol->text().simplified().isEmpty()) {
            errorMessageList << tr("Symbol cannot be empty!");
        } else if(!m_ui->leSymbol->hasAcceptableInput()) {
            errorMessageList << tr("Symbol is invalid!");
        }

        if(Util::BUY == m_ui->cbOperationType->currentData().toInt())
        {
            if(m_ui->leName->text().simplified().isEmpty()) {
                errorMessageList << tr("Stock name cannot be empty!");
            } else if(!m_ui->leName->hasAcceptableInput()) {
                errorMessageList << tr("Stock name is invalid!");
            }
        }

        if(m_ui->dsbPrice->text().simplified().isEmpty()) {
            errorMessageList << tr("Price cannot be empty!");
        } else if(!m_ui->dsbPrice->hasAcceptableInput()) {
            errorMessageList << tr("Price is invalid!");
        } else if(Util::checkDoubleEqualityIn6DecPoints(m_ui->dsbPrice->value(), 0.0)) {
            errorMessageList << tr("Price cannot be 0!");
        } else if(m_ui->sbCount->text().simplified().isEmpty()) {
            errorMessageList << tr("Count cannot be empty!");
        } else if(!m_ui->sbCount->hasAcceptableInput()) {
            errorMessageList << tr("Count is invalid!");
        } else if(m_ui->sbCount->value() == 0) {
            errorMessageList << tr("Count cannot be 0!");
        } else if(m_ui->dsbCommissionRate->text().simplified().isEmpty()) {
            errorMessageList << tr("Commission rate cannot be empty!");
        } else if(!m_ui->dsbCommissionRate->hasAcceptableInput()) {
            errorMessageList << tr("Commission rate is invalid!");
        } else if(Util::checkDoubleEqualityIn6DecPoints(m_ui->dsbCommissionRate->value(), 0.0)) {
            errorMessageList << tr("Commission rate cannot be 0!");
        } else if(m_ui->dteDateTime->text().simplified().isEmpty()) {
            errorMessageList << tr("Operation datetime cannot be empty!");
        } else if(!m_ui->dteDateTime->hasAcceptableInput()) {
            errorMessageList << tr("Operation datetime is invalid!");
        }

        //If it is a buy operation, check the validity of goal price.
        if(Util::BUY == m_ui->cbOperationType->currentData().toInt())
        {
            if(!m_ui->dsbGoalPrice->text().simplified().isEmpty() && !m_ui->dsbGoalPrice->hasAcceptableInput()) {
                errorMessageList << tr("Goal price is invalid!");
            }
        }

        m_transaction = StockTransaction(static_cast<Util::Operation>(m_ui->cbOperationType->currentData().toInt()),
                                         static_cast<Util::StockMarket>(m_ui->cbMarket->currentData().toInt()),
                                         m_ui->leSymbol->text(),
                                         m_ui->leName->text(),
                                         m_ui->dsbPrice->value(),
                                         m_ui->sbCount->value(),
                                         m_ui->dsbCommissionRate->value(),
                                         m_ui->dteDateTime->dateTime(),
                                         m_ui->dsbGoalPrice->value());

        //If there is an error, warn the user.
        if(!errorMessageList.isEmpty())
        {
            m_statusBar.showMessage(errorMessageList.at(0), 3000);
            return;
        }

        //Passed the validation
        QDialog::accept();
    }

}
