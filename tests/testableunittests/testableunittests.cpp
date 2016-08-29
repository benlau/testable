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
    engine.load(QUrl::fromLocalFile(QString(SRCDIR) + "/TestableCaseTests.qml"));
    Automator automator(&engine);

    QVERIFY(automator.runTestCase());

    QObject* testCase = automator.findObject("testCase");
    QVERIFY(testCase);
    QCOMPARE(testCase->property("executedCount").toInt(), 4);

    testCase->setProperty("executedCount", 0);
    QVERIFY(automator.runTestCase(QStringList() << "test_def"));
    QCOMPARE(testCase->property("executedCount").toInt(), 3);

}

void TestableUnitTests::automatorRunTestCase_fails()
{
    QQmlApplicationEngine engine;

    engine.addImportPath(QString(SRCDIR));
    engine.addImportPath("qrc:/");
    engine.load(QUrl::fromLocalFile(QString(SRCDIR) + "/TestableCaseFailTests.qml"));

    Automator automator(&engine);

    QVERIFY(!automator.runTestCase(QStringList() << "test_exception"));

    QVERIFY(!automator.runTestCase());

}

void TestableUnitTests::autmatorCreatorTracker()
{
    QQmlApplicationEngine engine;

    engine.addImportPath(QString(SRCDIR));
    engine.addImportPath("qrc:/");
    engine.load(QUrl::fromLocalFile(QString(SRCDIR) + "/AutomatorCreateTracker.qml"));

    Automator automator(&engine);

    QQuickItem * label = qobject_cast<QQuickItem*>(automator.findObject("label"));
    QVERIFY(label);

    automator.createTracker(label,"red");

}

void TestableUnitTests::automatorWaitUntilSignal()
{
    QTimer * timer = new QTimer(this);
    QTime time;
    time.start();

    timer->setInterval(500);
    timer->setSingleShot(true);
    timer->start();

    QVERIFY(Automator::waitUntilSignal(timer, SIGNAL(timeout())));

    QVERIFY(time.elapsed() >= 400);

    time.start();
    QVERIFY(!Automator::waitUntilSignal(timer, SIGNAL(timeout())));
    QVERIFY(time.elapsed() >= 900);

}
