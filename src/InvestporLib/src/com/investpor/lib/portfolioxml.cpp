#include "lib/portfolioxml.h"

#include <QDir>
#include <QFile>
#include <QFileInfo>
#include <QTextStream>
#include <QXmlStreamWriter>
#include <QXmlStreamReader>
#include <QDomDocument>
#include <QList>
#include <QSortFilterProxyModel>

#define PORTFOLIO_ELEMENT_TAGNAME           QStringLiteral("Portfolio")

#define CRYPTOCURRENCY_INVESTMENT_TAGNAME   QStringLiteral("CryptocurrencyInvestment")
#define DISCOUNT_BOND_INVESTMENT_TAGNAME    QStringLiteral("DiscountbondInvestment")
#define EXCHANGE_INVESTMENT_TAGNAME         QStringLiteral("ExchangeInvestment")
#define FUND_INVESTMENT_TAGNAME             QStringLiteral("FundInvestment")
#define GOLD_INVESTMENT_TAGNAME             QStringLiteral("GoldInvestment")
#define STOCK_INVESTMENT_TAGNAME            QStringLiteral("StockInvestment")

#define CRYPTOCURRENCY_ELEMENT_TAGNAME      QStringLiteral("Cryptocurrency")
#define DISCOUNT_BOND_ELEMENT_TAGNAME       QStringLiteral("Discountbond")
#define EXCHANGE_ELEMENT_TAGNAME            QStringLiteral("Exchange")
#define FUND_ELEMENT_TAGNAME                QStringLiteral("Fund")
#define GOLD_ELEMENT_TAGNAME                QStringLiteral("Gold")
#define STOCK_MARKET_ELEMENT_TAGNAME        QStringLiteral("StockMarket")
#define STOCK_ELEMENT_TAGNAME               QStringLiteral("Stock")

#define TRANSACTION_ELEMENT_TAGNAME         QStringLiteral("Transaction")
#define AMOUNT_ELEMENT_TAGNAME              QStringLiteral("Amount")
#define BASE_CURRENCY_ELEMENT_TAGNAME       QStringLiteral("BaseCurrency")
#define PRICE_ELEMENT_TAGNAME               QStringLiteral("Price")
#define COUNT_ELEMENT_TAGNAME               QStringLiteral("Count")
#define EXTRA_EXPENSES_ELEMENT_TAGNAME      QStringLiteral("ExtraExpenses")
#define DATE_ELEMENT_TAGNAME                QStringLiteral("Date")
#define DATETIME_ELEMENT_TAGNAME            QStringLiteral("DateTime")
#define GOAL_PRICE_ELEMENT_TAGNAME          QStringLiteral("GoalPrice")

#define BASE_CURRENCY_ATTRIBUTE_NAME        QStringLiteral("baseCurrency")
#define NAME_ATTRIBUTE_NAME                 QStringLiteral("name")
#define ID_ATTRIBUTE_NAME                   QStringLiteral("id")
#define CODE_ATTRIBUTE_NAME                 QStringLiteral("code")
#define OPERATION_TYPE_ATTRIBUTE_NAME       QStringLiteral("operationType")
#define TERM_ATTRIBUTE_NAME                 QStringLiteral("term")
#define NOMINAL_VALUE_ATTRIBUTE_NAME        QStringLiteral("nominalValue")

namespace lib {

    /**
    * @brief Creates a new portfolio by using the provided parameters.
    * @param filePath : File path of portfolio file.
    * @param pName : Name of portfolio.
    * @param bCurrency : Base currency of portfolio.
    * @param parent
    * @return
    */
    PortfolioXML* PortfolioXML::createPortfolio(const QString &filePath, const QString &pName,
                                                const Util::Currency &bCurrency, QObject *parent)
    {
        PortfolioXML *portfolio = new PortfolioXML(filePath, parent);

        //Get the directory of the file.
        QFileInfo fileInfo(*(portfolio->m_portfolioFile));
        QDir dir(fileInfo.absolutePath());

        //Create the directory if not exists.
        if(!dir.exists())
        {
            if(!dir.mkpath(dir.absolutePath()))
            {
                portfolio->m_state = FileCouldNotBeCreated;
                return portfolio;
            }
        }

        //Open the file with write permission.
        if(!portfolio->m_portfolioFile->open(QIODevice::WriteOnly | QIODevice::Text))
        {
            portfolio->m_state = FileCouldNotBeOpened;
            return portfolio;
        }

        //Create XML document
        QXmlStreamWriter outStream(portfolio->m_portfolioFile);
        outStream.setAutoFormatting(true);
        outStream.writeStartDocument();

        //create root element
        outStream.writeStartElement(PORTFOLIO_ELEMENT_TAGNAME);
        outStream.writeAttribute(NAME_ATTRIBUTE_NAME, pName);
        outStream.writeAttribute(BASE_CURRENCY_ATTRIBUTE_NAME, QVariant::fromValue(bCurrency).toString());

        outStream.writeStartElement(CRYPTOCURRENCY_INVESTMENT_TAGNAME);
        outStream.writeEndElement();

        outStream.writeStartElement(DISCOUNT_BOND_INVESTMENT_TAGNAME);
        outStream.writeEndElement();

        outStream.writeStartElement(EXCHANGE_INVESTMENT_TAGNAME);
        outStream.writeEndElement();

        outStream.writeStartElement(FUND_INVESTMENT_TAGNAME);
        outStream.writeEndElement();

        outStream.writeStartElement(GOLD_INVESTMENT_TAGNAME);
        outStream.writeEndElement();

        outStream.writeStartElement(STOCK_INVESTMENT_TAGNAME);
        outStream.writeEndElement();

        //Close XML document
        outStream.writeEndDocument();

        portfolio->m_portfolioFile->close();
        portfolio->m_portfolioName = pName;
        portfolio->m_baseCurrency = bCurrency;
        portfolio->m_state = Valid;

        return portfolio;
    }

