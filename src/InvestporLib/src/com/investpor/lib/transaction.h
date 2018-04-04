#ifndef TRANSACTION_H
#define TRANSACTION_H

#include <QObject>
#include <QDateTime>

namespace lib {

    class Transaction
    {
    public:
        explicit Transaction(const QDateTime &id = QDateTime::currentDateTimeUtc()) : transactionId(id) { }
        virtual ~Transaction() = 0;

        void setId(const QDateTime &id) { transactionId = id; }
        const QDateTime getId() const { return transactionId; }

    private:
        QDateTime transactionId;
    };

}
#endif // TRANSACTION_H
