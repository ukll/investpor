#ifndef CRYPTOCURRENCYDIALOG_H
#define CRYPTOCURRENCYDIALOG_H

#include "investpor/core/cryptocurrencytransaction.h"

#include <QDialog>
#include <QStatusBar>

namespace Ui {
    class CryptocurrencyDialog;
}

using investpor::core::CryptocurrencyTransaction;

namespace investpor {

    namespace gui {

        class CryptocurrencyDialog : public QDialog
        {
            Q_OBJECT

        public:
            explicit CryptocurrencyDialog(QWidget *parent = 0);
            ~CryptocurrencyDialog();

            CryptocurrencyTransaction getTransaction() const { return transaction; }

        private:
            Ui::CryptocurrencyDialog *ui;
            QStatusBar statusBar;
            CryptocurrencyTransaction transaction;

            void rearrangeDialog(int &operationIndex);
            virtual void accept() override;
        };

    }

}

#endif // CRYPTOCURRENCYDIALOG_H
