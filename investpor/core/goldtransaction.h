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
            GoldTransaction(quint16 id = 0) : Transaction(id) { }
            GoldTransaction(Operation op, Gold gType, double prc, double amnt, QDateTime dt, double gPrice, quint16 id = 0);
            virtual ~GoldTransaction() { }

            Operation getOperationType() { return operationType; }
            void setOperationType(Operation op) { operationType = op; }
            Gold getGoldType() { return goldType; }
            void setGoldType(Gold gType) { goldType = gType; }
            double getPrice() { return price; }
            void setPrice(double prc) { price = prc; }
            double getAmount() { return amount; }
            void setAmount(double amnt) { amount = amnt; }
            QDateTime getOperationDateTime() { return operationDateTime; }
            void setOperationDateTime(QDateTime dt) { operationDateTime = dt; }
            double getGoalPrice() { return goalPrice; }
            void setGoalPrice(double gPrice) { goalPrice = gPrice;}

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
