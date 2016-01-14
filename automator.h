#pragma once
#include <QObject>
#include <QQmlApplicationEngine>
#include <QPointer>

/// Automator provides an interface to manipulate UI object loaded by QQmlApplicationEngine

class Automator
{
public:
    Automator(QQmlApplicationEngine* engine);

    QQmlApplicationEngine *engine() const;

    void setEngine(QQmlApplicationEngine *engine);

    static void wait(int timeout);

    QObject* findObject(QString objectName);

    QObjectList findObjects(QString objectName);

private:

    QObjectList findObjects(QObject* object, QString objectName);

    QPointer<QQmlApplicationEngine> m_engine;
};

