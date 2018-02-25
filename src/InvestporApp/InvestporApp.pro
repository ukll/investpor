#-------------------------------------------------
#
# Project created by QtCreator 2018-01-12T18:29:19
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TEMPLATE = app
TARGET = Investpor
VERSION = 0.1.0
INCLUDEPATH += ../InvestporCore/
LIBS += -L../../lib/InvestporCore -lInvestporCore

DESTDIR = ../../bin/InvestporApp
OBJECTS_DIR = $${DESTDIR}/obj
MOC_DIR = $${DESTDIR}/moc
UI_DIR = $${DESTDIR}/ui
RCC_DIR = $${DESTDIR}/rcc

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    main.cpp \
    investpor/gui/mainwindow.cpp \
    investpor/gui/cryptocurrencydialog.cpp \
    investpor/gui/discountbonddialog.cpp \
    investpor/gui/exchangedialog.cpp \
    investpor/gui/funddialog.cpp \
    investpor/gui/golddialog.cpp \
    investpor/gui/stockdialog.cpp \
    investpor/gui/cryptocurrencytablemodel.cpp \
    investpor/gui/tablemodel.cpp \
    investpor/gui/discountbondtablemodel.cpp \
    investpor/gui/exchangetablemodel.cpp \
    investpor/gui/fundtablemodel.cpp \
    investpor/gui/goldtablemodel.cpp \
    investpor/gui/stocktablemodel.cpp \
    investpor/gui/portfoliodialog.cpp

HEADERS += \
    investpor/gui/mainwindow.h \
    investpor/gui/cryptocurrencydialog.h \
    investpor/gui/discountbonddialog.h \
    investpor/gui/exchangedialog.h \
    investpor/gui/funddialog.h \
    investpor/gui/golddialog.h \
    investpor/gui/stockdialog.h \
    investpor/gui/cryptocurrencytablemodel.h \
    investpor/gui/tablemodel.h \
    investpor/gui/discountbondtablemodel.h \
    investpor/gui/exchangetablemodel.h \
    investpor/gui/fundtablemodel.h \
    investpor/gui/goldtablemodel.h \
    investpor/gui/stocktablemodel.h \
    investpor/gui/portfoliodialog.h

FORMS += \
    investpor/gui/mainwindow.ui \
    investpor/gui/cryptocurrencydialog.ui \
    investpor/gui/discountbonddialog.ui \
    investpor/gui/exchangedialog.ui \
    investpor/gui/funddialog.ui \
    investpor/gui/golddialog.ui \
    investpor/gui/stockdialog.ui \
    investpor/gui/portfoliodialog.ui
