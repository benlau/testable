#ifndef DUMMYTESTS1_H
#define DUMMYTESTS1_H

#include <QObject>

class DummyTests1 : public QObject
{
    Q_OBJECT
public:
    explicit DummyTests1(QObject *parent = 0);

signals:

public slots:

private slots:
    void test1();

    void test2();
};

#endif // DUMMYTESTS1_H
