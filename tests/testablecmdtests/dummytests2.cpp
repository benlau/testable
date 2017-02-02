#include <QTest>
#include "dummytests2.h"

DummyTests2::DummyTests2(QObject *parent) : QObject(parent)
{
    auto ref =[=]() {
        QTest::qExec(this, 0, 0);
    };
    Q_UNUSED(ref);
}

void DummyTests2::test1()
{

}

void DummyTests2::fail()
{
    QVERIFY(false);
}

