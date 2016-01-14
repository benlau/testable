#ifndef TESTABLE_H
#define TESTABLE_H

#include <QObject>
#include <QQmlApplicationEngine>
#include <QPointer>

/// Testable is a helper component to provide a testable interface over a QQmlApplicationEngine instance.

class Testable
{
public:
    Testable(QQmlApplicationEngine* engine);

    QQmlApplicationEngine *engine() const;

    void setEngine(QQmlApplicationEngine *engine);

    static void wait(int timeout);

    QObjectList findChildren(QString objectName);

private:

    QPointer<QQmlApplicationEngine> m_engine;
};

#endif // TESTABLE_H
