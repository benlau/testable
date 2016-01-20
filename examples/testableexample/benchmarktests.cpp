#include <QTest>
#include "benchmarktests.h"

BenchmarkTests::BenchmarkTests(QObject *parent) : QObject(parent)
{

}

void BenchmarkTests::forLoop()
{

    QBENCHMARK {
        QVariantList list;
        for (int i = 0 ; i < 100000 ; i++) {
            QVariantMap item;
            item["value"] = i;
            list << item;
        }
    }

}

