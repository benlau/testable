#include <QQuickWindow>
#include <QEventLoop>
#include <QTimer>
#include "testable.h"

Testable::Testable(QQmlApplicationEngine* engine)
{
    setEngine(engine);
}


QQmlApplicationEngine *Testable::engine() const
{
    return m_engine;
}

void Testable::setEngine(QQmlApplicationEngine *engine)
{
    m_engine = engine;
}

void Testable::wait(int timeout) {

    QEventLoop loop;
    QTimer timer;
    QObject::connect(&timer,SIGNAL(timeout()),
            &loop,SLOT(quit()));
    timer.start(timeout);
    loop.exec();

}

QObjectList Testable::findChildren(QString objectName)
{
    QObjectList result;
    QObject *firstObject = m_engine->rootObjects().first();

    QQuickWindow *window = qobject_cast<QQuickWindow*>(firstObject);

    if (window) {
        if (window->objectName() == objectName) {
            result << window;
        }
        firstObject = window->children().first();
    }

    if (!firstObject) {
        return result;
    }

    if (firstObject->objectName() == objectName) {
        result << firstObject;
    }

    QObjectList subResult = firstObject->findChildren<QObject*>(objectName);

    if (subResult.size() > 0)
        result << subResult;

    return result;
}
