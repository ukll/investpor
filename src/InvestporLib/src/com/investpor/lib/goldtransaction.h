#ifndef GOLDTRANSACTION_H
#define GOLDTRANSACTION_H

#include "lib/util.h"
#include "lib/transaction.h"

#include <QDateTime>

namespace lib {

    class GoldTransaction : public Transaction
    {
    public:
        GoldTransaction() : Transaction() { }
        GoldTransaction(const Util::Operation &op, const Util::Gold &gType, const double &prc, const double &amnt,
                        const QDateTime &dt, const double &gPrice);
        virtual ~GoldTransaction() { }

        Util::Operation getOperationType() const { return operationType; }
        void setOperationType(const Util::Operation &op) { operationType = op; }
        Util::Gold getGoldType() const { return goldType; }
        void setGoldType(const Util::Gold &gType) { goldType = gType; }
        double getPrice() const { return price; }
        void setPrice(const double &prc) { price = prc; }
        double getAmount() const { return amount; }
        void setAmount(const double &amnt) { amount = amnt; }
        QDateTime getOperationDateTime() const { return operationDateTime; }
        void setOperationDateTime(const QDateTime &dt) { operationDateTime = dt; }
        double getGoalPrice() const { return goalPrice; }
        void setGoalPrice(const double &gPrice) { goalPrice = gPrice;}

    private:
        Util::Operation operationType;
        Util::Gold goldType;
        double price;
        double amount;
        QDateTime operationDateTime;
        double goalPrice;
    };

}

#endif // GOLDTRANSACTION_H
