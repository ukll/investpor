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

            DiscountBondTransaction getTransaction();

        private:
            Ui::BondDialog *ui;
            DiscountBondTransaction transaction;
            QStatusBar statusBar;
            QRegExpValidator ISINValidator;

            virtual void accept() override;
            void rearrangeDialog(int index);
        };

    }

}



#endif // BONDDIALOG_H
