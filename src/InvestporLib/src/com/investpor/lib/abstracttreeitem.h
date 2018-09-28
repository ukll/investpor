#ifndef ABSTRACTTREEITEM_H
#define ABSTRACTTREEITEM_H

#include <QDateTime>
#include <QList>

namespace lib {

    class AbstractTreeItem
    {
    public:
        AbstractTreeItem();
        virtual ~AbstractTreeItem() = 0;

        //Transaction related functions
        const QDateTime getTransactionId() const { return m_transactionId; }

        //Model related functions
        void appendChildItem(AbstractTreeItem *child);

        AbstractTreeItem *getParentItem() const { return m_parentItem; }
        AbstractTreeItem *getChildItem(int row) const { return m_childItems.at(row); }
        int getChildCount() const { return m_childItems.length(); }
        int getRowNumber() const;

    protected:
        //Transaction related functions
        //To prevent other classes (except those which inherit) to call setId method.
        void setTransactionId(const QDateTime &id) { m_transactionId = id; }
        //Only PortfolioXML class can alter an existing item id.
        friend class PortfolioXML;

        //Model related functions
        void setParentItem(AbstractTreeItem *parent) { m_parentItem = parent; }
        int findRowNumber(AbstractTreeItem* const child) const { return m_childItems.indexOf(child); }

    private:
        AbstractTreeItem *m_parentItem;
        QList<AbstractTreeItem*> m_childItems;
        QDateTime m_transactionId;
    };

}

#endif // ABSTRACTTREEITEM_H
