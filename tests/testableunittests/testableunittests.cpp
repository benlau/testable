#include <QtCore>
#include <QTest>
#include <QQmlApplicationEngine>
#include <Automator>
#include <TestRunner>
#include "testableunittests.h"

TestableUnitTests::TestableUnitTests(QObject *parent) : QObject(parent)
{
    auto ref = [=]() {
        QTest::qExec(this, 0, 0); // Autotest detect available test cases of a QObject by looking for "QTest::qExec" in source code
    };
    Q_UNUSED(ref);
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

void TestableUnitTests::automatorRunTestCase_onNonRootObject()
{
    QQmlApplicationEngine engine;

    engine.addImportPath(QString(SRCDIR));
    engine.addImportPath("qrc:///");
    engine.load(QUrl::fromLocalFile(QString(SRCDIR) + "/Dummy.qml"));
    engine.load(QUrl::fromLocalFile(QString(SRCDIR) + "/TestableCaseTests.qml"));
    Automator automator(&engine);
    QVERIFY(automator.runTestCase());

    QObject* testCase = automator.findObject("testCase");
    QVERIFY(testCase);
    QCOMPARE(testCase->property("executedCount").toInt(), 4);
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

void TestableUnitTests::gallery()
{

    TestRunner runner;
    int count = 0;
    QStringList args;

    qDebug() << "Run default gallery function";
    QVERIFY(runner.gallery()(QStringList()) == false);

    runner.setGallery([&](const QStringList& arguments) {
        args = arguments;
        count++;
        return true;
    });

    QVERIFY(runner.gallery()(QStringList()) == true);

    QCOMPARE(count, 1);
    QCOMPARE(args, QStringList());

    QVERIFY(runner.exec(QStringList() << "app" << "--gallery" << "input.json"));

    QCOMPARE(count, 2);
    QCOMPARE(args, QStringList() << "input.json");
}
