#include "investpor/gui/cryptocurrencytablemodel.h"

#include "investpor/core/util.h"

#include <QBrush>
#include <QColor>

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
                if(iter->getOperationType() == Util::BUY)
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
                if(iter->getOperationType() == Util::SELL)
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
                return QString("Operation");
            case 2:
                return QString("Price");
            case 3:
                return QString("Amount");
            case 4:
                return QString("Goal Price");
            case 5:
                return QString("Date and Time");
            default:
                return QVariant();
            }
        }

        QVariant CryptocurrencyTableModel::data(const QModelIndex &index, int role) const
        {
            if(Qt::TextAlignmentRole == role)
            {
                return Qt::AlignCenter;
            }

            if(Qt::BackgroundRole == role)
            {
                if(Util::BUY == transactionList.at(index.row()).getOperationType()) {
                    return QBrush(QColor(0, 255, 0, 100));
                }
                return QBrush(QColor(255, 0, 0, 100));
            }

            if(Qt::DisplayRole != role)
            {
                return QVariant();
            }

            switch (index.column()) {
            case 0:
                return Util::currencySymbol(transactionList.at(index.row()).getCryptocurrency()).toUpper();
            case 1:
                return Util::operationName(transactionList.at(index.row()).getOperationType());
            case 2:
                return QString::number(transactionList.at(index.row()).getPrice(), 'f');
            case 3:
                return QString::number(transactionList.at(index.row()).getAmount(), 'f', 10);
            case 4:
                return QString::number(transactionList.at(index.row()).getGoalPrice(), 'f');
            case 5:
                return transactionList.at(index.row()).getOperationDateTime().toString(Qt::ISODate);
            default:
                return QVariant();
            }
        }

    }

}
