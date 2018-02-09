#ifndef UTIL_H
#define UTIL_H

#include "investpor/core/types.h"

class QString;
class QRegularExpression;

namespace investpor {

    namespace core {

        class Util
        {
        public:
            static bool doubleEquality6DecPoints(const double &d1, const double &d2);
            static bool doubleEquality10DecPoints(const double &d1, const double &d2);

            static const QString getInvestmentTagName(const Investment &investment);

            static const QString cryptoCurrencySymbol(const Cryptocurrency &ccurrency);
            static const QString cryptoCurrencyName(const Cryptocurrency &ccurrency);
            static Cryptocurrency getCryptocurrency(const QString &text);
            static const QString currencySymbol(const Currency &currency);
            static const QString currencyName(const Currency &currency);
            static Currency getCurrency(const QString &text);
            static const QString goldSymbol(const Gold &gold);
            static const QString goldName(const Gold &gold);
            static Gold getGold(const QString &text);
            static const QString operationCode(const Operation &operation);
            static const QString operationName(const Operation &operation);
            static Operation getOperation(const QString &text);
            static const QString stockMarketSymbol(const StockMarket &market);
            static const QString stockMarketName(const StockMarket &market);
            static StockMarket getStockMarket(const QString &text);

            static const QRegularExpression bondISINRegularExpression();
            static const QRegularExpression fundCodeRegularExpression();
            static const QRegularExpression fundNameRegularExpression();
            static const QRegularExpression stockSymbolRegularExpression();
            static const QRegularExpression stockNameRegularExpression();

        private:
            Util() = delete;
            Util(const Util &) = delete;
            Util(const Util &&) = delete;
            ~Util() = delete;
        };

    }

}
#endif // UTIL_H
