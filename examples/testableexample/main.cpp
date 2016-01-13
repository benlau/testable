#include <QtCore>
#include <QCoreApplication>
#include "testrunner.h"
#include "dummytests1.h"
#include "dummytests2.h"

int main(int argc, char *argv[])
{
    QCoreApplication app(argc,argv);

    TestRunner runner;

    runner.add<DummyTests1>();
    runner.add<DummyTests2>();

    bool error = runner.exec(app.arguments());

    if (!error) {
        qWarning() << "All test cases passed!";
    }

    return error;
}
