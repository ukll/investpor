#ifndef TRANSACTION_H
#define TRANSACTION_H

#include <QObject>

namespace investpor {

    namespace core {

        class Transaction
        {
        public:
            virtual ~Transaction() = 0;
        };

    }

}
#endif // TRANSACTION_H
