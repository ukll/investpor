#include "desktop/mainwindow.h"
#include "ui_mainwindow.h"

#include "lib/portfolioxml.h"
#include "desktop/portfoliodialog.h"
#include "desktop/cryptocurrencydialog.h"
#include "desktop/discountbonddialog.h"
#include "desktop/exchangedialog.h"
#include "desktop/funddialog.h"
#include "desktop/golddialog.h"
#include "desktop/stockdialog.h"

#include <QSettings>
#include <QJsonDocument>
#include <QJsonArray>
#include <QDir>
#include <QFileDialog>
#include <QMessageBox>
#include <QSortFilterProxyModel>
#include <QTranslator>

using lib::PortfolioXML;

namespace desktop {

    /**
    * @brief Setup UI, make connections & prepare portfolio.
    * @param parent : Parent to own main window.
    */
    MainWindow::MainWindow(QMap<QString, QList<QTranslator *> > *translators, QWidget *parent) :
        QMainWindow(parent),
        m_ui(new Ui::MainWindow),
        m_portfolio(nullptr),
        m_translatorMap(translators)
    {
        m_ui->setupUi(this);
        m_ui->centralWidget->setEnabled(false);
        m_ui->trvCryptocurrencyView->header()->setDefaultAlignment(Qt::AlignCenter);

        setTitle();
        readApplicationSettings();

        //File menu actions
        connect(m_ui->actionNew_Portfolio, &QAction::triggered, this, &MainWindow::newPortfolio);
        connect(m_ui->actionOpen_Portfolio, &QAction::triggered, this, &MainWindow::openPortfolio);
        connect(m_ui->actionClose, &QAction::triggered, this, &MainWindow::close);

        //Edit menu actions
        connect(m_ui->actionEdit_Portfolio, &QAction::triggered, this, &MainWindow::editPortfolio);

        //Tools menu actions
        connect(m_ui->actionEnglish, &QAction::triggered, this, &MainWindow::changeLocale);
        connect(m_ui->actionTurkish, &QAction::triggered, this, &MainWindow::changeLocale);

        //CryptocurrencyDialog connections
        connect(m_ui->btnNewCryptocurrencyTransaction, &QPushButton::clicked, m_ui->actionCryptocurrency, &QAction::trigger);
        connect(m_ui->actionCryptocurrency, &QAction::triggered, this, &MainWindow::cryptoCurrencyTransaction);

        //DiscountBondDialog connections
        connect(m_ui->btnNewDiscountBondTransaction, &QPushButton::clicked, m_ui->actionDiscountBond, &QAction::trigger);
        connect(m_ui->actionDiscountBond, &QAction::triggered, this, &MainWindow::discountBondTransaction);

        //ExchangeDialog connections
        connect(m_ui->btnNewExchangeTransaction, &QPushButton::clicked, m_ui->actionExchange, &QAction::trigger);
        connect(m_ui->actionExchange, &QAction::triggered, this, &MainWindow::exchangeTransaction);

        //FundDialog connections
        connect(m_ui->btnNewFundTransaction, &QPushButton::clicked, m_ui->actionFund, &QAction::trigger);
        connect(m_ui->actionFund, &QAction::triggered, this, &MainWindow::fundTransaction);

        //GoldDialog connections
        connect(m_ui->btnNewGoldTransaction, &QPushButton::clicked, m_ui->actionGold, &QAction::trigger);
        connect(m_ui->actionGold, &QAction::triggered, this, &MainWindow::goldTransaction);

        //StockDialog connections
        connect(m_ui->btnNewStockTransaction, &QPushButton::clicked, m_ui->actionStock, &QAction::trigger);
        connect(m_ui->actionStock, &QAction::triggered, this, &MainWindow::stockTransaction);
    }

    /**
    * @brief Delete non-decendants of QObject & objects without a parent.
    */
    MainWindow::~MainWindow()
    {
        delete m_ui;
    }

