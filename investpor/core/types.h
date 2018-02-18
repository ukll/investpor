#ifndef TYPES_H
#define TYPES_H

namespace investpor {

    namespace core {

        enum Investment {
            CryptoCurrencyInvestment = 0, DiscountBondInvestment, ExchangeInvestment,
            FundInvestment, GoldInvestment, StockInvestment
        };

        enum Cryptocurrency {
            InvalidCryptocurrency = 0, BCH, DASH, ETC, ETH, LTC, MIOTA, XBT, XRP
        };

        enum Currency {
            InvalidCurrency = 0, ARS, AUD, BRL, CAD, CHF, CNY, EUR, GBP,
            HKD, IDR, INR, JPY, KRW, MXN, PLN, QAR, RUB, SAR, TND, TRY, USD, ZAR
        };

        enum Gold {
            InvalidGold = 0, GRAMS, ONS
        };

        enum Operation {
            InvalidOperation = 0, BUY, SELL
        };

        enum StockMarket {
            InvalidStockMarket = 0,
            BMEX, BVMF, MISX, NAPA, XAMS, XASX, XBOM, XFRA,
            XIST, XLON, XMIL, XHKG, XJPX, XJSE, XKRX, XNAS,
            XNSE, XNYS, XPAR, XSHE, XSHG, XSWX, XTAI, XTSE
        };

    }

}

#endif // TYPES_H
