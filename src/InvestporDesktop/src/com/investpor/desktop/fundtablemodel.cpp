#include "desktop/fundtablemodel.h"

#include "lib/util.h"

#include <QBrush>
#include <QColor>

using lib::Util;
using lib::FundTransaction;

namespace desktop {

    FundTableModel::FundTableModel(QList<FundTransaction> list, QObject *parent) :
        TableModel(parent), transactionList(list)
    {

    }

    void FundTableModel::updateTransactionList(QList<FundTransaction> list)
    {
        beginResetModel();

        transactionList = list;

        endResetModel();
    }

    double FundTableModel::totalBuys() const
    {
        double buys = 0.0;

        QList<FundTransaction>::const_iterator iter;
        for(iter = transactionList.cbegin(); iter < transactionList.cend(); ++iter)
        {
            if(Util::BUY == iter->getOperationType())
            {
                buys += (iter->getPrice() * iter->getCount());
            }
        }

        return buys;
    }

    double FundTableModel::totalSells() const
    {
        double sells = 0.0;

        QList<FundTransaction>::const_iterator iter;
        for(iter = transactionList.cbegin(); iter < transactionList.cend(); ++iter)
        {
            if(Util::SELL == iter->getOperationType())
            {
                sells += (iter->getPrice() * iter->getCount());
            }
        }

        return sells;
    }

    QVariant FundTableModel::headerData(int section, Qt::Orientation orientation, int role) const
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
            return QString("Fund Code");
        case 1:
            return QString("Fund Name");
        case 2:
            return QString("Operation");
        case 3:
            return QString("Price");
        case 4:
            return QString("Count");
        case 5:
            return QString("Goal Price");
        case 6:
            return QString("Order Date");
        case 7:
            return QString("Operation Date");
        default:
            return QVariant();
        }

    }

    QVariant FundTableModel::data(const QModelIndex &index, int role) const
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
            return transactionList.at(index.row()).getFundCode().toUpper();
        case 1:
            return transactionList.at(index.row()).getFundName().toUpper();
        case 2:
            return Util::getOperationName(transactionList.at(index.row()).getOperationType());
        case 3:
            return QString::number(transactionList.at(index.row()).getPrice(), 'f');
        case 4:
            return transactionList.at(index.row()).getCount();
        case 5:
            return QString::number(transactionList.at(index.row()).getGoalPrice(), 'f');
        case 6:
            return transactionList.at(index.row()).getOrderDate().toString(Qt::ISODate);
        case 7:
            return transactionList.at(index.row()).getOperationDate().toString(Qt::ISODate);
        default:
            return QVariant();
        }
    }

}
