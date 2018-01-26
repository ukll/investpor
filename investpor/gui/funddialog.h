#ifndef FUNDDIALOG_H
#define FUNDDIALOG_H

#include "investpor/core/fundtransaction.h"

#include <QDialog>
#include <QStatusBar>
#include <QRegExpValidator>

namespace Ui {
    class FundDialog;
}

using investpor::core::FundTransaction;

namespace investpor {

    namespace gui {

        class FundDialog : public QDialog
        {
            Q_OBJECT

        public:
            explicit FundDialog(QWidget *parent = 0);
            ~FundDialog();

            FundTransaction getTransaction() const { return transaction; }

        private:
            Ui::FundDialog *ui;
            FundTransaction transaction;
            QStatusBar statusBar;
            QRegExpValidator fundCodeValidator;
            QRegExpValidator fundNameValidator;

            void rearrangeDialog(int &index);
            virtual void accept() override;
        };

    }

}

#endif // FUNDDIALOG_H
