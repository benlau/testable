Testable - Qt/QML Unit Test Utilities
=======================
[![Build Status](https://travis-ci.org/benlau/testable.svg?branch=master)](https://travis-ci.org/benlau/testable)

Qt offers two testing frameworks : [QTest](http://doc.qt.io/qt-5/qtest.html) for C++ and [Qt Quick Test](http://doc.qt.io/qt-5/qtquick-qtquicktest.html) for QML. Testable is an utililiy library to enhance their function.

The features:

1. Support to run tests from mutiple QObjects
2. Support to run QTest (C++) and Quick Tests (QML) in a single project
3. Run specific test case / test object by command line
4. Utilities to search QQuickItem from Repeater/Flickable/ListView/GridView

Classes

1. TestRunner - Multiple test objects runner
2. Automator - Automator provides an interface to manipulate UI object loaded by QQmlApplicationEngine
3. ResourceGenerator - Generate .qrc according to the file tree
 
Installation
===========

    qpm install com.github.benlau.testable

Example
=======

```
int main(int argc, char *argv[])
{
    QGuiApplication app(argc,argv);

    TestRunner runner;

    runner.add<DummyTests1>(); // Run tests in DummyTest1 QObject
    runner.add<DummyTests2>(); // Run tests in DummyTest2 QObject
    // Run Qt Quick Test in SRCDIR. It will scan all qml file begin with tst_
    runner.add(QString(SRCDIR));

    runner.addImportPath("qrc:///");
    runner.setEngineHook(callback);

    bool error = runner.exec(app.arguments());

    if (!error) {
        qWarning() << "All test cases passed!";
    }

    return error;
}
```

Please refer to the project in [examples](https://github.com/benlau/testable/tree/master/examples/testableexample) folder.

Run all tests with function name equal to "test1"

```
$ ./testable test1
********* Start testing of DummyTests1 *********
Config: Using QtTest library 5.5.0, Qt 5.5.0 (x86_64-little_endian-lp64 shared (dynamic) release build; by Clang 6.0 (clang-600.0.56) (Apple))
PASS   : DummyTests1::initTestCase()
PASS   : DummyTests1::test1()
PASS   : DummyTests1::cleanupTestCase()
Totals: 3 passed, 0 failed, 0 skipped, 0 blacklisted
********* Finished testing of DummyTests1 *********
********* Start testing of DummyTests2 *********
Config: Using QtTest library 5.5.0, Qt 5.5.0 (x86_64-little_endian-lp64 shared (dynamic) release build; by Clang 6.0 (clang-600.0.56) (Apple))
PASS   : DummyTests2::initTestCase()
PASS   : DummyTests2::test1()
PASS   : DummyTests2::cleanupTestCase()
Totals: 3 passed, 0 failed, 0 skipped, 0 blacklisted
********* Finished testing of DummyTests2 *********
```

Run all test functions in DummyTests1 test object

```
$ ./testable DummyTests1
********* Start testing of DummyTests1 *********
Config: Using QtTest library 5.5.0, Qt 5.5.0 (x86_64-little_endian-lp64 shared (dynamic) release build; by Clang 6.0 (clang-600.0.56) (Apple))
PASS   : DummyTests1::initTestCase()
PASS   : DummyTests1::test1()
PASS   : DummyTests1::test2()
PASS   : DummyTests1::cleanupTestCase()
Totals: 4 passed, 0 failed, 0 skipped, 0 blacklisted
********* Finished testing of DummyTests1 *********
All test cases passed!
```

Run a test function via qmltest

```
./testable QuickTests::test_dummy1
********* Start testing of QuickTests *********
Config: Using QtTest library 5.5.0, Qt 5.5.0 (x86_64-little_endian-lp64 shared (dynamic) release build; by Clang 6.0 (clang-600.0.56) (Apple))
PASS   : QuickTests::QuickTests::initTestCase()
PASS   : QuickTests::QuickTests::test_dummy1()
PASS   : QuickTests::QuickTests::cleanupTestCase()
Totals: 3 passed, 0 failed, 0 skipped, 0 blacklisted
********* Finished testing of QuickTests *********
```

Run all tests

```
./testable

Starting /Users/benlau/src/github/testable/examples/build-testableexample-Desktop_Qt_5_5_0_clang_64bit-Debug/testable...
********* Start testing of DummyTests1 *********
Config: Using QtTest library 5.5.1, Qt 5.5.1 (x86_64-little_endian-lp64 shared (dynamic) release build; by Clang 6.0 (clang-600.0.56) (Apple))
PASS   : DummyTests1::initTestCase()
PASS   : DummyTests1::test1()
PASS   : DummyTests1::test2()
PASS   : DummyTests1::cleanupTestCase()
Totals: 4 passed, 0 failed, 0 skipped, 0 blacklisted
********* Finished testing of DummyTests1 *********
********* Start testing of DummyTests2 *********
Config: Using QtTest library 5.5.1, Qt 5.5.1 (x86_64-little_endian-lp64 shared (dynamic) release build; by Clang 6.0 (clang-600.0.56) (Apple))
PASS   : DummyTests2::initTestCase()
PASS   : DummyTests2::test1()
FAIL!  : DummyTests2::fail() 'false' returned FALSE. ()
   Loc: [../testableexample/dummytests2.cpp(16)]
PASS   : DummyTests2::cleanupTestCase()
Totals: 3 passed, 1 failed, 0 skipped, 0 blacklisted
********* Finished testing of DummyTests2 *********
********* Start testing of QuickTests *********
Config: Using QtTest library 5.5.1, Qt 5.5.1 (x86_64-little_endian-lp64 shared (dynamic) release build; by Clang 6.0 (clang-600.0.56) (Apple))
PASS   : QuickTests::TestableTests::initTestCase()
PASS   : QuickTests::TestableTests::test_TestRunner()
PASS   : QuickTests::TestableTests::cleanupTestCase()
PASS   : QuickTests::QuickTests::initTestCase()
PASS   : QuickTests::QuickTests::test_dummy1()
PASS   : QuickTests::QuickTests::test_dummy2()
PASS   : QuickTests::QuickTests::cleanupTestCase()
Totals: 7 passed, 0 failed, 0 skipped, 0 blacklisted
********* Finished testing of QuickTests *********
```

Autotests Plugin
================

Qt Creator could not detect the tests written by Testable automatically. And therefore it will show nothing in the "Tests" panel and you can't trigger test via [Autotests](http://doc.qt.io/qtcreator/creator-autotest.html)
 plugin.

To make it work, you have to declare the test object explicitly .

```
DummyTests1::DummyTests1(QObject *parent) : QObject(parent)
{
    auto ref = [=]() {
        QTest::qExec(this, 0, 0); // Autotest detect available test cases of a QObject by looking for "QTest::qExec" in source code
    };
    Q_UNUSED(ref);
}
```

The code does actually nothing but it is required for Autotest's parser to recognize the tests.

Autotests does not allow to declare more than a test within a source file. So you have to add this piece of code per source file.

For Qt Quick Tests, you need to declare QUICK_TEST_SOURCE_DIR in pro file:


project.pro file

```
DEFINES += QUICK_TEST_SOURCE_DIR=\\\"$$PWD\\\"
```

Then place QUICK_TEST_MAIN on your code explicitly.

```
namespace AutoTestRegister {
    QUICK_TEST_MAIN(QuickTests)
}

int main(int argc, char *argv[]) {
```

![Autotests Screenshot](https://raw.githubusercontent.com/benlau/testable/master/docs/screenshot1.png)




