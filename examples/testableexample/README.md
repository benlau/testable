Testable Example
================

Command Line Arguments

    ./testable [testcase ...]

Example:

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
