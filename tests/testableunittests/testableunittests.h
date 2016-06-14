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
    void resourceGenerator();

    void automatorSearchWindow();

    void automatorObtainSingletonObject();

    void automatorRunTestCase();
};

#endif // TESTABLEUNITTESTS_H
