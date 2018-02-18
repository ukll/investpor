#include "investpor/core/goldtransaction.h"

#include "investpor/core/util.h"
#include "investpor/core/transaction.h"

namespace investpor {

    namespace core {

        GoldTransaction::GoldTransaction(const Util::Operation &op, const Util::Gold &gType, const double &prc, const double &amnt, const QDateTime &dt, const double &gPrice, const quint16 &id) :
            Transaction(id), operationType(op), goldType(gType), price(prc), amount(amnt), operationDateTime(dt), goalPrice(gPrice)
        {

        }

    }

}
