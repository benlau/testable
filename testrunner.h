#ifndef TESTRUNNER_H
#define TESTRUNNER_H

#include <QObject>

/// Multiple test case runner

class TestRunner
{
public:
    TestRunner();
    ~TestRunner();

    void add(QObject* object);

    // Add Qt Quick Tests
    void add(const QString& path);

    template <typename T>
    void add() {
        add(new T());
    }

    bool exec(QStringList arguments);

    /// Return no. of test objects added
    int count() const;

private:

    void add(QVariant value);

    // Run QTest
    bool run(QObject* object, const QStringList& arguments);

    // Run Qt Quick Tests
    bool run(QString path, const QStringList& arguments);

    QVariantList m_testObjects;
};

#endif // TESTRUNNER_H
