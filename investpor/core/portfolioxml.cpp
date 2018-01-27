#include "investpor/core/portfolioxml.h"

#include "investpor/core/types.h"
#include "investpor/core/util.h"

#include <QDir>
#include <QFile>
#include <QFileInfo>
#include <QTextStream>
#include <QXmlStreamWriter>
#include <QXmlStreamReader>
#include <QDomDocument>
#include <QList>

namespace investpor {

    namespace core {

        /**
         * @brief Creates portfolio.
         * @param filePath : Filepath of portfolio file.
         * @param parent : Parent to own portfolio.
         */
        PortfolioXML::PortfolioXML(const QString &filePath, QObject *parent) :
            QObject(parent), portfolioFile(new QFile(filePath, this))
        {
            //Check if portfolio already exists.
            QDomDocument domDocument;

            if(loadDomDocument(domDocument))
            {
                state = PortfolioState::Valid;
                return;
            }

            //Get the directory of the file.
            QFileInfo fileInfo(*portfolioFile);
            QDir dir(fileInfo.absolutePath());

            //Create the directory if not exists.
            if(!dir.exists())
            {
                if(!dir.mkpath(dir.absolutePath()))
                {
                    state = PortfolioState::FolderCouldNotBeCreated;
                    return;
                }
            }

            //Open the file with write permission.
            if(!portfolioFile->open(QIODevice::WriteOnly | QIODevice::Text))
            {
                state = PortfolioState::FileCouldNotBeOpened;
                return;
            }

            //Create XML document
            QXmlStreamWriter outStream(portfolioFile);
            outStream.setAutoFormatting(true);
            outStream.writeStartDocument();

            //create root element
            outStream.writeStartElement("investments");

            outStream.writeStartElement(Util::getInvestmentTagName(Investment::CryptoCurrencyInvestment));
            outStream.writeEndElement();

            outStream.writeStartElement(Util::getInvestmentTagName(Investment::DiscountBondInvestment));
            outStream.writeEndElement();

            outStream.writeStartElement(Util::getInvestmentTagName(Investment::ExchangeInvestment));
            outStream.writeEndElement();

            outStream.writeStartElement(Util::getInvestmentTagName(Investment::FundInvestment));
            outStream.writeEndElement();

            outStream.writeStartElement(Util::getInvestmentTagName(Investment::GoldInvestment));
            outStream.writeEndElement();

            outStream.writeStartElement(Util::getInvestmentTagName(Investment::StockInvestment));
            outStream.writeEndElement();

            //Close XML document
            outStream.writeEndDocument();

            portfolioFile->close();

            state = PortfolioState::Valid;
            return;
        }

        PortfolioXML::~PortfolioXML()
        {

        }

        bool PortfolioXML::saveCryptocurrencyTransaction(const CryptocurrencyTransaction &transaction)
        {
            QDomDocument domDocument;
            QDomElement cryptoCurrencyInvestmentElement;
            QDomElement cryptoCurrencyElement;
            QDomElement transactionElement = domDocument.createElement("transaction");

            //Load the DOM document
            if(!loadDomDocument(domDocument))
            {
                return false;
            }

            if(!findDomElementByTagName(domDocument, cryptoCurrencyElement,
                Util::cryptoCurrencySymbol(transaction.getCryptocurrency()).toLower()))
            {
                //Cryptocurrency element does not exist. Create a new one.
                if(!findDomElementByTagName(domDocument, cryptoCurrencyInvestmentElement,
                    Util::getInvestmentTagName(Investment::CryptoCurrencyInvestment)))
                {
                    return false;
                }

                cryptoCurrencyElement = domDocument.createElement(Util::cryptoCurrencySymbol(transaction.getCryptocurrency()).toLower());
                cryptoCurrencyInvestmentElement.appendChild(cryptoCurrencyElement);
                transactionElement.setAttribute("id", 1);
            } else {
                transactionElement.setAttribute("id", cryptoCurrencyElement.lastChild().toElement().attribute("id").toInt() + 1);
            }

            transactionElement.setAttribute("type", Util::operationCode(transaction.getOperationType()));
            cryptoCurrencyElement.appendChild(transactionElement);

            QDomElement priceElement = domDocument.createElement("price");
            QDomText priceText = domDocument.createTextNode(QString::number(transaction.getPrice()));
            priceElement.appendChild(priceText);
            transactionElement.appendChild(priceElement);

            QDomElement amountElement = domDocument.createElement("amount");
            QDomText amountText = domDocument.createTextNode(QString::number(transaction.getAmount()));
            amountElement.appendChild(amountText);
            transactionElement.appendChild(amountElement);

            QDomElement dateTimeElement = domDocument.createElement("date-time");
            QDomText dateTimeText = domDocument.createTextNode(transaction.getOperationDateTime().toString("yyyy-MM-dd hh:mm:ss"));
            dateTimeElement.appendChild(dateTimeText);
            transactionElement.appendChild(dateTimeElement);

            if(transaction.getOperationType() == Operation::BUY)
            {
                QDomElement goalPriceElement = domDocument.createElement("goal-price");
                QDomText goalPriceText = domDocument.createTextNode(QString::number(transaction.getGoalPrice()));
                goalPriceElement.appendChild(goalPriceText);
                transactionElement.appendChild(goalPriceElement);
            }

            //Save the transaction
            if(!savePortfolio(domDocument))
            {
                return false;
            }

            return true;
        }

