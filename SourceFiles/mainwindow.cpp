#include "../HeaderFiles/mainwindow.h"
#include "ui_mainwindow.h"

#include "HeaderFiles/bonddialog.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QObject::connect(ui->btnNewBondTransaction, &QPushButton::clicked, ui->actionBond, &QAction::trigger);
    QObject::connect(ui->actionBond, &QAction::triggered, this, &MainWindow::bondTransaction);
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
