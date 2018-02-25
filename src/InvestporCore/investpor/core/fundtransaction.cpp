#include "investpor/core/fundtransaction.h"

#include "investpor/core/util.h"

namespace investpor {

    namespace core {

        FundTransaction::FundTransaction(const Util::Operation &op, const QString &fCode, const QString &fName, const double &prc, const quint32 &cnt,
            const QDate &orDate, const QDate &opDate, const double &gPrice) :
            Transaction(), operationType(op), fundCode(fCode), fundName(fName), price(prc),
            count(cnt), orderDate(orDate), operationDate(opDate), goalPrice(gPrice)
        {

        }

    }

}
