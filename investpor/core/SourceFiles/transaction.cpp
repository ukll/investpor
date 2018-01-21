#include "investpor/core/HeaderFiles/transaction.h"

namespace investpor {

    namespace core {

        Transaction::Transaction(int id) :
            transactionID(id)
        {

        }

        Transaction::~Transaction()
        {

        }

        int Transaction::getTransactionId()
        {
            return transactionID;
        }

        void Transaction::setTransactionId(int id)
        {
            transactionID = id;
        }

    }

}
