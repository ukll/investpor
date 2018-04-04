#ifndef CRYPTOCURRENCYTABLEMODEL_H
#define CRYPTOCURRENCYTABLEMODEL_H

#include "desktop/tablemodel.h"
#include "lib/cryptocurrencytransaction.h"

using lib::CryptocurrencyTransaction;

namespace desktop {

    class CryptocurrencyTableModel : public TableModel
    {
    public:
        CryptocurrencyTableModel(QList<CryptocurrencyTransaction> list, QObject *parent = nullptr);
        ~CryptocurrencyTableModel(){ }

        void updateTransactionList(QList<CryptocurrencyTransaction> list);
        virtual double totalBuys() const override;
        virtual double totalSells() const override;

        virtual QVariant headerData(int section, Qt::Orientation orientation, int role) const override;
        virtual QVariant data(const QModelIndex &index, int role) const override;
        virtual int rowCount(const QModelIndex &parent) const override { return transactionList.length(); }
        virtual int columnCount(const QModelIndex &parent) const override { return columns; }

    private:
        const static int columns = 6;
        QList<CryptocurrencyTransaction> transactionList;
    };

}

#endif // CRYPTOCURRENCYTABLEMODEL_H
