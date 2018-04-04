#ifndef DISCOUNTBONDTABLEMODEL_H
#define DISCOUNTBONDTABLEMODEL_H

#include "desktop/tablemodel.h"
#include "lib/discountbondtransaction.h"

using lib::DiscountBondTransaction;

namespace desktop {

    class DiscountBondTableModel : public TableModel
    {
    public:
        DiscountBondTableModel(QList<DiscountBondTransaction> list, QObject *parent = nullptr);
        ~DiscountBondTableModel() { }

        void updateTransactionList(QList<DiscountBondTransaction> list);
        virtual double totalBuys() const override;
        virtual double totalSells() const override;

        virtual QVariant headerData(int section, Qt::Orientation orientation, int role) const override;
        virtual QVariant data(const QModelIndex &index, int role) const override;
        virtual int rowCount(const QModelIndex &parent) const override { return transactionList.length(); }
        virtual int columnCount(const QModelIndex &parent) const override { return columns; }

    private:
        const static int columns = 7;
        QList<DiscountBondTransaction> transactionList;
    };

}
#endif // DISCOUNTBONDTABLEMODEL_H
