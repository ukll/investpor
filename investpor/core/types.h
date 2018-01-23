#ifndef TYPES_H
#define TYPES_H

namespace investpor {

    namespace core {

        enum Cryptocurrency {
            ETC = 0, ETH, LTC, IOT, XBT, XRP
        };

        enum Currency {
            AUD = 0, CAD, CNY, EUR, TRY, USD
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

}

#endif // TYPES_H
