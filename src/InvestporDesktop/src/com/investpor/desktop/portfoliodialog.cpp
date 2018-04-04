#include "desktop/portfoliodialog.h"
#include "ui_portfoliodialog.h"

#include "lib/util.h"

#include <QFileDialog>
#include <QDir>

using lib::Util;

namespace desktop {

    PortfolioDialog* PortfolioDialog::newPortfolioDialog(QWidget *parent)
    {
        return new PortfolioDialog(parent);
    }

    PortfolioDialog* PortfolioDialog::editPortfolioDialog(const QString &pName, const Util::Currency &bCurrency, QWidget *parent)
    {
        return new PortfolioDialog(pName, bCurrency, parent);
    }

    PortfolioDialog::~PortfolioDialog()
    {
        delete m_ui;
    }

    /**
         * @brief Constructor to use when creating a new portfolio.
         * @param parent : Parent object to own this dialog.
         */
    PortfolioDialog::PortfolioDialog(QWidget *parent) :
        QDialog(parent), m_ui(new Ui::PortfolioDialog), m_isEditDialog(false)
    {
        m_ui->setupUi(this);
        setWindowTitle(tr("New Portfolio"));
        prepareDialog();
        QObject::connect(m_ui->btnBrowse, &QPushButton::clicked, this, &PortfolioDialog::browseForFile);
    }

    /**
         * @brief Constructor to use when editing portfolio details.
         * @param pName : Current portfolio name.
         * @param bCurrency : Current portfolio base currency.
         * @param parent : Parent object to own this dialog.
         */
    PortfolioDialog::PortfolioDialog(const QString &pName, const Util::Currency &bCurrency, QWidget *parent) :
        QDialog(parent), m_ui(new Ui::PortfolioDialog), m_isEditDialog(true), m_portfolioName(pName), m_baseCurrency(bCurrency)
    {
        m_ui->setupUi(this);
        setWindowTitle(tr("Edit Portfolio"));
        prepareDialog();
    }

    void PortfolioDialog::prepareDialog()
    {
        m_ui->vlStatusBarLayout->addWidget(&m_statusBar);

        for(uint i = Util::ARS; i <= Util::ZAR; ++i)
        {
            m_ui->cbBaseCurrency->addItem(QString("%1 - %2").arg(QVariant::fromValue(static_cast<Util::Currency>(i)).toString().toUpper())
                                          .arg(Util::getCurrencyName(static_cast<Util::Currency>(i))));
        }

        if(m_isEditDialog) {
            m_ui->lePortfolioName->setText(m_portfolioName);
            m_ui->cbBaseCurrency->setCurrentIndex(static_cast<int>(m_baseCurrency - 1));

            m_ui->lblPortfolioFile->setHidden(true);
            m_ui->lePortfolioFile->setHidden(true);
            m_ui->btnBrowse->setHidden(true);
        }
    }

    /**
         * @brief Opens a dialog to get the path and name of new portfolio file.
         */
    void PortfolioDialog::browseForFile()
    {
        m_portfolioURL =
                QFileDialog::getSaveFileName(this, tr("New portfolio file"), QDir::homePath(), tr("XML Files (*.xml)"));

        if(!m_portfolioURL.isEmpty() && !m_portfolioURL.endsWith(".xml"))
        {
            m_portfolioURL.append(".xml");
        }
        m_ui->lePortfolioFile->setText(m_portfolioURL);
    }

    /**
         * @brief Checks the validity of the form inputs before accepting.
         */
    void PortfolioDialog::accept()
    {
        if(m_ui->lePortfolioName->text().simplified().isEmpty()) {
            m_statusBar.showMessage(tr("Portfolio name cannot be empty!"), 3000);
            return;
        } else if(!m_isEditDialog && m_ui->lePortfolioFile->text().simplified().isEmpty()) {
            m_statusBar.showMessage(tr("Portfolio file has not been selected!"), 3000);
            return;
        }

        m_portfolioName = m_ui->lePortfolioName->text();
        m_baseCurrency = static_cast<Util::Currency>(m_ui->cbBaseCurrency->currentIndex() + 1);

        QDialog::accept();
    }

}
