#include "investpor/gui/mainwindow.h"
#include "ui_mainwindow.h"

#include "investpor/core/portfolioxml.h"
#include "investpor/gui/portfoliodialog.h"
#include "investpor/gui/cryptocurrencydialog.h"
#include "investpor/gui/discountbonddialog.h"
#include "investpor/gui/exchangedialog.h"
#include "investpor/gui/funddialog.h"
#include "investpor/gui/golddialog.h"
#include "investpor/gui/stockdialog.h"

#include <QSettings>
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
            ui->centralWidget->setEnabled(false);
            setWindowTitle(QString("%1 v%2 - Investment Portfolio Tracker").arg(qApp->applicationName()).arg(qApp->applicationVersion()));

            readApplicationSettings();

            //File menu actions
            QObject::connect(ui->actionNew_Portfolio, &QAction::triggered, this, &MainWindow::newPortfolio);
            QObject::connect(ui->actionOpen_Portfolio, &QAction::triggered, this, &MainWindow::openPortfolio);
            QObject::connect(ui->actionClose, &QAction::triggered, this, &MainWindow::close);

            //Edit menu actions
            QObject::connect(ui->actionEdit_Portfolio, &QAction::triggered, this, &MainWindow::editPortfolio);

            //CryptocurrencyDialog connections
            QObject::connect(ui->btnNewCryptocurrencyTransaction, &QPushButton::clicked, ui->actionCryptocurrency, &QAction::trigger);
            QObject::connect(ui->actionCryptocurrency, &QAction::triggered, this, &MainWindow::cryptoCurrencyTransaction);

            //DiscountBondDialog connections
            QObject::connect(ui->btnNewDiscountBondTransaction, &QPushButton::clicked, ui->actionDiscountBond, &QAction::trigger);
            QObject::connect(ui->actionDiscountBond, &QAction::triggered, this, &MainWindow::discountBondTransaction);

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

        /**
         * @brief Reads application settings from previous session
         */
        void MainWindow::readApplicationSettings()
        {
            QSettings settings;
            settings.beginGroup("MainWindow");
            resize(settings.value("size", QSize(1100, 575)).toSize());
            move(settings.value("pos", QPoint(200, 200)).toPoint());
            settings.endGroup();
        }

        /**
         * @brief Writes application settings for next session
         */
        void MainWindow::writeApplicationSettings() const
        {
            QSettings settings;
            settings.beginGroup("MainWindow");
            settings.setValue("size", size());
            settings.setValue("pos", pos());
            settings.endGroup();
        }

        /**
         * @brief Creates a new portfolio by using portfolio filepath, name and base currency.
         */
        void MainWindow::newPortfolio()
        {
            PortfolioDialog *pd = PortfolioDialog::newPortfolioDialog(this);
            if(pd->exec() == QDialog::Accepted)
            {
                portfolio = PortfolioXML::createPortfolio(QDir::toNativeSeparators(pd->getPortfolioURL()),
                                             pd->getPortfolioName(), pd->getBasecurrency(), this);
                if(portfolio->getState() != PortfolioXML::Valid)
                {
                    QMessageBox::critical(this, tr("No Portfolio"),
                                          tr("Portfolio file could not be created!"));
                    ui->centralWidget->setEnabled(false);
                    return;
                }


                connectModels();
                updateTotals();
                ui->centralWidget->setEnabled(true);
                ui->actionEdit_Portfolio->setEnabled(true);
                ui->menuNew_Transaction->setEnabled(true);
            }
        }

        /**
         * @brief Changes portfolio name and base currency.
         */
        void MainWindow::editPortfolio()
        {
            PortfolioDialog *pd = PortfolioDialog::editPortfolioDialog(portfolio->getPortfolioName(), portfolio->getBaseCurrency(), this);
            if(pd->exec() == QDialog::Accepted)
            {
                if(!portfolio->setPortfolioName(pd->getPortfolioName()) ||
                        !portfolio->setBaseCurrency(pd->getBasecurrency()))
                {
                    QMessageBox::warning(this, tr("Operation Failed!"),
                                         tr("Portfolio file could not be edited!"));
                }
            }
        }

        /**
         * @brief Opens an existing portfolio file by using its filepath.
         */
        void MainWindow::openPortfolio()
        {
            QString portfolioURL =
                    QFileDialog::getOpenFileName(this, tr("Open a portfolio file"), QDir::homePath(), tr("XML Files (*.xml)"));

            if(portfolioURL.isEmpty())
            {
                return;
            }

            portfolio = PortfolioXML::openPortfolio(QDir::toNativeSeparators(portfolioURL), this);
            if(portfolio->getState() != PortfolioXML::Valid)
            {
                QMessageBox::critical(this, tr("No Portfolio"),
                                      tr("Portfolio file could not be opened!"));
                ui->centralWidget->setEnabled(false);
                return;
            }


            connectModels();
            updateTotals();
            ui->centralWidget->setEnabled(true);
            ui->actionEdit_Portfolio->setEnabled(true);
            ui->menuNew_Transaction->setEnabled(true);
        }

        /**
         * @brief Connect transaction models to views.
         */
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

        /**
         * @brief Update total buys & total sells values in the window.
         */
        void MainWindow::updateTotals()
        {
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
                                             tr("Operation result"), tr("Cryptocurrency transaction could not be saved!"),
                                             QMessageBox::Ok);
                } else {
                    //Update cryptocurrencyModel
                    cryptoCurrencyModel->updateTransactionList(portfolio->getCryptocurrencyTransactionList());
                    updateTotals();
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
                                             tr("Operation result"), tr("Discount bond transaction could not be saved!"),
                                             QMessageBox::Ok);
                } else {
                    //Update discountBondModel
                    discountBondModel->updateTransactionList(portfolio->getDiscountBondTransactionList());
                    updateTotals();
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
                                             tr("Operation result"), tr("Exchange transaction could not be saved!"),
                                             QMessageBox::Ok);
                } else {
                    //Update exchangeModel
                    exchangeModel->updateTransactionList(portfolio->getExchangeTransactionList());
                    updateTotals();
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
                                             tr("Operation result"), tr("Fund transaction could not be saved!"),
                                             QMessageBox::Ok);
                } else {
                    //Update fundModel
                    fundModel->updateTransactionList(portfolio->getFundTransactionList());
                    updateTotals();
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
                                             tr("Operation result"), tr("Gold transaction could not be saved!"),
                                             QMessageBox::Ok);
                } else {
                    //Update goldModel
                    goldModel->updateTransactionList(portfolio->getGoldTransactionList());
                    updateTotals();
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
                                             tr("Operation result"), tr("Stock transaction could not be saved!"),
                                             QMessageBox::Ok);
                } else {
                    //Update stockModel
                    stockModel->updateTransactionList(portfolio->getStockTransactionList());
                    updateTotals();
                    statusBar()->showMessage(tr("Stock transaction has been saved successfully!"), 3000);
                }
            }
        }

        /**
         * @brief Interrupts closeEvent for some important operations.
         * @param event : QCloseEvent object that is sent when window is closing.
         */
        void MainWindow::closeEvent(QCloseEvent *event)
        {
            writeApplicationSettings();
            event->accept();
        }

    }

}
