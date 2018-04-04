#ifndef UTIL_H
#define UTIL_H

#include <QObject>

class QString;
class QRegularExpression;

namespace lib {

    class Util final : public QObject
    {
        Q_OBJECT
    public:
        enum Currency {
            InvalidCurrency = 0,

            //Currency list
            ARS, AUD, BRL, CAD, CHF, CNY, EUR, GBP, HKD, IDR, INR,
            JPY, KRW, MXN, PLN, QAR, RUB, SAR, TND, TRY, USD, ZAR,

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
            XHKG, XIST, XJPX, XJSE, XKRX, XLON, XMIL, XNAS,
            XNSE, XNYS, XPAR, XSHE, XSHG, XSWX, XTAI, XTSE
        };
        Q_ENUM(StockMarket)

        static bool checkDoubleEqualityIn6DecPoints(const double &d1, const double &d2);
        static bool checkDoubleEqualityIn10DecPoints(const double &d1, const double &d2);

        static const QString getCurrencyName(const Currency &currency);
        static const QString getGoldName(const Gold &gold);
        static const QString getOperationName(const Operation &operation);
        static const QString getStockMarketName(const StockMarket &market);

        static const QRegularExpression getISINRegularExpression();
        static const QRegularExpression getFundCodeRegularExpression();
        static const QRegularExpression getFundNameRegularExpression();
        static const QRegularExpression getStockSymbolRegularExpression();
        static const QRegularExpression getStockNameRegularExpression();

    private:
        Util() = delete;
        Util(const Util &) = delete;
        Util& operator=(const Util &) = delete;
        Util(const Util &&) = delete;
    };

}
#endif // UTIL_H
