#include <QMap>
#include <QQuickItem>
#include "testablefunctions.h"

bool Testable::inherited(QObject *object, const QString &className)
{
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

void Testable::walk(QObject *object, std::function<bool (QObject *, QObject*)> predicate)
{
    QMap<QObject*, bool> map;

    std::function<bool(QObject*, QObject*)> _walk;

    _walk = [&](QObject* object, QObject* parent) -> bool {

        if (!object || map[object]) {
            return true;
        }

        map[object] = true;

        if (!predicate(object, parent)) {
            return false;
        }

        if (inherited(object,"QQuickRepeater")) {
            int count = object->property("count").toInt();

            for (int i = 0 ;  i < count ;i++) {
                QQuickItem* item;
                QMetaObject::invokeMethod(object,"itemAt",Qt::DirectConnection,
                                          Q_RETURN_ARG(QQuickItem*,item),
                                          Q_ARG(int,i));

                if (!_walk(item, object)) {
                    return false;
                }
            }

        } else if (inherited(object, "QQuickFlickable") || inherited(object, "QQuickWindow")) {

            QQuickItem* contentItem = object->property("contentItem").value<QQuickItem*>();

            if (contentItem) {
                QList<QQuickItem *>items = contentItem->childItems() ;
                for (int i = 0 ;  i < items.size() ; i++) {
                    if (!_walk(items.at(i) , object)){
                        return false;
                    }
                }
            }
        }

        QObjectList children = object->children();

        for (int i = 0 ; i < children.size();i++) {
            if (!_walk(children.at(i), object)) {
                return false;
            }
        }

        return true;
    };

    _walk(object, 0);
}

#define CHILDREN_KEY "___children___"

QVariantMap Testable::snapshot(QObject *object)
{
    QMap<QObject*, QVariantMap> map;

    QMap<QObject*, QObject*> parentTable;

    QList<QObject*> backtrace;

    auto capture = [=](QObject* source) {
        QVariantMap dest;
        const QMetaObject* meta = source->metaObject();

        for (int i = 0 ; i < meta->propertyCount(); i++) {
            const QMetaProperty property = meta->property(i);
            const char* name = property.name();
            QString stringName = name;

            QVariant value = source->property(name);

            if (value.canConvert<QObject*>()) {
                continue;
            }
            dest[stringName] = value;
        }
        return dest;
    };

    auto traveler = [&](QObject* object, QObject* parent) {
        parentTable[object] = parent;

        QVariantMap data = capture(object);
        map[object] = data;
        backtrace << object;
        return true;
    };

    walk(object, traveler);

    while (backtrace.size() > 0) {
        auto node = backtrace.takeLast();
        auto parent = parentTable[node];
        if (!parent) {
            break;
        }

        QVariantMap pData = map[parent];
        QVariantList children;
        if (!pData.contains(CHILDREN_KEY)) {
            children = pData[CHILDREN_KEY].toList();
        }

         children << map[node];
         pData[CHILDREN_KEY] = children;
         map[parent] = pData;
    }

    return map[object];
}
