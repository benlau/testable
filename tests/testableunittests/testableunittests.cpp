#include <QtCore>
#include <QTest>
#include <QQmlApplicationEngine>
#include <Automator>
#include <TestRunner>
#include "testableunittests.h"
#include "testablefunctions.h"

TestableUnitTests::TestableUnitTests(QObject *parent) : QObject(parent)
{
    auto ref = [=]() {
        QTest::qExec(this, 0, 0); // Autotest detect available test cases of a QObject by looking for "QTest::qExec" in source code
    };
    Q_UNUSED(ref);
}

void TestableUnitTests::test_walk()
{

    QQmlApplicationEngine engine;
    engine.load(QUrl::fromLocalFile(QString(SRCDIR) + "/SnapshotSample1.qml"));

    int count = 0;
    Testable::walk(engine.rootObjects()[0], [&](QObject* object, QObject* parent) {
        Q_UNUSED(object);
        Q_UNUSED(parent);
        count++;
        return true;
    });

    QCOMPARE(count, 4);
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

