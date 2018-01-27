#ifndef PORTFOLIOXML_H
#define PORTFOLIOXML_H

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
                Valid = 0, FileContentIsNotValid, FileCouldNotBeOpened, FileCouldNotBeSaved, FolderCouldNotBeCreated
            };

            explicit PortfolioXML(const QString &filePath, QObject *parent = nullptr);
            ~PortfolioXML();

            PortfolioState getState() const { return state; }

            bool saveCryptocurrencyTransaction(const CryptocurrencyTransaction &transaction);
            bool saveDiscountBondTransaction(const DiscountBondTransaction &transaction);
            bool saveExchangeTransaction(const ExchangeTransaction &transaction);
            bool saveFundTransaction(const FundTransaction &transaction);
            bool saveGoldTransaction(const GoldTransaction &transaction);
            bool saveStockTransaction(const StockTransaction &transaction);

            QList<CryptocurrencyTransaction> getCryptoCurrencyTransactionList() const;
            QList<DiscountBondTransaction> getDiscountBondTransactionList() const;
            QList<ExchangeTransaction> getExchangeTransactionList() const;
            QList<FundTransaction> getFundTransactionList() const;
            QList<GoldTransaction> getGoldTransactionList() const;
            QList<StockTransaction> getStockTransactionList() const;

        private:
            QFile *portfolioFile;
            PortfolioState state;

            bool loadDomDocument(QDomDocument &domDocument);
            bool findDomElementByTagName(const QDomDocument &domDocument, QDomElement &domElement, const QString &tagName);
            bool savePortfolio(const QDomDocument &domDocument);
        };

    }

}
#endif // PORTFOLIOXML_H
