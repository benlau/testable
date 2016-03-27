#ifndef QMLTESTS_H
#define QMLTESTS_H

#include <QObject>

class QmlTests : public QObject
{
    Q_OBJECT
public:
    explicit QmlTests(QObject *parent = 0);

signals:

public slots:

private slots:
    void interactive();
    void errorWarning();
};

#endif // QMLTESTS_H
