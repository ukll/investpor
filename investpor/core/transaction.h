#ifndef TRANSACTION_H
#define TRANSACTION_H

#include <QObject>

namespace investpor {

    namespace core {

        class Transaction
        {
        public:
            explicit Transaction(const quint16 &id) { transactionID = id; }
            virtual ~Transaction() = 0;

            quint16 getTransactionId() const { return transactionID; }
            void setTransactionId(const quint16 &id) { transactionID = id; }

        private:
            quint16 transactionID;
        };

    }

}
#endif // TRANSACTION_H
