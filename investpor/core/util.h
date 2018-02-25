#ifndef UTIL_H
#define UTIL_H

#include <QObject>

class QString;
class QRegularExpression;

namespace investpor {

    namespace core {

        class Util : public QObject
        {
            Q_OBJECT
        public:
            enum Investment {
                CryptocurrencyInvestment = 0, DiscountBondInvestment, ExchangeInvestment,
                FundInvestment, GoldInvestment, StockInvestment
            };
            Q_ENUM(Investment)

            enum Currency {
                InvalidCurrency = 0,

                //Currency list
                ARS, AUD, BRL, CAD, CHF, CNY, EUR, GBP,
                HKD, IDR, INR, JPY, KRW, MXN, PLN, QAR, RUB, SAR, TND, TRY, USD, ZAR,

                //Cryptocurrency list
                BCH, DASH, ETC, ETH, LTC, MIOTA, XBT, XRP
            };
            Q_ENUM(Currency)

            enum Gold {
                InvalidGold = 0, GRAM, OUNCE
            };
            Q_ENUM(Gold)

            enum Operation {
                InvalidOperation = 0, BUY, SELL
            };
            Q_ENUM(Operation)

            enum StockMarket {
                InvalidStockMarket = 0,
                BMEX, BVMF, MISX, NAPA, XAMS, XASX, XBOM, XFRA,
                XIST, XLON, XMIL, XHKG, XJPX, XJSE, XKRX, XNAS,
                XNSE, XNYS, XPAR, XSHE, XSHG, XSWX, XTAI, XTSE
            };
            Q_ENUM(StockMarket)

            static bool doubleEquality6DecPoints(const double &d1, const double &d2);
            static bool doubleEquality10DecPoints(const double &d1, const double &d2);

            static const QString getInvestmentTagName(const Investment &investment);

            static Currency getCurrency(const QString &text);
            static const QString currencySymbol(const Currency &currency);
            static const QString currencyName(const Currency &currency);
            static Gold getGold(const QString &text);
            static const QString goldSymbol(const Gold &gold);
            static const QString goldName(const Gold &gold);
            static Operation getOperation(const QString &text);
            static const QString operationCode(const Operation &operation);
            static const QString operationName(const Operation &operation);
            static StockMarket getStockMarket(const QString &text);
            static const QString stockMarketSymbol(const StockMarket &market);
            static const QString stockMarketName(const StockMarket &market);

            static const QRegularExpression bondISINRegularExpression();
            static const QRegularExpression fundCodeRegularExpression();
            static const QRegularExpression fundNameRegularExpression();
            static const QRegularExpression stockSymbolRegularExpression();
            static const QRegularExpression stockNameRegularExpression();

        private:
            Util() = delete;
            Util(const Util &) = delete;
            Util& operator=(const Util &) = delete;
            Util(const Util &&) = delete;
        };

    }

}
#endif // UTIL_H