        bool PortfolioXML::saveDiscountBondTransaction(const DiscountBondTransaction &transaction)
        {
            QDomDocument domDocument;
            QDomElement discountBondInvestmentElement;
            QDomElement discountBondElement;
            QDomElement transactionElement = domDocument.createElement("transaction");

            //Load the DOM document
            if(!loadDomDocument(domDocument))
            {
                return false;
            }

            if(!findDomElementByTagName(domDocument, discountBondElement, transaction.getISIN().toLower()))
            {
                //Discount bond element does not exist. Create a new one.
                if(!findDomElementByTagName(domDocument, discountBondInvestmentElement,
                    Util::getInvestmentTagName(Investment::DiscountBondInvestment)))
                {
                    return false;
                }

                discountBondElement = domDocument.createElement(transaction.getISIN().toLower());
                discountBondElement.setAttribute("term", transaction.getTerm().toString("yyyy-MM-dd"));
                discountBondElement.setAttribute("nominal-value", QString::number(transaction.getNominalValue()));
                discountBondInvestmentElement.appendChild(discountBondElement);
                transactionElement.setAttribute("id", 1);
            } else {
                transactionElement.setAttribute("id", discountBondElement.lastChild().toElement().attribute("id").toInt() + 1);
            }

            transactionElement.setAttribute("type", Util::operationCode(transaction.getOperationType()));
            discountBondElement.appendChild(transactionElement);

            QDomElement salePriceElement = domDocument.createElement("sale-price");
            QDomText salePriceText = domDocument.createTextNode(QString::number(transaction.getSalePrice()));
            salePriceElement.appendChild(salePriceText);
            transactionElement.appendChild(salePriceElement);

            QDomElement operationDateElement = domDocument.createElement("operation-date");
            QDomText operationDateText = domDocument.createTextNode(transaction.getOperationDate().toString("yyyy-MM-dd"));
            operationDateElement.appendChild(operationDateText);
            transactionElement.appendChild(operationDateElement);

            //Save the transaction
            if(!savePortfolio(domDocument))
            {
                return false;
            }

            return true;
        }

