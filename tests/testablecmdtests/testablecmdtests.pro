#-------------------------------------------------
#
# Project created by QtCreator 2016-01-14T07:19:12
#
#-------------------------------------------------

QT       += testlib

TARGET = testablecmdtests
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app


SOURCES += \
    main.cpp \
    dummytests1.cpp \
    dummytests2.cpp

DEFINES += SRCDIR=\\\"$$PWD/\\\"

include (../../testable.pri)

HEADERS += \
    dummytests1.h \
    dummytests2.h

DISTFILES += \
    README.md \
    SampleWindow.qml \
    ../../README.md \
    tst_quicktests.qml \
    tst_Testable.qml \
    ItemWithError.qml \
    run-tests.sh

QMAKE_POST_LINK += $$PWD/run-tests.sh
