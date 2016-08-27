#pragma once
#include <QObject>
#include <QQmlApplicationEngine>
#include <QPointer>
#include <QQuickItem>
#include <QPointF>

/// Automator provides an interface to manipulate UI object loaded by QQmlApplicationEngine

class Automator : public QObject
{
    Q_OBJECT
public:
    Automator(QQmlApplicationEngine* engine);

    QQmlApplicationEngine *engine() const;

    void setEngine(QQmlApplicationEngine *engine);

    static void wait(int timeout);

    QObject* findObject(QString objectName);

    QObjectList findObjects(QString objectName);

    bool waitExists(QString objectName,int timeout = 1000);


    bool waitUntil(QString objectName, QString property, QVariant value, int timeout = 1000);

    // If the point paremter is missed. It will hit the center point
    bool click(QQuickItem *item,  int delay = 100, QPointF point = QPointF());

    bool click(QQuickItem *item, QString childObjectName);

    bool click(QString name, int delay = 100, QPointF point = QPointF());

    // Click on the view directly
    bool click(int interval= 100 ,QPointF = QPointF());

    bool anyError() const;

    void setAnyError(bool anyError);

    bool runTestCase(QStringList filters = QStringList()) const;

    QObject* obtainSingletonObject(QString package, int versionMajor, int versionMinor, QString typeName);

    QQuickItem* createTracker(QQuickItem* target,QColor color, qreal opacity = 0.3);

    static bool waitUntil(QObject *object, QString property, QVariant value,int timeout = 1000);

    /// Wait until a signal is emietted from object
    static bool waitUntil(QObject *object, const char* signal, int timeout = 1000);

private slots:
    void onWarnings(QList<QQmlError>);

private:

    QObjectList findObjects(QObject* object, QString objectName);

    QPointer<QQmlApplicationEngine> m_engine;

    QQuickWindow* window();

    bool m_anyError;
};

