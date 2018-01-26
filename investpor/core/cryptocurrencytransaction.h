#ifndef HEADERFILESCRYPTOCURRENCYTRANSACTION_H
#define HEADERFILESCRYPTOCURRENCYTRANSACTION_H

#include "investpor/core/types.h"
#include "investpor/core/transaction.h"

#include <QDateTime>

using investpor::core::Operation;
using investpor::core::Cryptocurrency;

namespace investpor {

    namespace core {

        class CryptocurrencyTransaction : public Transaction
        {
        public:
            CryptocurrencyTransaction(const quint16 &id = 0) : Transaction(id) { }
            CryptocurrencyTransaction(const Operation &op, const Cryptocurrency &ccurrency, const double &prc, const double &amnt,
                const QDateTime &opDateTime, const double &gPrice, const quint16 &id = 0);
            virtual ~CryptocurrencyTransaction() { }

            Operation getOperationType() const { return operationType; }
            void setOperationType(const Operation &op) { operationType = op; }
            Cryptocurrency getCryptocurrency() const { return cryptoCurrency; }
            void setCryptocurrency(const Cryptocurrency &ccurrency) { cryptoCurrency = ccurrency; }
            double getPrice() const { return price; }
            void setPrice(const double &prc) { price = prc; }
            double getAmount() const { return amount; }
            void setAmount(const double &amnt) { amount = amnt; }
            QDateTime getOperationDateTime() const { return operationDateTime; }
            void setOperationDateTime(const QDateTime &opDateTime) { operationDateTime = opDateTime; }
            double getGoalPrice() const { return goalPrice; }
            void setGoalPrice(const double &gp) { goalPrice = gp; }

        private:
            Operation operationType;
            Cryptocurrency cryptoCurrency;
            double price;
            double amount;
            QDateTime operationDateTime;
            double goalPrice;
        };

    }

}

#endif // HEADERFILESCRYPTOCURRENCYTRANSACTION_H