        bool PortfolioXML::saveExchangeTransaction(const ExchangeTransaction &transaction)
        {
            QDomDocument domDocument;
            QDomElement exchangeInvestmentElement;
            QDomElement exchangeElement;
            QDomElement transactionElement = domDocument.createElement("transaction");

            //Load the DOM document
            if(!loadDomDocument(domDocument))
            {
                return false;
            }

            if(!findDomElementByTagName(domDocument, exchangeElement, Util::currencySymbol(transaction.getCurrency()).toLower()))
            {
                //Exchange element does not exist. Create a new one.
                if(!findDomElementByTagName(domDocument, exchangeInvestmentElement,
                    Util::getInvestmentTagName(Investment::ExchangeInvestment)))
                {
                    return false;
                }

                exchangeElement = domDocument.createElement(Util::currencySymbol(transaction.getCurrency()).toLower());
                exchangeInvestmentElement.appendChild(exchangeElement);
                transactionElement.setAttribute("id", 1);
            } else {
                transactionElement.setAttribute("id", exchangeElement.lastChild().toElement().attribute("id").toInt() + 1);
            }

            transactionElement.setAttribute("type", Util::operationCode(transaction.getOperationType()));
            exchangeElement.appendChild(transactionElement);

            QDomElement priceElement = domDocument.createElement("price");
            QDomText priceText = domDocument.createTextNode(QString::number(transaction.getPrice()));
            priceElement.appendChild(priceText);
            transactionElement.appendChild(priceElement);

            QDomElement amountElement = domDocument.createElement("amount");
            QDomText amountText = domDocument.createTextNode(QString::number(transaction.getAmount()));
            amountElement.appendChild(amountText);
            transactionElement.appendChild(amountElement);

            QDomElement dateTimeElement = domDocument.createElement("date-time");
            QDomText dateTimeText = domDocument.createTextNode(transaction.getOperationDateTime().toString("yyyy-MM-dd hh:mm:ss"));
            dateTimeElement.appendChild(dateTimeText);
            transactionElement.appendChild(dateTimeElement);

            if(transaction.getOperationType() == Operation::BUY)
            {
                QDomElement goalPriceElement = domDocument.createElement("goal-price");
                QDomText goalPriceText = domDocument.createTextNode(QString::number(transaction.getGoalPrice()));
                goalPriceElement.appendChild(goalPriceText);
                transactionElement.appendChild(goalPriceElement);
            }

            //Save the transaction
            if(!savePortfolio(domDocument))
            {
                return false;
            }

            return true;
        }

        bool PortfolioXML::saveFundTransaction(const FundTransaction &transaction)
        {
            QDomDocument domDocument;
            QDomElement fundInvestmentElement;
            QDomElement fundElement;
            QDomElement transactionElement = domDocument.createElement("transaction");

            //Load the DOM document
            if(!loadDomDocument(domDocument))
            {
                return false;
            }

            if(!findDomElementByTagName(domDocument, fundElement, transaction.getFundCode().toLower()))
            {
                //Fund element does not exist. Create a new one.
                if(!findDomElementByTagName(domDocument, fundInvestmentElement,
                    Util::getInvestmentTagName(Investment::FundInvestment)))
                {
                    return false;
                }

                fundElement = domDocument.createElement(transaction.getFundCode().toLower());
                fundElement.setAttribute("name", transaction.getFundName());
                fundInvestmentElement.appendChild(fundElement);
                transactionElement.setAttribute("id", 1);
            } else {
                transactionElement.setAttribute("id", fundElement.lastChild().toElement().attribute("id").toInt() + 1);
            }

            transactionElement.setAttribute("type", Util::operationCode(transaction.getOperationType()));
            fundElement.appendChild(transactionElement);

            QDomElement priceElement = domDocument.createElement("price");
            QDomText priceText = domDocument.createTextNode(QString::number(transaction.getPrice()));
            priceElement.appendChild(priceText);
            transactionElement.appendChild(priceElement);

            QDomElement countElement = domDocument.createElement("count");
            QDomText countText = domDocument.createTextNode(QString::number(transaction.getCount()));
            countElement.appendChild(countText);
            transactionElement.appendChild(countElement);

            QDomElement orderDateElement = domDocument.createElement("order-date");
            QDomText orderDateText = domDocument.createTextNode(transaction.getOrderDate().toString("yyyy-MM-dd"));
            orderDateElement.appendChild(orderDateText);
            transactionElement.appendChild(orderDateElement);

            QDomElement operationDateElement = domDocument.createElement("order-date");
            QDomText operationDateText = domDocument.createTextNode(transaction.getOperationDate().toString("yyyy-MM-dd"));
            operationDateElement.appendChild(operationDateText);
            transactionElement.appendChild(operationDateElement);

            if(transaction.getOperationType() == Operation::BUY)
            {
                QDomElement goalPriceElement = domDocument.createElement("goal-price");
                QDomText goalPriceText = domDocument.createTextNode(QString::number(transaction.getGoalPrice()));
                goalPriceElement.appendChild(goalPriceText);
                transactionElement.appendChild(goalPriceElement);
            }

            //Save the transaction
            if(!savePortfolio(domDocument))
            {
                return false;
            }

            return true;
        }

