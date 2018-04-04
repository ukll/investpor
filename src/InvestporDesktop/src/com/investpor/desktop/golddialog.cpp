#include "desktop/golddialog.h"
#include "ui_golddialog.h"

#include "lib/util.h"

using lib::Util;

namespace desktop {

    GoldDialog::GoldDialog(QWidget *parent) :
        QDialog(parent), m_ui(new Ui::GoldDialog)
    {
        m_ui->setupUi(this);
        setWindowTitle(tr("Gold Transaction"));
        m_ui->vlStatusBar->addWidget(&m_statusBar);

        for(int i = Util::BUY, cbOpIndex = 0; i <= Util::SELL; ++i, ++cbOpIndex)
        {
            m_ui->cbOperationType->addItem(Util::getOperationName(static_cast<Util::Operation>(i)));
            m_ui->cbOperationType->setItemData(cbOpIndex, i);
        }

        for(uint i = Util::GRAM, cbGoldIndex = 0; i <= Util::OUNCE; ++i, ++cbGoldIndex)
        {
            m_ui->cbGoldType->addItem(Util::getGoldName(static_cast<Util::Gold>(i)));
            m_ui->cbGoldType->setItemData(cbGoldIndex, i);
        }

        connect(m_ui->cbOperationType, SIGNAL(currentIndexChanged(int)), this, SLOT(rearrangeDialog()));
        connect(m_ui->bbTransactionApproval, &QDialogButtonBox::accepted, this, &GoldDialog::accept);
    }

    GoldDialog::~GoldDialog()
    {
        delete m_ui;
    }

    void GoldDialog::rearrangeDialog()
    {
        if(Util::BUY == m_ui->cbOperationType->currentData().toInt()) {
            m_ui->lblGoalPrice->setVisible(true);
            m_ui->dsbGoalPrice->setVisible(true);
        } else {
            m_ui->lblGoalPrice->setVisible(false);
            m_ui->dsbGoalPrice->setVisible(false);
        }
    }

    void GoldDialog::accept()
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

        //If it is a buy operation, check the validity of goal price.
        if(Util::BUY == m_ui->cbOperationType->currentData().toInt())
        {
            if(!m_ui->dsbGoalPrice->text().simplified().isEmpty() && !m_ui->dsbGoalPrice->hasAcceptableInput())
            {
                errorMessageList << tr("Goal price is invalid!");
            }
        }

        m_transaction = GoldTransaction(static_cast<Util::Operation>(m_ui->cbOperationType->currentData().toInt()),
                                        static_cast<Util::Gold>(m_ui->cbGoldType->currentData().toInt()),
                                        m_ui->dsbPrice->value(),
                                        m_ui->dsbAmount->value(),
                                        m_ui->dteDateTime->dateTime(),
                                        m_ui->dsbGoalPrice->value());

        if(!errorMessageList.isEmpty())
        {
            m_statusBar.showMessage(errorMessageList.at(0), 3000);
            return;
        }

        //Passed the validation.
        QDialog::accept();
    }

}
