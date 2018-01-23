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
            DiscountBondTransaction(quint16 id = 0);
            DiscountBondTransaction(Operation op, QString isin, QDate term, double nomValue, double sPrice, QDate opDate, quint16 id = 0);
            virtual ~DiscountBondTransaction();

            Operation getOperationType();
            void setOperationType(Operation op);
            QString getISIN();
            void setISIN(QString isin);
            QDate getTerm();
            void setTerm(QDate term);
            double getNominalValue();
            void setNominalValue(double nomValue);
            double getSalePrice();
            void setSalePrice(double sPrice);
            QDate getOperationDate();
            void setOperationDate(QDate opDate);

        private:
            Operation operation;
            QString ISIN;
            QDate termDate;
            double nominalValue;
            double salePrice;
            QDate operationDate;
        };

    }

}
#endif // DISCOUNTBONDTRANSACTION_H
