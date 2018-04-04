#ifndef PORTFOLIOXML_H
#define PORTFOLIOXML_H

#include "lib/abstractportfolio.h"
#include "lib/cryptocurrencytreemodel.h"
#include "lib/util.h"

#include "lib/cryptocurrencytransaction.h"
#include "lib/discountbondtransaction.h"
#include "lib/exchangetransaction.h"
#include "lib/fundtransaction.h"
#include "lib/goldtransaction.h"
#include "lib/stocktransaction.h"


#include <QObject>
#include <QList>

class QFile;
class QDomDocument;
class QDomElement;
class QSortFilterProxyModel;

namespace lib {

    class PortfolioXML final : public AbstractPortfolio
    {
        Q_OBJECT
    public:
        static PortfolioXML* createPortfolio(const QString &filePath, const QString &pName,
                                             const Util::Currency &bCurrency, QObject *parent = nullptr);
        static PortfolioXML* openPortfolio(const QString &filePath, QObject *parent = nullptr);
        ~PortfolioXML();

        virtual bool editPortfolio(const QString &pName, const Util::Currency &bCurrency) override;

        bool saveCryptocurrencyTransaction(const CryptocurrencyTransaction &transaction);
        bool saveDiscountBondTransaction(const DiscountBondTransaction &transaction);
        bool saveExchangeTransaction(const ExchangeTransaction &transaction);
        bool saveFundTransaction(const FundTransaction &transaction);
        bool saveGoldTransaction(const GoldTransaction &transaction);
        bool saveStockTransaction(const StockTransaction &transaction);

        virtual QSortFilterProxyModel *getCryptocurrencyProxyModel(
                const QList<CryptocurrencyTreeModel::CryptocurrencyFieldHeaderPair> &headerDataList) override;

        QList<DiscountBondTransaction> getDiscountBondTransactionList() const;
        QList<ExchangeTransaction> getExchangeTransactionList() const;
        QList<FundTransaction> getFundTransactionList() const;
        QList<GoldTransaction> getGoldTransactionList() const;
        QList<StockTransaction> getStockTransactionList() const;

    private:
        explicit PortfolioXML(const QString &filePath, QObject *parent = nullptr);

        bool loadDomDocument(QDomDocument &domDocument) const;
        bool findChildElementByTagName(const QDomElement &parent, QDomElement &child, const QString &tagName) const;
        bool savePortfolio(const QDomDocument &domDocument) const;
    };

}
#endif // PORTFOLIOXML_H
