#ifndef TABLEMODEL_H
#define TABLEMODEL_H

#include <QAbstractTableModel>

namespace desktop {

    class TableModel : public QAbstractTableModel
    {
    public:
        TableModel(QObject *parent = nullptr);
        ~TableModel() { }

        virtual double totalBuys() const = 0;
        virtual double totalSells() const = 0;
    };
}
#endif // TABLEMODEL_H
