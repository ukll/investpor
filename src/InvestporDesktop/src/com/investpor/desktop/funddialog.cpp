#include "desktop/funddialog.h"
#include "ui_funddialog.h"

#include "lib/util.h"

using lib::Util;

namespace desktop {

    FundDialog::FundDialog(QWidget *parent) :
        QDialog(parent), m_ui(new Ui::FundDialog)
    {
        m_ui->setupUi(this);
        setWindowTitle(tr("Fund Transaction"));
        m_ui->vlStatusBar->addWidget(&m_statusBar);
        m_fundCodeValidator.setRegularExpression(Util::getFundCodeRegularExpression());
        m_ui->leCode->setValidator(&m_fundCodeValidator);
        m_fundNameValidator.setRegularExpression(Util::getFundNameRegularExpression());
        m_ui->leName->setValidator(&m_fundNameValidator);

        for(int i = Util::BUY, cbOpIndex = 0; i <= Util::SELL; ++i, ++cbOpIndex)
        {
            m_ui->cbOperationType->addItem(Util::getOperationName(static_cast<Util::Operation>(i)));
            m_ui->cbOperationType->setItemData(cbOpIndex, i);
        }

        connect(m_ui->cbOperationType, SIGNAL(currentIndexChanged(int)), this, SLOT(rearrangeDialog()));
        connect(m_ui->deOrderDate, &QDateEdit::dateChanged, m_ui->deOperationDate, &QDateEdit::setMinimumDate);
        connect(m_ui->bbTransactionApproval, &QDialogButtonBox::accepted, this, &FundDialog::accept);
    }

    FundDialog::~FundDialog()
    {
        delete m_ui;
    }

    void FundDialog::rearrangeDialog()
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

    void FundDialog::accept()
    {
        QStringList errorMessageList;

        if(m_ui->leCode->text().simplified().isEmpty()) {
            errorMessageList << tr("Fund code cannot be empty!");
        } else if(!m_ui->leCode->hasAcceptableInput()) {
            errorMessageList << tr("Fund code is invalid!");
        }

        if(Util::BUY == m_ui->cbOperationType->currentData().toInt()) {
            if(m_ui->leName->text().simplified().isEmpty()) {
                errorMessageList << tr("Fund name cannot be empty!");
            } else if(!m_ui->leName->hasAcceptableInput()) {
                errorMessageList << tr("Fund name is invalid!");
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
        } else if(m_ui->deOrderDate->text().simplified().isEmpty()) {
            errorMessageList << tr("Order date cannot be empty!");
        } else if(!m_ui->deOrderDate->hasAcceptableInput()) {
            errorMessageList << tr("Order date is invalid!");
        } else if(m_ui->deOperationDate->text().simplified().isEmpty()) {
            errorMessageList << tr("Operation date cannot be empty!");
        } else if(!m_ui->deOperationDate->hasAcceptableInput()) {
            errorMessageList << tr("Operation date is invalid!");
        }

        //If it is a buy operation, check the validity of goal price.
        if(Util::BUY == m_ui->cbOperationType->currentData().toInt())
        {
            if(!m_ui->dsbGoalPrice->text().simplified().isEmpty() && !m_ui->dsbGoalPrice->hasAcceptableInput()) {
                errorMessageList << tr("Goal price is invalid!");
            }
        }

        //If there is an error, warn the user.
        if(!errorMessageList.isEmpty())
        {
            m_statusBar.showMessage(errorMessageList.at(0), 3000);
            return;
        }

        m_transaction = FundTransaction(static_cast<Util::Operation>(m_ui->cbOperationType->currentData().toInt()),
                                        m_ui->leCode->text().simplified(),
                                        m_ui->leName->text().simplified(),
                                        m_ui->dsbPrice->value(),
                                        m_ui->sbCount->value(),
                                        m_ui->deOrderDate->date(),
                                        m_ui->deOperationDate->date(),
                                        m_ui->dsbGoalPrice->value());

        //Passed the validation
        QDialog::accept();
    }

}
