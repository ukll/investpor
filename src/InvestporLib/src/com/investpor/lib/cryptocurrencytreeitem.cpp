#include "lib/cryptocurrencytreeitem.h"

namespace lib {

    CryptocurrencyTreeItem::CryptocurrencyTreeItem() :
        m_cryptocurrency(Util::InvalidCurrency),
        m_operation(Util::InvalidOperation),
        m_referenceCurrency(Util::InvalidCurrency),
        m_price(0.0),
        m_amount(0.0),
        m_extraExpenses(0.0),
        m_goalPrice(0.0)
    {

    }

}
