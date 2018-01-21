#ifndef EXCHANGEDIALOG_H
#define EXCHANGEDIALOG_H

#include "investpor/core/HeaderFiles/exchangetransaction.h"

#include <QDialog>
#include <QStatusBar>

namespace Ui {
    class ExchangeDialog;
}

namespace investpor {

    namespace gui {

        class ExchangeDialog : public QDialog
        {
            Q_OBJECT

        public:
            explicit ExchangeDialog(QWidget *parent = 0);
            ~ExchangeDialog();

            ExchangeTransaction getTransaction();

        private:
            Ui::ExchangeDialog *ui;
            QStatusBar statusBar;
            ExchangeTransaction transaction;

            void rearrangeDialog(int index);
            virtual void accept();
        };

    }

}
#endif // EXCHANGEDIALOG_H
