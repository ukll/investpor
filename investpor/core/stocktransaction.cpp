#include "investpor/core/stocktransaction.h"

#include "investpor/core/transaction.h"

namespace investpor {

    namespace core {

        StockTransaction::StockTransaction(quint16 id) :
            Transaction(id)
        {

        }

        StockTransaction::StockTransaction(Operation op, StockMarket sMarket, QString symbol, QString name, double prc,
            quint32 cnt, double cRate, QDateTime opDateTime, double gPrice, quint16 id) :
            Transaction(id), operationType(op), stockMarket(sMarket), stockSymbol(symbol), stockName(name), price(prc),
            count(cnt), commissionRate(cRate), operationDateTime(opDateTime), goalPrice(gPrice)
        {

        }

    }

}
