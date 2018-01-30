#include "investpor/core/util.h"

#include "investpor/core/types.h"

#include <cmath>

#include <QObject>
#include <QRegExp>

namespace investpor {

    namespace core {

        bool Util::doubleEquality6DecPoints(const double &d1, const double &d2)
        {
            static const double EPSILON = 0.0000001;

            if(std::abs(d1 - d2) <= EPSILON || std::abs(d1 - d2) <= EPSILON * std::max(std::abs(d1), std::abs(d2))) {
                return true;
            } else {
                return false;
            }
        }

        bool Util::doubleEquality10DecPoints(const double &d1, const double &d2)
        {
            static const double EPSILON = 0.00000000001;

            if(std::abs(d1 - d2) <= EPSILON || std::abs(d1 - d2) <= EPSILON * std::max(std::abs(d1), std::abs(d2))) {
                return true;
            } else {
                return false;
            }
        }

        const QString Util::getInvestmentTagName(const Investment &investment)
        {
            switch (investment) {
            case Investment::CryptoCurrencyInvestment:
                return "cryptocurrency-investments";
            case Investment::DiscountBondInvestment:
                return "discount-bond-investments";
            case Investment::ExchangeInvestment:
                return "exchange-investments";
            case Investment::FundInvestment:
                return "fund-investments";
            case Investment::GoldInvestment:
                return "gold-investments";
            case Investment::StockInvestment:
                return "stock-investments";
            default:
                return QString();
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
                return QString();
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
                return QString();
            }
        }

        Cryptocurrency Util::getCryptocurrency(const QString &text)
        {
            if(text == Util::cryptoCurrencySymbol(Cryptocurrency::ETC)) {
                return Cryptocurrency::ETC;
            } else if(text == Util::cryptoCurrencySymbol(Cryptocurrency::ETH)) {
                return Cryptocurrency::ETH;
            } else if(text == Util::cryptoCurrencySymbol(Cryptocurrency::IOT)) {
                return Cryptocurrency::IOT;
            } else if(text == Util::cryptoCurrencySymbol(Cryptocurrency::LTC)) {
                return Cryptocurrency::LTC;
            } else if(text == Util::cryptoCurrencySymbol(Cryptocurrency::XBT)) {
                return Cryptocurrency::XBT;
            } else if(text == Util::cryptoCurrencySymbol(Cryptocurrency::XRP)) {
                return Cryptocurrency::XRP;
            } else {
                return Cryptocurrency::InvalidCryptocurrency;
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
                return QString();
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
                return QString();
            }
        }

        Currency Util::getCurrency(const QString &text)
        {
            if(Util::currencySymbol(Currency::AUD) == text) {
                return Currency::AUD;
            } else if(Util::currencySymbol(Currency::CAD) == text) {
                return Currency::CAD;
            } else if(Util::currencySymbol(Currency::CNY) == text) {
                return Currency::CNY;
            } else if(Util::currencySymbol(Currency::EUR) == text) {
                return Currency::EUR;
            } else if(Util::currencySymbol(Currency::TRY) == text) {
                return Currency::TRY;
            } else if(Util::currencySymbol(Currency::USD) == text) {
                return Currency::USD;
            } else {
                return Currency::InvalidCurrency;
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
                return QString();
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
                return QString();
            }
        }

        Gold Util::getGold(const QString &text)
        {
            if(Util::goldSymbol(Gold::GRAMS) == text) {
                return Gold::GRAMS;
            } else if (Util::goldSymbol(Gold::ONS) == text) {
                return Gold::ONS;
            } else {
                return Gold::InvalidGold;
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
                return QString();
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
                return QString();
            }
        }

        Operation Util::getOperation(const QString &text)
        {
            if(Util::operationCode(Operation::BUY) == text) {
                return Operation::BUY;
            } else if(Util::operationCode(Operation::SELL) == text) {
                return Operation::SELL;
            } else {
                return Operation::InvalidOperation;
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
                return QString();
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
                return QString();
            }
        }

        StockMarket Util::getStockMarket(const QString &text)
        {
            if(Util::stockMarketSymbol(StockMarket::BIST) == text) {
                return StockMarket::BIST;
            } else if(Util::stockMarketSymbol(StockMarket::NASDAQ) == text) {
                return StockMarket::NASDAQ;
            } else if(Util::stockMarketSymbol(StockMarket::NYSE) == text) {
                return StockMarket::NYSE;
            } else {
                return StockMarket::InvalidStockMarket;
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
