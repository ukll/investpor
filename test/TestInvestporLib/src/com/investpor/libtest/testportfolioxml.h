#ifndef TESTPORTFOLIOXML_H
#define TESTPORTFOLIOXML_H

#include "lib/portfolioxml.h"

#include <QtTest>

namespace libtest {

    class TestPortfolioXML : public QObject
    {
        Q_OBJECT

    public:
        TestPortfolioXML();
        ~TestPortfolioXML();

    private slots:
        void initTestCase();
        void cleanupTestCase();
        void testCreatePortfolio();
    };

}

#endif // TESTPORTFOLIOXML_H
