#-------------------------------------------------
#
# Project created by QtCreator 2018-01-12T18:29:19
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 5): QT += widgets

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
DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += \
    main.cpp \
    investpor/gui/mainwindow.cpp \
    investpor/gui/stockdialog.cpp \
    investpor/gui/bonddialog.cpp \
    investpor/gui/cryptocurrencydialog.cpp \
    investpor/gui/exchangedialog.cpp \
    investpor/gui/funddialog.cpp \
    investpor/gui/golddialog.cpp \
    investpor/core/util.cpp \
    investpor/core/transaction.cpp \
    investpor/core/discountbondtransaction.cpp \
    investpor/core/cryptocurrencytransaction.cpp \
    investpor/core/exchangetransaction.cpp

HEADERS += \
    investpor/gui/mainwindow.h \
    investpor/gui/stockdialog.h \
    investpor/gui/bonddialog.h \
    investpor/gui/cryptocurrencydialog.h \
    investpor/gui/exchangedialog.h \
    investpor/gui/funddialog.h \
    investpor/gui/golddialog.h \
    investpor/core/types.h \
    investpor/core/util.h \
    investpor/core/transaction.h \
    investpor/core/discountbondtransaction.h \
    investpor/core/cryptocurrencytransaction.h \
    investpor/core/exchangetransaction.h

FORMS += \
    investpor/gui/mainwindow.ui \
    investpor/gui/stockdialog.ui \
    investpor/gui/bonddialog.ui \
    investpor/gui/cryptocurrencydialog.ui \
    investpor/gui/exchangedialog.ui \
    investpor/gui/funddialog.ui \
    investpor/gui/golddialog.ui
