#ifndef EXCHANGETRANSACTION_H
#define EXCHANGETRANSACTION_H

#include "lib/util.h"
#include "lib/transaction.h"

#include <QDateTime>

namespace lib {

    class ExchangeTransaction : public Transaction
    {
    public:
        ExchangeTransaction() : Transaction() { }
        ExchangeTransaction(const Util::Operation &op, const Util::Currency &cur, const double &prc, const double &amnt,
                            const QDateTime &dt, const double &gPrice);
        virtual ~ExchangeTransaction() { }

        Util::Operation getOperationType() const { return operationType; }
        void setOperationType(const Util::Operation &op) { operationType = op; }
        Util::Currency getCurrency() const { return currency; }
        void setCurrency(const Util::Currency &cur) { currency = cur; }
        double getPrice() const { return price; }
        void setPrice(const double &prc) { price = prc; }
        double getAmount() const { return amount; }
        void setAmount(const double &amnt) { amount = amnt; }
        QDateTime getOperationDateTime() const { return dateTime; }
        void setOperationDateTime(const QDateTime &dt) { dateTime = dt; }
        double getGoalPrice() const { return goalPrice; }
        void setGoalPrice(const double &gPrice) { goalPrice = gPrice; }

    private:
        Util::Operation operationType;
        Util::Currency currency;
        double price;
        double amount;
        QDateTime dateTime;
        double goalPrice;
    };

}

#endif // EXCHANGETRANSACTION_H
