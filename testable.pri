INCLUDEPATH += $$PWD
QML_IMPORT_PATH += $$PWD

QT += testlib quick qml qmltest xml

HEADERS += \
    $$PWD/testrunner.h \
    $$PWD/automator.h \
    $$PWD/priv/testrunnerwrapper.h \
    $$PWD/Automator \
    $$PWD/TestRunner \
    $$PWD/priv/testableutils.h \
    $$PWD/priv/objectutils.h \
    $$PWD/testablefunctions.h

SOURCES += \
    $$PWD/testrunner.cpp \
    $$PWD/automator.cpp \
    $$PWD/priv/testrunnerwrapper.cpp \
    $$PWD/priv/testableutils.cpp \
    $$PWD/priv/objectutils.cpp \
    $$PWD/testablefunctions.cpp

DISTFILES += \
    $$PWD/Testable/TestableCase.qml \
    $$PWD/Testable/qmldir

RESOURCES += \
    $$PWD/testable.qrc