    /**
     * @brief Catch the locale change event.
     * @param event
     */
    void MainWindow::changeEvent(QEvent *event)
    {
        if(event->type() == QEvent::LocaleChange) {
            if(locale().language() == QLocale::English) {
                m_ui->actionEnglish->setChecked(true);
                m_ui->actionTurkish->setChecked(false);

                for(QTranslator *translator : m_translatorMap->value(QStringLiteral("en")))
                {
                    //Load provided translations for English.
                    qApp->installTranslator(translator);
                }
            } else if(locale().language() == QLocale::Turkish) {
                m_ui->actionTurkish->setChecked(true);
                m_ui->actionEnglish->setChecked(false);

                for(QTranslator *translator : m_translatorMap->value(QStringLiteral("tr")))
                {
                    //Load provided translations for Turkish.
                    qApp->installTranslator(translator);
                }
            }

            m_ui->retranslateUi(this);
        } else {
            QMainWindow::changeEvent(event);
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

    /**
    * @brief Sets the window title to include portfolio name if there is an open portfolio.
    */
    void MainWindow::setTitle()
    {
        if(m_portfolio == nullptr) {
            //Do not include portfolio name.
            setWindowTitle(QStringLiteral("%1 v%2").arg(qApp->applicationName()).arg(qApp->applicationVersion()));
        } else {
            //Include portfolio name.
            setWindowTitle(QStringLiteral("%1 - %2 v%3").arg(m_portfolio->getPortfolioName())
                           .arg(qApp->applicationName()).arg(qApp->applicationVersion()));
        }
    }

    void MainWindow::changeLocale()
    {
        const QAction* const localeAction = static_cast<QAction*>(sender());

        QLocale newLocale;
        if(localeAction == nullptr || localeAction == m_ui->actionEnglish) {
            newLocale = QLocale(QLocale::English, QLocale::UnitedStates);
        } else if(localeAction == m_ui->actionTurkish) {
            newLocale = QLocale(QLocale::Turkish, QLocale::Turkey);
        }
        setLocale(newLocale);
        QLocale::setDefault(newLocale);
    }

    /**
    * @brief Reads application settings from previous session
    */
    void MainWindow::readApplicationSettings()
    {
        QSettings settings;
        settings.beginGroup(QStringLiteral("MainWindow"));

        //Load MainWindow size from previous session.
        resize(settings.value(QStringLiteral("size"), QSize(1100, 575)).toSize());

        //Load MainWindow position from previous session.
        move(settings.value(QStringLiteral("pos"), QPoint(200, 200)).toPoint());

        //Load MainWindow locale from the previous session.
        setLocale(settings.value(QStringLiteral("locale")).toLocale());
        QLocale::setDefault(locale());

        settings.endGroup();
        loadRecentPortfoliosList();
    }

    /**
    * @brief Writes application settings for next session
    */
    void MainWindow::writeApplicationSettings() const
    {
        QSettings settings;
        settings.beginGroup(QStringLiteral("MainWindow"));

        //Save MainWindow size for next session.
        settings.setValue(QStringLiteral("size"), size());

        //Save MainWindow position for next session.
        settings.setValue(QStringLiteral("pos"), pos());

        //Save MainWindow locale for next session.
        settings.setValue(QStringLiteral("locale"), locale());
        settings.endGroup();
    }

    /**
    * @brief Loads recently opened portfolios list from settings
    * and adds corresponding QAction's for last 10 portfolios to menu.
    */
    void MainWindow::loadRecentPortfoliosList()
    {
        QSettings settings;
        settings.beginGroup(QStringLiteral("RecentPortfolios"));
        QJsonDocument jsonDocument = QJsonDocument::fromVariant(settings.value(QStringLiteral("PortfolioList")));
        settings.endGroup();

        m_ui->menuOpen_Recent_Portfolios->clear(); //Clear the menu.

        //Create new actions for the menu.
        QJsonArray portfolioUrlsArray = jsonDocument.array();
        for(QJsonArray::const_iterator iter = portfolioUrlsArray.constBegin();
            iter < portfolioUrlsArray.constEnd();
            ++iter)
        {
            PortfolioXML *tempPortfolio = PortfolioXML::openPortfolio(iter->toString());
            QAction *tempAction = nullptr;
            if(tempPortfolio != nullptr && tempPortfolio->getState() == PortfolioXML::Valid)
            {
                tempAction = new QAction(QStringLiteral("%1 (%2) - %3")
                                         .arg(tempPortfolio->getPortfolioName())
                                         .arg(QVariant::fromValue(tempPortfolio->getBaseCurrency()).toString())
                                         .arg(tempPortfolio->getPortfolioFilePath()), this);

                //Connect actions to loadPortfolio function.
                QString tempPortfolioUrl = tempPortfolio->getPortfolioFilePath();
                connect(tempAction, &QAction::triggered, [=](){ loadPortfolio(tempPortfolioUrl); });
                m_ui->menuOpen_Recent_Portfolios->addAction(tempAction);
            }

            delete tempPortfolio; //Delete temporary portfolio object.
        }
    }

    /**
    * @brief Saves the list of recently opened portfolios to settings.
    * @param lastPortfolioUrl : CanonicalFilePath of last opened portfolio.
    */
    void MainWindow::saveRecentPortfoliosList(const QString &lastPortfolioUrl) const
    {
        QSettings settings;
        settings.beginGroup(QStringLiteral("RecentPortfolios"));
        QJsonDocument jsonDocument = QJsonDocument::fromVariant(settings.value(QStringLiteral("PortfolioList")));
        QJsonArray portfolioArray = (jsonDocument.isArray() ? jsonDocument.array() : QJsonArray());

        //If list currently includes newly opened portfolio, remove previous occurences.
        if(portfolioArray.contains(lastPortfolioUrl)) {
            for(int i = 0; i <= portfolioArray.size(); ++i)
            {
                if(portfolioArray.at(i) == lastPortfolioUrl)
                {
                    portfolioArray.removeAt(i);
                }
            }
        }

        //Prepend newly opened portfolio to portfolio Urls list.
        portfolioArray.prepend(lastPortfolioUrl);

        //Reduce the list to 10 portfolios.
        if(portfolioArray.size() > 10)
        {
            for(int i = (portfolioArray.size() - 1); i > 9; --i)
            {
                portfolioArray.removeLast();
            }
        }

        //Save the new list to settings.
        jsonDocument = QJsonDocument(portfolioArray);
        settings.setValue(QStringLiteral("PortfolioList"), jsonDocument.toVariant());
        settings.endGroup();
    }

    /**
    * @brief Creates a new portfolio
    * by using portfolio filepath, name and base currency returned from PortfolioDialog.
    */
    void MainWindow::newPortfolio()
    {
        PortfolioDialog *pd = PortfolioDialog::newPortfolioDialog(this);
        if(pd->exec() == QDialog::Accepted)
        {
            m_portfolio = PortfolioXML::createPortfolio(QDir::toNativeSeparators(pd->getPortfolioURL()),
                                                        pd->getPortfolioName(), pd->getBasecurrency(), this);
            loadPortfolio(); //Load newly created portfolio.
        }
    }

    /**
    * @brief Changes portfolio name and base currency.
    */
    void MainWindow::editPortfolio()
    {
        PortfolioDialog *pd = PortfolioDialog::editPortfolioDialog(m_portfolio->getPortfolioName(), m_portfolio->getBaseCurrency(), this);
        if(pd->exec() == QDialog::Accepted)
        {
            if(!m_portfolio->editPortfolio(pd->getPortfolioName(), pd->getBasecurrency())) {
                //Problem with editing portfolio.
                QMessageBox::warning(this, tr("Operation Failed!"), tr("Portfolio file could not be edited!"));
            } else {
                //Edit is successful. Update GUI.
                setTitle();
                saveRecentPortfoliosList(m_portfolio->getPortfolioFilePath());
                loadRecentPortfoliosList();
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
            //User has closed the dialog without selecting a file.
            return;
        }

        m_portfolio = PortfolioXML::openPortfolio(QDir::toNativeSeparators(portfolioURL), this);
        loadPortfolio(); //Load the newly opened portfolio.
    }

    /**
    * @brief Loads current portfolio values to MainWindow.
    * @param portfolioUrl : CanonicalFilePath to be used if portfolio is selected from menu.
    */
    void MainWindow::loadPortfolio(const QString &portfolioUrl)
    {
        if(!portfolioUrl.isEmpty())
        {
            //Portfolio is selected from the recently opened portfolios list.
            m_portfolio = PortfolioXML::openPortfolio(QDir::toNativeSeparators(portfolioUrl), this);
        }

        //Check the validity of portfolio object.
        if(m_portfolio == nullptr || m_portfolio->getState() != PortfolioXML::Valid)
        {
            QMessageBox::critical(this, tr("No Portfolio"), tr("Portfolio file could not be opened!"));
            m_ui->centralWidget->setEnabled(false);
            return;
        }

        saveRecentPortfoliosList(m_portfolio->getPortfolioFilePath()); //List has been changed. Save the new one.
        loadRecentPortfoliosList(); //Update the menu with new list.
        connectModels(); //Connect new models to views.
        setTitle(); //Change the window title to include new portfolio name.
        m_ui->centralWidget->setEnabled(true);
        m_ui->actionEdit_Portfolio->setEnabled(true);
    }

    /**
    * @brief Connect transaction models to views.
    */
    void MainWindow::connectModels()
    {
        //Cryptocurrency model
        QList<CryptocurrencyTreeModel::CryptocurrencyFieldHeaderPair> cCurrencyHeaderList;
        cCurrencyHeaderList.append( {CryptocurrencyTreeModel::Cryptocurrency, tr("Cryptocurrency")} );
        cCurrencyHeaderList.append( {CryptocurrencyTreeModel::ReferenceCurrency, tr("Reference Currency")} );
        cCurrencyHeaderList.append( {CryptocurrencyTreeModel::Price, tr("Price")} );
        cCurrencyHeaderList.append( {CryptocurrencyTreeModel::Amount, tr("Amount")} );
        cCurrencyHeaderList.append( {CryptocurrencyTreeModel::ExtraExpenses, tr("Extra Expenses")} );
        cCurrencyHeaderList.append( {CryptocurrencyTreeModel::GoalPrice, tr("Goal Price")} );
        cCurrencyHeaderList.append( {CryptocurrencyTreeModel::DateTime, tr("Date & Time")} );
        m_ui->trvCryptocurrencyView->setModel(m_portfolio->getCryptocurrencyProxyModel(cCurrencyHeaderList));
        m_ui->trvCryptocurrencyView->setSortingEnabled(true);

        //Discount bond model
        m_discountBondModel = new DiscountBondTableModel(m_portfolio->getDiscountBondTransactionList(), this);
        m_ui->tbvDiscountBondView->setModel(m_discountBondModel);

        //Exchange model
        m_exchangeModel = new ExchangeTableModel(m_portfolio->getExchangeTransactionList(), this);
        m_ui->tbvExchangeView->setModel(m_exchangeModel);

        //Fund model
        m_fundModel = new FundTableModel(m_portfolio->getFundTransactionList(), this);
        m_ui->tbvFundView->setModel(m_fundModel);

        //Gold model
        m_goldModel = new GoldTableModel(m_portfolio->getGoldTransactionList(), this);
        m_ui->tbvGoldView->setModel(m_goldModel);

        //Stock model
        m_stockModel = new StockTableModel(m_portfolio->getStockTransactionList(), this);
        m_ui->tbvStockView->setModel(m_stockModel);
    }

    /**
    * @brief Send CryptocurrencyTransaction received from CryptocurrencyDialog to Portfolio
    */
    void MainWindow::cryptoCurrencyTransaction()
    {
        CryptocurrencyDialog cd(this);
        if(cd.exec() == QDialog::Accepted)
        {
            if(!m_portfolio->saveCryptocurrencyTransaction(cd.getTransaction())) {
                QMessageBox::information(this, tr("Operation result"),
                                         tr("Cryptocurrency transaction could not be saved!"), QMessageBox::Ok);
            } else {
                //Update cryptocurrencyModel
                //cryptoCurrencyModel->updateTransactionList(portfolio->getCryptocurrencyTransactionList());
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
            if(!m_portfolio->saveDiscountBondTransaction(dbd.getTransaction())) {
                QMessageBox::information(this, tr("Operation result"),
                                         tr("Discount bond transaction could not be saved!"), QMessageBox::Ok);
            } else {
                //Update discountBondModel
                m_discountBondModel->updateTransactionList(m_portfolio->getDiscountBondTransactionList());
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
            if(!m_portfolio->saveExchangeTransaction(ed.getTransaction())) {
                QMessageBox::information(this, tr("Operation result"),
                                         tr("Exchange transaction could not be saved!"), QMessageBox::Ok);
            } else {
                //Update exchangeModel
                m_exchangeModel->updateTransactionList(m_portfolio->getExchangeTransactionList());
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
            if(!m_portfolio->saveFundTransaction(fd.getTransaction())) {
                QMessageBox::information(this, tr("Operation result"),
                                         tr("Fund transaction could not be saved!"), QMessageBox::Ok);
            } else {
                //Update fundModel
                m_fundModel->updateTransactionList(m_portfolio->getFundTransactionList());
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
            if(!m_portfolio->saveGoldTransaction(gd.getTransaction())) {
                QMessageBox::information(this, tr("Operation result"),
                                         tr("Gold transaction could not be saved!"), QMessageBox::Ok);
            } else {
                //Update goldModel
                m_goldModel->updateTransactionList(m_portfolio->getGoldTransactionList());
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
            if(!m_portfolio->saveStockTransaction(sd.getTransaction())) {
                QMessageBox::information(this, tr("Operation result"),
                                         tr("Stock transaction could not be saved!"), QMessageBox::Ok);
            } else {
                //Update stockModel
                m_stockModel->updateTransactionList(m_portfolio->getStockTransactionList());
                statusBar()->showMessage(tr("Stock transaction has been saved successfully!"), 3000);
            }
        }
    }

}
