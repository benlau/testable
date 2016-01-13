#ifndef DUMMYTESTS2_H
#define DUMMYTESTS2_H

#include <QObject>

class DummyTests2 : public QObject
{
    Q_OBJECT
public:
    explicit DummyTests2(QObject *parent = 0);

signals:

public slots:

private slots:

    void test1();

    void fail();
};

#endif // DUMMYTESTS2_H
