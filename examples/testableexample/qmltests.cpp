#include <QTest>
#include <QQmlApplicationEngine>
#include "testable.h"
#include "qmltests.h"

QmlTests::QmlTests(QObject *parent) : QObject(parent)
{

}

void QmlTests::interactive()
{
    QQmlApplicationEngine engine;
    engine.load(QUrl::fromLocalFile(QString(SRCDIR) + "/SampleWindow.qml"));

    Testable testable(&engine);

    QObjectList objects = testable.findChildren("DummyItem");

    QCOMPARE(objects.size() , 1);

    objects = testable.findChildren("SampleWindow");

    QCOMPARE(objects.size() , 1);


    Testable::wait(5000);
}

