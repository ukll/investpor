#ifndef UTIL_H
#define UTIL_H

#include "HeaderFiles/types.h"

class QString;

namespace Investpor {

    class Util
    {
    public:
        static const QString cryptoCurrencySymbol(Cryptocurrency ccurrency);
        static const QString cryptoCurrencyName(Cryptocurrency ccurrency);
        static const QString currencySymbol(Currency currency);
        static const QString currencyName(Currency currency);
        static const QString goldSymbol(Gold gold);
        static const QString goldName(Gold gold);
        static const QString operationCode(Operation operation);
        static const QString operationName(Operation operation);
        static const QString stockMarketSymbol(StockMarket market);
        static const QString stockMarketName(StockMarket market);

    private:
        Util() = delete;
        Util(const Util &) = delete;
        Util(const Util &&) = delete;
        ~Util() = delete;
    };

}
#endif // UTIL_H
