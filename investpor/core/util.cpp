#include "investpor/core/util.h"

#include "investpor/core/types.h"

#include <cmath>

#include <QObject>
#include <QRegExp>

namespace investpor {

    namespace core {

        bool Util::doublesEqual(const double &d1, const double &d2)
        {
            static const double EPSILON = 0.0000001;

            if(std::abs(d1 - d2) <= EPSILON || std::abs(d1 - d2) <= EPSILON * std::max(std::abs(d1), std::abs(d2))) {
                return true;
            } else {
                return false;
            }
        }

        const QString Util::cryptoCurrencySymbol(const Cryptocurrency &ccurrency)
        {
            switch (ccurrency) {
            case Cryptocurrency::ETC:
                return "etc";
            case Cryptocurrency::ETH:
                return "eth";
            case Cryptocurrency::LTC:
                return "ltc";
            case Cryptocurrency::IOT:
                return "iot";
            case Cryptocurrency::XBT:
                return "xbt";
            case Cryptocurrency::XRP:
                return "xrp";
            default:
                return "";
            }
        }

        const QString Util::cryptoCurrencyName(const Cryptocurrency &ccurrency)
        {
            switch (ccurrency) {
            case Cryptocurrency::ETC:
                return QObject::tr("Ethereum Classic");
            case Cryptocurrency::ETH:
                return QObject::tr("Ethereum");
            case Cryptocurrency::LTC:
                return QObject::tr("Litecoin");
            case Cryptocurrency::IOT:
                return QObject::tr("IOTA");
            case Cryptocurrency::XBT:
                return QObject::tr("Bitcoin");
            case Cryptocurrency::XRP:
                return QObject::tr("Ripple");
            default:
                return "";
            }
        }

        const QString Util::currencySymbol(const Currency &currency)
        {
            switch (currency) {
            case Currency::AUD:
                return "aud";
            case Currency::CAD:
                return "cad";
            case Currency::CNY:
                return "cny";
            case Currency::EUR:
                return "eur";
            case Currency::TRY:
                return "try";
            case Currency::USD:
                return "usd";
            default:
                return "";
            }
        }

        const QString Util::currencyName(const Currency &currency)
        {
            switch (currency) {
            case Currency::AUD:
                return QObject::tr("Australian Dollar");
            case Currency::CAD:
                return QObject::tr("Canadian Dollar");
            case Currency::CNY:
                return QObject::tr("Chinese Yuan Renminbi");
            case Currency::EUR:
                return QObject::tr("Euro");
            case Currency::TRY:
                return QObject::tr("Turkish Lira");
            case Currency::USD:
                return QObject::tr("United States Dollar");
            default:
                return "";
            }
        }

        const QString Util::goldSymbol(const Gold &gold)
        {
            switch (gold) {
            case Gold::GRAMS:
                return "grams";
            case Gold::ONS:
                return "ons";
            default:
                return "";
            }
        }

        const QString Util::goldName(const Gold &gold)
        {
            switch (gold) {
            case Gold::GRAMS:
                return QObject::tr("Grams");
            case Gold::ONS:
                return QObject::tr("Ons");
            default:
                return "";
            }
        }

        const QString Util::operationCode(const Operation &operation)
        {
            switch (operation) {
            case Operation::BUY:
                return "buy";
            case Operation::SELL:
                return "sell";
            default:
                return "";
            }
        }

        const QString Util::operationName(const Operation &operation)
        {
            switch (operation) {
            case Operation::BUY:
                return QObject::tr("Buy");
            case Operation::SELL:
                return QObject::tr("Sell");
            default:
                return "";
            }
        }

        const QString Util::stockMarketSymbol(const StockMarket &market)
        {
            switch (market) {
            case StockMarket::BIST:
                return "bist";
            case StockMarket::NASDAQ:
                return "nasdaq";
            case StockMarket::NYSE:
                return "nyse";
            default:
                return "";
            }
        }

        const QString Util::stockMarketName(const StockMarket &market)
        {
            switch (market) {
            case StockMarket::BIST:
                return QObject::tr("Borsa Istanbul");
            case StockMarket::NASDAQ:
                return QObject::tr("National Association of Securities Dealer Automated Quotation");
            case StockMarket::NYSE:
                return QObject::tr("New York Stock Exchange");
            default:
                return "";
            }
        }

        const QRegExp Util::bondISINRegExp()
        {
            QRegExp exp("^[a-zA-Z]{2}[a-zA-Z0-9]{9}[0-9]{1,3}$");
            return exp;
        }

        const QRegExp Util::fundCodeRegExp()
        {
            QRegExp exp("^[a-zA-Z0-9]{3,5}$");
            return exp;
        }

        const QRegExp Util::fundNameRegExp()
        {
            QRegExp exp("^([a-zA-Z0-9]+\\.? ?)+$");
            return exp;
        }

        const QRegExp Util::stockSymbolRegExp()
        {
            QRegExp exp("^[a-zA-Z]+$");
            return exp;
        }

        const QRegExp Util::stockNameRegExp()
        {
            QRegExp exp("^([a-zA-Z0-9]+\\.? ?)+$");
            return exp;
        }

    }
}
