#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "investpor/core/portfolioxml.h"
#include "investpor/gui/cryptocurrencytablemodel.h"
#include "investpor/gui/discountbondtablemodel.h"
#include "investpor/gui/exchangetablemodel.h"
#include "investpor/gui/fundtablemodel.h"
#include "investpor/gui/goldtablemodel.h"
#include "investpor/gui/stocktablemodel.h"

#include <QMainWindow>

namespace Ui {
    class MainWindow;
}

using investpor::core::PortfolioXML;

namespace investpor {

    namespace gui {

        class MainWindow : public QMainWindow
        {
            Q_OBJECT

        public:
            explicit MainWindow(QWidget *parent = 0);
            ~MainWindow();

        protected:
            virtual void closeEvent(QCloseEvent *event) override;

        private:
            Ui::MainWindow *ui;

            PortfolioXML *portfolio = nullptr;
            CryptocurrencyTableModel *cryptoCurrencyModel;
            DiscountBondTableModel *discountBondModel;
            ExchangeTableModel *exchangeModel;
            FundTableModel *fundModel;
            GoldTableModel *goldModel;
            StockTableModel *stockModel;

            void setTitle(const QString &title = QString());
            void readApplicationSettings();
            void writeApplicationSettings() const;

            void newPortfolio();
            void editPortfolio();
            void openPortfolio();
            void connectModels();
            void updateTotals();

            void cryptoCurrencyTransaction();
            void discountBondTransaction();
            void exchangeTransaction();
            void fundTransaction();
            void goldTransaction();
            void stockTransaction();
        };

    }

}

#endif // MAINWINDOW_H
