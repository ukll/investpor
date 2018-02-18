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
         * @brief Constructor to create a portfolio object when opening an existing portfolio file.
         * @param filePath : Filepath of portfolio file.
         * @param parent : Parent to own portfolio.
         */
        PortfolioXML::PortfolioXML(const QString &filePath, QObject *parent) :
            QObject(parent), portfolioFile(new QFile(filePath, this))
        {
            QDomDocument domDocument;

            if(portfolioFile->exists()) {
                //Check if portfolio file is valid.
                if(loadDomDocument(domDocument))
                {
                    state = PortfolioState::Valid;

                    QDomElement portfolioElement = domDocument.documentElement();
                    portfolioName = portfolioElement.attribute("name");
                    baseCurrency = Util::getCurrency(portfolioElement.attribute("currency"));

                    return;
                }

                state = PortfolioState::FileContentIsNotValid;
                return;
            }
        }

        PortfolioXML::PortfolioXML(const QString &filePath, const QString &pName, const Util::Currency &bCurrency, QObject *parent) :
            QObject(parent), portfolioFile(new QFile(filePath, this)), portfolioName(pName), baseCurrency(bCurrency)
        {
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
            outStream.writeStartElement("portfolio");
            outStream.writeAttribute("name", pName);
            outStream.writeAttribute("currency", Util::currencySymbol(bCurrency).toLower());

            outStream.writeStartElement(Util::getInvestmentTagName(Util::Investment::CryptoCurrencyInvestment));
            outStream.writeEndElement();

            outStream.writeStartElement(Util::getInvestmentTagName(Util::Investment::DiscountBondInvestment));
            outStream.writeEndElement();

            outStream.writeStartElement(Util::getInvestmentTagName(Util::Investment::ExchangeInvestment));
            outStream.writeEndElement();

            outStream.writeStartElement(Util::getInvestmentTagName(Util::Investment::FundInvestment));
            outStream.writeEndElement();

            outStream.writeStartElement(Util::getInvestmentTagName(Util::Investment::GoldInvestment));
            outStream.writeEndElement();

            outStream.writeStartElement(Util::getInvestmentTagName(Util::Investment::StockInvestment));
            outStream.writeEndElement();

            //Close XML document
            outStream.writeEndDocument();

            portfolioFile->close();

            state = PortfolioState::Valid;
        }

        PortfolioXML::~PortfolioXML()
        {

        }

        bool PortfolioXML::setPortfolioName(const QString &pName)
        {
            QDomDocument domDocument;
            //Load the DOM document
            if(!loadDomDocument(domDocument))
            {
                return false;
            }

            QDomElement portfolioElement = domDocument.documentElement();
            portfolioElement.setAttribute("name", pName);

            //Save the transaction
            if(!savePortfolio(domDocument))
            {
                state = FileCouldNotBeSaved;
                return false;
            }

            portfolioName = pName;
            return true;
        }

        bool PortfolioXML::setBaseCurrency(const Util::Currency &bCurrency)
        {
            QDomDocument domDocument;
            //Load the DOM document
            if(!loadDomDocument(domDocument))
            {
                return false;
            }

            QDomElement portfolioElement = domDocument.documentElement();
            portfolioElement.setAttribute("currency", Util::currencySymbol(bCurrency));

            //Save the transaction
            if(!savePortfolio(domDocument))
            {
                state = FileCouldNotBeSaved;
                return false;
            }

            baseCurrency = bCurrency;
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

            if(!findDomElementByTagName(domDocument, cryptoCurrencyInvestmentElement,
                                        Util::getInvestmentTagName(Util::Investment::CryptoCurrencyInvestment)))
            {
                //Cryptocurrency investment element does not exist. File is not valid.
                return false;
            }

            QDomElement cryptoCurrencyElement;
            QDomElement transactionElement = domDocument.createElement("transaction");
            if(!findDirectChildElementByTagName(cryptoCurrencyInvestmentElement, cryptoCurrencyElement,
                                                Util::cryptoCurrencySymbol(transaction.getCryptocurrency()).toLower()))
            {
                //Cryptocurrency element does not exist. Create a new one.
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

            if(transaction.getOperationType() == Util::Operation::BUY)
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
            if(!findDomElementByTagName(domDocument, discountBondInvestmentElement,
                                        Util::getInvestmentTagName(Util::Investment::DiscountBondInvestment)))
            {
                //Discount bond investment element does not exist. File is not valid.
                return false;
            }

            QDomElement discountBondElement;
            QDomElement transactionElement = domDocument.createElement("transaction");
            if(!findDirectChildElementByTagName(discountBondInvestmentElement, discountBondElement,
                                                transaction.getISIN().toLower()))
            {
                //Discount bond element does not exist. Create a new one.
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

            QDomElement countElement = domDocument.createElement("count");
            QDomText countText = domDocument.createTextNode(QString::number(transaction.getCount()));
            countElement.appendChild(countText);
            transactionElement.appendChild(countElement);

            QDomElement operationDateElement = domDocument.createElement("operation-date");
            QDomText operationDateText = domDocument.createTextNode(transaction.getOperationDate().toString("yyyy-MM-dd"));
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
            if(!findDomElementByTagName(domDocument, exchangeInvestmentElement,
                                        Util::getInvestmentTagName(Util::Investment::ExchangeInvestment)))
            {
                //Exchange investment element does not exist. File is not valid.
                return false;
            }

            QDomElement exchangeElement;
            QDomElement transactionElement = domDocument.createElement("transaction");
            if(!findDirectChildElementByTagName(exchangeInvestmentElement, exchangeElement,
                                                Util::currencySymbol(transaction.getCurrency()).toLower()))
            {
                //Exchange element does not exist. Create a new one.
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

            if(transaction.getOperationType() == Util::Operation::BUY)
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
            if(!findDomElementByTagName(domDocument, fundInvestmentElement,
                                        Util::getInvestmentTagName(Util::Investment::FundInvestment)))
            {
                //Fund investment element does not exist. File is not valid.
                return false;
            }

            QDomElement fundElement;
            QDomElement transactionElement = domDocument.createElement("transaction");
            if(!findDirectChildElementByTagName(fundInvestmentElement, fundElement, transaction.getFundCode().toLower()))
            {
                //Fund element does not exist. Create a new one.
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

            QDomElement operationDateElement = domDocument.createElement("operation-date");
            QDomText operationDateText = domDocument.createTextNode(transaction.getOperationDate().toString("yyyy-MM-dd"));
            operationDateElement.appendChild(operationDateText);
            transactionElement.appendChild(operationDateElement);

            if(transaction.getOperationType() == Util::Operation::BUY)
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
            QDomElement transactionElement = domDocument.createElement("transaction");

            //Load the DOM document
            if(!loadDomDocument(domDocument))
            {
                return false;
            }

            if(!findDomElementByTagName(domDocument, goldInvestmentElement,
                                        Util::getInvestmentTagName(Util::Investment::GoldInvestment)))
            {
                //Gold investment element does not exist. File is not valid.
                return false;
            }

            if(!findDirectChildElementByTagName(goldInvestmentElement, goldElement,
                                                Util::goldSymbol(transaction.getGoldType()).toLower()))
            {
                //Gold element does not exist. Create a new one.
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

            if(transaction.getOperationType() == Util::Operation::BUY)
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
            if(!findDomElementByTagName(domDocument, stockInvestmentElement,
                                        Util::getInvestmentTagName(Util::Investment::StockInvestment)))
            {
                //Stock investment element does not exist. File is not valid.
                return false;
            }

            QDomElement stockMarketElement;
            QDomElement stockElement;
            QDomElement transactionElement = domDocument.createElement("transaction");
            if(!findDirectChildElementByTagName(stockInvestmentElement, stockMarketElement,
                                                Util::stockMarketSymbol(transaction.getStockMarket()).toLower()))
            {
                //Stock market element does not exist. Create a new one.
                stockMarketElement = domDocument.createElement(Util::stockMarketSymbol(transaction.getStockMarket()).toLower());
                stockInvestmentElement.appendChild(stockMarketElement);
            }

            //Check if stock element exists.
            if(!findDirectChildElementByTagName(stockMarketElement, stockElement, transaction.getStockSymbol().toLower()))
            {
                //Stock element does not exist. Create a new one.
                stockElement = domDocument.createElement(transaction.getStockSymbol().toLower());
                stockMarketElement.appendChild(stockElement);
                stockElement.setAttribute("name", transaction.getStockName().toLower());
                transactionElement.setAttribute("id", 1);
            } else {
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

            if(transaction.getOperationType() == Util::Operation::BUY)
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
            if(!findDomElementByTagName(domDocument, cryptoCurrencyInvestmentElement,
                                        Util::getInvestmentTagName(Util::Investment::CryptoCurrencyInvestment)))
            {
                //Cryptocurrency investment element does not exist. File is not valid.
                return QList<CryptocurrencyTransaction>();
            }

            QDomNodeList cryptoCurrencyNodeList = cryptoCurrencyInvestmentElement.childNodes();
            for(int cryptoCurrencyNode = 0; cryptoCurrencyNode < cryptoCurrencyNodeList.length(); ++cryptoCurrencyNode)
            {
                Util::Cryptocurrency currentCryptocurrency = Util::getCryptocurrency(
                            cryptoCurrencyNodeList.at(cryptoCurrencyNode).toElement().tagName());
                if(currentCryptocurrency == Util::Cryptocurrency::InvalidCryptocurrency)
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
                    transaction.setTransactionId(transactionNodes.at(transactionNode).toElement().attribute("id").toUShort());
                    transaction.setCryptocurrency(currentCryptocurrency);

                    Util::Operation operation = Util::getOperation(transactionNodes.at(transactionNode).toElement().attribute("type"));
                    if(operation == Util::Operation::InvalidOperation)
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
                                transaction.setOperationDateTime(QDateTime::fromString(transactionChildElement.text(), "yyyy-MM-dd hh:mm:ss"));
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
            if(!findDomElementByTagName(domDocument, discountBondInvestmentElement,
                                        Util::getInvestmentTagName(Util::Investment::DiscountBondInvestment)))
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
                    transaction.setTransactionId(transactionNodes.at(transactionNode).toElement().attribute("id").toUShort());
                    transaction.setISIN(discountBondNodeList.at(discountBondNode).toElement().tagName());
                    transaction.setTerm(QDate::fromString(discountBondNodeList.at(discountBondNode).toElement().attribute("term"), "yyyy-MM-dd"));
                    transaction.setNominalValue(discountBondNodeList.at(discountBondNode).toElement().attribute("nominal-value").toDouble());

                    Util::Operation operation = Util::getOperation(transactionNodes.at(transactionNode).toElement().attribute("type"));
                    if(operation == Util::Operation::InvalidOperation)
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
                                transaction.setOperationDate(QDate::fromString(transactionChildElement.text(), "yyyy-MM-dd"));
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
            if(!findDomElementByTagName(domDocument, exchangeInvestmentElement,
                                        Util::getInvestmentTagName(Util::Investment::ExchangeInvestment)))
            {
                //Exchange investment element does not exist. File is not valid.
                return QList<ExchangeTransaction>();
            }

            QDomNodeList exchangeNodeList = exchangeInvestmentElement.childNodes();
            for(int exchangeNode = 0; exchangeNode < exchangeNodeList.length(); ++exchangeNode)
            {
                Util::Currency currentCurrency = Util::getCurrency(exchangeNodeList.at(exchangeNode).toElement().tagName());
                if(Util::Currency::InvalidCurrency == currentCurrency)
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
                    transaction.setTransactionId(transactionNodes.at(transactionNode).toElement().attribute("id").toUShort());
                    transaction.setCurrency(currentCurrency);

                    Util::Operation operation = Util::getOperation(transactionNodes.at(transactionNode).toElement().attribute("type"));
                    if(operation == Util::Operation::InvalidOperation)
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
                                transaction.setOperationDateTime(QDateTime::fromString(transactionChildElement.text(), "yyyy-MM-dd hh:mm:ss"));
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
            if(!findDomElementByTagName(domDocument, fundInvestmentElement,
                                        Util::getInvestmentTagName(Util::Investment::FundInvestment)))
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
                    transaction.setTransactionId(transactionNodes.at(transactionNode).toElement().attribute("id").toUShort());
                    transaction.setFundCode(fundNodeList.at(fundNode).toElement().tagName());
                    transaction.setFundName(fundNodeList.at(fundNode).toElement().attribute("name"));

                    Util::Operation operation = Util::getOperation(transactionNodes.at(transactionNode).toElement().attribute("type"));
                    if(operation == Util::Operation::InvalidOperation)
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
                                transaction.setOrderDate(QDate::fromString(transactionChildElement.text(), "yyyy-MM-dd"));
                            } else if(transactionChildElement.tagName() == "operation-date") {
                                transaction.setOperationDate(QDate::fromString(transactionChildElement.text(), "yyyy-MM-dd"));
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
            if(!findDomElementByTagName(domDocument, goldInvestmentElement,
                                        Util::getInvestmentTagName(Util::Investment::GoldInvestment)))
            {
                //Gold investment element does not exist. File is not valid.
                return QList<GoldTransaction>();
            }

            QDomNodeList goldNodeList = goldInvestmentElement.childNodes();
            for(int goldNode = 0; goldNode < goldNodeList.length(); ++goldNode)
            {
                Util::Gold currentGold = Util::getGold(goldNodeList.at(goldNode).toElement().tagName());
                if(Util::Gold::InvalidGold == currentGold)
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
                    transaction.setTransactionId(transactionNodes.at(transactionNode).toElement().attribute("id").toUShort());
                    transaction.setGoldType(currentGold);

                    Util::Operation operation = Util::getOperation(transactionNodes.at(transactionNode).toElement().attribute("type"));
                    if(operation == Util::Operation::InvalidOperation)
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
                                transaction.setOperationDateTime(QDateTime::fromString(transactionChildElement.text(), "yyyy-MM-dd hh:mm:ss"));
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
            if(!findDomElementByTagName(domDocument, stockInvestmentElement,
                                        Util::getInvestmentTagName(Util::Investment::StockInvestment)))
            {
                //Stock investment element does not exist. File is not valid.
                return QList<StockTransaction>();
            }

            QDomNodeList stockMarketNodeList = stockInvestmentElement.childNodes();
            for(int stockMarketNode = 0; stockMarketNode < stockMarketNodeList.length(); ++stockMarketNode)
            {
                Util::StockMarket currentStockMarket =
                        Util::getStockMarket(stockMarketNodeList.at(stockMarketNode).toElement().tagName());
                if(Util::StockMarket::InvalidStockMarket == currentStockMarket)
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
                        transaction.setTransactionId(transactionNodes.at(transactionNode).toElement().attribute("id").toUShort());
                        transaction.setStockMarket(currentStockMarket);
                        transaction.setStockSymbol(stockNodeList.at(stockNode).toElement().tagName());
                        transaction.setStockName(stockNodeList.at(stockNode).toElement().attribute("name"));

                        Util::Operation operation = Util::getOperation(transactionNodes.at(transactionNode).toElement().attribute("type"));
                        if(operation == Util::Operation::InvalidOperation)
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
                                    transaction.setOperationDateTime(QDateTime::fromString(transactionChildElement.text(), "yyyy-MM-dd hh:mm:ss"));
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

        bool PortfolioXML::findDomElementByTagName(const QDomDocument &domDocument, QDomElement &domElement, const QString &tagName) const
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

        bool PortfolioXML::findDirectChildElementByTagName(const QDomElement &parent, QDomElement &child, const QString &tagName) const
        {
            QDomNodeList childNodes = parent.elementsByTagName(tagName);
            if(childNodes.length() == 1)
            {
                child = childNodes.at(0).toElement();
                return true;
            }

            return false;
        }

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
