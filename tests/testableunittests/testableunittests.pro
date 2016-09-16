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

DEFINES += SRCDIR=\\\"$$PWD/\\\"


include(../../testable.pri)

DISTFILES += \
    window.qml \
    PackageA/example.js \
    PackageA/qmldir \
    PackageA/Store.qml \
    TestableCaseTests.qml \
    TestableCaseFailTests.qml \
    AutomatorCreateTracker.qml \
    Dummy.qml