    /**
    * @brief Opens a portfolio by using the provided filePath.
    * @param filePath : File path of portfolio file.
    * @param parent
    * @return
    */
    PortfolioXML* PortfolioXML::openPortfolio(const QString &filePath, QObject *parent)
    {
        PortfolioXML *portfolio = new PortfolioXML(filePath, parent);

        if(portfolio->m_portfolioFile->exists())
        {
            //Check if portfolio file is valid.
            QDomDocument domDocument;
            if(portfolio->loadDomDocument(domDocument))
            {
                QDomElement portfolioElement = domDocument.documentElement();
                portfolio->m_portfolioName = portfolioElement.attribute(NAME_ATTRIBUTE_NAME);
                portfolio->m_baseCurrency = QVariant(portfolioElement.attribute(BASE_CURRENCY_ATTRIBUTE_NAME)).value<Util::Currency>();
                portfolio->m_state = Valid;
            } else {
                portfolio->m_state = FileContentIsNotValid;
            }

            return portfolio;
        }

        return nullptr;
    }

    PortfolioXML::~PortfolioXML()
    {

    }

    bool PortfolioXML::editPortfolio(const QString &pName, const Util::Currency &bCurrency)
    {
        QDomDocument domDocument;
        //Load the DOM document
        if(!loadDomDocument(domDocument))
        {
            return false;
        }

        QDomElement portfolioElement = domDocument.documentElement();
        portfolioElement.setAttribute(NAME_ATTRIBUTE_NAME, pName);
        portfolioElement.setAttribute(BASE_CURRENCY_ATTRIBUTE_NAME, QVariant::fromValue(bCurrency).toString());

        //Save the transaction
        if(!savePortfolio(domDocument))
        {
            m_state = FileCouldNotBeSaved;
            return false;
        }

        m_portfolioName = pName;
        m_baseCurrency = bCurrency;
        return true;
    }

    bool PortfolioXML::saveCryptocurrencyTransaction(const CryptocurrencyTransaction &transaction)
    {
        QDomDocument domDocument;
        QDomElement cryptoCurrencyInvestmentElement;

        //Load the DOM document
        if(!loadDomDocument(domDocument))
        {
            return false;
        }

        if(!findChildElementByTagName(domDocument.documentElement(),
                                      cryptoCurrencyInvestmentElement, CRYPTOCURRENCY_INVESTMENT_TAGNAME))
        {
            //Cryptocurrency investment element does not exist. File is not valid.
            return false;
        }

        QDomElement cryptoCurrencyElement;
        QDomNodeList cryptoCurrencyNodes = cryptoCurrencyInvestmentElement.childNodes();
        for(int i = 0; i < cryptoCurrencyNodes.length(); ++i)
        {
            if(cryptoCurrencyNodes.at(i).isElement() &&
                    cryptoCurrencyNodes.at(i).nodeName() == CRYPTOCURRENCY_ELEMENT_TAGNAME &&
                    cryptoCurrencyNodes.at(i).toElement().attribute(CODE_ATTRIBUTE_NAME) ==
                    QVariant::fromValue(transaction.getCryptocurrency()).toString())
            {
                cryptoCurrencyElement = cryptoCurrencyNodes.at(i).toElement();
                break;
            }
        }

        if(cryptoCurrencyElement.isNull())
        {
            cryptoCurrencyElement = domDocument.createElement(CRYPTOCURRENCY_ELEMENT_TAGNAME);
            cryptoCurrencyElement.setAttribute(CODE_ATTRIBUTE_NAME, QVariant::fromValue(transaction.getCryptocurrency()).toString());
            cryptoCurrencyInvestmentElement.appendChild(cryptoCurrencyElement);
        }

        QDomElement transactionElement = domDocument.createElement(TRANSACTION_ELEMENT_TAGNAME);
        transactionElement.setAttribute(ID_ATTRIBUTE_NAME, transaction.getId().toString(Qt::ISODate));
        transactionElement.setAttribute(OPERATION_TYPE_ATTRIBUTE_NAME, QVariant::fromValue(transaction.getOperationType()).toString());
        cryptoCurrencyElement.appendChild(transactionElement);

        QDomElement amountElement = domDocument.createElement(AMOUNT_ELEMENT_TAGNAME);
        QDomText amountText = domDocument.createTextNode(QString::number(transaction.getAmount()));
        amountElement.appendChild(amountText);
        transactionElement.appendChild(amountElement);

        QDomElement baseCurrencyElement = domDocument.createElement(BASE_CURRENCY_ELEMENT_TAGNAME);
        QDomText baseCurencyText = domDocument.createTextNode(QVariant::fromValue(transaction.getBaseCurrency()).toString());
        baseCurrencyElement.appendChild(baseCurencyText);
        transactionElement.appendChild(baseCurrencyElement);

        QDomElement priceElement = domDocument.createElement(PRICE_ELEMENT_TAGNAME);
        QDomText priceText = domDocument.createTextNode(QString::number(transaction.getPrice()));
        priceElement.appendChild(priceText);
        transactionElement.appendChild(priceElement);

        QDomElement extraExpensesElement = domDocument.createElement(EXTRA_EXPENSES_ELEMENT_TAGNAME);
        QDomText extraExpensesText = domDocument.createTextNode(QString::number(transaction.getExtraExpenses()));
        extraExpensesElement.appendChild(extraExpensesText);
        transactionElement.appendChild(extraExpensesElement);

        QDomElement dateTimeElement = domDocument.createElement(DATETIME_ELEMENT_TAGNAME);
        QDomText dateTimeText = domDocument.createTextNode(transaction.getOperationDateTime().toString(Qt::ISODate));
        dateTimeElement.appendChild(dateTimeText);
        transactionElement.appendChild(dateTimeElement);

        if(transaction.getOperationType() == Util::BUY)
        {
            QDomElement goalPriceElement = domDocument.createElement(GOAL_PRICE_ELEMENT_TAGNAME);
            QDomText goalPriceText = domDocument.createTextNode(QString::number(transaction.getGoalPrice()));
            goalPriceElement.appendChild(goalPriceText);
            transactionElement.appendChild(goalPriceElement);
        }

        //Save the transaction
        if(!savePortfolio(domDocument))
        {
            m_state = FileCouldNotBeSaved;
            return false;
        }

        return true;
    }

