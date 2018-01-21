#ifndef TRANSACTION_H
#define TRANSACTION_H

#include <QObject>

namespace investpor {

    namespace core {

        class Transaction
        {
        public:
            explicit Transaction(quint16 id);
            virtual ~Transaction() = 0;

            quint16 getTransactionId();
            void setTransactionId(quint16 id);

        private:
            quint16 transactionID;
        };

    }

}
#endif // TRANSACTION_H
