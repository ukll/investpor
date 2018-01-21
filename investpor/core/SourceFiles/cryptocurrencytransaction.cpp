#include "investpor/core/HeaderFiles/cryptocurrencytransaction.h"

namespace investpor {

    namespace core {

        CryptocurrencyTransaction::CryptocurrencyTransaction(int id) :
            Transaction(id)
        {

        }

        CryptocurrencyTransaction::CryptocurrencyTransaction(Operation op, Cryptocurrency ccurrency,
            double prc, double amnt, QDateTime opDateTime, double gPrice, int id) :
            Transaction(id), operationType(op), cryptoCurrency(ccurrency), price(prc),
            amount(amnt), operationDateTime(opDateTime), goalPrice(gPrice)
        {

        }

        CryptocurrencyTransaction::~CryptocurrencyTransaction()
        {

        }

    }

}
