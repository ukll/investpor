#ifndef GOLDDIALOG_H
#define GOLDDIALOG_H

#include "lib/goldtransaction.h"

#include <QDialog>
#include <QStatusBar>

namespace Ui {
    class GoldDialog;
}

using lib::GoldTransaction;

namespace desktop {

    class GoldDialog : public QDialog
    {
        Q_OBJECT

    public:
        explicit GoldDialog(QWidget *parent = 0);
        ~GoldDialog();

        GoldTransaction getTransaction() const { return m_transaction; }

    private:
        Ui::GoldDialog *m_ui;
        QStatusBar m_statusBar;
        GoldTransaction m_transaction;

        virtual void accept() override;

    private slots:
        void rearrangeDialog();
    };

}

#endif // GOLDDIALOG_H
