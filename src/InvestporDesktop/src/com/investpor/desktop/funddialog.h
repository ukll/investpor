#ifndef FUNDDIALOG_H
#define FUNDDIALOG_H

#include "lib/fundtransaction.h"

#include <QDialog>
#include <QStatusBar>
#include <QRegularExpressionValidator>

namespace Ui {
    class FundDialog;
}

using lib::FundTransaction;

namespace desktop {

    class FundDialog : public QDialog
    {
        Q_OBJECT

    public:
        explicit FundDialog(QWidget *parent = 0);
        ~FundDialog();

        FundTransaction getTransaction() const { return m_transaction; }

    private:
        Ui::FundDialog *m_ui;
        FundTransaction m_transaction;
        QStatusBar m_statusBar;
        QRegularExpressionValidator m_fundCodeValidator;
        QRegularExpressionValidator m_fundNameValidator;

        virtual void accept() override;

    private slots:
        void rearrangeDialog();
    };

}

#endif // FUNDDIALOG_H
