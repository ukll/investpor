#ifndef EXCHANGEDIALOG_H
#define EXCHANGEDIALOG_H

#include "investpor/core/exchangetransaction.h"

#include <QDialog>
#include <QStatusBar>

namespace Ui {
    class ExchangeDialog;
}

using investpor::core::ExchangeTransaction;

namespace investpor {

    namespace gui {

        class ExchangeDialog : public QDialog
        {
            Q_OBJECT

        public:
            explicit ExchangeDialog(QWidget *parent = 0);
            ~ExchangeDialog();

            ExchangeTransaction getTransaction() const { return transaction; }

        private:
            Ui::ExchangeDialog *ui;
            QStatusBar statusBar;
            ExchangeTransaction transaction;

            virtual void accept() override;

        private slots:
            void rearrangeDialog();
        };

    }

}
#endif // EXCHANGEDIALOG_H
