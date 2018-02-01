#ifndef STOCKTABLEMODEL_H
#define STOCKTABLEMODEL_H

#include "investpor/gui/tablemodel.h"
#include "investpor/core/stocktransaction.h"

using investpor::core::StockTransaction;

namespace investpor {

    namespace gui {

        class StockTableModel : public TableModel
        {
        public:
            StockTableModel(QList<StockTransaction> list, QObject *parent = nullptr);
            ~StockTableModel() { }

            void updateTransactionList(QList<StockTransaction> list);
            virtual double totalBuys() const override;
            virtual double totalSells() const override;

            virtual QVariant headerData(int section, Qt::Orientation orientation, int role) const override;
            virtual QVariant data(const QModelIndex &index, int role) const override;
            virtual int rowCount(const QModelIndex &parent) const override { return transactionList.length(); }
            virtual int columnCount(const QModelIndex &parent) const override { return columns; }

        private:
            const static int columns = 10;
            QList<StockTransaction> transactionList;
        };

    }

}

#endif // STOCKTABLEMODEL_H
