#include "../HeaderFiles/mainwindow.h"
#include "ui_mainwindow.h"

#include "HeaderFiles/bonddialog.h"
#include "HeaderFiles/cryptocurrencydialog.h"

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
