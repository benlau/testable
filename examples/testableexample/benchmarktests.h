#pragma once

#include <QObject>

class BenchmarkTests : public QObject
{
    Q_OBJECT
public:
    explicit BenchmarkTests(QObject *parent = 0);

signals:

private slots:
    void forLoop();

private:
};

