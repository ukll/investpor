#ifndef GOLDTRANSACTION_H
#define GOLDTRANSACTION_H

#include "investpor/core/types.h"
#include "investpor/core/transaction.h"

#include <QDateTime>

using investpor::core::Operation;
using investpor::core::Gold;

namespace investpor {

    namespace core {

        class GoldTransaction : public Transaction
        {
        public:
            GoldTransaction(const quint16 &id = 0) : Transaction(id) { }
            GoldTransaction(const Operation &op, const Gold &gType, const double &prc, const double &amnt,
                const QDateTime &dt, const double &gPrice, const quint16 &id = 0);
            virtual ~GoldTransaction() { }

            Operation getOperationType() const { return operationType; }
            void setOperationType(const Operation &op) { operationType = op; }
            Gold getGoldType() const { return goldType; }
            void setGoldType(const Gold &gType) { goldType = gType; }
            double getPrice() const { return price; }
            void setPrice(const double &prc) { price = prc; }
            double getAmount() const { return amount; }
            void setAmount(const double &amnt) { amount = amnt; }
            QDateTime getOperationDateTime() const { return operationDateTime; }
            void setOperationDateTime(const QDateTime &dt) { operationDateTime = dt; }
            double getGoalPrice() const { return goalPrice; }
            void setGoalPrice(const double &gPrice) { goalPrice = gPrice;}

        private:
            Operation operationType;
            Gold goldType;
            double price;
            double amount;
            QDateTime operationDateTime;
            double goalPrice;
        };

    }

}

#endif // GOLDTRANSACTION_H
