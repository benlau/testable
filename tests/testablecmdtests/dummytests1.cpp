#include <QTest>
#include "dummytests1.h"

DummyTests1::DummyTests1(QObject *parent) : QObject(parent)
{
    auto ref =[=]() {
        QTest::qExec(this, 0, 0);
    };
    Q_UNUSED(ref);
}

void DummyTests1::test1()
{

}

void DummyTests1::test2()
{

}

