#include "investpor/core/stocktransaction.h"

#include "investpor/core/util.h"
#include "investpor/core/transaction.h"

namespace investpor {

    namespace core {

        StockTransaction::StockTransaction(const Util::Operation &op, const Util::StockMarket &sMarket, const QString &symbol, const QString &name,
            const double &prc, const quint32 &cnt, const double &cRate, const QDateTime &opDateTime, const double &gPrice) :
            Transaction(), operationType(op), stockMarket(sMarket), stockSymbol(symbol), stockName(name), price(prc),
            count(cnt), commissionRate(cRate), operationDateTime(opDateTime), goalPrice(gPrice)
        {

        }

    }

}