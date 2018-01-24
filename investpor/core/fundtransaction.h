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
            FundTransaction(quint16 id = 0) : Transaction(id) { }
            FundTransaction(Operation op, QString fCode, QString fName, double prc, quint32 cnt,
                            QDate orDate, QDate opDate, double gPrice, quint16 id = 0);
            virtual ~FundTransaction() { }

            Operation getOperationType() const { return operationType; }
            void setOperationType(Operation op) { operationType = op; }
            QString getFundCode() const { return fundCode; }
            void setFundCode(QString fCode) { fundCode = fCode; }
            QString getFundName() const { return fundName; }
            void setFundName(QString fName) { fundName = fName; }
            double getPrice() const { return price; }
            void setPrice(double prc) { price = prc; }
            quint32 getCount() const { return count; }
            void setCount(quint32 cnt) { count = cnt; }
            QDate getOrderDate() const { return orderDate; }
            void setOrderDate(QDate orDate) { orderDate = orDate; }
            QDate getOperationDate() const { return operationDate; }
            void setOperationDate(QDate opDate) { operationDate = opDate; }
            double getGoalPrice() const { return goalPrice; }
            void setGoalPrice(double gPrice) { goalPrice = gPrice; }

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
