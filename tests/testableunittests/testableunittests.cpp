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
    QDir dir;
    generator.setRoot(dir.currentPath());
    generator.scan("/Testable", QString(SRCDIR) + "../testableunittests");
    generator.scan("/Testable2", QString(SRCDIR) + "../testableunittests");

    qDebug() << generator.text();

    QVERIFY(!generator.text().isEmpty());
    QVERIFY(generator.save("resource.qrc"));
}
