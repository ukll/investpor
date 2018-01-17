#include "../HeaderFiles/mainwindow.h"
#include "ui_mainwindow.h"

#include "HeaderFiles/bonddialog.h"
#include "HeaderFiles/cryptocurrencydialog.h"
#include "HeaderFiles/exchangedialog.h"
#include "HeaderFiles/funddialog.h"
#include "HeaderFiles/golddialog.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //BondDialog connections
    QObject::connect(ui->btnNewBondTransaction, &QPushButton::clicked, ui->actionBond, &QAction::trigger);
    QObject::connect(ui->actionBond, &QAction::triggered, this, &MainWindow::bondTransaction);

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
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::bondTransaction()
{
    BondDialog bd;
    bd.exec();
}

void MainWindow::cryptoCurrencyTransaction()
{
    CryptocurrencyDialog cd;
    cd.exec();
}

void MainWindow::exchangeTransaction()
{
    ExchangeDialog ed;
    ed.exec();
}

void MainWindow::fundTransaction()
{
    FundDialog fd;
    fd.exec();
}

void MainWindow::goldTransaction()
{
    GoldDialog gd;
    gd.exec();
}
