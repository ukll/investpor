#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "lib/portfolioxml.h"
#include "lib/cryptocurrencytreemodel.h"

#include "desktop/cryptocurrencytablemodel.h"
#include "desktop/discountbondtablemodel.h"
#include "desktop/exchangetablemodel.h"
#include "desktop/fundtablemodel.h"
#include "desktop/goldtablemodel.h"
#include "desktop/stocktablemodel.h"

#include <QMainWindow>

namespace Ui {
    class MainWindow;
}

class QTranslator;

using lib::PortfolioXML;
using lib::CryptocurrencyTreeModel;

namespace desktop {

    class MainWindow : public QMainWindow
    {
        Q_OBJECT

    public:
        explicit MainWindow(QMap<QString, QList<QTranslator*> > *translators, QWidget *parent = 0);
        ~MainWindow();

    protected:
        virtual void changeEvent(QEvent *event) override;
        virtual void closeEvent(QCloseEvent *event) override;

    private:
        Ui::MainWindow *m_ui;

        PortfolioXML *m_portfolio;
        QMap<QString, QList<QTranslator*> > *m_translatorMap;

        DiscountBondTableModel *m_discountBondModel;
        ExchangeTableModel *m_exchangeModel;
        FundTableModel *m_fundModel;
        GoldTableModel *m_goldModel;
        StockTableModel *m_stockModel;

        void setTitle();
        void changeLocale();
        void readApplicationSettings();
        void writeApplicationSettings() const;
        void loadRecentPortfoliosList();
        void saveRecentPortfoliosList(const QString &lastPortfolioUrl) const;

        void newPortfolio();
        void editPortfolio();
        void openPortfolio();
        void loadPortfolio(const QString &portfolioUrl = QString());
        void connectModels();

        void cryptoCurrencyTransaction();
        void discountBondTransaction();
        void exchangeTransaction();
        void fundTransaction();
        void goldTransaction();
        void stockTransaction();
    };

}

#endif // MAINWINDOW_H
