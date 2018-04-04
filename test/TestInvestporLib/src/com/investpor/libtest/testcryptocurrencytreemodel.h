#ifndef TESTCRYPTOCURRENCYTREEMODEL_H
#define TESTCRYPTOCURRENCYTREEMODEL_H

#include "lib/cryptocurrencytreemodel.h"

#include <QtTest>

namespace libtest {

    class TestCryptocurrencyTreeModel : public QObject
    {
        Q_OBJECT

    public:
        TestCryptocurrencyTreeModel();
        ~TestCryptocurrencyTreeModel();

    private slots:
        void initTestCase();
        void cleanupTestCase();
    };

}

#endif // TESTCRYPTOCURRENCYTREEMODEL_H
