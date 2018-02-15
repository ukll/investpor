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
            PortfolioXML(const QString &filePath, const QString &pName, const Currency &bCurrency, QObject *parent = nullptr);
            ~PortfolioXML();

            const QString getPortfolioName() const { return portfolioName; }
            bool setPortfolioName(const QString &pName);
            Currency getBaseCurrency() const { return baseCurrency; }
            bool setBaseCurrency(const Currency &bCurrency);
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

        signals:
            void portFolioModified();

        private:
            QFile *portfolioFile;
            QString portfolioName;
            Currency baseCurrency;
            PortfolioState state;

            bool loadDomDocument(QDomDocument &domDocument) const;
            bool findDomElementByTagName(const QDomDocument &domDocument, QDomElement &domElement, const QString &tagName) const;
            bool findDirectChildElementByTagName(const QDomElement &parent, QDomElement &child, const QString &tagName) const;
            bool savePortfolio(const QDomDocument &domDocument) const;
        };

    }

}
#endif // PORTFOLIOXML_H
