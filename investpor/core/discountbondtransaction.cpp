#include "investpor/core/discountbondtransaction.h"

#include <QString>
#include <QDate>

namespace investpor {

    namespace core {

        DiscountBondTransaction::DiscountBondTransaction(Operation op, QString isin, QDate term,
            double nomValue, double sPrice, QDate opDate, quint16 id) :
            Transaction(id), operationType(op), ISIN(isin), termDate(term),
            nominalValue(nomValue), salePrice(sPrice), operationDate(opDate)
        {

        }

    }

}
