#include <QQuickWindow>
#include <QEventLoop>
#include <QTimer>
#include <QQuickItem>
#include <QTime>
#include <QTest>
#include "automator.h"

static bool inherited(QObject* object,QString className) {
    bool res = false;

    const QMetaObject *metaObject = object->metaObject();

    while (metaObject) {
        if (metaObject->className() == className) {
            res = true;
            break;
        }
        metaObject = metaObject->superClass();
    }


    return res;
}

Automator::Automator(QQmlApplicationEngine* engine)
{
    setEngine(engine);
}


QQmlApplicationEngine *Automator::engine() const
{
    return m_engine;
}

void Automator::setEngine(QQmlApplicationEngine *engine)
{
    m_engine = engine;
}

void Automator::wait(int timeout) {

    QEventLoop loop;
    QTimer timer;
    QObject::connect(&timer,SIGNAL(timeout()),
            &loop,SLOT(quit()));
    timer.start(timeout);
    loop.exec();

}

QObject *Automator::findObject(QString objectName)
{
    QObjectList list = findObjects(objectName);
    QObject* res = 0;

    if (list.size() > 0) {
        res = list.first();
    }

    return res;
}

QObjectList Automator::findObjects(QString objectName)
{
    QObjectList result;
    QObject *firstObject = m_engine->rootObjects().first();

    if (!firstObject) {
        return result;
    }

    QObjectList subResult = findObjects(firstObject, objectName);

    if (subResult.size() > 0) {
        result << subResult;
    }

    return result;
}

bool Automator::waitExists(QString objectName, int timeout)
{
    QTime time;
    time.start();

    while (true) {
        QObject* object = findObject(objectName);
        if (object) {
            break;
        }
        wait(100);

        if (time.elapsed() > timeout) {
            qWarning() << "waitExists() : Time out";
            return false;
        }
    }

    return true;

}

bool Automator::waitUntil(QObject *object, QString property, QVariant value, int timeout)
{
    QVariant objectValue = object->property(property.toLocal8Bit().constData());
    QTime time;
    time.start();

    while (objectValue != value) {
        wait(100);
        objectValue = object->property(property.toLocal8Bit().constData());

        if (time.elapsed() > timeout) {
            qWarning() << "waitUntil() : Time out";
            return false;
        }
    }
    return true;
}

bool Automator::waitUntil(QString objectName, QString property, QVariant value, int timeout)
{
    QTime time;
    time.start();

    QObject* object = findObject(objectName);
    if (!object) {
        qWarning() << "Object not found" << objectName;
        return false;
    }

    return waitUntil(object, property, value, timeout);
}

bool Automator::click(QQuickItem *item, int delay,  QPointF pt)
{
    QQuickWindow* win = window();
    if (!win) {
        qWarning() << "click: No window object";
        return false;
    }

    QPointF hit;
    if (pt.isNull()) {
        int w = item->width();
        int h = item->height();
        int cx =  w /2;
        int cy =  h / 2;
        hit = item->mapToScene(QPointF(cx,cy));
    } else {
        hit = item->mapToScene(pt);
    }

    QTest::mouseClick(win, Qt::LeftButton,
                      Qt::NoModifier,
                      hit.toPoint(),
                      delay);
    return true;
}

bool Automator::click(QQuickItem *item, QString childObjectName)
{
    QObjectList list = findObjects(item, childObjectName);
    QQuickItem* child = 0;

    if (list.size() == 0) {
        return false;
    }

    child = qobject_cast<QQuickItem*>(list.first());
    if (!child) {
        return false;
    }

    return click(child);
}

bool Automator::click(QString objectName, int delay, QPointF point)
{
    QQuickItem* item = qobject_cast<QQuickItem*>(findObject(objectName));

    if (!item) {
        qWarning() << "Object not found" << objectName;
        return false;
    }

    return click(item, delay, point);
}

QObjectList Automator::findObjects(QObject *object, QString objectName)
{
    QObjectList result;

    if (!object) {
        return result;
    }

    if (object->objectName() == objectName) {
        result << object;
    }

    if ( inherited(object,"QQuickRepeater")) {
        int count = object->property("count").toInt();

        for (int i = 0 ;  i < count ;i++) {
            QQuickItem* item;
            QMetaObject::invokeMethod(object,"itemAt",Qt::DirectConnection,
                                      Q_RETURN_ARG(QQuickItem*,item),
                                      Q_ARG(int,i));
            QObjectList subResult = findObjects(item, objectName);
            if (subResult.size() > 0) {
                result.append(subResult);
            }
        }

    } else if (inherited(object, "QQuickFlickable")) {

        QQuickItem* contentItem = object->property("contentItem").value<QQuickItem*>();
        if (contentItem) {

            QList<QQuickItem *>items = contentItem->childItems() ;

            for (int i = 0 ;  i < items.size() ; i++) {
                QObjectList subResult = findObjects(items.at(i),objectName);
                if (subResult.size() > 0) {
                    result.append(subResult);
                }
            }

        }
    }

    QObjectList children = object->children();

    for (int i = 0 ; i < children.size();i++) {
        QObjectList subResult = findObjects(children.at(i), objectName);

        if (subResult.size() > 0) {
            result.append(subResult);
        }
    }

    return result;

}

QQuickWindow *Automator::window()
{
    QObject *firstObject = m_engine->rootObjects().first();
    QQuickWindow *window = qobject_cast<QQuickWindow*>(firstObject);

    return window;
}
