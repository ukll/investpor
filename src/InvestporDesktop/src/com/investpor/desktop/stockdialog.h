#ifndef STOCKDIALOG_H
#define STOCKDIALOG_H

#include "lib/stocktransaction.h"

#include <QDialog>
#include <QStatusBar>
#include <QRegularExpressionValidator>

namespace Ui {
    class StockDialog;
}

using lib::StockTransaction;

namespace desktop {

    class StockDialog : public QDialog
    {
        Q_OBJECT

    public:
        explicit StockDialog(QWidget *parent = 0);
        ~StockDialog();

        StockTransaction getTransaction() const { return m_transaction; }

    private:
        Ui::StockDialog *m_ui;
        QStatusBar m_statusBar;
        QRegularExpressionValidator m_symbolValidator;
        QRegularExpressionValidator m_nameValidator;
        StockTransaction m_transaction;

        virtual void accept() override;

    private slots:
        void rearrangeDialog();
    };

}

#endif // STOCKDIALOG_H
