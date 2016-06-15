#include <QEventLoop>
#include <QTimer>
#include <QtQml>
#include "testutils.h"

TestUtils::TestUtils(QObject *parent) : QObject(parent)
{

}

void TestUtils::wait(int timeout)
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

    TestUtils* object = new TestUtils();

    return object;
}
class TestUtilsRegistrationHelper {

public:
    TestUtilsRegistrationHelper() {
        qmlRegisterSingletonType<TestUtils>("Testable", 1, 0, "TestUtils", provider);
    }
};

static TestUtilsRegistrationHelper registerHelper;

