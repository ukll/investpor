#-------------------------------------------------
#
# Project created by QtCreator 2018-01-12T18:29:19
#
#-------------------------------------------------

QT       += core gui xml

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TEMPLATE = app
TARGET = InvestporDesktop
VERSION = 0.1.0

INCLUDEPATH += src/com/investpor/
INCLUDEPATH += ../InvestporLib/src/com/investpor/

CONFIG(debug, debug|release) {
    LIBS += -L../../lib/Debug/InvestporLib -lInvestporLib
    DESTDIR = ../../bin/Debug/InvestporDesktop/
} else {
    LIBS += -L../../lib/Release/InvestporLib -lInvestporLib
    DESTDIR = ../../bin/Release/InvestporDesktop/
}

OBJECTS_DIR = $${DESTDIR}/obj/
MOC_DIR = $${DESTDIR}/moc/
UI_DIR = $${DESTDIR}/ui/
RCC_DIR = $${DESTDIR}/rcc/

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
    src/main.cpp \
    src/com/investpor/desktop/mainwindow.cpp \
    src/com/investpor/desktop/cryptocurrencydialog.cpp \
    src/com/investpor/desktop/discountbonddialog.cpp \
    src/com/investpor/desktop/exchangedialog.cpp \
    src/com/investpor/desktop/funddialog.cpp \
    src/com/investpor/desktop/golddialog.cpp \
    src/com/investpor/desktop/stockdialog.cpp \
    src/com/investpor/desktop/cryptocurrencytablemodel.cpp \
    src/com/investpor/desktop/tablemodel.cpp \
    src/com/investpor/desktop/discountbondtablemodel.cpp \
    src/com/investpor/desktop/exchangetablemodel.cpp \
    src/com/investpor/desktop/fundtablemodel.cpp \
    src/com/investpor/desktop/goldtablemodel.cpp \
    src/com/investpor/desktop/stocktablemodel.cpp \
    src/com/investpor/desktop/portfoliodialog.cpp

HEADERS += \
    src/com/investpor/desktop/mainwindow.h \
    src/com/investpor/desktop/cryptocurrencydialog.h \
    src/com/investpor/desktop/discountbonddialog.h \
    src/com/investpor/desktop/exchangedialog.h \
    src/com/investpor/desktop/funddialog.h \
    src/com/investpor/desktop/golddialog.h \
    src/com/investpor/desktop/stockdialog.h \
    src/com/investpor/desktop/cryptocurrencytablemodel.h \
    src/com/investpor/desktop/tablemodel.h \
    src/com/investpor/desktop/discountbondtablemodel.h \
    src/com/investpor/desktop/exchangetablemodel.h \
    src/com/investpor/desktop/fundtablemodel.h \
    src/com/investpor/desktop/goldtablemodel.h \
    src/com/investpor/desktop/stocktablemodel.h \
    src/com/investpor/desktop/portfoliodialog.h

FORMS += \
    src/com/investpor/desktop/mainwindow.ui \
    src/com/investpor/desktop/cryptocurrencydialog.ui \
    src/com/investpor/desktop/discountbonddialog.ui \
    src/com/investpor/desktop/exchangedialog.ui \
    src/com/investpor/desktop/funddialog.ui \
    src/com/investpor/desktop/golddialog.ui \
    src/com/investpor/desktop/stockdialog.ui \
    src/com/investpor/desktop/portfoliodialog.ui

TRANSLATIONS += \
    resources/translations/$${TARGET}_en.ts \
    resources/translations/$${TARGET}_tr.ts

RESOURCES += \
    resources/InvestporDesktop.qrc

unix {
    target.path = /opt/Investpor/bin
    documentation.path = /opt/Investpor/docs/$${TARGET}
    documentation.files = docs/*
    INSTALLS += target documentation
}
