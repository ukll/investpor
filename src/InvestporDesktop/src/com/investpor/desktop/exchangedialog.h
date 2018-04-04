#ifndef EXCHANGEDIALOG_H
#define EXCHANGEDIALOG_H

#include "lib/exchangetransaction.h"

#include <QDialog>
#include <QStatusBar>

namespace Ui {
    class ExchangeDialog;
}

using lib::ExchangeTransaction;

namespace desktop {

    class ExchangeDialog : public QDialog
    {
        Q_OBJECT

    public:
        explicit ExchangeDialog(QWidget *parent = 0);
        ~ExchangeDialog();

        ExchangeTransaction getTransaction() const { return m_transaction; }

    private:
        Ui::ExchangeDialog *m_ui;
        QStatusBar m_statusBar;
        ExchangeTransaction m_transaction;

        virtual void accept() override;

    private slots:
        void rearrangeDialog();
    };

}
#endif // EXCHANGEDIALOG_H
