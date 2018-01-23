#ifndef EXCHANGETRANSACTION_H
#define EXCHANGETRANSACTION_H

#include "investpor/core/types.h"
#include "investpor/core/transaction.h"

#include <QDateTime>

using investpor::core::Operation;
using investpor::core::Currency;
using investpor::core::Transaction;

namespace investpor {

    namespace core {

        class ExchangeTransaction : public Transaction
        {
        public:
            ExchangeTransaction(quint16 id = 0) : Transaction(id) { }
            ExchangeTransaction(Operation op, Currency cur, double prc, double amnt, QDateTime dt, double gPrice, quint16 id = 0);
            virtual ~ExchangeTransaction() { }

            Operation getOperationType() { return operationType; }
            void setOperationType(Operation op) { operationType = op; }
            Currency getCurrency() { return currency; }
            void setCurrency(Currency cur) { currency = cur; }
            double getPrice() { return price; }
            void setPrice(double prc) { price = prc; }
            double getAmount() { return amount; }
            void setAmount(double amnt) { amount = amnt; }
            QDateTime getOperationDateTime() { return dateTime; }
            void setOperationDateTime(QDateTime dt) { dateTime = dt; }
            double getGoalPrice() { return goalPrice; }
            void setGoalPrice(double gPrice) { goalPrice = gPrice; }

        private:
            Operation operationType;
            Currency currency;
            double price;
            double amount;
            QDateTime dateTime;
            double goalPrice;
        };

    }

}

#endif // EXCHANGETRANSACTION_H
