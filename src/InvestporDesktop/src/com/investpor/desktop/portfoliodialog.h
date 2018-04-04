#ifndef PORTFOLIODIALOG_H
#define PORTFOLIODIALOG_H

#include "lib/util.h"

#include <QDialog>
#include <QStatusBar>

namespace Ui {
    class PortfolioDialog;
}

using lib::Util;

namespace desktop {

    class PortfolioDialog : public QDialog
    {
        Q_OBJECT

    public:
        static PortfolioDialog* newPortfolioDialog(QWidget *parent = nullptr);
        static PortfolioDialog* editPortfolioDialog(const QString &pName, const Util::Currency &bCurrency, QWidget *parent = nullptr);

        ~PortfolioDialog();

        const QString getPortfolioName() const { return m_portfolioName; }
        const QString getPortfolioURL() const { return m_portfolioURL; }
        Util::Currency getBasecurrency() const { return m_baseCurrency; }

    private:
        Ui::PortfolioDialog *m_ui;
        QStatusBar m_statusBar;

        bool m_isEditDialog;
        QString m_portfolioName;
        QString m_portfolioURL;
        Util::Currency m_baseCurrency;

        explicit PortfolioDialog(QWidget *parent = nullptr);
        PortfolioDialog(const QString &pName, const Util::Currency &bCurrency, QWidget *parent = nullptr);
        void prepareDialog();
        void browseForFile();
        virtual void accept() override;
    };

}
#endif // PORTFOLIODIALOG_H
