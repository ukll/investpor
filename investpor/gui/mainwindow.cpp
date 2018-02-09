#include "investpor/gui/mainwindow.h"
#include "ui_mainwindow.h"

#include "investpor/core/portfolioxml.h"
#include "investpor/gui/cryptocurrencydialog.h"
#include "investpor/gui/discountbonddialog.h"
#include "investpor/gui/exchangedialog.h"
#include "investpor/gui/funddialog.h"
#include "investpor/gui/golddialog.h"
#include "investpor/gui/stockdialog.h"

#include <QDir>
#include <QFileDialog>
#include <QMessageBox>

using investpor::core::PortfolioXML;

namespace investpor {

    namespace gui {

        /**
         * @brief Setup UI, make connections & prepare portfolio.
         * @param parent : Parent to own main window.
         */
        MainWindow::MainWindow(QWidget *parent) :
            QMainWindow(parent),
            ui(new Ui::MainWindow)
        {
            ui->setupUi(this);
            setWindowTitle(QString("%1 v%2 - Investment Portfolio Tracker").arg(qApp->applicationName()).arg(qApp->applicationVersion()));

            //File menu actions
            QObject::connect(ui->actionNew_Portfolio, &QAction::triggered, this, &MainWindow::newPortfolio);
            QObject::connect(ui->actionOpen_Portfolio, &QAction::triggered, this, &MainWindow::openPortfolio);
            QObject::connect(ui->actionClose, &QAction::triggered, this, &MainWindow::close);

            //BondDialog connections
            QObject::connect(ui->btnNewDiscountBondTransaction, &QPushButton::clicked, ui->actionDiscountBond, &QAction::trigger);
            QObject::connect(ui->actionDiscountBond, &QAction::triggered, this, &MainWindow::discountBondTransaction);

            //CryptocurrencyDialog connections
            QObject::connect(ui->btnNewCryptocurrencyTransaction, &QPushButton::clicked, ui->actionCryptocurrency, &QAction::trigger);
            QObject::connect(ui->actionCryptocurrency, &QAction::triggered, this, &MainWindow::cryptoCurrencyTransaction);

            //ExchangeDialog connections
            QObject::connect(ui->btnNewExchangeTransaction, &QPushButton::clicked, ui->actionExchange, &QAction::trigger);
            QObject::connect(ui->actionExchange, &QAction::triggered, this, &MainWindow::exchangeTransaction);

            //FundDialog connections
            QObject::connect(ui->btnNewFundTransaction, &QPushButton::clicked, ui->actionFund, &QAction::trigger);
            QObject::connect(ui->actionFund, &QAction::triggered, this, &MainWindow::fundTransaction);

            //GoldDialog connections
            QObject::connect(ui->btnNewGoldTransaction, &QPushButton::clicked, ui->actionGold, &QAction::trigger);
            QObject::connect(ui->actionGold, &QAction::triggered, this, &MainWindow::goldTransaction);

            //StockDialog connections
            QObject::connect(ui->btnNewStockTransaction, &QPushButton::clicked, ui->actionStock, &QAction::trigger);
            QObject::connect(ui->actionStock, &QAction::triggered, this, &MainWindow::stockTransaction);
        }

        /**
         * @brief Delete non-decendants of QObject & objects without a parent
         */
        MainWindow::~MainWindow()
        {
            delete ui;
        }

        void MainWindow::newPortfolio()
        {

            QString portfolioURL =
                QFileDialog::getSaveFileName(this, tr("New portfolio file"), QDir::homePath(), tr("XML Files (*.xml)"));

            portfolio = new PortfolioXML(QDir::toNativeSeparators(portfolioURL), this);
            if(portfolio->getState() != PortfolioXML::PortfolioState::Valid)
            {
                QMessageBox::critical(this, tr("No Portfolio"),
                    tr("Portfolio file could not be created!"));
                ui->centralWidget->setEnabled(false);
                return;
            }

            QObject::connect(portfolio, &PortfolioXML::portFolioModified, this, &MainWindow::updateModelsAndGUI);

            connectModels();
            updateModelsAndGUI();
            ui->centralWidget->setEnabled(true);
            ui->menuNew_Transaction->setEnabled(true);
        }

