#include "lib/exchangetransaction.h"

#include "lib/util.h"

namespace lib {

    ExchangeTransaction::ExchangeTransaction(const Util::Operation &op, const Util::Currency &cur, const double &prc, const double &amnt,
                                             const QDateTime &dt, const double &gPrice) :
        Transaction(), operationType(op), currency(cur), price(prc), amount(amnt), dateTime(dt), goalPrice(gPrice)
    {

    }

}
