#ifndef UTIL_H
#define UTIL_H

#include "types.h"

class QString;
class QRegExp;

namespace investpor {

    namespace core {

        class Util
        {
        public:
            static bool doublesEqual(double d1, double d2);

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

            static const QRegExp bondISINRegExp();
            static const QRegExp fundCodeRegExp();
            static const QRegExp fundNameRegExp();
            static const QRegExp stockSymbolRegExp();
            static const QRegExp stockNameRegExp();

        private:
            Util() = delete;
            Util(const Util &) = delete;
            Util(const Util &&) = delete;
            ~Util() = delete;
        };

    }

}
#endif // UTIL_H
