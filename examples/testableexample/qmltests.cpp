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

    Automator testable(&engine);

    QObjectList objects = testable.findChildren("DummyItem");

    QCOMPARE(objects.size() , 1);

    objects = testable.findChildren("SampleWindow");

    QCOMPARE(objects.size() , 1);


    Automator::wait(5000);
}