    bool PortfolioXML::saveDiscountBondTransaction(const DiscountBondTransaction &transaction)
    {
        QDomDocument domDocument;

        //Load the DOM document
        if(!loadDomDocument(domDocument))
        {
            return false;
        }

        QDomElement discountBondInvestmentElement;

        if(!findChildElementByTagName(domDocument.documentElement(),
                                      discountBondInvestmentElement, DISCOUNT_BOND_INVESTMENT_TAGNAME))
        {
            //Discount bond investment element does not exist. File is not valid.
            return false;
        }

        QDomElement discountBondElement;
        if(!findChildElementByTagName(discountBondInvestmentElement, discountBondElement,
                                      transaction.getISIN().toUpper()))
        {
            //Discount bond element does not exist. Create a new one.
            discountBondElement = domDocument.createElement(transaction.getISIN().toUpper());
            discountBondElement.setAttribute(TERM_ATTRIBUTE_NAME, transaction.getTerm().toString(Qt::ISODate));
            discountBondElement.setAttribute(NOMINAL_VALUE_ATTRIBUTE_NAME, QString::number(transaction.getNominalValue()));
            discountBondInvestmentElement.appendChild(discountBondElement);
        }

        QDomElement transactionElement = domDocument.createElement(TRANSACTION_ELEMENT_TAGNAME);
        transactionElement.setAttribute(OPERATION_TYPE_ATTRIBUTE_NAME, QVariant::fromValue(transaction.getOperationType()).toString());
        discountBondElement.appendChild(transactionElement);

        QDomElement salePriceElement = domDocument.createElement(PRICE_ELEMENT_TAGNAME);
        QDomText salePriceText = domDocument.createTextNode(QString::number(transaction.getSalePrice()));
        salePriceElement.appendChild(salePriceText);
        transactionElement.appendChild(salePriceElement);

        QDomElement countElement = domDocument.createElement(COUNT_ELEMENT_TAGNAME);
        QDomText countText = domDocument.createTextNode(QString::number(transaction.getCount()));
        countElement.appendChild(countText);
        transactionElement.appendChild(countElement);

        QDomElement operationDateElement = domDocument.createElement(DATE_ELEMENT_TAGNAME);
        QDomText operationDateText = domDocument.createTextNode(transaction.getOperationDate().toString(Qt::ISODate));
        operationDateElement.appendChild(operationDateText);
        transactionElement.appendChild(operationDateElement);

        //Save the transaction
        if(!savePortfolio(domDocument))
        {
            m_state = FileCouldNotBeSaved;
            return false;
        }

        return true;
    }

    bool PortfolioXML::saveExchangeTransaction(const ExchangeTransaction &transaction)
    {
        QDomDocument domDocument;

        //Load the DOM document
        if(!loadDomDocument(domDocument))
        {
            return false;
        }

        QDomElement exchangeInvestmentElement;
        if(!findChildElementByTagName(domDocument.documentElement(), exchangeInvestmentElement, EXCHANGE_INVESTMENT_TAGNAME))
        {
            //Exchange investment element does not exist. File is not valid.
            return false;
        }

        QDomElement exchangeElement;
        if(!findChildElementByTagName(exchangeInvestmentElement, exchangeElement,
                                      QVariant::fromValue(transaction.getCurrency()).toString()))
        {
            //Exchange element does not exist. Create a new one.
            exchangeElement = domDocument.createElement(QVariant::fromValue(transaction.getCurrency()).toString());
            exchangeInvestmentElement.appendChild(exchangeElement);
        }

        QDomElement transactionElement = domDocument.createElement(TRANSACTION_ELEMENT_TAGNAME);
        transactionElement.setAttribute(OPERATION_TYPE_ATTRIBUTE_NAME, QVariant::fromValue(transaction.getOperationType()).toString());
        exchangeElement.appendChild(transactionElement);

        QDomElement priceElement = domDocument.createElement(PRICE_ELEMENT_TAGNAME);
        QDomText priceText = domDocument.createTextNode(QString::number(transaction.getPrice()));
        priceElement.appendChild(priceText);
        transactionElement.appendChild(priceElement);

        QDomElement amountElement = domDocument.createElement(AMOUNT_ELEMENT_TAGNAME);
        QDomText amountText = domDocument.createTextNode(QString::number(transaction.getAmount()));
        amountElement.appendChild(amountText);
        transactionElement.appendChild(amountElement);

        QDomElement dateTimeElement = domDocument.createElement(DATETIME_ELEMENT_TAGNAME);
        QDomText dateTimeText = domDocument.createTextNode(transaction.getOperationDateTime().toString(Qt::ISODate));
        dateTimeElement.appendChild(dateTimeText);
        transactionElement.appendChild(dateTimeElement);

        if(transaction.getOperationType() == Util::BUY)
        {
            QDomElement goalPriceElement = domDocument.createElement(GOAL_PRICE_ELEMENT_TAGNAME);
            QDomText goalPriceText = domDocument.createTextNode(QString::number(transaction.getGoalPrice()));
            goalPriceElement.appendChild(goalPriceText);
            transactionElement.appendChild(goalPriceElement);
        }

        //Save the transaction
        if(!savePortfolio(domDocument))
        {
            m_state = FileCouldNotBeSaved;
            return false;
        }

        return true;
    }

