#include <QtCore>
#include <QGuiApplication>
#include <QQmlEngine>
#include "testrunner.h"
#include "dummytests1.h"
#include "dummytests2.h"
#include <QtQuickTest>

void callback(QQmlEngine* engine) {
    Q_UNUSED(engine);
    // You may register image provider here for QtTest
}

namespace AutoTest {
    QUICK_TEST_MAIN(QuickTests)
}

int main(int argc, char *argv[])
{
    QGuiApplication app(argc,argv);

    TestRunner runner;

    runner.add<DummyTests1>();
    runner.add<DummyTests2>();

    // Run Qt Quick Test in SRCDIR. It will scan all qml file begin with tst_
    runner.add(QString(SRCDIR));

    runner.addImportPath("qrc:///");
    runner.setEngineHook(callback);

    bool error = runner.exec(app.arguments());

    if (!error) {
        qWarning() << "All test cases passed!";
    }

    return error;
}
