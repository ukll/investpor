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
            StockTransaction(quint16 id = 0) : Transaction(id) { }
            StockTransaction(Operation op, StockMarket sMarket, QString symbol, QString name, double prc,
                             quint32 cnt, double cRate, QDateTime opDateTime, double gPrice, quint16 id = 0);
            virtual ~StockTransaction() { }

            Operation getOperationType() { return operationType; }
            void setOperationType(Operation op) { operationType = op; }
            StockMarket getStockMarket() { return stockMarket; }
            void setStockMarket(StockMarket sMarket) { stockMarket = sMarket; }
            QString getStockSymbol() { return stockSymbol; }
            void setStockSymbol(QString symbol) { stockSymbol = symbol; }
            QString getStockName() { return stockName; }
            void setStockName(QString name) { stockName = name; }
            double getPrice() { return price; }
            void setPrice(double prc) { price = prc; }
            quint32 getCount() { return count; }
            void setCount(quint32 cnt) { count = cnt; }
            double getCommissionRate() { return commissionRate; }
            void setCommissionRate(double cRate) { commissionRate = cRate; }
            QDateTime getOperationDateTime() { return operationDateTime; }
            void setOperationDateTime(QDateTime opDateTime) { operationDateTime = opDateTime; }
            double getGoalPrice() { return goalPrice; }
            void setGoalPrice(double gPrice) { goalPrice = gPrice; }

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
