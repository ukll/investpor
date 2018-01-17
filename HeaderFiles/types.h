#ifndef TYPES_H
#define TYPES_H

namespace Investpor {

    enum Cryptocurrency {
        BTC = 0, ETC, ETH, LTC, MIOTA, XRP
    };

    enum Currency {
        AUD = 0, CAD, CNY, EUR, TL, USD
    };

    enum Gold {
        GRAMS = 0, ONS
    };

    enum Operation {
        BUY = 0, SELL
    };

    enum StockMarket {
        BIST = 0, NASDAQ, NYSE
    };
}

#endif // TYPES_H