        bool PortfolioXML::saveGoldTransaction(const GoldTransaction &transaction)
        {
            QDomDocument domDocument;
            QDomElement goldInvestmentElement;
            QDomElement goldElement;
            QDomElement transactionElement = domDocument.createElement("transaction");

            //Load the DOM document
            if(!loadDomDocument(domDocument))
            {
                return false;
            }

            if(!findDomElementByTagName(domDocument, goldElement, Util::goldSymbol(transaction.getGoldType()).toLower()))
            {
                //Gold element does not exist. Create a new one.
                if(!findDomElementByTagName(domDocument, goldInvestmentElement,
                    Util::getInvestmentTagName(Investment::GoldInvestment)))
                {
                    return false;
                }

                goldElement = domDocument.createElement(Util::goldSymbol(transaction.getGoldType()).toLower());
                goldInvestmentElement.appendChild(goldElement);
                transactionElement.setAttribute("id", 1);
            } else {
                transactionElement.setAttribute("id", goldElement.lastChild().toElement().attribute("id").toInt() + 1);
            }

            transactionElement.setAttribute("type", Util::operationCode(transaction.getOperationType()));
            goldElement.appendChild(transactionElement);

            QDomElement priceElement = domDocument.createElement("price");
            QDomText priceText = domDocument.createTextNode(QString::number(transaction.getPrice()));
            priceElement.appendChild(priceText);
            transactionElement.appendChild(priceElement);

            QDomElement amountElement = domDocument.createElement("amount");
            QDomText amountText = domDocument.createTextNode(QString::number(transaction.getAmount()));
            amountElement.appendChild(amountText);
            transactionElement.appendChild(amountElement);

            QDomElement dateTimeElement = domDocument.createElement("date-time");
            QDomText dateTimeText = domDocument.createTextNode(transaction.getOperationDateTime().toString("yyyy-MM-dd hh:mm:ss"));
            dateTimeElement.appendChild(dateTimeText);
            transactionElement.appendChild(dateTimeElement);

            if(transaction.getOperationType() == Operation::BUY)
            {
                QDomElement goalPriceElement = domDocument.createElement("goal-price");
                QDomText goalPriceText = domDocument.createTextNode(QString::number(transaction.getGoalPrice()));
                goalPriceElement.appendChild(goalPriceText);
                transactionElement.appendChild(goalPriceElement);
            }

            //Save the transaction
            if(!savePortfolio(domDocument))
            {
                return false;
            }

            return true;
        }

