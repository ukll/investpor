QT += testlib core gui

TEMPLATE = app
CONFIG += qt warn_on depend_includepath testcase
TARGET = TestInvestporLib
VERSION = 0.1.0

INCLUDEPATH += src/com/investpor/
INCLUDEPATH += ../../src/InvestporLib/src/com/investpor/
LIBS += -L../../lib/Debug/InvestporLib -lInvestporLib

DESTDIR = ../../lib/Debug/$${TARGET}/
OBJECTS_DIR = $${DESTDIR}/obj/
MOC_DIR = $${DESTDIR}/moc/
UI_DIR = $${DESTDIR}/ui/
RCC_DIR = $${DESTDIR}/rcc/

SOURCES +=  \
    src/com/investpor/libtest/testutil.cpp \
    src/com/investpor/libtest/testportfolioxml.cpp \
    src/com/investpor/libtest/testcryptocurrencytreemodel.cpp \
    src/main.cpp

HEADERS += \
    src/com/investpor/libtest/testutil.h \
    src/com/investpor/libtest/testportfolioxml.h \
    src/com/investpor/libtest/testcryptocurrencytreemodel.h
