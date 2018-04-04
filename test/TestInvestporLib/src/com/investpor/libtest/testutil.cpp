#include "libtest/testutil.h"

#include "lib/util.h"

#include <QRegularExpression>
#include <QRegularExpressionMatch>

using namespace lib;

namespace libtest {

    TestUtil::TestUtil()
    {

    }

    TestUtil::~TestUtil()
    {

    }

    void TestUtil::testCheckDoubleEqualityIn6DecPoints()
    {
        QVERIFY2(Util::checkDoubleEqualityIn6DecPoints(1.0, 1.0),
                 "Could not detect equality in 1 dec points.");
        QEXPECT_FAIL("", "Catches difference in 1 decimal point.", Continue);
        QVERIFY(Util::checkDoubleEqualityIn6DecPoints(0.0, 0.1));

        QVERIFY2(Util::checkDoubleEqualityIn6DecPoints(1.00, 1.00),
                 "Could not detect equality in 2 dec points.");
        QEXPECT_FAIL("", "Catches difference in 2 decimal points.", Continue);
        QVERIFY(Util::checkDoubleEqualityIn6DecPoints(0.00, 0.01));

        QVERIFY2(Util::checkDoubleEqualityIn6DecPoints(1.000, 1.000),
                 "Could not detect equality in 3 dec points.");
        QEXPECT_FAIL("", "Catches difference in 3 decimal points.", Continue);
        QVERIFY(Util::checkDoubleEqualityIn6DecPoints(0.000, 0.001));

        QVERIFY2(Util::checkDoubleEqualityIn6DecPoints(1.0000, 1.0000),
                 "Could not detect equality in 4 dec points.");
        QEXPECT_FAIL("", "Catches difference in 4 decimal points.", Continue);
        QVERIFY(Util::checkDoubleEqualityIn6DecPoints(0.0000, 0.0001));

        QVERIFY2(Util::checkDoubleEqualityIn6DecPoints(1.00000, 1.00000),
                 "Could not detect equality in 5 dec points.");
        QEXPECT_FAIL("", "Catches difference in 5 decimal points.", Continue);
        QVERIFY(Util::checkDoubleEqualityIn6DecPoints(0.00000, 0.00001));

        QVERIFY2(Util::checkDoubleEqualityIn6DecPoints(1.000000, 1.000000),
                 "Could not detect equality in 6 dec points.");
        QEXPECT_FAIL("", "Catches difference in 6 decimal points.", Continue);
        QVERIFY(Util::checkDoubleEqualityIn6DecPoints(0.000000, 0.000001));

        QVERIFY2(Util::checkDoubleEqualityIn6DecPoints(1.0000000, 1.0000000),
                 "Could not detect equality in 7 dec points.");
        QVERIFY2(Util::checkDoubleEqualityIn6DecPoints(0.0000000, 0.0000001),
                 "Problem with ignoring inequality in 7 dec points.");
    }

