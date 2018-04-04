#ifndef FUNDTABLEMODEL_H
#define FUNDTABLEMODEL_H

#include "desktop/tablemodel.h"
#include "lib/fundtransaction.h"

using lib::FundTransaction;

namespace desktop {

    class FundTableModel : public TableModel
    {
    public:
        FundTableModel(QList<FundTransaction> list, QObject *parent = nullptr);
        ~FundTableModel() { }

        void updateTransactionList(QList<FundTransaction> list);
        virtual double totalBuys() const override;
        virtual double totalSells() const override;

        virtual QVariant headerData(int section, Qt::Orientation orientation, int role) const override;
        virtual QVariant data(const QModelIndex &index, int role) const override;
        virtual int rowCount(const QModelIndex &parent) const override { return transactionList.length(); }
        virtual int columnCount(const QModelIndex &parent) const override { return columns; }

    private:
        const static int columns = 8;
        QList<FundTransaction> transactionList;
    };

}
#endif // FUNDTABLEMODEL_H
