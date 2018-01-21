#-------------------------------------------------
#
# Project created by QtCreator 2018-01-12T18:29:19
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Investpor
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += \
    main.cpp \
    investpor/gui/SourceFiles/mainwindow.cpp \
    investpor/gui/SourceFiles/stockdialog.cpp \
    investpor/gui/SourceFiles/bonddialog.cpp \
    investpor/gui/SourceFiles/cryptocurrencydialog.cpp \
    investpor/gui/SourceFiles/exchangedialog.cpp \
    investpor/gui/SourceFiles/funddialog.cpp \
    investpor/gui/SourceFiles/golddialog.cpp \
    investpor/core/SourceFiles/util.cpp \
    investpor/core/SourceFiles/transaction.cpp \
    investpor/core/SourceFiles/discountbondtransaction.cpp \
    investpor/core/SourceFiles/cryptocurrencytransaction.cpp \
    investpor/core/SourceFiles/exchangetransaction.cpp

HEADERS += \
    investpor/gui/HeaderFiles/mainwindow.h \
    investpor/gui/HeaderFiles/stockdialog.h \
    investpor/gui/HeaderFiles/bonddialog.h \
    investpor/gui/HeaderFiles/cryptocurrencydialog.h \
    investpor/gui/HeaderFiles/exchangedialog.h \
    investpor/gui/HeaderFiles/funddialog.h \
    investpor/gui/HeaderFiles/golddialog.h \
    investpor/core/HeaderFiles/types.h \
    investpor/core/HeaderFiles/util.h \
    investpor/core/HeaderFiles/transaction.h \
    investpor/core/HeaderFiles/discountbondtransaction.h \
    investpor/core/HeaderFiles/cryptocurrencytransaction.h \
    investpor/core/HeaderFiles/exchangetransaction.h

FORMS += \
    investpor/gui/UIFiles/mainwindow.ui \
    investpor/gui/UIFiles/stockdialog.ui \
    investpor/gui/UIFiles/bonddialog.ui \
    investpor/gui/UIFiles/cryptocurrencydialog.ui \
    investpor/gui/UIFiles/exchangedialog.ui \
    investpor/gui/UIFiles/funddialog.ui \
    investpor/gui/UIFiles/golddialog.ui
