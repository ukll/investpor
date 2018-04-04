#ifndef TESTUTIL_H
#define TESTUTIL_H

#include <QtTest>

namespace libtest {

    class TestUtil : public QObject
    {
        Q_OBJECT

    public:
        TestUtil();
        ~TestUtil();

    private slots:
        void testCheckDoubleEqualityIn6DecPoints();
        void testCheckDoubleEqualityIn10DecPoints();
        void testGetCurrencyName();
        void testGetGoldName();
        void testGetOperationName();
        void testGetStockMarketName();
        void testISINRegularExpression();
        void testFundCodeRegularExpression();
        void testFundNameRegularExpression();
        void testStockSymbolRegularExpression();
        void testStockNameRegularExpression();
    };

}

#endif // TESTUTIL_H
