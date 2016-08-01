import QtQuick 2.0
import Testable 1.0
import QtQuick.Window 2.0

Window {
    id: window

    TestableCase {
        id: testCase
        objectName: "testCase"

        property int executedCount: 0

        function initTestCase() {
            executedCount++;
            wait(100);
        }

        function cleanupTestCase() {
            executedCount++;
        }

        function test_findChild() {
            var child = findChild(window, "testCase");
            compare(child === testCase, true);
            compare(child.hasOwnProperty("executedCount"), true);

            compare(1,1);
            executedCount++;
        }

        function test_def() {
            compare(1,1);
            executedCount++;
        }
    }

}