    bool PortfolioXML::saveFundTransaction(const FundTransaction &transaction)
    {
        QDomDocument domDocument;

        //Load the DOM document
        if(!loadDomDocument(domDocument))
        {
            return false;
        }

        QDomElement fundInvestmentElement;
        if(!findChildElementByTagName(domDocument.documentElement(), fundInvestmentElement, FUND_INVESTMENT_TAGNAME))
        {
            //Fund investment element does not exist. File is not valid.
            return false;
        }

        QDomElement fundElement;
        if(!findChildElementByTagName(fundInvestmentElement, fundElement, transaction.getFundCode().toUpper()))
        {
            //Fund element does not exist. Create a new one.
            fundElement = domDocument.createElement(transaction.getFundCode().toUpper());
            fundElement.setAttribute(NAME_ATTRIBUTE_NAME, transaction.getFundName());
            fundInvestmentElement.appendChild(fundElement);
        }

        QDomElement transactionElement = domDocument.createElement(TRANSACTION_ELEMENT_TAGNAME);
        transactionElement.setAttribute(OPERATION_TYPE_ATTRIBUTE_NAME, QVariant::fromValue(transaction.getOperationType()).toString());
        fundElement.appendChild(transactionElement);

        QDomElement priceElement = domDocument.createElement(PRICE_ELEMENT_TAGNAME);
        QDomText priceText = domDocument.createTextNode(QString::number(transaction.getPrice()));
        priceElement.appendChild(priceText);
        transactionElement.appendChild(priceElement);

        QDomElement countElement = domDocument.createElement(COUNT_ELEMENT_TAGNAME);
        QDomText countText = domDocument.createTextNode(QString::number(transaction.getCount()));
        countElement.appendChild(countText);
        transactionElement.appendChild(countElement);

        QDomElement orderDateElement = domDocument.createElement("order-date");
        QDomText orderDateText = domDocument.createTextNode(transaction.getOrderDate().toString(Qt::ISODate));
        orderDateElement.appendChild(orderDateText);
        transactionElement.appendChild(orderDateElement);

        QDomElement operationDateElement = domDocument.createElement(DATE_ELEMENT_TAGNAME);
        QDomText operationDateText = domDocument.createTextNode(transaction.getOperationDate().toString(Qt::ISODate));
        operationDateElement.appendChild(operationDateText);
        transactionElement.appendChild(operationDateElement);

        if(transaction.getOperationType() == Util::BUY)
        {
            QDomElement goalPriceElement = domDocument.createElement(GOAL_PRICE_ELEMENT_TAGNAME);
            QDomText goalPriceText = domDocument.createTextNode(QString::number(transaction.getGoalPrice()));
            goalPriceElement.appendChild(goalPriceText);
            transactionElement.appendChild(goalPriceElement);
        }

        //Save the transaction
        if(!savePortfolio(domDocument))
        {
            m_state = FileCouldNotBeSaved;
            return false;
        }

        return true;
    }

    bool PortfolioXML::saveGoldTransaction(const GoldTransaction &transaction)
    {
        QDomDocument domDocument;
        QDomElement goldInvestmentElement;
        QDomElement goldElement;

        //Load the DOM document
        if(!loadDomDocument(domDocument))
        {
            return false;
        }

        if(!findChildElementByTagName(domDocument.documentElement(), goldInvestmentElement, GOLD_INVESTMENT_TAGNAME))
        {
            //Gold investment element does not exist. File is not valid.
            return false;
        }

        if(!findChildElementByTagName(goldInvestmentElement, goldElement,
                                      QVariant::fromValue(transaction.getGoldType()).toString()))
        {
            //Gold element does not exist. Create a new one.
            goldElement = domDocument.createElement(QVariant::fromValue(transaction.getGoldType()).toString());
            goldInvestmentElement.appendChild(goldElement);
        }

        QDomElement transactionElement = domDocument.createElement(TRANSACTION_ELEMENT_TAGNAME);
        transactionElement.setAttribute(OPERATION_TYPE_ATTRIBUTE_NAME, QVariant::fromValue(transaction.getOperationType()).toString());
        goldElement.appendChild(transactionElement);

        QDomElement priceElement = domDocument.createElement(PRICE_ELEMENT_TAGNAME);
        QDomText priceText = domDocument.createTextNode(QString::number(transaction.getPrice()));
        priceElement.appendChild(priceText);
        transactionElement.appendChild(priceElement);

        QDomElement amountElement = domDocument.createElement(AMOUNT_ELEMENT_TAGNAME);
        QDomText amountText = domDocument.createTextNode(QString::number(transaction.getAmount()));
        amountElement.appendChild(amountText);
        transactionElement.appendChild(amountElement);

        QDomElement dateTimeElement = domDocument.createElement(DATETIME_ELEMENT_TAGNAME);
        QDomText dateTimeText = domDocument.createTextNode(transaction.getOperationDateTime().toString(Qt::ISODate));
        dateTimeElement.appendChild(dateTimeText);
        transactionElement.appendChild(dateTimeElement);

        if(transaction.getOperationType() == Util::BUY)
        {
            QDomElement goalPriceElement = domDocument.createElement(GOAL_PRICE_ELEMENT_TAGNAME);
            QDomText goalPriceText = domDocument.createTextNode(QString::number(transaction.getGoalPrice()));
            goalPriceElement.appendChild(goalPriceText);
            transactionElement.appendChild(goalPriceElement);
        }

        //Save the transaction
        if(!savePortfolio(domDocument))
        {
            m_state = FileCouldNotBeSaved;
            return false;
        }

        return true;
    }

