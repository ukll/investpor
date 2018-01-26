#ifndef UTIL_H
#define UTIL_H

#include "investpor/core/types.h"

class QString;
class QRegExp;

namespace investpor {

    namespace core {

        class Util
        {
        public:
            static bool doublesEqual(const double &d1, const double &d2);

            static const QString cryptoCurrencySymbol(const Cryptocurrency &ccurrency);
            static const QString cryptoCurrencyName(const Cryptocurrency &ccurrency);
            static const QString currencySymbol(const Currency &currency);
            static const QString currencyName(const Currency &currency);
            static const QString goldSymbol(const Gold &gold);
            static const QString goldName(const Gold &gold);
            static const QString operationCode(const Operation &operation);
            static const QString operationName(const Operation &operation);
            static const QString stockMarketSymbol(const StockMarket &market);
            static const QString stockMarketName(const StockMarket &market);

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
