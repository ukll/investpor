#-------------------------------------------------
#
# Project created by QtCreator 2018-02-26T00:36:46
#
#-------------------------------------------------

QT       += core gui xml

TEMPLATE = lib
CONFIG += staticlib
TARGET = InvestporLib
VERSION = 0.1.0

INCLUDEPATH += src/com/investpor/

CONFIG(debug, debug|release) {
    DESTDIR = ../../lib/Debug/$${TARGET}/
} else {
    DESTDIR = ../../lib/Release/$${TARGET}/
}

OBJECTS_DIR = $${DESTDIR}/obj/
MOC_DIR = $${DESTDIR}/moc/
UI_DIR = $${DESTDIR}/ui/
RCC_DIR = $${DESTDIR}/rcc/

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
    src/com/investpor/lib/util.cpp \
    src/com/investpor/lib/transaction.cpp \
    src/com/investpor/lib/cryptocurrencytransaction.cpp \
    src/com/investpor/lib/discountbondtransaction.cpp \
    src/com/investpor/lib/exchangetransaction.cpp \
    src/com/investpor/lib/fundtransaction.cpp \
    src/com/investpor/lib/goldtransaction.cpp \
    src/com/investpor/lib/stocktransaction.cpp \
    src/com/investpor/lib/portfolioxml.cpp \
    src/com/investpor/lib/abstracttreemodel.cpp \
    src/com/investpor/lib/cryptocurrencytreemodel.cpp \
    src/com/investpor/lib/abstracttreeitem.cpp \
    src/com/investpor/lib/cryptocurrencytreeitem.cpp \
    src/com/investpor/lib/abstractportfolio.cpp

HEADERS += \
    src/com/investpor/lib/util.h \
    src/com/investpor/lib/transaction.h \
    src/com/investpor/lib/cryptocurrencytransaction.h \
    src/com/investpor/lib/discountbondtransaction.h \
    src/com/investpor/lib/exchangetransaction.h \
    src/com/investpor/lib/fundtransaction.h \
    src/com/investpor/lib/goldtransaction.h \
    src/com/investpor/lib/stocktransaction.h \
    src/com/investpor/lib/portfolioxml.h \
    src/com/investpor/lib/abstracttreemodel.h \
    src/com/investpor/lib/cryptocurrencytreemodel.h \
    src/com/investpor/lib/abstracttreeitem.h \
    src/com/investpor/lib/cryptocurrencytreeitem.h \
    src/com/investpor/lib/abstractportfolio.h

TRANSLATIONS += \
    resources/translations/$${TARGET}_en.ts \
    resources/translations/$${TARGET}_tr.ts

RESOURCES += \
    resources/InvestporLib.qrc

unix {
    target.path = /opt/Investpor/lib
    documentation.path = /opt/Investpor/docs/$${TARGET}
    documentation.files = docs/*
    INSTALLS += target documentation
}
