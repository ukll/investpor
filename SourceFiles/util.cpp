#include "HeaderFiles/util.h"

#include "HeaderFiles/types.h"

#include <QObject>

namespace Investpor {

    const QString Util::cryptoCurrencySymbol(Cryptocurrency ccurrency)
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

    const QString Util::cryptoCurrencyName(Cryptocurrency ccurrency)
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

    const QString Util::currencySymbol(Currency currency)
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

    const QString Util::currencyName(Currency currency)
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

    const QString Util::goldSymbol(Gold gold)
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

    const QString Util::goldName(Gold gold)
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

    const QString Util::operationCode(Operation operation)
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

    const QString Util::operationName(Operation operation)
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

    const QString Util::stockMarketSymbol(StockMarket market)
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

    const QString Util::stockMarketName(StockMarket market)
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
}
