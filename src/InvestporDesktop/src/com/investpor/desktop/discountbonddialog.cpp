#include "desktop/discountbonddialog.h"
#include "ui_discountbonddialog.h"

#include "lib/util.h"
#include "lib/discountbondtransaction.h"

#include <QStatusBar>

using lib::Util;
using lib::DiscountBondTransaction;

namespace desktop {

    DiscountBondDialog::DiscountBondDialog(QWidget *parent) :
        QDialog(parent), m_ui(new Ui::DiscountBondDialog)
    {
        m_ui->setupUi(this);
        setWindowTitle(tr("Discount Bond Transaction"));
        m_ui->vlStatusBar->addWidget(&m_statusBar);
        m_ISINValidator.setRegularExpression(Util::getISINRegularExpression());
        m_ui->leISINCode->setValidator(&m_ISINValidator);

        for(int i = Util::BUY, cbOpIndex = 0; i <= Util::SELL; ++i, ++cbOpIndex)
        {
            m_ui->cbOperationType->addItem(Util::getOperationName(static_cast<Util::Operation>(i)));
            m_ui->cbOperationType->setItemData(cbOpIndex, i);
        }

        connect(m_ui->cbOperationType, SIGNAL(currentIndexChanged(int)), this, SLOT(rearrangeDialog()));
        connect(m_ui->deTerm, &QDateEdit::dateChanged, m_ui->deDate, &QDateEdit::setMaximumDate);
        connect(m_ui->bbTransactionApproval, &QDialogButtonBox::accepted, this, &DiscountBondDialog::accept);
    }

    DiscountBondDialog::~DiscountBondDialog()
    {
        delete m_ui;
    }

    void DiscountBondDialog::rearrangeDialog()
    {
        if(Util::BUY == m_ui->cbOperationType->currentData().toInt()) {
            m_ui->lblTerm->setVisible(true);
            m_ui->deTerm->setVisible(true);
            m_ui->lblNominalValue->setVisible(true);
            m_ui->dsbNominalValue->setVisible(true);
        } else {
            m_ui->lblTerm->setVisible(false);
            m_ui->deTerm->setVisible(false);
            m_ui->lblNominalValue->setVisible(false);
            m_ui->dsbNominalValue->setVisible(false);
        }
    }

    void DiscountBondDialog::accept()
    {
        QStringList errorMessageList;

        if(m_ui->leISINCode->text().simplified().isEmpty()) {
            errorMessageList << tr("ISIN code cannot be empty!");
        } else if(!m_ui->leISINCode->hasAcceptableInput()) {
            errorMessageList << tr("ISIN code is not valid!");
        }

        if(Util::BUY == m_ui->cbOperationType->currentData().toInt()) {
            //If it is a BUY transacton, validate term and nominal value too.
            if(m_ui->deTerm->text().simplified().isEmpty()) {
                errorMessageList << tr("Term date cannot be empty!");
            } else if(!m_ui->deTerm->hasAcceptableInput()) {
                errorMessageList << tr("Term date is not valid!");
            } else if(m_ui->dsbNominalValue->text().simplified().isEmpty()) {
                errorMessageList << tr("Nominal value cannot be empty!");
            } else if(!m_ui->dsbNominalValue->hasAcceptableInput()) {
                errorMessageList << tr("Nominal value is not valid!");
            } else if(Util::checkDoubleEqualityIn6DecPoints(m_ui->dsbNominalValue->value(), 0.0)) {
                errorMessageList << tr("Nominal value cannot be 0!");
            }
        }

        if(m_ui->dsbSalePrice->text().simplified().isEmpty()) {
            errorMessageList << tr("Sale price cannot be empty!");
        } else if(!m_ui->dsbSalePrice->hasAcceptableInput()) {
            errorMessageList << tr("Sale price is not valid!");
        } else if(Util::checkDoubleEqualityIn6DecPoints(m_ui->dsbSalePrice->value(), 0.0)) {
            errorMessageList << tr("Sale price cannot be 0!");
        } else if(m_ui->sbCount->text().simplified().isEmpty()) {
            errorMessageList << tr("Count cannot be empty!");
        } else if(!m_ui->sbCount->hasAcceptableInput()) {
            errorMessageList << tr("Count is not valid!");
        } else if(m_ui->sbCount->value() == 0) {
            errorMessageList << tr("Count cannot be 0!");
        } else if(m_ui->deDate->text().simplified().isEmpty()) {
            errorMessageList << tr("Operation date cannot be empty!");
        } else if(!m_ui->deDate->hasAcceptableInput()) {
            errorMessageList << tr("Operation date is not valid!");
        }

        //If there is an error, warn the user.
        if(!errorMessageList.isEmpty())
        {
            m_statusBar.showMessage(errorMessageList.at(0), 3000);
            return;
        }

        m_transaction = DiscountBondTransaction(static_cast<Util::Operation>(m_ui->cbOperationType->currentData().toInt()),
                                                m_ui->leISINCode->text(),
                                                m_ui->deTerm->date(),
                                                m_ui->dsbNominalValue->value(),
                                                m_ui->dsbSalePrice->value(),
                                                m_ui->sbCount->value(),
                                                m_ui->deDate->date());
        //Passed the validation
        QDialog::accept();
    }

}
