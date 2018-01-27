#ifndef DISCOUNTBONDDIALOG_H
#define DISCOUNTBONDDIALOG_H

#include "investpor/core/discountbondtransaction.h"

#include <QDialog>
#include <QStatusBar>
#include <QValidator>

namespace Ui {
    class DiscountBondDialog;
}

using investpor::core::DiscountBondTransaction;

namespace investpor {

    namespace gui {

        class DiscountBondDialog : public QDialog
        {
            Q_OBJECT

        public:
            explicit DiscountBondDialog(QWidget *parent = 0);
            ~DiscountBondDialog();

            DiscountBondTransaction getTransaction() const { return transaction; }

        private:
            Ui::DiscountBondDialog *ui;
            DiscountBondTransaction transaction;
            QStatusBar statusBar;
            QRegExpValidator ISINValidator;

            void rearrangeDialog(int &index);
            virtual void accept() override;
        };

    }

}



#endif // DISCOUNTBONDDIALOG_H
