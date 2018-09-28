#ifndef ABSTRACTPORTFOLIO_H
#define ABSTRACTPORTFOLIO_H

#include "lib/util.h"
#include "lib/cryptocurrencytreemodel.h"
#include "lib/cryptocurrencytreeitem.h"
//#include "lib/discountbondtreemodel.h"
//#include "lib/exchangetreemodel.h"
//#include "lib/fundtreemodel.h"
//#include "lib/goldtreemodel.h"
//#include "lib/stocktreemodel.h"

#include <QObject>
#include <QList>
#include <QFileInfo>

class QFile;
class QSortFilterProxyModel;

namespace lib {

    class AbstractPortfolio : public QObject
    {
        Q_OBJECT
    public:
        enum PortfolioState {
            Invalid = 0,
            FileContentIsNotValid, FileCouldNotBeCreated,
            FileCouldNotBeOpened, FileCouldNotBeSaved,
            Valid
        };

        explicit AbstractPortfolio(const QString &filePath, QObject *parent = nullptr);

        virtual bool editPortfolio(const QString &pName, const Util::Currency &bCurrency) = 0;
        const QString getPortfolioFilePath() const { return QFileInfo(*m_portfolioFile).canonicalFilePath(); }
        const QString getPortfolioName() const { return m_portfolioName; }
        Util::Currency getBaseCurrency() const { return m_baseCurrency; }
        PortfolioState getState() const { return m_state; }

        virtual bool newCryptocurrencyTransaction(CryptocurrencyTreeItem cti) = 0;
//        virtual bool newCryptocurrencyTransaction(const DiscountBondTreeItem dbti) = 0;

        virtual QSortFilterProxyModel *getCryptocurrencyProxyModel(
                const QList<CryptocurrencyTreeModel::CryptocurrencyFieldHeaderPair> &headerDataList) = 0;
//        virtual QSortFilterProxyModel *getDiscountBondTreeModel(
//                const QList<DiscountBondTreeModel::DiscountBondFieldHeaderPair> &headerDataList) = 0;
//        virtual QSortFilterProxyModel *getExchangeTreeModel(
//                const QList<ExchangeTreeModel::ExchangeFieldHeaderPair> &headerDataList) = 0;
//        virtual QSortFilterProxyModel *getFundTreeModel(
//                const QList<FundTreeModel::FundFieldHeaderPair> &headerDataList) = 0;
//        virtual QSortFilterProxyModel *getGoldTreeModel(
//                const QList<GoldTreeModel::GoldFieldHeaderPair> &headerDataList) = 0;
//        virtual QSortFilterProxyModel *getStockTreeModel(
//                const QList<StockTreeModel::StockFieldHeaderPair> &headerDataList) = 0;

    protected:
        QFile *m_portfolioFile;
        QString m_portfolioName;
        Util::Currency m_baseCurrency;
        PortfolioState m_state;

        CryptocurrencyTreeModel *m_cryptocurrencyModel;
        QSortFilterProxyModel *m_cryptocurrencyProxyModel;
//        DiscountBondTreeModel *m_discountBondModel;
//        QSortFilterProxyModel *m_discountBondProxyModel;
//        ExchangeTreeModel *m_exchangeModel;
//        QSortFilterProxyModel *m_exchangeProxyModel;
//        FundTreeModel *m_fundModel;
//        QSortFilterProxyModel *m_fundProxyModel;
//        GoldTreeModel *m_goldModel;
//        QSortFilterProxyModel *m_goldProxyModel;
//        StockTreeModel *m_stockModel;
//        QSortFilterProxyModel *m_stockProxyModel;
    };

}
#endif // ABSTRACTPORTFOLIO_H
