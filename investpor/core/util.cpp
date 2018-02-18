#include "investpor/core/util.h"

#include "investpor/core/types.h"

#include <cmath>

#include <QObject>
#include <QRegularExpression>

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
            case Cryptocurrency::BCH:
                return "bch";
            case Cryptocurrency::DASH:
                return "dash";
            case Cryptocurrency::ETC:
                return "etc";
            case Cryptocurrency::ETH:
                return "eth";
            case Cryptocurrency::LTC:
                return "ltc";
            case Cryptocurrency::MIOTA:
                return "miota";
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
            case Cryptocurrency::BCH:
                return QObject::tr("Bitcoin Cash");
            case Cryptocurrency::DASH:
                return QObject::tr("Dash");
            case Cryptocurrency::ETC:
                return QObject::tr("Ethereum Classic");
            case Cryptocurrency::ETH:
                return QObject::tr("Ethereum");
            case Cryptocurrency::LTC:
                return QObject::tr("Litecoin");
            case Cryptocurrency::MIOTA:
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
            if(text == Util::cryptoCurrencySymbol(Cryptocurrency::BCH)){
                return Cryptocurrency::BCH;
            } else if(text == Util::cryptoCurrencySymbol(Cryptocurrency::DASH)) {
                return Cryptocurrency::DASH;
            } else if(text == Util::cryptoCurrencySymbol(Cryptocurrency::ETC)) {
                return Cryptocurrency::ETC;
            } else if(text == Util::cryptoCurrencySymbol(Cryptocurrency::ETH)) {
                return Cryptocurrency::ETH;
            } else if(text == Util::cryptoCurrencySymbol(Cryptocurrency::MIOTA)) {
                return Cryptocurrency::MIOTA;
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
            case Currency::ARS:
                return "ars";
            case Currency::AUD:
                return "aud";
            case Currency::BRL:
                return "brl";
            case Currency::CAD:
                return "cad";
            case Currency::CHF:
                return "chf";
            case Currency::CNY:
                return "cny";
            case Currency::EUR:
                return "eur";
            case Currency::GBP:
                return "gbp";
            case Currency::HKD:
                return "hkd";
            case Currency::IDR:
                return "idr";
            case Currency::INR:
                return "inr";
            case Currency::JPY:
                return "jpy";
            case Currency::KRW:
                return "krw";
            case Currency::MXN:
                return "mxn";
            case Currency::PLN:
                return "pln";
            case Currency::QAR:
                return "qar";
            case Currency::RUB:
                return "rub";
            case Currency::SAR:
                return "sar";
            case Currency::TND:
                return "tnd";
            case Currency::TRY:
                return "try";
            case Currency::USD:
                return "usd";
            case Currency::ZAR:
                return "zar";
            default:
                return QString();
            }
        }

        const QString Util::currencyName(const Currency &currency)
        {
            switch (currency) {
            case Currency::ARS:
                return QObject::tr("Argentine Peso");
            case Currency::AUD:
                return QObject::tr("Australian Dollar");
            case Currency::BRL:
                return QObject::tr("Brazilian Real");
            case Currency::CAD:
                return QObject::tr("Canadian Dollar");
            case Currency::CHF:
                return QObject::tr("Swiss Franc");
            case Currency::CNY:
                return QObject::tr("Chinese Yuan Renminbi");
            case Currency::EUR:
                return QObject::tr("Euro");
            case Currency::GBP:
                return QObject::tr("British Pound");
            case Currency::HKD:
                return QObject::tr("Hong Kong Dollar");
            case Currency::IDR:
                return QObject::tr("Indonesian Rupiah");
            case Currency::INR:
                return QObject::tr("Indian Rupee");
            case Currency::JPY:
                return QObject::tr("Japanese Yen");
            case Currency::KRW:
                return QObject::tr("South Korean Won");
            case Currency::MXN:
                return QObject::tr("Mexican Peso");
            case Currency::PLN:
                return QObject::tr("Polish Zloty");
            case Currency::QAR:
                return QObject::tr("Qatari Riyal");
            case Currency::RUB:
                return QObject::tr("Russian Ruble");
            case Currency::SAR:
                return QObject::tr("Saudi Riyal");
            case Currency::TND:
                return QObject::tr("Indian Rupee");
            case Currency::TRY:
                return QObject::tr("Turkish Lira");
            case Currency::USD:
                return QObject::tr("United States Dollar");
            case Currency::ZAR:
                return QObject::tr("South African Rand");
            default:
                return QString();
            }
        }

        Currency Util::getCurrency(const QString &text)
        {
            if(Util::currencySymbol(Currency::ARS) == text) {
                return Currency::ARS;
            } else if(Util::currencySymbol(Currency::AUD) == text) {
                return Currency::AUD;
            } else if(Util::currencySymbol(Currency::BRL) == text) {
                return Currency::BRL;
            } else if(Util::currencySymbol(Currency::CAD) == text) {
                return Currency::CAD;
            } else if(Util::currencySymbol(Currency::CHF) == text) {
                return Currency::CHF;
            } else if(Util::currencySymbol(Currency::CNY) == text) {
                return Currency::CNY;
            } else if(Util::currencySymbol(Currency::EUR) == text) {
                return Currency::EUR;
            } else if(Util::currencySymbol(Currency::GBP) == text) {
                return Currency::GBP;
            } else if(Util::currencySymbol(Currency::HKD) == text) {
                return Currency::HKD;
            } else if(Util::currencySymbol(Currency::IDR) == text) {
                return Currency::IDR;
            } else if(Util::currencySymbol(Currency::INR) == text) {
                return Currency::INR;
            } else if(Util::currencySymbol(Currency::JPY) == text) {
                return Currency::JPY;
            } else if(Util::currencySymbol(Currency::KRW) == text) {
                return Currency::KRW;
            } else if(Util::currencySymbol(Currency::MXN) == text) {
                return Currency::MXN;
            } else if(Util::currencySymbol(Currency::PLN) == text) {
                return Currency::PLN;
            } else if(Util::currencySymbol(Currency::QAR) == text) {
                return Currency::QAR;
            } else if(Util::currencySymbol(Currency::RUB) == text) {
                return Currency::RUB;
            } else if(Util::currencySymbol(Currency::SAR) == text) {
                return Currency::SAR;
            } else if(Util::currencySymbol(Currency::TND) == text) {
                return Currency::TND;
            } else if(Util::currencySymbol(Currency::TRY) == text) {
                return Currency::TRY;
            } else if(Util::currencySymbol(Currency::USD) == text) {
                return Currency::USD;
            } else if(Util::currencySymbol(Currency::ZAR) == text) {
                return Currency::ZAR;
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
            case StockMarket::BMEX:
                return QString("bmex");
            case StockMarket::BVMF:
                return QString("bvmf");
            case StockMarket::MISX:
                return QString("misx");
            case StockMarket::NAPA:
                return QString("napa");
            case StockMarket::XAMS:
                return QString("xams");
            case StockMarket::XASX:
                return QString("xasx");
            case StockMarket::XBOM:
                return QString("xbom");
            case StockMarket::XFRA:
                return QString("xfra");
            case StockMarket::XIST:
                return QString("xist");
            case StockMarket::XLON:
                return QString("xlon");
            case StockMarket::XMIL:
                return QString("xmil");
            case StockMarket::XHKG:
                return QString("xhkg");
            case StockMarket::XJPX:
                return QString("xjpx");
            case StockMarket::XJSE:
                return QString("xjse");
            case StockMarket::XKRX:
                return QString("xkrx");
            case StockMarket::XNAS:
                return QString("xnas");
            case StockMarket::XNSE:
                return QString("xnse");
            case StockMarket::XNYS:
                return QString("xnys");
            case StockMarket::XPAR:
                return QString("xpar");
            case StockMarket::XSHE:
                return QString("xshe");
            case StockMarket::XSHG:
                return QString("xshg");
            case StockMarket::XSWX:
                return QString("xswx");
            case StockMarket::XTAI:
                return QString("xtai");
            case StockMarket::XTSE:
                return QString("xtse");
            default:
                return QString();
            }
        }

        const QString Util::stockMarketName(const StockMarket &market)
        {
            switch (market) {
            case StockMarket::BMEX:
                return QObject::tr("(ES) Bolsas y Mercados Españoles");
            case StockMarket::BVMF:
                return QObject::tr("(BR) Brasil, Bolsa, Balcão");
            case StockMarket::MISX:
                return QObject::tr("(RU) Moscow Exchange");
            case StockMarket::NAPA:
                return QObject::tr("(SE) NASDAQ Nordic");
            case StockMarket::XAMS:
                return QObject::tr("(NL) Euronext Amsterdam");
            case StockMarket::XASX:
                return QObject::tr("(AU) Australian Securities Exchange");
            case StockMarket::XBOM:
                return QObject::tr("(IN) Bombay Stock Exchange");
            case StockMarket::XFRA:
                return QObject::tr("(DE) Frankfurt Stock Exchange");
            case StockMarket::XIST:
                return QObject::tr("(TR) Borsa Istanbul");
            case StockMarket::XLON:
                return QObject::tr("(GB) London Stock Exchange");
            case StockMarket::XMIL:
                return QObject::tr("(IT) Milan Stock Exchange");
            case StockMarket::XHKG:
                return QObject::tr("(HK) Hong Kong Stock Exchange");
            case StockMarket::XJPX:
                return QObject::tr("(JP) Tokyo Stock Exchange");
            case StockMarket::XJSE:
                return QObject::tr("(ZA) Johannesburg Stock Exchange");
            case StockMarket::XKRX:
                return QObject::tr("(KR) Korea Exchange");
            case StockMarket::XNAS:
                return QObject::tr("(US) National Association of Securities Dealer Automated Quotation");
            case StockMarket::XNSE:
                return QObject::tr("(IN) National Stock Exchange of India");
            case StockMarket::XNYS:
                return QObject::tr("(US) New York Stock Exchange");
            case StockMarket::XPAR:
                return QObject::tr("(FR) Euronext Paris");
            case StockMarket::XSHE:
                return QObject::tr("(CN) Shenzhen Stock Exchange");
            case StockMarket::XSHG:
                return QObject::tr("(CN) Shanghai Stock Exchange");
            case StockMarket::XSWX:
                return QObject::tr("(CH) SIX Swiss Exchange");
            case StockMarket::XTAI:
                return QObject::tr("(TW) Taiwan Stock Exchange");
            case StockMarket::XTSE:
                return QObject::tr("(CA) Toronto Stock Exchange");
            default:
                return QString();
            }
        }

        StockMarket Util::getStockMarket(const QString &text)
        {
            if(Util::stockMarketSymbol(StockMarket::BMEX) == text) {
                return StockMarket::BMEX;
            } else if(Util::stockMarketSymbol(StockMarket::BVMF) == text) {
                return StockMarket::BVMF;
            } else if(Util::stockMarketSymbol(StockMarket::MISX) == text) {
                return StockMarket::MISX;
            } else if(Util::stockMarketSymbol(StockMarket::NAPA) == text) {
                return StockMarket::NAPA;
            } else if(Util::stockMarketSymbol(StockMarket::XAMS) == text) {
                return StockMarket::XAMS;
            } else if(Util::stockMarketSymbol(StockMarket::XASX) == text) {
                return StockMarket::XASX;
            } else if(Util::stockMarketSymbol(StockMarket::XBOM) == text) {
                return StockMarket::XBOM;
            } else if(Util::stockMarketSymbol(StockMarket::XFRA) == text) {
                return StockMarket::XFRA;
            } else if(Util::stockMarketSymbol(StockMarket::XIST) == text) {
                return StockMarket::XIST;
            } else if(Util::stockMarketSymbol(StockMarket::XLON) == text) {
                return StockMarket::XLON;
            } else if(Util::stockMarketSymbol(StockMarket::XMIL) == text) {
                return StockMarket::XMIL;
            } else if(Util::stockMarketSymbol(StockMarket::XHKG) == text) {
                return StockMarket::XHKG;
            } else if(Util::stockMarketSymbol(StockMarket::XJPX) == text) {
                return StockMarket::XJPX;
            } else if(Util::stockMarketSymbol(StockMarket::XJSE) == text) {
                return StockMarket::XJSE;
            } else if(Util::stockMarketSymbol(StockMarket::XKRX) == text) {
                return StockMarket::XKRX;
            } else if(Util::stockMarketSymbol(StockMarket::XNAS) == text) {
                return StockMarket::XNAS;
            } else if(Util::stockMarketSymbol(StockMarket::XNSE) == text) {
                return StockMarket::XNSE;
            } else if(Util::stockMarketSymbol(StockMarket::XNYS) == text) {
                return StockMarket::XNYS;
            } else if(Util::stockMarketSymbol(StockMarket::XPAR) == text) {
                return StockMarket::XPAR;
            } else if(Util::stockMarketSymbol(StockMarket::XSHE) == text) {
                return StockMarket::XSHE;
            } else if(Util::stockMarketSymbol(StockMarket::XSHG) == text) {
                return StockMarket::XSHG;
            } else if(Util::stockMarketSymbol(StockMarket::XSWX) == text) {
                return StockMarket::XSWX;
            } else if(Util::stockMarketSymbol(StockMarket::XTAI) == text) {
                return StockMarket::XTAI;
            } else if(Util::stockMarketSymbol(StockMarket::XTSE) == text) {
                return StockMarket::XTSE;
            } else {
                return StockMarket::InvalidStockMarket;
            }
        }

        const QRegularExpression Util::bondISINRegularExpression()
        {
            QRegularExpression exp("^[a-zA-Z]{2}[a-zA-Z0-9]{9}[0-9]{1,3}$");
            return exp;
        }

        const QRegularExpression Util::fundCodeRegularExpression()
        {
            QRegularExpression exp("^[a-zA-Z0-9]{3,5}$");
            return exp;
        }

        const QRegularExpression Util::fundNameRegularExpression()
        {
            QRegularExpression exp("^([a-zA-Z0-9]+\\.? ?)+$");
            return exp;
        }

        const QRegularExpression Util::stockSymbolRegularExpression()
        {
            QRegularExpression exp("^[a-zA-Z]+$");
            return exp;
        }

        const QRegularExpression Util::stockNameRegularExpression()
        {
            QRegularExpression exp("^([a-zA-Z0-9]+\\.? ?)+$");
            return exp;
        }

    }
}
