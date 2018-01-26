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
            ExchangeTransaction(const quint16 &id = 0) : Transaction(id) { }
            ExchangeTransaction(const Operation &op, const Currency &cur, const double &prc, const double &amnt,
                const QDateTime &dt, const double &gPrice, const quint16 &id = 0);
            virtual ~ExchangeTransaction() { }

            Operation getOperationType() const { return operationType; }
            void setOperationType(const Operation &op) { operationType = op; }
            Currency getCurrency() const { return currency; }
            void setCurrency(const Currency &cur) { currency = cur; }
            double getPrice() const { return price; }
            void setPrice(const double &prc) { price = prc; }
            double getAmount() const { return amount; }
            void setAmount(const double &amnt) { amount = amnt; }
            QDateTime getOperationDateTime() const { return dateTime; }
            void setOperationDateTime(const QDateTime &dt) { dateTime = dt; }
            double getGoalPrice() const { return goalPrice; }
            void setGoalPrice(const double &gPrice) { goalPrice = gPrice; }

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
