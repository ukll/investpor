#include "lib/cryptocurrencytreemodel.h"

#include <QBrush>
#include <QColor>
#include <QPen>

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
        if(childItem)
        {
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

        if(Qt::ForegroundRole == role)
        {
            return QPen(QColor(0, 0, 0, 100));
        }

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
            return item->getTransactionId().toString(Qt::ISODate);
        case Cryptocurrency:
            return QVariant();
        case Operation:
            return Util::getOperationName(static_cast<Util::Operation>(item->getOperation()));
        case ReferenceCurrency:
            return QVariant::fromValue(item->getReferenceCurrency()).toString();
        case Price:
            return item->getPricePerShare();
        case Amount:
            return item->getAmount();
        case ExtraExpenses:
            return item->getExtraExpensesPerTransaction();
        case GoalPrice:
            return item->getGoalPricePerShare();
        case DateTime:
            return item->getOperationDateTime().toString(Qt::ISODate);
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

    Qt::ItemFlags CryptocurrencyTreeModel::flags(const QModelIndex &index) const
    {
        if(!index.parent().isValid())
        {
            return Qt::NoItemFlags;
        }

        return Qt::ItemIsEnabled | Qt::ItemIsSelectable;
    }

    bool CryptocurrencyTreeModel::insertTransaction(CryptocurrencyTreeItem cti)
    {
        beginResetModel();

        CryptocurrencyTreeItem *rootItem = static_cast<CryptocurrencyTreeItem*>(getRootItem());
        CryptocurrencyTreeItem *newItem = new CryptocurrencyTreeItem(cti);
        bool inserted = false;

        if(rootItem->getChildCount() != 0)
        {
            for(int i = 0; i < rootItem->getChildCount(); ++i)
            {
                CryptocurrencyTreeItem *childItem = static_cast<CryptocurrencyTreeItem*>(rootItem->getChildItem(i));

                if(childItem->getCryptocurrency() == newItem->getCryptocurrency())
                {
                    childItem->appendChildItem(newItem);
                    inserted = true;
                    break;
                }
            }
        }

        if(!inserted)
        {
            CryptocurrencyTreeItem *emptyItem = new CryptocurrencyTreeItem();
            emptyItem->setCryptocurrency(newItem->getCryptocurrency());
            emptyItem->appendChildItem(newItem);
            rootItem->appendChildItem(emptyItem);
            inserted = true;
        }

        endResetModel();

        return inserted;
    }

}
