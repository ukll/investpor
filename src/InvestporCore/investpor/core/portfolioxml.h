#ifndef PORTFOLIOXML_H
#define PORTFOLIOXML_H

#include "investpor/core/util.h"
#include "investpor/core/cryptocurrencytransaction.h"
#include "investpor/core/discountbondtransaction.h"
#include "investpor/core/exchangetransaction.h"
#include "investpor/core/fundtransaction.h"
#include "investpor/core/goldtransaction.h"
#include "investpor/core/stocktransaction.h"

#include <QObject>
#include <QList>

class QFile;
class QDomDocument;
class QDomElement;

namespace investpor {

    namespace core {

        class PortfolioXML : public QObject
        {
            Q_OBJECT
        public:
            enum PortfolioState {
                Valid = 0, FileContentIsNotValid, FileCouldNotBeCreated, FileCouldNotBeOpened, FileCouldNotBeSaved
            };

            static PortfolioXML* createPortfolio(const QString &filePath, const QString &pName,
                                                 const Util::Currency &bCurrency, QObject *parent = nullptr);
            static PortfolioXML* openPortfolio(const QString &filePath, QObject *parent = nullptr);
            ~PortfolioXML();

            bool editPortfolio(const QString &pName, const Util::Currency &bCurrency);
            const QString getPortfolioFilePath() const;
            const QString getPortfolioName() const { return portfolioName; }
            Util::Currency getBaseCurrency() const { return baseCurrency; }
            PortfolioState getState() const { return state; }

            bool saveCryptocurrencyTransaction(const CryptocurrencyTransaction &transaction);
            bool saveDiscountBondTransaction(const DiscountBondTransaction &transaction);
            bool saveExchangeTransaction(const ExchangeTransaction &transaction);
            bool saveFundTransaction(const FundTransaction &transaction);
            bool saveGoldTransaction(const GoldTransaction &transaction);
            bool saveStockTransaction(const StockTransaction &transaction);

            QList<CryptocurrencyTransaction> getCryptocurrencyTransactionList() const;
            QList<DiscountBondTransaction> getDiscountBondTransactionList() const;
            QList<ExchangeTransaction> getExchangeTransactionList() const;
            QList<FundTransaction> getFundTransactionList() const;
            QList<GoldTransaction> getGoldTransactionList() const;
            QList<StockTransaction> getStockTransactionList() const;

        private:
            QFile *portfolioFile;
            QString portfolioName;
            Util::Currency baseCurrency;
            PortfolioState state;

            explicit PortfolioXML(const QString &filePath, QObject *parent = nullptr);

            bool loadDomDocument(QDomDocument &domDocument) const;
            bool findChildElementByTagName(const QDomElement &parent, QDomElement &child, const QString &tagName) const;
            bool savePortfolio(const QDomDocument &domDocument) const;
        };

    }

}
#endif // PORTFOLIOXML_H