    void TestUtil::testCheckDoubleEqualityIn10DecPoints()
    {
        QVERIFY2(Util::checkDoubleEqualityIn10DecPoints(1.0, 1.0),
                "Could not detect equality in 1 dec points.");
        QEXPECT_FAIL("", "Catches difference in 1 decimal point.", Continue);
        QVERIFY(Util::checkDoubleEqualityIn10DecPoints(0.0, 0.1));

        QVERIFY2(Util::checkDoubleEqualityIn10DecPoints(1.00, 1.00),
                "Could not detect equality in 2 dec points.");
        QEXPECT_FAIL("", "Catches difference in 2 decimal points.", Continue);
        QVERIFY(Util::checkDoubleEqualityIn10DecPoints(0.00, 0.01));

        QVERIFY2(Util::checkDoubleEqualityIn10DecPoints(1.000, 1.000),
                "Could not detect equality in 3 dec points.");
        QEXPECT_FAIL("", "Catches difference in 3 decimal points.", Continue);
        QVERIFY(Util::checkDoubleEqualityIn10DecPoints(0.000, 0.001));

        QVERIFY2(Util::checkDoubleEqualityIn10DecPoints(1.0000, 1.0000),
                "Could not detect equality in 4 dec points.");
        QEXPECT_FAIL("", "Catches difference in 4 decimal points.", Continue);
        QVERIFY(Util::checkDoubleEqualityIn10DecPoints(0.0000, 0.0001));

        QVERIFY2(Util::checkDoubleEqualityIn10DecPoints(1.00000, 1.00000),
                "Could not detect equality in 5 dec points.");
        QEXPECT_FAIL("", "Catches difference in 5 decimal points.", Continue);
        QVERIFY(Util::checkDoubleEqualityIn10DecPoints(0.00000, 0.00001));

        QVERIFY2(Util::checkDoubleEqualityIn10DecPoints(1.000000, 1.000000),
                 "Could not detect equality in 6 dec points.");
        QEXPECT_FAIL("", "Catches difference in 6 decimal points.", Continue);
        QVERIFY(Util::checkDoubleEqualityIn10DecPoints(0.000000, 0.000001));

        QVERIFY2(Util::checkDoubleEqualityIn10DecPoints(1.0000000, 1.0000000),
                 "Could not detect equality in 7 dec points.");
        QEXPECT_FAIL("", "Catches difference in 7 decimal points.", Continue);
        QVERIFY(Util::checkDoubleEqualityIn10DecPoints(0.0000000, 0.0000001));

        QVERIFY2(Util::checkDoubleEqualityIn10DecPoints(1.00000000, 1.00000000),
                 "Could not detect equality in 8 dec points.");
        QEXPECT_FAIL("", "Catches difference in 8 decimal points.", Continue);
        QVERIFY(Util::checkDoubleEqualityIn10DecPoints(0.00000000, 0.00000001));

        QVERIFY2(Util::checkDoubleEqualityIn10DecPoints(1.000000000, 1.000000000),
                "Could not detect equality in 9 dec points.");
        QEXPECT_FAIL("", "Catches difference in 9 decimal points.", Continue);
        QVERIFY(Util::checkDoubleEqualityIn10DecPoints(0.000000000, 0.000000001));

        QVERIFY2(Util::checkDoubleEqualityIn10DecPoints(1.0000000000, 1.0000000000),
                "Could not detect equality in 10 dec points.");
        QEXPECT_FAIL("", "Catches difference in 10 decimal points.", Continue);
        QVERIFY(Util::checkDoubleEqualityIn10DecPoints(0.0000000000, 0.0000000001));

        QVERIFY2(Util::checkDoubleEqualityIn10DecPoints(1.00000000000, 1.00000000000),
                "Could not detect equality in 11 dec points.");
        QVERIFY2(Util::checkDoubleEqualityIn10DecPoints(0.00000000000, 0.00000000001),
                 "Problem with ignoring inequality in 11 dec points.");
    }

    void TestUtil::testGetCurrencyName()
    {
        //Invalid currency must have no name.
        QCOMPARE(Util::getCurrencyName(Util::InvalidCurrency), QString());

        //Try to catch invalid currency creation.
        QCOMPARE(Util::getCurrencyName(static_cast<Util::Currency>(-1000)), QString());
    }

    void TestUtil::testGetGoldName()
    {
        //Invalid gold must have no name.
        QCOMPARE(Util::getGoldName(Util::InvalidGold), QString());

        //Try to catch invalid gold creation.
        QCOMPARE(Util::getGoldName(static_cast<Util::Gold>(1000)), QString());
    }

    void TestUtil::testGetOperationName()
    {
        //Invalid operation must have no name.
        QCOMPARE(Util::getOperationName(Util::InvalidOperation), QString());

        //Try to catch invalid operation creation.
        QCOMPARE(Util::getOperationName(static_cast<Util::Operation>(1000)), QString());
    }

    void TestUtil::testGetStockMarketName()
    {
        //Invalid stock market name.
        QCOMPARE(Util::getStockMarketName(Util::InvalidStockMarket), QString());

        //Try to catch invalid stock market creation.
        QCOMPARE(Util::getStockMarketName(static_cast<Util::StockMarket>(-1000)), QString());
    }

