#ifndef DISCOUNTBONDDIALOG_H
#define DISCOUNTBONDDIALOG_H

#include "lib/discountbondtransaction.h"

#include <QDialog>
#include <QStatusBar>
#include <QRegularExpressionValidator>

namespace Ui {
    class DiscountBondDialog;
}

using lib::DiscountBondTransaction;

namespace desktop {

    class DiscountBondDialog : public QDialog
    {
        Q_OBJECT

    public:
        explicit DiscountBondDialog(QWidget *parent = 0);
        ~DiscountBondDialog();

        DiscountBondTransaction getTransaction() const { return m_transaction; }

    private:
        Ui::DiscountBondDialog *m_ui;
        DiscountBondTransaction m_transaction;
        QStatusBar m_statusBar;
        QRegularExpressionValidator m_ISINValidator;

        virtual void accept() override;

    private slots:
        void rearrangeDialog();
    };

}



#endif // DISCOUNTBONDDIALOG_H
