INCLUDEPATH += $$PWD

QT += testlib quick qml qmltest xml

HEADERS += \
    $$PWD/testrunner.h \
    $$PWD/automator.h \
    $$PWD/priv/testrunnerwrapper.h \
    $$PWD/resourcegenerator.h

SOURCES += \
    $$PWD/testrunner.cpp \
    $$PWD/automator.cpp \
    $$PWD/priv/testrunnerwrapper.cpp \
    $$PWD/resourcegenerator.cpp
