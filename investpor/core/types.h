#ifndef TYPES_H
#define TYPES_H

namespace investpor {

    namespace core {

        enum Investment {
            CryptoCurrencyInvestment = 0, DiscountBondInvestment, ExchangeInvestment,
            FundInvestment, GoldInvestment, StockInvestment
        };

        enum Cryptocurrency {
            InvalidCryptocurrency = 0, ETC, ETH, LTC, IOT, XBT, XRP
        };

        enum Currency {
            InvalidCurrency = 0, AUD, CAD, CNY, EUR, TRY, USD
        };

        enum Gold {
            InvalidGold = 0, GRAMS, ONS
        };

        enum Operation {
            InvalidOperation = 0, BUY, SELL
        };

        enum StockMarket {
            InvalidStockMarket = 0, BIST, NASDAQ, NYSE
        };

    }

}

#endif // TYPES_H
