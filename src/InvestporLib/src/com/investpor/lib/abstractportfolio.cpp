#include "lib/abstractportfolio.h"

namespace lib {

    AbstractPortfolio::AbstractPortfolio(const QString &filePath, QObject *parent) :
        QObject(parent),
        m_portfolioFile(new QFile(filePath, this)),
        m_cryptocurrencyModel(nullptr), m_cryptocurrencyProxyModel(nullptr)//,
      //        m_discountBondModel(nullptr), m_discountBondProxyModel(nullptr),
      //        m_exchangeModel(nullptr), m_exchangeProxyModel(nullptr),
      //        m_fundModel(nullptr), m_fundProxyModel(nullptr),
      //        m_goldModel(nullptr), m_goldProxyModel(nullptr),
      //        m_stockModel(nullptr), m_stockProxyModel(nullptr)
    {

    }
}
