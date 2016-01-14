#include <QQuickWindow>
#include <QEventLoop>
#include <QTimer>
#include <QQuickItem>
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

//    QQuickWindow *window = qobject_cast<QQuickWindow*>(firstObject);

//    if (window) {
//        if (window->objectName() == objectName) {
//            result << window;
//        }
//        firstObject = window->children().first();
//    }

    if (!firstObject) {
        return result;
    }

    QObjectList subResult = findObjects(firstObject, objectName);

    if (subResult.size() > 0) {
        result << subResult;
    }

    return result;
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
