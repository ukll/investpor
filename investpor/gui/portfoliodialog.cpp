#include "portfoliodialog.h"
#include "ui_portfoliodialog.h"

#include "investpor/core/types.h"
#include "investpor/core/util.h"

#include <QFileDialog>
#include <QDir>
#include <QDebug>
using investpor::core::Currency;
using investpor::core::Util;

namespace investpor {

    namespace gui {

        /**
         * @brief Constructor to use when creating a new portfolio.
         * @param parent : Parent object to own this dialog.
         */
        PortfolioDialog::PortfolioDialog(QWidget *parent) :
            QDialog(parent), isEditDialog(false), ui(new Ui::PortfolioDialog)
        {
            ui->setupUi(this);
            setWindowTitle(tr("New Portfolio"));
            ui->vlStatusBarLayout->addWidget(&statusBar);

            for(uint i = Currency::ARS; i <= Currency::ZAR; ++i)
            {
                ui->cbBaseCurrency->addItem(QString("%1 - %2").arg(Util::currencySymbol(static_cast<Currency>(i)).toUpper())
                                            .arg(Util::currencyName(static_cast<Currency>(i))));
            }

            QObject::connect(ui->btnBrowse, &QPushButton::clicked, this, &PortfolioDialog::browseForFile);
        }

        /**
         * @brief Constructor to use when editing portfolio details.
         * @param pName : Current portfolio name.
         * @param bCurrency : Current portfolio base currency.
         * @param parent : Parent object to own this dialog.
         */
        PortfolioDialog::PortfolioDialog(const QString &pName, const Currency &bCurrency, QWidget *parent) :
            QDialog(parent), isEditDialog(true),  ui(new Ui::PortfolioDialog), portfolioName(pName), baseCurrency(bCurrency)
        {
            ui->setupUi(this);
            setWindowTitle(tr("Edit Portfolio"));
            ui->vlStatusBarLayout->addWidget(&statusBar);

            for(uint i = Currency::ARS; i <= Currency::ZAR; ++i)
            {
                ui->cbBaseCurrency->addItem(QString("%1 - %2").arg(Util::currencySymbol(static_cast<Currency>(i)).toUpper())
                                            .arg(Util::currencyName(static_cast<Currency>(i))));
            }

            ui->lePortfolioName->setText(portfolioName);
            ui->cbBaseCurrency->setCurrentIndex(static_cast<int>(baseCurrency - 1));

            ui->lblPortfolioFile->setHidden(true);
            ui->lePortfolioFile->setHidden(true);
            ui->btnBrowse->setHidden(true);
        }

        PortfolioDialog::~PortfolioDialog()
        {
            delete ui;
        }

        /**
         * @brief Opens a dialog to get the path and name of new portfolio file.
         */
        void PortfolioDialog::browseForFile()
        {
            portfolioURL =
                    QFileDialog::getSaveFileName(this, tr("New portfolio file"), QDir::homePath(), tr("XML Files (*.xml)"));

            if(!portfolioURL.isEmpty() && !portfolioURL.endsWith(".xml"))
            {
                portfolioURL.append(".xml");
            }
            ui->lePortfolioFile->setText(portfolioURL);
        }

        /**
         * @brief Checks the validity of the form inputs before accepting.
         */
        void PortfolioDialog::accept()
        {
            if(ui->lePortfolioName->text().simplified().isEmpty()) {
                statusBar.showMessage(tr("Portfolio name cannot be empty!"), 3000);
                return;
            } else if(!isEditDialog && ui->lePortfolioFile->text().simplified().isEmpty()) {
                statusBar.showMessage(tr("Portfolio file has not been selected!"), 3000);
                return;
            }

            portfolioName = ui->lePortfolioName->text();
            baseCurrency = static_cast<Currency>(ui->cbBaseCurrency->currentIndex() + 1);

            QDialog::accept();
        }

    }

}
