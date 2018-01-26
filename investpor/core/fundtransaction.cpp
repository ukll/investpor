#include "investpor/core/fundtransaction.h"

namespace investpor {

    namespace core {

        FundTransaction::FundTransaction(const Operation &op, const QString &fCode, const QString &fName, const double &prc, const quint32 &cnt,
            const QDate &orDate, const QDate &opDate, const double &gPrice, const quint16 &id) :
            Transaction(id), operationType(op), fundCode(fCode), fundName(fName), price(prc),
            count(cnt), orderDate(orDate), operationDate(opDate), goalPrice(gPrice)
        {

        }

    }

}
