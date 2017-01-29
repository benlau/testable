#include <QApplication>
#include <QtCore>
#include <QTest>
#include <TestRunner>
#include "testableunittests.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    TestRunner runner;
    runner.add<TestableUnitTests>();
    bool error = runner.exec(a.arguments());

    if (!error) {
        qWarning() << "All test cases passed!";
    }

    return error;
}
