#include "investpor/core/portfolioxml.h"

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
            QFileInfo fileInfo(*(portfolio->portfolioFile));
            QDir dir(fileInfo.absolutePath());

            //Create the directory if not exists.
            if(!dir.exists())
            {
                if(!dir.mkpath(dir.absolutePath()))
                {
                    portfolio->state = FileCouldNotBeCreated;
                    return portfolio;
                }
            }

            //Open the file with write permission.
            if(!portfolio->portfolioFile->open(QIODevice::WriteOnly | QIODevice::Text))
            {
                portfolio->state = FileCouldNotBeOpened;
                return portfolio;
            }

            //Create XML document
            QXmlStreamWriter outStream(portfolio->portfolioFile);
            outStream.setAutoFormatting(true);
            outStream.writeStartDocument();

            //create root element
            outStream.writeStartElement("portfolio");
            outStream.writeAttribute("name", pName);
            outStream.writeAttribute("currency", Util::currencySymbol(bCurrency).toLower());

            outStream.writeStartElement(Util::getInvestmentTagName(Util::CryptocurrencyInvestment));
            outStream.writeEndElement();

            outStream.writeStartElement(Util::getInvestmentTagName(Util::DiscountBondInvestment));
            outStream.writeEndElement();

            outStream.writeStartElement(Util::getInvestmentTagName(Util::ExchangeInvestment));
            outStream.writeEndElement();

            outStream.writeStartElement(Util::getInvestmentTagName(Util::FundInvestment));
            outStream.writeEndElement();

            outStream.writeStartElement(Util::getInvestmentTagName(Util::GoldInvestment));
            outStream.writeEndElement();

            outStream.writeStartElement(Util::getInvestmentTagName(Util::StockInvestment));
            outStream.writeEndElement();

            //Close XML document
            outStream.writeEndDocument();

            portfolio->portfolioFile->close();
            portfolio->portfolioName = pName;
            portfolio->baseCurrency = bCurrency;
            portfolio->state = Valid;

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

            if(portfolio->portfolioFile->exists()) {
                //Check if portfolio file is valid.
                QDomDocument domDocument;
                if(portfolio->loadDomDocument(domDocument))
                {
                    QDomElement portfolioElement = domDocument.documentElement();
                    portfolio->portfolioName = portfolioElement.attribute("name");
                    portfolio->baseCurrency = Util::getCurrency(portfolioElement.attribute("currency"));
                    portfolio->state = Valid;
                } else {
                    portfolio->state = FileContentIsNotValid;
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
            portfolioElement.setAttribute("name", pName);
            portfolioElement.setAttribute("currency", Util::currencySymbol(bCurrency));

            //Save the transaction
            if(!savePortfolio(domDocument))
            {
                state = FileCouldNotBeSaved;
                return false;
            }

            portfolioName = pName;
            baseCurrency = bCurrency;
            return true;
        }

        /**
         * @brief Returns CanonicalFilePath of portfolio file.
         * @return CanonicalFilePath of portfolio file.
         */
        const QString PortfolioXML::getPortfolioFilePath() const
        {
            QFileInfo fileInfo(*portfolioFile);
            return fileInfo.canonicalFilePath();
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

            if(!findChildElementByTagName(domDocument.documentElement(), cryptoCurrencyInvestmentElement,
                                                Util::getInvestmentTagName(Util::CryptocurrencyInvestment)))
            {
                //Cryptocurrency investment element does not exist. File is not valid.
                return false;
            }

            QDomElement cryptoCurrencyElement;
            if(!findChildElementByTagName(cryptoCurrencyInvestmentElement, cryptoCurrencyElement,
                                                Util::currencySymbol(transaction.getCryptocurrency()).toLower()))
            {
                //Cryptocurrency element does not exist. Create a new one.
                cryptoCurrencyElement = domDocument.createElement(Util::currencySymbol(transaction.getCryptocurrency()).toLower());
                cryptoCurrencyInvestmentElement.appendChild(cryptoCurrencyElement);
            }

            QDomElement transactionElement = domDocument.createElement("transaction");
            transactionElement.setAttribute("type", Util::operationCode(transaction.getOperationType()).toLower());
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
            QDomText dateTimeText = domDocument.createTextNode(transaction.getOperationDateTime().toString(Qt::ISODate));
            dateTimeElement.appendChild(dateTimeText);
            transactionElement.appendChild(dateTimeElement);

            if(transaction.getOperationType() == Util::BUY)
            {
                QDomElement goalPriceElement = domDocument.createElement("goal-price");
                QDomText goalPriceText = domDocument.createTextNode(QString::number(transaction.getGoalPrice()));
                goalPriceElement.appendChild(goalPriceText);
                transactionElement.appendChild(goalPriceElement);
            }

            //Save the transaction
            if(!savePortfolio(domDocument))
            {
                state = FileCouldNotBeSaved;
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

            if(!findChildElementByTagName(domDocument.documentElement(), discountBondInvestmentElement,
                                                Util::getInvestmentTagName(Util::DiscountBondInvestment)))
            {
                //Discount bond investment element does not exist. File is not valid.
                return false;
            }

            QDomElement discountBondElement;
            if(!findChildElementByTagName(discountBondInvestmentElement, discountBondElement,
                                                transaction.getISIN().toLower()))
            {
                //Discount bond element does not exist. Create a new one.
                discountBondElement = domDocument.createElement(transaction.getISIN().toLower());
                discountBondElement.setAttribute("term", transaction.getTerm().toString(Qt::ISODate));
                discountBondElement.setAttribute("nominal-value", QString::number(transaction.getNominalValue()));
                discountBondInvestmentElement.appendChild(discountBondElement);
            }

            QDomElement transactionElement = domDocument.createElement("transaction");
            transactionElement.setAttribute("type", Util::operationCode(transaction.getOperationType()).toLower());
            discountBondElement.appendChild(transactionElement);

            QDomElement salePriceElement = domDocument.createElement("sale-price");
            QDomText salePriceText = domDocument.createTextNode(QString::number(transaction.getSalePrice()));
            salePriceElement.appendChild(salePriceText);
            transactionElement.appendChild(salePriceElement);

            QDomElement countElement = domDocument.createElement("count");
            QDomText countText = domDocument.createTextNode(QString::number(transaction.getCount()));
            countElement.appendChild(countText);
            transactionElement.appendChild(countElement);

            QDomElement operationDateElement = domDocument.createElement("operation-date");
            QDomText operationDateText = domDocument.createTextNode(transaction.getOperationDate().toString(Qt::ISODate));
            operationDateElement.appendChild(operationDateText);
            transactionElement.appendChild(operationDateElement);

            //Save the transaction
            if(!savePortfolio(domDocument))
            {
                state = FileCouldNotBeSaved;
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
            if(!findChildElementByTagName(domDocument.documentElement(), exchangeInvestmentElement,
                                                Util::getInvestmentTagName(Util::ExchangeInvestment)))
            {
                //Exchange investment element does not exist. File is not valid.
                return false;
            }

            QDomElement exchangeElement;
            if(!findChildElementByTagName(exchangeInvestmentElement, exchangeElement,
                                                Util::currencySymbol(transaction.getCurrency()).toLower()))
            {
                //Exchange element does not exist. Create a new one.
                exchangeElement = domDocument.createElement(Util::currencySymbol(transaction.getCurrency()).toLower());
                exchangeInvestmentElement.appendChild(exchangeElement);
            }

            QDomElement transactionElement = domDocument.createElement("transaction");
            transactionElement.setAttribute("type", Util::operationCode(transaction.getOperationType()).toLower());
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
            QDomText dateTimeText = domDocument.createTextNode(transaction.getOperationDateTime().toString(Qt::ISODate));
            dateTimeElement.appendChild(dateTimeText);
            transactionElement.appendChild(dateTimeElement);

            if(transaction.getOperationType() == Util::BUY)
            {
                QDomElement goalPriceElement = domDocument.createElement("goal-price");
                QDomText goalPriceText = domDocument.createTextNode(QString::number(transaction.getGoalPrice()));
                goalPriceElement.appendChild(goalPriceText);
                transactionElement.appendChild(goalPriceElement);
            }

            //Save the transaction
            if(!savePortfolio(domDocument))
            {
                state = FileCouldNotBeSaved;
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
            if(!findChildElementByTagName(domDocument.documentElement(), fundInvestmentElement,
                                                Util::getInvestmentTagName(Util::FundInvestment)))
            {
                //Fund investment element does not exist. File is not valid.
                return false;
            }

            QDomElement fundElement;
            if(!findChildElementByTagName(fundInvestmentElement, fundElement, transaction.getFundCode().toLower()))
            {
                //Fund element does not exist. Create a new one.
                fundElement = domDocument.createElement(transaction.getFundCode().toLower());
                fundElement.setAttribute("name", transaction.getFundName());
                fundInvestmentElement.appendChild(fundElement);
            }

            QDomElement transactionElement = domDocument.createElement("transaction");
            transactionElement.setAttribute("type", Util::operationCode(transaction.getOperationType()).toLower());
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
            QDomText orderDateText = domDocument.createTextNode(transaction.getOrderDate().toString(Qt::ISODate));
            orderDateElement.appendChild(orderDateText);
            transactionElement.appendChild(orderDateElement);

            QDomElement operationDateElement = domDocument.createElement("operation-date");
            QDomText operationDateText = domDocument.createTextNode(transaction.getOperationDate().toString(Qt::ISODate));
            operationDateElement.appendChild(operationDateText);
            transactionElement.appendChild(operationDateElement);

            if(transaction.getOperationType() == Util::BUY)
            {
                QDomElement goalPriceElement = domDocument.createElement("goal-price");
                QDomText goalPriceText = domDocument.createTextNode(QString::number(transaction.getGoalPrice()));
                goalPriceElement.appendChild(goalPriceText);
                transactionElement.appendChild(goalPriceElement);
            }

            //Save the transaction
            if(!savePortfolio(domDocument))
            {
                state = FileCouldNotBeSaved;
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

            if(!findChildElementByTagName(domDocument.documentElement(), goldInvestmentElement,
                                                Util::getInvestmentTagName(Util::GoldInvestment)))
            {
                //Gold investment element does not exist. File is not valid.
                return false;
            }

            if(!findChildElementByTagName(goldInvestmentElement, goldElement,
                                                Util::goldSymbol(transaction.getGoldType()).toLower()))
            {
                //Gold element does not exist. Create a new one.
                goldElement = domDocument.createElement(Util::goldSymbol(transaction.getGoldType()).toLower());
                goldInvestmentElement.appendChild(goldElement);
            }

            QDomElement transactionElement = domDocument.createElement("transaction");
            transactionElement.setAttribute("type", Util::operationCode(transaction.getOperationType()).toLower());
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
            QDomText dateTimeText = domDocument.createTextNode(transaction.getOperationDateTime().toString(Qt::ISODate));
            dateTimeElement.appendChild(dateTimeText);
            transactionElement.appendChild(dateTimeElement);

            if(transaction.getOperationType() == Util::BUY)
            {
                QDomElement goalPriceElement = domDocument.createElement("goal-price");
                QDomText goalPriceText = domDocument.createTextNode(QString::number(transaction.getGoalPrice()));
                goalPriceElement.appendChild(goalPriceText);
                transactionElement.appendChild(goalPriceElement);
            }

            //Save the transaction
            if(!savePortfolio(domDocument))
            {
                state = FileCouldNotBeSaved;
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
            if(!findChildElementByTagName(domDocument.documentElement(), stockInvestmentElement,
                                                Util::getInvestmentTagName(Util::StockInvestment)))
            {
                //Stock investment element does not exist. File is not valid.
                return false;
            }

            QDomElement stockMarketElement;
            QDomElement stockElement;
            if(!findChildElementByTagName(stockInvestmentElement, stockMarketElement,
                                                Util::stockMarketSymbol(transaction.getStockMarket()).toLower()))
            {
                //Stock market element does not exist. Create a new one.
                stockMarketElement = domDocument.createElement(Util::stockMarketSymbol(transaction.getStockMarket()).toLower());
                stockInvestmentElement.appendChild(stockMarketElement);
            }

            //Check if stock element exists.
            if(!findChildElementByTagName(stockMarketElement, stockElement, transaction.getStockSymbol().toLower()))
            {
                //Stock element does not exist. Create a new one.
                stockElement = domDocument.createElement(transaction.getStockSymbol().toLower());
                stockMarketElement.appendChild(stockElement);
                stockElement.setAttribute("name", transaction.getStockName().toLower());
            }

            QDomElement transactionElement = domDocument.createElement("transaction");
            transactionElement.setAttribute("type", Util::operationCode(transaction.getOperationType()).toLower());
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
            QDomText dateTimeText = domDocument.createTextNode(transaction.getOperationDateTime().toString(Qt::ISODate));
            dateTimeElement.appendChild(dateTimeText);
            transactionElement.appendChild(dateTimeElement);

            if(transaction.getOperationType() == Util::BUY)
            {
                QDomElement goalPriceElement = domDocument.createElement("goal-price");
                QDomText goalPriceText = domDocument.createTextNode(QString::number(transaction.getGoalPrice()));
                goalPriceElement.appendChild(goalPriceText);
                transactionElement.appendChild(goalPriceElement);
            }

            //Save the transaction
            if(!savePortfolio(domDocument))
            {
                state = FileCouldNotBeSaved;
                return false;
            }

            return true;
        }

        QList<CryptocurrencyTransaction> PortfolioXML::getCryptocurrencyTransactionList() const
        {
            QList<CryptocurrencyTransaction> transactionList;
            QDomDocument domDocument;
            if(!loadDomDocument(domDocument))
            {
                return QList<CryptocurrencyTransaction>();
            }

            QDomElement cryptoCurrencyInvestmentElement;
            if(!findChildElementByTagName(domDocument.documentElement(), cryptoCurrencyInvestmentElement,
                                                Util::getInvestmentTagName(Util::CryptocurrencyInvestment)))
            {
                //Cryptocurrency investment element does not exist. File is not valid.
                return QList<CryptocurrencyTransaction>();
            }

            QDomNodeList cryptoCurrencyNodeList = cryptoCurrencyInvestmentElement.childNodes();
            for(int cryptoCurrencyNode = 0; cryptoCurrencyNode < cryptoCurrencyNodeList.length(); ++cryptoCurrencyNode)
            {
                Util::Currency currentCryptocurrency = Util::getCurrency(
                            cryptoCurrencyNodeList.at(cryptoCurrencyNode).toElement().tagName());
                if(currentCryptocurrency == Util::InvalidCurrency)
                {
                    //Not yet supported Cryptocurrency. Skip this.
                    continue;
                }

                QDomNodeList transactionNodes = cryptoCurrencyNodeList.at(cryptoCurrencyNode).childNodes();
                CryptocurrencyTransaction transaction;
                for(int transactionNode = 0; transactionNode < transactionNodes.length(); ++transactionNode)
                {
                    if(transactionNodes.at(transactionNode).toElement().tagName() != "transaction")
                    {
                        //Not a transaction element. Skip this.
                        continue;
                    }

                    transaction = CryptocurrencyTransaction();
                    transaction.setCryptocurrency(currentCryptocurrency);

                    Util::Operation operation = Util::getOperation(transactionNodes.at(transactionNode).toElement().attribute("type"));
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

                            if(transactionChildElement.tagName() == "price") {
                                transaction.setPrice(transactionChildElement.text().toDouble());
                            } else if(transactionChildElement.tagName() == "amount") {
                                transaction.setAmount(transactionChildElement.text().toDouble());
                            } else if(transactionChildElement.tagName() == "date-time") {
                                transaction.setOperationDateTime(QDateTime::fromString(transactionChildElement.text(), Qt::ISODate));
                            } else if(transactionChildElement.tagName() == "goal-price") {
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

        QList<DiscountBondTransaction> PortfolioXML::getDiscountBondTransactionList() const
        {
            QList<DiscountBondTransaction> transactionList;
            QDomDocument domDocument;
            if(!loadDomDocument(domDocument))
            {
                return QList<DiscountBondTransaction>();
            }

            QDomElement discountBondInvestmentElement;
            if(!findChildElementByTagName(domDocument.documentElement(), discountBondInvestmentElement,
                                                Util::getInvestmentTagName(Util::DiscountBondInvestment)))
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
                    if(transactionNodes.at(transactionNode).toElement().tagName() != "transaction")
                    {
                        //Not a transaction element. Skip this.
                        continue;
                    }

                    transaction = DiscountBondTransaction();
                    transaction.setISIN(discountBondNodeList.at(discountBondNode).toElement().tagName());
                    transaction.setTerm(QDate::fromString(discountBondNodeList.at(discountBondNode).toElement().attribute("term"), Qt::ISODate));
                    transaction.setNominalValue(discountBondNodeList.at(discountBondNode).toElement().attribute("nominal-value").toDouble());

                    Util::Operation operation = Util::getOperation(transactionNodes.at(transactionNode).toElement().attribute("type"));
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

                            if(transactionChildElement.tagName() == "sale-price") {
                                transaction.setSalePrice(transactionChildElement.text().toDouble());
                            } else if(transactionChildElement.tagName() == "count") {
                                transaction.setCount(transactionChildElement.text().toUShort());
                            } else if(transactionChildElement.tagName() == "operation-date") {
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
            if(!findChildElementByTagName(domDocument.documentElement(), exchangeInvestmentElement,
                                                Util::getInvestmentTagName(Util::ExchangeInvestment)))
            {
                //Exchange investment element does not exist. File is not valid.
                return QList<ExchangeTransaction>();
            }

            QDomNodeList exchangeNodeList = exchangeInvestmentElement.childNodes();
            for(int exchangeNode = 0; exchangeNode < exchangeNodeList.length(); ++exchangeNode)
            {
                Util::Currency currentCurrency = Util::getCurrency(exchangeNodeList.at(exchangeNode).toElement().tagName());
                if(Util::InvalidCurrency == currentCurrency)
                {
                    //Not yet supported currency. Skip this.
                    continue;
                }

                QDomNodeList transactionNodes = exchangeNodeList.at(exchangeNode).childNodes();
                ExchangeTransaction transaction;
                for(int transactionNode = 0; transactionNode < transactionNodes.length(); ++transactionNode)
                {
                    if(transactionNodes.at(transactionNode).toElement().tagName() != "transaction")
                    {
                        //Not a transaction element. Skip this.
                        continue;
                    }

                    transaction = ExchangeTransaction();
                    transaction.setCurrency(currentCurrency);

                    Util::Operation operation = Util::getOperation(transactionNodes.at(transactionNode).toElement().attribute("type"));
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

                            if(transactionChildElement.tagName() == "price") {
                                transaction.setPrice(transactionChildElement.text().toDouble());
                            } else if(transactionChildElement.tagName() == "amount") {
                                transaction.setAmount(transactionChildElement.text().toDouble());
                            } else if(transactionChildElement.tagName() == "date-time") {
                                transaction.setOperationDateTime(QDateTime::fromString(transactionChildElement.text(), Qt::ISODate));
                            } else if(transactionChildElement.tagName() == "goal-price") {
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
            if(!findChildElementByTagName(domDocument.documentElement(), fundInvestmentElement,
                                                Util::getInvestmentTagName(Util::FundInvestment)))
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
                    if(transactionNodes.at(transactionNode).toElement().tagName() != "transaction")
                    {
                        //Not a transaction element. Skip this.
                        continue;
                    }

                    transaction = FundTransaction();
                    transaction.setFundCode(fundNodeList.at(fundNode).toElement().tagName());
                    transaction.setFundName(fundNodeList.at(fundNode).toElement().attribute("name"));

                    Util::Operation operation = Util::getOperation(transactionNodes.at(transactionNode).toElement().attribute("type"));
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

                            if(transactionChildElement.tagName() == "price") {
                                transaction.setPrice(transactionChildElement.text().toDouble());
                            } else if(transactionChildElement.tagName() == "count") {
                                transaction.setCount(transactionChildElement.text().toDouble());
                            } else if(transactionChildElement.tagName() == "order-date") {
                                transaction.setOrderDate(QDate::fromString(transactionChildElement.text(), Qt::ISODate));
                            } else if(transactionChildElement.tagName() == "operation-date") {
                                transaction.setOperationDate(QDate::fromString(transactionChildElement.text(), Qt::ISODate));
                            } else if(transactionChildElement.tagName() == "goal-price") {
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
            if(!findChildElementByTagName(domDocument.documentElement(), goldInvestmentElement,
                                                Util::getInvestmentTagName(Util::GoldInvestment)))
            {
                //Gold investment element does not exist. File is not valid.
                return QList<GoldTransaction>();
            }

            QDomNodeList goldNodeList = goldInvestmentElement.childNodes();
            for(int goldNode = 0; goldNode < goldNodeList.length(); ++goldNode)
            {
                Util::Gold currentGold = Util::getGold(goldNodeList.at(goldNode).toElement().tagName());
                if(Util::InvalidGold == currentGold)
                {
                    //Not yet supported gold. Skip this.
                    continue;
                }

                QDomNodeList transactionNodes = goldNodeList.at(goldNode).childNodes();
                GoldTransaction transaction;
                for(int transactionNode = 0; transactionNode < transactionNodes.length(); ++transactionNode)
                {
                    if(transactionNodes.at(transactionNode).toElement().tagName() != "transaction")
                    {
                        //Not a transaction element. Skip this.
                        continue;
                    }

                    transaction = GoldTransaction();
                    transaction.setGoldType(currentGold);

                    Util::Operation operation = Util::getOperation(transactionNodes.at(transactionNode).toElement().attribute("type"));
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

                            if(transactionChildElement.tagName() == "price") {
                                transaction.setPrice(transactionChildElement.text().toDouble());
                            } else if(transactionChildElement.tagName() == "amount") {
                                transaction.setAmount(transactionChildElement.text().toDouble());
                            } else if(transactionChildElement.tagName() == "date-time") {
                                transaction.setOperationDateTime(QDateTime::fromString(transactionChildElement.text(), Qt::ISODate));
                            } else if(transactionChildElement.tagName() == "goal-price") {
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
            if(!findChildElementByTagName(domDocument.documentElement(), stockInvestmentElement,
                                                Util::getInvestmentTagName(Util::StockInvestment)))
            {
                //Stock investment element does not exist. File is not valid.
                return QList<StockTransaction>();
            }

            QDomNodeList stockMarketNodeList = stockInvestmentElement.childNodes();
            for(int stockMarketNode = 0; stockMarketNode < stockMarketNodeList.length(); ++stockMarketNode)
            {
                Util::StockMarket currentStockMarket =
                        Util::getStockMarket(stockMarketNodeList.at(stockMarketNode).toElement().tagName());
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
                        if(transactionNodes.at(transactionNode).toElement().tagName() != "transaction")
                        {
                            //Not a transaction element. Skip this.
                            continue;
                        }

                        transaction = StockTransaction();
                        transaction.setStockMarket(currentStockMarket);
                        transaction.setStockSymbol(stockNodeList.at(stockNode).toElement().tagName());
                        transaction.setStockName(stockNodeList.at(stockNode).toElement().attribute("name"));

                        Util::Operation operation = Util::getOperation(transactionNodes.at(transactionNode).toElement().attribute("type"));
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

                                if(transactionChildElement.tagName() == "price") {
                                    transaction.setPrice(transactionChildElement.text().toDouble());
                                } else if(transactionChildElement.tagName() == "count") {
                                    transaction.setCount(transactionChildElement.text().toUShort());
                                } else if(transactionChildElement.tagName() == "commission-rate") {
                                    transaction.setCommissionRate(transactionChildElement.text().toDouble());
                                } else if(transactionChildElement.tagName() == "date-time") {
                                    transaction.setOperationDateTime(QDateTime::fromString(transactionChildElement.text(), Qt::ISODate));
                                } else if(transactionChildElement.tagName() == "goal-price") {
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
            QObject(parent), portfolioFile(new QFile(filePath, this))
        {

        }

        bool PortfolioXML::loadDomDocument(QDomDocument &domDocument) const
        {
            if(!domDocument.setContent(portfolioFile, false))
            {
                portfolioFile->close();
                return false;
            }

            portfolioFile->close();
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
            if(!portfolioFile->open(QIODevice::Text | QIODevice::WriteOnly)){
                return false;
            }
            QTextStream outStream(portfolioFile);
            domDocument.save(outStream, 4);
            portfolioFile->close();
            return true;
        }

    }

}
