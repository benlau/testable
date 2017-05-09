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

void Testable::walk(QObject *object, std::function<bool (QObject *)> predicate)
{
    QMap<QObject*, bool> map;

    std::function<bool(QObject*)> _walk;

    _walk = [&](QObject* object) -> bool {

        if (!object || map[object]) {
            return true;
        }

        map[object] = true;

        if (!predicate(object)) {
            return false;
        }

        if (inherited(object,"QQuickRepeater")) {
            int count = object->property("count").toInt();

            for (int i = 0 ;  i < count ;i++) {
                QQuickItem* item;
                QMetaObject::invokeMethod(object,"itemAt",Qt::DirectConnection,
                                          Q_RETURN_ARG(QQuickItem*,item),
                                          Q_ARG(int,i));

                if (!_walk(item)) {
                    return false;
                }
            }

        } else if (inherited(object, "QQuickFlickable") || inherited(object, "QQuickWindow")) {

            QQuickItem* contentItem = object->property("contentItem").value<QQuickItem*>();
            qDebug() << "content item" << contentItem;

            if (contentItem) {
                QList<QQuickItem *>items = contentItem->childItems() ;

                for (int i = 0 ;  i < items.size() ; i++) {
                    qDebug() << "i" << i;
                    if (!_walk(items.at(i))){
                        return false;
                    }
                }
            }
        }

        QObjectList children = object->children();

        for (int i = 0 ; i < children.size();i++) {
            if (!_walk(children.at(i))) {
                return false;
            }
        }

        return true;
    };

    _walk(object);
}
