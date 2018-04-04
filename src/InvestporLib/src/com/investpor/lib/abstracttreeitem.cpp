#include "lib/abstracttreeitem.h"

namespace lib {

    AbstractTreeItem::AbstractTreeItem() :
        m_parentItem(nullptr),
        m_transactionId(QDateTime::currentDateTime())
    {

    }

    void AbstractTreeItem::appendChildItem(AbstractTreeItem *child)
    {
        m_childItems.append(child);
        child->setParentItem(this);
    }

    AbstractTreeItem::~AbstractTreeItem()
    {
        qDeleteAll(m_childItems.begin(), m_childItems.end());
        m_childItems.clear();
    }

    int AbstractTreeItem::getRowNumber() const
    {
        return (m_parentItem != nullptr ? m_parentItem->findRowNumber(const_cast<AbstractTreeItem*>(this)) : 0);
    }

}
