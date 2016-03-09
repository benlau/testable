import QtQuick 2.0
import QtQuick.Window 2.0
import Testable 1.0
import QtTest 1.0

Item {
    id: test
    width: 640
    height: 480

    TestCase {
        name: "TestableTests"

        function test_TestRunner() {
            compare(TestRunner.arguments !== undefined, true);
            compare(TestRunner.config !== undefined, true);
        }
    }
}

