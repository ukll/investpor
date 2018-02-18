#include "investpor/gui/stocktablemodel.h"

#include "investpor/core/util.h"

#include <QBrush>
#include <QColor>

using investpor::core::Util;

namespace investpor {

    namespace gui {

        StockTableModel::StockTableModel(QList<StockTransaction> list, QObject *parent) :
            TableModel(parent), transactionList(list)
        {

        }

        void StockTableModel::updateTransactionList(QList<core::StockTransaction> list)
        {
            beginResetModel();

            transactionList = list;

            endResetModel();
        }

        double StockTableModel::totalBuys() const
        {
            double buys = 0.0;

            QList<StockTransaction>::const_iterator iter;
            for(iter = transactionList.cbegin(); iter < transactionList.cend(); ++iter)
            {
                if(Util::Operation::BUY == iter->getOperationType())
                {
                    buys += ((iter->getPrice() + (iter->getPrice() * iter->getCommissionRate())) * iter->getCount());
                }
            }

            return buys;
        }

        double StockTableModel::totalSells() const
        {
            double sells = 0.0;

            QList<StockTransaction>::const_iterator iter;
            for(iter = transactionList.cbegin(); iter < transactionList.cend(); ++iter)
            {
                if(Util::Operation::SELL == iter->getOperationType())
                {
                    sells += ((iter->getPrice() + (iter->getPrice() * iter->getCommissionRate())) * iter->getCount());
                }
            }

            return sells;
        }

        QVariant StockTableModel::headerData(int section, Qt::Orientation orientation, int role) const
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
                return QString("Market");
            case 1:
                return QString("Symbol");
            case 2:
                return QString("Name");
            case 3:
                return QString("Operation Type");
            case 4:
                return QString("Price");
            case 5:
                return QString("Count");
            case 6:
                return QString("Commission Rate");
            case 7:
                return QString("Goal Price");
            case 8:
                return QString("Date and Time");
            default:
                return QVariant();
            }
        }

        QVariant StockTableModel::data(const QModelIndex &index, int role) const
        {
            if(Qt::TextAlignmentRole == role)
            {
                return Qt::AlignCenter;
            }

            if(Qt::BackgroundRole == role)
            {
                if(Util::Operation::BUY == transactionList.at(index.row()).getOperationType()) {
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
                return Util::stockMarketSymbol(transactionList.at(index.row()).getStockMarket()).toUpper();
            case 1:
                return transactionList.at(index.row()).getStockSymbol().toUpper();
            case 2:
                return transactionList.at(index.row()).getStockName().toUpper();
            case 3:
                return Util::operationName(transactionList.at(index.row()).getOperationType());
            case 4:
                return QString::number(transactionList.at(index.row()).getPrice(), 'f');
            case 5:
                return transactionList.at(index.row()).getCount();
            case 6:
                return QString::number(transactionList.at(index.row()).getCommissionRate(), 'f');
            case 7:
                return QString::number(transactionList.at(index.row()).getGoalPrice(), 'f');
            case 8:
                return transactionList.at(index.row()).getOperationDateTime().toString(Qt::ISODate);
            default:
                return QVariant();
            }
        }

    }

}
