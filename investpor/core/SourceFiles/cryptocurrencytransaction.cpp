#include "investpor/core/HeaderFiles/cryptocurrencytransaction.h"

namespace investpor {

    namespace core {

        CryptocurrencyTransaction::CryptocurrencyTransaction(quint16 id) :
            Transaction(id)
        {

        }

        CryptocurrencyTransaction::CryptocurrencyTransaction(Operation op, Cryptocurrency ccurrency,
            double prc, double amnt, QDateTime opDateTime, double gPrice, quint16 id) :
            Transaction(id), operationType(op), cryptoCurrency(ccurrency), price(prc),
            amount(amnt), operationDateTime(opDateTime), goalPrice(gPrice)
        {

        }

        CryptocurrencyTransaction::~CryptocurrencyTransaction()
        {

        }

    }

}
