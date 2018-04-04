#include "lib/goldtransaction.h"

#include "lib/util.h"
#include "lib/transaction.h"

namespace lib {

    GoldTransaction::GoldTransaction(const Util::Operation &op, const Util::Gold &gType, const double &prc, const double &amnt, const QDateTime &dt, const double &gPrice) :
        Transaction(), operationType(op), goldType(gType), price(prc), amount(amnt), operationDateTime(dt), goalPrice(gPrice)
    {

    }

}
