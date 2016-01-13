#include <QTest>
#include "dummytests2.h"

DummyTests2::DummyTests2(QObject *parent) : QObject(parent)
{

}

void DummyTests2::test1()
{

}

void DummyTests2::fail()
{
    QVERIFY(false);
}

