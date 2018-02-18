#include "investpor/core/cryptocurrencytransaction.h"

#include <QDateTime>

namespace investpor {

    namespace core {

        CryptocurrencyTransaction::CryptocurrencyTransaction(const Util::Operation &op, const Util::Cryptocurrency &ccurrency,
            const double &prc, const double &amnt, const QDateTime &opDateTime, const double &gPrice) :
            Transaction(), operationType(op), cryptoCurrency(ccurrency), price(prc),
            amount(amnt), operationDateTime(opDateTime), goalPrice(gPrice)
        {

        }

    }

}
