#include "investpor/gui/cryptocurrencytablemodel.h"

#include "investpor/core/util.h"

using investpor::core::Util;
using investpor::core::CryptocurrencyTransaction;

namespace investpor {

    namespace gui {

        CryptocurrencyTableModel::CryptocurrencyTableModel(QList<CryptocurrencyTransaction> list, QObject *parent) :
            TableModel(parent), transactionList(list)
        {

        }

        void CryptocurrencyTableModel::updateTransactionList(QList<CryptocurrencyTransaction> list)
        {
            beginResetModel();

            transactionList = list;

            endResetModel();
        }

        double CryptocurrencyTableModel::totalBuys() const
        {
            double buys = 0;

            QList<CryptocurrencyTransaction>::const_iterator iter;
            for(iter = transactionList.cbegin(); iter < transactionList.cend(); ++iter)
            {
                if(iter->getOperationType() == Operation::BUY)
                {
                    buys += (iter->getPrice() * iter->getAmount());
                }
            }

            return buys;
        }

        double CryptocurrencyTableModel::totalSells() const
        {
            double sells = 0;

            QList<CryptocurrencyTransaction>::const_iterator iter;
            for(iter = transactionList.cbegin(); iter < transactionList.cend(); ++iter)
            {
                if(iter->getOperationType() == Operation::SELL)
                {
                    sells += (iter->getPrice() * iter->getAmount());
                }
            }

            return sells;
        }

        QVariant CryptocurrencyTableModel::headerData(int section, Qt::Orientation orientation, int role) const
        {
            if(Qt::DisplayRole != role)
            {
                return QVariant();
            }

            if(Qt::Vertical == orientation)
            {
                return QVariant();
            }

            switch (section) {
            case 0:
                return QString("Cryptocurrency");
            case 1:
                return QString("Transaction ID");
            case 2:
                return QString("Operation Type");
            case 3:
                return QString("Price");
            case 4:
                return QString("Amount");
            case 5:
                return QString("Goal Price");
            case 6:
                return QString("Date and Time");
            default:
                return QVariant();
            }
        }

        QVariant CryptocurrencyTableModel::data(const QModelIndex &index, int role) const
        {
            if(Qt::DisplayRole != role)
            {
                return QVariant();
            }

            switch (index.column()) {
            case 0:
                return Util::cryptoCurrencySymbol(transactionList.at(index.row()).getCryptocurrency());
            case 1:
                return transactionList.at(index.row()).getTransactionId();
            case 2:
                return Util::operationName(transactionList.at(index.row()).getOperationType());
            case 3:
                return transactionList.at(index.row()).getPrice();
            case 4:
                return transactionList.at(index.row()).getAmount();
            case 5:
                return transactionList.at(index.row()).getGoalPrice();
            case 6:
                return transactionList.at(index.row()).getOperationDateTime().toString(Qt::ISODate);
            default:
                return QVariant();
            }
        }

    }

}