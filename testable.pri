INCLUDEPATH += $$PWD

QT += testlib quick qml qmltest

HEADERS += \
    $$PWD/testrunner.h \
    $$PWD/automator.h \
    $$PWD/priv/testrunnerwrapper.h

SOURCES += \
    $$PWD/testrunner.cpp \
    $$PWD/automator.cpp \
    $$PWD/priv/testrunnerwrapper.cpp
