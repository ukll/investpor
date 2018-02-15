#ifndef PORTFOLIODIALOG_H
#define PORTFOLIODIALOG_H

#include "investpor/core/types.h"

#include <QDialog>
#include <QStatusBar>

namespace Ui {
    class PortfolioDialog;
}

using investpor::core::Currency;

namespace investpor {

    namespace gui {

        class PortfolioDialog : public QDialog
        {
            Q_OBJECT

        public:
            explicit PortfolioDialog(QWidget *parent = nullptr);
            PortfolioDialog(const QString &pName, const Currency &bCurrency, QWidget *parent = nullptr);
            ~PortfolioDialog();

            const QString getPortfolioName() const { return portfolioName; }
            const QString getPortfolioURL() const { return portfolioURL; }
            Currency getBasecurrency() const { return baseCurrency; }

        private:
            Ui::PortfolioDialog *ui;
            QStatusBar statusBar;

            bool isEditDialog;
            QString portfolioName;
            QString portfolioURL;
            Currency baseCurrency;

            void browseForFile();
            virtual void accept() override;
        };

    }

}
#endif // PORTFOLIODIALOG_H
