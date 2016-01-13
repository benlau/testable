#include <QTest>
#include <QMetaObject>
#include <QMetaMethod>
#include "testrunner.h"

TestRunner::TestRunner()
{

}

void TestRunner::add(QObject *object)
{
    m_testObjects.append(object);
}

bool TestRunner::exec(QStringList args)
{
    QObject *object;
    bool error = false;

    QString executable = args.at(0);
    args.takeAt(0);

    foreach (object,m_testObjects) {
        const QMetaObject *meta = object->metaObject();
        bool execute; // Should it execute this test object?
        QStringList params; // params for qTest
        params << executable;

        execute = args.size() > 0 ? false : true; // If no argument passed , it should always execute a test object

        foreach (QString arg, args){

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
            continue;
        }

        error |= QTest::qExec(object,params);
    }

    return error;
}

int TestRunner::count() const
{
    return m_testObjects.size();
}