        void MainWindow::openPortfolio()
        {

            QString portfolioURL =
                QFileDialog::getOpenFileName(this, tr("Open a portfolio file"), QDir::homePath(), tr("XML Files (*.xml)"));

            portfolio = new PortfolioXML(QDir::toNativeSeparators(portfolioURL), this);
            if(portfolio->getState() != PortfolioXML::PortfolioState::Valid)
            {
                QMessageBox::critical(this, tr("No Portfolio"),
                    tr("Portfolio file could not be opened!"));
                ui->centralWidget->setEnabled(false);
                return;
            }

            QObject::connect(portfolio, &PortfolioXML::portFolioModified, this, &MainWindow::updateModelsAndGUI);

            connectModels();
            updateModelsAndGUI();
            ui->centralWidget->setEnabled(true);
            ui->menuNew_Transaction->setEnabled(true);
        }

        void MainWindow::connectModels()
        {
            //Cryptocurrency model
            cryptoCurrencyModel = new CryptocurrencyTableModel(portfolio->getCryptocurrencyTransactionList(), this);
            ui->tbvCryptocurrencyView->setModel(cryptoCurrencyModel);

            //Discount bond model
            discountBondModel = new DiscountBondTableModel(portfolio->getDiscountBondTransactionList(), this);
            ui->tbvDiscountBondView->setModel(discountBondModel);

            //Exchange model
            exchangeModel = new ExchangeTableModel(portfolio->getExchangeTransactionList(), this);
            ui->tbvExchangeView->setModel(exchangeModel);

            //Fund model
            fundModel = new FundTableModel(portfolio->getFundTransactionList(), this);
            ui->tbvFundView->setModel(fundModel);

            //Gold model
            goldModel = new GoldTableModel(portfolio->getGoldTransactionList(), this);
            ui->tbvGoldView->setModel(goldModel);

            //Stock model
            stockModel = new StockTableModel(portfolio->getStockTransactionList(), this);
            ui->tbvStockView->setModel(stockModel);
        }

        void MainWindow::updateModelsAndGUI()
        {
            cryptoCurrencyModel->updateTransactionList(portfolio->getCryptocurrencyTransactionList());
            discountBondModel->updateTransactionList(portfolio->getDiscountBondTransactionList());
            exchangeModel->updateTransactionList(portfolio->getExchangeTransactionList());
            fundModel->updateTransactionList(portfolio->getFundTransactionList());
            goldModel->updateTransactionList(portfolio->getGoldTransactionList());
            stockModel->updateTransactionList(portfolio->getStockTransactionList());

            double cryptoCurrencyBuys = cryptoCurrencyModel->totalBuys();
            double cryptoCurrencySells = cryptoCurrencyModel->totalSells();
            ui->leTotalCryptocurrencyBuys->setText(QString::number(cryptoCurrencyBuys, 'f'));
            ui->leTotalCryptocurrencySells->setText(QString::number(cryptoCurrencySells, 'f'));

            double discountBondBuys = discountBondModel->totalBuys();
            double discountBondSells = discountBondModel->totalSells();
            ui->leTotalDiscountBondBuys->setText(QString::number(discountBondBuys, 'f'));
            ui->leTotalDiscountBondSells->setText(QString::number(discountBondSells, 'f'));

            double exchangeBuys = exchangeModel->totalBuys();
            double exchangeSells = exchangeModel->totalSells();
            ui->leTotalExchangeBuys->setText(QString::number(exchangeBuys, 'f'));
            ui->leTotalExchangeSells->setText(QString::number(exchangeSells, 'f'));

            double fundBuys = fundModel->totalBuys();
            double fundSells = fundModel->totalSells();
            ui->leTotalFundBuys->setText(QString::number(fundBuys, 'f'));
            ui->leTotalFundSells->setText(QString::number(fundSells, 'f'));

            double goldBuys = goldModel->totalBuys();
            double goldSells = goldModel->totalSells();
            ui->leTotalGoldBuys->setText(QString::number(goldBuys, 'f'));
            ui->leTotalGoldSells->setText(QString::number(goldSells, 'f'));

            double stockBuys = stockModel->totalBuys();
            double stockSells = stockModel->totalSells();
            ui->leTotalStockBuys->setText(QString::number(stockBuys, 'f'));
            ui->leTotalStockSells->setText(QString::number(stockSells, 'f'));

            double totalInvestmentBuys = 0;
            double totalInvestmentSells = 0;
            totalInvestmentBuys = cryptoCurrencyBuys + discountBondBuys + exchangeBuys + fundBuys + goldBuys + stockBuys;
            totalInvestmentSells = cryptoCurrencySells + discountBondSells + exchangeSells + fundSells + goldSells + stockSells;
            ui->leTotalBuys->setText(QString::number(totalInvestmentBuys, 'f'));
            ui->leTotalSells->setText(QString::number(totalInvestmentSells, 'f'));

            ui->leTotalCryptocurrencyBuys->setEnabled(true);
            ui->leTotalCryptocurrencySells->setEnabled(true);
            ui->leTotalDiscountBondBuys->setEnabled(true);
            ui->leTotalDiscountBondSells->setEnabled(true);
            ui->leTotalExchangeBuys->setEnabled(true);
            ui->leTotalExchangeSells->setEnabled(true);
            ui->leTotalFundBuys->setEnabled(true);
            ui->leTotalFundSells->setEnabled(true);
            ui->leTotalGoldBuys->setEnabled(true);
            ui->leTotalGoldSells->setEnabled(true);
            ui->leTotalStockBuys->setEnabled(true);
            ui->leTotalStockSells->setEnabled(true);
            ui->leTotalBuys->setEnabled(true);
            ui->leTotalSells->setEnabled(true);
        }

