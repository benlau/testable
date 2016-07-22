#-------------------------------------------------
#
# Project created by QtCreator 2016-02-25T18:56:34
#
#-------------------------------------------------

QT       += testlib qml

TARGET = unittests
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app

SOURCES += \
    main.cpp \
    tests.cpp

DEFINES += SRCDIR=\\\"$$PWD/\\\"

include(vendor/vendor.pri)

DISTFILES += \
    qpm.json \
    qmltests/tst_QmlTests.qml

HEADERS += \
    tests.h

