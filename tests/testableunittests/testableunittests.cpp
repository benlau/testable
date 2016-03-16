#include <QtCore>
#include <QTest>
#include "testableunittests.h"
#include "resourcegenerator.h"

TestableUnitTests::TestableUnitTests(QObject *parent) : QObject(parent)
{

}

void TestableUnitTests::resourceGenerator()
{
    ResourceGenerator generator;
    generator.scan("/",QString(SRCDIR) + "../");

    QVERIFY(!generator.text().isEmpty());
    QVERIFY(generator.save("resource.qrc"));
}