        /**
         * @brief Send CryptocurrencyTransaction received from CryptocurrencyDialog to Portfolio
         */
        void MainWindow::cryptoCurrencyTransaction()
        {
            CryptocurrencyDialog cd(this);
            if(cd.exec() == QDialog::Accepted)
            {
                if(!portfolio->saveCryptocurrencyTransaction(cd.getTransaction()))
                {
                    QMessageBox::information(this,
                                             tr("Operation result"), tr("Cryptocurrency transaction could not be saved!"), QMessageBox::Ok);
                } else {
                    statusBar()->showMessage(tr("Cryptocurrency transaction has been saved successfully!"), 3000);
                }
            }
        }

        /**
         * @brief Send DiscountBondTransaction received from DiscountBondDialog to Portfolio
         */
        void MainWindow::discountBondTransaction()
        {
            DiscountBondDialog dbd(this);
            if(dbd.exec() == QDialog::Accepted)
            {
                if(!portfolio->saveDiscountBondTransaction(dbd.getTransaction())) {
                    QMessageBox::information(this,
                                             tr("Operation result"), tr("Discount bond transaction could not be saved!"), QMessageBox::Ok);
                } else {
                    statusBar()->showMessage(tr("Discount bond transaction has been saved successfully!"), 3000);
                }
            }
        }

        /**
         * @brief Send ExchangeTransaction received from ExchangeDialog to Portfolio
         */
        void MainWindow::exchangeTransaction()
        {
            ExchangeDialog ed(this);
            if(ed.exec() == QDialog::Accepted)
            {
                if(!portfolio->saveExchangeTransaction(ed.getTransaction()))
                {
                    QMessageBox::information(this,
                                             tr("Operation result"), tr("Exchange transaction could not be saved!"), QMessageBox::Ok);
                } else {
                    statusBar()->showMessage(tr("Exchange transaction has been saved successfully!"), 3000);
                }
            }
        }

        /**
         * @brief Send FundTransaction received from FundDialog to Portfolio
         */
        void MainWindow::fundTransaction()
        {
            FundDialog fd(this);
            if(fd.exec() == QDialog::Accepted)
            {
                if(!portfolio->saveFundTransaction(fd.getTransaction()))
                {
                    QMessageBox::information(this,
                                             tr("Operation result"), tr("Fund transaction could not be saved!"), QMessageBox::Ok);
                } else {
                    statusBar()->showMessage(tr("Fund transaction has been saved successfully!"), 3000);
                }
            }
        }

        /**
         * @brief Send GoldTransaction received from GoldDialog to Portfolio
         */
        void MainWindow::goldTransaction()
        {
            GoldDialog gd(this);
            if(gd.exec() == QDialog::Accepted)
            {
                if(!portfolio->saveGoldTransaction(gd.getTransaction()))
                {
                    QMessageBox::information(this,
                                             tr("Operation result"), tr("Gold transaction could not be saved!"), QMessageBox::Ok);
                } else {
                    statusBar()->showMessage(tr("Gold transaction has been saved successfully!"), 3000);
                }
            }
        }

        /**
         * @brief Send StockTransaction received from StockDialog to Portfolio
         */
        void MainWindow::stockTransaction()
        {
            StockDialog sd(this);
            if(sd.exec() == QDialog::Accepted)
            {
                if(!portfolio->saveStockTransaction(sd.getTransaction()))
                {
                    QMessageBox::information(this,
                                             tr("Operation result"), tr("Stock transaction could not be saved!"), QMessageBox::Ok);
                } else {
                    statusBar()->showMessage(tr("Stock transaction has been saved successfully!"), 3000);
                }
            }
        }

    }

}
