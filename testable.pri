INCLUDEPATH += $$PWD

QT += testlib quick qml qmltest xml

HEADERS += \
    $$PWD/testrunner.h \
    $$PWD/automator.h \
    $$PWD/priv/testrunnerwrapper.h \
    $$PWD/resourcegenerator.h \
    $$PWD/Automator \
    $$PWD/TestRunner \
    $$PWD/ResourceGenerator \
    $$PWD/priv/testableutils.h

SOURCES += \
    $$PWD/testrunner.cpp \
    $$PWD/automator.cpp \
    $$PWD/priv/testrunnerwrapper.cpp \
    $$PWD/resourcegenerator.cpp \
    $$PWD/priv/testableutils.cpp

DISTFILES += \
    $$PWD/Testable/TestableCase.qml \
    $$PWD/Testable/qmldir

RESOURCES += \
    $$PWD/testable.qrc

