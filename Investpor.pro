TEMPLATE = subdirs
CONFIG += ordered

CONFIG(debug, debug|release) {
    DESTDIR = ../build-Investpor-Debug
} else {
    DESTDIR = ../build-Investpor-Release
}

SUBDIRS += \
    src/InvestporCore \
    src/InvestporApp
