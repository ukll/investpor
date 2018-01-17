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
        SourceFiles/main.cpp \
        SourceFiles/mainwindow.cpp \
    SourceFiles/stockdialog.cpp \
    SourceFiles/bonddialog.cpp \
    SourceFiles/cryptocurrencydialog.cpp \
    SourceFiles/exchangedialog.cpp \
    SourceFiles/funddialog.cpp \
    SourceFiles/golddialog.cpp \
    SourceFiles/util.cpp

HEADERS += \
        HeaderFiles/mainwindow.h \
    HeaderFiles/stockdialog.h \
    HeaderFiles/bonddialog.h \
    HeaderFiles/cryptocurrencydialog.h \
    HeaderFiles/exchangedialog.h \
    HeaderFiles/funddialog.h \
    HeaderFiles/golddialog.h \
    HeaderFiles/types.h \
    HeaderFiles/util.h

FORMS += \
        UIFiles/mainwindow.ui \
    UIFiles/stockdialog.ui \
    UIFiles/bonddialog.ui \
    UIFiles/cryptocurrencydialog.ui \
    UIFiles/exchangedialog.ui \
    UIFiles/funddialog.ui \
    UIFiles/golddialog.ui
