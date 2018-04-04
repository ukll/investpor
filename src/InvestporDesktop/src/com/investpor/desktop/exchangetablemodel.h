#ifndef EXCHANGETABLEMODEL_H
#define EXCHANGETABLEMODEL_H

#include "desktop/tablemodel.h"
#include "lib/exchangetransaction.h"

using lib::ExchangeTransaction;

namespace desktop {

    class ExchangeTableModel : public TableModel
    {
    public:
        ExchangeTableModel(QList<ExchangeTransaction> list, QObject *parent = nullptr);
        ~ExchangeTableModel() { }

        void updateTransactionList(QList<ExchangeTransaction> list);
        virtual double totalBuys() const override;
        virtual double totalSells() const override;

        virtual QVariant headerData(int section, Qt::Orientation orientation, int role) const override;
        virtual QVariant data(const QModelIndex &index, int role) const override;
        virtual int rowCount(const QModelIndex &parent) const override { return transactionList.length(); }
        virtual int columnCount(const QModelIndex &parent) const override { return columns; }

    private:
        const static int columns = 6;
        QList<ExchangeTransaction> transactionList;
    };

}
#endif // EXCHANGETABLEMODEL_H
