#ifndef CRYPTOCURRENCYTREEMODEL_H
#define CRYPTOCURRENCYTREEMODEL_H

#include "lib/abstracttreemodel.h"
#include "lib/cryptocurrencytreeitem.h"
#include "lib/util.h"

#include <QList>
#include <QMap>

namespace lib {

    class CryptocurrencyTreeModel final : public AbstractTreeModel
    {
    public:

        enum CryptocurrencyField {
            Id, Cryptocurrency, Operation, ReferenceCurrency, Price,
            Amount, ExtraExpenses, GoalPrice, DateTime
        };

        struct CryptocurrencyFieldHeaderPair {
            CryptocurrencyFieldHeaderPair(const CryptocurrencyField &f, const QString &h) :
                m_field(f), m_header(h) {}
            CryptocurrencyField m_field;
            QString m_header;
        };

        virtual QVariant headerData(int section, Qt::Orientation orientation, int role) const override;
        virtual QModelIndex index(int row, int column, const QModelIndex &parent) const override;
        virtual QModelIndex parent(const QModelIndex &child) const override;
        virtual QVariant data(const QModelIndex &index, int role) const override;
        virtual int rowCount(const QModelIndex &parent) const override;
        virtual int columnCount(const QModelIndex &parent) const override;
        virtual Qt::ItemFlags flags(const QModelIndex &index) const override;

        bool insertTransaction(CryptocurrencyTreeItem cti);

    private:
        QList<CryptocurrencyFieldHeaderPair> m_headersList;

        /**
        * To prevent other classes to call the constructor.
        * Only PortfolioXML class can create an object.
        */
        friend class PortfolioXML;
        CryptocurrencyTreeModel(const QList<CryptocurrencyFieldHeaderPair> &headerDataList,
                                CryptocurrencyTreeItem* const root,
                                QObject *parent = nullptr);
    };

}
#endif // CRYPTOCURRENCYTREEMODEL_H
