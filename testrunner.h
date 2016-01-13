#ifndef TESTRUNNER_H
#define TESTRUNNER_H

#include <QObject>

class TestRunner
{
public:
    TestRunner();

    void add(QObject* object);

    template <typename T>
    void add() {
        add(new T());
    }

    bool exec(QStringList arguments);

    /// Return no. of test objects added
    int count() const;

private:
    QObjectList m_testObjects;
};

#endif // TESTRUNNER_H
