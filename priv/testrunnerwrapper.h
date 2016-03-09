#ifndef TESTRUNNERWRAPPER_H
#define TESTRUNNERWRAPPER_H

#include <QObject>
#include <QVariantMap>
#include "../testrunner.h"

/// Wrapper of TestRunner for QML

class TestRunnerWrapper : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QStringList arguments READ arguments NOTIFY argumentsChanged)
    Q_PROPERTY(QVariantMap config READ config NOTIFY configChanged)

public:
    explicit TestRunnerWrapper(QObject *parent = 0);

    QStringList arguments() const;

    QVariantMap config() const;

signals:
    void argumentsChanged();

    void configChanged();

private:

};

#endif // TESTRUNNERWRAPPER_H
