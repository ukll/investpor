#include "investpor/gui/discountbondtablemodel.h"

#include "investpor/core/util.h"

using investpor::core::Operation;
using investpor::core::Util;

namespace investpor {

    namespace gui {

        DiscountBondTableModel::DiscountBondTableModel(QList<DiscountBondTransaction> list, QObject *parent) :
            TableModel(parent), transactionList(list)
        {

        }

        void DiscountBondTableModel::updateTransactionList(QList<core::DiscountBondTransaction> list)
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
                if(iter->getOperationType() == Operation::BUY)
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
                if(iter->getOperationType() == Operation::SELL)
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
                return QString("Transaction ID");
            case 2:
                return QString("Operation Type");
            case 3:
                return QString("Term");
            case 4:
                return QString("Nominal Value");
            case 5:
                return QString("Sale Price");
            case 6:
                return QString("Count");
            case 7:
                return QString("Operation Date");
            default:
                return QVariant();
            }
        }

        QVariant DiscountBondTableModel::data(const QModelIndex &index, int role) const
        {
            if(Qt::DisplayRole != role)
            {
                return QVariant();
            }

            switch (index.column()) {
            case 0:
                return transactionList.at(index.row()).getISIN();
            case 1:
                return transactionList.at(index.row()).getTransactionId();
            case 2:
                return Util::operationName(transactionList.at(index.row()).getOperationType());
            case 3:
                return transactionList.at(index.row()).getTerm().toString(Qt::ISODate);
            case 4:
                return QString::number(transactionList.at(index.row()).getNominalValue(), 'f', 6);
            case 5:
                return QString::number(transactionList.at(index.row()).getSalePrice(), 'f', 6);;
            case 6:
                return transactionList.at(index.row()).getCount();
            case 7:
                return transactionList.at(index.row()).getOperationDate().toString(Qt::ISODate);
            default:
                return QVariant();
            }
        }

    }

}
