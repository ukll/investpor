#include "investpor/core/goldtransaction.h"

#include "investpor/core/transaction.h"

using investpor::core::Operation;
using investpor::core::Gold;

namespace investpor {

    namespace core {

        GoldTransaction::GoldTransaction(quint16 id) :
            Transaction(id)
        {

        }

        GoldTransaction::GoldTransaction(Operation op, Gold gType, double prc, double amnt, QDateTime dt, double gPrice, quint16 id) :
            Transaction(id), operationType(op), goldType(gType), price(prc), amount(amnt), operationDateTime(dt), goalPrice(gPrice)
        {

        }

        GoldTransaction::~GoldTransaction()
        {

        }




    }

}
