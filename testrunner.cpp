#include <QTest>
#include <QtQuickTest/quicktest.h>
#include <QMetaObject>
#include <QMetaMethod>
#include "testrunner.h"

TestRunner::TestRunner()
{

}

TestRunner::~TestRunner()
{
    QObject* object;
    QVariant item;

    foreach (item, m_testObjects) {
        object = item.value<QObject*>();
        if (object) {
            delete object;
        }
    }
    m_testObjects.clear();
}

void TestRunner::add(QObject *object)
{
    QVariant value = QVariant::fromValue<QObject*>(object);
    m_testObjects.append(value);
}

void TestRunner::add(const QString &path)
{
    add(QVariant(path));
}

bool TestRunner::exec(QStringList arguments)
{
    QObject *object;
    QVariant item;
    bool error = false;

    foreach (item,m_testObjects) {
        object = item.value<QObject*>();
        if (object) {
            error |= run(object, arguments);
        } else if (item.type() == QMetaType::QString) {
            error != run(item.toString(), arguments);
        }
    }

    return error;
}

int TestRunner::count() const
{
    return m_testObjects.size();
}

void TestRunner::add(QVariant value)
{
    m_testObjects.append(value);
}

bool TestRunner::run(QObject *object, const QStringList& arguments)
{
    const QMetaObject *meta = object->metaObject();
    QStringList args = arguments;
    QString executable = args.takeAt(0);
    bool execute; // Should it execute this test object?
    QStringList params; // params for qTest
    params << executable;

    execute = args.size() > 0 ? false : true; // If no argument passed , it should always execute a test object

    foreach (QString arg, args) {

        if (arg == meta->className()) {
            params.clear();
            params << executable;
            execute = true;
            break;
        }

        for (int i = 0 ; i < meta->methodCount();i++){
            if (meta->method(i).name() == arg) {
                params << arg;
                execute = true;
            }
        }
    }

    if (!execute) {
        return false;
    }

    return QTest::qExec(object,params);
}

bool TestRunner::run(QString path, const QStringList &arguments)
{
    QStringList args(arguments);
    QString executable = args.takeAt(0);
    QStringList testcases = arguments.filter(QRegExp("::"));

    if (args.size() !=0 && testcases.size() == 0) {
        return false;
    }

    char **s = (char**) malloc(sizeof(char*) * 10 + testcases.size());
    int idx = 0;
    s[idx++] = executable.toUtf8().data();
    s[idx++] = strdup("-import");
    s[idx++] = path.toUtf8().data();

    foreach( QString testcase,testcases) {
        s[idx++] = testcase.toUtf8().data();
    }
    s[idx++] = 0;

    const char *name = "QuickTests";
    const char *source = SRCDIR;

    bool error = quick_test_main( idx-1, s, name, source);
    free(s);

    return error;
}

