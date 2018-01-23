#include "investpor/core/exchangetransaction.h"

#include "investpor/core/types.h"

namespace investpor {

    namespace core {

        ExchangeTransaction::ExchangeTransaction(Operation op, Currency cur, double prc, double amnt, QDateTime dt, double gPrice, quint16 id) :
            Transaction(id), operationType(op), currency(cur), price(prc), amount(amnt), dateTime(dt), goalPrice(gPrice)
        {

        }

    }

}
