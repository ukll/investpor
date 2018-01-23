#ifndef FUNDDIALOG_H
#define FUNDDIALOG_H

#include <QDialog>

namespace Ui {
    class FundDialog;
}

namespace investpor {

    namespace gui {

        class FundDialog : public QDialog
        {
            Q_OBJECT

        public:
            explicit FundDialog(QWidget *parent = 0);
            ~FundDialog();

        private:
            Ui::FundDialog *ui;

            void rearrangeDialog(int index);
        };

    }

}

#endif // FUNDDIALOG_H