    void TestUtil::testISINRegularExpression()
    {
        QRegularExpression reg = Util::getISINRegularExpression();
        QVERIFY2(reg.isValid(), "ISIN regular expression is not valid.");

        QRegularExpressionMatch regMatch;
        regMatch = reg.match("trT010120T11");
        QEXPECT_FAIL("", "Catches lowercase letters in country code part.", Continue);
        QVERIFY(regMatch.hasMatch());

        regMatch = reg.match("99T010120T11");
        QEXPECT_FAIL("", "Catches digits in country code part.", Continue);
        QVERIFY(regMatch.hasMatch());

        regMatch = reg.match("?.T010120T11");
        QEXPECT_FAIL("", "Catches invalid characters in country code part.", Continue);
        QVERIFY(regMatch.hasMatch());

        regMatch = reg.match("TRt010120t11");
        QEXPECT_FAIL("", "Catches lowercase letters in NSIN part.", Continue);
        QVERIFY(regMatch.hasMatch());

        regMatch = reg.match("TR?010120.11");
        QEXPECT_FAIL("", "Catches invalid characters in NSIN part.", Continue);
        QVERIFY(regMatch.hasMatch());

        regMatch = reg.match("TRT010120T1A");
        QEXPECT_FAIL("", "Catches letters in control part.", Continue);
        QVERIFY(regMatch.hasMatch());

        regMatch = reg.match("TRT010120T1.");
        QEXPECT_FAIL("", "Catches invalid characters in control part.", Continue);
        QVERIFY(regMatch.hasMatch());

        regMatch = reg.match("TRT010120T11");
        QVERIFY2(regMatch.hasMatch(), "Problem with identifying valid ISIN code.");
    }

    void TestUtil::testFundCodeRegularExpression()
    {
        QRegularExpression reg = Util::getFundCodeRegularExpression();
        QVERIFY2(reg.isValid(), "Fund code regular expression is not valid.");

        QRegularExpressionMatch regMatch;
        regMatch = reg.match("AKu");
        QEXPECT_FAIL("", "Catches lowercase letters in fund code.", Continue);
        QVERIFY(regMatch.hasMatch());

        regMatch = reg.match("AKU.");
        QEXPECT_FAIL("", "Catches invalid characters in fund code.", Continue);
        QVERIFY(regMatch.hasMatch());

        regMatch = reg.match("AKU");
        QVERIFY2(regMatch.hasMatch(), "Problem with identifying valid fund code containing only letters.");

        regMatch = reg.match("AKU2");
        QVERIFY2(regMatch.hasMatch(), "Problem with identifying valid fund code containing letters and numbers.");
    }

    void TestUtil::testFundNameRegularExpression()
    {
        QRegularExpression reg = Util::getFundNameRegularExpression();
        QVERIFY2(reg.isValid(), "Fund name regular expression is not valid");

        QRegularExpressionMatch regMatch;
        regMatch = reg.match("HSBC çğıöüşÇĞIÖÜŞ");
        QEXPECT_FAIL("", "Cathes non-English characters in fund name.", Continue);
        QVERIFY(regMatch.hasMatch());

        regMatch = reg.match("HSBC abcd");
        QEXPECT_FAIL("", "Catches lowercase letters in fund name.", Continue);
        QVERIFY(regMatch.hasMatch());

        regMatch = reg.match("HSBC EXCHANGE TRADED FUND (EUR.)");
        QVERIFY2(regMatch.hasMatch(), "Problem with identifying valid fund name.");
    }

    void TestUtil::testStockSymbolRegularExpression()
    {
        QRegularExpression reg = Util::getStockSymbolRegularExpression();
        QVERIFY2(reg.isValid(), "Stock symbol regular expression is not valid.");

        QRegularExpressionMatch regMatch;
        regMatch = reg.match("AAPl");
        QEXPECT_FAIL("", "Catches lowercase letters in stock symbol.", Continue);
        QVERIFY(regMatch.hasMatch());

        regMatch = reg.match("AAPL1");
        QEXPECT_FAIL("", "Catches digits in stock symbol.", Continue);
        QVERIFY(regMatch.hasMatch());

        regMatch = reg.match("AAPL?");
        QEXPECT_FAIL("", "Catches invalid characters in stock symbol.", Continue);
        QVERIFY(regMatch.hasMatch());

        regMatch = reg.match("AAPL");
        QVERIFY2(regMatch.hasMatch(), "Problem with identifying valid stock symbol.");
    }

    void TestUtil::testStockNameRegularExpression()
    {
        QRegularExpression reg = Util::getFundNameRegularExpression();
        QVERIFY2(reg.isValid(), "Stock name regular expression is not valid");

        QRegularExpressionMatch regMatch;
        regMatch = reg.match("APPLE çğıöüşÇĞIÖÜŞ");
        QEXPECT_FAIL("", "Cathes non-English characters in fund name.", Continue);
        QVERIFY(regMatch.hasMatch());

        regMatch = reg.match("APPLE abcd");
        QEXPECT_FAIL("", "Catches lowercase letters in fund name.", Continue);
        QVERIFY(regMatch.hasMatch());

        regMatch = reg.match("APPLE COMPUTER INC. (US)");
        QVERIFY2(regMatch.hasMatch(), "Problem with identifying valid fund name.");
    }

}
