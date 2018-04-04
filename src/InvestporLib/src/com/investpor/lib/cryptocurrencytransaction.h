#ifndef HEADERFILESCRYPTOCURRENCYTRANSACTION_H
#define HEADERFILESCRYPTOCURRENCYTRANSACTION_H

#include "lib/util.h"
#include "lib/transaction.h"

#include <QDateTime>

namespace lib {

    class CryptocurrencyTransaction : public Transaction
    {
    public:
        CryptocurrencyTransaction() : Transaction() { }
        virtual ~CryptocurrencyTransaction() { }

        Util::Operation getOperationType() const { return operationType; }
        void setOperationType(const Util::Operation &op) { operationType = op; }
        Util::Currency getCryptocurrency() const { return cryptoCurrency; }
        void setCryptocurrency(const Util::Currency &ccurrency) { cryptoCurrency = ccurrency; }
        double getAmount() const { return amount; }
        void setAmount(const double &amnt) { amount = amnt; }
        Util::Currency getBaseCurrency() const { return baseCurrency; }
        void setBaseCurrency(const Util::Currency &bCurrency) { baseCurrency = bCurrency; }
        double getPrice() const { return price; }
        void setPrice(const double &prc) { price = prc; }
        double getExtraExpenses() const { return extraExpenses; }
        void setExtraExpenses(const double &eExpenses) { extraExpenses = eExpenses; }
        QDateTime getOperationDateTime() const { return operationDateTime; }
        void setOperationDateTime(const QDateTime &opDateTime) { operationDateTime = opDateTime; }
        double getGoalPrice() const { return goalPrice; }
        void setGoalPrice(const double &gp) { goalPrice = gp; }

    private:
        Util::Operation operationType;
        Util::Currency cryptoCurrency;
        double amount;
        Util::Currency baseCurrency;
        double price;
        double extraExpenses;
        QDateTime operationDateTime;
        double goalPrice;
    };

}

#endif // HEADERFILESCRYPTOCURRENCYTRANSACTION_H
