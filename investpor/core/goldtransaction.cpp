#include "investpor/core/goldtransaction.h"

#include "investpor/core/transaction.h"

using investpor::core::Operation;
using investpor::core::Gold;

namespace investpor {

    namespace core {

        GoldTransaction::GoldTransaction(const Operation &op, const Gold &gType, const double &prc, const double &amnt, const QDateTime &dt, const double &gPrice, const quint16 &id) :
            Transaction(id), operationType(op), goldType(gType), price(prc), amount(amnt), operationDateTime(dt), goalPrice(gPrice)
        {

        }

    }

}
