#include "investpor/core/fundtransaction.h"

namespace investpor {

    namespace core {

        FundTransaction::FundTransaction(quint16 id) :
            Transaction(id)
        {

        }

        FundTransaction::FundTransaction(Operation op, QString fCode, QString fName, double prc, quint32 cnt,
            QDate orDate, QDate opDate, double gPrice, quint16 id) :
            Transaction(id), operationType(op), fundCode(fCode), fundName(fName), price(prc),
            count(cnt), orderDate(orDate), operationDate(opDate), goalPrice(gPrice)
        {

        }

        FundTransaction::~FundTransaction()
        {

        }

    }

}
