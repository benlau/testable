#include <QQmlEngine>
#include <QJSEngine>
#include <QtQml>
#include "testrunnerwrapper.h"

TestRunnerWrapper::TestRunnerWrapper(QObject *parent) : QObject(parent)
{

}

QStringList TestRunnerWrapper::arguments() const
{
    QStringList res;
    TestRunner* runner = TestRunner::defautInstance();

    if (runner) {
        res = runner->arguments();
    }

    return res;
}

QVariantMap TestRunnerWrapper::config() const
{
    QVariantMap res;
    TestRunner* runner = TestRunner::defautInstance();
    if (runner) {
        res = runner->config();
    }
    return res;
}


static QObject *provider(QQmlEngine *engine, QJSEngine *scriptEngine) {
    Q_UNUSED(engine);
    Q_UNUSED(scriptEngine);

    TestRunnerWrapper* object = new TestRunnerWrapper();

    return object;
}

class TestableTestRunnerWrapperRegistrationHelper {

public:
    TestableTestRunnerWrapperRegistrationHelper() {
        qmlRegisterSingletonType<TestRunnerWrapper>("Testable", 1, 0, "TestRunner", provider);
    }
};

static TestableTestRunnerWrapperRegistrationHelper registerHelper;
