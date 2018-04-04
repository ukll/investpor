#include "lib/discountbondtransaction.h"

#include <QString>
#include <QDate>

namespace lib {

    DiscountBondTransaction::DiscountBondTransaction(const Util::Operation &op, const QString &isin, const QDate &term,
                                                     const double &nomValue, const double &sPrice, quint32 cnt, const QDate &opDate) :
        Transaction(), operationType(op), ISIN(isin), termDate(term),
        nominalValue(nomValue), salePrice(sPrice), count(cnt), operationDate(opDate)
    {

    }

}
