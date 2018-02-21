#include "investpor/core/util.h"

#include <cmath>

#include <QObject>
#include <QMetaEnum>
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
            QMetaObject metaObject = Util::staticMetaObject;
            QMetaEnum metaEnum = metaObject.enumerator(metaObject.indexOfEnumerator("Investment"));

            return QString(metaEnum.valueToKey(investment));
        }

        const QString Util::currencySymbol(const Currency &currency)
        {
            QMetaObject metaObject = Util::staticMetaObject;
            QMetaEnum metaEnum = metaObject.enumerator(metaObject.indexOfEnumerator("Currency"));

            switch (currency) {
            case Currency::ARS:
            case Currency::AUD:
            case Currency::BRL:
            case Currency::CAD:
            case Currency::CHF:
            case Currency::CNY:
            case Currency::EUR:
            case Currency::GBP:
            case Currency::HKD:
            case Currency::IDR:
            case Currency::INR:
            case Currency::JPY:
            case Currency::KRW:
            case Currency::MXN:
            case Currency::PLN:
            case Currency::QAR:
            case Currency::RUB:
            case Currency::SAR:
            case Currency::TND:
            case Currency::TRY:
            case Currency::USD:
            case Currency::ZAR:

                //Cryptocurrency list begins
            case Currency::BCH:
            case Currency::DASH:
            case Currency::ETC:
            case Currency::ETH:
            case Currency::LTC:
            case Currency::MIOTA:
            case Currency::XBT:
            case Currency::XRP:
                return QString(metaEnum.valueToKey(currency)).toUpper();
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

                //Cryptocurrency list begins
            case Currency::BCH:
                return QObject::tr("Bitcoin Cash");
            case Currency::DASH:
                return QObject::tr("Dash");
            case Currency::ETC:
                return QObject::tr("Ethereum Classic");
            case Currency::ETH:
                return QObject::tr("Ethereum");
            case Currency::LTC:
                return QObject::tr("Litecoin");
            case Currency::MIOTA:
                return QObject::tr("IOTA");
            case Currency::XBT:
                return QObject::tr("Bitcoin");
            case Currency::XRP:
                return QObject::tr("Ripple");
            default:
                return QString();
            }
        }

        Util::Currency Util::getCurrency(const QString &text)
        {
            QMetaObject metaObject = Util::staticMetaObject;
            QMetaEnum metaEnum = metaObject.enumerator(metaObject.indexOfEnumerator("Currency"));

            switch (metaEnum.keysToValue(text.toLatin1().toUpper())) {
            case Currency::ARS:
            case Currency::AUD:
            case Currency::BRL:
            case Currency::CAD:
            case Currency::CHF:
            case Currency::CNY:
            case Currency::EUR:
            case Currency::GBP:
            case Currency::HKD:
            case Currency::IDR:
            case Currency::INR:
            case Currency::JPY:
            case Currency::KRW:
            case Currency::MXN:
            case Currency::PLN:
            case Currency::QAR:
            case Currency::RUB:
            case Currency::SAR:
            case Currency::TND:
            case Currency::TRY:
            case Currency::USD:
            case Currency::ZAR:

                //Cryptocurrency list begins
            case Currency::BCH:
            case Currency::DASH:
            case Currency::ETC:
            case Currency::ETH:
            case Currency::LTC:
            case Currency::MIOTA:
            case Currency::XBT:
            case Currency::XRP:
                return static_cast<Util::Currency>(metaEnum.keyToValue(text.toLatin1().toUpper()));
            default:
                return Util::Currency::InvalidCurrency;
            }
        }

        const QString Util::goldSymbol(const Gold &gold)
        {
            QMetaObject metaObject = Util::staticMetaObject;
            QMetaEnum metaEnum = metaObject.enumerator(metaObject.indexOfEnumerator("Gold"));

            switch (gold) {
            case Gold::GRAMS:
            case Gold::ONS:
                return QString(metaEnum.valueToKey(gold)).toUpper();
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

        Util::Gold Util::getGold(const QString &text)
        {
            QMetaObject metaObject= Util::staticMetaObject;
            QMetaEnum metaEnum = metaObject.enumerator(metaObject.indexOfEnumerator("Gold"));

            switch (metaEnum.keysToValue(text.toLatin1().toUpper())) {
            case Gold::GRAMS:
            case Gold::ONS:
                return static_cast<Util::Gold>(metaEnum.keyToValue(text.toLatin1().toUpper()));
            default:
                return Util::Gold::InvalidGold;
            }
        }

        const QString Util::operationCode(const Operation &operation)
        {
            QMetaObject metaObject = Util::staticMetaObject;
            QMetaEnum metaEnum = metaObject.enumerator(metaObject.indexOfEnumerator("Operation"));

            switch (operation) {
            case Operation::BUY:
            case Operation::SELL:
                return QString(metaEnum.valueToKey(operation)).toUpper();
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

        Util::Operation Util::getOperation(const QString &text)
        {
            QMetaObject metaObject = Util::staticMetaObject;
            QMetaEnum metaEnum = metaObject.enumerator(metaObject.indexOfEnumerator("Operation"));

            switch (metaEnum.keysToValue(text.toLatin1().toUpper())) {
            case Operation::BUY:
            case Operation::SELL:
                return static_cast<Operation>(metaEnum.keysToValue(text.toLatin1().toUpper()));
            default:
                return Operation::InvalidOperation;
            }
        }

        const QString Util::stockMarketSymbol(const StockMarket &market)
        {
            QMetaObject metaObject =Util::staticMetaObject;
            QMetaEnum metaEnum = metaObject.enumerator(metaObject.indexOfEnumerator("StockMarket"));

            switch (market) {
            case StockMarket::BMEX:
            case StockMarket::BVMF:
            case StockMarket::MISX:
            case StockMarket::NAPA:
            case StockMarket::XAMS:
            case StockMarket::XASX:
            case StockMarket::XBOM:
            case StockMarket::XFRA:
            case StockMarket::XIST:
            case StockMarket::XLON:
            case StockMarket::XMIL:
            case StockMarket::XHKG:
            case StockMarket::XJPX:
            case StockMarket::XJSE:
            case StockMarket::XKRX:
            case StockMarket::XNAS:
            case StockMarket::XNSE:
            case StockMarket::XNYS:
            case StockMarket::XPAR:
            case StockMarket::XSHE:
            case StockMarket::XSHG:
            case StockMarket::XSWX:
            case StockMarket::XTAI:
            case StockMarket::XTSE:
                return QString(metaEnum.valueToKey(market)).toUpper();
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

        Util::StockMarket Util::getStockMarket(const QString &text)
        {
            QMetaObject metaObject = Util::staticMetaObject;
            QMetaEnum metaEnum = metaObject.enumerator(metaObject.indexOfEnumerator("StockMarket"));

            switch (metaEnum.keysToValue(text.toLatin1().toUpper())) {
            case StockMarket::BMEX:
            case StockMarket::BVMF:
            case StockMarket::MISX:
            case StockMarket::NAPA:
            case StockMarket::XAMS:
            case StockMarket::XASX:
            case StockMarket::XBOM:
            case StockMarket::XFRA:
            case StockMarket::XIST:
            case StockMarket::XLON:
            case StockMarket::XMIL:
            case StockMarket::XHKG:
            case StockMarket::XJPX:
            case StockMarket::XJSE:
            case StockMarket::XKRX:
            case StockMarket::XNAS:
            case StockMarket::XNSE:
            case StockMarket::XNYS:
            case StockMarket::XPAR:
            case StockMarket::XSHE:
            case StockMarket::XSHG:
            case StockMarket::XSWX:
            case StockMarket::XTAI:
            case StockMarket::XTSE:
                return static_cast<Util::StockMarket>(metaEnum.keyToValue(text.toLatin1().toUpper()));
            default:
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
