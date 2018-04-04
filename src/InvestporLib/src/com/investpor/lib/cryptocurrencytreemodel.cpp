#include "lib/cryptocurrencytreemodel.h"

#include <QBrush>
#include <QColor>

namespace lib {

    CryptocurrencyTreeModel::CryptocurrencyTreeModel(const QList<CryptocurrencyFieldHeaderPair> &headerDataList,
                                                     CryptocurrencyTreeItem* const root, QObject *parent) :
        AbstractTreeModel(root, parent), m_headersList(headerDataList)
    {

    }

    QVariant CryptocurrencyTreeModel::headerData(int section, Qt::Orientation orientation, int role) const
    {
        if(Qt::DisplayRole != role || Qt::Horizontal != orientation)
        {
            return QVariant();
        }

        return m_headersList.at(section).m_header;
    }

    QModelIndex CryptocurrencyTreeModel::index(int row, int column, const QModelIndex &parent) const
    {
        if(!hasIndex(row, column, parent))
        {
            return QModelIndex();
        }

        CryptocurrencyTreeItem *parentItem;
        if(!parent.isValid()) {
            parentItem = static_cast<CryptocurrencyTreeItem*>(getRootItem());
        } else {
            parentItem = static_cast<CryptocurrencyTreeItem*>(parent.internalPointer());
        }

        CryptocurrencyTreeItem *childItem = static_cast<CryptocurrencyTreeItem*>(parentItem->getChildItem(row));
        if(childItem) {
            return createIndex(row, column, childItem);
        }

        return QModelIndex();
    }

    QModelIndex CryptocurrencyTreeModel::parent(const QModelIndex &child) const
    {
        if(!child.isValid())
        {
            return QModelIndex();
        }

        CryptocurrencyTreeItem *childItem = static_cast<CryptocurrencyTreeItem*>(child.internalPointer());
        CryptocurrencyTreeItem *parentItem = static_cast<CryptocurrencyTreeItem*>(childItem->getParentItem());

        if(parentItem == static_cast<CryptocurrencyTreeItem*>(getRootItem()))
        {
            return QModelIndex();
        }

        return createIndex(parentItem->getRowNumber(), 0, parentItem);
    }

    QVariant CryptocurrencyTreeModel::data(const QModelIndex &index, int role) const
    {
        if(Qt::TextAlignmentRole == role)
        {
            return Qt::AlignCenter;
        }

        CryptocurrencyTreeItem *item = static_cast<CryptocurrencyTreeItem*>(index.internalPointer());

        if(Qt::BackgroundRole == role)
        {
            if(item->getParentItem() == static_cast<CryptocurrencyTreeItem*>(getRootItem()))
            {
                return QBrush(QColor(255, 255, 255, 100));
            }

            if(Util::BUY == item->getOperation()) {
                return QBrush(QColor(0, 255, 0, 100));
            }
            return QBrush(QColor(255, 0, 0, 100));
        }

        if(Qt::ToolTipRole == role)
        {
            switch (m_headersList.at(index.column()).m_field) {
            case Cryptocurrency:
                return Util::getCurrencyName(static_cast<Util::Currency>(item->getCryptocurrency()));
            case ReferenceCurrency:
                return Util::getCurrencyName(static_cast<Util::Currency>(item->getReferenceCurrency()));
            default:
                return QVariant();
            }

        }

        if(Qt::WhatsThisRole == role)
        {
            return QVariant();
        }

        if(Qt::DisplayRole != role)
        {
            return QVariant();
        }

        if(item->getParentItem() == static_cast<CryptocurrencyTreeItem*>(getRootItem()))
        {
            if(m_headersList.at(index.column()).m_field == Cryptocurrency) {
                return QVariant::fromValue(item->getCryptocurrency()).toString();
            } else {
                return QVariant();
            }
        }

        switch (m_headersList.at(index.column()).m_field) {
        case Id:
            return item->getId().toString(Qt::ISODate);
        case Cryptocurrency:
            return QVariant();
        case Operation:
            return Util::getOperationName(static_cast<Util::Operation>(item->getOperation()));
        case ReferenceCurrency:
            return QVariant::fromValue(item->getReferenceCurrency()).toString();
        case Price:
            return item->getPrice();
        case Amount:
            return item->getAmount();
        case ExtraExpenses:
            return item->getExtraExpenses();
        case GoalPrice:
            return item->getGoalPrice();
        case DateTime:
            return item->getDateTime().toString(Qt::ISODate);
        default:
            return QVariant();
        }
    }

    int CryptocurrencyTreeModel::rowCount(const QModelIndex &parent) const
    {
        CryptocurrencyTreeItem *parentItem;

        if(!parent.isValid()) {
            parentItem = static_cast<CryptocurrencyTreeItem*>(getRootItem());
        } else {
            parentItem = static_cast<CryptocurrencyTreeItem*>(parent.internalPointer());
        }

        return parentItem->getChildCount();
    }

    int CryptocurrencyTreeModel::columnCount(const QModelIndex &parent) const
    {
        return m_headersList.length();
    }

}
