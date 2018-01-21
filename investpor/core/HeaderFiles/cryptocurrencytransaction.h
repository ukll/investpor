#ifndef HEADERFILESCRYPTOCURRENCYTRANSACTION_H
#define HEADERFILESCRYPTOCURRENCYTRANSACTION_H

#include "types.h"
#include "transaction.h"

#include <QDateTime>

using investpor::core::Operation;
using investpor::core::Cryptocurrency;

namespace investpor {

    namespace core {

        class CryptocurrencyTransaction : public Transaction
        {
        public:
            CryptocurrencyTransaction(quint16 id = 0);
            CryptocurrencyTransaction(Operation op, Cryptocurrency ccurrency,
                                      double prc, double amnt, QDateTime opDateTime, double gPrice, quint16 id = 0);
            virtual ~CryptocurrencyTransaction();

            Operation getOperationType() { return operationType; }
            void setOperationType(Operation op) { operationType = op; }
            Cryptocurrency getCryptocurrency() { return cryptoCurrency; }
            void setCryptocurrency(Cryptocurrency ccurrency) { cryptoCurrency = ccurrency; }
            double getPrice() { return price; }
            void setPrice(double prc) { price = prc; }
            double getAmount() { return amount; }
            void setAmount(double amnt) { amount = amnt; }
            QDateTime getOperationDateTime() { return operationDateTime; }
            void setOperationDateTime(QDateTime opDateTime) { operationDateTime = opDateTime; }
            double getGoalPrice() { return goalPrice; }
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
