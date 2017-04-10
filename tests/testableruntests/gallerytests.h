#ifndef GALLERYTESTS_H
#define GALLERYTESTS_H

#include <QObject>

class GalleryTests : public QObject
{
    Q_OBJECT
public:
    static QStringList executedTests;

    explicit GalleryTests(QObject *parent = 0);

signals:

public slots:

private slots:

    void test1();

    void test2();

};

#endif // GALLERYTESTS_H
