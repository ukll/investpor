#include "investpor/gui/exchangetablemodel.h"

#include "investpor/core/util.h"

#include <QBrush>
#include <QColor>

using investpor::core::Util;

namespace investpor {

    namespace gui {

        ExchangeTableModel::ExchangeTableModel(QList<ExchangeTransaction> list, QObject *parent) :
            TableModel(parent), transactionList(list)
        {

        }

        void ExchangeTableModel::updateTransactionList(QList<core::ExchangeTransaction> list)
        {
            beginResetModel();

            transactionList = list;

            endResetModel();
        }

        double ExchangeTableModel::totalBuys() const
        {
            double buys = 0.0;

            QList<ExchangeTransaction>::const_iterator iter;
            for(iter = transactionList.cbegin(); iter < transactionList.cend(); ++iter)
            {
                if(Util::Operation::BUY == iter->getOperationType())
                {
                    buys += (iter->getPrice() * iter->getAmount());
                }
            }

            return buys;
        }

        double ExchangeTableModel::totalSells() const
        {
            double sells = 0.0;

            QList<ExchangeTransaction>::const_iterator iter;
            for(iter = transactionList.cbegin(); iter < transactionList.cend(); ++iter)
            {
                if(Util::Operation::SELL == iter->getOperationType())
                {
                    sells += (iter->getPrice() * iter->getAmount());
                }
            }

            return sells;
        }

        QVariant ExchangeTableModel::headerData(int section, Qt::Orientation orientation, int role) const
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
                return QString("Currency");
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

        QVariant ExchangeTableModel::data(const QModelIndex &index, int role) const
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
                return Util::currencySymbol(transactionList.at(index.row()).getCurrency()).toUpper();
            case 1:
                return transactionList.at(index.row()).getTransactionId();
            case 2:
                return Util::operationName(transactionList.at(index.row()).getOperationType());
            case 3:
                return QString::number(transactionList.at(index.row()).getPrice(), 'f');
            case 4:
                return QString::number(transactionList.at(index.row()).getAmount(), 'f');
            case 5:
                return QString::number(transactionList.at(index.row()).getGoalPrice(), 'f');
            case 6:
                return transactionList.at(index.row()).getOperationDateTime().toString(Qt::ISODate);
            default:
                return QVariant();
            }
        }

    }

}
