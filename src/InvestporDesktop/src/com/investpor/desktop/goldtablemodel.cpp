#include "desktop/goldtablemodel.h"

#include "lib/util.h"

#include <QBrush>
#include <QColor>

using lib::Util;
using lib::GoldTransaction;

namespace desktop {

    GoldTableModel::GoldTableModel(QList<GoldTransaction> list, QObject *parent) :
        TableModel(parent), transactionList(list)
    {

    }

    void GoldTableModel::updateTransactionList(QList<GoldTransaction> list)
    {
        beginResetModel();

        transactionList = list;

        endResetModel();
    }

    double GoldTableModel::totalBuys() const
    {
        double buys = 0.0;

        QList<GoldTransaction>::const_iterator iter;
        for(iter = transactionList.cbegin(); iter < transactionList.cend(); ++iter)
        {
            if(Util::BUY == iter->getOperationType())
            {
                buys += (iter->getPrice() * iter->getAmount());
            }
        }

        return buys;
    }

    double GoldTableModel::totalSells() const
    {
        double sells = 0.0;

        QList<GoldTransaction>::const_iterator iter;
        for(iter = transactionList.cbegin(); iter < transactionList.cend(); ++iter)
        {
            if(Util::SELL == iter->getOperationType())
            {
                sells += (iter->getPrice() * iter->getAmount());
            }
        }

        return sells;
    }

    QVariant GoldTableModel::headerData(int section, Qt::Orientation orientation, int role) const
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
            return QString("Type");
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

    QVariant GoldTableModel::data(const QModelIndex &index, int role) const
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
            return Util::getGoldName(transactionList.at(index.row()).getGoldType()).toUpper();
        case 1:
            return Util::getOperationName(transactionList.at(index.row()).getOperationType());
        case 2:
            return QString::number(transactionList.at(index.row()).getPrice(), 'f');
        case 3:
            return QString::number(transactionList.at(index.row()).getAmount(), 'f');
        case 4:
            return QString::number(transactionList.at(index.row()).getGoalPrice(), 'f');
        case 5:
            return transactionList.at(index.row()).getOperationDateTime().toString(Qt::ISODate);
        default:
            return QVariant();
        }
    }

}