    bool PortfolioXML::saveStockTransaction(const StockTransaction &transaction)
    {
        QDomDocument domDocument;

        //Load the DOM document
        if(!loadDomDocument(domDocument))
        {
            return false;
        }

        QDomElement stockInvestmentElement;
        if(!findChildElementByTagName(domDocument.documentElement(), stockInvestmentElement, STOCK_INVESTMENT_TAGNAME))
        {
            //Stock investment element does not exist. File is not valid.
            return false;
        }

        QDomElement stockMarketElement;
        QDomElement stockElement;
        if(!findChildElementByTagName(stockInvestmentElement, stockMarketElement,
                                      QVariant::fromValue(transaction.getStockMarket()).toString()))
        {
            //Stock market element does not exist. Create a new one.
            stockMarketElement = domDocument.createElement(QVariant::fromValue(transaction.getStockMarket()).toString());
            stockInvestmentElement.appendChild(stockMarketElement);
        }

        //Check if stock element exists.
        if(!findChildElementByTagName(stockMarketElement, stockElement, transaction.getStockSymbol()))
        {
            //Stock element does not exist. Create a new one.
            stockElement = domDocument.createElement(transaction.getStockSymbol());
            stockMarketElement.appendChild(stockElement);
            stockElement.setAttribute(NAME_ATTRIBUTE_NAME, transaction.getStockName().toUpper());
        }

        QDomElement transactionElement = domDocument.createElement(TRANSACTION_ELEMENT_TAGNAME);
        transactionElement.setAttribute(OPERATION_TYPE_ATTRIBUTE_NAME, QVariant::fromValue(transaction.getOperationType()).toString());
        stockElement.appendChild(transactionElement);

        QDomElement priceElement = domDocument.createElement(PRICE_ELEMENT_TAGNAME);
        QDomText priceText = domDocument.createTextNode(QString::number(transaction.getPrice()));
        priceElement.appendChild(priceText);
        transactionElement.appendChild(priceElement);

        QDomElement countElement = domDocument.createElement(COUNT_ELEMENT_TAGNAME);
        QDomText countText = domDocument.createTextNode(QString::number(transaction.getCount()));
        countElement.appendChild(countText);
        transactionElement.appendChild(countElement);

        QDomElement commissionRateElement = domDocument.createElement("commission-rate");
        QDomText commissionRateText = domDocument.createTextNode(QString::number(transaction.getCommissionRate()));
        commissionRateElement.appendChild(commissionRateText);
        transactionElement.appendChild(commissionRateElement);

        QDomElement dateTimeElement = domDocument.createElement(DATETIME_ELEMENT_TAGNAME);
        QDomText dateTimeText = domDocument.createTextNode(transaction.getOperationDateTime().toString(Qt::ISODate));
        dateTimeElement.appendChild(dateTimeText);
        transactionElement.appendChild(dateTimeElement);

        if(transaction.getOperationType() == Util::BUY)
        {
            QDomElement goalPriceElement = domDocument.createElement(GOAL_PRICE_ELEMENT_TAGNAME);
            QDomText goalPriceText = domDocument.createTextNode(QString::number(transaction.getGoalPrice()));
            goalPriceElement.appendChild(goalPriceText);
            transactionElement.appendChild(goalPriceElement);
        }

        //Save the transaction
        if(!savePortfolio(domDocument))
        {
            m_state = FileCouldNotBeSaved;
            return false;
        }

        return true;
    }

    QSortFilterProxyModel *PortfolioXML::getCryptocurrencyProxyModel(
            const QList<CryptocurrencyTreeModel::CryptocurrencyFieldHeaderPair> &headerDataList)
    {
        //Check if cryptocurrencyModel & cryptocurrencyProxyModel has been instantiated before.
        if(m_cryptocurrencyProxyModel != nullptr)
        {
            return m_cryptocurrencyProxyModel;
        }

        CryptocurrencyTreeItem *rootItem = new CryptocurrencyTreeItem();

        QDomDocument domDocument;
        if(!loadDomDocument(domDocument))
        {
            return m_cryptocurrencyProxyModel;
        }

        QDomElement cryptoCurrencyInvestmentElement;
        if(!findChildElementByTagName(domDocument.documentElement(),
                                      cryptoCurrencyInvestmentElement,
                                      CRYPTOCURRENCY_INVESTMENT_TAGNAME))
        {
            //Cryptocurrency investment element does not exist. File is not valid.
            return m_cryptocurrencyProxyModel;
        }

        CryptocurrencyTreeItem *cryptocurrencyItem;
        for(QDomElement cryptoCurrencyElement =
            cryptoCurrencyInvestmentElement.firstChildElement(CRYPTOCURRENCY_ELEMENT_TAGNAME);
            !cryptoCurrencyElement.isNull();
            cryptoCurrencyElement = cryptoCurrencyElement.nextSiblingElement(CRYPTOCURRENCY_ELEMENT_TAGNAME))
        {
            Util::Currency currentCryptcurrency =
                    QVariant(cryptoCurrencyElement.attribute(CODE_ATTRIBUTE_NAME)).value<Util::Currency>();
            if(currentCryptcurrency == Util::InvalidCurrency)
            {
                continue;
            }

            cryptocurrencyItem = new CryptocurrencyTreeItem();
            rootItem->appendChildItem(cryptocurrencyItem);
            cryptocurrencyItem->setCryptocurrency(currentCryptcurrency);
            CryptocurrencyTreeItem *transactionItem;

            for(QDomElement transactionElement = cryptoCurrencyElement.firstChildElement(TRANSACTION_ELEMENT_TAGNAME);
                !transactionElement.isNull();
                transactionElement = transactionElement.nextSiblingElement(TRANSACTION_ELEMENT_TAGNAME))
            {
                transactionItem = new CryptocurrencyTreeItem();
                cryptocurrencyItem->appendChildItem(transactionItem);

                transactionItem->setId(QDateTime::fromString(transactionElement.attribute(ID_ATTRIBUTE_NAME), Qt::ISODate));
                transactionItem->setCryptocurrency(QVariant(cryptoCurrencyElement.attribute(CODE_ATTRIBUTE_NAME)).value<Util::Currency>());
                transactionItem->setOperation(QVariant(transactionElement.attribute(OPERATION_TYPE_ATTRIBUTE_NAME)).value<Util::Operation>());

                for(QDomNode transactionChildNode = transactionElement.firstChild();
                    !transactionChildNode.isNull() && transactionChildNode.isElement();
                    transactionChildNode = transactionChildNode.nextSibling())
                {
                    if(transactionChildNode.nodeName() == BASE_CURRENCY_ELEMENT_TAGNAME) {
                        transactionItem->setReferenceCurrency(QVariant(transactionChildNode.toElement().text()).value<Util::Currency>());
                    } else if(transactionChildNode.nodeName() == PRICE_ELEMENT_TAGNAME) {
                        transactionItem->setPrice(transactionChildNode.toElement().text().toDouble());
                    } else if(transactionChildNode.nodeName() == AMOUNT_ELEMENT_TAGNAME) {
                        transactionItem->setAmount(transactionChildNode.toElement().text().toDouble());
                    } else if(transactionChildNode.nodeName() == EXTRA_EXPENSES_ELEMENT_TAGNAME) {
                        transactionItem->setExtraExpenses(transactionChildNode.toElement().text().toDouble());
                    } else if(transactionChildNode.nodeName() == DATETIME_ELEMENT_TAGNAME) {
                        transactionItem->setDateTime(QDateTime::fromString(transactionChildNode.toElement().text(), Qt::ISODate));
                    } else if(transactionChildNode.nodeName() == GOAL_PRICE_ELEMENT_TAGNAME) {
                        transactionItem->setGoalPrice(transactionChildNode.toElement().text().toDouble());
                    } else {
                        //Not yet supported transaction info.
                        continue;
                    }
                }
            }

        }

        m_cryptocurrencyModel = new CryptocurrencyTreeModel(headerDataList, rootItem, this);
        m_cryptocurrencyProxyModel = new QSortFilterProxyModel(this);
        m_cryptocurrencyProxyModel->setSourceModel(m_cryptocurrencyModel);

        return m_cryptocurrencyProxyModel;
    }

