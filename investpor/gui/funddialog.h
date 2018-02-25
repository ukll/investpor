#ifndef FUNDDIALOG_H
#define FUNDDIALOG_H

#include "investpor/core/fundtransaction.h"

#include <QDialog>
#include <QStatusBar>
#include <QRegularExpressionValidator>

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
            QRegularExpressionValidator fundCodeValidator;
            QRegularExpressionValidator fundNameValidator;

            virtual void accept() override;

        private slots:
            void rearrangeDialog();
        };

    }

}

#endif // FUNDDIALOG_H
