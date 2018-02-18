#ifndef STOCKTRANSACTION_H
#define STOCKTRANSACTION_H

#include "investpor/core/util.h"
#include "investpor/core/transaction.h"

#include <QDateTime>

namespace investpor {

    namespace core {

        class StockTransaction : public Transaction
        {
        public:
            StockTransaction() : Transaction() { }
            StockTransaction(const Util::Operation &op, const Util::StockMarket &sMarket, const QString &symbol, const QString &name, const double &prc,
                             const quint32 &cnt, const double &cRate, const QDateTime &opDateTime, const double &gPrice);
            virtual ~StockTransaction() { }

            Util::Operation getOperationType() const { return operationType; }
            void setOperationType(const Util::Operation &op) { operationType = op; }
            Util::StockMarket getStockMarket() const { return stockMarket; }
            void setStockMarket(const Util::StockMarket &sMarket) { stockMarket = sMarket; }
            QString getStockSymbol() const { return stockSymbol; }
            void setStockSymbol(const QString &symbol) { stockSymbol = symbol; }
            QString getStockName() const { return stockName; }
            void setStockName(const QString &name) { stockName = name; }
            double getPrice() const { return price; }
            void setPrice(const double &prc) { price = prc; }
            quint32 getCount() const { return count; }
            void setCount(const quint32 &cnt) { count = cnt; }
            double getCommissionRate() const { return commissionRate; }
            void setCommissionRate(const double &cRate) { commissionRate = cRate; }
            QDateTime getOperationDateTime() const { return operationDateTime; }
            void setOperationDateTime(const QDateTime &opDateTime) { operationDateTime = opDateTime; }
            double getGoalPrice() const { return goalPrice; }
            void setGoalPrice(const double &gPrice) { goalPrice = gPrice; }

        private:
            Util::Operation operationType;
            Util::StockMarket stockMarket;
            QString stockSymbol;
            QString stockName;
            double price;
            quint32 count;
            double commissionRate;
            QDateTime operationDateTime;
            double goalPrice;
        };

    }

}

#endif // STOCKTRANSACTION_H