        bool PortfolioXML::saveStockTransaction(const StockTransaction &transaction)
        {
            QDomDocument domDocument;
            QDomElement stockInvestmentElement;
            QDomElement stockMarketElement;
            QDomElement stockElement;
            QDomElement transactionElement = domDocument.createElement("transaction");

            //Load the DOM document
            if(!loadDomDocument(domDocument))
            {
                return false;
            }

            if(!findDomElementByTagName(domDocument, stockMarketElement, Util::stockMarketSymbol(transaction.getStockMarket()).toLower()))
            {
                //Stock market element does not exist. Create a new one.
                if(!findDomElementByTagName(domDocument, stockInvestmentElement,
                    Util::getInvestmentTagName(Investment::StockInvestment)))
                {
                    return false;
                }

                stockMarketElement = domDocument.createElement(Util::stockMarketSymbol(transaction.getStockMarket()).toLower());
                stockInvestmentElement.appendChild(stockMarketElement);
                stockElement = domDocument.createElement(transaction.getStockSymbol());
                stockMarketElement.appendChild(stockElement);
                stockElement.setAttribute("name", transaction.getStockName().toLower());
                transactionElement.setAttribute("id", 1);
            } else {
                //Stock market element exists. Check if stock element exists.
                QDomNodeList stockElements = stockMarketElement.elementsByTagName(transaction.getStockSymbol());

                if(stockElements.length() == 1)
                {
                    stockElement = stockElements.at(0).toElement();
                }
                transactionElement.setAttribute("id", stockElement.lastChild().toElement().attribute("id").toInt() + 1);
            }

            transactionElement.setAttribute("type", Util::operationCode(transaction.getOperationType()));
            stockElement.appendChild(transactionElement);

            QDomElement priceElement = domDocument.createElement("price");
            QDomText priceText = domDocument.createTextNode(QString::number(transaction.getPrice()));
            priceElement.appendChild(priceText);
            transactionElement.appendChild(priceElement);

            QDomElement countElement = domDocument.createElement("count");
            QDomText countText = domDocument.createTextNode(QString::number(transaction.getCount()));
            countElement.appendChild(countText);
            transactionElement.appendChild(countElement);

            QDomElement commissionRateElement = domDocument.createElement("commission-rate");
            QDomText commissionRateText = domDocument.createTextNode(QString::number(transaction.getCommissionRate()));
            commissionRateElement.appendChild(commissionRateText);
            transactionElement.appendChild(commissionRateElement);

            QDomElement dateTimeElement = domDocument.createElement("date-time");
            QDomText dateTimeText = domDocument.createTextNode(transaction.getOperationDateTime().toString("yyyy-MM-dd hh:mm:ss"));
            dateTimeElement.appendChild(dateTimeText);
            transactionElement.appendChild(dateTimeElement);

            if(transaction.getOperationType() == Operation::BUY)
            {
                QDomElement goalPriceElement = domDocument.createElement("goal-price");
                QDomText goalPriceText = domDocument.createTextNode(QString::number(transaction.getGoalPrice()));
                goalPriceElement.appendChild(goalPriceText);
                transactionElement.appendChild(goalPriceElement);
            }

            //Save the transaction
            if(!savePortfolio(domDocument))
            {
                return false;
            }

            return true;
        }

        QList<CryptocurrencyTransaction> PortfolioXML::getCryptoCurrencyTransactionList() const
        {
            //TODO
            return QList<CryptocurrencyTransaction>();
        }

        QList<DiscountBondTransaction> PortfolioXML::getDiscountBondTransactionList() const
        {
            //TODO
            return QList<DiscountBondTransaction>();
        }

        QList<ExchangeTransaction> PortfolioXML::getExchangeTransactionList() const
        {
            //TODO
            return QList<ExchangeTransaction>();
        }

        QList<FundTransaction> PortfolioXML::getFundTransactionList() const
        {
            //TODO
            return QList<FundTransaction>();
        }

        QList<GoldTransaction> PortfolioXML::getGoldTransactionList() const
        {
            //TODO
            return QList<GoldTransaction>();
        }

        QList<StockTransaction> PortfolioXML::getStockTransactionList() const
        {
            //TODO
            return QList<StockTransaction>();
        }

        bool PortfolioXML::loadDomDocument(QDomDocument &domDocument)
        {
            domDocument.setContent(portfolioFile, false);
            portfolioFile->close();

            //Check if XML is valid.
            if(domDocument.isNull())
            {
                state = PortfolioState::FileContentIsNotValid;
                return false;
            }

            return true;
        }

        bool PortfolioXML::findDomElementByTagName(const QDomDocument &domDocument, QDomElement &domElement, const QString &tagName)
        {
            //Find out if the child element has been created previously.
            QDomNodeList domElementNodes = domDocument.elementsByTagName(tagName);
            if(domElementNodes.length() == 1)
            {
                domElement = domElementNodes.at(0).toElement();
                return true;
            }

            return false;
        }

        bool PortfolioXML::savePortfolio(const QDomDocument &domDocument)
        {
            if(!portfolioFile->open(QIODevice::Text | QIODevice::WriteOnly)){
                state = FileCouldNotBeSaved;
                return false;
            }
            QTextStream outStream(portfolioFile);
            domDocument.save(outStream, 4);
            portfolioFile->close();
            return true;
        }

    }

}
