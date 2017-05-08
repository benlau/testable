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
    void automatorSearchWindow();

    void automatorObtainSingletonObject();

    void automatorRunTestCase();

    void automatorRunTestCase_fails();

    void automatorRunTestCase_onNonRootObject();


    void autmatorCreatorTracker();

    void automatorWaitUntilSignal();

    void gallery();
};

#endif // TESTABLEUNITTESTS_H
