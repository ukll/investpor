#ifndef HEADERFILESCRYPTOCURRENCYTRANSACTION_H
#define HEADERFILESCRYPTOCURRENCYTRANSACTION_H

#include "investpor/core/util.h"
#include "investpor/core/transaction.h"

#include <QDateTime>

using investpor::core::Util;

namespace investpor {

    namespace core {

        class CryptocurrencyTransaction : public Transaction
        {
        public:
            CryptocurrencyTransaction() : Transaction() { }
            CryptocurrencyTransaction(const Util::Operation &op, const Util::Cryptocurrency &ccurrency, const double &prc, const double &amnt,
                const QDateTime &opDateTime, const double &gPrice);
            virtual ~CryptocurrencyTransaction() { }

            Util::Operation getOperationType() const { return operationType; }
            void setOperationType(const Util::Operation &op) { operationType = op; }
            Util::Cryptocurrency getCryptocurrency() const { return cryptoCurrency; }
            void setCryptocurrency(const Util::Cryptocurrency &ccurrency) { cryptoCurrency = ccurrency; }
            double getPrice() const { return price; }
            void setPrice(const double &prc) { price = prc; }
            double getAmount() const { return amount; }
            void setAmount(const double &amnt) { amount = amnt; }
            QDateTime getOperationDateTime() const { return operationDateTime; }
            void setOperationDateTime(const QDateTime &opDateTime) { operationDateTime = opDateTime; }
            double getGoalPrice() const { return goalPrice; }
            void setGoalPrice(const double &gp) { goalPrice = gp; }

        private:
            Util::Operation operationType;
            Util::Cryptocurrency cryptoCurrency;
            double price;
            double amount;
            QDateTime operationDateTime;
            double goalPrice;
        };

    }

}

#endif // HEADERFILESCRYPTOCURRENCYTRANSACTION_H
