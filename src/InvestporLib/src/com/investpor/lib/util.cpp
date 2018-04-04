#include "lib/util.h"

#include <cmath>

#include <QObject>
#include <QRegularExpression>

namespace lib {

    bool Util::checkDoubleEqualityIn6DecPoints(const double &d1, const double &d2)
    {
        static const double EPSILON = 0.0000001;

        if(std::abs(d1 - d2) <= EPSILON || std::abs(d1 - d2) <= EPSILON * std::max(std::abs(d1), std::abs(d2))) {
            return true;
        } else {
            return false;
        }
    }

    bool Util::checkDoubleEqualityIn10DecPoints(const double &d1, const double &d2)
    {
        static const double EPSILON = 0.00000000001;

        if(std::abs(d1 - d2) <= EPSILON || std::abs(d1 - d2) <= EPSILON * std::max(std::abs(d1), std::abs(d2))) {
            return true;
        } else {
            return false;
        }
    }

    const QString Util::getCurrencyName(const Currency &currency)
    {
        switch (currency) {
        case Currency::ARS:
            return tr("Argentine Peso");
        case Currency::AUD:
            return tr("Australian Dollar");
        case Currency::BRL:
            return tr("Brazilian Real");
        case Currency::CAD:
            return tr("Canadian Dollar");
        case Currency::CHF:
            return tr("Swiss Franc");
        case Currency::CNY:
            return tr("Chinese Yuan Renminbi");
        case Currency::EUR:
            return tr("Euro");
        case Currency::GBP:
            return tr("British Pound");
        case Currency::HKD:
            return tr("Hong Kong Dollar");
        case Currency::IDR:
            return tr("Indonesian Rupiah");
        case Currency::INR:
            return tr("Indian Rupee");
        case Currency::JPY:
            return tr("Japanese Yen");
        case Currency::KRW:
            return tr("South Korean Won");
        case Currency::MXN:
            return tr("Mexican Peso");
        case Currency::PLN:
            return tr("Polish Zloty");
        case Currency::QAR:
            return tr("Qatari Riyal");
        case Currency::RUB:
            return tr("Russian Ruble");
        case Currency::SAR:
            return tr("Saudi Riyal");
        case Currency::TND:
            return tr("Indian Rupee");
        case Currency::TRY:
            return tr("Turkish Lira");
        case Currency::USD:
            return tr("United States Dollar");
        case Currency::ZAR:
            return tr("South African Rand");

            //Cryptocurrency names
        case Currency::BCH:
            return tr("Bitcoin Cash");
        case Currency::DASH:
            return tr("Dash");
        case Currency::ETC:
            return tr("Ethereum Classic");
        case Currency::ETH:
            return tr("Ethereum");
        case Currency::LTC:
            return tr("Litecoin");
        case Currency::MIOTA:
            return tr("IOTA");
        case Currency::XBT:
            return tr("Bitcoin");
        case Currency::XRP:
            return tr("Ripple");
        default:
            return QString();
        }
    }

    const QString Util::getGoldName(const Gold &gold)
    {
        switch (gold) {
        case Gold::GRAM:
            return tr("Gram");
        case Gold::OUNCE:
            return tr("Ounce");
        default:
            return QString();
        }
    }

    const QString Util::getOperationName(const Operation &operation)
    {
        switch (operation) {
        case Operation::BUY:
            return tr("Buy");
        case Operation::SELL:
            return tr("Sell");
        default:
            return QString();
        }
    }

    const QString Util::getStockMarketName(const StockMarket &market)
    {
        switch (market) {
        case StockMarket::BMEX:
            return tr("(ES) Bolsas y Mercados Españoles");
        case StockMarket::BVMF:
            return tr("(BR) Brasil, Bolsa, Balcão");
        case StockMarket::MISX:
            return tr("(RU) Moscow Exchange");
        case StockMarket::NAPA:
            return tr("(SE) NASDAQ Nordic");
        case StockMarket::XAMS:
            return tr("(NL) Euronext Amsterdam");
        case StockMarket::XASX:
            return tr("(AU) Australian Securities Exchange");
        case StockMarket::XBOM:
            return tr("(IN) Bombay Stock Exchange");
        case StockMarket::XFRA:
            return tr("(DE) Frankfurt Stock Exchange");
        case StockMarket::XIST:
            return tr("(TR) Borsa Istanbul");
        case StockMarket::XLON:
            return tr("(GB) London Stock Exchange");
        case StockMarket::XMIL:
            return tr("(IT) Milan Stock Exchange");
        case StockMarket::XHKG:
            return tr("(HK) Hong Kong Stock Exchange");
        case StockMarket::XJPX:
            return tr("(JP) Tokyo Stock Exchange");
        case StockMarket::XJSE:
            return tr("(ZA) Johannesburg Stock Exchange");
        case StockMarket::XKRX:
            return tr("(KR) Korea Exchange");
        case StockMarket::XNAS:
            return tr("(US) National Association of Securities Dealer Automated Quotation");
        case StockMarket::XNSE:
            return tr("(IN) National Stock Exchange of India");
        case StockMarket::XNYS:
            return tr("(US) New York Stock Exchange");
        case StockMarket::XPAR:
            return tr("(FR) Euronext Paris");
        case StockMarket::XSHE:
            return tr("(CN) Shenzhen Stock Exchange");
        case StockMarket::XSHG:
            return tr("(CN) Shanghai Stock Exchange");
        case StockMarket::XSWX:
            return tr("(CH) SIX Swiss Exchange");
        case StockMarket::XTAI:
            return tr("(TW) Taiwan Stock Exchange");
        case StockMarket::XTSE:
            return tr("(CA) Toronto Stock Exchange");
        default:
            return QString();
        }
    }

    const QRegularExpression Util::getISINRegularExpression()
    {
        QRegularExpression exp("\\A[A-Z]{2}[A-Z0-9]{9}\\d\\z");
        return exp;
    }

    const QRegularExpression Util::getFundCodeRegularExpression()
    {
        QRegularExpression exp("\\A[A-Z0-9]{3,5}\\z");
        return exp;
    }

    const QRegularExpression Util::getFundNameRegularExpression()
    {
        QRegularExpression exp("\\A[A-Z0-9\\.\\)\\( ]+\\z");
        return exp;
    }

    const QRegularExpression Util::getStockSymbolRegularExpression()
    {
        QRegularExpression exp("\\A[A-Z]{4,6}\\z");
        return exp;
    }

    const QRegularExpression Util::getStockNameRegularExpression()
    {
        QRegularExpression exp("\\A[A-Z0-9\\.\\)\\( ]+\\z");
        return exp;
    }

}
