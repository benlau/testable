#include <QTest>
#include <QQmlApplicationEngine>
#include "automator.h"
#include "qmltests.h"

QmlTests::QmlTests(QObject *parent) : QObject(parent)
{

}

void QmlTests::interactive()
{
    QQmlApplicationEngine engine;
    engine.load(QUrl::fromLocalFile(QString(SRCDIR) + "/SampleWindow.qml"));

    Automator automator(&engine);

    QObjectList objects = automator.findObjects("DummyItem");

    QCOMPARE(objects.size() , 1);

    objects = automator.findObjects("SampleWindow");

    QCOMPARE(objects.size() , 1);

    objects = automator.findObjects("RepeaterItem");

    QCOMPARE(objects.size() , 5);

    objects = automator.findObjects("ListViewItem");

    QCOMPARE(objects.size() , 3);

    Automator::wait(5000);
}

void QmlTests::errorWarning()
{
    QQmlApplicationEngine engine;
    Automator automator(&engine);

    engine.load(QUrl::fromLocalFile(QString(SRCDIR) + "/ItemWithError.qml"));

    QVERIFY(!automator.anyError());
}