    QList<DiscountBondTransaction> PortfolioXML::getDiscountBondTransactionList() const
    {
        QList<DiscountBondTransaction> transactionList;
        QDomDocument domDocument;
        if(!loadDomDocument(domDocument))
        {
            return QList<DiscountBondTransaction>();
        }

        QDomElement discountBondInvestmentElement;
        if(!findChildElementByTagName(domDocument.documentElement(),
                                      discountBondInvestmentElement, DISCOUNT_BOND_INVESTMENT_TAGNAME))
        {
            //Discount bond investment element does not exist. File is not valid.
            return QList<DiscountBondTransaction>();
        }

        QDomNodeList discountBondNodeList = discountBondInvestmentElement.childNodes();
        DiscountBondTransaction transaction;
        for(int discountBondNode = 0; discountBondNode < discountBondNodeList.length(); ++discountBondNode)
        {
            QDomNodeList transactionNodes = discountBondNodeList.at(discountBondNode).childNodes();
            for(int transactionNode = 0; transactionNode < transactionNodes.length(); ++transactionNode)
            {
                if(transactionNodes.at(transactionNode).toElement().tagName() != TRANSACTION_ELEMENT_TAGNAME)
                {
                    //Not a transaction element. Skip this.
                    continue;
                }

                transaction = DiscountBondTransaction();
                transaction.setISIN(discountBondNodeList.at(discountBondNode).toElement().tagName());
                transaction.setTerm(QDate::fromString(discountBondNodeList.at(discountBondNode).toElement().attribute(TERM_ATTRIBUTE_NAME), Qt::ISODate));
                transaction.setNominalValue(discountBondNodeList.at(discountBondNode).toElement().attribute(NOMINAL_VALUE_ATTRIBUTE_NAME).toDouble());

                Util::Operation operation = QVariant(transactionNodes.at(transactionNode).toElement().attribute(OPERATION_TYPE_ATTRIBUTE_NAME)).value<Util::Operation>();
                if(operation == Util::InvalidOperation)
                {
                    //Not yet supported Operation. Skip this one.
                    continue;
                }
                transaction.setOperationType(operation);

                QDomNodeList transactionChildNodes = transactionNodes.at(transactionNode).childNodes();
                for(int transactionChildNode = 0; transactionChildNode < transactionChildNodes.length(); ++transactionChildNode)
                {
                    if(transactionChildNodes.at(transactionChildNode).isElement())
                    {
                        QDomElement transactionChildElement = transactionChildNodes.at(transactionChildNode).toElement();

                        if(transactionChildElement.tagName() == PRICE_ELEMENT_TAGNAME) {
                            transaction.setSalePrice(transactionChildElement.text().toDouble());
                        } else if(transactionChildElement.tagName() == COUNT_ELEMENT_TAGNAME) {
                            transaction.setCount(transactionChildElement.text().toUShort());
                        } else if(transactionChildElement.tagName() == DATE_ELEMENT_TAGNAME) {
                            transaction.setOperationDate(QDate::fromString(transactionChildElement.text(), Qt::ISODate));
                        } else {
                            //Not yet supported transaction info.
                            continue;
                        }
                    }
                }
                transactionList.append(transaction);
            }
        }

        return transactionList;
    }

    QList<ExchangeTransaction> PortfolioXML::getExchangeTransactionList() const
    {
        QList<ExchangeTransaction> transactionList;
        QDomDocument domDocument;
        if(!loadDomDocument(domDocument))
        {
            return QList<ExchangeTransaction>();
        }

        QDomElement exchangeInvestmentElement;
        if(!findChildElementByTagName(domDocument.documentElement(),
                                      exchangeInvestmentElement, EXCHANGE_INVESTMENT_TAGNAME))
        {
            //Exchange investment element does not exist. File is not valid.
            return QList<ExchangeTransaction>();
        }

        QDomNodeList exchangeNodeList = exchangeInvestmentElement.childNodes();
        for(int exchangeNode = 0; exchangeNode < exchangeNodeList.length(); ++exchangeNode)
        {
            Util::Currency currentCurrency = QVariant(exchangeNodeList.at(exchangeNode).toElement().tagName()).value<Util::Currency>();
            if(Util::InvalidCurrency == currentCurrency)
            {
                //Not yet supported currency. Skip this.
                continue;
            }

            QDomNodeList transactionNodes = exchangeNodeList.at(exchangeNode).childNodes();
            ExchangeTransaction transaction;
            for(int transactionNode = 0; transactionNode < transactionNodes.length(); ++transactionNode)
            {
                if(transactionNodes.at(transactionNode).toElement().tagName() != TRANSACTION_ELEMENT_TAGNAME)
                {
                    //Not a transaction element. Skip this.
                    continue;
                }

                transaction = ExchangeTransaction();
                transaction.setCurrency(currentCurrency);

                Util::Operation operation = QVariant(transactionNodes.at(transactionNode).toElement().attribute(OPERATION_TYPE_ATTRIBUTE_NAME)).value<Util::Operation>();
                if(operation == Util::InvalidOperation)
                {
                    //Not yet supported Operation. Skip this one.
                    continue;
                }
                transaction.setOperationType(operation);

                QDomNodeList transactionChildNodes = transactionNodes.at(transactionNode).childNodes();
                for(int transactionChildNode = 0; transactionChildNode < transactionChildNodes.length(); ++transactionChildNode)
                {
                    if(transactionChildNodes.at(transactionChildNode).isElement())
                    {
                        QDomElement transactionChildElement = transactionChildNodes.at(transactionChildNode).toElement();

                        if(transactionChildElement.tagName() == PRICE_ELEMENT_TAGNAME) {
                            transaction.setPrice(transactionChildElement.text().toDouble());
                        } else if(transactionChildElement.tagName() == AMOUNT_ELEMENT_TAGNAME) {
                            transaction.setAmount(transactionChildElement.text().toDouble());
                        } else if(transactionChildElement.tagName() == DATETIME_ELEMENT_TAGNAME) {
                            transaction.setOperationDateTime(QDateTime::fromString(transactionChildElement.text(), Qt::ISODate));
                        } else if(transactionChildElement.tagName() == GOAL_PRICE_ELEMENT_TAGNAME) {
                            transaction.setGoalPrice(transactionChildElement.text().toDouble());
                        } else {
                            //Not yet supported transaction info.
                            continue;
                        }
                    }
                }
                transactionList.append(transaction);
            }
        }

        return transactionList;
    }

