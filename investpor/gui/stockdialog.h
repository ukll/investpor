#ifndef STOCKDIALOG_H
#define STOCKDIALOG_H

#include "investpor/core/stocktransaction.h"

#include <QDialog>
#include <QStatusBar>
#include <QRegExpValidator>

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
            QRegExpValidator symbolValidator;
            QRegExpValidator nameValidator;
            StockTransaction transaction;

            void rearrangeDialog(int index);
            virtual void accept() override;
        };

    }

}

#endif // STOCKDIALOG_H
