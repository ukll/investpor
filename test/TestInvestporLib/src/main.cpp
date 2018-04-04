#include <QtTest>

#include "libtest/testutil.h"
#include "libtest/testcryptocurrencytreemodel.h"
#include "libtest/testportfolioxml.h"

using namespace libtest;

int main(int argc, char *argv[])
{
    int status = 0;
    auto ASSERT_TEST = [&status, argc, argv](QObject* obj) {
        status |= QTest::qExec(obj, argc, argv);
        delete obj;
    };

    ASSERT_TEST(new TestUtil());
    ASSERT_TEST(new TestCryptocurrencyTreeModel());
    ASSERT_TEST(new TestPortfolioXML());

    return status;
}