    QList<FundTransaction> PortfolioXML::getFundTransactionList() const
    {
        QList<FundTransaction> transactionList;
        QDomDocument domDocument;
        if(!loadDomDocument(domDocument))
        {
            return QList<FundTransaction>();
        }

        QDomElement fundInvestmentElement;
        if(!findChildElementByTagName(domDocument.documentElement(), fundInvestmentElement, FUND_INVESTMENT_TAGNAME))
        {
            //Fund investment element does not exist. File is not valid.
            return QList<FundTransaction>();
        }

        QDomNodeList fundNodeList = fundInvestmentElement.childNodes();
        FundTransaction transaction;
        for(int fundNode = 0; fundNode < fundNodeList.length(); ++fundNode)
        {
            QDomNodeList transactionNodes = fundNodeList.at(fundNode).childNodes();
            for(int transactionNode = 0; transactionNode < transactionNodes.length(); ++transactionNode)
            {
                if(transactionNodes.at(transactionNode).toElement().tagName() != TRANSACTION_ELEMENT_TAGNAME)
                {
                    //Not a transaction element. Skip this.
                    continue;
                }

                transaction = FundTransaction();
                transaction.setFundCode(fundNodeList.at(fundNode).toElement().tagName());
                transaction.setFundName(fundNodeList.at(fundNode).toElement().attribute(NAME_ATTRIBUTE_NAME));

                Util::Operation operation = QVariant(transactionNodes.at(transactionNode).toElement().attribute(OPERATION_TYPE_ATTRIBUTE_NAME)).value<Util::Operation>();
                if(operation == Util::InvalidOperation)
                {
                    //Not yet supported Operation. Skip this one.
                    continue;
                }
                transaction.setOperationType(operation);

                QDomNodeList transactionChildNodes = transactionNodes.at(transactionNode).childNodes();
                for(int transactionChildNode = 0; transactionChildNode < transactionChildNodes.length(); ++transactionChildNode)
                {
                    if(transactionChildNodes.at(transactionChildNode).isElement())
                    {
                        QDomElement transactionChildElement = transactionChildNodes.at(transactionChildNode).toElement();

                        if(transactionChildElement.tagName() == PRICE_ELEMENT_TAGNAME) {
                            transaction.setPrice(transactionChildElement.text().toDouble());
                        } else if(transactionChildElement.tagName() == COUNT_ELEMENT_TAGNAME) {
                            transaction.setCount(transactionChildElement.text().toDouble());
                        } else if(transactionChildElement.tagName() == "order-date") {
                            transaction.setOrderDate(QDate::fromString(transactionChildElement.text(), Qt::ISODate));
                        } else if(transactionChildElement.tagName() == DATE_ELEMENT_TAGNAME) {
                            transaction.setOperationDate(QDate::fromString(transactionChildElement.text(), Qt::ISODate));
                        } else if(transactionChildElement.tagName() == GOAL_PRICE_ELEMENT_TAGNAME) {
                            transaction.setGoalPrice(transactionChildElement.text().toDouble());
                        } else {
                            //Not yet supported transaction info.
                            continue;
                        }
                    }
                }
                transactionList.append(transaction);
            }
        }

        return transactionList;
    }

    QList<GoldTransaction> PortfolioXML::getGoldTransactionList() const
    {
        QList<GoldTransaction> transactionList;
        QDomDocument domDocument;
        if(!loadDomDocument(domDocument))
        {
            return QList<GoldTransaction>();
        }

        QDomElement goldInvestmentElement;
        if(!findChildElementByTagName(domDocument.documentElement(), goldInvestmentElement, GOLD_INVESTMENT_TAGNAME))
        {
            //Gold investment element does not exist. File is not valid.
            return QList<GoldTransaction>();
        }

        QDomNodeList goldNodeList = goldInvestmentElement.childNodes();
        for(int goldNode = 0; goldNode < goldNodeList.length(); ++goldNode)
        {
            Util::Gold currentGold = QVariant(goldNodeList.at(goldNode).toElement().tagName()).value<Util::Gold>();
            if(Util::InvalidGold == currentGold)
            {
                //Not yet supported gold. Skip this.
                continue;
            }

            QDomNodeList transactionNodes = goldNodeList.at(goldNode).childNodes();
            GoldTransaction transaction;
            for(int transactionNode = 0; transactionNode < transactionNodes.length(); ++transactionNode)
            {
                if(transactionNodes.at(transactionNode).toElement().tagName() != TRANSACTION_ELEMENT_TAGNAME)
                {
                    //Not a transaction element. Skip this.
                    continue;
                }

                transaction = GoldTransaction();
                transaction.setGoldType(currentGold);

                Util::Operation operation = QVariant(transactionNodes.at(transactionNode).toElement().attribute(OPERATION_TYPE_ATTRIBUTE_NAME)).value<Util::Operation>();
                if(operation == Util::InvalidOperation)
                {
                    //Not yet supported Operation. Skip this one.
                    continue;
                }
                transaction.setOperationType(operation);

                QDomNodeList transactionChildNodes = transactionNodes.at(transactionNode).childNodes();
                for(int transactionChildNode = 0; transactionChildNode < transactionChildNodes.length(); ++transactionChildNode)
                {
                    if(transactionChildNodes.at(transactionChildNode).isElement())
                    {
                        QDomElement transactionChildElement = transactionChildNodes.at(transactionChildNode).toElement();

                        if(transactionChildElement.tagName() == PRICE_ELEMENT_TAGNAME) {
                            transaction.setPrice(transactionChildElement.text().toDouble());
                        } else if(transactionChildElement.tagName() == AMOUNT_ELEMENT_TAGNAME) {
                            transaction.setAmount(transactionChildElement.text().toDouble());
                        } else if(transactionChildElement.tagName() == DATETIME_ELEMENT_TAGNAME) {
                            transaction.setOperationDateTime(QDateTime::fromString(transactionChildElement.text(), Qt::ISODate));
                        } else if(transactionChildElement.tagName() == GOAL_PRICE_ELEMENT_TAGNAME) {
                            transaction.setGoalPrice(transactionChildElement.text().toDouble());
                        } else {
                            //Not yet supported transaction info.
                            continue;
                        }
                    }
                }
                transactionList.append(transaction);
            }
        }

        return transactionList;
    }

