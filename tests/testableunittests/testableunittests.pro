QT += core
QT -= gui

CONFIG += c++11

TARGET = testableunittests
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

SOURCES += main.cpp \
    testableunittests.cpp

HEADERS += \
    testableunittests.h

include(../../testable.pri)
