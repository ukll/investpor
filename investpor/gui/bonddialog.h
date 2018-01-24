#ifndef BONDDIALOG_H
#define BONDDIALOG_H

#include "investpor/core/discountbondtransaction.h"

#include <QDialog>
#include <QStatusBar>
#include <QValidator>

namespace Ui {
    class BondDialog;
}

using investpor::core::DiscountBondTransaction;

namespace investpor {

    namespace gui {

        class BondDialog : public QDialog
        {
            Q_OBJECT

        public:
            explicit BondDialog(QWidget *parent = 0);
            ~BondDialog();

            DiscountBondTransaction getTransaction() const { return transaction; }

        private:
            Ui::BondDialog *ui;
            DiscountBondTransaction transaction;
            QStatusBar statusBar;
            QRegExpValidator ISINValidator;

            void rearrangeDialog(int index);
            virtual void accept() override;
        };

    }

}



#endif // BONDDIALOG_H
