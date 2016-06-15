#ifndef TESTUTILS_H
#define TESTUTILS_H

#include <QObject>

class TestUtils : public QObject
{
    Q_OBJECT
public:
    explicit TestUtils(QObject *parent = 0);

signals:

public slots:

    void wait(int timeout = 1000);
};

#endif // TESTUTILS_H
