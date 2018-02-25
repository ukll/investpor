#-------------------------------------------------
#
# Project created by QtCreator 2018-02-26T00:36:46
#
#-------------------------------------------------

QT       += core xml
QT       -= gui

TEMPLATE = lib
CONFIG += staticlib
TARGET = InvestporCore
VERSION = 0.1.0

DESTDIR = ../../lib/InvestporCore
OBJECTS_DIR = $${DESTDIR}/obj
MOC_DIR = $${DESTDIR}/moc
UI_DIR = $${DESTDIR}/ui
RCC_DIR = $${DESTDIR}/rcc

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    investpor/core/util.cpp \
    investpor/core/transaction.cpp \
    investpor/core/cryptocurrencytransaction.cpp \
    investpor/core/discountbondtransaction.cpp \
    investpor/core/exchangetransaction.cpp \
    investpor/core/fundtransaction.cpp \
    investpor/core/goldtransaction.cpp \
    investpor/core/stocktransaction.cpp \
    investpor/core/portfolioxml.cpp

HEADERS += \
    investpor/core/util.h \
    investpor/core/transaction.h \
    investpor/core/cryptocurrencytransaction.h \
    investpor/core/discountbondtransaction.h \
    investpor/core/exchangetransaction.h \
    investpor/core/fundtransaction.h \
    investpor/core/goldtransaction.h \
    investpor/core/stocktransaction.h \
    investpor/core/portfolioxml.h

unix {
    documentation.path = /opt/InvestporCore/docs
    documentation.files = docs/*
    target.path = /opt/InvestporCore
    INSTALLS += target documentation
}
