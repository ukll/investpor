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
            CryptocurrencyTransaction(quint16 id = 0) : Transaction(id) { }
            CryptocurrencyTransaction(Operation op, Cryptocurrency ccurrency,
                                      double prc, double amnt, QDateTime opDateTime, double gPrice, quint16 id = 0);
            virtual ~CryptocurrencyTransaction() { }

            Operation getOperationType() const { return operationType; }
            void setOperationType(Operation op) { operationType = op; }
            Cryptocurrency getCryptocurrency() const { return cryptoCurrency; }
            void setCryptocurrency(Cryptocurrency ccurrency) { cryptoCurrency = ccurrency; }
            double getPrice() const { return price; }
            void setPrice(double prc) { price = prc; }
            double getAmount() const { return amount; }
            void setAmount(double amnt) { amount = amnt; }
            QDateTime getOperationDateTime() const { return operationDateTime; }
            void setOperationDateTime(QDateTime opDateTime) { operationDateTime = opDateTime; }
            double getGoalPrice() const { return goalPrice; }
            void setGoalPrice(double gp) { goalPrice = gp; }

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
