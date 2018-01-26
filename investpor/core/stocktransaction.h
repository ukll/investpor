#ifndef STOCKTRANSACTION_H
#define STOCKTRANSACTION_H

#include "investpor/core/types.h"
#include "investpor/core/transaction.h"

#include <QDateTime>

using investpor::core::Operation;
using investpor::core::StockMarket;

namespace investpor {

    namespace core {

        class StockTransaction : public Transaction
        {
        public:
            StockTransaction(const quint16 &id = 0) : Transaction(id) { }
            StockTransaction(const Operation &op, const StockMarket &sMarket, const QString &symbol, const QString &name, const double &prc,
                             const quint32 &cnt, const double &cRate, const QDateTime &opDateTime, const double &gPrice, const quint16 &id = 0);
            virtual ~StockTransaction() { }

            Operation getOperationType() const { return operationType; }
            void setOperationType(const Operation &op) { operationType = op; }
            StockMarket getStockMarket() const { return stockMarket; }
            void setStockMarket(const StockMarket &sMarket) { stockMarket = sMarket; }
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
            Operation operationType;
            StockMarket stockMarket;
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
