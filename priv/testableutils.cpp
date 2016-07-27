#include <QEventLoop>
#include <QTimer>
#include <QtQml>
#include "testableutils.h"

TestableUtils::TestableUtils(QObject *parent) : QObject(parent)
{

}

void TestableUtils::wait(int timeout)
{
    QEventLoop loop;
    QTimer timer;
    QObject::connect(&timer,SIGNAL(timeout()),
            &loop,SLOT(quit()));
    timer.start(timeout);
    loop.exec();
}


static QObject *provider(QQmlEngine *engine, QJSEngine *scriptEngine) {
    Q_UNUSED(engine);
    Q_UNUSED(scriptEngine);

    TestableUtils* object = new TestableUtils();

    return object;
}

void registerTestableUtils() {
    qmlRegisterSingletonType<TestableUtils>("Testable", 1, 0, "TestableUtils", provider);
}

Q_COREAPP_STARTUP_FUNCTION(registerTestableUtils)

