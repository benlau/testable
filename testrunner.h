#ifndef TESTRUNNER_H
#define TESTRUNNER_H

#include <QObject>

/// Multiple test case runner

class TestRunner
{
public:
    TestRunner();
    ~TestRunner();

    // Add a QObject test suite
    void add(QObject* object);

    // Add Qt Quick test suite
    void add(const QString& path);

    // Add a QObject test suite
    template <typename T> void add();

    bool exec(QStringList arguments);

    // Add a import path for Qt Quick Test suite
    void addImportPath(const QString& path);

    /// Return no. of test objects added
    int count() const;

private:

    void add(QVariant value);

    // Run QTest
    bool run(QObject* object, const QStringList& arguments);

    // Run Qt Quick Tests
    bool run(QString path, const QStringList& arguments);

    QVariantList m_testObjects;

    QStringList m_importPaths;
};

template <typename T>
void TestRunner::add()
{
    add(new T());
}

#endif // TESTRUNNER_H
