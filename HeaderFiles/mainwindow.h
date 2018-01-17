#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    void bondTransaction();
    void cryptoCurrencyTransaction();
    void exchangeTransaction();
    void fundTransaction();
    void goldTransaction();
    void stockTransaction();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
