#ifndef ABSTRACTTREEMODEL_H
#define ABSTRACTTREEMODEL_H

#include "lib/abstracttreeitem.h"

#include <QAbstractItemModel>

namespace lib {

    class AbstractTreeModel : public QAbstractItemModel
    {
    public:
        AbstractTreeModel(AbstractTreeItem *root, QObject *parent = nullptr);
        ~AbstractTreeModel() = 0;

        AbstractTreeItem* getRootItem() const { return m_rootItem; }

    private:
        AbstractTreeItem* const m_rootItem;
    };

}
#endif // ABSTRACTTREEMODEL_H
