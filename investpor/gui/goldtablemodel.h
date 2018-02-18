#ifndef GOLDTABLEMODEL_H
#define GOLDTABLEMODEL_H

#include "investpor/gui/tablemodel.h"
#include "investpor/core/goldtransaction.h"

using investpor::core::GoldTransaction;

namespace investpor {

    namespace gui {

        class GoldTableModel : public TableModel
        {
        public:
            GoldTableModel(QList<GoldTransaction> list, QObject *parent = nullptr);
            ~GoldTableModel() { }

            void updateTransactionList(QList<GoldTransaction> list);
            virtual double totalBuys() const override;
            virtual double totalSells() const override;

            virtual QVariant headerData(int section, Qt::Orientation orientation, int role) const override;
            virtual QVariant data(const QModelIndex &index, int role) const override;
            virtual int rowCount(const QModelIndex &parent) const override { return transactionList.length(); }
            virtual int columnCount(const QModelIndex &parent) const override { return columns; }

        private:
            const static int columns = 6;
            QList<GoldTransaction> transactionList;
        };
    }

}
#endif // GOLDTABLEMODEL_H
