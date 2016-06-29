QML Unit Test Utilities
=======================

Qt offers two testing frameworks : [QTest](http://doc.qt.io/qt-5/qtest.html) for C++ and [Qt Quick Test](http://doc.qt.io/qt-5/qtquick-qtquicktest.html) for QML. They are powerful testing library. However, they have few problems:

1. QTEST_MIAN() in QTest run test cases from a single QObject object. If you put all test cases into a single object, it may become a god object.
2. QUICK_TEST_MAIN() in Qt Quick Test do not export the QQmlEngine instance. Therefore you can not set context properties and use custom QQuickImageProvider

Testable a solution for those problems. The features:

1. Support to run tests from mutiple QObject
2. Support to run QTest (C++) and Quick Tests (QML) in a single project
3. Run specific test case / test object by command line
4. Utilities to search QQuickItem from Repeater/Flickable/ListView/GridView
5. Execute unit test written in Javascript by C++ ( Automator.runTestCase() )

Classes

1. TestRunner - Multiple test objects runner
2. Automator - Automator provides an interface to manipulate UI object loaded by QQmlApplicationEngine
3. ResourceGenerator - Generate .qrc according to the file tree
 
Installation
===========

    qpm install com.github.benlau.testable

Example
=======

Please refer to the project in examples folder


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
Config: Using QtTest library 5.5.0, Qt 5.5.0 (x86_64-little_endian-lp64 shared (dynamic) release build; by Clang 6.0 (clang-600.0.56) (Apple))
PASS   : DummyTests1::initTestCase()
PASS   : DummyTests1::test1()
PASS   : DummyTests1::test2()
PASS   : DummyTests1::cleanupTestCase()
Totals: 4 passed, 0 failed, 0 skipped, 0 blacklisted
********* Finished testing of DummyTests1 *********
********* Start testing of DummyTests2 *********
Config: Using QtTest library 5.5.0, Qt 5.5.0 (x86_64-little_endian-lp64 shared (dynamic) release build; by Clang 6.0 (clang-600.0.56) (Apple))
PASS   : DummyTests2::initTestCase()
PASS   : DummyTests2::test1()
FAIL!  : DummyTests2::fail() 'false' returned FALSE. ()
   Loc: [../testableexample/dummytests2.cpp(16)]
PASS   : DummyTests2::cleanupTestCase()
Totals: 3 passed, 1 failed, 0 skipped, 0 blacklisted
********* Finished testing of DummyTests2 *********
```

