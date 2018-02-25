#ifndef STOCKDIALOG_H
#define STOCKDIALOG_H

#include "investpor/core/stocktransaction.h"

#include <QDialog>
#include <QStatusBar>
#include <QRegularExpressionValidator>

namespace Ui {
    class StockDialog;
}

using investpor::core::StockTransaction;

namespace investpor {

    namespace gui {

        class StockDialog : public QDialog
        {
            Q_OBJECT

        public:
            explicit StockDialog(QWidget *parent = 0);
            ~StockDialog();

            StockTransaction getTransaction() const { return transaction; }

        private:
            Ui::StockDialog *ui;
            QStatusBar statusBar;
            QRegularExpressionValidator symbolValidator;
            QRegularExpressionValidator nameValidator;
            StockTransaction transaction;

            virtual void accept() override;

        private slots:
            void rearrangeDialog();
        };

    }

}

#endif // STOCKDIALOG_H
