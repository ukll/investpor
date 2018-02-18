#ifndef GOLDDIALOG_H
#define GOLDDIALOG_H

#include "investpor/core/goldtransaction.h"

#include <QDialog>
#include <QStatusBar>

namespace Ui {
    class GoldDialog;
}

using investpor::core::GoldTransaction;

namespace investpor {

    namespace gui {

        class GoldDialog : public QDialog
        {
            Q_OBJECT

        public:
            explicit GoldDialog(QWidget *parent = 0);
            ~GoldDialog();

            GoldTransaction getTransaction() const { return transaction; }

        private:
            Ui::GoldDialog *ui;
            QStatusBar statusBar;
            GoldTransaction transaction;

            void rearrangeDialog(int &operationIndex);
            virtual void accept() override;
        };

    }

}

#endif // GOLDDIALOG_H
