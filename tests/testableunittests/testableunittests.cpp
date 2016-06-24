#include <QtCore>
#include <QTest>
#include <QQmlApplicationEngine>
#include <Automator>
#include <ResourceGenerator>
#include "testableunittests.h"

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

void TestableUnitTests::automatorSearchWindow()
{

    QQmlApplicationEngine engine;
    engine.load(QUrl::fromLocalFile(QString(SRCDIR) + "/window.qml"));

    Automator automator(&engine);

    QObjectList list = automator.findObjects("Item1");
    QCOMPARE(list.count(), 1);

    list = automator.findObjects("Item2");
    QCOMPARE(list.count(), 1);

}

void TestableUnitTests::automatorObtainSingletonObject()
{
    QQmlApplicationEngine engine;

    engine.addImportPath(QString(SRCDIR));
    engine.load(QUrl::fromLocalFile(QString(SRCDIR) + "/window.qml"));

    Automator automator(&engine);
    QObject* store = automator.obtainSingletonObject("PackageA",1,0,"Store");
    QVERIFY(store);
}

void TestableUnitTests::automatorRunTestCase()
{
    QQmlApplicationEngine engine;

    engine.addImportPath(QString(SRCDIR));
    engine.addImportPath("qrc:///");
    engine.load(QUrl::fromLocalFile(QString(SRCDIR) + "/SceneTest.qml"));
    Automator automator(&engine);

    QVERIFY(automator.runTestCase());

    QObject* testCase = automator.findObject("testCase");
    QVERIFY(testCase);
    QCOMPARE(testCase->property("executedCount").toInt(), 4);

    testCase->setProperty("executedCount", 0);
    QVERIFY(automator.runTestCase(QStringList() << "test_def"));
    QCOMPARE(testCase->property("executedCount").toInt(), 3);

}
