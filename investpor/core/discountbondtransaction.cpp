#include "investpor/core/discountbondtransaction.h"

#include <QString>
#include <QDate>

namespace investpor {

    namespace core {

        DiscountBondTransaction::DiscountBondTransaction(quint16 id) :
            Transaction(id)
        {

        }

        DiscountBondTransaction::DiscountBondTransaction(Operation op, QString isin, QDate term,
            double nomValue, double sPrice, QDate opDate, quint16 id) :
            Transaction(id), operation(op), ISIN(isin), termDate(term),
            nominalValue(nomValue), salePrice(sPrice), operationDate(opDate)
        {

        }

        DiscountBondTransaction::~DiscountBondTransaction()
        {

        }

        Operation DiscountBondTransaction::getOperationType()
        {
            return operation;
        }

        void DiscountBondTransaction::setOperationType(Operation op)
        {
            operation = op;
        }

        QString DiscountBondTransaction::getISIN()
        {
            return ISIN;
        }

        void DiscountBondTransaction::setISIN(QString isin)
        {
            ISIN = isin;
        }

        QDate DiscountBondTransaction::getTerm()
        {
            return termDate;
        }

        void DiscountBondTransaction::setTerm(QDate term)
        {
            termDate = term;
        }

        double DiscountBondTransaction::getNominalValue()
        {
            return nominalValue;
        }

        void DiscountBondTransaction::setNominalValue(double nomValue)
        {
            nominalValue = nomValue;
        }

        double DiscountBondTransaction::getSalePrice()
        {
            return salePrice;
        }

        void DiscountBondTransaction::setSalePrice(double sPrice)
        {
            salePrice = sPrice;
        }

        QDate DiscountBondTransaction::getOperationDate()
        {
            return operationDate;
        }

        void DiscountBondTransaction::setOperationDate(QDate opDate)
        {
            operationDate = opDate;
        }

    }

}
