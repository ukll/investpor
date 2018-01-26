#include "investpor/core/exchangetransaction.h"

#include "investpor/core/types.h"

namespace investpor {

    namespace core {

        ExchangeTransaction::ExchangeTransaction(const Operation &op, const Currency &cur, const double &prc, const double &amnt,
            const QDateTime &dt, const double &gPrice, const quint16 &id) :
            Transaction(id), operationType(op), currency(cur), price(prc), amount(amnt), dateTime(dt), goalPrice(gPrice)
        {

        }

    }

}
