#include <QEventLoop>
#include <QTimer>
#include <QtQml>
#include <QTest>
#include "testableutils.h"
#include "objectutils.h"

using namespace Testable;

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

QObject *TestableUtils::findChild(QObject *parent, const QString &objectName)
{
    QObjectList list = ObjectUtils::allChildren(parent);

    QObject *res = 0;
    foreach (QObject* object, list) {
        if (object->objectName() == objectName) {
            res = object;
            break;
        }
    }

    return res;
}

static QObject *provider(QQmlEngine *engine, QJSEngine *scriptEngine) {
    Q_UNUSED(engine);
    Q_UNUSED(scriptEngine);

    TestableUtils* object = new TestableUtils();

    return object;
}

static void registerTestableUtils() {
    qmlRegisterSingletonType<TestableUtils>("Testable", 1, 0, "TestableUtils", provider);
}

Q_COREAPP_STARTUP_FUNCTION(registerTestableUtils)


static void enableAutoTest() {
    /* This function do nothing. But that would enable
     * autotest plugin panel in Qt Creator 4.1
     */

    auto ref = [=](){
        int argc = 0;
        char *argv[] = {0};
        TestableUtils test;
        QTest::qExec(&test, argc, argv);
     };
     Q_UNUSED(ref);
}

Q_COREAPP_STARTUP_FUNCTION(enableAutoTest)

