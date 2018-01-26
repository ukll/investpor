#ifndef FUNDTRANSACTION_H
#define FUNDTRANSACTION_H

#include "investpor/core/types.h"
#include "investpor/core/transaction.h"

#include <QDate>

using investpor::core::Operation;

namespace investpor {

    namespace core {

        class FundTransaction : public Transaction
        {
        public:
            FundTransaction(const quint16 &id = 0) : Transaction(id) { }
            FundTransaction(const Operation &op, const QString &fCode, const QString &fName, const double &prc, const quint32 &cnt,
                            const QDate &orDate, const QDate &opDate, const double &gPrice, const quint16 &id = 0);
            virtual ~FundTransaction() { }

            Operation getOperationType() const { return operationType; }
            void setOperationType(const Operation &op) { operationType = op; }
            QString getFundCode() const { return fundCode; }
            void setFundCode(const QString &fCode) { fundCode = fCode; }
            QString getFundName() const { return fundName; }
            void setFundName(const QString &fName) { fundName = fName; }
            double getPrice() const { return price; }
            void setPrice(const double &prc) { price = prc; }
            quint32 getCount() const { return count; }
            void setCount(const quint32 &cnt) { count = cnt; }
            QDate getOrderDate() const { return orderDate; }
            void setOrderDate(const QDate &orDate) { orderDate = orDate; }
            QDate getOperationDate() const { return operationDate; }
            void setOperationDate(const QDate &opDate) { operationDate = opDate; }
            double getGoalPrice() const { return goalPrice; }
            void setGoalPrice(const double &gPrice) { goalPrice = gPrice; }

        private:
            Operation operationType;
            QString fundCode;
            QString fundName;
            double price;
            quint32 count;
            QDate orderDate;
            QDate operationDate;
            double goalPrice;
        };

    }

}

#endif // FUNDTRANSACTION_H
