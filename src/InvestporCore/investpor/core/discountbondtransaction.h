#ifndef DISCOUNTBONDTRANSACTION_H
#define DISCOUNTBONDTRANSACTION_H

#include "investpor/core/util.h"
#include "investpor/core/transaction.h"

#include <QString>
#include <QDate>

namespace investpor {

    namespace core {

        class DiscountBondTransaction : public Transaction
        {
        public:
            DiscountBondTransaction() : Transaction() { }
            DiscountBondTransaction(const Util::Operation &op, const QString &isin, const QDate &term, const double &nomValue,
                const double &sPrice, quint32 cnt, const QDate &opDate);
            virtual ~DiscountBondTransaction() { }

            Util::Operation getOperationType() const { return operationType; }
            void setOperationType(const Util::Operation &op) { operationType = op; }
            QString getISIN() const { return ISIN; }
            void setISIN(const QString &isin) { ISIN = isin; }
            QDate getTerm() const { return termDate; }
            void setTerm(const QDate &term) { termDate = term; }
            double getNominalValue() const { return nominalValue; }
            void setNominalValue(const double &nomValue) { nominalValue = nomValue; }
            double getSalePrice() const { return salePrice; }
            void setSalePrice(const double &sPrice) { salePrice = sPrice; }
            quint32 getCount() const { return count; }
            void setCount(const quint32 &cnt) { count = cnt;}
            QDate getOperationDate() const { return operationDate; }
            void setOperationDate(const QDate &opDate) { operationDate = opDate; }

        private:
            Util::Operation operationType;
            QString ISIN;
            QDate termDate;
            double nominalValue;
            double salePrice;
            quint32 count;
            QDate operationDate;
        };

    }

}
#endif // DISCOUNTBONDTRANSACTION_H
