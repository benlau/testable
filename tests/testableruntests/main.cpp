#include <QCoreApplication>
#include <QTimer>
#include <TestRunner>
#include "gallerytests.h"

void testGallery() {
    TestRunner runner;
    runner.add<GalleryTests>();

    Q_ASSERT(!runner.exec(QStringList() << "app"));

    Q_ASSERT(GalleryTests::executedTests.size() == 2);

    GalleryTests::executedTests.clear();

    bool timeout = false;

    QTimer::singleShot(100,[&]() {
        QCoreApplication::instance()->quit();;
        timeout = true;
    });

    Q_ASSERT(!runner.exec(QStringList() << "app" << "--eventloop" << "test1"));

    Q_ASSERT(timeout);

    Q_ASSERT(GalleryTests::executedTests.size() == 1);
    Q_ASSERT(GalleryTests::executedTests[0] == "test1");
}

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    testGallery();

    return 0;
}
