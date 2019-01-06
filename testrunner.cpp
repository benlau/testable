#include <QTest>
#include <QtQuickTest/quicktest.h>
#include <QMetaObject>
#include <QMetaMethod>
#include <QPointer>
#include <QCommandLineParser>
#include <QTemporaryFile>
#include <QVector>
#include "testrunner.h"
#include "automator.h"
#include "priv/objectutils.h"

static TestRunner *m_defaultInstance = nullptr;

TestRunner::TestRunner()
{
    if (m_defaultInstance == nullptr) {
        m_defaultInstance = this;
    }

    m_engineHook = nullptr;
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

    if (m_defaultInstance == this) {
        m_defaultInstance = nullptr;
    }
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
    m_arguments = arguments;

    int indexOfOutFile = -1;
    for(int index = 0; index < m_arguments.size();  ++index) {
         if (m_arguments[index].indexOf("-o") == 0)
         {
             indexOfOutFile = index+1;
             break;
         }
    }

    QFileInfo outputFile;
    QString outputFileExt;
    QString path;
    if(indexOfOutFile != -1)
    {
        outputFile.setFile(arguments[indexOfOutFile]);
        outputFileExt = outputFile.completeSuffix();
        path = outputFile.path() + QDir::separator() + outputFile.baseName() +"_";

    }
    QStringList outputfiles;
    outputfiles.reserve(m_testObjects.size());
    QObject *object;
    QVariant item;
    bool error = false;

    foreach (item,m_testObjects) {
        object = item.value<QObject*>();
        if(indexOfOutFile != -1)
        {

            QString uniquePath ( (object) ? object->metaObject()->className() :  "QuickTests");
            m_arguments[indexOfOutFile] = path + uniquePath + "."+outputFileExt;
        }
        if (object) {
            error |= run(object, m_arguments);
        } else if (item.type() == static_cast<int>(QMetaType::QString)) {
            error |= run(item.toString(), m_arguments);
        }
    }

    return error;
}

void TestRunner::addImportPath(const QString &path)
{
    m_importPaths << path;
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

    QStringList tmp;
    // Always add "-*" to params.
    bool addNext = false;
    foreach (QString arg, args) {
        //-o options pramaters are stored in the next arg
        if (arg.indexOf("-o") == 0) {
             params << arg;
             addNext = true;
             continue;
        }
        else if (arg.indexOf("-") == 0 || addNext) {
            params << arg;
            addNext = false;
        } else {
            tmp << arg;
        }
    }

    args = tmp;

    execute = args.size() > 0 ? false : true; // If no argument passed , it should always execute a test object

    foreach (QString arg, args) {

        if (arg == meta->className()) {
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

    QStringList nonOptionArgs; // Filter all "-" parameter

    bool addNext = false;
    foreach (QString arg, args) {
        if (arg.indexOf("-o") == 0 || addNext == true) {
             addNext = !addNext;
             continue;
        }
        else if (arg.indexOf("-") != 0) {
            nonOptionArgs << arg;
        }
    }

    if (nonOptionArgs.size() !=0 && testcases.size() == 0) {
        // If you non-option args, but not a quick test case. Return
        return false;
    }

    QStringList paths;
    paths << path;
    paths << m_importPaths;

    char **s = static_cast<char**>( malloc(sizeof(char*) * static_cast<size_t>((10 + args.size() + paths.size() * 2))));
    int idx = 0;
    s[idx++] = executable.toUtf8().data();

    foreach (QString p , paths) {
        s[idx++] = strdup("-import");
        s[idx++] = strdup(p.toUtf8().data());
    }

    foreach( QString arg,args) {
        s[idx++] = strdup(arg.toUtf8().data());
    }
    s[idx++] = nullptr;

    const char *name = "QuickTests";
    const char *source = strdup(path.toUtf8().data());


    bool error = quick_test_main( idx-1, s, name, source);
    free(s);

    return error;
}

QVariantMap TestRunner::config() const
{
    return m_config;
}

void TestRunner::setConfig(const QVariantMap &config)
{
    m_config = config;
}

void TestRunner::execEngineHook(QQmlEngine *engine)
{
    if (m_engineHook != nullptr) {
        m_engineHook(engine);
    }
}

void TestRunner::setEngineHook(std::function<void(QQmlEngine*)> func)
{
    m_engineHook = func;
}

QStringList TestRunner::arguments() const
{
    return m_arguments;
}

TestRunner *TestRunner::defaultInstance()
{
    return m_defaultInstance;
}