    QList<StockTransaction> PortfolioXML::getStockTransactionList() const
    {
        QList<StockTransaction> transactionList;
        QDomDocument domDocument;
        if(!loadDomDocument(domDocument))
        {
            return QList<StockTransaction>();
        }

        QDomElement stockInvestmentElement;
        if(!findChildElementByTagName(domDocument.documentElement(), stockInvestmentElement, STOCK_INVESTMENT_TAGNAME))
        {
            //Stock investment element does not exist. File is not valid.
            return QList<StockTransaction>();
        }

        QDomNodeList stockMarketNodeList = stockInvestmentElement.childNodes();
        for(int stockMarketNode = 0; stockMarketNode < stockMarketNodeList.length(); ++stockMarketNode)
        {
            Util::StockMarket currentStockMarket =
                    QVariant(stockMarketNodeList.at(stockMarketNode).toElement().tagName()).value<Util::StockMarket>();
            if(Util::InvalidStockMarket == currentStockMarket)
            {
                //Not yet supported stock market. Skip this.
                continue;
            }

            QDomNodeList stockNodeList = stockMarketNodeList.at(stockMarketNode).childNodes();
            for(int stockNode = 0; stockNode < stockNodeList.length(); ++stockNode)
            {
                QDomNodeList transactionNodes = stockNodeList.at(stockNode).childNodes();
                StockTransaction transaction;
                for(int transactionNode = 0; transactionNode < transactionNodes.length(); ++transactionNode)
                {
                    if(transactionNodes.at(transactionNode).toElement().tagName() != TRANSACTION_ELEMENT_TAGNAME)
                    {
                        //Not a transaction element. Skip this.
                        continue;
                    }

                    transaction = StockTransaction();
                    transaction.setStockMarket(currentStockMarket);
                    transaction.setStockSymbol(stockNodeList.at(stockNode).toElement().tagName());
                    transaction.setStockName(stockNodeList.at(stockNode).toElement().attribute(NAME_ATTRIBUTE_NAME));

                    Util::Operation operation = QVariant(transactionNodes.at(transactionNode).toElement().attribute(OPERATION_TYPE_ATTRIBUTE_NAME)).value<Util::Operation>();
                    if(operation == Util::InvalidOperation)
                    {
                        //Not yet supported Operation. Skip this one.
                        continue;
                    }
                    transaction.setOperationType(operation);

                    QDomNodeList transactionChildNodes = transactionNodes.at(transactionNode).childNodes();
                    for(int transactionChildNode = 0; transactionChildNode < transactionChildNodes.length(); ++transactionChildNode)
                    {
                        if(transactionChildNodes.at(transactionChildNode).isElement())
                        {
                            QDomElement transactionChildElement = transactionChildNodes.at(transactionChildNode).toElement();

                            if(transactionChildElement.tagName() == PRICE_ELEMENT_TAGNAME) {
                                transaction.setPrice(transactionChildElement.text().toDouble());
                            } else if(transactionChildElement.tagName() == COUNT_ELEMENT_TAGNAME) {
                                transaction.setCount(transactionChildElement.text().toUShort());
                            } else if(transactionChildElement.tagName() == "commission-rate") {
                                transaction.setCommissionRate(transactionChildElement.text().toDouble());
                            } else if(transactionChildElement.tagName() == DATETIME_ELEMENT_TAGNAME) {
                                transaction.setOperationDateTime(QDateTime::fromString(transactionChildElement.text(), Qt::ISODate));
                            } else if(transactionChildElement.tagName() == GOAL_PRICE_ELEMENT_TAGNAME) {
                                transaction.setGoalPrice(transactionChildElement.text().toDouble());
                            } else {
                                //Not yet supported transaction info.
                                continue;
                            }
                        }
                    }
                    transactionList.append(transaction);
                }

            }
        }

        return transactionList;
    }

    /**
         * @brief Constructs a new object with the given file path.
         * @param filePath : Filepath of portfolio file.
         * @param parent : Parent to own portfolio.
         */
    PortfolioXML::PortfolioXML(const QString &filePath, QObject *parent) :
        AbstractPortfolio(filePath, parent)
    {

    }

    bool PortfolioXML::loadDomDocument(QDomDocument &domDocument) const
    {
        if(!domDocument.setContent(m_portfolioFile, false))
        {
            m_portfolioFile->close();
            return false;
        }

        m_portfolioFile->close();
        return true;
    }

    bool PortfolioXML::findChildElementByTagName(const QDomElement &parent, QDomElement &child, const QString &tagName) const
    {
        QDomNodeList childNodes = parent.elementsByTagName(tagName);
        if(childNodes.length() == 1)
        {
            child = childNodes.at(0).toElement();
            return true;
        }

        return false;
    }

    /**
    * @brief Saves the QDomDocument to portfolio file.
    * @param domDocument : QDomDocument to save.
    * @return
    */
    bool PortfolioXML::savePortfolio(const QDomDocument &domDocument) const
    {
        if(!m_portfolioFile->open(QIODevice::Text | QIODevice::WriteOnly)){
            return false;
        }
        QTextStream outStream(m_portfolioFile);
        domDocument.save(outStream, 4);
        m_portfolioFile->close();
        return true;
    }

}
