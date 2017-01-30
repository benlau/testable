#include <QApplication>
#include <QtCore>
#include <QTest>
#include <TestRunner>
#include "testableunittests.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    /* This function do nothing. But that could let Qt Creator
     * detect available test cases
     */
    auto enableAutoTest = []{
        QTest::qExec((TestableUnitTests*)(0), 0,0);
    };
    Q_UNUSED(enableAutoTest);

    TestRunner runner;
    runner.add<TestableUnitTests>();
    bool error = runner.exec(a.arguments());

    if (!error) {
        qWarning() << "All test cases passed!";
    }

    return error;
}
