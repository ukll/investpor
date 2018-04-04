#include "desktop/discountbondtablemodel.h"

#include "lib/util.h"

#include <QBrush>
#include <QColor>

using lib::Util;
using lib::DiscountBondTransaction;

namespace desktop {

    DiscountBondTableModel::DiscountBondTableModel(QList<DiscountBondTransaction> list, QObject *parent) :
        TableModel(parent), transactionList(list)
    {

    }

    void DiscountBondTableModel::updateTransactionList(QList<DiscountBondTransaction> list)
    {
        beginResetModel();

        transactionList = list;

        endResetModel();
    }

    double DiscountBondTableModel::totalBuys() const
    {
        double buys = 0;

        QList<DiscountBondTransaction>::const_iterator iter;
        for(iter = transactionList.cbegin(); iter < transactionList.cend(); ++iter)
        {
            if(iter->getOperationType() == Util::BUY)
            {
                buys += (iter->getSalePrice() * iter->getCount());
            }
        }

        return buys;
    }

    double DiscountBondTableModel::totalSells() const
    {
        double sells = 0;

        QList<DiscountBondTransaction>::const_iterator iter;
        for(iter = transactionList.cbegin(); iter < transactionList.cend(); ++iter)
        {
            if(iter->getOperationType() == Util::SELL)
            {
                sells += (iter->getSalePrice() * iter->getCount());
            }
        }

        return sells;
    }

    QVariant DiscountBondTableModel::headerData(int section, Qt::Orientation orientation, int role) const
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
            return QString("ISIN");
        case 1:
            return QString("Operation");
        case 2:
            return QString("Term");
        case 3:
            return QString("Nominal Value");
        case 4:
            return QString("Sale Price");
        case 5:
            return QString("Count");
        case 6:
            return QString("Operation Date");
        default:
            return QVariant();
        }
    }

    QVariant DiscountBondTableModel::data(const QModelIndex &index, int role) const
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
            return transactionList.at(index.row()).getISIN().toUpper();
        case 1:
            return Util::getOperationName(transactionList.at(index.row()).getOperationType());
        case 2:
            return transactionList.at(index.row()).getTerm().toString(Qt::ISODate);
        case 3:
            return QString::number(transactionList.at(index.row()).getNominalValue(), 'f');
        case 4:
            return QString::number(transactionList.at(index.row()).getSalePrice(), 'f');;
        case 5:
            return transactionList.at(index.row()).getCount();
        case 6:
            return transactionList.at(index.row()).getOperationDate().toString(Qt::ISODate);
        default:
            return QVariant();
        }
    }

}
