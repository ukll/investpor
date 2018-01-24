#ifndef DISCOUNTBONDTRANSACTION_H
#define DISCOUNTBONDTRANSACTION_H

#include "investpor/core/types.h"
#include "investpor/core/transaction.h"

#include <QString>
#include <QDate>

namespace investpor {

    namespace core {

        class DiscountBondTransaction : public Transaction
        {
        public:
            DiscountBondTransaction(quint16 id = 0) : Transaction(id) { }
            DiscountBondTransaction(Operation op, QString isin, QDate term, double nomValue, double sPrice, QDate opDate, quint16 id = 0);
            virtual ~DiscountBondTransaction() { }

            Operation getOperationType() const { return operationType; }
            void setOperationType(Operation op) { operationType = op; }
            QString getISIN() const { return ISIN; }
            void setISIN(QString isin) { ISIN = isin; }
            QDate getTerm() const { return termDate; }
            void setTerm(QDate term) { termDate = term; }
            double getNominalValue() const { return nominalValue; }
            void setNominalValue(double nomValue) { nominalValue = nomValue; }
            double getSalePrice() const { return salePrice; }
            void setSalePrice(double sPrice) { salePrice = sPrice; }
            QDate getOperationDate() const { return operationDate; }
            void setOperationDate(QDate opDate) { operationDate = opDate; }

        private:
            Operation operationType;
            QString ISIN;
            QDate termDate;
            double nominalValue;
            double salePrice;
            QDate operationDate;
        };

    }

}
#endif // DISCOUNTBONDTRANSACTION_H
