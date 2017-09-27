import QtQuick 2.0
import Testable 1.0
import QtTest 1.0

Item {
    id: test
    width: 640
    height: 480

    TestCase {
        name: "ContextProperty"

        function test_available() {
            TestRunner.prepare("");
            // CustomProperty is registered by engine hook
            compare(CustomProperty.value1, 1);
        }
    }
}
