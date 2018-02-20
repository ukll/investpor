#include "portfoliodialog.h"
#include "ui_portfoliodialog.h"

#include "investpor/core/util.h"

#include <QFileDialog>
#include <QDir>

using investpor::core::Util;

namespace investpor {

    namespace gui {

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
            delete ui;
        }

        /**
         * @brief Constructor to use when creating a new portfolio.
         * @param parent : Parent object to own this dialog.
         */
        PortfolioDialog::PortfolioDialog(QWidget *parent) :
            QDialog(parent), ui(new Ui::PortfolioDialog), isEditDialog(false)
        {
            ui->setupUi(this);
            setWindowTitle(tr("New Portfolio"));
            prepareDialog();
            QObject::connect(ui->btnBrowse, &QPushButton::clicked, this, &PortfolioDialog::browseForFile);
        }

        /**
         * @brief Constructor to use when editing portfolio details.
         * @param pName : Current portfolio name.
         * @param bCurrency : Current portfolio base currency.
         * @param parent : Parent object to own this dialog.
         */
        PortfolioDialog::PortfolioDialog(const QString &pName, const Util::Currency &bCurrency, QWidget *parent) :
            QDialog(parent), ui(new Ui::PortfolioDialog), isEditDialog(true), portfolioName(pName), baseCurrency(bCurrency)
        {
            ui->setupUi(this);
            setWindowTitle(tr("Edit Portfolio"));
            prepareDialog();
        }

        void PortfolioDialog::prepareDialog()
        {
            ui->vlStatusBarLayout->addWidget(&statusBar);

            for(uint i = Util::Currency::ARS; i <= Util::Currency::ZAR; ++i)
            {
                ui->cbBaseCurrency->addItem(QString("%1 - %2").arg(Util::currencySymbol(static_cast<Util::Currency>(i)).toUpper())
                                            .arg(Util::currencyName(static_cast<Util::Currency>(i))));
            }

            if(isEditDialog) {
                ui->lePortfolioName->setText(portfolioName);
                ui->cbBaseCurrency->setCurrentIndex(static_cast<int>(baseCurrency - 1));

                ui->lblPortfolioFile->setHidden(true);
                ui->lePortfolioFile->setHidden(true);
                ui->btnBrowse->setHidden(true);
            }
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
            baseCurrency = static_cast<Util::Currency>(ui->cbBaseCurrency->currentIndex() + 1);

            QDialog::accept();
        }

    }

}
