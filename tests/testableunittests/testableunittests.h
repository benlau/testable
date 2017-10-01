#ifndef TESTABLEUNITTESTS_H
#define TESTABLEUNITTESTS_H

#include <QObject>

class TestableUnitTests : public QObject
{
    Q_OBJECT
public:
    explicit TestableUnitTests(QObject *parent = 0);

signals:

public slots:

private slots:

    void test_walk();

    void automatorSearchWindow();

    void automatorObtainSingletonObject();

    void automatorWaitUntilSignal();
};

#endif // TESTABLEUNITTESTS_H
