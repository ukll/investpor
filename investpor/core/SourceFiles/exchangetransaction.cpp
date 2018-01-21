#include "investpor/core/HeaderFiles/exchangetransaction.h"

#include "investpor/core/HeaderFiles/types.h"

ExchangeTransaction::ExchangeTransaction(quint16 id) :
    Transaction(id)
{

}

ExchangeTransaction::ExchangeTransaction(Operation op, Currency cur, double prc, double amnt, QDateTime dt, double gPrice, quint16 id) :
    Transaction(id), operationType(op), currency(cur), price(prc), amount(amnt), dateTime(dt), goalPrice(gPrice)
{

}

ExchangeTransaction::~ExchangeTransaction()
{

}
