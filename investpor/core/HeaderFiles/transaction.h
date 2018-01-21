#ifndef TRANSACTION_H
#define TRANSACTION_H

#include <QObject>

namespace investpor {

    namespace core {

        class Transaction
        {
        public:
            explicit Transaction(int id);
            virtual ~Transaction() = 0;

            int getTransactionId();
            void setTransactionId(int id);

        private:
            int transactionID;
        };

    }

}
#endif // TRANSACTION_H
