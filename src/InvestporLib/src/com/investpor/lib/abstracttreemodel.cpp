#include "lib/abstracttreemodel.h"

namespace lib {

    AbstractTreeModel::AbstractTreeModel(AbstractTreeItem *root, QObject *parent) :
        QAbstractItemModel(parent), m_rootItem(root)
    {

    }

    AbstractTreeModel::~AbstractTreeModel()
    {
        delete m_rootItem;
    }

}
