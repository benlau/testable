#include <QTest>
#include <TestRunner>
#include "gallerytests.h"

QStringList GalleryTests::executedTests;

GalleryTests::GalleryTests(QObject *parent) : QObject(parent)
{

}

void GalleryTests::test1()
{
    executedTests << QTest::currentTestFunction();
    TestRunner::defaultInstance()->runEventLoop();
}

void GalleryTests::test2()
{
    executedTests << QTest::currentTestFunction();

}
