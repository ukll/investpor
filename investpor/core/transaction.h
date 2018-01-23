#ifndef TRANSACTION_H
#define TRANSACTION_H

#include <QObject>

namespace investpor {

    namespace core {

        class Transaction
        {
        public:
            explicit Transaction(quint16 id) { transactionID = id; }
            virtual ~Transaction() = 0;

            quint16 getTransactionId() { return transactionID; }
            void setTransactionId(quint16 id) { transactionID = id; }

        private:
            quint16 transactionID;
        };

    }

}
#endif // TRANSACTION_H
