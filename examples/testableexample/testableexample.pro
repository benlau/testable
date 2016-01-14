#-------------------------------------------------
#
# Project created by QtCreator 2016-01-14T07:19:12
#
#-------------------------------------------------

QT       += testlib

QT       -= gui

TARGET = testable
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app


SOURCES += \
    main.cpp \
    dummytests1.cpp \
    dummytests2.cpp \
    qmltests.cpp
DEFINES += SRCDIR=\\\"$$PWD/\\\"

include (../../testable.pri)

HEADERS += \
    dummytests1.h \
    dummytests2.h \
    qmltests.h

DISTFILES += \
    README.md \
    SampleWindow.qml
