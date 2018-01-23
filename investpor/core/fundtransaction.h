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

            Operation getOperationType() { return operationType; }
            void setOperationType(Operation op) { operationType = op; }
            QString getFundCode() { return fundCode; }
            void setFundCode(QString fCode) { fundCode = fCode; }
            QString getFundName() { return fundName; }
            void setFundName(QString fName) { fundName = fName; }
            double getPrice() { return price; }
            void setPrice(double prc) { price = prc; }
            quint32 getCount() { return count; }
            void setCount(quint32 cnt) { count = cnt; }
            QDate getOrderDate() { return orderDate; }
            void setOrderDate(QDate orDate) { orderDate = orDate; }
            QDate getOperationDate() { return operationDate; }
            void setOperationDate(QDate opDate) { operationDate = opDate; }
            double getGoalPrice() { return goalPrice; }
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
