#ifndef CRYPTOCURRENCYDIALOG_H
#define CRYPTOCURRENCYDIALOG_H

#include "lib/cryptocurrencytransaction.h"

#include <QDialog>
#include <QStatusBar>

namespace Ui {
    class CryptocurrencyDialog;
}

using lib::CryptocurrencyTransaction;

namespace desktop {

    class CryptocurrencyDialog : public QDialog
    {
        Q_OBJECT

    public:
        explicit CryptocurrencyDialog(QWidget *parent = 0);
        ~CryptocurrencyDialog();

        CryptocurrencyTransaction getTransaction() const { return m_transaction; }

        virtual void accept() override;

    private:
        Ui::CryptocurrencyDialog *m_ui;
        QStatusBar m_statusBar;
        CryptocurrencyTransaction m_transaction;

    private slots:
        void rearrangeDialog();
    };

}

#endif // CRYPTOCURRENCYDIALOG_H
