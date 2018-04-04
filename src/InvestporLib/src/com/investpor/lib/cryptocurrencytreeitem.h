#ifndef CRYPTOCURRENCYTREEITEM_H
#define CRYPTOCURRENCYTREEITEM_H

#include "lib/abstracttreeitem.h"
#include "lib/util.h"

namespace lib {

    class CryptocurrencyTreeItem final : public AbstractTreeItem
    {
    public:
        explicit CryptocurrencyTreeItem();

        //Cryptocurrency transaction related functions
        Util::Currency getCryptocurrency() const { return m_cryptocurrency; }
        void setCryptocurrency(const Util::Currency &ccurrency) { m_cryptocurrency = ccurrency; }
        Util::Operation getOperation() const { return m_operation; }
        void setOperation(const Util::Operation &op) { m_operation = op; }
        Util::Currency getReferenceCurrency() const { return m_referenceCurrency; }
        void setReferenceCurrency(const Util::Currency &refCurrency) { m_referenceCurrency = refCurrency; }
        double getPrice() const { return m_price; }
        void setPrice(const double &prc) { m_price = prc; }
        double getAmount() const { return m_amount; }
        void setAmount(const double &amnt) { m_amount = amnt; }
        double getExtraExpenses() const { return m_extraExpenses; }
        void setExtraExpenses(const double &eExpenses) { m_extraExpenses = eExpenses; }
        double getGoalPrice() const { return m_goalPrice; }
        void setGoalPrice(const double &gPrice) { m_goalPrice = gPrice; }
        QDateTime getDateTime() const { return m_dateTime; }
        void setDateTime(const QDateTime &dtm) { m_dateTime = dtm; }

    private:
        Util::Currency m_cryptocurrency;
        Util::Operation m_operation;
        Util::Currency m_referenceCurrency;
        double m_price;
        double m_amount;
        double m_extraExpenses;
        double m_goalPrice;
        QDateTime m_dateTime;
    };

}
#endif // CRYPTOCURRENCYTREEITEM_H
